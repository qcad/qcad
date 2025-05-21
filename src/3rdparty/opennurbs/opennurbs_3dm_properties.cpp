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

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmRevisionHistory
//

ON_3dmRevisionHistory::ON_3dmRevisionHistory() 
{
  memset( &m_create_time,    0, sizeof(m_create_time) );
  memset( &m_last_edit_time, 0, sizeof(m_last_edit_time) );
}

ON_3dmRevisionHistory ON_3dmRevisionHistory::FirstRevision()
{
  ON_3dmRevisionHistory first_revision;
  first_revision.NewRevision();
  return first_revision;
}

static int ON_CompareRevisionHistoryTime( const struct tm* time0, const struct tm* time1 )
{
  if ( 0 == time0 || 0 == time1 )
  {
    if ( 0 != time0 )
      return 1;
    if ( 0 != time1 )
      return -1;
    return 0;
  }

  if (time0->tm_year < time1->tm_year)
    return -1;
  if (time0->tm_year > time1->tm_year)
    return 1;

  if (time0->tm_mon < time1->tm_mon)
    return -1;
  if (time0->tm_mon > time1->tm_mon)
    return 1;

  if (time0->tm_mday < time1->tm_mday)
    return -1;
  if (time0->tm_mday > time1->tm_mday)
    return 1;

  if (time0->tm_hour < time1->tm_hour)
    return -1;
  if (time0->tm_hour > time1->tm_hour)
    return 1;

  if (time0->tm_min < time1->tm_min)
    return -1;
  if (time0->tm_min > time1->tm_min)
    return 1;

  if (time0->tm_sec < time1->tm_sec)
    return -1;
  if (time0->tm_sec > time1->tm_sec)
    return 1;

  return 0;
}

bool ON_3dmRevisionHistory::CreateTimeIsSet() const
{
  struct tm jan_1_1970;
  memset(&jan_1_1970,0,sizeof(jan_1_1970));
  jan_1_1970.tm_mday = 1;    /* day of the month - [1,31] */
  jan_1_1970.tm_year = 70;   /* years since 1900 */
  return ( ON_CompareRevisionHistoryTime(&jan_1_1970,&m_create_time) <= 0 );
}
/*
Returns:
  true 
    if m_last_edit_time is >= January 1, 1970
*/
bool ON_3dmRevisionHistory::LastEditedTimeIsSet() const
{
  struct tm jan_1_1970;
  memset(&jan_1_1970,0,sizeof(jan_1_1970));
  jan_1_1970.tm_mday = 1;    /* day of the month - [1,31] */
  jan_1_1970.tm_year = 70;   /* years since 1900 */
  return ( ON_CompareRevisionHistoryTime(&jan_1_1970,&m_last_edit_time) <= 0 );
}


bool ON_3dmRevisionHistory::IsEmpty() const
{
  if ( 0 == m_revision_count
       && !CreateTimeIsSet()
       && !LastEditedTimeIsSet()
       && m_sCreatedBy.IsEmpty()
       && m_sLastEditedBy.IsEmpty()
     )
  {
    return true;
  }
  return false;
}

bool ON_3dmRevisionHistory::IsValid() const
{
  return (     LastEditedTimeIsSet() 
            && ON_CompareRevisionHistoryTime(&m_create_time, &m_last_edit_time) <= 0
         );
}

int ON_3dmRevisionHistory::NewRevision()
{
  if ( 0 == m_revision_count )
    *this = ON_3dmRevisionHistory::Empty;

  struct tm current_time;
  memset(&current_time,0,sizeof(current_time));
  {
    time_t gmt = time(0);
    const struct tm* t = gmtime(&gmt);
    if ( t )
      current_time = *t;
  }
  m_last_edit_time = current_time;

#if defined(ON_RUNTIME_WIN)  
  // use Windows ::GetUserNameW() to get current user name
  wchar_t current_user[512];
  memset( current_user, 0, sizeof(current_user) );
  ULONG len = 510;
  if( !::GetUserNameW(current_user,&len) )
    current_user[0] = 0;
  m_sLastEditedBy = current_user;
#endif
#if defined(ON_RUNTIME_COCOA_AVAILABLE)
  m_sLastEditedBy = NSFullUserName().UTF8String;
#endif

  if ( m_revision_count <= 0 ) 
  {
    m_revision_count = 0;
    m_sCreatedBy = m_sLastEditedBy;
    m_create_time = current_time;
  };

  m_revision_count++;

  return m_revision_count;
}


bool ON_3dmRevisionHistory::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion( 1, 0 );
  if (rc) rc = file.WriteString( m_sCreatedBy );
  if (rc) rc = file.WriteTime( m_create_time );
  if (rc) rc = file.WriteString( m_sLastEditedBy );
  if (rc) rc = file.WriteTime(m_last_edit_time );
  if (rc) rc = file.WriteInt( m_revision_count );
  return rc;
}

bool ON_3dmRevisionHistory::Read( ON_BinaryArchive& file )
{
  *this = ON_3dmRevisionHistory::Empty;
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion( &major_version, &minor_version );
  if ( rc && major_version == 1 ) {
    rc = file.ReadString( m_sCreatedBy );
    if (rc) rc = file.ReadTime( m_create_time );
    if (rc) rc = file.ReadString( m_sLastEditedBy );
    if (rc) rc = file.ReadTime(m_last_edit_time );
    if (rc) rc = file.ReadInt( &m_revision_count );
  }
  return rc;
}

void ON_3dmRevisionHistory::Dump( ON_TextLog& dump ) const
{
  if ( IsEmpty() )
  {
    dump.Print("Empty revision history.\n");
  }
  else
  {
    const wchar_t* ws = static_cast< const wchar_t* >(m_sCreatedBy);
    if ( !ws ) ws = L"";
    dump.Print("Created by: %ls\n", ws );
    dump.Print("Created on: "); dump.PrintTime(m_create_time); dump.Print("\n");

  
    ws = static_cast< const wchar_t* >(m_sLastEditedBy);
    if ( !ws ) ws = L"";
    dump.Print("Last edited by: %ls\n", ws );
    dump.Print("Last edited on: "); dump.PrintTime(m_last_edit_time); dump.Print("\n");

    dump.Print("Revision count: %d\n",m_revision_count);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmNotes
//

const ON_3dmNotes ON_3dmNotes::Empty;

ON_3dmNotes::ON_3dmNotes()
: m_bVisible(false)
, m_bHTML(false)
, m_window_left(0)
, m_window_top(0)
, m_window_right(0)
, m_window_bottom(0)
, m_bLocked(false)
{}

ON_3dmNotes::~ON_3dmNotes()
{
  m_notes.Destroy();
}

bool ON_3dmNotes::IsValid() const
{
  return m_notes.IsEmpty() ? false : true;
}

bool ON_3dmNotes::IsEmpty() const
{
  return m_notes.IsEmpty();
}

bool ON_3dmNotes::Read( ON_BinaryArchive& file )
{
  *this = ON_3dmNotes::Empty;
  bool rc = false;
  for(;;)
  {
    int i;
    int major_version = 0;
    int minor_version = 0;
    if ( !file.Read3dmChunkVersion( &major_version, &minor_version ) )
      break;
    if ( 1 !=  major_version == 1 )
      break;
    i = m_bHTML;
    if ( !file.ReadInt( &i ) )
      break;
    m_bHTML = i ? true : false;
    if (!file.ReadString( m_notes ))
      break;
    i = m_bVisible;
    if (!file.ReadInt( &i ))
      break;
    m_bVisible = i ? true : false;
    if (!file.ReadInt( &m_window_left ))
      break;
    if (!file.ReadInt( &m_window_top ))
      break;
    if (!file.ReadInt( &m_window_right ))
      break;
    if (!file.ReadInt( &m_window_bottom ))
      break;

    if (minor_version >= 1)
    {
      //https://mcneel.myjetbrains.com/youtrack/issue/RH-74718/Lock-notes
      if (!file.ReadBool(&m_bLocked))
        break;
    }

    rc = true;
    break;
  }
  return rc;
}

bool ON_3dmNotes::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion(1,1);
  if ( rc ) rc = file.WriteInt( m_bHTML );
  if ( rc ) rc = file.WriteString( m_notes );
  if ( rc ) rc = file.WriteInt( m_bVisible );
  if ( rc ) rc = file.WriteInt( m_window_left );
  if ( rc ) rc = file.WriteInt( m_window_top );
  if ( rc ) rc = file.WriteInt( m_window_right );
  if ( rc ) rc = file.WriteInt( m_window_bottom );

  if (rc) rc = file.WriteBool(m_bLocked);

  return rc;
}

void ON_3dmNotes::Dump(ON_TextLog& dump) const
{
  const wchar_t* s = static_cast< const wchar_t* >(m_notes);
  if ( s )
    dump.PrintWrappedText(s);
  dump.Print("\n");
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmApplication
//

const ON_3dmApplication ON_3dmApplication::Empty;

ON_3dmApplication::ON_3dmApplication()
{
}

ON_3dmApplication::~ON_3dmApplication()
{
  m_application_name.Empty();
  m_application_URL.Empty();
  m_application_details.Empty();
}

void ON_3dmApplication::Dump( ON_TextLog& dump ) const
{
  const wchar_t* s = static_cast< const wchar_t* >(m_application_name);
  if ( s )
    dump.Print("Name: %ls\n",s);
  s = static_cast< const wchar_t* >(m_application_URL);
  if ( s )
    dump.Print("URL: %ls\n",s);
  s = static_cast< const wchar_t* >(m_application_details);
  if ( s )
    dump.Print("Details: %ls\n",s);
}

bool ON_3dmApplication::IsValid() const
{
  return m_application_name.IsEmpty() ? false : true;
}

bool ON_3dmApplication::IsEmpty() const
{
  return    m_application_name.IsEmpty() 
         && m_application_URL.IsEmpty()
         && m_application_details.IsEmpty();
}

bool ON_3dmApplication::Read( ON_BinaryArchive& file )
{
  int major_version = 0;
  int minor_version = 0;
  bool rc = file.Read3dmChunkVersion( &major_version, &minor_version );
  if (rc) rc = file.ReadString( m_application_name );
  if (rc) rc = file.ReadString( m_application_URL );
  if (rc) rc = file.ReadString( m_application_details );
  return rc;
}

bool ON_3dmApplication::Write( ON_BinaryArchive& file ) const
{
  bool rc = file.Write3dmChunkVersion( 1, 0 );
  if (rc) rc = file.WriteString( m_application_name );
  if (rc) rc = file.WriteString( m_application_URL );
  if (rc) rc = file.WriteString( m_application_details );
  return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// ON_3dmProperties
//

bool ON_3dmProperties::IsEmpty() const
{
  return    m_RevisionHistory.IsEmpty() 
         && m_PreviewImage.IsEmpty()
         && m_Notes.IsEmpty()
         && m_Application.IsEmpty()
         && m_3dmArchiveFullPathName.IsEmpty();
}

void ON_SetBinaryArchiveOpenNURBSVersion(ON_BinaryArchive& file, unsigned int value)
{
  if ( ON_VersionNumberIsValid(value) )
  {
    // can be yyyymmddn or a number from ON_VersionNumberConstruct().
    file.m_3dm_opennurbs_version = value;
  }
  else if ( ON_VersionNumberIsYearMonthDateFormat(file.Archive3dmVersion(),value) )
  {
    // can be yyyymmddn or a number from ON_VersionNumberConstruct().
    if ( 9 == (value%10) && value <= 201712319 )
    {
      // 9 marked debug versions.
      unsigned int n = file.Archive3dmVersion();
      if ( n >= 50 && 0 == (n%10) )
        n /= 10;
      if ( n > 0 && n < 9 )
        value = ((value/10)*10) + n;
    }
    file.m_3dm_opennurbs_version = value;
  }
  else
  {
    ON_ERROR("ON_SetBinaryArchiveOpenNURBSVersion - invalid opennurbs version");
    file.m_3dm_opennurbs_version = 0;
  }
}

bool ON_3dmProperties::Read(ON_BinaryArchive& file )
{
  *this = ON_3dmProperties::Empty;

  bool rc = true;

  unsigned int tcode;
  ON__INT64 value;

  for(;;) 
  {

    rc = file.BeginRead3dmBigChunk( &tcode, &value );
    if ( !rc )
      break;

    switch(tcode) 
    {

    case TCODE_PROPERTIES_OPENNURBS_VERSION:
      { 
        unsigned int opennurbs_version = 0;
        if ( value > 0 && value <= 0xFFFFFFFFll)
        {
          opennurbs_version = (unsigned int)((ON__UINT64)value);
        }

        if (    !ON_VersionNumberIsValid(opennurbs_version)
             && !ON_VersionNumberIsYearMonthDateFormat(file.Archive3dmVersion(),opennurbs_version)
           )
        {
          ON_ERROR("ON_3dmProperties::Read - TCODE_PROPERTIES_OPENNURBS_VERSION corrupt value");
          rc = false;
        }

        ON_SetBinaryArchiveOpenNURBSVersion(file,opennurbs_version);
      }
      break;

    case TCODE_PROPERTIES_AS_FILE_NAME:
      rc = file.ReadString(m_3dmArchiveFullPathName);
      break;
      
    case TCODE_PROPERTIES_REVISIONHISTORY: // file creation/revision information
      rc = m_RevisionHistory.Read(file);
      break;
      
    case TCODE_PROPERTIES_NOTES: // file notes
      rc = m_Notes.Read(file);
      break;
      
    case TCODE_PROPERTIES_PREVIEWIMAGE: // uncompressed preview image
      rc = m_PreviewImage.ReadUncompressed(file);
      break;
      
    case TCODE_PROPERTIES_COMPRESSED_PREVIEWIMAGE: // compressed preview image
      rc = m_PreviewImage.ReadCompressed(file);
      break;
      
    case TCODE_PROPERTIES_APPLICATION: // application that created 3dm file
      rc = m_Application.Read(file);
      break;
      
    default:
      // information added in future will be skipped by file.EndRead3dmChunk()
      break;
    }

    if ( !file.EndRead3dmChunk() )
      rc = false;

    if (!rc)
      break;

    if ( TCODE_ENDOFTABLE == tcode )
      break;
  }

  return rc;
}

bool ON_3dmProperties::Write(ON_BinaryArchive& file) const
{
  bool rc = true;

  // This short chunk identifies the version of OpenNURBS that was used to write this file.
  const unsigned int version_number_to_write = ON_BinaryArchive::ArchiveOpenNURBSVersionToWrite(file.Archive3dmVersion(), ON::Version());
  rc = file.BeginWrite3dmChunk(TCODE_PROPERTIES_OPENNURBS_VERSION, version_number_to_write);
  if (rc)
    rc = file.EndWrite3dmChunk();
  if (!rc)
    return false;

  // This chunk added November 5, 2015
  const ON_wString archive_full_path
    = file.ArchiveFullPath().IsEmpty()
    ? m_3dmArchiveFullPathName
    : file.ArchiveFullPath();
  if (rc && archive_full_path.IsNotEmpty())
  {
    if (!file.BeginWrite3dmChunk(TCODE_PROPERTIES_AS_FILE_NAME, 0))
      return false;
    rc = file.WriteString(file.ArchiveFullPath());
    if (!file.EndWrite3dmChunk())
      rc = false;
    if (!rc)
      return false;
  }


  // optional TCODE_PROPERTIES_REVISIONHISTORY chunk - file creation/revision information
  if ( rc && m_RevisionHistory.IsValid() ) {
    rc = file.BeginWrite3dmChunk(TCODE_PROPERTIES_REVISIONHISTORY,0);
    if ( rc ) {
      rc = m_RevisionHistory.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // optional TCODE_PROPERTIES_NOTES chunk - file notes
  if ( rc && m_Notes.IsValid() ) {
    rc = file.BeginWrite3dmChunk(TCODE_PROPERTIES_NOTES,0);
    if ( rc ) {
      rc = m_Notes.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  //// When merging Mac code please note that the
  //// TCODE_PROPERTIES_PREVIEWIMAGE chunk is OBSOLETE.
  //// DO NOT WRITE THEM IN V6 FILES.  If performance is an
  //// issue, we will address it some other way.

  // optional TCODE_PROPERTIES_COMPRESSED_PREVIEWIMAGE chunk - bitmap preview
  if ( rc && m_PreviewImage.IsValid() && file.Save3dmPreviewImage()) 
  {
    rc = file.BeginWrite3dmChunk(TCODE_PROPERTIES_COMPRESSED_PREVIEWIMAGE,0);
    if ( rc ) 
    {
      rc = m_PreviewImage.WriteCompressed(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // optional TCODE_PROPERTIES_APPLICATION chunk - application information
  if ( rc && m_Application.IsValid() ) 
  {
    rc = file.BeginWrite3dmChunk(TCODE_PROPERTIES_APPLICATION,0);
    if ( rc ) 
    {
      rc = m_Application.Write(file);
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  // required TCODE_ENDOFTABLE chunk - marks end of properties table
  if ( rc ) {
    rc = file.BeginWrite3dmChunk( TCODE_ENDOFTABLE, 0 );
    if ( rc ) {
      if ( !file.EndWrite3dmChunk() )
        rc = false;
    }
  }

  return rc;
}

void ON_3dmProperties::Dump( ON_TextLog& dump ) const
{
  dump.Print("Revision history:\n");
  dump.PushIndent();
  m_RevisionHistory.Dump(dump);
  dump.PopIndent();

  dump.Print("\n");
  dump.Print("Notes:\n");
  if ( m_Notes.m_notes.Length() > 0 ) {
    dump.PushIndent();
    m_Notes.Dump(dump);
    dump.PopIndent();
  }

  dump.Print("\n");
  dump.Print("Application information:\n");
  dump.PushIndent();
  m_Application.Dump(dump);
  dump.PopIndent();

  if ( m_PreviewImage.IsValid() ) {
    dump.Print("\n");
    dump.Print("Preview image:\n");
    dump.PushIndent();
    m_PreviewImage.Dump(dump);
    dump.PopIndent();
  }
}

