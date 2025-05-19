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

// ON_2iPoint
ON_2iPoint::ON_2iPoint(int xValue, int yValue)
  : x(xValue)
  , y(yValue)
{}

const ON_2iPoint ON_2iPoint::From2dex(const class ON_2dex& src)
{
  return ON_2iPoint(src.i, src.j);
}

bool ON_2iPoint::IsSet() const
{
  return (ON_UNSET_INT_INDEX != x && ON_UNSET_INT_INDEX != y );
}

bool ON_2iPoint::IsOrigin() const
{
  return (0 == x && 0 == y);
}

ON_2iPoint& ON_2iPoint::operator+=(const class ON_2iVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2iPoint& ON_2iPoint::operator-=(const class ON_2iVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

bool operator==(const ON_2iPoint& lhs, const ON_2iPoint& rhs)
{
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const ON_2iPoint& lhs, const ON_2iPoint& rhs)
{
  return (lhs.x != rhs.x || lhs.y != rhs.y);
}

int ON_2iPoint::Compare(
  const ON_2iPoint& lhs,
  const ON_2iPoint& rhs
)
{
  if (lhs.x < rhs.x)
    return -1;
  if (lhs.x > rhs.x)
    return 1;
  if (lhs.y < rhs.y)
    return -1;
  if (lhs.y > rhs.y)
    return 1;
  return 0;
}

const ON_2iPoint ON_2iPoint::FromVector(const class ON_2iVector& v)
{
  return ON_2iPoint(v.x, v.y);
}

// ON_2iVector
ON_2iVector::ON_2iVector(int xValue, int yValue)
  : x(xValue)
  , y(yValue)
{}

const ON_2iVector ON_2iVector::From2dex(const class ON_2dex& src)
{
  return ON_2iVector(src.i, src.j);
}

bool ON_2iVector::IsSet() const
{
  return (ON_UNSET_INT_INDEX != x && ON_UNSET_INT_INDEX != y );
}

bool ON_2iVector::IsZero() const
{
  return (0 == x && 0 == y);
}

bool ON_2iVector::IsNotZero() const
{
  return ((0 != x || 0 != y) && IsSet());
}


ON_2iVector& ON_2iVector::operator+=(const class ON_2iVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2iVector& ON_2iVector::operator-=(const class ON_2iVector& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

ON_2iVector& ON_2iVector::operator*=(int s)
{
  x *= s;
  y *= s;
  return *this;
}

ON_2iVector ON_2iVector::operator-() const
{
	return ON_2iVector(-x, -y);
}

bool operator==(const ON_2iVector& lhs, const ON_2iVector& rhs)
{
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const ON_2iVector& lhs, const ON_2iVector& rhs)
{
  return (lhs.x != rhs.x || lhs.y != rhs.y);
}

int ON_2iVector::Compare(
  const ON_2iVector& lhs,
  const ON_2iVector& rhs
)
{
  if (lhs.x < rhs.x)
    return -1;
  if (lhs.x > rhs.x)
    return 1;
  if (lhs.y < rhs.y)
    return -1;
  if (lhs.y > rhs.y)
    return 1;
  return 0;
}

const ON_2iVector ON_2iVector::FromPoint(const class ON_2iPoint& p)
{
  return ON_2iVector(p.x, p.y);
}

//////////////////////////////////////////////////////

ON_2iPoint operator+(const ON_2iPoint& lhs, const ON_2iVector& rhs)
{
  ON_2iPoint p(lhs.x + rhs.x, lhs.y + rhs.y);
  return p;
}

ON_2iPoint operator-(const ON_2iPoint& lhs, const ON_2iVector& rhs)
{
  ON_2iPoint p(lhs.x - rhs.x, lhs.y - rhs.y);
  return p;
}

ON_2iVector operator+(const ON_2iVector& lhs, const ON_2iVector& rhs)
{
  ON_2iVector v(lhs.x + rhs.x, lhs.y + rhs.y);
  return v;
}

ON_2iVector operator-(const ON_2iVector& lhs, const ON_2iVector& rhs)
{
  ON_2iVector v(lhs.x - rhs.x, lhs.y - rhs.y);
  return v;
}

ON_2iVector operator*(int lhs, const ON_2iVector& rhs)
{
  ON_2iVector v(lhs*rhs.x, lhs*rhs.y);
  return v;
}

// ON_2iBoundingBox
ON_2iBoundingBox::ON_2iBoundingBox(
  const class ON_2iPoint bbox_min,
  const class ON_2iPoint bbox_max
)
  : m_min(bbox_min)
  , m_max(bbox_max)
{}

bool ON_2iBoundingBox::IsSet() const
{
  return (
    m_min.x <= m_max.x
    && m_min.y <= m_max.y
    && m_min.IsSet()
    && m_max.IsSet()
    );
}

const ON_2iPoint ON_2iBoundingBox::Min() const
{
  return m_min;
}

const ON_2iPoint ON_2iBoundingBox::Max() const
{
  return m_max;
}

bool operator==(const ON_2iBoundingBox& lhs, const ON_2iBoundingBox& rhs)
{
  return (lhs.m_min == rhs.m_min && lhs.m_max == rhs.m_max);
}

bool operator!=(const ON_2iBoundingBox& lhs, const ON_2iBoundingBox& rhs)
{
  return (lhs.m_min != rhs.m_min || lhs.m_max != rhs.m_max);
}

// ON_2iSize

int ON_2iSize::Compare(
  const ON_2iSize& lhs,
  const ON_2iSize& rhs
)
{
  if (lhs.cx < rhs.cx)
    return -1;
  if (lhs.cx > rhs.cx)
    return 1;
  if (lhs.cy < rhs.cy)
    return -1;
  if (lhs.cy > rhs.cy)
    return 1;
  return 0;
}

int ON_2iSize::ComparePointer(
  const ON_2iSize* lhs,
  const ON_2iSize* rhs
)
{
  if (lhs == rhs)
    return 0;
  if (nullptr == lhs)
    return -1;
  if (nullptr == rhs)
    return 1;
  if (lhs->cx < rhs->cx)
    return -1;
  if (lhs->cx > rhs->cx)
    return 1;
  if (lhs->cy < rhs->cy)
    return -1;
  if (lhs->cy > rhs->cy)
    return 1;
  return 0;
}

ON_2iSize::ON_2iSize(int cxValue, int cyValue)
  : cx(cxValue)
  , cy(cyValue)
{}

bool ON_2iSize::IsSet() const
{
  return (ON_UNSET_INT_INDEX != cx && ON_UNSET_INT_INDEX != cy);
}

bool ON_2iSize::IsZero() const
{
  return (0 == cx && 0 == cy);
}

bool operator==(
  const ON_2iSize& lhs,
  const ON_2iSize& rhs
  )
{
  return (lhs.cx == rhs.cx && lhs.cy == rhs.cy);
}

bool operator!=(const ON_2iSize& lhs, const ON_2iSize& rhs)
{
  return (lhs.cx != rhs.cx || lhs.cy != rhs.cy);
}

// ON_4iRect
ON_4iRect::ON_4iRect(int leftValue, int topValue, int rightValue, int bottomValue)
  : left(leftValue)
  , top(topValue)
  , right(rightValue)
  , bottom(bottomValue)
{}

ON_4iRect::ON_4iRect(const ON_2iPoint topLeft, const ON_2iPoint& bottomRight)
	: left(topLeft.x)
	, top(topLeft.y)
	, right(bottomRight.x)
	, bottom(bottomRight.y)
{}

ON_4iRect::ON_4iRect(const ON_2iPoint& point, const ON_2iSize& size)
{
	left = point.x;
	top = point.y;
	right = left + size.cx;
	bottom = top + size.cy;
}

bool ON_4iRect::IsSet() const
{
  return (
    ON_UNSET_INT_INDEX != left 
    && ON_UNSET_INT_INDEX != top
    && ON_UNSET_INT_INDEX != right
    && ON_UNSET_INT_INDEX != bottom
    );
}

int ON_4iRect::Width(void) const { return std::abs(right - left); }

int ON_4iRect::Height(void) const { return std::abs(bottom - top); }

const ON_2iSize ON_4iRect::Size(void) const { return ON_2iSize(Width(), Height()); }

const ON_2iPoint ON_4iRect::CenterPoint(void) const { return ON_2iPoint((left + right) / 2, (top + bottom) / 2); }

const ON_2iPoint ON_4iRect::TopLeft(void) const { return ON_2iPoint(left, top); }

const ON_2iPoint ON_4iRect::BottomRight(void) const { return ON_2iPoint(right, bottom); }

bool ON_4iRect::IntersectRect(const ON_4iRect * r1, const ON_4iRect * r2)
{
  left = ON_Max(r1->left, r2->left);
  right = ON_Min(r1->right, r2->right);
  if (right > left)
  {
    top = ON_Max(r1->top, r2->top);
    bottom = ON_Min(r1->bottom, r2->bottom);
    if (bottom > top)
      return true;
  }

  // degenerate rectangle at this point...
  SetRectEmpty();
  return false;
}

bool ON_4iRect::IntersectRect(const ON_4iRect & r1, const ON_4iRect & r2) { return IntersectRect(&r1, &r2); }

bool ON_4iRect::IsRectEmpty(void) const 
{ 
	return 0 == Width() || 0 == Height(); 
}

bool ON_4iRect::IsRectNull(void) const
{ 
	return 0 == left &&
		   0 == top  &&
		   0 == bottom &&
		   0 == right; 
}

void ON_4iRect::SetRect(int l, int t, int r, int b) { left = l; top = t; right = r; bottom = b; }

bool ON_4iRect::PtInRect(const ON_2iPoint & pt) const
{
	return pt.x >= left && pt.y >= top && pt.x < right && pt.y < bottom;
}

void ON_4iRect::OffsetRect(int x, int y)
{
	left += x;
	right += x;
	top += y;
	bottom += y;
}

void ON_4iRect::OffsetRect(const ON_2iVector& v)
{
	left += v.x;
	right += v.x;
	top += v.y;
	bottom += v.y;
}

void ON_4iRect::InflateRect(int x, int y)
{
	left -= x;
	top -= y;
	right += x;
	bottom += y;
}

void ON_4iRect::InflateRect(int l, int t, int r, int b)
{
	left -= l;
	top -= t;
	right += r;
	bottom += b;
}

void ON_4iRect::DeflateRect(int x, int y)
{
	left += x;
	top += y;
	right -= x;
	bottom -= y;
}

bool ON_4iRect::SubtractRect(const ON_4iRect* rect1, const ON_4iRect* rect2)
{
	if (rect1 == nullptr)
		return false;

	*this = *rect1;

	if (rect1->IsRectEmpty() || rect2 == nullptr || rect2->IsRectEmpty())
	{
		return true;
	}

	if (rect2->top <= rect1->top && rect2->bottom >= rect1->bottom)
	{
		if (left < rect2->right)
		{
			left = ON_Min(rect2->right, right);
		}
		if (right > rect2->left)
		{
			right = ON_Max(left, rect2->left);
		}
	}

	if (rect2->left <= rect1->left && rect2->right >= rect1->right)
	{
		if (top < rect2->bottom)
		{
			top = ON_Min(rect2->bottom, bottom);
		}
		if (bottom > rect2->top)
		{
			bottom = ON_Max(top, rect2->top);
		}
	}

	return true;
}

void ON_4iRect::NormalizeRect()
{
	int nTemp;
	if (left > right)
	{
		nTemp = left;
		left = right;
		right = nTemp;
	}
	if (top > bottom)
	{
		nTemp = top;
		top = bottom;
		bottom = nTemp;
	}
}

bool ON_4iRect::IsZero() const
{
  return (0 == left && 0 == top && 0 == right && 0 == bottom);
}

void ON_4iRect::SetZero() { *this = Zero; }


bool operator==(const ON_4iRect& lhs, const ON_4iRect& rhs)
{
  return (lhs.left == rhs.left
    && lhs.top == rhs.top 
    && lhs.right == rhs.right
    && lhs.bottom == rhs.bottom);
}

bool operator!=(const ON_4iRect& lhs, const ON_4iRect& rhs)
{
  return (lhs.left != rhs.left
    || lhs.top != rhs.top 
    || lhs.right != rhs.right
    || lhs.bottom != rhs.bottom);
}
