/*
 * Copyright 2024 Advanced Micro Devices Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VART_LOGGER_TYPES_HPP
#define VART_LOGGER_TYPES_HPP

namespace vart {

#define VART_LOG_FILE_PATH "VART_LOG_FILE_PATH"
#define VART_CORE_DEBUG "VART_CORE_DEBUG_ENV"
#define VART_LOG_CONSOLE "CONSOLE"
#define VART_LOG_SYSLOG "SYSLOG"

/**
 * @enum LogLevel - Log levels supported.
 *
 * @var LOG_LEVEL_NONE
 *  None
 *
 * @var LOG_LEVEL_ERROR
 *  print ERROR logs
 *
 * @var LOG_LEVEL_WARNING
 *  Prints WARNING and ERROR logs
 *
 * @var LOG_LEVEL_FIXME
 *  Prints any TODO/FIXME logs
 *
 * @var LOG_LEVEL_INFO
 *  Prints INFO, WARNING & ERROR logs
 *
 * @var LOG_LEVEL_DEBUG
 *  Prints DEBUG, INFO, WARNING & ERROR logs
 */
enum class LogLevel {
  LOG_LEVEL_NONE = 0,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_FIXME,
  LOG_LEVEL_INFO,
  LOG_LEVEL_DEBUG,
};

/**
 * @enum LogType - Log types(sink) supported
 *
 * @var NO_LOG
 *  Do not log to any sink
 *
 * @var CONSOLE
 *  Logs to console
 *
 * @var FILE
 *  Logs to file specified with VART_LOG_FILE_PATH environment variable
 *
 * @var SYSLOG
 *  Logs using syslog mechanism
 */
enum LogType {
  NO_LOG = 0,
  CONSOLE,
  FILE,
  SYSLOG,
};

/**
 * @struct log_context
 *
 * @brief Context of a particular module instance
 *
 * @var id
 *  Instance id of the module
 *
 * @var log_level
 *  Logging level of the module
 *
 * @var mod_instance_name
 *  Module instance name
 */
struct log_context {
  int16_t id;
  uint16_t log_level;
  std::string mod_instance_name;
};

}  // namespace vart
#endif  // VART_LOGGER_TYPES_HPP
