//
// Copyright (c) 1993-2022 Robert McNeel & Associates. All rights reserved.
// OpenNURBS, Rhinoceros, and Rhino3D are registered trademarks of Robert
// McNeel & Associates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////

#if !defined(OPENNURBS_PRIVATE_WRAP_DEFS_INC_)
#define OPENNURBS_PRIVATE_WRAP_DEFS_INC_

#if 0
// OBSOLETE
template <class T>
ON_PrivateWrap<T>::ON_PrivateWrap()
  : r(*(new(((void*)_buffer))T()))
{
  // Use placement new to construct a T class in the memory located in the _buffer[] member;
}

template <class T >
ON_PrivateWrap< T >::~ON_PrivateWrap()
{
  T * p = &r;
  if (nullptr != p)
    p->~T();
  _buffer[0] = _buffer[1] = _buffer[2] = _buffer[3] = _buffer[4] = 0;
}

template <class T >
ON_PrivateWrap< T >::ON_PrivateWrap(const ON_PrivateWrap< T >& src)
  : r(*(new(((void*)_buffer))T(src.r)))
{
  // Use in placement new to copy construct a T class in the memory located in the _buffer[] member;
}

template <class T >
ON_PrivateWrap< T >& ON_PrivateWrap< T >::operator=(const ON_PrivateWrap< T >& src)
{
  if (this != &src)
    r = src.r;
  return *this;
}

template <class T >
ON_PrivateWrap< T >::ON_PrivateWrap(const ON_PrivateWrap< T >&& src)
  : r(*(new(((void*)_buffer))T(std::move(src.r))))
{
  // Use in placement new to rvalue copy construct a T class in the memory located in the _buffer[] member;
}

template <class T >
ON_PrivateWrap< T >& ON_PrivateWrap< T >::operator=(const ON_PrivateWrap< T >&& src)
{
  if (this != &src)
    r = std::move(src.r);
  return *this;
}

template <class T >
ON_PrivateWrap< T >::operator const T * () const
{
  return &r;
}

template <class T >
ON_PrivateWrap< T >::operator T * ()
{
  return &r;
}

template <class T >
ON_PrivateWrap< T >::operator const T & () const
{
  return r;
}

template <class T >
ON_PrivateWrap< T >::operator T& ()
{
  return r;
}
#endif

#endif

