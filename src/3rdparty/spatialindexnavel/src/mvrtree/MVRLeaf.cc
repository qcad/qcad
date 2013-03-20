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
#include "MVRTree.h"
#include "MVRNode.h"
#include "MVRIndex.h"
#include "MVRLeaf.h"

using namespace SpatialIndex::MVRTree;

Leaf::~Leaf()
{
}

Leaf::Leaf(SpatialIndex::MVRTree::MVRTree* pTree, id_type id): Node(pTree, id, 0, pTree->m_leafCapacity)
{
}

NodePtr Leaf::chooseSubtree(const TimeRegion& mbr, size_t level, std::stack<id_type>& pathBuffer)
{
	// should make sure to relinquish other PoolPointer lists that might be pointing to the
	// same leaf.
	return NodePtr(this, &(m_pTree->m_leafPool));
}

NodePtr Leaf::findLeaf(const TimeRegion& mbr, id_type id, std::stack<id_type>& pathBuffer)
{
	for (size_t cChild = 0; cChild < m_children; cChild++)
	{
		// should make sure to relinquish other PoolPointer lists that might be pointing to the
		// same leaf.
		if (m_pIdentifier[cChild] == id && static_cast<Region>(mbr) == static_cast<Region>(*(m_ptrMBR[cChild])))
			return NodePtr(this, &(m_pTree->m_leafPool));
	}

	return NodePtr();
}

void Leaf::split(
	size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, NodePtr& pLeft, NodePtr& pRight,
	TimeRegion& mbr2, id_type id2, bool bInsertMbr2)
{
	m_pTree->m_stats.m_splits++;

	std::vector<size_t> g1, g2;

	switch (m_pTree->m_treeVariant)
	{
		case RV_LINEAR:
		case RV_QUADRATIC:
			rtreeSplit(dataLength, pData, mbr, id, g1, g2, mbr2, id2, bInsertMbr2);
			break;
		case RV_RSTAR:
			rstarSplit(dataLength, pData, mbr, id, g1, g2, mbr2, id2, bInsertMbr2);
			break;
		default:
			throw Tools::NotSupportedException("Leaf::split: Tree variant not supported.");
	}

	pLeft = m_pTree->m_leafPool.acquire();
	pRight = m_pTree->m_leafPool.acquire();

	if (pLeft.get() == 0) pLeft = NodePtr(new Leaf(m_pTree, -1), &(m_pTree->m_leafPool));
	if (pRight.get() == 0) pRight = NodePtr(new Leaf(m_pTree, -1), &(m_pTree->m_leafPool));

	pLeft->m_nodeMBR = m_pTree->m_infiniteRegion;
	pRight->m_nodeMBR = m_pTree->m_infiniteRegion;

	size_t cIndex;

	for (cIndex = 0; cIndex < g1.size(); cIndex++)
	{
		pLeft->insertEntry(m_pDataLength[g1[cIndex]], m_pData[g1[cIndex]], *(m_ptrMBR[g1[cIndex]]), m_pIdentifier[g1[cIndex]]);
		// we don't want to delete the data array from this node's destructor!
		m_pData[g1[cIndex]] = 0;
	}

	for (cIndex = 0; cIndex < g2.size(); cIndex++)
	{
		pRight->insertEntry(m_pDataLength[g2[cIndex]], m_pData[g2[cIndex]], *(m_ptrMBR[g2[cIndex]]), m_pIdentifier[g2[cIndex]]);
		// we don't want to delete the data array from this node's destructor!
		m_pData[g2[cIndex]] = 0;
	}
}
