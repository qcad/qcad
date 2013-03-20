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
		class Leaf : public Node
		{
		public:
			virtual ~Leaf();

		private:
			Leaf(MVRTree* pTree, id_type id);

			virtual NodePtr chooseSubtree(const TimeRegion& mbr, size_t level, std::stack<id_type>& pathBuffer);
			virtual NodePtr findLeaf(const TimeRegion& mbr, id_type id, std::stack<id_type>& pathBuffer);

			virtual void split(
				size_t dataLength, byte* pData, TimeRegion& mbr, id_type id, NodePtr& left, NodePtr& right,
				TimeRegion& mbr2, id_type id2, bool bInsertMbr2 = false);

			friend class MVRTree;
			friend class Node;
		}; // Leaf
	}
}

