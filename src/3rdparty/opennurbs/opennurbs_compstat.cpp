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

//////////////////////////////////////////////////////////////////////////
//
// ON_ComponentStatus bits
//

#define SELECTED_BIT (0x01U)
#define SELECTED_PERSISTENT_BIT (0x02U)
#define SELECTED_MASK   (SELECTED_BIT | SELECTED_PERSISTENT_BIT)
#define HIGHLIGHTED_BIT (0x04U)
#define LOCKED_BIT     (0x08U)
#define HIDDEN_BIT     (0x10U)

// A mark is a tool used in a wide variety of ways by calculations. 
// Its value is unpredictable outside the scope of a specific code block. 
// High quality calculations will save and restore mark state, 
// but this is not always the case.
// This state is not saved in archives.
#define RUNTIME_MARK_BIT (0x20U)


#define DELETED_BIT    (0x40U)

#define DAMAGED_BIT    (0x80U)

// Do NOT include RUNTIME_MARK_BIT in ALL_MASK
#define ALL_MASK (SELECTED_MASK|HIGHLIGHTED_BIT|LOCKED_BIT|HIDDEN_BIT|DELETED_BIT|DAMAGED_BIT)

ON_ComponentState ON_ComponentStateFromUnsigned(
  unsigned int state_as_unsigned
  )
{
  switch (state_as_unsigned)
  {
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Unset);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Clear);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::NotSelected);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Selected);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::SelectedPersistent);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::NotHighlighted);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Highlighted);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::NotHidden);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Hidden);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::NotLocked);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Locked);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::NotDamaged);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Damaged);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::NotDeleted);
  ON_ENUM_FROM_UNSIGNED_CASE(ON_ComponentState::Deleted);
  }

  return ON_ComponentState::Unset;
}


//enum STATE_FILTER : unsigned int
//{
//  selected = 0,
//  highlighted = 1,
//  hidden = 2,
//  locked = 4,
//  damaged = 8
//};

ON_ComponentStatus::ON_ComponentStatus(
  ON_ComponentState state
  )
{
  switch ( state)
  {
  case ON_ComponentState::Selected:
    m_status_flags = SELECTED_BIT;
    break;
  case ON_ComponentState::SelectedPersistent:
    m_status_flags = SELECTED_BIT | SELECTED_PERSISTENT_BIT;
    break;
  case ON_ComponentState::Highlighted:
    m_status_flags = HIGHLIGHTED_BIT;
    break;
  case ON_ComponentState::Hidden:
    m_status_flags = HIDDEN_BIT;
    break;
  case ON_ComponentState::Locked:
    m_status_flags = LOCKED_BIT;
    break;
  case ON_ComponentState::RuntimeMarkSet:
    m_status_flags = RUNTIME_MARK_BIT;
    break;
  case ON_ComponentState::Deleted:
    m_status_flags = DELETED_BIT;
    break;
  case ON_ComponentState::Damaged:
    m_status_flags = DAMAGED_BIT;
    break;
  default:
    m_status_flags = 0U;
    break;
  }
}

bool ON_ComponentStatus::operator==(ON_ComponentStatus b)
{
  return (m_status_flags&ALL_MASK) == (b.m_status_flags&ALL_MASK);
}

bool ON_ComponentStatus::operator!=(ON_ComponentStatus b)
{
  return (m_status_flags&ALL_MASK) != (b.m_status_flags&ALL_MASK);
}

const ON_ComponentStatus ON_ComponentStatus::LogicalAnd(ON_ComponentStatus lhs, ON_ComponentStatus rhs)
{
  ON_ComponentStatus x;
  x.m_status_flags = (lhs.m_status_flags & rhs.m_status_flags);
  return x;
}

const ON_ComponentStatus ON_ComponentStatus::LogicalOr(ON_ComponentStatus lhs, ON_ComponentStatus rhs)
{
  ON_ComponentStatus x;
  x.m_status_flags = (lhs.m_status_flags | rhs.m_status_flags);
  return x;
}

bool ON_ComponentStatus::StatusCheck(
  ON_ComponentStatus candidate,
  ON_ComponentStatus status_pass,
  ON_ComponentStatus status_fail
)
{
  if (0 != ON_ComponentStatus::LogicalAnd(candidate, status_pass).m_status_flags)
    return true;
  if (0 != ON_ComponentStatus::LogicalAnd(candidate, status_fail).m_status_flags)
    return false;
  if (0 == status_fail.m_status_flags)
    return true;
  if (0 != status_pass.m_status_flags)
    return false;
  return true;
}

bool ON_ComponentStatus::IsClear() const
{
  return (0 == (m_status_flags&ALL_MASK));
}

bool ON_ComponentStatus::IsNotClear() const
{
  return (0 != (m_status_flags&ALL_MASK));
}

unsigned int ON_ComponentStatus::SetStatus(
  ON_ComponentStatus status_to_copy
  )
{
  unsigned char s1 = (status_to_copy.m_status_flags&ALL_MASK);
  if ( 0 == (SELECTED_BIT & s1) )
    s1 &= ~SELECTED_PERSISTENT_BIT;
  if (s1 != (m_status_flags&ALL_MASK))
  {
    const unsigned char mark = (m_status_flags&RUNTIME_MARK_BIT);
    m_status_flags = (s1|mark);
    return 1;
  }
  return 0;
}

unsigned int ON_ComponentStatus::SetStates(
  ON_ComponentStatus states_to_set
  )
{
  unsigned char s1 = (m_status_flags&ALL_MASK);
  unsigned char mask = (ALL_MASK & states_to_set.m_status_flags);

  if (0 == (SELECTED_BIT & mask))
  {
    // no changes to s1's selected status
    mask &= ~SELECTED_PERSISTENT_BIT;
  }
  else
  {
    // states_to_set specifies setting selected or selected_persistent.
    //
    // Clear the persistent bit on s1.
    // If s1's SELECTED_PERSISTENT_BIT it is supposed to remain set, 
    // then mask's SELECTED_PERSISTENT_BIT is set and the 
    // s1 bit will get set by the s1 |= mask line below.
    s1 &= ~SELECTED_PERSISTENT_BIT;
  }

  s1 |= mask;
  if (s1 != (m_status_flags&ALL_MASK))
  {
    const unsigned char mark = (m_status_flags&RUNTIME_MARK_BIT);
    m_status_flags = (s1|mark);
    return 1;
  }
  return 0;
}

unsigned int ON_ComponentStatus::ClearStates(
  ON_ComponentStatus states_to_clear
  )
{
  unsigned char s1 = (m_status_flags&ALL_MASK);

  unsigned char mask = ~(ALL_MASK & states_to_clear.m_status_flags);

  switch (SELECTED_MASK & mask)
  {
  case 0: 
    // states_to_clear.IsSelectedPersistent() is true.
    // This means all selection states must be cleared from s1.
    // We are in this case because 0 = (SELECTED_MASK & mask)
    // so the s1 &= mask line below will remove any set selection
    // states from s1.
    break;

  case SELECTED_PERSISTENT_BIT:
    // states_to_clear.IsSelected() is true.
    // states_to_clear.IsSelectedPersistent() is false.
    // That is SELECTED_BIT = (SELECTED_MASK & states_to_clear.m_status_flags)
    // If s1 is selected persistent, it must stay selected.
    // If s1 is selected but not persistent, its selection state must be cleared.
    if (SELECTED_MASK == (SELECTED_MASK & s1))
    {
      // s1 is selected persistent and must stay that way
      mask |= SELECTED_MASK;
    }
    else
    {
      // s1 is not selected persistent and must end up not selected.
      mask &= ~SELECTED_MASK;
    }
    break;

  default:
    // states_to_clear.IsSelected() is false.
    // No changes to s1's selection state.
    mask |= SELECTED_MASK;
  }

  s1 &= mask;
  if (s1 != (m_status_flags & ALL_MASK))
  {
    // 29 Dec 2022, Mikko, RH-71974:
    // This is wrong, selected and highlighted are separate states. A thing can be not selected but
    // still highlighted.
    /*
    // If input was selected and highlighted,
    // and output is not selected,
    // and hightlight and not explictily cleared,
    // then preserve highlight sync by auto-clearing highlight.
    if ( 0 == (SELECTED_MASK & s1)
      && 0 != (SELECTED_MASK & m_status_flags)
      && 0 != (HIGHLIGHTED_BIT & m_status_flags)
      && 0 != (HIGHLIGHTED_BIT & s1)
      )
    { 
      // Input was selected and hightlighted,
      // output is not selected.
      // Clear highlight automatically.
      s1 &= ~HIGHLIGHTED_BIT;
    }
    */

    // preserve value of runtime mark bit on m_status_flags
    const unsigned char mark = (m_status_flags&RUNTIME_MARK_BIT);

    // change m_status_flags to new value
    m_status_flags = (s1|mark);

    return 1;
  }

  return 0;
}


ON_ComponentState ON_ComponentStatus::SelectedState() const
{
  switch ((m_status_flags & SELECTED_MASK))
  {
  case 0U:
    return ON_ComponentState::NotSelected;

  case SELECTED_BIT:
    return ON_ComponentState::Selected;

  case (SELECTED_BIT|SELECTED_PERSISTENT_BIT):
    return ON_ComponentState::SelectedPersistent;
  }

  // error
  return ON_ComponentState::NotSelected;
}

unsigned int ON_ComponentStatus::SetSelectedState(
    bool bSelectedState,
    bool bPersistent,
    bool bSynchronizeHighlight
  )
{
  if (bSelectedState)
  {
    return 
      bPersistent
      ? SetSelectedState(ON_ComponentState::SelectedPersistent, bSynchronizeHighlight)
      : SetSelectedState(ON_ComponentState::Selected, bSynchronizeHighlight)
      ;
  }
  return SetSelectedState(ON_ComponentState::NotSelected, bSynchronizeHighlight);
}

unsigned int ON_ComponentStatus::SetSelectedState(
  ON_ComponentState selected_state,
  bool bSynchronizeHighlight
  )
{
  bool bChanged = false;
  switch (selected_state)
  {
  case ON_ComponentState::NotSelected:
    if ( 0 != ClearStates(ON_ComponentStatus::Selected) )
      bChanged = true;
    if ( bSynchronizeHighlight && 0 != ClearStates(ON_ComponentStatus::Highlighted) )
      bChanged = true;
    break;

  case ON_ComponentState::Selected:
    if ( 0 != SetStates(ON_ComponentStatus::Selected) )
      bChanged = true;
    if ( bSynchronizeHighlight && 0 != SetStates(ON_ComponentStatus::Highlighted) )
      bChanged = true;
    break;

  case ON_ComponentState::SelectedPersistent:
    if ( 0 != SetStates(ON_ComponentStatus::SelectedPersistent) )
      bChanged = true;
    if ( bSynchronizeHighlight && 0 != SetStates(ON_ComponentStatus::Highlighted) )
      bChanged = true;
    break;
  default:
    break;
  }

  return bChanged ? 1U : 0U;
}

bool ON_ComponentStatus::IsSelected() const
{
  return 0 != (m_status_flags & SELECTED_BIT);
}

bool ON_ComponentStatus::IsSelectedPersistent() const
{
  return ( (SELECTED_BIT | SELECTED_PERSISTENT_BIT) == (m_status_flags & SELECTED_MASK) );
}

unsigned int ON_ComponentStatus::SetHighlightedState(
  bool bIsHighlighted
  )
{
  return bIsHighlighted ? SetStates(ON_ComponentStatus::Highlighted) : ClearStates(ON_ComponentStatus::Highlighted);
}

bool ON_ComponentStatus::IsHighlighted() const
{
  return 0 != (m_status_flags & HIGHLIGHTED_BIT);
}

bool ON_ComponentStatus::RuntimeMark() const
{
  return ( 0 != (m_status_flags & RUNTIME_MARK_BIT) );

}

bool ON_ComponentStatus::IsMarked(
  ON__UINT8 mark_bits
) const
{
  return (0 == mark_bits) ? (0 != (m_status_flags & RUNTIME_MARK_BIT)) : (mark_bits == m_mark_bits);
}


bool ON_ComponentStatus::SetRuntimeMark(
  bool bRuntimeMark
)
{
  return bRuntimeMark ? SetRuntimeMark() : ClearRuntimeMark();
}

bool ON_ComponentStatus::SetRuntimeMark()
{
  const unsigned char c = (m_status_flags | RUNTIME_MARK_BIT);
  if (c != m_status_flags)
  {
    m_status_flags = c;
    return true;
  }
  return false;
}

bool ON_ComponentStatus::ClearRuntimeMark()
{
  const unsigned char c = (m_status_flags & ~RUNTIME_MARK_BIT);
  if (c != m_status_flags)
  {
    m_status_flags = c;
    return true;
  }
  return false;
}

ON__UINT8 ON_ComponentStatus::MarkBits() const
{
  return m_mark_bits;
}

ON__UINT8 ON_ComponentStatus::SetMarkBits(ON__UINT8 bits)
{
  const ON__UINT8 rc = m_mark_bits;
  m_mark_bits = bits;
  return rc;
}


unsigned int ON_ComponentStatus::SetHiddenState(
  bool bIsHidden
  )
{
  return bIsHidden ? SetStates(ON_ComponentStatus::Hidden) : ClearStates(ON_ComponentStatus::Hidden);
}

bool ON_ComponentStatus::IsHidden() const
{
  return 0 != (m_status_flags & HIDDEN_BIT);
}

unsigned int ON_ComponentStatus::SetLockedState(
  bool bIsLocked
  )
{
  return bIsLocked ? SetStates(ON_ComponentStatus::Locked) : ClearStates(ON_ComponentStatus::Locked);
}

bool ON_ComponentStatus::IsLocked() const
{
  return 0 != (m_status_flags & LOCKED_BIT);
}

unsigned int ON_ComponentStatus::SetDeletedState(
  bool bIsDeleted
  )
{
  return bIsDeleted ? SetStates(ON_ComponentStatus::Deleted) : ClearStates(ON_ComponentStatus::Deleted);
}

bool ON_ComponentStatus::IsDeleted() const
{
  return 0 != (m_status_flags & DELETED_BIT);
}



unsigned int ON_ComponentStatus::SetDamagedState(
  bool bIsDamaged
  )
{
  return bIsDamaged ? SetStates(ON_ComponentStatus::Damaged) : ClearStates(ON_ComponentStatus::Damaged);
}

bool ON_ComponentStatus::IsDamaged() const
{
  return 0 != (m_status_flags & DAMAGED_BIT);
}

bool ON_ComponentStatus::operator==(const ON_ComponentStatus& other) const
{
  return m_status_flags == other.m_status_flags;
}

bool ON_ComponentStatus::operator!=(const ON_ComponentStatus& other) const
{
  return m_status_flags != other.m_status_flags;
}

bool ON_ComponentStatus::AllEqualStates(
  ON_ComponentStatus states_filter,
  ON_ComponentStatus comparand
  ) const
{
  unsigned char mask = (states_filter.m_status_flags & ALL_MASK);
  mask &= ~SELECTED_PERSISTENT_BIT;
  if (0 == mask)
    return false;
  
  unsigned char s1 = mask & m_status_flags;
  unsigned char s2 = mask & comparand.m_status_flags;

  return (s1 == s2);
}

bool ON_ComponentStatus::SomeEqualStates(
  ON_ComponentStatus states_filter,
  ON_ComponentStatus comparand
  ) const
{
  unsigned char mask = (states_filter.m_status_flags & ALL_MASK);
  mask &= ~SELECTED_PERSISTENT_BIT;
  if (0 == mask)
    return false;

  unsigned char s1 = mask & m_status_flags;
  unsigned char s2 = mask & comparand.m_status_flags;

  if (0 != (s1&s2))
    return true; // some set states are equal

  s1 = mask & ~s1;
  s2 = mask & ~s2;
  if (0 != (s1&s2))
    return true; // some clear states are equal

  return false;
}


bool ON_ComponentStatus::NoEqualStates(
  ON_ComponentStatus states_filter,
  ON_ComponentStatus comparand
  ) const
{
  unsigned char mask = (states_filter.m_status_flags & ALL_MASK);
  mask &= ~SELECTED_PERSISTENT_BIT;
  if (0 == mask)
    return false;

  unsigned char s1 = mask & m_status_flags;
  unsigned char s2 = mask & comparand.m_status_flags;

  return (mask == (s1 ^ s2));
}

ON_AggregateComponentStatus::ON_AggregateComponentStatus(const ON_AggregateComponentStatusEx& src)
{
  memcpy(this, &src, sizeof(*this));
}

ON_AggregateComponentStatus& ON_AggregateComponentStatus::operator=(const ON_AggregateComponentStatusEx& src)
{
  memcpy(this, &src, sizeof(*this));
  return *this;
}

ON_AggregateComponentStatusEx::ON_AggregateComponentStatusEx(const ON_AggregateComponentStatus& src)
  : ON_AggregateComponentStatus(src)
{
  Internal_ChangeStatusSerialNumber();
}

ON_AggregateComponentStatusEx& ON_AggregateComponentStatusEx::operator=(const ON_AggregateComponentStatus& src)
{
  ON_AggregateComponentStatus::operator=(src);
  Internal_ChangeStatusSerialNumber();
  return *this;
}

ON__UINT64 ON_AggregateComponentStatusEx::ComponentStatusSerialNumber() const
{
  return m_component_status_serial_number;
}

void ON_AggregateComponentStatusEx::Internal_ChangeStatusSerialNumber()
{
  m_component_status_serial_number = ON_NextContentSerialNumber();
}

bool ON_AggregateComponentStatus::ClearAllStates()
{
  if (m_current <= 1)
  {
    unsigned char c = m_current;
    unsigned int n = m_component_count;
    *this = ON_AggregateComponentStatus::Empty;
    m_current = c;
    n = m_component_count;
    return true;
  }
  return false;
}

bool ON_AggregateComponentStatusEx::ClearAllStates()
{
  Internal_ChangeStatusSerialNumber();
  return ON_AggregateComponentStatus::ClearAllStates();
}

bool ON_AggregateComponentStatus::ClearAggregateStatus(
  ON_ComponentStatus states_to_clear
  )
{
  if (states_to_clear.m_status_flags == ON_ComponentStatus::AllSet.m_status_flags || 0 == m_component_count)
    return ClearAllStates();

  if (1 == m_current)
  {
    m_aggregate_status.ClearStates(states_to_clear);
    const unsigned char s1 = m_aggregate_status.m_status_flags;
    if (0 == (SELECTED_BIT & s1))
    {
      m_selected_count = 0;
      m_selected_persistent_count = 0;
    }
    else if (0 == (SELECTED_PERSISTENT_BIT & s1))
    {
      m_selected_count -= m_selected_persistent_count;
      m_selected_persistent_count = 0;
    }
    if (0 == (HIGHLIGHTED_BIT & s1))
      m_highlighted_count = 0;
    if (0 == (LOCKED_BIT & s1))
      m_locked_count = 0;
    if (0 == (HIDDEN_BIT & s1))
      m_hidden_count = 0;
    if (0 == (DAMAGED_BIT & s1))
      m_damaged_count = 0;
    return true;
  }

  return false;
}

bool ON_AggregateComponentStatusEx::ClearAggregateStatus(
  ON_ComponentStatus states_to_clear
)
{
  Internal_ChangeStatusSerialNumber();
  return ON_AggregateComponentStatus::ClearAggregateStatus(states_to_clear);
}

bool ON_AggregateComponentStatus::IsEmpty() const
{
  return (0 == m_current);
}

bool ON_AggregateComponentStatusEx::IsEmpty() const
{
  return ON_AggregateComponentStatus::IsEmpty();
}

bool ON_AggregateComponentStatus::IsCurrent() const
{
  return (1 == m_current);
}

bool ON_AggregateComponentStatusEx::IsCurrent() const
{
  return ON_AggregateComponentStatus::IsCurrent();
}

void ON_AggregateComponentStatus::MarkAsNotCurrent()
{
  if (2 != m_current)
  {
    *this = ON_AggregateComponentStatus::Empty;
    m_current = 2;
  }
}

void ON_AggregateComponentStatusEx::MarkAsNotCurrent()
{
  Internal_ChangeStatusSerialNumber();
  return ON_AggregateComponentStatus::MarkAsNotCurrent();
}

ON_ComponentStatus ON_AggregateComponentStatus::AggregateStatus() const
{
  return m_aggregate_status;
}

ON_ComponentStatus ON_AggregateComponentStatusEx::AggregateStatus() const
{
  return ON_AggregateComponentStatus::AggregateStatus();
}

unsigned int ON_AggregateComponentStatus::ComponentCount() const
{
  return m_component_count;
}

unsigned int ON_AggregateComponentStatusEx::ComponentCount() const
{
  return ON_AggregateComponentStatus::ComponentCount();
}

unsigned int ON_AggregateComponentStatus::SelectedCount() const
{
  return m_selected_count;
}

unsigned int ON_AggregateComponentStatusEx::SelectedCount() const
{
  return ON_AggregateComponentStatus::SelectedCount();
}

unsigned int ON_AggregateComponentStatus::SelectedPersistentCount() const
{
  return m_selected_persistent_count;
}

unsigned int ON_AggregateComponentStatusEx::SelectedPersistentCount() const
{
  return ON_AggregateComponentStatus::SelectedPersistentCount();
}

unsigned int ON_AggregateComponentStatus::HighlightedCount() const
{
  return m_highlighted_count;
}

unsigned int ON_AggregateComponentStatusEx::HighlightedCount() const
{
  return ON_AggregateComponentStatus::HighlightedCount();
}

unsigned int ON_AggregateComponentStatus::HiddenCount() const
{
  return m_hidden_count;
}

unsigned int ON_AggregateComponentStatusEx::HiddenCount() const
{
  return ON_AggregateComponentStatus::HiddenCount();
}

unsigned int ON_AggregateComponentStatus::LockedCount() const
{
  return m_locked_count;
}

unsigned int ON_AggregateComponentStatusEx::LockedCount() const
{
  return ON_AggregateComponentStatus::LockedCount();
}

unsigned int ON_AggregateComponentStatus::DamagedCount() const
{
  return m_damaged_count;
}

unsigned int ON_AggregateComponentStatusEx::DamagedCount() const
{
  return ON_AggregateComponentStatus::DamagedCount();
}

bool ON_AggregateComponentStatus::Add(
  const ON_AggregateComponentStatus& aggregate_status
  )
{
  if (0 == m_current )
  {
    *this = aggregate_status;
    return m_current <= 1;
  }

  if ( m_current >= 2 )
    return false;

  if ( 0 == aggregate_status.m_current )
    return true;

  if ( aggregate_status.m_current >= 2 )
  {
    MarkAsNotCurrent();
    return false;
  }

  m_component_count += aggregate_status.m_component_count;
  
  const unsigned char s1 = aggregate_status.m_aggregate_status.m_status_flags;
  if ( 0 == s1 )
    return true;

  if (0 != (SELECTED_BIT & s1))
  {
    m_selected_count += aggregate_status.m_selected_count;
    m_selected_persistent_count += aggregate_status.m_selected_persistent_count;
  }
  if ( 0 != (HIGHLIGHTED_BIT & s1) )
    m_highlighted_count += aggregate_status.m_highlighted_count;
  if ( 0 != (LOCKED_BIT & s1) )
    m_locked_count += aggregate_status.m_locked_count;
  if ( 0 != (HIDDEN_BIT & s1) )
    m_hidden_count += aggregate_status.m_hidden_count;
  if ( 0 != (DAMAGED_BIT & s1) )
    m_damaged_count += aggregate_status.m_damaged_count;

  m_aggregate_status.m_status_flags |= s1;

  return true;
}

bool ON_AggregateComponentStatusEx::Add(
  const ON_AggregateComponentStatus& aggregate_status
)
{
  Internal_ChangeStatusSerialNumber();
  return ON_AggregateComponentStatus::Add(aggregate_status);
}

bool ON_AggregateComponentStatus::Add(
  ON_ComponentStatus component_status
  )
{
  if ( 0 == m_current )
    m_current = 1;
  else if ( 1 != m_current )
    return false;

  m_component_count++;

  const unsigned char s1 = component_status.m_status_flags;
  if ( 0 == s1 )
    return true;

  if (0 != (SELECTED_BIT & s1))
  {
    m_selected_count++;
    if (0 != (SELECTED_PERSISTENT_BIT & s1))
      m_selected_persistent_count++;
  }
  if ( 0 != (HIGHLIGHTED_BIT & s1) )
    m_highlighted_count++;
  if ( 0 != (LOCKED_BIT & s1) )
    m_locked_count++;
  if ( 0 != (HIDDEN_BIT & s1) )
    m_hidden_count++;
  if ( 0 != (DAMAGED_BIT & s1) )
    m_damaged_count++;

  m_aggregate_status.m_status_flags |= s1;

  return true;
}


bool ON_AggregateComponentStatusEx::Add(
  ON_ComponentStatus component_status
)
{
  Internal_ChangeStatusSerialNumber();
  return ON_AggregateComponentStatus::Add(component_status);
}

/////////////////////////////////////////////////////////////////
//
// ON_Object component status virtual interface
//
//
unsigned int ON_Object::ClearAllComponentStates() const
{
  return ClearComponentStates(ON_ComponentStatus::AllSet);
}

// virtual
unsigned int ON_Object::ClearComponentStates(
  ON_ComponentStatus states_to_clear
  ) const
{
  return 0U;
}

//virtual
unsigned int ON_Object::GetComponentsWithSetStates(
  ON_ComponentStatus states_filter,
  bool bAllEqualStates,
  ON_SimpleArray< ON_COMPONENT_INDEX >& components
  ) const
{
  components.SetCount(0);
  return 0U;
}
  

// virtual
unsigned int ON_Object::SetComponentStates(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus states_to_set
  ) const
{
  return 0U;
}

// virtual
unsigned int ON_Object::ClearComponentStates(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus states_to_clear
  ) const
{
  return 0U;
}
  
// virtual
unsigned int ON_Object::SetComponentStatus(
  ON_COMPONENT_INDEX component_index,
  ON_ComponentStatus status_to_copy
  ) const
{
  return 0U;
}

// virtual
ON_AggregateComponentStatus ON_Object::AggregateComponentStatus() const
{
  return ON_AggregateComponentStatus::Empty;
}

// virtual
void ON_Object::MarkAggregateComponentStatusAsNotCurrent() const
{
  return;
}

// virtual
bool ON_Object::DeleteComponents(
  const ON_COMPONENT_INDEX* ci_list,
  size_t ci_count
  )
{
  return false;
}
