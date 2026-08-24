/*
** EPITECH PROJECT, 2026
** Blackbox
** File description:
** Logger
*/

#pragma once

#include "LogLevel.hpp"
#include "SafeQueue.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

namespace blackbox
{
    class Logger
    {
    public:
        /**
        * @brief Get the singleton instance of the Logger.
        * @return The singleton instance of the Logger.
        **/
        static Logger &instance()
        {
            static Logger logger;
            return logger;
        }

        /**
        * @brief Initialize the logger.
        * @param filepath The path to the log file.
        * @param minLevel The minimum log level.
        **/
        void init(const std::string &filepath = "", LogLevel minLevel = LogLevel::INFO)
        {
            _minLevel = minLevel;
            if (!filepath.empty())
                _file.open(filepath, std::ios::out | std::ios::app);
            _running = true;
            _worker = std::thread(&Logger::workerLoop, this);
        }

        /**
        * @brief Stop the logger.
        **/
        void stop()
        {
            if (!_running)
                return;
            _running = false;
            _queue.stop();
            if (_worker.joinable())
                _worker.join();
            if (_file.is_open())
                _file.close();
        }

        /**
        * @brief Log a message.
        * @param level The log level.
        * @param file The file name.
        * @param line The line number.
        * @param msg The message to log.
        **/
        void log(LogLevel level, const std::string &file, int line, const std::string &msg)
        {
            if (level < _minLevel)
                return;

            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm tmBuffer;
            localtime_r(&now, &tmBuffer);

            std::ostringstream oss;
            oss << std::put_time(&tmBuffer, "%Y-%m-%d %H:%M:%S")
                << " [" << to_string(level) << "] "
                << "[" << file << ":" << line << "] "
                << msg;

            _queue.push(oss.str());
        }

    private:
        Logger() = default;
        ~Logger()
        {
            stop();
        }

        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

        /**
        * @brief The worker loop for processing log entries.
        **/
        void workerLoop()
        {
            while (true)
            {
                auto entry = _queue.pop();
                if (!entry.has_value())
                    break;

                std::cout << *entry << std::endl;
                if (_file.is_open())
                    _file << *entry << std::endl;
            }
        }

        SafeQueue<std::string> _queue;
        LogLevel _minLevel {LogLevel::INFO};
        std::ofstream _file;
        std::thread _worker;
        bool _running {false};
    };
}

/**
* @brief Logging macros for different log levels.
* @param level The log level.
* @param stream_msg The message to log, can be a stream expression.
**/
#define LOG(level, stream_msg) \
    do { \
        std::ostringstream _oss_macro; \
        _oss_macro << stream_msg; \
        blackbox::Logger::instance().log(level, __FILE__, __LINE__, _oss_macro.str()); \
    } while (0)

#define LOG_TRACE(msg) LOG(blackbox::LogLevel::TRACE, msg)
#define LOG_DEBUG(msg) LOG(blackbox::LogLevel::DEBUG, msg)
#define LOG_INFO(msg)  LOG(blackbox::LogLevel::INFO, msg)
#define LOG_WARN(msg)  LOG(blackbox::LogLevel::WARN, msg)
#define LOG_ERROR(msg) LOG(blackbox::LogLevel::ERROR, msg)
#define LOG_FATAL(msg) LOG(blackbox::LogLevel::FATAL, msg)