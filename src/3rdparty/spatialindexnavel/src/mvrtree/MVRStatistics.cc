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
#include "MVRStatistics.h"

using namespace SpatialIndex::MVRTree;

Statistics::Statistics()
{
	reset();
}

Statistics::Statistics(const Statistics& s)
{
	m_reads  = s.m_reads;
	m_writes = s.m_writes;
	m_splits = s.m_splits;
	m_hits   = s.m_hits;
	m_misses = s.m_misses;
	m_nodes  = s.m_nodes;
	m_deadIndexNodes = s.m_deadIndexNodes;
	m_deadLeafNodes = s.m_deadLeafNodes;
	m_adjustments = s.m_adjustments;
	m_queryResults = s.m_queryResults;
	m_data = s.m_data;
	m_totalData = s.m_totalData;
	m_treeHeight = s.m_treeHeight;
	m_nodesInLevel = s.m_nodesInLevel;
}

Statistics::~Statistics()
{
}

Statistics& Statistics::operator=(const Statistics& s)
{
	if (this != &s)
	{
		m_reads  = s.m_reads;
		m_writes = s.m_writes;
		m_splits = s.m_splits;
		m_hits   = s.m_hits;
		m_misses = s.m_misses;
		m_nodes  = s.m_nodes;
		m_deadIndexNodes = s.m_deadIndexNodes;
		m_deadLeafNodes = s.m_deadLeafNodes;
		m_adjustments = s.m_adjustments;
		m_queryResults = s.m_queryResults;
		m_data = s.m_data;
		m_totalData = s.m_totalData;
		m_treeHeight = s.m_treeHeight;
		m_nodesInLevel = s.m_nodesInLevel;
	}

	return *this;
}

size_t Statistics::getReads() const
{
	return m_reads;
}

size_t Statistics::getWrites() const
{
	return m_writes;
}

size_t Statistics::getNumberOfNodes() const
{
	return m_nodes;
}

size_t Statistics::getNumberOfData() const
{
	return m_data;
}

size_t Statistics::getSplits() const
{
	return m_splits;
}

size_t Statistics::getHits() const
{
	return m_hits;
}

size_t Statistics::getMisses() const
{
	return m_misses;
}

size_t Statistics::getAdjustments() const
{
	return m_adjustments;
}

size_t Statistics::getQueryResults() const
{
	return m_queryResults;
}

size_t Statistics::getTreeHeight() const
{
	size_t ret = 0;

	for (size_t cIndex = 0; cIndex < m_treeHeight.size(); cIndex++)
	{
		ret = std::max(ret, m_treeHeight[cIndex]);
	}

	return ret;
}

size_t Statistics::getNumberOfNodesInLevel(size_t l) const
{
	try
	{
		return m_nodesInLevel.at(l);
	}
	catch (...)
	{
		throw Tools::IndexOutOfBoundsException(l);
	}
}

void Statistics::reset()
{
	m_reads = 0;
	m_writes = 0;
	m_splits = 0;
	m_hits = 0;
	m_misses = 0;
	m_nodes = 0;
	m_deadIndexNodes = 0;
	m_deadLeafNodes = 0;
	m_adjustments = 0;
	m_queryResults = 0;
	m_data = 0;
	m_totalData = 0;
	m_treeHeight.clear();
	m_nodesInLevel.clear();
}

std::ostream& SpatialIndex::MVRTree::operator<<(std::ostream& os, const Statistics& s)
{
	os	<< "Reads: " << s.m_reads << std::endl
		<< "Writes: " << s.m_writes << std::endl
		<< "Hits: " << s.m_hits << std::endl
		<< "Misses: " << s.m_misses << std::endl
		<< "Number of live data: " << s.m_data << std::endl
		<< "Total number of data: " << s.m_totalData << std::endl
		<< "Number of nodes: " << s.m_nodes << std::endl
		<< "Numer of dead index nodes: " << s.m_deadIndexNodes << std::endl
		<< "Numer of dead leaf nodes: " << s.m_deadLeafNodes << std::endl;

	for (size_t cTree = 0; cTree < s.m_treeHeight.size(); cTree++)
	{
		os << "Tree " << cTree << ", Height " << s.m_treeHeight[cTree] << std::endl;
	}

	for (size_t cLevel = 0; cLevel < s.m_nodesInLevel.size(); cLevel++)
	{
		os << "Level " << cLevel << " pages: " << s.m_nodesInLevel[cLevel] << std::endl;
	}

	os	<< "Splits: " << s.m_splits << std::endl
		<< "Adjustments: " << s.m_adjustments << std::endl
		<< "Query results: " << s.m_queryResults << std::endl;

	return os;
}
