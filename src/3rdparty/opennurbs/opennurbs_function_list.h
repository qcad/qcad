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


#if !defined(OPENNURBS_FUNCTION_LIST_INC_)
#define OPENNURBS_FUNCTION_LIST_INC_

class ON_CLASS ON_FunctionList
{
public:
  /*
  Parameters:
    function_count_estimate - [in]
      An estimate of the maximum number of functions that will
      be in the list at any one time.  Pass 0 if you don't know.
  */
  ON_FunctionList(
    size_t function_count_estimate
    );

  ~ON_FunctionList();

  /*
  Description:
    Unconditionally add a function to the list.
  Parameters:
    function - [in]
      A function that takes a single ON__UINT_PTR parameter.
    function_parameter - [in]
  Returns:
    0: list in use
    1: function added
    2: invalid input
  */
  unsigned int AddFunction(
    void (*function)(ON__UINT_PTR),
    ON__UINT_PTR function_parameter
    );

  /*
  Returns:
    0: list in use
    1: function removed
    2: matching function not in the list
  */
  unsigned int RemoveFunction(
    void (*function)(ON__UINT_PTR)
    );

  /*
  Returns:
    0: list in use
    1: function removed
    2: matching function not in the list
  */
  unsigned int RemoveFunction(
    void (*function)(ON__UINT_PTR),
    ON__UINT_PTR function_parameter
    );

  /*
  Returns:
    0: Matching function and parameter are not in the list.
    1: Matching function and parameter are in the list.
    2: list in use
  */
   unsigned int IsInList(
    void (*function)(ON__UINT_PTR),
    ON__UINT_PTR function_parameter
    ) const;

  /*
  Returns:
    0: list in use
    1: Matching function is in the list.
    2: Matching function is not in the list.
  */
  unsigned int  IsInList(
    void (*function)(ON__UINT_PTR)
    ) const;

  /*
  Returns:
    0: list in use
    1: list was emptied
  */
  bool EmptyList();

  /*
  Description:
    Call all the functions in the function list.
  Parameters:
    bFirstToLast - [in]
      true - function are called in the order added
      false - functions are called in the reverse order added      
  Returns:
    True if the functions were called or the list is empty.
    False if the list is in use.
  */
  bool CallFunctions(
    bool bFirstToLast
    );

  /*
  Returns:
    True if the list is in use.
  */
  bool InUse() const;

  unsigned int FunctionCount() const;

private:
  ON_FixedSizePool m_fsp;
  void* m_head = nullptr;
  void* m_tail = nullptr;
  mutable ON_Lock m_lock;
};

#endif
