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

#if !defined(ON_FSP_DEFS_INC_)
#define ON_FSP_DEFS_INC_

template <class T> 
ON_SimpleFixedSizePool<T>::ON_SimpleFixedSizePool()
: ON_FixedSizePool()
{}

template <class T>
ON_SimpleFixedSizePool<T>::~ON_SimpleFixedSizePool()
{ 
  ON_FixedSizePool::Destroy();
}

template <class T>
bool ON_SimpleFixedSizePool<T>::Create( 
  size_t element_count_estimate,
  size_t block_element_count
  )
{
  return ON_FixedSizePool::Create(sizeof(T),element_count_estimate,block_element_count);
}

template <class T>
size_t ON_SimpleFixedSizePool<T>::SizeofElement() const
{
  return ON_FixedSizePool::SizeofElement();
}

template <class T>
T* ON_SimpleFixedSizePool<T>::AllocateElement()
{
  return (T *)ON_FixedSizePool::AllocateElement();
}

template <class T>
void ON_SimpleFixedSizePool<T>::ReturnElement(T* p)
{
  ON_FixedSizePool::ReturnElement(p);
}

template <class T>
void ON_SimpleFixedSizePool<T>::ReturnAll()
{
  ON_FixedSizePool::ReturnAll();
}

template <class T>
void ON_SimpleFixedSizePool<T>::Destroy()
{
  ON_FixedSizePool::Destroy();
}

template <class T>
size_t ON_SimpleFixedSizePool<T>::ActiveElementCount() const
{
  return ON_FixedSizePool::ActiveElementCount();
}

template <class T>
size_t ON_SimpleFixedSizePool<T>::TotalElementCount() const
{
  return ON_FixedSizePool::TotalElementCount();
}

template <class T>
T* ON_SimpleFixedSizePool<T>::Element(size_t element_index) const
{
  return (T *)ON_FixedSizePool::Element(element_index);
}

template <class T>
size_t ON_SimpleFixedSizePool<T>::ElementIndex(T* element_ptr) const
{
  return ON_FixedSizePool::ElementIndex(element_ptr);
}

template <class T> 
ON_SimpleFixedSizePoolIterator<T>::ON_SimpleFixedSizePoolIterator(const class ON_SimpleFixedSizePool<T>& fsp)
: ON_FixedSizePoolIterator((ON_FixedSizePool&)fsp)
{}

template <class T> 
ON_SimpleFixedSizePoolIterator<T>::ON_SimpleFixedSizePoolIterator(const class ON_SimpleFixedSizePoolIterator<T>& fsp_it)
: ON_FixedSizePoolIterator(fsp_it)
{}

template <class T>
T* ON_SimpleFixedSizePoolIterator<T>::FirstElement()
{
  return (T *)ON_FixedSizePoolIterator::FirstElement();
}


template <class T>
T* ON_SimpleFixedSizePoolIterator<T>::FirstElement(size_t element_index)
{
  return (T *)ON_FixedSizePoolIterator::FirstElement(element_index);
}

template <class T>
T* ON_SimpleFixedSizePoolIterator<T>::NextElement()
{
  return (T *)ON_FixedSizePoolIterator::NextElement();
}

template <class T>
T* ON_SimpleFixedSizePoolIterator<T>::CurrentElement()
{
  return (T *)ON_FixedSizePoolIterator::CurrentElement();
}


template <class T>
void ON_SimpleFixedSizePoolIterator<T>::Reset()
{
  ON_FixedSizePoolIterator::Reset();
}

template <class T>
T* ON_SimpleFixedSizePoolIterator<T>::FirstBlock( size_t* block_element_count )
{
  return (T *)ON_FixedSizePoolIterator::FirstBlock(block_element_count);
}

template <class T>
T* ON_SimpleFixedSizePoolIterator<T>::NextBlock( size_t* block_element_count )
{
  return (T *)ON_FixedSizePoolIterator::NextBlock(block_element_count);
}

#endif
