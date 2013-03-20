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

#include "MVRNode.h"

namespace Tools
{
	template<> class PointerPool<SpatialIndex::MVRTree::Node>
	{
	public:
		explicit PointerPool(size_t capacity) : m_capacity(capacity)
		{
			#ifndef NDEBUG
			m_hits = 0;
			m_misses = 0;
			m_pointerCount = 0;
			#endif
		}

		~PointerPool()
		{
			assert(m_pool.size() <= m_capacity);

			while (! m_pool.empty())
			{
				SpatialIndex::MVRTree::Node* x = m_pool.top(); m_pool.pop();
				#ifndef NDEBUG
				m_pointerCount--;
				#endif
				delete x;
			}

			#ifndef NDEBUG
			std::cerr << "Lost pointers: " << m_pointerCount << std::endl;
			#endif
		}

		PoolPointer<SpatialIndex::MVRTree::Node> acquire()
		{
			if (! m_pool.empty())
			{
				SpatialIndex::MVRTree::Node* p = m_pool.top(); m_pool.pop();
				#ifndef NDEBUG
				m_hits++;
				#endif

				return PoolPointer<SpatialIndex::MVRTree::Node>(p, this);
			}
			#ifndef NDEBUG
			else
			{
				// fixme: well sort of...
				m_pointerCount++;
				m_misses++;
			}
			#endif

			return PoolPointer<SpatialIndex::MVRTree::Node>();
		}

		void release(SpatialIndex::MVRTree::Node* p)
		{
			if (p != 0)
			{
				if (m_pool.size() < m_capacity)
				{
					if (p->m_pData != 0)
					{
						for (size_t cChild = 0; cChild < p->m_children; cChild++)
						{
							if (p->m_pData[cChild] != 0) delete[] p->m_pData[cChild];
						}
					}

					p->m_level = 0;
					p->m_identifier = -1;
					p->m_children = 0;
					p->m_totalDataLength = 0;

					m_pool.push(p);
				}
				else
				{
					#ifndef NDEBUG
					m_pointerCount--;
					#endif
					delete p;
				}

				assert(m_pool.size() <= m_capacity);
			}
		}

		size_t getCapacity() const { return m_capacity; }
		void setCapacity(size_t c)
		{
			assert (c >= 0);
			m_capacity = c;
		}

	protected:
		size_t m_capacity;
		std::stack<SpatialIndex::MVRTree::Node*> m_pool;

	#ifndef NDEBUG
	public:
		size_t m_hits;
		size_t m_misses;
		size_t m_pointerCount;
	#endif
	};
}

