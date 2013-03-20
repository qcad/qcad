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

#include "../../include/SpatialIndex.h"

#undef __USE_BSD
#include <cstring>

using namespace SpatialIndex;

TimeRegion::TimeRegion()
	: Region(), m_startTime(-std::numeric_limits<double>::max()), m_endTime(std::numeric_limits<double>::max())
{
}

TimeRegion::TimeRegion(const double* pLow, const double* pHigh, const IInterval& ti, size_t dimension)
	: Region(pLow, pHigh, dimension), m_startTime(ti.getLowerBound()), m_endTime(ti.getUpperBound())
{
}

TimeRegion::TimeRegion(const double* pLow, const double* pHigh, double tStart, double tEnd, size_t dimension)
	: Region(pLow, pHigh, dimension), m_startTime(tStart), m_endTime(tEnd)
{
}

TimeRegion::TimeRegion(const Point& low, const Point& high, const IInterval& ti)
	: Region(low, high), m_startTime(ti.getLowerBound()), m_endTime(ti.getUpperBound())
{
}

TimeRegion::TimeRegion(const Point& low, const Point& high, double tStart, double tEnd)
	: Region(low, high), m_startTime(tStart), m_endTime(tEnd)
{
}

TimeRegion::TimeRegion(const Region& r, const IInterval& ti)
	: Region(r), m_startTime(ti.getLowerBound()), m_endTime(ti.getUpperBound())
{
}

TimeRegion::TimeRegion(const Region& r, double tStart, double tEnd)
	: Region(r), m_startTime(tStart), m_endTime(tEnd)
{
}

TimeRegion::TimeRegion(const TimePoint& low, const TimePoint& high)
	: Region((Point&) low, (Point&) high), m_startTime(low.m_startTime), m_endTime(high.m_endTime)
{
}

TimeRegion::TimeRegion(const TimeRegion& r)
	: m_startTime(r.m_startTime), m_endTime(r.m_endTime)
{
	m_dimension = r.m_dimension;
	m_pLow = 0;

	try
	{
		m_pLow = new double[m_dimension];
		m_pHigh = new double[m_dimension];
	}
	catch (...)
	{
		delete[] m_pLow;
		throw;
	}

	memcpy(m_pLow, r.m_pLow, m_dimension * sizeof(double));
	memcpy(m_pHigh, r.m_pHigh, m_dimension * sizeof(double));
}

TimeRegion::~TimeRegion()
{
}

TimeRegion& TimeRegion::operator=(const TimeRegion& r)
{
	if(this != &r)
	{
		makeDimension(r.m_dimension);
		memcpy(m_pLow, r.m_pLow, m_dimension * sizeof(double));
		memcpy(m_pHigh, r.m_pHigh, m_dimension * sizeof(double));

		m_startTime = r.m_startTime;
		m_endTime = r.m_endTime;
	}

	return *this;
}

bool TimeRegion::operator==(const TimeRegion& r) const
{
	if (m_startTime < r.m_startTime - std::numeric_limits<double>::epsilon() ||
		m_startTime > r.m_startTime + std::numeric_limits<double>::epsilon() ||
		m_endTime < r.m_endTime - std::numeric_limits<double>::epsilon() ||
		m_endTime > r.m_endTime + std::numeric_limits<double>::epsilon())
		return false;

	for (size_t i = 0; i < m_dimension; i++)
	{
		if (
			m_pLow[i] < r.m_pLow[i] - std::numeric_limits<double>::epsilon() ||
			m_pLow[i] > r.m_pLow[i] + std::numeric_limits<double>::epsilon() ||
			m_pHigh[i] < r.m_pHigh[i] - std::numeric_limits<double>::epsilon() ||
			m_pHigh[i] > r.m_pHigh[i] + std::numeric_limits<double>::epsilon())
			return false;
	}
	return true;
}

bool TimeRegion::intersectsRegionInTime(const TimeRegion& r) const
{
	// they should just intersect in time.
	// check if they intersect in time first.
	// the first check is needed for the following case:
	// m_endTime == m_startTime == r.m_startTime.
	// For open ended intervals this should be considered as an intersection
	// (takes care of degenarate intervals)
	//if (m_startTime != r.m_startTime &&
	//	(m_startTime >= r.m_endTime || m_endTime <= r.m_startTime))
	if (! intersectsInterval(r)) return false;
	return Region::intersectsRegion(r);
}

bool TimeRegion::containsRegionInTime(const TimeRegion& r) const
{
	// it should be contained in time.
	if (! containsInterval(r)) return false;
	return Region::containsRegion(r);
}

bool TimeRegion::touchesRegionInTime(const TimeRegion& r) const
{
	// they should just intersect in time.
	//if (m_startTime != r.m_startTime &&
	//	(m_startTime >= r.m_endTime || m_endTime <= r.m_startTime))
	if (!intersectsInterval(r)) return false;
	return Region::touchesRegion(r);
}

bool TimeRegion::containsPointInTime(const TimePoint& p) const
{
	// it should be contained in time.
	//if (p.m_startTime < m_startTime || p.m_endTime > m_endTime) return false;
	if (containsInterval(p)) return false;
	return Region::containsPoint(p);
}

bool TimeRegion::touchesPointInTime(const TimePoint& p) const
{
	// they should just intersect in time.
	//if (m_startTime != p.m_startTime &&
	//	(m_startTime >= p.m_endTime || m_endTime <= p.m_startTime))
	if (intersectsInterval(p)) return false;
	return Region::touchesPoint(p);
}

void TimeRegion::combineRegionInTime(const TimeRegion& r)
{
	Region::combineRegion(r);

	m_startTime = std::min(m_startTime, r.m_startTime);
	m_endTime = std::max(m_endTime, r.m_endTime);
}

void TimeRegion::getCombinedRegionInTime(TimeRegion& out, const TimeRegion& in) const
{
	Region::getCombinedRegion(out, in);

	out.m_startTime = std::min(m_startTime, in.m_startTime);
	out.m_endTime = std::max(m_endTime, in.m_endTime);
}

//
// IObject interface
//
TimeRegion* TimeRegion::clone()
{
	return new TimeRegion(*this);
}

//
// ISerializable interface
//
size_t TimeRegion::getByteArraySize()
{
	return (sizeof(size_t) + 2 * sizeof(double) + 2 * m_dimension * sizeof(double));
}

void TimeRegion::loadFromByteArray(const byte* ptr)
{
	size_t dimension;

	memcpy(&dimension, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&m_startTime, ptr, sizeof(double));
	ptr += sizeof(double);
	memcpy(&m_endTime, ptr, sizeof(double));
	ptr += sizeof(double);

	makeDimension(dimension);
	memcpy(m_pLow, ptr, m_dimension * sizeof(double));
	ptr += m_dimension * sizeof(double);
	memcpy(m_pHigh, ptr, m_dimension * sizeof(double));
	//ptr += m_dimension * sizeof(double);
}

void TimeRegion::storeToByteArray(byte** data, size_t& len)
{
	len = getByteArraySize();
	*data = new byte[len];
	byte* ptr = *data;

	memcpy(ptr, &m_dimension, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(ptr, &m_startTime, sizeof(double));
	ptr += sizeof(double);
	memcpy(ptr, &m_endTime, sizeof(double));
	ptr += sizeof(double);

	memcpy(ptr, m_pLow, m_dimension * sizeof(double));
	ptr += m_dimension * sizeof(double);
	memcpy(ptr, m_pHigh, m_dimension * sizeof(double));
	//ptr += m_dimension * sizeof(double);
}

//
// ITimeShape interface
//
bool TimeRegion::intersectsShapeInTime(const ITimeShape& in) const
{
	const TimeRegion* pr = dynamic_cast<const TimeRegion*>(&in);
	if (pr != 0) return intersectsRegionInTime(*pr);

	const TimePoint* ppt = dynamic_cast<const TimePoint*>(&in);
	if (ppt != 0) return containsPointInTime(*ppt);

	throw Tools::IllegalStateException("intersectsShapeInTime: Not implemented yet!");
}

bool TimeRegion::intersectsShapeInTime(const IInterval& ivI, const ITimeShape& in) const
{
	throw Tools::IllegalStateException("intersectsShapeInTime: Not implemented yet!");
}

bool TimeRegion::containsShapeInTime(const ITimeShape& in) const
{
	const TimeRegion* pr = dynamic_cast<const TimeRegion*>(&in);
	if (pr != 0) return containsRegionInTime(*pr);

	const TimePoint* ppt = dynamic_cast<const TimePoint*>(&in);
	if (ppt != 0) return containsPointInTime(*ppt);

	throw Tools::IllegalStateException("containsShapeInTime: Not implemented yet!");
}

bool TimeRegion::containsShapeInTime(const IInterval& ivI, const ITimeShape& in) const
{
	throw Tools::IllegalStateException("containsShapeInTime: Not implemented yet!");
}

bool TimeRegion::touchesShapeInTime(const ITimeShape& in) const
{
	const TimeRegion* pr = dynamic_cast<const TimeRegion*>(&in);
	if (pr != 0) return touchesRegionInTime(*pr);

	throw Tools::IllegalStateException("touchesShapeInTime: Not implemented yet!");
}

bool TimeRegion::touchesShapeInTime(const IInterval& ivI, const ITimeShape& in) const
{
	throw Tools::IllegalStateException("touchesShapeInTime: Not implemented yet!");
}

double TimeRegion::getAreaInTime() const
{
	throw Tools::IllegalStateException("getAreaInTime: Not implemented yet!");
}

double TimeRegion::getAreaInTime(const IInterval& ivI) const
{
	throw Tools::IllegalStateException("getAreaInTime: Not implemented yet!");
}

double TimeRegion::getIntersectingAreaInTime(const ITimeShape& r) const
{
	throw Tools::IllegalStateException("getIntersectingAreaInTime: Not implemented yet!");
}

double TimeRegion::getIntersectingAreaInTime(const IInterval& ivI, const ITimeShape& r) const
{
	throw Tools::IllegalStateException("getIntersectingAreaInTime: Not implemented yet!");
}

//
// IInterval interface
//
Tools::IInterval& TimeRegion::operator=(const Tools::IInterval& i)
{
	if (this != &i)
	{
		m_startTime = i.getLowerBound();
		m_endTime = i.getUpperBound();
	}

	return *this;
}

double TimeRegion::getLowerBound() const
{
	return m_startTime;
}

double TimeRegion::getUpperBound() const
{
	return m_endTime;
}

void TimeRegion::setBounds(double l, double h)
{
	assert(m_startTime <= m_endTime);

	m_startTime = l;
	m_endTime = h;
}

bool TimeRegion::intersectsInterval(const IInterval& ti) const
{
	return intersectsInterval(ti.getIntervalType(), ti.getLowerBound(), ti.getUpperBound());
}

bool TimeRegion::intersectsInterval(Tools::IntervalType t, const double start, const double end) const
{
	//if (m_startTime != start &&
	//		(m_startTime >= end || m_endTime <= start)) return false;
	// this will not work for degenarate intervals.
	if (m_startTime >= end || m_endTime <= start) return false;

	return true;
}

bool TimeRegion::containsInterval(const IInterval& ti) const
{
	if (m_startTime <= ti.getLowerBound() && m_endTime >= ti.getUpperBound()) return true;
	return false;
}

Tools::IntervalType TimeRegion::getIntervalType() const
{
	return Tools::IT_RIGHTOPEN;
}

void TimeRegion::makeInfinite(size_t dimension)
{
	makeDimension(dimension);
	for (size_t cIndex = 0; cIndex < m_dimension; cIndex++)
	{
		m_pLow[cIndex] = std::numeric_limits<double>::max();
		m_pHigh[cIndex] = -std::numeric_limits<double>::max();
	}

	m_startTime = std::numeric_limits<double>::max();
	m_endTime = -std::numeric_limits<double>::max();
}

void TimeRegion::makeDimension(size_t dimension)
{
	if (m_dimension != dimension)
	{
		m_dimension = dimension;

		delete[] m_pLow;
		delete[] m_pHigh;
		m_pLow = 0; m_pHigh = 0;

		m_pLow = new double[m_dimension];
		m_pHigh = new double[m_dimension];
	}
}

std::ostream& SpatialIndex::operator<<(std::ostream& os, const TimeRegion& r)
{
	size_t i;

	os << "Low: ";
	for (i = 0; i < r.m_dimension; i++)
	{
		os << r.m_pLow[i] << " ";
	}

	os << ", High: ";

	for (i = 0; i < r.m_dimension; i++)
	{
		os << r.m_pHigh[i] << " ";
	}

	os << ", Start: " << r.m_startTime << ", End: " << r.m_endTime;

	return os;
}
