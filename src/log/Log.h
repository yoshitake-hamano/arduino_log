// Copyright 2018 yoshitake. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#pragma once

#include <string>

class Log
{
public:
    enum {
        LOG_LEVEL_TRACE = 0,
        LOG_LEVEL_DEBUG,
        LOG_LEVEL_INFO,
        LOG_LEVEL_WARN,
        LOG_LEVEL_ERROR,
        LOG_LEVEL_FATAL,
        LOG_CAPACITY = 64,
    };

public:
    static void SetLevel(int level);
    static int  Size();
    static bool GetLog(int index, std::string& log);
    static void Fatal(const char *message);
    static void Error(const char *message);
    static void Warn(const char *message);
    static void Info(const char *message);
    static void Debug(const char *message);
    static void Trace(const char *message);
    static void Clean();
};
