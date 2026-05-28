/*
 * Copyright 2024 Advanced Micro Devices Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VART_LOGGER_HPP
#define VART_LOGGER_HPP

#include <syslog.h>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include "vart_logger_types.hpp"

namespace vart {

// Below 'obj' object is created as static object and shared by all the
// components when header file is included
#define VART_LOG_REGISTER(x, y) obj.mod_register(x, y);

#define VART_LOG_ERR_OBJ(x, ...)                                            \
  obj.vart_logger_log_obj(LogLevel::LOG_LEVEL_ERROR, x, __FILE__, __func__, \
                          __LINE__, __VA_ARGS__)
#define VART_LOG_WARN_OBJ(x, ...)                                             \
  obj.vart_logger_log_obj(LogLevel::LOG_LEVEL_WARNING, x, __FILE__, __func__, \
                          __LINE__, __VA_ARGS__)
#define VART_LOG_FIXME_OBJ(x, ...)                                          \
  obj.vart_logger_log_obj(LogLevel::LOG_LEVEL_FIXME, x, __FILE__, __func__, \
                          __LINE__, __VA_ARGS__)
#define VART_LOG_INFO_OBJ(x, ...)                                          \
  obj.vart_logger_log_obj(LogLevel::LOG_LEVEL_INFO, x, __FILE__, __func__, \
                          __LINE__, __VA_ARGS__)
#define VART_LOG_DEBUG_OBJ(x, ...)                                          \
  obj.vart_logger_log_obj(LogLevel::LOG_LEVEL_DEBUG, x, __FILE__, __func__, \
                          __LINE__, __VA_ARGS__)

static const int sys_log_level[] = {0,          LOG_ERR,  LOG_WARNING,
                                    LOG_NOTICE, LOG_INFO, LOG_DEBUG};
/*!
  The logger module provides the logging support for VART modules.
  Supports logging to console, file, syslog.
 */

class Logger {
 public:
  /**
   * get_instance() -  Creates a logger() instance if not created earlier,
   *   else return an existing instance.
   *
   * @return
   *  Returns a logger instance
   *
   * Logger object when created reads the environment variable VART_CORE_DEBUG
   * to get and store log levels of each module and global log level. Default
   * module instance id is stored as -1. This id will be updated later when each
   * module instance registers with logger.
   *   Apart from that, logger reads the environment variable VART_LOG_FILE_PATH
   *   and if:
   *   1. VART_LOG_FILE_PATH is set to CONSOLE, logs messages to on screen
   *      console.
   *   2. VART_LOG_FILE_PATH is set to SYSLOG, appends log messages to syslog.
   *   3. VART_LOG_FILE_PATH is set to a file on disk, log messages to that
   *      file. If the file cannot be opened to log, defaults to syslog
   *      logging.
   */
  static Logger& get_instance() {
    static Logger log_obj;
    return log_obj;
  }

  /**
   * mod_register() - Registers a module with logger object
   *
   * @param modname
   *  Module name to register with logger
   *
   * @param need_id
   *  Flag describing the need for an id to be appended to module name during
   *  logging
   *
   * @return
   *  Returns logger context associated with a module instance.
   *
   *  If the module is already registered with the logger, its instance id is
   *  incremented, else a default instance id = 0 is assigned.
   *    Module instance log level is assigned from logger object's database or
   *  from global log level if per module log level is not provided by user.
   *    If need_id is set to false, module instance id is not appended to
   *  module's instance name. Components such as 'videoframe', 'memory' need
   *  to set this flag to false as there can be too many instances of those
   *  components in a single pipeline use case and can be be distinguished by
   *  their pointers. Components representing IP blocks can set this to true to
   *  distinguish IP instances.
   */
  std::shared_ptr<struct log_context> mod_register(const char* modname,
                                                   bool need_id);

  /**
   * vart_logger_log_obj() - Logs a module's message along with metadata like
   * filename, function name, line number, process id, thread id.
   *
   * @param LogLevel
   *  Logging level with which module logs a message
   *
   * @param ctx
   *  Module's logger context obtained with mod_register()
   *
   * @param filename
   *  Source code filename from which this logging is triggered
   *
   * @param func
   *  Source code function name
   *
   * @param line
   *  Source code line number
   *
   * @param fmt
   *  Format string passed for logging.
   */
  void vart_logger_log_obj(LogLevel,
                           std::shared_ptr<struct log_context> ctx,
                           const char* filename,
                           const char* func,
                           uint32_t line,
                           const char* fmt,
                           ...);

 private:
  Logger();
  ~Logger();
  Logger(const Logger&) = delete;
  void operator=(const Logger&) = delete;
  LogLevel global_log_level;
  LogLevel level;
  LogType type;
  std::mutex reg_mutex;
  std::mutex log_mutex;
  std::map<std::string, std::tuple<int16_t, uint16_t>> vart_components;
  std::chrono::high_resolution_clock::time_point logger_start_time;
  std::FILE* log_file;
};

static Logger& obj = Logger::get_instance();
}  // namespace vart
#endif
