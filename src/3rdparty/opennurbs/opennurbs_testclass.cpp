#include "opennurbs.h"
#include "opennurbs_testclass.h"

#if !defined(OPENNURBS_NO_STD_MUTEX)

ON__UINT64 ON_TestClass::CurrentCount()
{
  ON__UINT64 constructed_count = 0;
  ON__UINT64 current_count = 0;
  ON_TestClass::GetCurrentAndConstructedCount(constructed_count, current_count);
  return current_count;
}

ON__UINT64 ON_TestClass::ConstructedCount()
{
  ON__UINT64 constructed_count = 0;
  ON__UINT64 current_count = 0;
  ON_TestClass::GetCurrentAndConstructedCount(constructed_count, current_count);
  return constructed_count;
}

ON__UINT64 ON_TestClass::DestructedCount()
{
  ON__UINT64 constructed_count = 0;
  ON__UINT64 current_count = 0;
  ON_TestClass::GetCurrentAndConstructedCount(constructed_count, current_count);
  return constructed_count - current_count;
}

ON__UINT64 ON_TestClass::Internal_CounterHelper(
  int task, // 0 = construct, 1 = destruct, 2 = query
  ON__UINT64* constructed_count,
  ON__UINT64* current_count
)
{
  std::lock_guard<std::mutex> lock(ON_TestClass::internal_counter_mutex);
  ON__UINT64 rc = 0;
  if (0 == task)
  {
    ++ON_TestClass::internal_PopulationCounter;
    rc = ++ON_TestClass::internal_CtorSerialNumberGenerator;
  }
  else if (1 == task)
  {
    --ON_TestClass::internal_PopulationCounter;
  }
  else
  {
    *constructed_count = ON_TestClass::internal_CtorSerialNumberGenerator;
    *current_count = ON_TestClass::internal_PopulationCounter;
  }
  return rc;
}

void  ON_TestClass::GetCurrentAndConstructedCount(
  ON__UINT64& constructed_count,
  ON__UINT64& current_count
)
{
  ON_TestClass::Internal_CounterHelper(2, &constructed_count, &current_count);
}

ON_TestClass::ON_TestClass()
  : SerialNumber(ON_TestClass::Internal_CounterHelper(0,nullptr,nullptr))
  , CopiedFrom(0)
  , ConstructedAt((ON__UINT64)time(nullptr))
{}

ON_TestClass::~ON_TestClass()
{
  ON_TestClass::Internal_CounterHelper(1, nullptr, nullptr);
}

ON_TestClass::ON_TestClass(const ON_TestClass& src)
  : SerialNumber(ON_TestClass::Internal_CounterHelper(0,nullptr,nullptr))
  , CopiedFrom(src.SerialNumber)
  , ConstructedAt((ON__UINT64)time(nullptr))
  , m_string(src.Value())
{}

ON_TestClass& ON_TestClass::operator=(const ON_TestClass& src)
{
  if (this != &src)
  {
    SetValue(src.Value());
  }
  return *this;
}

const ON_wString ON_TestClass::Value() const
{
  std::lock_guard<std::mutex> lock(m_local_mutex);
  return m_string;
}

void ON_TestClass::SetValue(
  const ON_wString s
)
{
  std::lock_guard<std::mutex> lock(m_local_mutex);
  m_string = s;
}

void ON_TestClass::Dump(class ON_TextLog& text_log) const
{
  const ON_wString s(ToString());
  text_log.PrintString(s);
  text_log.PrintNewLine();
}

const ON_wString ON_TestClass::ToString() const
{
  const ON_wString v = Value();

  const ON_wString ymdhms = ON_wString::FromSecondsSinceJanuaryFirst1970(
    ConstructedAt,
    ON_DateFormat::YearMonthDay,
    ON_TimeFormat::HourMinuteSecond24,
    0,0,0
  );


  return ON_wString::FormatToString(
    L"ON_TestClass[%llu] @ %s \"%ls\"",
    SerialNumber, 
    static_cast<const wchar_t*>(ymdhms),
    static_cast<const wchar_t*>(v)
  );
}

#endif
