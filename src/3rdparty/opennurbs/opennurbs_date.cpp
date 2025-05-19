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

  // 1582 was the first Gregorian year. See http://en.wikipedia.org/wiki/Gregorian_calendar
#define FIRST_GREGORIAN_YEAR 1582

bool ON_IsGregorianLeapYear(
  unsigned int year
  )
{
  // According to http://en.wikipedia.org/wiki/Gregorian_calendar,
  // the Gregorian calendar was introduced 24, February 1582, in 
  // the Papal States, Spain, Portugal, the Polish-Lithuanian
  // Commonwealth, and most of Italy.  However the Julian leap
  // day was omitted for the first 10 occurrences to correct
  // for the "vernal equinox drift" the Julian calendar had
  // introduced from  AD 325 to 1582.  The goal was to have
  // March 21 be the date of the vernal equinox.
  // As a result, the first Gregorian calendar leap day
  // leap day in the Gregorian calendar occurred on Feb 29, 1624.
  return ( year >= 1624 && 0 == (year %4) && (0 == (year%400) || 0 != (year%100)) );
}

unsigned int ON_DaysInGregorianYear(
  unsigned int year
  )
{
  return (year >= FIRST_GREGORIAN_YEAR) ? (ON_IsGregorianLeapYear(year) ? 366 : 365) : 0;
}

static
const unsigned int* CommonYearDayCount()
{
  static const unsigned int common_year_day_count[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
  return common_year_day_count;
}

static
const unsigned int* LeapYearDayCount()
{
  static const unsigned int leap_year_day_count[13]   = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
  return leap_year_day_count;
}

static
const unsigned int* YearDayCount(unsigned int year)
{
  return ON_IsGregorianLeapYear(year) 
        ? LeapYearDayCount()
        : CommonYearDayCount();
}

unsigned int ON_DaysInMonthOfGregorianYear(
  unsigned int year,
  unsigned int month
  )
{
  unsigned int days_in_month = 0;
  if( year >= FIRST_GREGORIAN_YEAR && month >= 1 && month <= 12)
  {
    const unsigned int* year_day_count = YearDayCount(year);
    days_in_month = year_day_count[month] - year_day_count[month-1];
  }
  return days_in_month;
}

unsigned int ON_DayOfGregorianYear(
  unsigned int year,
  unsigned int month,
  unsigned int date
  )
{
  unsigned int day_of_year = 0;
  if( year >= FIRST_GREGORIAN_YEAR && month >= 1 && month <= 12 && date >= 1 && date <= 31 )
  {
    const unsigned int* year_day_count = YearDayCount(year);
    day_of_year = year_day_count[month-1] + date;
    if ( day_of_year > year_day_count[month] )
      day_of_year = 0; // input date value too large
  }
  return day_of_year;
}

bool ON_GetGregorianMonthAndDayOfMonth(
  unsigned int year,
  unsigned int day_of_year,
  unsigned int* month,
  unsigned int* date
  )
{
  unsigned int mm = 0;
  unsigned int dd = 0;
  if( year >= FIRST_GREGORIAN_YEAR )
  {
    const unsigned int* year_day_count = YearDayCount(year);
    for ( mm = 1; mm <= 12; mm++ )
    {
      if ( day_of_year <= year_day_count[mm] )
      {
        dd = day_of_year - year_day_count[mm-1];
        break;
      }
    }
    if ( 0 == dd )
      mm = dd;
  }

  if ( 0 != month )
    *month = mm;

  if ( 0 != date )
    *date = dd;

  return (0 != dd);
}
