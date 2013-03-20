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

#pragma once

namespace SpatialIndex
{
	namespace TPRTree
	{
		class TPRTree;
		class Leaf;
		class Index;
		class Node;

		typedef Tools::PoolPointer<Node> NodePtr;

		class Node : public SpatialIndex::INode
		{
		public:
			virtual ~Node();

			//
			// Tools::IObject interface
			//
			virtual Tools::IObject* clone();

			//
			// Tools::ISerializable interface
			//
			virtual size_t getByteArraySize();
			virtual void loadFromByteArray(const byte* data);
			virtual void storeToByteArray(byte** data, size_t& len);

			//
			// SpatialIndex::IEntry interface
			//
			virtual id_type getIdentifier() const;
			virtual void getShape(IShape** out) const;

			//
			// SpatialIndex::INode interface
			//
			virtual size_t getChildrenCount() const;
			virtual id_type getChildIdentifier(size_t index)  const;
			virtual void getChildShape(size_t index, IShape** out)  const;

                        virtual void getChildData(size_t index, size_t& length, byte** data) const;
			virtual size_t getLevel() const;
			virtual bool isIndex() const;
			virtual bool isLeaf() const;

		private:
			Node();
			Node(TPRTree* pTree, id_type id, size_t level, size_t capacity);

			virtual Node& operator=(const Node&);

			virtual bool insertEntry(size_t dataLength, byte* pData, MovingRegion& mbr, id_type id);
			virtual void deleteEntry(size_t index);

			virtual bool insertData(size_t dataLength, byte* pData, MovingRegion& mbr, id_type id, std::stack<id_type>& pathBuffer, byte* overflowTable);
			virtual void reinsertData(size_t dataLength, byte* pData, MovingRegion& mbr, id_type id, std::vector<size_t>& reinsert, std::vector<size_t>& keep);

			virtual void rstarSplit(size_t dataLength, byte* pData, MovingRegion& mbr, id_type id, std::vector<size_t>& group1, std::vector<size_t>& group2);

			//virtual void pickSeeds(size_t& index1, size_t& index2);

			virtual void condenseTree(std::stack<NodePtr>& toReinsert, std::stack<id_type>& pathBuffer, NodePtr& ptrThis);

			virtual NodePtr chooseSubtree(const MovingRegion& mbr, size_t level, std::stack<id_type>& pathBuffer) = 0;
			virtual NodePtr findLeaf(const MovingRegion& mbr, id_type id, std::stack<id_type>& pathBuffer) = 0;

			virtual void split(size_t dataLength, byte* pData, MovingRegion& mbr, id_type id, NodePtr& left, NodePtr& right) = 0;

			TPRTree* m_pTree;
				// Parent of all nodes.

			size_t m_level;
				// The level of the node in the tree.
				// Leaves are always at level 0.

			id_type m_identifier;
				// The unique ID of this node.

			size_t m_children;
				// The number of children pointed by this node.

			size_t m_capacity;
				// Specifies the node capacity.

			MovingRegion m_nodeMBR;
				// The minimum bounding region enclosing all data contained in the node.

			byte** m_pData;
				// The data stored in the node.

			MovingRegionPtr* m_ptrMBR;
				// The corresponding data MBRs.

			id_type* m_pIdentifier;
				// The corresponding data identifiers.

			size_t* m_pDataLength;

			size_t m_totalDataLength;

			class RstarSplitEntry
			{
			public:
				MovingRegion* m_pRegion;
				size_t m_index;
				size_t m_sortDim;

				RstarSplitEntry(MovingRegion* pr, size_t index, size_t dimension)
					: m_pRegion(pr), m_index(index), m_sortDim(dimension) {}

				static int compareLow(const void* pv1, const void* pv2)
				{
					RstarSplitEntry* pe1 = * (RstarSplitEntry**) pv1;
					RstarSplitEntry* pe2 = * (RstarSplitEntry**) pv2;

					if (pe1->m_pRegion->m_pLow[pe1->m_sortDim] < pe2->m_pRegion->m_pLow[pe1->m_sortDim]) return -1;
					if (pe1->m_pRegion->m_pLow[pe1->m_sortDim] > pe2->m_pRegion->m_pLow[pe1->m_sortDim]) return 1;
					return 0;
				}

				static int compareHigh(const void* pv1, const void* pv2)
				{
					RstarSplitEntry* pe1 = * (RstarSplitEntry**) pv1;
					RstarSplitEntry* pe2 = * (RstarSplitEntry**) pv2;

					if (pe1->m_pRegion->m_pHigh[pe1->m_sortDim] < pe2->m_pRegion->m_pHigh[pe1->m_sortDim]) return -1;
					if (pe1->m_pRegion->m_pHigh[pe1->m_sortDim] > pe2->m_pRegion->m_pHigh[pe1->m_sortDim]) return 1;
					return 0;
				}

				static int compareVLow(const void* pv1, const void* pv2)
				{
					RstarSplitEntry* pe1 = * (RstarSplitEntry**) pv1;
					RstarSplitEntry* pe2 = * (RstarSplitEntry**) pv2;

					if (pe1->m_pRegion->m_pVLow[pe1->m_sortDim] < pe2->m_pRegion->m_pVLow[pe1->m_sortDim]) return -1;
					if (pe1->m_pRegion->m_pVLow[pe1->m_sortDim] > pe2->m_pRegion->m_pVLow[pe1->m_sortDim]) return 1;
					return 0;
				}

				static int compareVHigh(const void* pv1, const void* pv2)
				{
					RstarSplitEntry* pe1 = * (RstarSplitEntry**) pv1;
					RstarSplitEntry* pe2 = * (RstarSplitEntry**) pv2;

					if (pe1->m_pRegion->m_pVHigh[pe1->m_sortDim] < pe2->m_pRegion->m_pVHigh[pe1->m_sortDim]) return -1;
					if (pe1->m_pRegion->m_pVHigh[pe1->m_sortDim] > pe2->m_pRegion->m_pVHigh[pe1->m_sortDim]) return 1;
					return 0;
				}
			}; // RstarSplitEntry

			class ReinsertEntry
			{
			public:
				size_t m_index;
				double m_dist;

				ReinsertEntry(size_t index, double dist) : m_index(index), m_dist(dist) {}

				static int compareReinsertEntry(const void* pv1, const void* pv2)
				{
					ReinsertEntry* pe1 = * (ReinsertEntry**) pv1;
					ReinsertEntry* pe2 = * (ReinsertEntry**) pv2;

					if (pe1->m_dist < pe2->m_dist) return -1;
					if (pe1->m_dist > pe2->m_dist) return 1;
					return 0;
				}
			}; // ReinsertEntry

			// Needed to access protected members without having to cast from Node.
			// It is more efficient than using member functions to access protected members.
			friend class TPRTree;
			friend class Leaf;
			friend class Index;
			friend class Tools::PointerPool<Node>;
		}; // Node
	}
}
