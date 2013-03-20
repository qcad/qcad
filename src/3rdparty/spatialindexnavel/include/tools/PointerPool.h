// Spatial Index Library
//
// Copyright (C) 2004  Navel Ltd.
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

#include "PoolPointer.h"

namespace Tools
{
	template <class X> class PointerPool
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
				X* x = m_pool.top(); m_pool.pop();
				#ifndef NDEBUG
				m_pointerCount--;
				#endif
				delete x;
			}

			#ifndef NDEBUG
			std::cerr << "Lost pointers: " << m_pointerCount << std::endl;
			#endif
		}

		PoolPointer<X> acquire()
		{
			X* p = 0;

			if (! m_pool.empty())
			{
				p = m_pool.top(); m_pool.pop();
				#ifndef NDEBUG
				m_hits++;
				#endif
			}
			else
			{
				p = new X();
				#ifndef NDEBUG
				m_pointerCount++;
				m_misses++;
				#endif
			}

			return PoolPointer<X>(p, this);
		}

		void release(X* p)
		{
			if (m_pool.size() < m_capacity)
			{
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

		size_t getCapacity() const { return m_capacity; }
		void setCapacity(size_t c)
		{
			assert (c >= 0);
			m_capacity = c;
		}

	private:
		size_t m_capacity;
		std::stack<X*> m_pool;

	#ifndef NDEBUG
	public:
		size_t m_hits;
		size_t m_misses;
		size_t m_pointerCount;
	#endif
	};
}

