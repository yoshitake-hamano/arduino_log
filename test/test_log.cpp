// Copyright 2018 yoshitake. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "unit_test.hpp"

#include <string>
#include <vector>
#include "log/Log.h"
#include "log/Log.cpp"

void test_trace()
{
    Log::Trace("abc");
    UT_ASSERT_INT(1, Log::Size());

    std::string log;
    UT_ASSERT_TRUE(Log::GetLog(0, log));
    UT_ASSERT_STRING("[TRACE] abc", log.c_str());
    Log::Clean();
}

void test_debug()
{
    Log::Debug("abc");
    UT_ASSERT_INT(1, Log::Size());

    std::string log;
    UT_ASSERT_TRUE(Log::GetLog(0, log));
    UT_ASSERT_STRING("[DEBUG] abc", log.c_str());
    Log::Clean();
}

void test_info()
{
    Log::Info("abc");
    std::string log;
    UT_ASSERT_TRUE(Log::GetLog(0, log));
    UT_ASSERT_STRING("[INFO ] abc", log.c_str());
    UT_ASSERT_INT(1, Log::Size());
    UT_ASSERT_FALSE(Log::GetLog(1, log));
    Log::Clean();
}

void test_error()
{
    Log::Error("abc");
    std::string log;
    UT_ASSERT_TRUE(Log::GetLog(0, log));
    UT_ASSERT_STRING("[ERROR] abc", log.c_str());
    UT_ASSERT_INT(1, Log::Size());
    UT_ASSERT_FALSE(Log::GetLog(1, log));
    Log::Clean();
}

void test_warn()
{
    Log::Warn("abc");
    std::string log;
    UT_ASSERT_TRUE(Log::GetLog(0, log));
    UT_ASSERT_STRING("[WARN ] abc", log.c_str());
    UT_ASSERT_INT(1, Log::Size());
    UT_ASSERT_FALSE(Log::GetLog(1, log));
    Log::Clean();
}

void test_fatal()
{
    Log::Fatal("abc");
    std::string log;
    UT_ASSERT_TRUE(Log::GetLog(0, log));
    UT_ASSERT_STRING("[FATAL] abc", log.c_str());
    UT_ASSERT_INT(1, Log::Size());
    UT_ASSERT_FALSE(Log::GetLog(1, log));
    Log::Clean();
}

void test_set_level()
{
    Log::SetLevel(Log::LOG_LEVEL_TRACE);
    Log::Trace("abc"); UT_ASSERT_INT(1, Log::Size());
    Log::Debug("abc"); UT_ASSERT_INT(2, Log::Size());
    Log::Info("abc");  UT_ASSERT_INT(3, Log::Size());
    Log::Warn("abc");  UT_ASSERT_INT(4, Log::Size());
    Log::Error("abc"); UT_ASSERT_INT(5, Log::Size());
    Log::Fatal("abc"); UT_ASSERT_INT(6, Log::Size());
    Log::Clean();

    Log::SetLevel(Log::LOG_LEVEL_DEBUG);
    Log::Trace("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Debug("abc"); UT_ASSERT_INT(1, Log::Size());
    Log::Info("abc");  UT_ASSERT_INT(2, Log::Size());
    Log::Warn("abc");  UT_ASSERT_INT(3, Log::Size());
    Log::Error("abc"); UT_ASSERT_INT(4, Log::Size());
    Log::Fatal("abc"); UT_ASSERT_INT(5, Log::Size());
    Log::Clean();

    Log::SetLevel(Log::LOG_LEVEL_INFO);
    Log::Trace("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Debug("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Info("abc");  UT_ASSERT_INT(1, Log::Size());
    Log::Warn("abc");  UT_ASSERT_INT(2, Log::Size());
    Log::Error("abc"); UT_ASSERT_INT(3, Log::Size());
    Log::Fatal("abc"); UT_ASSERT_INT(4, Log::Size());
    Log::Clean();

    Log::SetLevel(Log::LOG_LEVEL_WARN);
    Log::Trace("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Debug("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Info("abc");  UT_ASSERT_INT(0, Log::Size());
    Log::Warn("abc");  UT_ASSERT_INT(1, Log::Size());
    Log::Error("abc"); UT_ASSERT_INT(2, Log::Size());
    Log::Fatal("abc"); UT_ASSERT_INT(3, Log::Size());
    Log::Clean();

    Log::SetLevel(Log::LOG_LEVEL_ERROR);
    Log::Trace("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Debug("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Info("abc");  UT_ASSERT_INT(0, Log::Size());
    Log::Warn("abc");  UT_ASSERT_INT(0, Log::Size());
    Log::Error("abc"); UT_ASSERT_INT(1, Log::Size());
    Log::Fatal("abc"); UT_ASSERT_INT(2, Log::Size());
    Log::Clean();

    Log::SetLevel(Log::LOG_LEVEL_FATAL);
    Log::Trace("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Debug("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Info("abc");  UT_ASSERT_INT(0, Log::Size());
    Log::Warn("abc");  UT_ASSERT_INT(0, Log::Size());
    Log::Error("abc"); UT_ASSERT_INT(0, Log::Size());
    Log::Fatal("abc"); UT_ASSERT_INT(1, Log::Size());
    Log::Clean();
}

void test_full_log()
{
    for (int i=0; i<Log::CapacityOfRecords(); i++) {
        Log::Fatal("abc"); UT_ASSERT_INT(i+1, Log::Size());
    }
    for (int i=0; i<Log::CapacityOfRecords(); i++) {
        Log::Fatal("abc"); UT_ASSERT_INT(Log::CapacityOfRecords(), Log::Size());
    }
    Log::Clean();
}

void test_get_all_logs_fn(int index, std::string& log)
{
    static int expectedIndex = 0;
    UT_ASSERT_INT(expectedIndex, index);
    expectedIndex++;

    switch(index) {
    case 0:  UT_ASSERT_STRING("[INFO ] abc", log.c_str()); break;
    case 1:  UT_ASSERT_STRING("[WARN ] abc", log.c_str()); break;
    case 2:  UT_ASSERT_STRING("[ERROR] abc", log.c_str()); break;
    case 3:  UT_ASSERT_STRING("[FATAL] abc", log.c_str()); break;
    default: UT_ASSERT_TRUE(false); break;
    }
}

void test_get_all_logs()
{
    Log::Info("abc");
    Log::Warn("abc");
    Log::Error("abc");
    Log::Fatal("abc");
    UT_ASSERT_INT(4, Log::Size());
    Log::GetAllLogs(test_get_all_logs_fn);
    Log::Clean();
}

int main(int argc, char **argv)
{
    UT_RUN(test_trace);
    UT_RUN(test_debug);
    UT_RUN(test_info);
    UT_RUN(test_error);
    UT_RUN(test_warn);
    UT_RUN(test_fatal);
    UT_RUN(test_get_all_logs);
    UT_RUN(test_set_level);
    UT_RUN(test_full_log);
    return 0;
}
