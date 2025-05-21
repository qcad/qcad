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

#if !defined(OPENNURBS_COMPSTAT_INC_)
#define OPENNURBS_COMPSTAT_INC_

//////////////////////////////////////////////////////////////////////////
//
// ON_ComponentState and ON_ComponentStatus
//

#pragma region RH_C_SHARED_ENUM [ON_ComponentState] [Rhino.Geometry.ComponentState] [internal:byte]

///<summary><para>Provides a set of values describing component state.</para>
///<para>This is not a bit field.</para>
///<para>Some of these values are mutually exclusive and should not be combined.</para></summary>
enum class ON_ComponentState : unsigned char
{
  ///<summary>Not a valid status.</summary>
  Unset = 0,

  ///<summary>This is a default component state.</summary>
  Clear = 1,

  ///<summary>This is a default component state, but not selected.</summary>
  NotSelected = 2,

  ///<summary>This component is selected.</summary>
  Selected = 3,

  ///<summary>This component is selected persistently.</summary>
  SelectedPersistent = 4,

  ///<summary>This is a default component state, but not highlighted.</summary>
  NotHighlighted = 5,

  ///<summary>This component is highlighted.</summary>
  Highlighted = 6,

  ///<summary>This is a default component state, but not hidden.</summary>
  NotHidden = 7,

  ///<summary>This component is hidden.</summary>
  Hidden = 8,

  ///<summary>This is a default component state, but not locked.</summary>
  NotLocked = 9,

  ///<summary>This component is locked.</summary>
  Locked = 10,

  ///<summary>This is a default component state, but not damaged.</summary>
  NotDamaged = 11,

  ///<summary>This component is damaged.</summary>
  Damaged = 12,

  ///<summary>This component is not deleted.</summary>
  NotDeleted = 13,

  ///<summary>This component is deleted.</summary>
  Deleted = 14,

  ///<summary>This runtime mark is clear.</summary>
  RuntimeMarkClear = 15,

  ///<summary>This runtime mark is set.</summary>
  RuntimeMarkSet = 16
};
#pragma endregion

ON_DECL 
ON_ComponentState ON_ComponentStateFromUnsigned( 
  unsigned int state_as_unsigned
  );

class ON_CLASS ON_ComponentStatus
{
public:

  static const ON_ComponentStatus NoneSet;
  static const ON_ComponentStatus Selected;
  static const ON_ComponentStatus SelectedPersistent;
  static const ON_ComponentStatus Highlighted;
  static const ON_ComponentStatus Hidden;
  static const ON_ComponentStatus Locked;
  static const ON_ComponentStatus Deleted;
  static const ON_ComponentStatus Damaged;
  static const ON_ComponentStatus Marked;

  /*
  The six bits for SelectedPersistent, Highlighted, Hidden, Locked, and Damaged are set.
  The two bits for Deleted and RuntimeMark are clear.
  */
  static const ON_ComponentStatus AllSet;

  /*
  Returns:
    A logical and of the status bit in lhs and rhs.
  */
  static const ON_ComponentStatus LogicalAnd(ON_ComponentStatus lhs, ON_ComponentStatus rhs);

  /*
  Returns:
    A logical and of the status bit in lhs and rhs.
  */
  static const ON_ComponentStatus LogicalOr(ON_ComponentStatus lhs, ON_ComponentStatus rhs);

  /*
  Description:
    A tool for adding a status check filter. This tool pays attention to RuntimeMark().

  Parameters:
    candidate - [in]
    pass_bits - [in]
    fail_bits - [in]

  Returns:
    Checking is performed in the following order and every bit, include the RuntimeMark() bit, are tested.

    First:
    If ON_ComponentStatus::LogicalAnd(candidate,status_pass) has any set bits,
    then true is returned.

    Second:
    If ON_ComponentStatus::LogicalAnd(candidate,status_fail) has any set bits,
    then false is returned.

    Third:
    If status_fail has no set bits the true is returned.

    Forth:
    If status_pass has any set bits then false is returned.

    Fifth:
    True is returned.

  Examples:
    StatusCheck(candidate,ON_ComponentStatus::Selected,ON_ComponentStatus::NoneSet) = candidate.>IsSelected().

    StatusCheck(candidate,ON_ComponentStatus::NoneSet,ON_ComponentStatus::Selected) = !candidate.>IsSelected().

    StatusCheck(candidate,ON_ComponentStatus::NoneSet,ON_ComponentStatus::NoneSet) = true;

    StatusCheck(candidate,ON_ComponentStatus::AllSet,ON_ComponentStatus::NoneSet) = true;

    StatusCheck(candidate,ON_ComponentStatus::NoneSet,ON_ComponentStatus::AllSet) = candidate.IsClear() && false==candidate.RuntimeMark();
  */
  static bool StatusCheck(
    ON_ComponentStatus candidate,
    ON_ComponentStatus status_pass,
    ON_ComponentStatus status_fail
  );

  ON_ComponentStatus() = default;
  ~ON_ComponentStatus() = default;
  ON_ComponentStatus(const ON_ComponentStatus&) = default;
  ON_ComponentStatus& operator=(const ON_ComponentStatus&) = default;

  /*
  Description:
    Constructs a status with the specified state set.
  */
  ON_ComponentStatus(
    ON_ComponentState state
    );

  bool operator==(ON_ComponentStatus);
  bool operator!=(ON_ComponentStatus);

  /*
  Returns:
    True if every setting besides runtime mark is 0 or false.
    Ignores the runtime mark state.
  Remarks:
    The runtime mark setting is ignored by IsClear().
  */
  bool IsClear() const;

  /*
  Returns:
    True if some setting besides runtime mark is 1 or true.
    Ignores the runtime mark state.
  Remarks:
    The runtime mark setting is ignored by IsNotClear().
  */
  bool IsNotClear() const;

  /*
  Description:
    Sets *this = status_to_copy and returns 1 if a state setting changed.
  Returns:
    1 if status changed.
    0 if status did not change.
  Remarks:
    The runtime mark setting cannot be changed using SetStatus().
  */
  unsigned int SetStatus(
    ON_ComponentStatus status_to_copy
    );

  /*
  Description:
    If a state is set in states_to_set, the same state is set in "this".
  Parameters:
    states_to_set - [in]
  Returns:
    1 if status changed.
    0 if status did not change.
  Remarks:
    The runtime mark setting cannot be changed using SetStates().
  */
  unsigned int SetStates(
    ON_ComponentStatus states_to_set
    );

  /*
  Description:
    If a state is set in states_to_clear, the same state is cleared in "this".
  Parameters:
    states_to_clear - [in]
  Returns:
    1 if status changed.
    0 if status did not change.
  Remarks:
    The runtime mark setting cannot be changed using ClearStates().
  */
  unsigned int ClearStates(
    ON_ComponentStatus states_to_clear
    );

  //////////////////////////////////////////////////////////////////////////
  //
  // RuntimeMark
  //
  bool RuntimeMark() const;

  /*
  Returns:
    Input value of RuntimeMark();
  */
  bool SetRuntimeMark(
   bool bRuntimeMark
  );

  /*
  Returns:
    Input value of RuntimeMark();
  */
  bool SetRuntimeMark();

  /*
  Returns:
    Input value of RuntimeMark();
  */
  bool ClearRuntimeMark();

  ON__UINT8 MarkBits() const;

  ON__UINT8 SetMarkBits(ON__UINT8 bits);

  /*
  Returns:
    (0==mark_bits) ? RuntimeMark() : (mark_bits == MarkBits()
  */
  bool IsMarked(
    ON__UINT8 mark_bits
  ) const;


  //////////////////////////////////////////////////////////////////////////
  //
  // Selection
  //

  /*
  Returns:
      ON_ComponentState::not_selected,
      ON_ComponentState::Selected or
      ON_ComponentState::Selected_pesistent.
  */
  ON_ComponentState SelectedState() const;

  /*
  Returns:
    1 if status changed.
    0 if status did not change.
  */
  unsigned int SetSelectedState(
    bool bSelectedState,
    bool bPersistent,
    bool bSynchronizeHighlight
    );

  unsigned int SetSelectedState(
    ON_ComponentState selected_state,
    bool bSynchronizeHighlight
    );

  /*
  Returns: 
    false
      The selection state is ON_ComponentState::not_selected.
    true 
      The selection state is ON_ComponentState::Selected 
      or ON_ComponentState::Selected_pesistent.
  */
  bool IsSelected() const;

  /*
  Returns: 
    false
      The selection state is ON_ComponentState::not_selected.
    true 
      The selection state is ON_ComponentState::Selected_pesistent.
  */
  bool IsSelectedPersistent() const;

  //////////////////////////////////////////////////////////////////////////
  //
  // Highlighted
  //
  /*
  Returns:
    1 if status changed.
    0 if status did not change.
  */
  unsigned int SetHighlightedState(
    bool bIsHighlighed
    );
  
  /*
  Returns: 
    false if not highlighted.
    true otherwise.
  */
  bool IsHighlighted() const;


  //////////////////////////////////////////////////////////////////////////
  //
  // Hidden
  //

  /*
  Returns:
    1 if status changed.
    0 if status did not change.
  */
  unsigned int SetHiddenState(
    bool bIsHidden
    );

  /*
  Returns: 
    false if not hidden.
    true otherwise.
    (ON_ComponentStatus::HIDDEN_STATE::not_hidden != HiddenState())
  */
  bool IsHidden() const;

  //////////////////////////////////////////////////////////////////////////
  //
  // Locked
  //
  /*
  Returns:
    1 if status changed.
    0 if status did not change.
  */
  unsigned int SetLockedState(
    bool bIsLocked
    );

  /*
  Returns: 
    false if not locked.
    true otherwise.
    (ON_ComponentStatus::LOCKED_STATE::not_locked != LockedState())
  */
  bool IsLocked() const;

  //////////////////////////////////////////////////////////////////////////
  //
  // Deleted
  //

  /*
  Returns:
    1 if status changed.
    0 if status did not change.
  */
  unsigned int SetDeletedState(
    bool bIsDeleted
    );

  /*
  Returns: 
    false if not hidden.
    true otherwise.
    (ON_ComponentStatus::DELETED_STATE::not_deleted != DeletedState())
  */
  bool IsDeleted() const;

 
  //////////////////////////////////////////////////////////////////////////
  //
  // Damaged
  //

  /*
  Returns:
    1 if status changed.
    0 if status did not change.
  */
  unsigned int SetDamagedState(
    bool bIsDamaged
    );

  /*
  Returns: 
    false if not damaged.
    true otherwise.
    (ON_ComponentStatus::DAMAGED_STATE::not_damaged != DamagedState())
  */
  bool IsDamaged() const;


  //////////////////////////////////////////////////////////////////////////
  //
  // Checking multiple state values efficiently
  //

  bool operator==(const ON_ComponentStatus&) const;
  bool operator!=(const ON_ComponentStatus&) const;

  /*
  Parameters:
    states_filter - [in]
      If no states are specified, then false is returned.
    comparand - [in]
      If a state is set in states_filter, the corresponding state
      in "this" and comparand will be tested.  
  Returns:
    True if every tested state in "this" and comparand are identical.
  Remarks:
    For the purposes of this test, ON_ComponentState::Selected 
    and ON_ComponentState::SelectedPersistent are considered equal.
  */
  bool AllEqualStates(
    ON_ComponentStatus states_filter,
    ON_ComponentStatus comparand
    ) const;

  /*
  Parameters:
    states_filter - [in]
      If no states are specified, then false is returned.
    comparand - [in]
      If a state is set in states_filter, the corresponding state
      in "this" and comparand will be tested.
  Returns:
    True if at least one tested state in "this" and comparand are identical.
  Remarks:
    For the purposes of this test, ON_ComponentState::Selected 
    and ON_ComponentState::SelectedPersistent are considered equal.
  */
  bool SomeEqualStates(
    ON_ComponentStatus states_filter,
    ON_ComponentStatus comparand
    ) const;

  /*
  Parameters:
    states_filter - [in]
      If no states are specified, then false is returned.
    comparand - [in]
      If a state is set in states_filter, the corresponding state
      in "this" and comparand will be tested.
  Returns:
    True if every tested state in "this" and comparand are different.
  Remarks:
    For the purposes of this test, ON_ComponentState::Selected 
    and ON_ComponentState::SelectedPersistent are considered equal.
  */
  bool NoEqualStates(
    ON_ComponentStatus states_filter,
    ON_ComponentStatus comparand
    ) const;

private:
  friend class ON_AggregateComponentStatus;

  // NOTE:
  // Hidden, Selected, ..., Mark() bool values are saved
  // as single bits on m_status_flags.
  unsigned char m_status_flags = 0U;

  // extra bits for advanced marking
  // no rules for use and runtime only - never saved in 3dm archives
  // NOTE: Mark() and MarkBits() are independent.
  //   bool Mark() is a bit on m_status_flags.
  //   ON__UINT8 MarkBits() returns m_mark_bits.
  ON__UINT8 m_mark_bits = 0U;
};



//////////////////////////////////////////////////////////////////////////
//
// ON_AggregateComponentStatus
//
//


/*
ON_AggregateComponentStatus is obsolete.
It exists because the virtual interface on ON_Object and the member on ON_Brep
cannot be changed without breakky the pubic C++ SDK.
Whenever possible, use ON_AggregateComponentStatusEx.
*/
class ON_CLASS ON_AggregateComponentStatus
{
public:
  static const ON_AggregateComponentStatus Empty;
  static const ON_AggregateComponentStatus NotCurrent;

  ON_AggregateComponentStatus() = default;
  ~ON_AggregateComponentStatus() = default;
  ON_AggregateComponentStatus(const ON_AggregateComponentStatus&) = default;
  ON_AggregateComponentStatus& operator=(const ON_AggregateComponentStatus&) = default;

  ON_AggregateComponentStatus(const class ON_AggregateComponentStatusEx&);
  ON_AggregateComponentStatus& operator=(const class ON_AggregateComponentStatusEx&);

  /*
  Description:
    Sets all states to clear.  
    Marks status as current.
    Does not change component count
  Returns
    true if successful.
    false if information is not current and ClearAllStates() failed.
  */
  bool ClearAllStates();

  /*
  Description:
    Sets all states specified by states_to_clear to clear.  
    Does not change current mark.
    Does not change component count.
  Returns
    true if successful.
    false if information is not current and ClearAggregateStatus() failed.
  */
  bool ClearAggregateStatus(
    ON_ComponentStatus states_to_clear
    );

  /*
  Description:
    Add the status information in component_status to this aggregate status.
  Parameters:
    component_status - [in]
  Returns:
    true if successful.
    false if information is not current and Add failed.
  */
  bool Add(
    ON_ComponentStatus component_status
    );

  /*
  Description:
    Add the status information in aggregate_status to this aggregate status.
  Parameters:
    aggregate_status - [in]
  Returns:
    true if successful.
    false if information is not current and Add failed.
  */
  bool Add(
    const ON_AggregateComponentStatus& aggregate_status
    );

  /*
  Returns:
    true if this is empty
    false if not empty.
  */
  bool IsEmpty() const;

  /*
  Returns:
    true if the information is current (valid, up to date, ...).
    false if the information is not current.
  Remarks:
    If the information is not current, all counts are zero and states are clear.
  */
  bool IsCurrent() const;

  /*
  Description:
    Mark the information as not current.
    Erases all information.
  */
  void MarkAsNotCurrent();

  ON_ComponentStatus AggregateStatus() const;

  unsigned int ComponentCount() const;

  /*
  Returns:
    Number of components that are selected or persistently selected.
  */
  unsigned int SelectedCount() const;

  /*
  Returns:
    Number of components that are persistently selected.
  */
  unsigned int SelectedPersistentCount() const;

  unsigned int HighlightedCount() const;

  unsigned int HiddenCount() const;

  unsigned int LockedCount() const;

  unsigned int DamagedCount() const;
    
private:
  // a bitwise or of all component status settings
  ON_ComponentStatus m_aggregate_status = ON_ComponentStatus::NoneSet;

private:
  unsigned char m_current = 0; // 0 = empty, 1 = current, 2 = dirty

private:
  unsigned char m_reserved1 = 0;
    
private:
  // number of components
  unsigned int m_component_count = 0;

  // number of selected components (includes persistent and non persistent)
  unsigned int m_selected_count = 0;

  // number of selected components
  unsigned int m_selected_persistent_count = 0;

  // number of highlighted components
  unsigned int m_highlighted_count = 0;

  // number of hidden components
  unsigned int m_hidden_count = 0;

  // number of locked components
  unsigned int m_locked_count = 0;

  // number of damaged components
  unsigned int m_damaged_count = 0;
};

class ON_CLASS ON_AggregateComponentStatusEx : private ON_AggregateComponentStatus
{
public:
  static const ON_AggregateComponentStatusEx Empty;
  static const ON_AggregateComponentStatusEx NotCurrent;

  ON_AggregateComponentStatusEx() = default;
  ~ON_AggregateComponentStatusEx() = default;
  ON_AggregateComponentStatusEx(const ON_AggregateComponentStatusEx&) = default;
  ON_AggregateComponentStatusEx& operator=(const ON_AggregateComponentStatusEx&) = default;

  ON_AggregateComponentStatusEx(const ON_AggregateComponentStatus&);
  ON_AggregateComponentStatusEx& operator=(const ON_AggregateComponentStatus&);

  /*
  Returns:
    A runtime serial number that is incremented every time a component status setting 
    changes, even when the actual counts may be unknown.
    If the returned value is 0, status information is unknown.
  */
  ON__UINT64 ComponentStatusSerialNumber() const;

  /*
  Description:
    Sets all states to clear.
    Marks status as current.
    Does not change component count
  Returns
    true if successful.
    false if information is not current and ClearAllStates() failed.
  */
  bool ClearAllStates();

  /*
  Description:
    Sets all states specified by states_to_clear to clear.
    Does not change current mark.
    Does not change component count.
  Returns
    true if successful.
    false if information is not current and ClearAggregateStatus() failed.
  */
  bool ClearAggregateStatus(
    ON_ComponentStatus states_to_clear
  );

  /*
  Description:
    Add the status information in component_status to this aggregate status.
  Parameters:
    component_status - [in]
  Returns:
    true if successful.
    false if information is not current and Add failed.
  */
  bool Add(
    ON_ComponentStatus component_status
  );

  /*
  Description:
    Add the status information in aggregate_status to this aggregate status.
  Parameters:
    aggregate_status - [in]
  Returns:
    true if successful.
    false if information is not current and Add failed.
  */
  bool Add(
    const ON_AggregateComponentStatus& aggregate_status
  );

  /*
  Returns:
    true if this is empty
    false if not empty.
  */
  bool IsEmpty() const;

  /*
  Returns:
    true if the information is current (valid, up to date, ...).
    false if the information is not current.
  Remarks:
    If the information is not current, all counts are zero and states are clear.
  */
  bool IsCurrent() const;

  /*
  Description:
    Mark the information as not current.
    Erases all information.
  */
  void MarkAsNotCurrent();

  ON_ComponentStatus AggregateStatus() const;

  unsigned int ComponentCount() const;

  /*
  Returns:
    Number of components that are selected or persistently selected.
  */
  unsigned int SelectedCount() const;

  /*
  Returns:
    Number of components that are persistently selected.
  */
  unsigned int SelectedPersistentCount() const;

  unsigned int HighlightedCount() const;

  unsigned int HiddenCount() const;

  unsigned int LockedCount() const;

  unsigned int DamagedCount() const;

private:
  // Whenever component status changes, m_runtime_serial_number is changed by calling Internal_ChangeStatusSerialNumber().
  void Internal_ChangeStatusSerialNumber();
  ON__UINT64 m_component_status_serial_number = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// ON_UniqueTester
//

class ON_CLASS ON_UniqueTester
{
public:
  ON_UniqueTester() = default;
  ~ON_UniqueTester();
  ON_UniqueTester(const ON_UniqueTester&);
  ON_UniqueTester& operator=(const ON_UniqueTester&);

public:

  /*
  Description:
    If p is not in the list, it is added.
  Returns:
    True if p is in the list.
  */
  bool InList(ON__UINT_PTR x) const;

  /*
  Description:
    If p is not in the list, it is added.
  Returns:
    True if p is not in the list and was added. False if p was already in the list.
  */
  bool AddToList(ON__UINT_PTR x);

  void ClearList();

  unsigned int Count() const;

public:
  /*
  Description:
    Add x to the list. The expert caller is certain that x is not already in the list.
    For large lists, using this function when appropriate, can result in substantial
    speed improvements.
  Parameters:
    x - [in]
      A value that is known to not be in the list.
  */
  void ExpertAddNewToList(ON__UINT_PTR x);

private:
  class Block
  {
  public:
    static Block* NewBlock();
    static void DeleteBlock(Block*);

  public:
    enum : size_t {BlockCapacity=1000};
    size_t m_count = 0;
    ON__UINT_PTR* m_a = nullptr;
    class Block* m_next = nullptr;
    bool InBlock(size_t sorted_count,ON__UINT_PTR p) const;

    void SortBlock();

  private:
    static int Compare(ON__UINT_PTR* lhs, ON__UINT_PTR* rhs);
    Block() = default;
    ~Block() = delete;
    Block(const Block&) = delete;
    Block& operator=(const Block&) = delete;
  };
  
  size_t m_sorted_count = 0;
  Block* m_block_list = nullptr;

private:
  void Internal_CopyFrom(const ON_UniqueTester& src);
  void Internal_Destroy();
  void Internal_AddValue(ON__UINT_PTR x);
};

#endif
