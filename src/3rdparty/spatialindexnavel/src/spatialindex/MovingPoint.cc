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

MovingPoint::MovingPoint()
{
}

MovingPoint::MovingPoint(const double* pCoords, const double* pVCoords, const IInterval& ti, size_t dimension)
{
	initialize(pCoords, pVCoords, ti.getLowerBound(), ti.getUpperBound(), dimension);
}

MovingPoint::MovingPoint(const double* pCoords, const double* pVCoords, double tStart, double tEnd, size_t dimension)
{
	initialize(pCoords, pVCoords, tStart, tEnd, dimension);
}

MovingPoint::MovingPoint(const Point& p, const Point& vp, const IInterval& ti)
{
	if (p.m_dimension != vp.m_dimension) throw Tools::IllegalArgumentException("MovingPoint: Points have different number of dimensions.");

	initialize(p.m_pCoords, vp.m_pCoords, ti.getLowerBound(), ti.getUpperBound(), p.m_dimension);
}

MovingPoint::MovingPoint(const Point& p, const Point& vp, double tStart, double tEnd)
{
	if (p.m_dimension != vp.m_dimension) throw Tools::IllegalArgumentException("MovingPoint: Points have different number of dimensions.");

	initialize(p.m_pCoords, vp.m_pCoords, tStart, tEnd, p.m_dimension);
}

MovingPoint::MovingPoint(const MovingPoint& p)
{
	m_startTime = p.m_startTime;
	m_endTime = p.m_endTime;
	m_pCoords = 0;

	m_dimension = p.m_dimension;

	try
	{
		m_pCoords = new double[m_dimension];
		m_pVCoords = new double[m_dimension];
	}
	catch (...)
	{
		delete[] m_pCoords;
		throw;
	}

	memcpy(m_pCoords, p.m_pCoords, m_dimension * sizeof(double));
	memcpy(m_pVCoords, p.m_pVCoords, m_dimension * sizeof(double));
}

MovingPoint::~MovingPoint()
{
	delete[] m_pVCoords;
}

void MovingPoint::initialize(
	const double* pCoords, const double* pVCoords,
	double tStart, double tEnd, size_t dimension)
{
	m_dimension = dimension;
	m_startTime = tStart;
	m_endTime = tEnd;
	m_pCoords = 0;

	if (m_endTime <= m_startTime) throw Tools::IllegalArgumentException("MovingPoint: Cannot support degenerate time intervals.");

	try
	{
		m_pCoords = new double[m_dimension];
		m_pVCoords = new double[m_dimension];
	}
	catch (...)
	{
		delete[] m_pCoords;
		throw;
	}

	// first store the point coordinates, than the point velocities.
	memcpy(m_pCoords, pCoords, m_dimension * sizeof(double));
	memcpy(m_pVCoords, pVCoords, m_dimension * sizeof(double));
}

MovingPoint& MovingPoint::operator=(const MovingPoint& p)
{
	if (this != &p)
	{
		makeDimension(p.m_dimension);
		memcpy(m_pCoords, p.m_pCoords, m_dimension * sizeof(double));
		memcpy(m_pVCoords, p.m_pVCoords, m_dimension * sizeof(double));

		m_startTime = p.m_startTime;
		m_endTime = p.m_endTime;
	}

	return *this;
}

bool MovingPoint::operator==(const MovingPoint& p) const
{
	if (
		m_startTime < p.m_startTime - std::numeric_limits<double>::epsilon() ||
		m_startTime > p.m_startTime + std::numeric_limits<double>::epsilon() ||
		m_endTime < p.m_endTime - std::numeric_limits<double>::epsilon() ||
		m_endTime > p.m_endTime + std::numeric_limits<double>::epsilon())
		return false;

	for (size_t cDim = 0; cDim < 2 * m_dimension; cDim++)
	{
		if (
			m_pCoords[cDim] < p.m_pCoords[cDim] - std::numeric_limits<double>::epsilon() ||
			m_pCoords[cDim] > p.m_pCoords[cDim] + std::numeric_limits<double>::epsilon() ||
			m_pVCoords[cDim] < p.m_pVCoords[cDim] - std::numeric_limits<double>::epsilon() ||
			m_pVCoords[cDim] > p.m_pVCoords[cDim] + std::numeric_limits<double>::epsilon()) 
			return false;
	}

	return true;
}

double MovingPoint::getCoord(size_t d, double t) const
{
	if (d < 0 && d >= m_dimension) throw Tools::IndexOutOfBoundsException(d);

	if (t >= m_endTime) return m_pCoords[d] + m_pVCoords[d] * (m_endTime - m_startTime);
	else if (t <= m_startTime) return m_pCoords[d] + m_pVCoords[d] * m_startTime;
	else return m_pCoords[d] + m_pVCoords[d] * (t - m_startTime);
}

double MovingPoint::getProjectedCoord(size_t d, double t) const
{
	if (d < 0 && d >= m_dimension) throw Tools::IndexOutOfBoundsException(d);

	return m_pCoords[d] + m_pVCoords[d] * (t - m_startTime);
}

double MovingPoint::getVCoord(size_t d) const
{
	if (d < 0 && d >= m_dimension) throw Tools::IndexOutOfBoundsException(d);

	return m_pVCoords[d];
}

void MovingPoint::getPointAtTime(double t, Point& out) const
{
	out.makeDimension(m_dimension);
	for (size_t cDim = 0; cDim < m_dimension; cDim++)
	{
		out.m_pCoords[cDim] = getCoord(cDim, t);
	}
}

//
// IObject interface
//
MovingPoint* MovingPoint::clone()
{
	return new MovingPoint(*this);
}

//
// ISerializable interface
//
size_t MovingPoint::getByteArraySize()
{
	return (sizeof(size_t) + 2 * sizeof(double) + 2 * m_dimension * sizeof(double));
}

void MovingPoint::loadFromByteArray(const byte* ptr)
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
	ptr += m_dimension * sizeof(double);
	memcpy(m_pVCoords, ptr, m_dimension * sizeof(double));
	//ptr += m_dimension * sizeof(double);
}

void MovingPoint::storeToByteArray(byte** data, size_t& len)
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
	ptr += m_dimension * sizeof(double);
	memcpy(ptr, m_pVCoords, m_dimension * sizeof(double));
	//ptr += m_dimension * sizeof(double);
}

//
// IEvolvingShape interface
//
void MovingPoint::getVMBR(Region& out) const
{
	out.makeDimension(m_dimension);
	memcpy(out.m_pLow, m_pVCoords, m_dimension * sizeof(double));
	memcpy(out.m_pHigh, m_pVCoords, m_dimension * sizeof(double));
}

void MovingPoint::getMBRAtTime(double t, Region& out) const
{
	out.makeDimension(m_dimension);
	for (size_t cDim = 0; cDim < m_dimension; cDim++)
	{
		out.m_pLow[cDim] = getCoord(cDim, t);
		out.m_pHigh[cDim] = getCoord(cDim, t);
	}
}

void MovingPoint::makeInfinite(size_t dimension)
{
	makeDimension(dimension);
	for (size_t cIndex = 0; cIndex < m_dimension; cIndex++)
	{
		m_pCoords[cIndex] = std::numeric_limits<double>::max();
		m_pVCoords[cIndex] = -std::numeric_limits<double>::max();
	}

	m_startTime = std::numeric_limits<double>::max();
	m_endTime = -std::numeric_limits<double>::max();
}

void MovingPoint::makeDimension(size_t dimension)
{
	if (m_dimension != dimension)
	{
		delete[] m_pCoords;
		delete[] m_pVCoords;
		m_pCoords = 0; m_pVCoords = 0;

		m_dimension = dimension;
		m_pCoords = new double[m_dimension];
		m_pVCoords = new double[m_dimension];
	}
}

std::ostream& SpatialIndex::operator<<(std::ostream& os, const MovingPoint& pt)
{
	size_t i;

	os << "Coords: ";
	for (i = 0; i < pt.m_dimension; i++)
	{
		os << pt.m_pCoords[i] << " ";
	}

	os << "VCoords: ";
	for (i = 0; i < pt.m_dimension; i++)
	{
		os << pt.m_pVCoords[i] << " ";
	}

	os << ", Start: " << pt.m_startTime << ", End: " << pt.m_endTime;

	return os;
}
