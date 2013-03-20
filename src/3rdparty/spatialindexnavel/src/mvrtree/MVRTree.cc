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

#include "../spatialindex/SpatialIndexImpl.h"
#include "MVRNode.h"
#include "MVRLeaf.h"
#include "MVRIndex.h"
#include "MVRTree.h"

#undef __USE_BSD
#include <cstring>

using namespace SpatialIndex::MVRTree;

SpatialIndex::MVRTree::Data::Data(size_t len, byte* pData, TimeRegion& r, id_type id)
	: m_id(id), m_region(r), m_pData(0), m_dataLength(len)
{
	if (m_dataLength > 0)
	{
		m_pData = new byte[m_dataLength];
		memcpy(m_pData, pData, m_dataLength);
	}
}

SpatialIndex::MVRTree::Data::~Data()
{
	delete[] m_pData;
}

SpatialIndex::MVRTree::Data* SpatialIndex::MVRTree::Data::clone()
{
	return new Data(m_dataLength, m_pData, m_region, m_id);
}

SpatialIndex::id_type SpatialIndex::MVRTree::Data::getIdentifier() const
{
	return m_id;
}

void SpatialIndex::MVRTree::Data::getShape(IShape** out) const
{
	*out = new TimeRegion(m_region);
}

void SpatialIndex::MVRTree::Data::getData(size_t& len, byte** data) const
{
	len = m_dataLength;
	*data = 0;

	if (m_dataLength > 0)
	{
		*data = new byte[m_dataLength];
		memcpy(*data, m_pData, m_dataLength);
	}
}

size_t SpatialIndex::MVRTree::Data::getByteArraySize()
{
	return
		sizeof(id_type) +
		sizeof(size_t) +
		m_dataLength +
		m_region.getByteArraySize();
}

void SpatialIndex::MVRTree::Data::loadFromByteArray(const byte* ptr)
{
	memcpy(&m_id, ptr, sizeof(id_type));
	ptr += sizeof(id_type);

	delete[] m_pData;
	m_pData = 0;

	memcpy(&m_dataLength, ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	if (m_dataLength > 0)
	{
		m_pData = new byte[m_dataLength];
		memcpy(m_pData, ptr, m_dataLength);
		ptr += m_dataLength;
	}

	m_region.loadFromByteArray(ptr);
}

void SpatialIndex::MVRTree::Data::storeToByteArray(byte** data, size_t& len)
{
	// it is thread safe this way.
	size_t regionsize;
	byte* regiondata = 0;
	m_region.storeToByteArray(&regiondata, regionsize);

	len = sizeof(id_type) + sizeof(size_t) + m_dataLength + regionsize;

	*data = new byte[len];
	byte* ptr = *data;

	memcpy(ptr, &m_id, sizeof(id_type));
	ptr += sizeof(id_type);
	memcpy(ptr, &m_dataLength, sizeof(size_t));
	ptr += sizeof(size_t);

	if (m_dataLength > 0)
	{
		memcpy(ptr, m_pData, m_dataLength);
		ptr += m_dataLength;
	}

	memcpy(ptr, regiondata, regionsize);
	delete[] regiondata;
	// ptr += regionsize;
}

SpatialIndex::ISpatialIndex* SpatialIndex::MVRTree::returnMVRTree(SpatialIndex::IStorageManager& sm, Tools::PropertySet& ps)
{
	SpatialIndex::ISpatialIndex* si = new SpatialIndex::MVRTree::MVRTree(sm, ps);
	return si;
}

SpatialIndex::ISpatialIndex* SpatialIndex::MVRTree::createNewMVRTree(
	SpatialIndex::IStorageManager& sm, double fillFactor, size_t indexCapacity,
	size_t leafCapacity, size_t dimension, MVRTreeVariant rv, id_type& indexIdentifier)
{
	Tools::Variant var;
	Tools::PropertySet ps;

	var.m_varType = Tools::VT_DOUBLE;
	var.m_val.dblVal = fillFactor;
	ps.setProperty("FillFactor", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = indexCapacity;
	ps.setProperty("IndexCapacity", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = leafCapacity;
	ps.setProperty("LeafCapacity", var);

	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = dimension;
	ps.setProperty("Dimension", var);

	var.m_varType = Tools::VT_LONG;
	var.m_val.lVal = rv;
	ps.setProperty("TreeVariant", var);

	ISpatialIndex* ret = returnMVRTree(sm, ps);

	var.m_varType = Tools::VT_LONGLONG;
	var = ps.getProperty("IndexIdentifier");
	indexIdentifier = var.m_val.llVal;

	return ret;
}

SpatialIndex::ISpatialIndex* SpatialIndex::MVRTree::loadMVRTree(IStorageManager& sm, id_type indexIdentifier)
{
	Tools::Variant var;
	Tools::PropertySet ps;

	var.m_varType = Tools::VT_LONGLONG;
	var.m_val.llVal = indexIdentifier;
	ps.setProperty("IndexIdentifier", var);

	return returnMVRTree(sm, ps);
}

SpatialIndex::MVRTree::MVRTree::MVRTree(IStorageManager& sm, Tools::PropertySet& ps) :
	m_pStorageManager(&sm),
	m_headerID(StorageManager::NewPage),
	m_treeVariant(RV_RSTAR),
	m_fillFactor(0.7),
	m_indexCapacity(100),
	m_leafCapacity(100),
	m_nearMinimumOverlapFactor(32),
	m_splitDistributionFactor(0.4),
	m_reinsertFactor(0.3),
	m_strongVersionOverflow(0.8),
	//m_strongVersionUnderflow(0.2),
	m_versionUnderflow(0.3),
	m_dimension(2),
	m_bTightMBRs(true),
	m_bHasVersionCopied(false),
	m_currentTime(0.0),
	m_pointPool(500),
	m_regionPool(1000),
	m_indexPool(100),
	m_leafPool(100)
{
#ifdef PTHREADS
	pthread_rwlock_init(&m_rwLock, NULL);
#else
	m_rwLock = false;
#endif

	Tools::Variant var = ps.getProperty("IndexIdentifier");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType == Tools::VT_LONGLONG) m_headerID = var.m_val.llVal;
		else if (var.m_varType == Tools::VT_LONG) m_headerID = var.m_val.lVal;
			// for backward compatibility only.
		else throw Tools::IllegalArgumentException("MVRTree: Property IndexIdentifier must be Tools::VT_LONGLONG");

		initOld(ps);
	}
	else
	{
		initNew(ps);
		var.m_varType = Tools::VT_LONGLONG;
		var.m_val.llVal = m_headerID;
		ps.setProperty("IndexIdentifier", var);
	}
}

SpatialIndex::MVRTree::MVRTree::~MVRTree()
{
#ifdef PTHREADS
	pthread_rwlock_destroy(&m_rwLock);
#endif

	storeHeader();
}

//
// ISpatialIndex interface
//

void SpatialIndex::MVRTree::MVRTree::insertData(size_t len, const byte* pData, const IShape& shape, id_type id)
{
	if (shape.getDimension() != m_dimension) throw Tools::IllegalArgumentException("insertData: Shape has the wrong number of dimensions.");
	const Tools::IInterval* ti = dynamic_cast<const Tools::IInterval*>(&shape);
	if (ti == 0) throw Tools::IllegalArgumentException("insertData: Shape does not support the Tools::IInterval interface.");
	if (ti->getLowerBound() < m_currentTime) throw Tools::IllegalArgumentException("insertData: Shape start time is older than tree current time.");

#ifdef PTHREADS
	Tools::ExclusiveLock lock(&m_rwLock);
#else
	if (m_rwLock == false) m_rwLock = true;
	else throw Tools::ResourceLockedException("insertData: cannot acquire an exclusive lock");
#endif

	try
	{
		// convert the shape into a TimeRegion (R-Trees index regions only; i.e., approximations of the shapes).
		Region mbrold;
		shape.getMBR(mbrold);

		TimeRegionPtr mbr = m_regionPool.acquire();
		mbr->makeDimension(mbrold.m_dimension);

		memcpy(mbr->m_pLow, mbrold.m_pLow, mbrold.m_dimension * sizeof(double));
		memcpy(mbr->m_pHigh, mbrold.m_pHigh, mbrold.m_dimension * sizeof(double));
		mbr->m_startTime = ti->getLowerBound();
		mbr->m_endTime = std::numeric_limits<double>::max();

		byte* buffer = 0;

		if (len > 0)
		{
			buffer = new byte[len];
			memcpy(buffer, pData, len);
		}

		insertData_impl(len, buffer, *mbr, id);
			// the buffer is stored in the tree. Do not delete here.

#ifndef PTHREADS
		m_rwLock = false;
#endif
	}
	catch (...)
	{
#ifndef PTHREADS
		m_rwLock = false;
#endif
		throw;
	}
}

bool SpatialIndex::MVRTree::MVRTree::deleteData(const IShape& shape, id_type id)
{
	if (shape.getDimension() != m_dimension) throw Tools::IllegalArgumentException("deleteData: Shape has the wrong number of dimensions.");
	const Tools::IInterval* ti = dynamic_cast<const Tools::IInterval*>(&shape);
	if (ti == 0) throw Tools::IllegalArgumentException("deleteData: Shape does not support the Tools::IInterval interface.");

#ifdef PTHREADS
	Tools::ExclusiveLock lock(&m_rwLock);
#else
	if (m_rwLock == false) m_rwLock = true;
	else throw Tools::ResourceLockedException("deleteData: cannot acquire an exclusive lock");
#endif

	try
	{
		Region mbrold;
		shape.getMBR(mbrold);

		TimeRegionPtr mbr = m_regionPool.acquire();
		mbr->makeDimension(mbrold.m_dimension);

		memcpy(mbr->m_pLow, mbrold.m_pLow, mbrold.m_dimension * sizeof(double));
		memcpy(mbr->m_pHigh, mbrold.m_pHigh, mbrold.m_dimension * sizeof(double));
		mbr->m_startTime = ti->getLowerBound();
		mbr->m_endTime = ti->getUpperBound();

		bool ret = deleteData_impl(*mbr, id);

#ifndef PTHREADS
		m_rwLock = false;
#endif

		return ret;
	}
	catch (...)
	{
#ifndef PTHREADS
		m_rwLock = false;
#endif
		throw;
	}
}

void SpatialIndex::MVRTree::MVRTree::containsWhatQuery(const IShape& query, IVisitor& v)
{
	if (query.getDimension() != m_dimension) throw Tools::IllegalArgumentException("containsWhatQuery: Shape has the wrong number of dimensions.");
	rangeQuery(ContainmentQuery, query, v);
}

void SpatialIndex::MVRTree::MVRTree::intersectsWithQuery(const IShape& query, IVisitor& v)
{
	if (query.getDimension() != m_dimension) throw Tools::IllegalArgumentException("intersectsWithQuery: Shape has the wrong number of dimensions.");
	rangeQuery(IntersectionQuery, query, v);
}

void SpatialIndex::MVRTree::MVRTree::pointLocationQuery(const Point& query, IVisitor& v)
{
	if (query.m_dimension != m_dimension) throw Tools::IllegalArgumentException("pointLocationQuery: Shape has the wrong number of dimensions.");
	const Tools::IInterval* ti = dynamic_cast<const Tools::IInterval*>(&query);
	if (ti == 0) throw Tools::IllegalArgumentException("pointLocationQuery: Shape does not support the Tools::IInterval interface.");
	TimeRegion r(query, query, *ti);
	rangeQuery(IntersectionQuery, r, v);
}

void SpatialIndex::MVRTree::MVRTree::nearestNeighborQuery(uint32_t k, const IShape& query, IVisitor& v, INearestNeighborComparator& nnc)
{
	throw Tools::IllegalStateException("nearestNeighborQuery: not impelmented yet.");
}

void SpatialIndex::MVRTree::MVRTree::nearestNeighborQuery(uint32_t k, const IShape& query, IVisitor& v)
{
	if (query.getDimension() != m_dimension) throw Tools::IllegalArgumentException("nearestNeighborQuery: Shape has the wrong number of dimensions.");
	NNComparator nnc;
	nearestNeighborQuery(k, query, v, nnc);
}

void SpatialIndex::MVRTree::MVRTree::selfJoinQuery(const IShape& query, IVisitor& v)
{
	throw Tools::IllegalStateException("selfJoinQuery: not impelmented yet.");
}

void SpatialIndex::MVRTree::MVRTree::queryStrategy(IQueryStrategy& qs)
{
#ifdef PTHREADS
	Tools::SharedLock lock(&m_rwLock);
#else
	if (m_rwLock == false) m_rwLock = true;
	else throw Tools::ResourceLockedException("queryStrategy: cannot acquire a shared lock");
#endif

	id_type next = m_roots[m_roots.size() - 1].m_id;
	bool hasNext = true;

	try
	{
		while (hasNext)
		{
			NodePtr n = readNode(next);
			qs.getNextEntry(*n, next, hasNext);
		}

#ifndef PTHREADS
		m_rwLock = false;
#endif
	}
	catch (...)
	{
#ifndef PTHREADS
		m_rwLock = false;
#endif
		throw;
	}
}

void SpatialIndex::MVRTree::MVRTree::getIndexProperties(Tools::PropertySet& out) const
{
	Tools::Variant var;

	// dimension
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_dimension;
	out.setProperty("Dimension", var);

	// index capacity
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_indexCapacity;
	out.setProperty("IndexCapacity", var);

	// leaf capacity
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_leafCapacity;
	out.setProperty("LeafCapacity", var);

	// Tree variant
	var.m_varType = Tools::VT_LONG;
	var.m_val.lVal = m_treeVariant;
	out.setProperty("TreeVariant", var);

	// fill factor
	var.m_varType = Tools::VT_DOUBLE;
	var.m_val.dblVal = m_fillFactor;
	out.setProperty("FillFactor", var);

	// near minimum overlap factor
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_nearMinimumOverlapFactor;
	out.setProperty("NearMinimumOverlapFactor", var);

	// split distribution factor
	var.m_varType = Tools::VT_DOUBLE;
	var.m_val.dblVal = m_splitDistributionFactor;
	out.setProperty("SplitDistributionFactor", var);

	// reinsert factor
	var.m_varType = Tools::VT_DOUBLE;
	var.m_val.dblVal = m_reinsertFactor;
	out.setProperty("ReinsertFactor", var);

	// tight MBRs
	var.m_varType = Tools::VT_BOOL;
	var.m_val.blVal = m_bTightMBRs;
	out.setProperty("EnsureTightMBRs", var);

	// index pool capacity
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_indexPool.getCapacity();
	out.setProperty("IndexPoolCapacity", var);

	// leaf pool capacity
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_leafPool.getCapacity();
	out.setProperty("LeafPoolCapacity", var);

	// region pool capacity
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_regionPool.getCapacity();
	out.setProperty("RegionPoolCapacity", var);

	// point pool capacity
	var.m_varType = Tools::VT_ULONG;
	var.m_val.ulVal = m_pointPool.getCapacity();
	out.setProperty("PointPoolCapacity", var);

	// strong version overflow
	var.m_varType = Tools::VT_DOUBLE;
	var.m_val.dblVal = m_strongVersionOverflow;
	out.setProperty("StrongVersionOverflow", var);

	// strong version underflow
	//var.m_varType = Tools::VT_DOUBLE;
	//var.m_val.dblVal = m_strongVersionUnderflow;
	//out.setProperty("StrongVersionUnderflow", var);

	// weak version underflow
	var.m_varType = Tools::VT_DOUBLE;
	var.m_val.dblVal = m_versionUnderflow;
	out.setProperty("VersionUnderflow", var);
}

void SpatialIndex::MVRTree::MVRTree::addCommand(ICommand* pCommand, CommandType ct)
{
	switch (ct)
	{
		case CT_NODEREAD:
			m_readNodeCommands.push_back(Tools::SmartPointer<ICommand>(pCommand));
			break;
		case CT_NODEWRITE:
			m_writeNodeCommands.push_back(Tools::SmartPointer<ICommand>(pCommand));
			break;
		case CT_NODEDELETE:
			m_deleteNodeCommands.push_back(Tools::SmartPointer<ICommand>(pCommand));
			break;
	}
}

bool SpatialIndex::MVRTree::MVRTree::isIndexValid()
{
	bool ret = true;
	std::stack<ValidateEntry> st;
	std::set<id_type> visitedEntries;
	size_t degenerateEntries = 0;

	for (size_t cRoot = 0; cRoot < m_roots.size(); cRoot++)
	{
		NodePtr root = readNode(m_roots[cRoot].m_id);

		if (root->m_level != m_stats.m_treeHeight[cRoot] - 1)
		{
			std::cerr << "Invalid tree height." << std::endl;
			return false;
		}

		ValidateEntry e(0, root->m_nodeMBR, root);
		e.m_bIsDead = (root->m_nodeMBR.m_endTime < std::numeric_limits<double>::max()) ? true : false;
		st.push(e);
	}

	while (! st.empty())
	{
		ValidateEntry e = st.top(); st.pop();

		std::set<id_type>::iterator itSet = visitedEntries.find(e.m_pNode->m_identifier);
		if (itSet == visitedEntries.end())
		{
			visitedEntries.insert(e.m_pNode->m_identifier);
			if (e.m_pNode->m_nodeMBR.m_startTime == e.m_pNode->m_nodeMBR.m_endTime) degenerateEntries++;
		}

		TimeRegion tmpRegion;
		tmpRegion = m_infiniteRegion;

		for (size_t cDim = 0; cDim < tmpRegion.m_dimension; cDim++)
		{
			for (size_t cChild = 0; cChild < e.m_pNode->m_children; cChild++)
			{
				tmpRegion.m_pLow[cDim] = std::min(tmpRegion.m_pLow[cDim], e.m_pNode->m_ptrMBR[cChild]->m_pLow[cDim]);
				tmpRegion.m_pHigh[cDim] = std::max(tmpRegion.m_pHigh[cDim], e.m_pNode->m_ptrMBR[cChild]->m_pHigh[cDim]);
			}
		}

		tmpRegion.m_startTime = e.m_pNode->m_nodeMBR.m_startTime;
		tmpRegion.m_endTime = e.m_pNode->m_nodeMBR.m_endTime;
		if (! (tmpRegion == e.m_pNode->m_nodeMBR))
		{
			std::cerr << "Invalid parent information." << std::endl;
			ret = false;
		}

		if (! e.m_bIsDead)
		{
			tmpRegion.m_startTime = e.m_parentMBR.m_startTime;
			tmpRegion.m_endTime = e.m_parentMBR.m_endTime;
			if (! (tmpRegion == e.m_parentMBR))
			{
				std::cerr << "Error in parent (Node id: " << e.m_pNode->m_identifier << ", Parent id: " << e.m_parentID << ")." << std::endl;
				ret = false;
			}
		}

		if (e.m_pNode->m_level != 0)
		{
			for (size_t cChild = 0; cChild < e.m_pNode->m_children; cChild++)
			{
				NodePtr ptrN = readNode(e.m_pNode->m_pIdentifier[cChild]);

				bool bIsDead =
					(e.m_pNode->m_ptrMBR[cChild]->m_endTime < std::numeric_limits<double>::max() || e.m_bIsDead) ? true : false;

				// if the parent says that this child is dead, force it dead since
				// this information is not propagated for efficiency and is inconsistent.
				if (bIsDead) ptrN->m_nodeMBR.m_endTime = e.m_pNode->m_ptrMBR[cChild]->m_endTime;

				ValidateEntry tmpEntry(e.m_pNode->m_identifier, *(e.m_pNode->m_ptrMBR[cChild]), ptrN);
				tmpEntry.m_bIsDead = bIsDead;
				st.push(tmpEntry);
			}
		}
	}

	//std::cerr << "Total accessible nodes: " << visitedEntries.size() << std::endl;
	//std::cerr << "Degenerate nodes: " << degenerateEntries << std::endl;

	return ret;
}

void SpatialIndex::MVRTree::MVRTree::getStatistics(IStatistics** out) const
{
	*out = new Statistics(m_stats);
}

void SpatialIndex::MVRTree::MVRTree::initNew(Tools::PropertySet& ps)
{
	Tools::Variant var;

	// tree variant
	var = ps.getProperty("TreeVariant");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_LONG || (var.m_val.lVal != RV_LINEAR && var.m_val.lVal != RV_QUADRATIC && var.m_val.lVal != RV_RSTAR))
			throw Tools::IllegalArgumentException("initNew: Property TreeVariant must be Tools::VT_LONG and of MVRTreeVariant type");

		m_treeVariant = static_cast<MVRTreeVariant>(var.m_val.lVal);
	}

	// fill factor
	// it cannot be larger than 50%, since linear and quadratic split algorithms
	// require assigning to both nodes the same number of entries.
	var = ps.getProperty("FillFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (
			var.m_varType != Tools::VT_DOUBLE ||
			var.m_val.dblVal <= 0.0 ||
			//((m_treeVariant == RV_LINEAR || m_treeVariant == RV_QUADRATIC) && var.m_val.dblVal > 0.5) ||
			var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initNew: Property FillFactor must be Tools::VT_DOUBLE and in (0.0, 1.0) for RSTAR, (0.0, 0.5) for LINEAR and QUADRATIC");

		m_fillFactor = var.m_val.dblVal;
	}

	// index capacity
	var = ps.getProperty("IndexCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG || var.m_val.ulVal < 10)
			throw Tools::IllegalArgumentException("initNew: Property IndexCapacity must be Tools::VT_ULONG and >= 10");

		m_indexCapacity = var.m_val.ulVal;
	}

	// leaf capacity
	var = ps.getProperty("LeafCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG || var.m_val.ulVal < 10)
			throw Tools::IllegalArgumentException("initNew: Property LeafCapacity must be Tools::VT_ULONG and >= 10");

		m_leafCapacity = var.m_val.ulVal;
	}

	// near minimum overlap factor
	var = ps.getProperty("NearMinimumOverlapFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG || var.m_val.ulVal < 1 ||	var.m_val.ulVal > m_indexCapacity ||	var.m_val.ulVal > m_leafCapacity)
			throw Tools::IllegalArgumentException("initNew: Property NearMinimumOverlapFactor must be Tools::VT_ULONG and less than both index and leaf capacities");

		m_nearMinimumOverlapFactor = var.m_val.ulVal;
	}

	// split distribution factor
	var = ps.getProperty("SplitDistributionFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_DOUBLE || var.m_val.dblVal <= 0.0 || var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initNew: Property SplitDistributionFactor must be Tools::VT_DOUBLE and in (0.0, 1.0)");

		m_splitDistributionFactor = var.m_val.dblVal;
	}

	// reinsert factor
	var = ps.getProperty("ReinsertFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_DOUBLE || var.m_val.dblVal <= 0.0 || var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initNew: Property ReinsertFactor must be Tools::VT_DOUBLE and in (0.0, 1.0)");

		m_reinsertFactor = var.m_val.dblVal;
	}

	// dimension
	var = ps.getProperty("Dimension");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initNew: Property Dimension must be Tools::VT_ULONG");
		if (var.m_val.ulVal <= 1) throw Tools::IllegalArgumentException("initNew: Property Dimension must be greater than 1");

		m_dimension = var.m_val.ulVal;
	}

	// tight MBRs
	var = ps.getProperty("EnsureTightMBRs");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_BOOL) throw Tools::IllegalArgumentException("initNew: Property EnsureTightMBRs must be Tools::VT_BOOL");

		m_bTightMBRs = var.m_val.blVal;
	}

	// index pool capacity
	var = ps.getProperty("IndexPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initNew: Property IndexPoolCapacity must be Tools::VT_ULONG");

		m_indexPool.setCapacity(var.m_val.ulVal);
	}

	// leaf pool capacity
	var = ps.getProperty("LeafPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initNew: Property LeafPoolCapacity must be Tools::VT_ULONG");

		m_leafPool.setCapacity(var.m_val.ulVal);
	}

	// region pool capacity
	var = ps.getProperty("RegionPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initNew: Property RegionPoolCapacity must be Tools::VT_ULONG");

		m_regionPool.setCapacity(var.m_val.ulVal);
	}

	// point pool capacity
	var = ps.getProperty("PointPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initNew: Property PointPoolCapacity must be Tools::VT_ULONG");

		m_pointPool.setCapacity(var.m_val.ulVal);
	}

	// strong version overflow
	var = ps.getProperty("StrongVersionOverflow");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_DOUBLE || var.m_val.dblVal <= 0.0 || var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initNew: Property StrongVersionOverflow must be Tools::VT_DOUBLE and in (0.0, 1.0)");

		m_strongVersionOverflow = var.m_val.dblVal;
	}

	// strong version underflow
	//var = ps.getProperty("StrongVersionUnderflow");
	//if (var.m_varType != Tools::VT_EMPTY)
	//{
	//	if (var.m_varType != Tools::VT_DOUBLE ||
	//			var.m_val.dblVal <= 0.0 ||
	//			var.m_val.dblVal >= 1.0) throw Tools::IllegalArgumentException("Property StrongVersionUnderflow must be Tools::VT_DOUBLE and in (0.0, 1.0)");

	//	m_strongVersionUnderflow = var.m_val.dblVal;
	//}

	// weak version underflow
	var = ps.getProperty("VersionUnderflow");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_DOUBLE || var.m_val.dblVal <= 0.0 || var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initNew: Property VersionUnderflow must be Tools::VT_DOUBLE and in (0.0, 1.0)");

		m_versionUnderflow = var.m_val.dblVal;
	}

	m_infiniteRegion.makeInfinite(m_dimension);

	m_stats.m_treeHeight.push_back(1);
	m_stats.m_nodesInLevel.push_back(1);

	Leaf root(this, -1);
	root.m_nodeMBR.m_startTime = 0.0;
	root.m_nodeMBR.m_endTime = std::numeric_limits<double>::max();
	writeNode(&root);
	m_roots.push_back(RootEntry(root.m_identifier, root.m_nodeMBR.m_startTime, root.m_nodeMBR.m_endTime));

	storeHeader();
}

void SpatialIndex::MVRTree::MVRTree::initOld(Tools::PropertySet& ps)
{
	loadHeader();

	// only some of the properties may be changed.
	// the rest are just ignored.

	Tools::Variant var;

	// tree variant
	var = ps.getProperty("TreeVariant");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_LONG || (var.m_val.lVal != RV_LINEAR && var.m_val.lVal != RV_QUADRATIC && var.m_val.lVal != RV_RSTAR))
			throw Tools::IllegalArgumentException("initOld: Property TreeVariant must be Tools::VT_LONG and of MVRTreeVariant type");

		m_treeVariant = static_cast<MVRTreeVariant>(var.m_val.lVal);
	}

	// near minimum overlap factor
	var = ps.getProperty("NearMinimumOverlapFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG || var.m_val.ulVal < 1 || var.m_val.ulVal > m_indexCapacity || var.m_val.ulVal > m_leafCapacity)
			throw Tools::IllegalArgumentException("initOld: Property NearMinimumOverlapFactor must be Tools::VT_ULONG and less than both index and leaf capacities");

		m_nearMinimumOverlapFactor = var.m_val.ulVal;
	}

	// split distribution factor
	var = ps.getProperty("SplitDistributionFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_DOUBLE || var.m_val.dblVal <= 0.0 || var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initOld: Property SplitDistributionFactor must be Tools::VT_DOUBLE and in (0.0, 1.0)");

		m_splitDistributionFactor = var.m_val.dblVal;
	}

	// reinsert factor
	var = ps.getProperty("ReinsertFactor");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_DOUBLE ||var.m_val.dblVal <= 0.0 || var.m_val.dblVal >= 1.0)
			throw Tools::IllegalArgumentException("initOld: Property ReinsertFactor must be Tools::VT_DOUBLE and in (0.0, 1.0)");

		m_reinsertFactor = var.m_val.dblVal;
	}

	// tight MBRs
	var = ps.getProperty("EnsureTightMBRs");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_BOOL) throw Tools::IllegalArgumentException("initOld: Property EnsureTightMBRs must be Tools::VT_BOOL");

		m_bTightMBRs = var.m_val.blVal;
	}

	// index pool capacity
	var = ps.getProperty("IndexPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initOld: Property IndexPoolCapacity must be Tools::VT_ULONG");

		m_indexPool.setCapacity(var.m_val.ulVal);
	}

	// leaf pool capacity
	var = ps.getProperty("LeafPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initOld: Property LeafPoolCapacity must be Tools::VT_ULONG");

		m_leafPool.setCapacity(var.m_val.ulVal);
	}

	// region pool capacity
	var = ps.getProperty("RegionPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initOld: Property RegionPoolCapacity must be Tools::VT_ULONG");

		m_regionPool.setCapacity(var.m_val.ulVal);
	}

	// point pool capacity
	var = ps.getProperty("PointPoolCapacity");
	if (var.m_varType != Tools::VT_EMPTY)
	{
		if (var.m_varType != Tools::VT_ULONG) throw Tools::IllegalArgumentException("initOld: Property PointPoolCapacity must be Tools::VT_ULONG");

		m_pointPool.setCapacity(var.m_val.ulVal);
	}

	m_infiniteRegion.makeInfinite(m_dimension);
}

void SpatialIndex::MVRTree::MVRTree::storeHeader()
{
	const size_t headerSize = 
		sizeof(size_t) +                                // size of m_roots
		m_roots.size() *
		(sizeof(id_type) + 2 * sizeof(double)) +        // m_roots
		sizeof(MVRTreeVariant) +                        // m_treeVariant
		sizeof(double)+                                 // m_fillFactor
		sizeof(size_t) +                                // m_indexCapacity
		sizeof(size_t) +                                // m_leafCapacity
		sizeof(size_t) +                                // m_nearMinimumOverlapFactor
		sizeof(double) +                                // m_splitDistributionFactor
		sizeof(double) +                                // m_reinsertFactor
		sizeof(size_t) +                                // m_dimension
		sizeof(byte) +                                  // m_bTightMBRs
		sizeof(size_t) +                                // m_stats.m_nodes
		sizeof(size_t) +                                // m_stats.m_totalData
		sizeof(size_t) +                                // m_stats.m_deadIndexNodes
		sizeof(size_t) +                                // m_stats.m_deadLeafNodes
		sizeof(size_t) +                                // m_stats.m_data
		sizeof(size_t) +                                // size of m_stats.m_treeHeight
		m_stats.m_treeHeight.size() * sizeof(size_t) +  // m_stats.m_treeHeight
		sizeof(double) +                                // m_strongVersionOverflow
		//sizeof(double) +                              // m_strongVersionUnderflow
		sizeof(double) +                                // m_versionUnderflow
		sizeof(double) +                                // m_currentTime
		sizeof(size_t) +                                // m_nodesInLevel size
		m_stats.m_nodesInLevel.size() * sizeof(size_t); // m_nodesInLevel values

	byte* header = new byte[headerSize];
	byte* ptr = header;

	size_t ul = m_roots.size();
	memcpy(ptr, &ul, sizeof(size_t));
	ptr += sizeof(size_t);

	for (size_t cIndex = 0; cIndex < m_roots.size(); cIndex++)
	{
		RootEntry& e = m_roots[cIndex];
		memcpy(ptr, &(e.m_id), sizeof(id_type));
		ptr += sizeof(id_type);
		memcpy(ptr, &(e.m_startTime), sizeof(double));
		ptr += sizeof(double);
		memcpy(ptr, &(e.m_endTime), sizeof(double));
		ptr += sizeof(double);
	}

	memcpy(ptr, &m_treeVariant, sizeof(MVRTreeVariant));
	ptr += sizeof(MVRTreeVariant);
	memcpy(ptr, &m_fillFactor, sizeof(double));
	ptr += sizeof(double);
	memcpy(ptr, &m_indexCapacity, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &m_leafCapacity, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &m_nearMinimumOverlapFactor, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &m_splitDistributionFactor, sizeof(double));
	ptr += sizeof(double);
	memcpy(ptr, &m_reinsertFactor, sizeof(double));
	ptr += sizeof(double);
	memcpy(ptr, &m_dimension, sizeof(size_t));
	ptr += sizeof(size_t);
	byte c = (byte) m_bTightMBRs;
	memcpy(ptr, &c, sizeof(byte));
	ptr += sizeof(byte);
	memcpy(ptr, &(m_stats.m_nodes), sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &(m_stats.m_totalData), sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &(m_stats.m_deadIndexNodes), sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &(m_stats.m_deadLeafNodes), sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &(m_stats.m_data), sizeof(size_t));
	ptr += sizeof(size_t);

	ul = m_stats.m_treeHeight.size();
	memcpy(ptr, &ul, sizeof(size_t));
	ptr += sizeof(size_t);

	for (size_t cIndex = 0; cIndex < m_stats.m_treeHeight.size(); cIndex++)
	{
		ul = m_stats.m_treeHeight[cIndex];
		memcpy(ptr, &ul, sizeof(size_t));
		ptr += sizeof(size_t);
	}

	memcpy(ptr, &m_strongVersionOverflow, sizeof(double));
	ptr += sizeof(double);
	//memcpy(ptr, &m_strongVersionUnderflow, sizeof(double));
	//ptr += sizeof(double);
	memcpy(ptr, &m_versionUnderflow, sizeof(double));
	ptr += sizeof(double);
	memcpy(ptr, &m_currentTime, sizeof(double));
	ptr += sizeof(double);

	ul = m_stats.m_nodesInLevel.size();
	memcpy(ptr, &ul, sizeof(size_t));
	ptr += sizeof(size_t);

	for (size_t cLevel = 0; cLevel < m_stats.m_nodesInLevel.size(); cLevel++)
	{
		ul = m_stats.m_nodesInLevel[cLevel];
		memcpy(ptr, &ul, sizeof(size_t));
		ptr += sizeof(size_t);
	}

	m_pStorageManager->storeByteArray(m_headerID, headerSize, header);

	delete[] header;
}

void SpatialIndex::MVRTree::MVRTree::loadHeader()
{
	size_t headerSize;
	byte* header = 0;
	m_pStorageManager->loadByteArray(m_headerID, headerSize, &header);

	byte* ptr = header;

	size_t rootsSize;
	memcpy(&rootsSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	for (size_t cIndex = 0; cIndex < rootsSize; cIndex++)
	{
		RootEntry e;
		memcpy(&(e.m_id), ptr, sizeof(id_type));
		ptr += sizeof(id_type);
		memcpy(&(e.m_startTime), ptr, sizeof(double));
		ptr += sizeof(double);
		memcpy(&(e.m_endTime), ptr, sizeof(double));
		ptr += sizeof(double);
		m_roots.push_back(e);
	}

	memcpy(&m_treeVariant, ptr, sizeof(MVRTreeVariant));
	ptr += sizeof(MVRTreeVariant);
	memcpy(&m_fillFactor, ptr, sizeof(double));
	ptr += sizeof(double);
	memcpy(&m_indexCapacity, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&m_leafCapacity, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&m_nearMinimumOverlapFactor, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&m_splitDistributionFactor, ptr, sizeof(double));
	ptr += sizeof(double);
	memcpy(&m_reinsertFactor, ptr, sizeof(double));
	ptr += sizeof(double);
	memcpy(&m_dimension, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	byte c;
	memcpy(&c, ptr, sizeof(byte));
	m_bTightMBRs = (c != 0);
	ptr += sizeof(byte);
	memcpy(&(m_stats.m_nodes), ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&(m_stats.m_totalData), ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&(m_stats.m_deadIndexNodes), ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&(m_stats.m_deadLeafNodes), ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&(m_stats.m_data), ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	size_t treeHeightSize;
	memcpy(&treeHeightSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	for (size_t cIndex = 0; cIndex < treeHeightSize; cIndex++)
	{
		size_t ul;
		memcpy(&ul, ptr, sizeof(size_t));
		m_stats.m_treeHeight.push_back(ul);
		ptr += sizeof(size_t);
	}

	memcpy(&m_strongVersionOverflow, ptr, sizeof(double));
	ptr += sizeof(double);
	//memcpy(&m_strongVersionUnderflow, ptr, sizeof(double));
	//ptr += sizeof(double);
	memcpy(&m_versionUnderflow, ptr, sizeof(double));
	ptr += sizeof(double);
	memcpy(&m_currentTime, ptr, sizeof(double));
	ptr += sizeof(double);

	size_t nodesInLevelSize;
	memcpy(&nodesInLevelSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	for (size_t cLevel = 0; cLevel < nodesInLevelSize; cLevel++)
	{
		size_t ul;
		memcpy(&ul, ptr, sizeof(size_t));
		ptr += sizeof(size_t);
		m_stats.m_nodesInLevel.push_back(ul);
	}

	delete[] header;
}

void SpatialIndex::MVRTree::MVRTree::insertData_impl(size_t dataLength, byte* pData, TimeRegion& mbr, id_type id)
{
	assert(mbr.getDimension() == m_dimension);
	assert(m_currentTime <= mbr.m_startTime);

	std::stack<id_type> pathBuffer;
	m_currentTime = mbr.m_startTime;

	NodePtr root = readNode(m_roots[m_roots.size() - 1].m_id);
	NodePtr l = root->chooseSubtree(mbr, 0, pathBuffer);

	if (l.get() == root.get())
	{
		assert(root.unique());
		root.relinquish();
	}
	l->insertData(dataLength, pData, mbr, id, pathBuffer, m_infiniteRegion, -1, false);

	m_stats.m_data++;
	m_stats.m_totalData++;
}

void SpatialIndex::MVRTree::MVRTree::insertData_impl(size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, size_t level)
{
	assert(mbr.getDimension() == m_dimension);

	std::stack<id_type> pathBuffer;

	NodePtr root = readNode(m_roots[m_roots.size() - 1].m_id);
	NodePtr l = root->chooseSubtree(mbr, level, pathBuffer);

	assert(l->m_level == level);

	if (l.get() == root.get())
	{
		assert(root.unique());
		root.relinquish();
	}
	l->insertData(dataLength, pData, mbr, id, pathBuffer, m_infiniteRegion, -1, false);
}

bool SpatialIndex::MVRTree::MVRTree::deleteData_impl(const TimeRegion& mbr, id_type id)
{
	assert(mbr.m_dimension == m_dimension);

	m_currentTime = mbr.m_endTime;

	std::stack<id_type> pathBuffer;
	NodePtr root = readNode(m_roots[m_roots.size() - 1].m_id);
	NodePtr l = root->findLeaf(mbr, id, pathBuffer);

	if (l.get() == root.get())
	{
		assert(root.unique());
		root.relinquish();
	}

	if (l.get() != 0)
	{
		l->deleteData(id, mbr.m_endTime, pathBuffer);
		m_stats.m_data--;
		return true;
	}

	return false;
}

SpatialIndex::id_type SpatialIndex::MVRTree::MVRTree::writeNode(Node* n)
{
	byte* buffer;
	size_t dataLength;
	n->storeToByteArray(&buffer, dataLength);

	id_type page;
	if (n->m_identifier < 0) page = StorageManager::NewPage;
	else page = n->m_identifier;

	try
	{
		m_pStorageManager->storeByteArray(page, dataLength, buffer);
		delete[] buffer;
	}
	catch (InvalidPageException& e)
	{
		delete[] buffer;
		std::cerr << e.what() << std::endl;
		//std::cerr << *this << std::endl;
		throw Tools::IllegalStateException("writeNode: failed with Tools::InvalidPageException");
	}

	if (n->m_identifier < 0)
	{
		n->m_identifier = page;
		m_stats.m_nodes++;
	}

	m_stats.m_writes++;

	for (size_t cIndex = 0; cIndex < m_writeNodeCommands.size(); cIndex++)
	{
		m_writeNodeCommands[cIndex]->execute(*n);
	}

	return page;
}

SpatialIndex::MVRTree::NodePtr SpatialIndex::MVRTree::MVRTree::readNode(id_type id)
{
	size_t dataLength;
	byte* buffer;

	try
	{
		m_pStorageManager->loadByteArray(id, dataLength, &buffer);
	}
	catch (InvalidPageException& e)
	{
		std::cerr << e.what() << std::endl;
		//std::cerr << *this << std::endl;
		throw Tools::IllegalStateException("readNode: failed with Tools::InvalidPageException");
	}

	try
	{
		size_t nodeType;
		memcpy(&nodeType, buffer, sizeof(size_t));

		NodePtr n;

		if (nodeType == PersistentIndex) n = m_indexPool.acquire();
		else if (nodeType == PersistentLeaf) n = m_leafPool.acquire();
		else throw Tools::IllegalStateException("readNode: failed reading the correct node type information");

		if (n.get() == 0)
		{
			if (nodeType == PersistentIndex) n = NodePtr(new Index(this, -1, 0), &m_indexPool);
			else if (nodeType == PersistentLeaf) n = NodePtr(new Leaf(this, -1), &m_leafPool);
		}

		//n->m_pTree = this;
		n->m_identifier = id;
		n->loadFromByteArray(buffer);

		m_stats.m_reads++;

		for (size_t cIndex = 0; cIndex < m_readNodeCommands.size(); cIndex++)
		{
			m_readNodeCommands[cIndex]->execute(*n);
		}

		delete[] buffer;
		return n;
	}
	catch (...)
	{
		delete[] buffer;
		throw;
	}
}

void SpatialIndex::MVRTree::MVRTree::deleteNode(Node* n)
{
	try
	{
		m_pStorageManager->deleteByteArray(n->m_identifier);
	}
	catch (InvalidPageException& e)
	{
		std::cerr << e.what() << std::endl;
		//std::cerr << *this << std::endl;
		throw Tools::IllegalStateException("deleteNode: failed with Tools::InvalidPageException");
	}

	m_stats.m_nodes--;
	//size_t ul = m_stats.m_nodesInLevel.size() - 1;
	//m_stats.m_nodesInLevel[ul][n->m_level] = m_stats.m_nodesInLevel[ul][n->m_level] - 1;

	for (size_t cIndex = 0; cIndex < m_deleteNodeCommands.size(); cIndex++)
	{
		m_deleteNodeCommands[cIndex]->execute(*n);
	}
}

void SpatialIndex::MVRTree::MVRTree::rangeQuery(RangeQueryType type, const IShape& query, IVisitor& v)
{
	// any shape that implements IInterval and IShape, can be used here.
	// FIXME: I am not using ITimeShape yet, even though I should.

	const Tools::IInterval* ti = dynamic_cast<const Tools::IInterval*>(&query);
	if (ti == 0) throw Tools::IllegalArgumentException("rangeQuery: Shape does not support the Tools::IInterval interface.");

#ifdef PTHREADS
	Tools::SharedLock lock(&m_rwLock);
#else
	if (m_rwLock == false) m_rwLock = true;
	else throw Tools::ResourceLockedException("rangeQuery: cannot acquire a shared lock");
#endif

	try
	{
		std::set<id_type> visitedNodes;
		std::set<id_type> visitedData;
		std::stack<NodePtr> st;
		std::vector<id_type> ids;
		findRootIdentifiers(*ti, ids);

		for (size_t cRoot = 0; cRoot < ids.size(); cRoot++)
		{
			NodePtr root = readNode(ids[cRoot]);
			if (root->m_children > 0 && query.intersectsShape(root->m_nodeMBR)) st.push(root);
		}

		while (! st.empty())
		{
			NodePtr n = st.top(); st.pop();
			visitedNodes.insert(n->m_identifier);

			if (n->m_level == 0)
			{
				v.visitNode(*n);

				for (size_t cChild = 0; cChild < n->m_children; cChild++)
				{
					if (visitedData.find(n->m_pIdentifier[cChild]) != visitedData.end()) continue;

					bool b;
					if (type == ContainmentQuery) b = (n->m_ptrMBR[cChild])->intersectsInterval(*ti) && query.containsShape(*(n->m_ptrMBR[cChild]));
					else b = (n->m_ptrMBR[cChild])->intersectsInterval(*ti) && query.intersectsShape(*(n->m_ptrMBR[cChild]));

					if (b)
					{
						visitedData.insert(n->m_pIdentifier[cChild]);
						Data data = Data(n->m_pDataLength[cChild], n->m_pData[cChild], *(n->m_ptrMBR[cChild]), n->m_pIdentifier[cChild]);
						v.visitData(data);
						m_stats.m_queryResults++;
					}
				}
			}
			else
			{
				v.visitNode(*n);

				for (size_t cChild = 0; cChild < n->m_children; cChild++)
				{
					if (	
						visitedNodes.find(n->m_pIdentifier[cChild]) == visitedNodes.end() &&
						n->m_ptrMBR[cChild]->intersectsInterval(*ti) &&
						query.intersectsShape(*(n->m_ptrMBR[cChild])))
						st.push(readNode(n->m_pIdentifier[cChild]));
				}
			}
		}

#ifndef PTHREADS
		m_rwLock = false;
#endif
	}
	catch (...)
	{
#ifndef PTHREADS
		m_rwLock = false;
#endif
		throw;
	}
}

void SpatialIndex::MVRTree::MVRTree::findRootIdentifiers(const Tools::IInterval& ti, std::vector<id_type>& ids)
{
	ids.clear();

	for (size_t cRoot = 0; cRoot < m_roots.size(); cRoot++)
	{
		RootEntry& e = m_roots[cRoot];
		if (ti.intersectsInterval(Tools::IT_RIGHTOPEN, e.m_startTime, e.m_endTime)) ids.push_back(e.m_id);
	}
}

std::string SpatialIndex::MVRTree::MVRTree::printRootInfo() const
{
	std::ostringstream s;

	for (size_t cRoot = 0; cRoot < m_roots.size(); cRoot++)
	{
		const RootEntry& e = m_roots[cRoot];

		s << "Root " << cRoot << ":  Start " << e.m_startTime << ", End " << e.m_endTime << std::endl;
	}

	return s.str();
}

std::ostream& SpatialIndex::MVRTree::operator<<(std::ostream& os, const MVRTree& t)
{
	os 	<< "Dimension: " << t.m_dimension << std::endl
		<< "Fill factor: " << t.m_fillFactor << std::endl
		<< "Index capacity: " << t.m_indexCapacity << std::endl
		<< "Leaf capacity: " << t.m_leafCapacity << std::endl
		<< "Tight MBRs: " << ((t.m_bTightMBRs) ? "enabled" : "disabled") << std::endl;

	if (t.m_treeVariant == RV_RSTAR)
	{
		os 	<< "Near minimum overlap factor: " << t.m_nearMinimumOverlapFactor << std::endl
			<< "Reinsert factor: " << t.m_reinsertFactor << std::endl
			<< "Split distribution factor: " << t.m_splitDistributionFactor << std::endl
			<< "Strong version overflow: " << t.m_strongVersionOverflow << std::endl
			//<< "Strong version underflow: " << t.m_strongVersionUnderflow << std::endl
			<< "Weak version underflow: " << t.m_versionUnderflow << std::endl;
	}

	// it is difficult to count utilization
	//os << "Utilization: " << 100 * t.m_stats.m_totalData / (t.m_stats.getNumberOfNodesInLevel(0) * t.m_leafCapacity) << "%" << std::endl

	os << t.m_stats;
	os << t.printRootInfo();

	#ifndef NDEBUG
	os 	<< "Leaf pool hits: " << t.m_leafPool.m_hits << std::endl
		<< "Leaf pool misses: " << t.m_leafPool.m_misses << std::endl
		<< "Index pool hits: " << t.m_indexPool.m_hits << std::endl
		<< "Index pool misses: " << t.m_indexPool.m_misses << std::endl
		<< "Region pool hits: " << t.m_regionPool.m_hits << std::endl
		<< "Region pool misses: " << t.m_regionPool.m_misses << std::endl
		<< "Point pool hits: " << t.m_pointPool.m_hits << std::endl
		<< "Point pool misses: " << t.m_pointPool.m_misses << std::endl;
	#endif

	return os;
}
