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

#include <cstring>

#include "../../include/SpatialIndex.h"

using namespace SpatialIndex;

TimePoint::TimePoint()
	: Point(), m_startTime(-std::numeric_limits<double>::max()), m_endTime(std::numeric_limits<double>::max())
{
}

TimePoint::TimePoint(const double* pCoords, const IInterval& ti, size_t dimension)
	: Point(pCoords, dimension), m_startTime(ti.getLowerBound()), m_endTime(ti.getUpperBound())
{
}

TimePoint::TimePoint(const double* pCoords, double tStart, double tEnd, size_t dimension)
	: Point(pCoords, dimension), m_startTime(tStart), m_endTime(tEnd)
{
}

TimePoint::TimePoint(const Point& p, const IInterval& ti)
	: Point(p), m_startTime(ti.getLowerBound()), m_endTime(ti.getUpperBound())
{
}

TimePoint::TimePoint(const Point& p, double tStart, double tEnd)
	: Point(p), m_startTime(tStart), m_endTime(tEnd)
{
}

TimePoint::TimePoint(const TimePoint& p)
	: m_startTime(p.m_startTime), m_endTime(p.m_endTime)
{
	m_dimension = p.m_dimension;

	m_pCoords = new double[m_dimension];
	memcpy(m_pCoords, p.m_pCoords, m_dimension * sizeof(double));
}

TimePoint::~TimePoint()
{
}

TimePoint& TimePoint::operator=(const TimePoint& p)
{
	if (this != &p)
	{
		makeDimension(p.m_dimension);
		memcpy(m_pCoords, p.m_pCoords, m_dimension * sizeof(double));
		m_startTime = p.m_startTime;
		m_endTime = p.m_endTime;
	}

	return *this;
}

bool TimePoint::operator==(const TimePoint& p) const
{
	if (
		m_startTime < p.m_startTime - std::numeric_limits<double>::epsilon() ||
		m_startTime > p.m_startTime + std::numeric_limits<double>::epsilon() ||
		m_endTime < p.m_endTime - std::numeric_limits<double>::epsilon() ||
		m_endTime > p.m_endTime + std::numeric_limits<double>::epsilon())
		return false;

	for (size_t cDim = 0; cDim < m_dimension; cDim++)
	{
		if (
			m_pCoords[cDim] < p.m_pCoords[cDim] - std::numeric_limits<double>::epsilon() ||
			m_pCoords[cDim] > p.m_pCoords[cDim] + std::numeric_limits<double>::epsilon()) 
			return false;
	}

	return true;
}

//
// IObject interface
//
TimePoint* TimePoint::clone()
{
	return new TimePoint(*this);
}

//
// ISerializable interface
//
size_t TimePoint::getByteArraySize()
{
	return (sizeof(size_t) + 2 * sizeof(double) + m_dimension * sizeof(double));
}

void TimePoint::loadFromByteArray(const byte* ptr)
{
	size_t dimension;
	memcpy(&dimension, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	memcpy(&m_startTime, ptr, sizeof(double));
	ptr += sizeof(double);
	memcpy(&m_endTime, ptr, sizeof(double));
	ptr += sizeof(double);

	makeDimension(dimension);
	memcpy(m_pCoords, ptr, m_dimension * sizeof(double));
	//ptr += m_dimension * sizeof(double);
}

void TimePoint::storeToByteArray(byte** data, size_t& len)
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
	memcpy(ptr, m_pCoords, m_dimension * sizeof(double));
	//ptr += m_dimension * sizeof(double);
}

//
// ITimeShape interface
//
bool TimePoint::intersectsShapeInTime(const ITimeShape& in) const
{
	const TimeRegion* pr = dynamic_cast<const TimeRegion*>(&in);
	if (pr != 0) return pr->containsPointInTime(*this);

	throw Tools::IllegalStateException("intersectsShapeInTime: Not implemented yet!");
}

bool TimePoint::intersectsShapeInTime(const IInterval& ivI, const ITimeShape& in) const
{
	throw Tools::IllegalStateException("intersectsShapeInTime: Not implemented yet!");
}

bool TimePoint::containsShapeInTime(const ITimeShape& in) const
{
	return false;
}

bool TimePoint::containsShapeInTime(const IInterval& ivI, const ITimeShape& in) const
{
	return false;
}

bool TimePoint::touchesShapeInTime(const ITimeShape& in) const
{
	throw Tools::IllegalStateException("touchesShapeInTime: Not implemented yet!");
}

bool TimePoint::touchesShapeInTime(const IInterval& ivI, const ITimeShape& in) const
{
	throw Tools::IllegalStateException("touchesShapeInTime: Not implemented yet!");
}

double TimePoint::getAreaInTime() const
{
	return 0.0;
}

double TimePoint::getAreaInTime(const IInterval& ivI) const
{
	return 0.0;
}

double TimePoint::getIntersectingAreaInTime(const ITimeShape& r) const
{
	return 0.0;
}

double TimePoint::getIntersectingAreaInTime(const IInterval& ivI, const ITimeShape& r) const
{
	return 0.0;
}

//
// IInterval interface
//
Tools::IInterval& TimePoint::operator=(const Tools::IInterval& i)
{
	if (this != &i)
	{
		m_startTime = i.getLowerBound();
		m_endTime = i.getUpperBound();
	}

	return *this;
}

double TimePoint::getLowerBound() const
{
	return m_startTime;
}

double TimePoint::getUpperBound() const
{
	return m_endTime;
}

void TimePoint::setBounds(double l, double h)
{
	assert(l <= h);

	m_startTime = l;
	m_endTime = h;
}

bool TimePoint::intersectsInterval(const IInterval& ti) const
{
	return intersectsInterval(ti.getIntervalType(), ti.getLowerBound(), ti.getUpperBound());
}

bool TimePoint::intersectsInterval(Tools::IntervalType t, const double start, const double end) const
{
	//if (m_startTime != start &&
	//		(m_startTime >= end || m_endTime <= start)) return false;
	if (m_startTime >= end || m_endTime <= start) return false;

	return true;
}

bool TimePoint::containsInterval(const IInterval& ti) const
{
	if (m_startTime <= ti.getLowerBound() && m_endTime >= ti.getUpperBound()) return true;
	return false;
}

Tools::IntervalType TimePoint::getIntervalType() const
{
	return Tools::IT_RIGHTOPEN;
}

void TimePoint::makeInfinite(size_t dimension)
{
	makeDimension(dimension);
	for (size_t cIndex = 0; cIndex < m_dimension; cIndex++)
	{
		m_pCoords[cIndex] = std::numeric_limits<double>::max();
	}

	m_startTime = std::numeric_limits<double>::max();
	m_endTime = -std::numeric_limits<double>::max();
}

void TimePoint::makeDimension(size_t dimension)
{
	if (m_dimension != dimension)
	{
		m_dimension = dimension;

		delete[] m_pCoords;
		m_pCoords = 0;

		m_pCoords = new double[m_dimension];
	}
}

std::ostream& SpatialIndex::operator<<(std::ostream& os, const TimePoint& pt)
{
	size_t i;

	for (i = 0; i < pt.m_dimension; i++)
	{
		os << pt.m_pCoords[i] << " ";
	}

	os << ", Start: " << pt.m_startTime << ", End: " << pt.m_endTime;

	return os;
}
