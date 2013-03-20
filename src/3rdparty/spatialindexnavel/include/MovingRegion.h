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
	class SIDX_DLL MovingRegion : public TimeRegion, public IEvolvingShape
	{
	public:
		MovingRegion();
		MovingRegion(
			const double* pLow, const double* pHigh,
			const double* pVLow, const double* pVHigh,
			const Tools::IInterval& ti, size_t dimension);
		MovingRegion(
			const double* pLow, const double* pHigh,
			const double* pVLow, const double* pVHigh,
			double tStart, double tEnd, size_t dimension);
		MovingRegion(
			const Point& low, const Point& high,
			const Point& vlow, const Point& vhigh,
			const Tools::IInterval& ti);
		MovingRegion(
			const Point& low, const Point& high,
			const Point& vlow, const Point& vhigh,
			double tStart, double tEnd);
		MovingRegion(const Region& mbr, const Region& vbr, const Tools::IInterval& ivI);
		MovingRegion(const Region& mbr, const Region& vbr, double tStart, double tEnd);
		MovingRegion(const MovingPoint& low, const MovingPoint& high);
		MovingRegion(const MovingRegion& in);
		virtual ~MovingRegion();

		virtual MovingRegion& operator=(const MovingRegion& r);
		virtual bool operator==(const MovingRegion&) const;

		bool isShrinking() const;

		virtual double getLow(size_t index, double t) const;
		virtual double getHigh(size_t index, double t) const;
		virtual double getExtrapolatedLow(size_t index, double t) const;
		virtual double getExtrapolatedHigh(size_t index, double t) const;
		virtual double getVLow(size_t index) const;
		virtual double getVHigh(size_t index) const;

		virtual bool intersectsRegionInTime(const MovingRegion& r) const;
		virtual bool intersectsRegionInTime(const MovingRegion& r, Tools::IInterval& out) const;
		virtual bool intersectsRegionInTime(const Tools::IInterval& ivI, const MovingRegion& r, Tools::IInterval& ret) const;
		virtual bool containsRegionInTime(const MovingRegion& r) const;
		virtual bool containsRegionInTime(const Tools::IInterval& ivI, const MovingRegion& r) const;
		virtual bool containsRegionAfterTime(double t, const MovingRegion& r) const;

		virtual double getProjectedSurfaceAreaInTime() const;
		virtual double getProjectedSurfaceAreaInTime(const Tools::IInterval& ivI) const;

		virtual double getCenterDistanceInTime(const MovingRegion& r) const;
		virtual double getCenterDistanceInTime(const Tools::IInterval& ivI, const MovingRegion& r) const;

		virtual bool intersectsRegionAtTime(double t, const MovingRegion& r) const;
		virtual bool containsRegionAtTime(double t, const MovingRegion& r) const;

		virtual bool intersectsPointInTime(const MovingPoint& p) const;
		virtual bool intersectsPointInTime(const MovingPoint& p, Tools::IInterval& out) const;
		virtual bool intersectsPointInTime(const Tools::IInterval& ivI, const MovingPoint& p, Tools::IInterval& out) const;
		virtual bool containsPointInTime(const MovingPoint& p) const;
		virtual bool containsPointInTime(const Tools::IInterval& ivI, const MovingPoint& p) const;

		//virtual bool intersectsPointAtTime(double t, const MovingRegion& in) const;
		//virtual bool containsPointAtTime(double t, const MovingRegion& in) const;

		virtual void combineRegionInTime(const MovingRegion& r);
		virtual void combineRegionAfterTime(double t, const MovingRegion& r);
		virtual void getCombinedRegionInTime(MovingRegion& out, const MovingRegion& in) const;
		virtual void getCombinedRegionAfterTime(double t, MovingRegion& out, const MovingRegion& in) const;

		virtual double getIntersectingAreaInTime(const MovingRegion& r) const;
		virtual double getIntersectingAreaInTime(const Tools::IInterval& ivI, const MovingRegion& r) const;

		//
		// IObject interface
		//
		virtual MovingRegion* clone();

		//
		// ISerializable interface
		//
		virtual size_t getByteArraySize();
		virtual void loadFromByteArray(const byte* data);
		virtual void storeToByteArray(byte** data, size_t& len);

		//
		// IEvolvingShape interface
		//
		virtual void getVMBR(Region& out) const;
		virtual void getMBRAtTime(double t, Region& out) const;

		//
		// ITimeShape interface
		//
		virtual double getAreaInTime() const;
		virtual double getAreaInTime(const Tools::IInterval& ivI) const;
		virtual double getIntersectingAreaInTime(const ITimeShape& r) const;
		virtual double getIntersectingAreaInTime(const Tools::IInterval& ivI, const ITimeShape& r) const;

		virtual void makeInfinite(size_t dimension);
		virtual void makeDimension(size_t dimension);

	private:
		void initialize(
			const double* pLow, const double* pHigh,
			const double* pVLow, const double* pVHigh,
			double tStart, double tEnd, size_t dimension);

	public:
		class CrossPoint
		{
		public:
			double m_t;
			size_t m_dimension;
			size_t m_boundary;
			const MovingRegion* m_to;

			struct ascending: public std::binary_function<CrossPoint&, CrossPoint&, bool>
			{
				bool operator()(const CrossPoint& __x, const CrossPoint& __y) const { return __x.m_t > __y.m_t; }
			};
		}; // CrossPoint

	public:
		double* m_pVLow;
		double* m_pVHigh;

		friend SIDX_DLL std::ostream& operator<<(std::ostream& os, const MovingRegion& r);
	}; // MovingRegion

	SIDX_DLL std::ostream& operator<<(std::ostream& os, const MovingRegion& r);
}
