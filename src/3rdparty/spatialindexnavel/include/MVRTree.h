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
	namespace MVRTree
	{
		SIDX_DLL enum MVRTreeVariant
		{
			RV_LINEAR = 0x0,
			RV_QUADRATIC,
			RV_RSTAR
		};

		SIDX_DLL enum PersistenObjectIdentifier
		{
			PersistentIndex = 0x1,
			PersistentLeaf = 0x2
		};

		SIDX_DLL enum RangeQueryType
		{
			ContainmentQuery = 0x1,
			IntersectionQuery = 0x2
		};

		class SIDX_DLL Data : public IData, public Tools::ISerializable
		{
		public:
			Data(size_t len, byte* pData, TimeRegion& r, id_type id);
			virtual ~Data();

			virtual Data* clone();
			virtual id_type getIdentifier() const;
			virtual void getShape(IShape** out) const;
			virtual void getData(size_t& len, byte** data) const;
			virtual size_t getByteArraySize();
			virtual void loadFromByteArray(const byte* data);
			virtual void storeToByteArray(byte** data, size_t& len);

			id_type m_id;
			TimeRegion m_region;
			byte* m_pData;
			size_t m_dataLength;
		}; // Data

		SIDX_DLL ISpatialIndex* returnMVRTree(IStorageManager& ind, Tools::PropertySet& in);
		SIDX_DLL ISpatialIndex* createNewMVRTree(
			IStorageManager& in,
			double fillFactor,
			size_t indexCapacity,
			size_t leafCapacity,
			size_t dimension,
			MVRTreeVariant rv,
			id_type& out_indexIdentifier
		);
		SIDX_DLL ISpatialIndex* loadMVRTree(
			IStorageManager& in,
			id_type indexIdentifier
		);
	}
}

