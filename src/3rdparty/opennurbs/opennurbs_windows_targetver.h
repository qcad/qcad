/* $NoKeywords: $ */
/*
//
// Copyright (c) 1993-2013 Robert McNeel & Associates. All rights reserved.
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
*/

#if !defined(ON_WINDOWS_TARGETVER_INC_)
#define ON_WINDOWS_TARGETVER_INC_

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#if defined(_MSC_VER) && !defined(ON_CMAKE_BUILD)

#if _MSC_VER >= 1700
// Using Microsoft Visual Studio 2012 or later

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#if !defined(RHINO_SDK_WINVER_H_INCLUDED_)


#endif

#pragma ON_PRAGMA_WARNING_BEFORE_DIRTY_INCLUDE
#include <SDKDDKVer.h>
#pragma ON_PRAGMA_WARNING_AFTER_DIRTY_INCLUDE

#endif //  _MSC_VER >= 1700


#endif // defined(_MSC_VER)

#endif
