// Copyright 2020 yoshitake. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.

#include "Log.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <iostream>
#endif

static bool log_initialized             = false;
static int  log_size                    = 0;
static int  log_capacity_of_records     = 0;
static int  log_capacity_of_each_record = 0;
static int  log_next_write_index        = 0;
static int  log_level                   = Log::LOG_LEVEL_TRACE;

static std::vector<std::string> logs;

static void add(const std::string& message)
{
    if (!log_initialized) {
        Log::SetCapacity(Log::LOG_DEFAULT_CAPACITY_OF_RECORDS,
                         Log::LOG_DEFAULT_CAPACITY_OF_EACH_RECORD);
    }

    std::string m = message.substr(0, log_capacity_of_each_record - 1);
#ifdef ARDUINO
    Serial.println(message.c_str());
#else
//    std::cout << "Log::add() add \"" << m << "\"" << std::endl;
#endif

    logs[log_next_write_index] = m;

    ++log_next_write_index;
    log_next_write_index = log_next_write_index % log_capacity_of_records;

    if (log_size < log_capacity_of_records) {
        ++log_size;
    }
}

void Log::SetCapacity(int capacityOfRecords, int capacityOfEachRecord)
{
    if (log_size != 0) {
#ifdef ARDUINO
#else
        assert(log_size == 0);
#endif
        return;
    }
    logs.clear();
    logs.reserve(capacityOfRecords);
    log_capacity_of_records = capacityOfRecords;
    log_capacity_of_each_record = capacityOfEachRecord;
    for (int i=0; i<capacityOfRecords; i++) {
        std::string s;
        s.reserve(capacityOfEachRecord);
        logs.push_back(s);
    }
    log_initialized = true;
}

void Log::SetLevel(int level)
{
    log_level = level;
}

int Log::Size()
{
    return log_size;
}

int Log::CapacityOfRecords()
{
    return log_capacity_of_records;
}

int Log::CapacityOfEachRecord()
{
    return log_capacity_of_each_record;
}

bool Log::GetAllLogs(void (*fn)(int index, std::string& log))
{
    int i = 0;
    if (log_next_write_index == log_size) {
        // log_size  != log_capacity_of_records
        // log_start == 0
        i = 0;
    } else {
        // log_size  == log_capacity_of_records
        // log_start == log_next_write_index
        i = log_next_write_index;
    }

    for (int index=0;; index++) {
        fn(index, logs[i]);

        i++;
        i = i % log_capacity_of_records;
        if (i == log_next_write_index) {
            break;
        }
    }
    return true;
}

bool Log::GetLog(int index, std::string& log)
{
    if (index < 0 || log_size <= index) {
        return false;
    }

    if (log_next_write_index == log_size) {
        // log_size  != log_capacity_of_records
        // log_start == 0
        log = logs[index];
        return true;
    }

    // log_size  == log_capacity_of_records
    // log_start == log_next_write_index
    int i = (log_next_write_index + index) % log_capacity_of_records;
    log = logs[i];
    return true;
}

void Log::Fatal(const char *message)
{
    if (log_level > LOG_LEVEL_FATAL) {
        return;
    }
    add(std::string("[FATAL] ") + message);
}

void Log::Error(const char *message)
{
    if (log_level > LOG_LEVEL_ERROR) {
        return;
    }
    add(std::string("[ERROR] ") + message);
}

void Log::Warn(const char *message)
{
    if (log_level > LOG_LEVEL_WARN) {
        return;
    }
    add(std::string("[WARN ] ") + message);
}

void Log::Info(const char *message)
{
    if (log_level > LOG_LEVEL_INFO) {
        return;
    }
    add(std::string("[INFO ] ") + message);
}

void Log::Debug(const char *message)
{
    if (log_level > LOG_LEVEL_DEBUG) {
        return;
    }
    add(std::string("[DEBUG] ") + message);
}

void Log::Trace(const char *message)
{
    if (log_level > LOG_LEVEL_TRACE) {
        return;
    }
    add(std::string("[TRACE] ") + message);
}

void Log::Clean()
{
    log_size = 0;
    log_next_write_index = 0;
    log_initialized = false;
}
