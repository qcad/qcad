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

#include "tools/Tools.h"

namespace SpatialIndex
{
	class SIDX_DLL Point : public Tools::IObject, public virtual IShape
	{
	public:
		Point();
		Point(const double* pCoords, uint32_t dimension);
		Point(const Point& p);
		virtual ~Point();

		virtual Point& operator=(const Point& p);
		virtual bool operator==(const Point& p) const;

		//
		// IObject interface
		//
		virtual Point* clone();

		//
		// ISerializable interface
		//
		virtual uint32_t getByteArraySize();
		virtual void loadFromByteArray(const byte* data);
		virtual void storeToByteArray(byte** data, uint32_t& length);

		//
		// IShape interface
		//
		virtual bool intersectsShape(const IShape& in) const;
		virtual bool containsShape(const IShape& in) const;
		virtual bool touchesShape(const IShape& in) const;
		virtual void getCenter(Point& out) const;
		virtual uint32_t getDimension() const;
		virtual void getMBR(Region& out) const;
		virtual double getArea() const;
		virtual double getMinimumDistance(const IShape& in) const;

		virtual double getMinimumDistance(const Point& p) const;

		virtual double getCoordinate(uint32_t index) const;

		virtual void makeInfinite(uint32_t dimension);
		virtual void makeDimension(uint32_t dimension);

	public:
		uint32_t m_dimension;
		double* m_pCoords;

		friend class Region;
		friend SIDX_DLL std::ostream& operator<<(std::ostream& os, const Point& pt);
	}; // Point
	
	typedef Tools::PoolPointer<Point> PointPtr;

	SIDX_DLL std::ostream& operator<<(std::ostream& os, const Point& pt);
}
