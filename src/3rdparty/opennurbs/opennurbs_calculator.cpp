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

class ON_ArithmeticCalculatorImplementation
{
public:
  ON_ArithmeticCalculatorImplementation();

  enum ARITHMETIC_OP
  {
    op_unset  = 0, // stack element is not set
    op_number = 1, // most recently entered number or expression value
    op_mult   = 2, // first operand in a multiplication
    op_div    = 3, // first operand in a division
    op_add    = 4, // first operand in a addition
    op_sub    = 5  // first operand in a subtraction
  };

  enum
  {
    // op_stack_capacity is large to accomodate expressions
    // with nested parenthises. A stack of four elements 
    // suffices to parse expressions that do not not contain
    // nested parentheses.
    op_stack_capacity = 62
  };

  // configuration settings true or false
  unsigned char m_bImpliedMultiplicationEnabled; // default = true

  // states 1 or 0
  unsigned char m_bPendingImpliedMultiplication;
  unsigned char m_bPendingUnaryPlus;
  unsigned char m_bPendingUnaryMinus;
  unsigned char m_bUnsetValue;
  unsigned char m_error_condition;
  
  unsigned char m_reserved[2];

  unsigned int m_op_stack_pointer;
  unsigned int m_expression_depth;

  struct tagOP_STACK_ELEMENT
  {
    double m_x;
    ARITHMETIC_OP m_op;
    unsigned int m_level;
  }; 

  // operation stack
  struct tagOP_STACK_ELEMENT m_op_stack[op_stack_capacity];

  //////////////////////////////////////////////////////////////
  //
  // State queries
  //
  bool IsEmpty() const;

  bool IsUnsetValue() const;

  ARITHMETIC_OP ArithmeticOperationIsPending() const;

  //////////////////////////////////////////////////////////////
  //
  // Calculation actions
  //
  bool AppendUnaryOperation(
    double sign
    );

  bool AppendNumber( double number, bool bSupportImpliedMultiplication );

  bool AppendArithmeticOperator( ARITHMETIC_OP op );

  bool IncreaseExpressionDepth();

  bool DecreaseExpressionDepth();

  bool EvaluatePendingArithmeticOperation();

  bool Evaluate(
    double* value
    );

  //////////////////////////////////////////////////////////////
  //
  // Other
  //
  void ClearStack();

  void ClearStates();
  
  void SetErrorCondition(
    ON_ArithmeticCalculator::ERROR_CONDITION error_condition
    );
};

ON_ArithmeticCalculatorImplementation::ON_ArithmeticCalculatorImplementation()
  : m_bImpliedMultiplicationEnabled(1)
{
  ClearStates();
  ClearStack();
}

ON_ArithmeticCalculator::ON_ArithmeticCalculator()
  : m_pCalc(0)
{
// suppress MSC "conditional expression is constant" warning
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
  if ( sizeof(*m_pCalc) <= sizeof(m_inplace_buffer) )
  {
    m_pCalc = new ((void*)(&m_inplace_buffer[0])) ON_ArithmeticCalculatorImplementation();
  }
#pragma ON_PRAGMA_WARNING_POP
}

ON_ArithmeticCalculator::ON_ArithmeticCalculator(const ON_ArithmeticCalculator& src)
  : m_pCalc(0)
{
  if ( 0 != src.m_pCalc )
  {
// suppress MSC "conditional expression is constant" warning
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
    if ( sizeof(*m_pCalc) <= sizeof(m_inplace_buffer) )
    {
      m_pCalc = new ((void*)(&m_inplace_buffer[0])) ON_ArithmeticCalculatorImplementation();
      *m_pCalc = *src.m_pCalc;
    }
#pragma ON_PRAGMA_WARNING_POP
  }
}

ON_ArithmeticCalculator::ON_ArithmeticCalculator(ON_ArithmeticCalculator&& src)
  : m_pCalc(0)
{
  // The && version is here because the implementation may change
  // in a way that will permit the && version to be more efficient.
  if ( 0 != src.m_pCalc )
  {
// suppress MSC "conditional expression is constant" warning
#pragma ON_PRAGMA_WARNING_PUSH
#pragma ON_PRAGMA_WARNING_DISABLE_MSC( 4127 )
    if ( sizeof(*m_pCalc) <= sizeof(m_inplace_buffer) )
    {
      m_pCalc = new ((void*)(&m_inplace_buffer[0])) ON_ArithmeticCalculatorImplementation();
      *m_pCalc = *src.m_pCalc;
    }
    src.m_pCalc = 0;
#pragma ON_PRAGMA_WARNING_POP
  }
}

ON_ArithmeticCalculator& ON_ArithmeticCalculator::operator=(const ON_ArithmeticCalculator& src)
{
  if ( this != &src )
  {
    if ( m_pCalc )
    {
      if ( src.m_pCalc )
        *m_pCalc = *src.m_pCalc;
      else
        ClearAll();
    }
  }
  return *this;
}

ON_ArithmeticCalculator& ON_ArithmeticCalculator::operator=(ON_ArithmeticCalculator&& src)
{
  // The && version is here because the implementation may change
  // in a way that will permit the && version to be more efficient.
  if ( this != &src )
  {
    if ( m_pCalc )
    {
      if ( src.m_pCalc )
      {
        *m_pCalc = *src.m_pCalc;
      }
      else
        ClearAll();
    }
    src.m_pCalc = 0;
  }
  return *this;
}



bool ON_ArithmeticCalculator::ImpliedMultiplication() const
{
  return (m_pCalc && m_pCalc->m_bImpliedMultiplicationEnabled)?true:false;
}

void ON_ArithmeticCalculator::SetImpliedMultiplication(
  bool bEnable
  )
{
  if ( m_pCalc )
  {
    m_pCalc->m_bImpliedMultiplicationEnabled = bEnable ? 1 : 0;
  }
}

ON_ArithmeticCalculator::ERROR_CONDITION ON_ArithmeticCalculator::ErrorCondition() const
{
  ERROR_CONDITION error_condition;
  if ( 0 == m_pCalc )
  {
    error_condition = ON_ArithmeticCalculator::program_error;
  }
  else
  {
    switch( m_pCalc->m_error_condition )
    {
    case ON_ArithmeticCalculator::no_error:
      error_condition = ON_ArithmeticCalculator::no_error;
      break;
    case ON_ArithmeticCalculator::program_error:
      error_condition = ON_ArithmeticCalculator::program_error;
      break;
    case ON_ArithmeticCalculator::invalid_expression_error:
      error_condition = ON_ArithmeticCalculator::invalid_expression_error;
      break;
    case ON_ArithmeticCalculator::divide_by_zero_error:
      error_condition = ON_ArithmeticCalculator::divide_by_zero_error;
      break;
    case ON_ArithmeticCalculator::overflow_error:
      error_condition = ON_ArithmeticCalculator::overflow_error;
      break;
    default:
      error_condition = ON_ArithmeticCalculator::program_error;
      break;
    }
  }

  return error_condition;
}

unsigned int ON_ArithmeticCalculator::ParenthesesDepth() const
{
  return (m_pCalc && m_pCalc->m_expression_depth > 1) ? ( m_pCalc->m_expression_depth - 1) : 0;
}

bool ON_ArithmeticCalculator::PendingUnaryOperation() const
{
  return (PendingUnaryMinus() || PendingUnaryPlus());
}

bool ON_ArithmeticCalculator::PendingUnaryPlus() const
{
  return (m_pCalc && m_pCalc->m_bPendingUnaryPlus)?true:false;
}

bool ON_ArithmeticCalculator::PendingUnaryMinus() const
{
  return (m_pCalc && m_pCalc->m_bPendingUnaryMinus)?true:false;
}

bool ON_ArithmeticCalculator::PendingImpliedMultiplication() const
{
  return ( (m_pCalc && m_pCalc->m_bImpliedMultiplicationEnabled) ?  m_pCalc->m_bPendingImpliedMultiplication : false)?true:false;
}

bool ON_ArithmeticCalculatorImplementation::AppendUnaryOperation(
  double sign
  )
{
  bool rc = false;

  for(;;)
  {
    if ( m_error_condition)
      break;

    if ( m_bPendingUnaryMinus || m_bPendingUnaryPlus )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( 1.0 == sign )
    {
      m_bPendingUnaryPlus = true;
      rc = true;
      break;
    }

    if ( -1.0 == sign )
    {
      m_bPendingUnaryMinus = true;
      rc = true;
      break;
    }

    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);

    break;
  }

  return rc;
}

bool ON_ArithmeticCalculator::UnaryPlus()
{
  return m_pCalc ? m_pCalc->AppendUnaryOperation(1.0) : false;
}

bool ON_ArithmeticCalculator::UnaryMinus()
{
  return m_pCalc ? m_pCalc->AppendUnaryOperation(-1.0) : false;
}

bool ON_ArithmeticCalculator::LeftParenthesis()
{
  return m_pCalc ? m_pCalc->IncreaseExpressionDepth() : false;
}

bool ON_ArithmeticCalculator::RightParenthesis()
{
  return m_pCalc ? m_pCalc->DecreaseExpressionDepth() : false;
}

bool ON_ArithmeticCalculatorImplementation::IncreaseExpressionDepth()
{
  if ( m_error_condition)
    return false;

  if (  IsEmpty() )
  {
    // SimpleNumber takes care of any pending unary minus or unary plus operations.
    if ( !AppendNumber(1.0,false) )
      return false;
    if ( !AppendArithmeticOperator(ON_ArithmeticCalculatorImplementation::op_mult) )
      return false;
  }
  else
  {
    if (    m_bImpliedMultiplicationEnabled 
        && ON_ArithmeticCalculatorImplementation::op_number ==  m_op_stack[m_op_stack_pointer].m_op 
        )
    {
      // previous element is a value and multiplication
      // is implied
      m_op_stack[m_op_stack_pointer].m_op = ON_ArithmeticCalculatorImplementation::op_mult;
    }

    const double unary_sign = m_bPendingUnaryMinus ? -1.0 : 1.0;
    m_bPendingUnaryMinus = false;
    m_bPendingUnaryPlus = false;
    switch(m_op_stack[m_op_stack_pointer].m_op)
    {
    case ON_ArithmeticCalculatorImplementation::op_mult:
    case ON_ArithmeticCalculatorImplementation::op_div:
      if ( false == m_bUnsetValue && 0.0 != m_op_stack[m_op_stack_pointer].m_x )
        m_op_stack[m_op_stack_pointer].m_x *= unary_sign;
      break;

    case ON_ArithmeticCalculatorImplementation::op_add:
    case ON_ArithmeticCalculatorImplementation::op_sub:
      if ( !AppendNumber(unary_sign,false) )
        return false;
      if ( !AppendArithmeticOperator(ON_ArithmeticCalculatorImplementation::op_mult) )
        return false;
      break;

    default:
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      return false;
      break;
    }
  }

  m_expression_depth++;

  return true;
}


bool ON_ArithmeticCalculatorImplementation::DecreaseExpressionDepth()
{
  if (m_error_condition)
    return false;

  if ( m_expression_depth <= 1 )
  {
    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
    return false;
  }

  if ( m_expression_depth != m_op_stack[m_op_stack_pointer].m_level )
  {
    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
    return false;    
  }

  m_bPendingImpliedMultiplication = false;

  const unsigned int pending_op = ArithmeticOperationIsPending();
  switch(pending_op)
  {
  case ON_ArithmeticCalculatorImplementation::op_add:
  case ON_ArithmeticCalculatorImplementation::op_sub:
    if ( !EvaluatePendingArithmeticOperation() )
      return false;
    break;

  case ON_ArithmeticCalculatorImplementation::op_unset:
    // empty case
    break;

  default:
    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
    return false;
    break;
  }

  if ( m_expression_depth != m_op_stack[m_op_stack_pointer].m_level )
  {
    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
    return false;    
  }

  if ( ON_ArithmeticCalculatorImplementation::op_number != m_op_stack[m_op_stack_pointer].m_op )
  {
    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
    return false;    
  }

  m_expression_depth--;
  m_op_stack[m_op_stack_pointer].m_level = m_expression_depth;

  const unsigned int previous_pending_op = ArithmeticOperationIsPending();
  switch(previous_pending_op)
  {
  case ON_ArithmeticCalculatorImplementation::op_mult:
  case ON_ArithmeticCalculatorImplementation::op_div:
    if ( !EvaluatePendingArithmeticOperation() )
      return false;
    break;
  }

  m_bPendingImpliedMultiplication = m_bImpliedMultiplicationEnabled;

  return true;
}


bool ON_ArithmeticCalculatorImplementation::AppendNumber( 
  double number, 
  bool bSupportImpliedMultiplication 
  )
{
  if (m_error_condition)
    return false;

  if (  bSupportImpliedMultiplication
        && m_bImpliedMultiplicationEnabled
        && false == IsEmpty() 
        && m_expression_depth > 0
        && m_expression_depth == m_op_stack[m_op_stack_pointer].m_level
        && ON_ArithmeticCalculatorImplementation::op_number == m_op_stack[m_op_stack_pointer].m_op 
      )
  {
    m_op_stack[m_op_stack_pointer].m_op = ON_ArithmeticCalculatorImplementation::op_mult;
  }

  m_bPendingImpliedMultiplication = false;

  double x = ON_UNSET_VALUE;
  if ( ON_UNSET_VALUE == number )
  {
    if ( !m_bUnsetValue )
      m_bUnsetValue = true;
    m_bPendingUnaryPlus = false;
    m_bPendingUnaryMinus = false;
  }
  else if ( !ON_IsValid(number) )
  {
    SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
    return false;
  }
  else
  {
    x = ( 0.0 != number ) ? number : 0.0;
    if ( m_bPendingUnaryMinus )
    {
      if ( 0.0 != x )
        x = -x;
      m_bPendingUnaryMinus = false;
    }
    else if ( m_bPendingUnaryPlus )
    {
      m_bPendingUnaryPlus = false;
    }
  }

  if ( IsEmpty() )
  {
    m_expression_depth = 1;
    m_op_stack_pointer = 0;
  }
  else
  {
    if ( m_expression_depth <= 0 )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      return false;
    }

    switch( m_op_stack[m_op_stack_pointer].m_op )
    {
    case ON_ArithmeticCalculatorImplementation::op_mult:
    case ON_ArithmeticCalculatorImplementation::op_div:
    case ON_ArithmeticCalculatorImplementation::op_add:
    case ON_ArithmeticCalculatorImplementation::op_sub:
      break;
    default:
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      return false;
      break;
    }

    m_op_stack_pointer++;
    if ( m_op_stack_pointer >= ON_ArithmeticCalculatorImplementation::op_stack_capacity )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      return false;
    }
  }

  m_op_stack[m_op_stack_pointer].m_x = x;
  m_op_stack[m_op_stack_pointer].m_op = ON_ArithmeticCalculatorImplementation::op_number;
  m_op_stack[m_op_stack_pointer].m_level = m_expression_depth;

  switch( ArithmeticOperationIsPending() )
  {
  case ON_ArithmeticCalculatorImplementation::op_mult:
  case ON_ArithmeticCalculatorImplementation::op_div:
    if ( !EvaluatePendingArithmeticOperation() )
      return false;
    break;
  default:
    break;
  }

  if ( bSupportImpliedMultiplication )
    m_bPendingImpliedMultiplication = m_bImpliedMultiplicationEnabled;

  return true;
}


bool ON_ArithmeticCalculator::Number(double number)
{
  return m_pCalc ? m_pCalc->AppendNumber(number,true) : false;
}

bool ON_ArithmeticCalculator::SimpleNumber(double number)
{
  return m_pCalc ? m_pCalc->AppendNumber(number,false) : false;
}

bool ON_ArithmeticCalculator::Multiply()
{
  return m_pCalc ? m_pCalc->AppendArithmeticOperator(ON_ArithmeticCalculatorImplementation::op_mult) : false;
}

bool ON_ArithmeticCalculator::Divide()
{
  return m_pCalc ? m_pCalc->AppendArithmeticOperator(ON_ArithmeticCalculatorImplementation::op_div) : false;
}

bool ON_ArithmeticCalculator::Add()
{
  return m_pCalc ? m_pCalc->AppendArithmeticOperator(ON_ArithmeticCalculatorImplementation::op_add) : false;
}

bool ON_ArithmeticCalculator::Subtract()
{
  return m_pCalc ? m_pCalc->AppendArithmeticOperator(ON_ArithmeticCalculatorImplementation::op_sub) : false;
}

void ON_ArithmeticCalculator::ClearAll()
{
  if ( m_pCalc )
  {
    // Do not clear configuration settings.
  
    // clear operation stack
    m_pCalc->ClearStack();
  
    // clear states
    m_pCalc->ClearStates();
  }
}

void ON_ArithmeticCalculatorImplementation::ClearStack()
{
  m_op_stack_pointer = 0;
  m_expression_depth = 0;
  m_op_stack[0].m_x = 0.0;
  m_op_stack[0].m_op = ON_ArithmeticCalculatorImplementation::op_unset;
  m_op_stack[0].m_level = 0;
}

void ON_ArithmeticCalculatorImplementation::ClearStates()
{
  m_bPendingImpliedMultiplication = false;
  m_bPendingUnaryPlus = false;
  m_bPendingUnaryMinus = false;
  m_bUnsetValue = false;
  m_error_condition = ON_ArithmeticCalculator::no_error;
}

bool ON_ArithmeticCalculator::Evaluate(double* value)
{
  double z = ON_UNSET_VALUE;
  bool rc = m_pCalc ? m_pCalc->Evaluate(&z) : false;
  if ( value )
    *value = z;
  return rc;
}

bool ON_ArithmeticCalculatorImplementation::Evaluate(double* value)
{
  bool rc = false;
  double x = ON_UNSET_VALUE;

  for(;;)
  {
    if ( 1 != m_expression_depth )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( 1 == m_op_stack_pointer )
    {
      if ( !EvaluatePendingArithmeticOperation() )
        break;
    }

    if (    0 != m_op_stack_pointer 
         || ON_ArithmeticCalculatorImplementation::op_number != m_op_stack[0].m_op
         || 1 != m_op_stack[0].m_level
       )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( m_bUnsetValue )
    {
      rc = true;
      break;
    }

    if ( !ON_IsValid(m_op_stack[0].m_x) )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    x = m_op_stack[0].m_x;
    rc = true;
    break;
  }

  if ( 0 != value )
    *value = x;

  return rc;
}

bool ON_ArithmeticCalculatorImplementation::IsEmpty() const
{
  if (m_error_condition)
    return false;

  return ( 0 == m_op_stack_pointer && 0 == m_expression_depth );
}

bool ON_ArithmeticCalculatorImplementation::IsUnsetValue() const
{
  if (m_error_condition)
    return false;

  return m_bUnsetValue?true:false;
}

void ON_ArithmeticCalculatorImplementation::SetErrorCondition(
    ON_ArithmeticCalculator::ERROR_CONDITION error_condition
    )
{
  if ( ON_ArithmeticCalculator::no_error == m_error_condition )
  {
    ClearStack();
    ClearStates();

    if (ON_ArithmeticCalculator::no_error == error_condition)
      error_condition = ON_ArithmeticCalculator::program_error;

    m_error_condition = (unsigned char)error_condition;
  }
}

bool ON_ArithmeticCalculatorImplementation::AppendArithmeticOperator( 
  ON_ArithmeticCalculatorImplementation::ARITHMETIC_OP op 
  )
{
  bool rc = false;

  for(;;)
  {
    if (m_error_condition)
      break;

    if ( IsEmpty() )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( m_bPendingUnaryPlus || m_bPendingUnaryMinus )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( m_expression_depth < 1 )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( ON_ArithmeticCalculatorImplementation::op_number != m_op_stack[m_op_stack_pointer].m_op )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( m_expression_depth != m_op_stack[m_op_stack_pointer].m_level )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    // specifying an explicit aritimetic operator clears the
    // potential for implied multiplication that occures after
    // a "symbol" value or right parenthesis.
    m_bPendingImpliedMultiplication = false;

    switch( op )
    {
    case ON_ArithmeticCalculatorImplementation::op_add:
    case ON_ArithmeticCalculatorImplementation::op_sub:
      switch(ArithmeticOperationIsPending())
      {
        case ON_ArithmeticCalculatorImplementation::op_add:
        case ON_ArithmeticCalculatorImplementation::op_sub:
          if ( !EvaluatePendingArithmeticOperation() )
            return false;
        break;
        default:
          break;
      }
      break;
    default:
      break;
    }

    m_op_stack[m_op_stack_pointer].m_op = op;
    rc = true;

    break;
  }

  return true;
}

ON_ArithmeticCalculatorImplementation::ARITHMETIC_OP ON_ArithmeticCalculatorImplementation::ArithmeticOperationIsPending() const
{
  ON_ArithmeticCalculatorImplementation::ARITHMETIC_OP rc = ON_ArithmeticCalculatorImplementation::op_unset;

  if ( m_error_condition )
    return rc;

  if ( m_op_stack_pointer < 1 )
    return rc;

  if ( m_op_stack[m_op_stack_pointer-1].m_level != m_op_stack[m_op_stack_pointer].m_level )
    return rc;

  if ( ON_ArithmeticCalculatorImplementation::op_number != m_op_stack[m_op_stack_pointer].m_op )
    return rc;

  if ( m_expression_depth != m_op_stack[m_op_stack_pointer].m_level )
    return rc;

  switch(m_op_stack[m_op_stack_pointer-1].m_op)
  {
  case ON_ArithmeticCalculatorImplementation::op_mult:
  case ON_ArithmeticCalculatorImplementation::op_div:
  case ON_ArithmeticCalculatorImplementation::op_add:
  case ON_ArithmeticCalculatorImplementation::op_sub:
    rc = m_op_stack[m_op_stack_pointer-1].m_op;
    break;
  default:
    break;
  }

  return rc;
}

bool ON_ArithmeticCalculatorImplementation::EvaluatePendingArithmeticOperation()
{
  double z = ON_UNSET_VALUE;
  bool rc = false;

  for(;;)
  {
    if ( m_error_condition )
      break;  

    const unsigned int op = ArithmeticOperationIsPending();
    if ( ON_ArithmeticCalculatorImplementation::op_unset == op )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    const double x = m_op_stack[m_op_stack_pointer-1].m_x;
    const double y = m_op_stack[m_op_stack_pointer].m_x;

    if ( !m_bUnsetValue && (ON_UNSET_VALUE == x || ON_UNSET_VALUE == y) )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if ( !ON_IsValid(x) || !ON_IsValid(y) )
    {
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    switch(op)
    {
    case ON_ArithmeticCalculatorImplementation::op_mult:
      z = m_bUnsetValue ? ON_UNSET_VALUE : (x*y);
      rc = true;
      break;

    case ON_ArithmeticCalculatorImplementation::op_div:
      if ( (0.0 != y) )
      {
        z = m_bUnsetValue ? ON_UNSET_VALUE : (x/y);
        rc = true;
      }
      else
      {
        SetErrorCondition(ON_ArithmeticCalculator::divide_by_zero_error);
      }
      break;

    case ON_ArithmeticCalculatorImplementation::op_add:
      z = m_bUnsetValue ? ON_UNSET_VALUE : (x + y);
      rc = true;
      break;

    case ON_ArithmeticCalculatorImplementation::op_sub:
      z = m_bUnsetValue ? ON_UNSET_VALUE : (x - y);
      rc = true;
      break;

    default:
      SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
      break;
    }

    if (!rc)
      break;

    if ( ON_UNSET_VALUE == z )
    {
      if ( !m_bUnsetValue )
      {
        SetErrorCondition(ON_ArithmeticCalculator::invalid_expression_error);
        rc = false;
        break;
      }
      break;
    }

    if ( !ON_IsValid(z) )
    {
      SetErrorCondition(ON_ArithmeticCalculator::overflow_error);
      rc = false;
      break;
    }

    break;
  }

  if (rc)
  {
    m_op_stack_pointer--;
    m_op_stack[m_op_stack_pointer].m_x = z;
    m_op_stack[m_op_stack_pointer].m_op = ON_ArithmeticCalculatorImplementation::op_number;
  }

  return rc;
}

