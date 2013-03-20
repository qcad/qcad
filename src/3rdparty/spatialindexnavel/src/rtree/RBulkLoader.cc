// Spatial Index Library
//
// Copyright (C) 2002 Navel Ltd.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  Email:
//    mhadji@gmail.com

#include <cstring>
#include <stdio.h>

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "../spatialindex/SpatialIndexImpl.h"
#include "RTree.h"
#include "RLeaf.h"
#include "RIndex.h"
#include "RBulkLoader.h"

using namespace SpatialIndex::RTree;

//
// ExternalSorter::Record
//
ExternalSorter::Record::Record() : m_pData(0)
{
}

ExternalSorter::Record::Record(const Region& r, id_type id, size_t len, byte* pData, size_t s)
: m_r(r), m_id(id), m_len(len), m_pData(pData), m_s(s)
{
}

ExternalSorter::Record::~Record()
{
    // if (m_pData != 0)
    //  delete[] m_pData;
}

bool ExternalSorter::Record::operator<(const Record& r) const
{
	if (m_s != r.m_s)
		throw Tools::IllegalStateException("ExternalSorter::Record::operator<: Incompatible sorting dimensions.");

	if (m_r.m_pHigh[m_s] + m_r.m_pLow[m_s] < r.m_r.m_pHigh[m_s] + r.m_r.m_pLow[m_s])
		return true;
	else
		return false;
}

void ExternalSorter::Record::storeToFile(Tools::TemporaryFile& f)
{
	f.write(static_cast<uint64_t>(m_id));
	f.write(static_cast<uint32_t>(m_r.m_dimension));
	f.write(static_cast<uint32_t>(m_s));

	for (size_t i = 0; i < m_r.m_dimension; ++i)
	{
		f.write(m_r.m_pLow[i]);
		f.write(m_r.m_pHigh[i]);
	}

	f.write(static_cast<uint32_t>(m_len));
	if (m_len > 0) f.write(m_len, m_pData);
}

void ExternalSorter::Record::loadFromFile(Tools::TemporaryFile& f)
{
	m_id = static_cast<id_type>(f.readUInt64());
	uint32_t dim = f.readUInt32();
	m_s = f.readUInt32();

	if (dim != m_r.m_dimension)
	{
		delete[] m_r.m_pLow;
		delete[] m_r.m_pHigh;
		m_r.m_dimension = dim;
		m_r.m_pLow = new double[dim];
		m_r.m_pHigh = new double[dim];
	}

	for (size_t i = 0; i < m_r.m_dimension; ++i)
	{
		m_r.m_pLow[i] = f.readDouble();
		m_r.m_pHigh[i] = f.readDouble();
	}
	
	m_len = static_cast<size_t>(f.readUInt32());
	delete[] m_pData; m_pData = 0;
	if (m_len > 0) f.readBytes(m_len, &m_pData);
}

//
// ExternalSorter
//
ExternalSorter::ExternalSorter(uint32_t u32PageSize, uint32_t u32BufferPages)
: m_bInsertionPhase(true), m_u32PageSize(u32PageSize),
	m_u32BufferPages(u32BufferPages), m_sortedFile(0), m_u64TotalEntries(0), m_stI(0)
{
}

ExternalSorter::~ExternalSorter()
{
	delete m_sortedFile;
	for (m_stI = 0; m_stI < m_buffer.size(); ++m_stI) delete m_buffer[m_stI];

}

void ExternalSorter::insert(Record* r)
{
	if (m_bInsertionPhase == false)
		throw Tools::IllegalStateException("ExternalSorter::insert: Input has already been sorted.");

	m_buffer.push_back(r);
	++m_u64TotalEntries;

	// this will create the initial, sorted buckets before the
	// external merge sort.
	if (m_buffer.size() >= m_u32PageSize * m_u32BufferPages)
	{
		std::sort(m_buffer.begin(), m_buffer.end(), Record::SortAscending());
		Tools::TemporaryFile* tf = new Tools::TemporaryFile();
		for (size_t j = 0; j < m_buffer.size(); ++j)
		{
			m_buffer[j]->storeToFile(*tf);
			delete m_buffer[j];
		}
		m_buffer.clear();
		tf->rewindForReading();
		m_runs.push_back(tf);
	}
}

void ExternalSorter::sort()
{
	if (m_bInsertionPhase == false)
		throw Tools::IllegalStateException("ExternalSorter::sort: Input has already been sorted.");

	if (m_runs.empty())
	{
		// The data fits in main memory. No need to store to disk.
		std::sort(m_buffer.begin(), m_buffer.end(), Record::SortAscending());
		m_bInsertionPhase = false;
		return;
	}

	if (m_buffer.size() > 0)
	{
		// Whatever remained in the buffer (if not filled) needs to be stored
		// as the final bucket.
		std::sort(m_buffer.begin(), m_buffer.end(), Record::SortAscending());
		Tools::TemporaryFile* tf = new Tools::TemporaryFile();
		for (size_t j = 0; j < m_buffer.size(); ++j)
		{
			m_buffer[j]->storeToFile(*tf);
			delete m_buffer[j];
		}
		m_buffer.clear();
		tf->rewindForReading();
		m_runs.push_back(tf);
	}

	m_sortedFile = m_runs.front();

	Record* r;
	uint32_t u32Count;

	while (m_runs.size() > 1)
	{
		Tools::TemporaryFile* tf = new Tools::TemporaryFile();
		std::vector<Tools::TemporaryFile*> buckets;
		std::vector<std::queue<Record*> > buffers;
		std::priority_queue<PQEntry, std::vector<PQEntry>, PQEntry::SortAscending> pq;

		// initialize buffers and priority queue.
		std::list<Tools::TemporaryFile*>::iterator it = m_runs.begin();
		for (uint32_t i = 0; i < (std::min)(m_runs.size(), static_cast<size_t>(m_u32BufferPages)); ++i)
		{
			buckets.push_back(*it);
			buffers.push_back(std::queue<Record*>());

			r = new Record();
			r->loadFromFile(*buckets.back());
				// a run cannot be empty initially, so this should never fail.
			pq.push(PQEntry(r, i));

			for (uint32_t j = 0; j < m_u32PageSize - 1; ++j)
			{
				// fill the buffer with the rest of the page of records.
				try
				{
					r = new Record();
					r->loadFromFile(*buckets.back());
					buffers.back().push(r);
				}
				catch (Tools::EndOfStreamException)
				{
					delete r;
					break;
				}
			}
			++it;
		}

		// exhaust buckets, buffers, and priority queue.
		while (! pq.empty())
		{
			PQEntry e = pq.top(); pq.pop();
			e.m_r->storeToFile(*tf);
			delete e.m_r;

			if (! buckets[e.m_u32Index]->eof() && buffers[e.m_u32Index].empty())
			{
				for (uint32_t j = 0; j < m_u32PageSize; ++j)
				{
					try
					{
						r = new Record();
						r->loadFromFile(*buckets[e.m_u32Index]);
						buffers[e.m_u32Index].push(r);
					}
					catch (Tools::EndOfStreamException)
					{
						delete r;
						break;
					}
				}
			}

			if (! buffers[e.m_u32Index].empty())
			{
				e.m_r = buffers[e.m_u32Index].front();
				buffers[e.m_u32Index].pop();
				pq.push(e);
			}
		}

		tf->rewindForReading();

		// check if another pass is needed.
		u32Count = m_runs.size();
		for (uint32_t i = 0; i < (std::min)(u32Count, m_u32BufferPages); ++i)
		{
			delete m_runs.front();
			m_runs.pop_front();
		}

		if (m_runs.size() == 0)
		{
			m_sortedFile = tf;
			break;
		}
		else
		{
			m_runs.push_back(tf);
		}
	}

	m_bInsertionPhase = false;
}

void ExternalSorter::getNextRecord(Record& r)
{
	if (m_bInsertionPhase == true) throw Tools::IllegalStateException("ExternalSorter::getNextRecord: Input has not been sorted yet.");

	if (m_sortedFile == 0)
	{
		if (m_stI < m_buffer.size())
			r = *(m_buffer[m_stI++]);
		else
			throw Tools::EndOfStreamException("");
	}
	else
		r.loadFromFile(*m_sortedFile);
}

void ExternalSorter::rewind()
{
	if (m_bInsertionPhase == true)
		throw Tools::IllegalStateException("ExternalSorter::rewind: Input has not been sorted yet.");

	if (m_sortedFile != 0) m_sortedFile->rewindForReading();
	else m_stI = 0;
}

inline uint64_t ExternalSorter::getTotalEntries() const
{
	return m_u64TotalEntries;
}

//
// BulkLoader
//
void BulkLoader::bulkLoadUsingSTR(
	SpatialIndex::RTree::RTree* pTree,
	IDataStream& stream,
	size_t bindex,
	size_t bleaf,
	size_t pageSize,
	size_t numberOfPages
) {
	NodePtr n = pTree->readNode(pTree->m_rootID);
	pTree->deleteNode(n.get());

	#ifndef NDEBUG
	std::cerr << "RTree::BulkLoader: Sorting data." << std::endl;
	#endif

	Tools::SmartPointer<ExternalSorter> es = Tools::SmartPointer<ExternalSorter>(new ExternalSorter(pageSize, numberOfPages));

	while (stream.hasNext())
	{
		IData* d = stream.getNext();

		IShape* s; d->getShape(&s);
		Region r; s->getMBR(r);
		delete s;

		byte* pData;
		size_t len;
		d->getData(len, &pData);

		es->insert(new ExternalSorter::Record(r, d->getIdentifier(), len, pData, 0));

		delete d;
	}
	es->sort();

	pTree->m_stats.m_data = es->getTotalEntries();

	// create index levels.
	size_t level = 0;

	while (true)
	{
		#ifndef NDEBUG
		std::cerr << "RTree::BulkLoader: Building level " << level << std::endl;
		#endif

		pTree->m_stats.m_nodesInLevel.push_back(0);

		Tools::SmartPointer<ExternalSorter> es2 = Tools::SmartPointer<ExternalSorter>(new ExternalSorter(800, 2000));
		createLevel(pTree, es, 0, bleaf, bindex, level++, es2, pageSize, numberOfPages);

		es = es2;

		if (es->getTotalEntries() == 1) break;
		es->sort();
	}

	pTree->m_stats.m_treeHeight = level;
	pTree->storeHeader();
}

void BulkLoader::createLevel(
	SpatialIndex::RTree::RTree* pTree,
	Tools::SmartPointer<ExternalSorter> es,
	size_t dimension,
	size_t bleaf,
	size_t bindex,
	size_t level,
	Tools::SmartPointer<ExternalSorter> es2,
	size_t pageSize,
	size_t numberOfPages
) {
	size_t b = (level == 0) ? bleaf : bindex;
	size_t P = static_cast<size_t>(std::ceil(static_cast<double>(es->getTotalEntries()) / static_cast<double>(b)));
	size_t S = static_cast<size_t>(std::ceil(std::sqrt(static_cast<double>(P))));

	if (S == 1 || dimension == pTree->m_dimension - 1)
	{
		// store new pages in storage manager and page information in temporary file.
		std::vector<ExternalSorter::Record> node;
		ExternalSorter::Record r;
		
		while (true)
		{
			try { es->getNextRecord(r); } catch (Tools::EndOfStreamException) { break; }
			node.push_back(r);

			if (node.size() == b)
			{
				Node* n = createNode(pTree, node, level);
				pTree->writeNode(n);
				es2->insert(new ExternalSorter::Record(n->m_nodeMBR, n->m_identifier, 0, 0, 0));
				pTree->m_rootID = n->m_identifier;
					// special case when the root has exactly bindex entries.
				node.clear();
				delete n;
			}
		}

		if (! node.empty())
		{
			Node* n = createNode(pTree, node, level);
			pTree->writeNode(n);
			es2->insert(new ExternalSorter::Record(n->m_nodeMBR, n->m_identifier, 0, 0, 0));
			pTree->m_rootID = n->m_identifier;
			delete n;
		}
	}
	else
	{
		bool bMore = true;

		while (bMore)
		{
			Tools::SmartPointer<ExternalSorter> es3 = Tools::SmartPointer<ExternalSorter>(new ExternalSorter(pageSize, numberOfPages));
			for (size_t i = 0; i < S * b; ++i)
			{
				ExternalSorter::Record* pR = new ExternalSorter::Record();
				try { es->getNextRecord(*pR); } catch (Tools::EndOfStreamException) { bMore = false; break; }
				pR->m_s = dimension + 1;
				es3->insert(pR);
			}
			es3->sort();
			createLevel(pTree, es3, dimension + 1, bindex, bleaf, level, es2, pageSize, numberOfPages);
		}
	}
}

Node* BulkLoader::createNode(SpatialIndex::RTree::RTree* pTree, std::vector<ExternalSorter::Record>& e, size_t level)
{
	Node* n;

	if (level == 0) n = new Leaf(pTree, -1);
	else n = new Index(pTree, -1, level);

	for (size_t cChild = 0; cChild < e.size(); ++cChild)
	{
		n->insertEntry(e[cChild].m_len, e[cChild].m_pData, e[cChild].m_r, e[cChild].m_id);
		e[cChild].m_pData = 0;
	}

	return n;
}

