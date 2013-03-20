// Spatial Index Library
//
// Copyright (C) 2003 Navel Ltd.
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
	class SIDX_DLL TimePoint : public Point, public ITimeShape
	{
	public:
		TimePoint();
		TimePoint(const double* pCoords, const Tools::IInterval& ti, size_t dimension);
		TimePoint(const double* pCoords, double tStart, double tEnd, size_t dimension);
		TimePoint(const Point& p, const Tools::IInterval& ti);
		TimePoint(const Point& p, double tStart, double tEnd);
		TimePoint(const TimePoint& p);
		virtual ~TimePoint();

		virtual TimePoint& operator=(const TimePoint& p);
		virtual bool operator==(const TimePoint& p) const;

		//
		// IObject interface
		//
		virtual TimePoint* clone();

		//
		// ISerializable interface
		//
		virtual size_t getByteArraySize();
		virtual void loadFromByteArray(const byte* data);
		virtual void storeToByteArray(byte** data, size_t& len);

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

		virtual void makeInfinite(size_t dimension);
		virtual void makeDimension(size_t dimension);

	public:
		double m_startTime;
		double m_endTime;

		friend SIDX_DLL std::ostream& operator<<(std::ostream& os, const TimePoint& pt);
	}; // TimePoint

	SIDX_DLL std::ostream& operator<<(std::ostream& os, const TimePoint& pt);
}
