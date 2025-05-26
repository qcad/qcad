/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2007 Robert McNeel & Associates. All rights reserved.
// Rhinoceros is a registered trademark of Robert McNeel & Assoicates.
//
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
// ALL IMPLIED WARRANTIES OF FITNESS FOR ANY PARTICULAR PURPOSE AND OF
// MERCHANTABILITY ARE HEREBY DISCLAIMED.
//				
// For complete openNURBS copyright information see <http://www.opennurbs.org>.
//
////////////////////////////////////////////////////////////////
*/

#if !defined(ON_CRASH_TEST_STATICS)

#error See instructions in the following comment.

/*

// This code defines a global function call MyGlobalCrashTestFunction
// that you can call from a release build to test your program's
// behavior when it crashes.
#define ON_CRASH_TEST_STATICS
#include "opennurbs_crashtest.h"
#undef ON_CRASH_TEST_STATICS
int MyGlobalCrashTestFunction( int crash_type, ON_TextLog& textlog )
{
  //crash_type
  //   0 = NullPtrDeRef
  //   1 = BogusPtrDeRef
  //   2 = CallNullFuncPtr
  //   3 = CallBogusFuncPtr
  //   4 = Call CRT _abort
  //   5 = Call CRT _exit99
  //   6 = DivideByDoubleZero
  //   7 = DivideByFloatZero
  //   8 = DivideByIntZero
  //   9 = log(negative number)
  //  10 = double overflow exception
  //  11 = calling throw(123)
  return CrashTestHelper(crash_type,textlog); // static function defined in opennurbs_crashtest.h
}

*/

#endif

///////////////////////////////////////////////////////////////////////////////
//
// For testing crash handling.
//

typedef int (*CRASHTEST__FUNCTION__POINTER__)(int);

static
void CrashTestHelper_GetNullIntPrt(int ** pp )
{
  *pp = 0;
}

static
void CrashTestHelper_GetBogusIntPtr(int ** pp )
{
  INT_PTR i = 0xCACAF00D;
  *pp = (int*)i;
}

static
void CrashTestHelper_GetNullFuncPtr(CRASHTEST__FUNCTION__POINTER__* pp )
{
  *pp = 0;
}

static
void CrashTestHelper_GetBogusFuncPtr(CRASHTEST__FUNCTION__POINTER__* pp )
{
  INT_PTR i = 0xCACAF00D;
  *pp = (CRASHTEST__FUNCTION__POINTER__)i;
}

static
int CrashTestHelper_DerefNullIntPtr( ON_TextLog& textlog, int crash_type, int* stack_ptr )
{
  int* ptr;
  CrashTestHelper_GetNullIntPrt(&ptr); // sets ptr = NULL
  textlog.Print("NULL ptr = %08x\n",ptr);
  *stack_ptr = *ptr;    // dereferences NULL pointer and crashes
  textlog.Print("*ptr = %d\n",*ptr);
  return crash_type;
}

static
int CrashTestHelper_DerefBogusIntPtr( ON_TextLog& textlog, int crash_type, int* stack_ptr )
{
  int* ptr;
  CrashTestHelper_GetBogusIntPtr(&ptr); // sets ptr = 0xCACAF00D
  textlog.Print("Bogus ptr = %08x\n",ptr);
  *stack_ptr = *ptr;     // dereferences bogus pointer and crashes
  textlog.Print("*ptr = %d\n",*ptr);
  return crash_type;
}

static
int CrashTestHelper_CallNullFuncPtr( ON_TextLog& textlog, int crash_type, int* stack_ptr )
{
  CRASHTEST__FUNCTION__POINTER__ fptr;
  CrashTestHelper_GetNullFuncPtr(&fptr); // sets ptr = NULL
  textlog.Print("NULL function f = %08x\n",fptr);
  *stack_ptr = fptr(crash_type); // dereferences NULL function pointer and crashes
  textlog.Print("f(%d) = %d\n",crash_type,*stack_ptr);
  return crash_type;
}

static
int CrashTestHelper_CallBoguslFuncPtr( ON_TextLog& textlog, int crash_type, int* stack_ptr )
{
  CRASHTEST__FUNCTION__POINTER__ fptr;
  CrashTestHelper_GetBogusFuncPtr(&fptr); // sets ptr = NULL
  textlog.Print("Bogus function f = %08x\n",fptr);
  *stack_ptr = fptr(crash_type); // dereferences bogus function pointer and crashes
  textlog.Print("f(%d) = %d\n",crash_type,*stack_ptr);
  return crash_type;
}

static
bool CrashTestHelper_DivideByFloatZero( ON_TextLog& textlog, const char* zero )
{
  double z;
  sscanf( zero, "%lg", &z );
  float fz = (float)z;
  textlog.Print("float fz = %f\n",fz);
  float fy = 13.0f/fz;
  textlog.Print("double 13.0f/fz = %f\n",fy);
  return (0.123f != fy);
}

static
bool CrashTestHelper_DivideByDoubleZero( ON_TextLog& textlog, const char* zero )
{
  double z;
  sscanf( zero, "%lg", &z );
  textlog.Print("double z = %g\n",z);
  double y = 13.0/z;
  textlog.Print("double 13.0/z = %g\n",y);
  return ON_IsValid(y);
}

static
bool CrashTestHelper_DivideByIntZero( ON_TextLog& textlog, const char* zero )
{
  int iz = 0, iy = 0;
  double z;
  sscanf( zero, "%lg", &z );
  iz = (int)z;
  textlog.Print("int iz = %d\n",iz);
  iy = 17/iz;
  textlog.Print("17/iz = %d\n",iy);
  return (123456 != iy);
}

static
bool CrashTestHelper_LogNegativeNumber( ON_TextLog& textlog, const char* minus_one )
{
  double z;
  sscanf( minus_one, "%lg", &z );
  textlog.Print("z = %g\n",z);
  double y = log(z);
  textlog.Print("log(z) = %g\n",y);
  return ON_IsValid(y);
}

static
bool CrashTestHelper_DoubleOverflow(  ON_TextLog& textlog, const char* sx, const char* sy )
{
  double x,y,z;
  sscanf( sx, "%lg", &x );
  sscanf( sy, "%lg", &y );
  textlog.Print("x = %g y = %g\n",x,y);
  z = x*y;
  textlog.Print("x*y = z = %g\n",z);
  return ON_IsValid(z);
}

static
bool CrashTestHelper_Throw(  ON_TextLog& textlog, const char* si )
{
  int i=0;
  sscanf( si, "%i", &i );
  textlog.Print("i = %d\n",i);
  if ( 0==strcmp("123",si) )
    throw(i);
  return (123==i);
}

/*
Description:
  Create a condition that should result in a crash.
  The intended use is for testing application crash handling.
Parameters:
  crash_type - [in]
    0: dereference NULL data pointer
    1: dereference bogus data pointer (0xCACAF00D)
    2: dereference NULL function pointer
    3: dereference bogus function pointer (0xCACAF00D)
    4: call abort()
    5: call exit(99);
    6: double divide by 0.0 - FPU exception
          well designed apps will mask the exception but detect the error
    7: float divide by 0.0 - FPU exception
          well designed apps will mask the exception but detect the error
    8: int divide by 0 - will crash
    9: log(-1.0) - should call math error handler
   10: double overflow - FPU exception
          well designed apps will mask the exception but detect the error
   11: throw(123) - well designed apps with catch the exception
                    before crashing
Returns:
  Value of crash_type parameter.
*/
#if defined(ON_COMPILER_MSC)
// Disable the MSC /W4 unreachable code warning around the exit(99) call
#pragma warning( push )
#pragma warning( disable : 4702 )
#endif

static
int CrashTestHelper( int crash_type, ON_TextLog& textlog )
{
  // Note: The code and calls are intentionally obtuse
  //       so that it is difficult for an optimizer to
  //       not perform the calculation.
  int stack_int = 0;
  int rc = crash_type;

  switch( crash_type )
  {
  case 0: // dereference NULL pointer
    rc = CrashTestHelper_DerefNullIntPtr( textlog, crash_type, &stack_int );
    break;

  case 1: // dereference bogus pointer
    rc = CrashTestHelper_DerefBogusIntPtr( textlog, crash_type, &stack_int );
    break;

  case 2: // call NULL function pointer
    rc = CrashTestHelper_CallNullFuncPtr( textlog, crash_type, &stack_int );
    break;

  case 3: // divide by zero
    rc = CrashTestHelper_CallBoguslFuncPtr( textlog, crash_type, &stack_int );
    break;

  case 4:
    abort();
    textlog.Print("abort() didn't crash.\n");
    break;

  case 5:
    exit(99);
    textlog.Print("exit(99) didn't crash.\n");
    break;

  case 6:
    if ( CrashTestHelper_DivideByDoubleZero( textlog, "0.0" ) )
    {
      textlog.Print("Divide by double 0.0 didn't crash - exception must have been handled or ignored.\n");
    }
    break;

  case 7:
    if ( CrashTestHelper_DivideByFloatZero( textlog, "0.0" ) )
    {
      textlog.Print("Divide by float 0.0f didn't crash - exception must have been handled or ignored.\n");
    }
    break;

  case 8:
    if ( CrashTestHelper_DivideByIntZero( textlog, "0.0" ) )
    {
      textlog.Print("Divide by int 0 didn't crash - exception must have been handled or ignored.\n");
    }
    break;

  case 9:
    if ( CrashTestHelper_LogNegativeNumber( textlog, "-1.0" ) )
    {
      textlog.Print("log(negative number) didn't crash - exception must have been handled or ignored.\n");
    }
    break;

  case 10:
    if ( CrashTestHelper_DoubleOverflow( textlog, "1.0e200", "2.0e222" ) )
    {
      textlog.Print("1.0e200*2.0e222 didn't crash - exception must have been handled or ignored.\n");
    }
    break;

  case 11:
    if ( CrashTestHelper_Throw( textlog, "123" ) )
    {
      textlog.Print("throw(123) crash - exception must have been handled or ignored.\n");
    }
    break;

  default:
    break;
  }

  return rc;
}

#if defined(ON_COMPILER_MSC)
#pragma warning( pop )
#endif
