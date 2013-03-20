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
	namespace MVRTree
	{
		class MVRTree;
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
			virtual IObject* clone();

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
			Node(MVRTree* pTree, id_type id, size_t level, size_t capacity);

			virtual Node& operator=(const Node&);

			virtual void insertEntry(size_t dataLength, byte* pData, TimeRegion& mbr, id_type id);
			virtual bool deleteEntry(size_t index);

			virtual bool insertData(
				size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, std::stack<id_type>& pathBuffer,
				TimeRegion& mbr2, id_type id2, bool bInsertMbr2 = false, bool forceAdjust = false);
			virtual void insertData(TimeRegion& mbr1, id_type id1, TimeRegion& mbr2, id_type id2, Node* oldVersion, std::stack<id_type>& pathBuffer);
			virtual bool deleteData(id_type id, double delTime, std::stack<id_type>& pathBuffer, bool adjustMBR = false);

			virtual void rtreeSplit(
				size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, std::vector<size_t>& group1, std::vector<size_t>& group2,
				TimeRegion& mbr2, id_type id2, bool bInsertMbr2 = false);
			virtual void rstarSplit(
				size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, std::vector<size_t>& group1, std::vector<size_t>& group2,
				TimeRegion& mbr2, id_type id2, bool bInsertMbr2 = false);

			virtual void pickSeeds(size_t& index1, size_t& index2, size_t total);

			virtual NodePtr chooseSubtree(const TimeRegion& mbr, size_t level, std::stack<id_type>& pathBuffer) = 0;
			virtual NodePtr findLeaf(const TimeRegion& mbr, id_type id, std::stack<id_type>& pathBuffer) = 0;
			virtual NodePtr findNode(const TimeRegion& mbr, id_type id, std::stack<id_type>& pathBuffer);

			virtual void split(
				size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, NodePtr& left, NodePtr& right,
				TimeRegion& mbr2, id_type id2, bool bInsertMbr2 = false) = 0;

			MVRTree* m_pTree;
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

			TimeRegion m_nodeMBR;
				// The minimum bounding region enclosing all data contained in the node.

			byte** m_pData;
				// The data stored in the node.

			TimeRegionPtr* m_ptrMBR;
				// The corresponding data MBRs.

			id_type* m_pIdentifier;
				// The corresponding data identifiers.

			size_t* m_pDataLength;

			size_t m_totalDataLength;

			class RstarSplitEntry
			{
			public:
				RstarSplitEntry(TimeRegion* pr, size_t index, size_t dimension) :
					m_pRegion(pr), m_index(index), m_sortDim(dimension) {}

				static int compareLow(const void* pv1, const void* pv2)
				{
					RstarSplitEntry* pe1 = * (RstarSplitEntry**) pv1;
					RstarSplitEntry* pe2 = * (RstarSplitEntry**) pv2;

					if (pe1->m_pRegion->m_pLow[pe1->m_sortDim] < pe2->m_pRegion->m_pLow[pe2->m_sortDim]) return -1;
					if (pe1->m_pRegion->m_pLow[pe1->m_sortDim] > pe2->m_pRegion->m_pLow[pe2->m_sortDim]) return 1;
					return 0;
				}

				static int compareHigh(const void* pv1, const void* pv2)
				{
					RstarSplitEntry* pe1 = * (RstarSplitEntry**) pv1;
					RstarSplitEntry* pe2 = * (RstarSplitEntry**) pv2;

					if (pe1->m_pRegion->m_pHigh[pe1->m_sortDim] < pe2->m_pRegion->m_pHigh[pe2->m_sortDim]) return -1;
					if (pe1->m_pRegion->m_pHigh[pe1->m_sortDim] > pe2->m_pRegion->m_pHigh[pe2->m_sortDim]) return 1;
					return 0;
				}

				TimeRegion* m_pRegion;
				size_t m_index;
				size_t m_sortDim;
			}; // RstarSplitEntry

			class DeleteDataEntry
			{
			public:
				DeleteDataEntry(size_t index, double d) : m_index(index), m_increase(d) {}

				static bool compare(DeleteDataEntry e1, DeleteDataEntry e2) { return e1.m_increase < e2.m_increase; }

				size_t m_index;
				double m_increase;
			}; // DeleteDataEntry

			// Needed to access protected members without having to cast from Node.
			// It is more efficient than using member functions to access protected members.
			friend class MVRTree;
			friend class Leaf;
			friend class Index;
			friend class Tools::PointerPool<Node>;
		}; // Node
	}
}

