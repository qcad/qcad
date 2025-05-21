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

#include "opennurbs.h"

#if !defined(ON_COMPILING_OPENNURBS)
// This check is included in all opennurbs source .c and .cpp files to insure
// ON_COMPILING_OPENNURBS is defined when opennurbs source is compiled.
// When opennurbs source is being compiled, ON_COMPILING_OPENNURBS is defined 
// and the opennurbs .h files alter what is declared and how it is declared.
#error ON_COMPILING_OPENNURBS must be defined when compiling opennurbs
#endif

struct tagFunctionItem
{
  struct tagFunctionItem* m_prev;
  struct tagFunctionItem* m_next;
  void (*m_function)(ON__UINT_PTR);
  ON__UINT_PTR m_function_parameter;
};

ON_FunctionList::ON_FunctionList(
    size_t function_count_estimate
    )
{
  m_fsp.Create(sizeof(struct tagFunctionItem),function_count_estimate,0);
}

ON_FunctionList::~ON_FunctionList()
{
  // The return value of m_lock.GetDefaultLock() is intentionally ignored
  // because this is a destructor.
  const int dtor_lock_value = 86;
  int dtor_error = 0;
  if (false == m_lock.GetLock(dtor_lock_value))
    dtor_error = 1;
  m_head=nullptr;
  m_tail=nullptr;
  m_fsp.Destroy();
  if (false == m_lock.ReturnLock(dtor_lock_value))
  {
    dtor_error += 2;
    m_lock.BreakLock();
  }
  if (dtor_error > 0 )
  {
    ON_ERROR("Destroying a locked list - multiple delete or multiple delete or multiple exists.");
  }
}

unsigned int ON_FunctionList::AddFunction(
    void (*function)(ON__UINT_PTR),
    ON__UINT_PTR function_parameter
    )
{
  if ( 0 == function)
    return 2;

  if ( false == m_lock.GetDefaultLock() )
    return 0;

  struct tagFunctionItem* item = (struct tagFunctionItem*)m_fsp.AllocateElement();
  item->m_prev = (struct tagFunctionItem*)m_tail;
  item->m_next = 0;
  item->m_function = function;
  item->m_function_parameter = function_parameter;
  m_tail = item;
  if ( 0 == m_head )
    m_head = m_tail;

  m_lock.ReturnDefaultLock();

  return 1;
}

static struct tagFunctionItem* FindItem(
  struct tagFunctionItem* item,
  void (*function)(ON__UINT_PTR)
  )
{
  while (item)
  {
    if ( item->m_function == function )
    {
      return item;
    }
  }
  return 0;
}

unsigned int ON_FunctionList::RemoveFunction(
    void (*function)(ON__UINT_PTR),
    ON__UINT_PTR function_parameter
    )
{
  if ( 0 == function)
    return 2;

  if ( false == m_lock.GetDefaultLock() )
    return 0;

  int rc = 2;
  struct tagFunctionItem* item = FindItem((struct tagFunctionItem*)m_head,function);
  if ( item && item->m_function_parameter == function_parameter )
  {
    rc = 1;
    if ( item->m_prev )
      item->m_prev = item->m_next;
    else
      m_head = item->m_next;
    if ( item->m_next )
      item->m_next = item->m_prev;
    else
      m_tail = item->m_prev;
    m_fsp.ReturnElement(item);
  }

  m_lock.ReturnDefaultLock();

  return rc;
}

unsigned int ON_FunctionList::RemoveFunction(
    void (*function)(ON__UINT_PTR)
    )
{
  if ( 0 == function)
    return 2;

  if ( false == m_lock.GetDefaultLock() )
    return 0;

  int rc = 2;
  struct tagFunctionItem* item = FindItem((struct tagFunctionItem*)m_head,function);
  if ( item )
  {
    rc = 1;
    if ( item->m_prev )
      item->m_prev = item->m_next;
    else
      m_head = item->m_next;
    if ( item->m_next )
      item->m_next = item->m_prev;
    else
      m_tail = item->m_prev;
    m_fsp.ReturnElement(item);
  }

  m_lock.ReturnDefaultLock();

  return rc;
}


unsigned int ON_FunctionList::IsInList(
    void (*function)(ON__UINT_PTR),
    ON__UINT_PTR function_parameter
    ) const
{
  if ( 0 == function)
    return 2;

  if ( false == m_lock.GetDefaultLock() )
    return 0;

  int rc = 2;
  struct tagFunctionItem* item = FindItem((struct tagFunctionItem*)m_head,function);
  if ( item && item->m_function_parameter == function_parameter )
  {
    rc = 1;
  }

  m_lock.ReturnDefaultLock();

  return rc;
}

unsigned int ON_FunctionList::IsInList(
    void (*function)(ON__UINT_PTR)
    ) const
{
  if ( 0 == function)
    return 2;

  if ( false == m_lock.GetDefaultLock() )
    return 0;

  int rc = 2;
  struct tagFunctionItem* item = FindItem((struct tagFunctionItem*)m_head,function);
  if ( item )
  {
    rc = 1;
  }

  m_lock.ReturnDefaultLock();

  return rc;
}

bool ON_FunctionList::EmptyList()
{
  if ( false == m_lock.GetDefaultLock() )
    return false;

  m_head = 0;
  m_tail = 0;
  m_fsp.ReturnAll();

  m_lock.ReturnDefaultLock();

  return true;
}

bool ON_FunctionList::CallFunctions(
  bool bFirstToLast
  )
{
  if ( false == m_lock.GetDefaultLock() )
    return false;

  if ( bFirstToLast )
  {
    for ( struct tagFunctionItem* item = (struct tagFunctionItem*)m_head; item; item = item->m_next )
    {
      item->m_function(item->m_function_parameter);
    }
  }
  else
  {
    for ( struct tagFunctionItem* item = (struct tagFunctionItem*)m_tail; item; item = item->m_prev )
    {
      item->m_function(item->m_function_parameter);
    }
  }
    
  m_lock.ReturnDefaultLock();

  return true;
}


