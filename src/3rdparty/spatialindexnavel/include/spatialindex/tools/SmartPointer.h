/******************************************************************************
 * Project:  libspatialindex - A C++ library for spatial indexing
 * Author:   Marios Hadjieleftheriou, mhadji@gmail.com
 ******************************************************************************
 * Copyright (c) 2004, Marios Hadjieleftheriou
 *
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

namespace Tools
{
	template <class X> class SmartPointer
	{
	public:
		explicit SmartPointer(X* p = 0) throw() : m_pointer(p) { m_prev = m_next = this; }
		~SmartPointer()	{ release(); }
		SmartPointer(const SmartPointer& p) throw() { acquire(p); }
		SmartPointer& operator=(const SmartPointer& p)
		{
			if (this != &p)
			{
				release();
				acquire(p);
			}
			return *this;
		}

		X& operator*() const throw() { return *m_pointer; }
		X* operator->() const throw() { return m_pointer; }
		X* get() const throw() { return m_pointer; }
		bool unique() const throw() { return m_prev ? m_prev == this : true; }

	private:
		X* m_pointer;
		mutable const SmartPointer* m_prev;
		mutable const SmartPointer* m_next;

		void acquire(const SmartPointer& p) throw()
		{
			m_pointer = p.m_pointer;
			m_next = p.m_next;
			m_next->m_prev = this;
			m_prev = &p;
			#ifndef mutable
			p.m_next = this;
			#else
			(const_cast<linked_ptr<X>*>(&p))->m_next = this;
			#endif
		}

		void release()
		{
			if (unique()) delete m_pointer;
			else
			{
				m_prev->m_next = m_next;
				m_next->m_prev = m_prev;
				m_prev = m_next = 0;
			}
			m_pointer = 0;
		}
	};
}

