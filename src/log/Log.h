// Copyright 2020 yoshitake. All rights reserved.
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
        LOG_DEFAULT_CAPACITY_OF_RECORDS = 64,
        LOG_DEFAULT_CAPACITY_OF_EACH_RECORD = 64,
    };

public:
    /**
     * @brief SetCapacity set Log capacities
     *
     * Invoke SetCapacity to reserve all log memory.
     *
     * @param[in] capacityOfRecords size capacity of records.
     * @param[in] capacityOfEachRecord memory capacity of each record. this includes null string and prefix string(ex. "[TRACE] ")
     * @warn Invoke SetCapacity when Log size is zero
     */
    static void SetCapacity(int capacityOfRecords, int capacityOfEachRecord);
    static void SetLevel(int level);
    static int  Size();
    static int  CapacityOfRecords();
    static int  CapacityOfEachRecord();
    static bool GetLog(int index, std::string& log);
    static bool GetAllLogs(void(*fn)(int index, std::string& log));
    static void Fatal(const char *message);
    static void Error(const char *message);
    static void Warn(const char *message);
    static void Info(const char *message);
    static void Debug(const char *message);
    static void Trace(const char *message);
    static void Clean();
};
