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

#if !defined(ON_SAFE_FRAME_INC_)
#define ON_SAFE_FRAME_INC_

class ON_CLASS ON_SafeFrame
{
public:
  ON_SafeFrame();
  ON_SafeFrame(ON_XMLNode& model_node);
  ON_SafeFrame(const ON_SafeFrame&);
  virtual ~ON_SafeFrame();

  virtual const ON_SafeFrame& operator = (const ON_SafeFrame& sf);

  virtual bool operator == (const ON_SafeFrame& sf) const;
  virtual bool operator != (const ON_SafeFrame& sf) const;

  // Returns true if the safe frame is enabled.
  virtual bool Enabled(void) const;

  // Sets the safe frame on or off.
  virtual void SetEnabled(bool b);

  // Returns true if the safe frame is only displayed in perspective views.
  virtual bool PerspectiveOnly(void) const;

  // Sets whether or not the safe frame is only displayed in perspective views.
  virtual void SetPerspectiveOnly(bool b);

  // Returns true if the 4x3 field grid is on.
  virtual bool FieldGridOn(void) const;

  // Sets whether or not the 4x3 field grid is on.
  virtual void SetFieldGridOn(bool b);

  // Returns true if the live frame is on.
  virtual bool LiveFrameOn(void) const;

  // Sets whether or not the live frame is on.
  virtual void SetLiveFrameOn(bool b);

  // Returns true if the action frame is on.
  virtual bool ActionFrameOn(void) const;

  // Sets whether or not the action frame is on.
  virtual void SetActionFrameOn(bool b);

  // Returns true if the action frame X and Y scales are linked.
  virtual bool ActionFrameLinked(void) const;

  // Sets whether or not the action frame X and Y scales are linked.
  virtual void SetActionFrameLinked(bool b);

  // Returns the action frame X scale.
  virtual double ActionFrameXScale(void) const;

  // Sets the action frame X scale.
  // This value should be in the range 0..1 but it is not clamped.
  virtual void SetActionFrameXScale(double d);

  // Returns the action frame Y scale.
  virtual double ActionFrameYScale(void) const;

  // Sets the action frame Y scale.
  // This value should be in the range 0..1 but it is not clamped.
  virtual void SetActionFrameYScale(double d);

  // Returns true if the title frame is on.
  virtual bool TitleFrameOn(void) const;

  // Sets whether or not the title frame is on.
  virtual void SetTitleFrameOn(bool b);

  // Returns true if the title frame X and Y scales are linked.
  virtual bool TitleFrameLinked(void) const;

  // Sets whether or not the title frame X and Y scales are linked.
  virtual void SetTitleFrameLinked(bool b);

  // Returns the title frame X scale.
  virtual double TitleFrameXScale(void) const;

  // Sets the title frame X scale.
  // This value should be in the range 0..1 but it is not clamped.
  virtual void SetTitleFrameXScale(double d);

  // Returns the title frame Y scale.
  virtual double TitleFrameYScale(void) const;

  // Sets the title frame Y scale.
  // This value should be in the range 0..1 but it is not clamped.
  virtual void SetTitleFrameYScale(double d);

  // Emergency virtual function for future expansion.
  virtual void* EVF(const wchar_t* func, void* data);

  // For internal use only.
  virtual void OnInternalXmlChanged(const ON_SafeFrame*);

private:
  class CImpl;
  CImpl* m_impl;
};

#endif
