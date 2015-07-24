/******************************************************************************
 * Project:  libspatialindex - A C++ library for spatial indexing
 * Author:   Marios Hadjieleftheriou, mhadji@gmail.com
 ******************************************************************************
 * Copyright (c) 2003, Marios Hadjieleftheriou
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

namespace SpatialIndex
{
	class SIDX_DLL TimeRegion : public Region, public ITimeShape
	{
	public:
		TimeRegion();
		TimeRegion(const double* pLow, const double* pHigh, const Tools::IInterval& ti, uint32_t dimension);
		TimeRegion(const double* pLow, const double* pHigh, double tStart, double tEnd, uint32_t dimension);
		TimeRegion(const Point& low, const Point& high, const Tools::IInterval& ti);
		TimeRegion(const Point& low, const Point& high, double tStart, double tEnd);
		TimeRegion(const Region& in, const Tools::IInterval& ti);
		TimeRegion(const Region& in, double tStart, double tEnd);
		TimeRegion(const TimePoint& low, const TimePoint& high);
		TimeRegion(const TimeRegion& in);
		virtual ~TimeRegion();

		virtual TimeRegion& operator=(const TimeRegion& r);
		virtual bool operator==(const TimeRegion&) const;

		virtual bool intersectsRegionInTime(const TimeRegion& in) const;
		virtual bool containsRegionInTime(const TimeRegion& in) const;
		virtual bool touchesRegionInTime(const TimeRegion& in) const;

		virtual bool containsPointInTime(const TimePoint& in) const;
		virtual bool touchesPointInTime(const TimePoint& in) const;

		virtual void combineRegionInTime(const TimeRegion& in);
		virtual void getCombinedRegionInTime(TimeRegion& out, const TimeRegion& in) const;

		//
		// IObject interface
		//
		virtual TimeRegion* clone();

		//
		// ISerializable interface
		//
		virtual uint32_t getByteArraySize();
		virtual void loadFromByteArray(const byte* data);
		virtual void storeToByteArray(byte** data, uint32_t& len);

		//
		// ITimeShape interface
		//
		virtual bool intersectsShapeInTime(const ITimeShape& in) const;
		virtual bool intersectsShapeInTime(const Tools::IInterval& ivI, const ITimeShape& in) const;
		virtual bool containsShapeInTime(const ITimeShape& in) const;
		virtual bool containsShapeInTime(const Tools::IInterval& ivI, const ITimeShape& in) const;
		virtual bool touchesShapeInTime(const ITimeShape& in) const;
		virtual bool touchesShapeInTime(const Tools::IInterval& ivI, const ITimeShape& in) const;
		virtual double getAreaInTime() const;
		virtual double getAreaInTime(const Tools::IInterval& ivI) const;
		virtual double getIntersectingAreaInTime(const ITimeShape& r) const;
		virtual double getIntersectingAreaInTime(const Tools::IInterval& ivI, const ITimeShape& r) const;

		//
		// IInterval interface
		//
		virtual Tools::IInterval& operator=(const Tools::IInterval&);
		virtual double getLowerBound() const;
		virtual double getUpperBound() const;
		virtual void setBounds(double, double);
		virtual bool intersectsInterval(const Tools::IInterval& ti) const;
		virtual bool intersectsInterval(Tools::IntervalType t, const double start, const double end) const;
		virtual bool containsInterval(const Tools::IInterval& ti) const;
		virtual Tools::IntervalType getIntervalType() const;

		virtual void makeInfinite(uint32_t dimension);
		virtual void makeDimension(uint32_t dimension);

	public:
		double m_startTime;
		double m_endTime;

		friend SIDX_DLL std::ostream& operator<<(std::ostream& os, const TimeRegion& r);
	}; // TimeRegion

	typedef Tools::PoolPointer<TimeRegion> TimeRegionPtr;
	SIDX_DLL std::ostream& operator<<(std::ostream& os, const TimeRegion& r);
}
