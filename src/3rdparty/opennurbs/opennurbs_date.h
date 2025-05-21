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

#if !defined(OPENNURBS_DATE_INC_)
#define OPENNURBS_DATE_INC_

/*
Description:
  Get the day of the year from the year, month and day_of_month.
Parameters:
  year - [in]
    >= 1582
  month - [in]
    >= 1 and <= 12
  day_of_month - [in]
    >= 1 and <= last valid day_of_month of the month
Returns:
  0: Invalid input
  1 to 366: Day of Gregorian year.
*/
ON_DECL
unsigned int ON_DayOfGregorianYear(
  unsigned int year,
  unsigned int month,
  unsigned int day_of_month
  );

/*
Parameters:
  year - [in]
    >= 1582
Returns:
  0: Invalid input
  365: If the year is a common year in the Gregorian calendar
  366: If the year is a leap year in the Gregorian calendar
*/
ON_DECL
unsigned int ON_DaysInGregorianYear(
  unsigned int year
  );
/*
Description:
  Get the number of days in a Gregorian month.
Parameters:
  year - [in]
    >= 1582
  month - [in]
    >= 1 and <= 12
Returns:
  0: Invalid input
  28, 29, 30 or 31: number of days in the specified month.
*/
ON_DECL
unsigned int ON_DaysInMonthOfGregorianYear(
  unsigned int year,
  unsigned int month
  );

/*
Description:
  Get the month and day_of_month from the year and day of year.
Parameters:
  year - [in]
    >= 1582
  day_of_year
    >= 1 and <= (ON_IsGregorianLeapYear(year) ? 366 : 365)
  month - [out]
    >= 1 and <= 12, when input parameters are valid, otherwise 0.
  day_of_month - [out]
    >= 1 and <= ON_DaysInMonthOfGregorianYear(year,month),
    when input parameters are valid, otherwise 0.
Returns:
  true: month and day_of_month returned.
  false: invalid input. Output values are zero.
*/
ON_DECL
bool ON_GetGregorianMonthAndDayOfMonth(
  unsigned int year,
  unsigned int day_of_year,
  unsigned int* month,
  unsigned int* day_of_month
  );

/*
Parameters:
  year - [in]
Returns:
  true if the year is a leap year in the Gregorian calendar.
*/
ON_DECL
bool ON_IsGregorianLeapYear(
  unsigned int year
  );

#endif
