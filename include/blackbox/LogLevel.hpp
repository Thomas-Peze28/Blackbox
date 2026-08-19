/*
** EPITECH PROJECT, 2026
** Blackbox
** File description:
** LogLevel
*/

#pragma once

#include <string_view>

namespace blackbox
{

    /**
    * @brief The level of logging.
    **/
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    /**
    * @brief Convert a LogLevel to its string representation.
    * @param level The LogLevel to convert.
    * @return A string_view representing the LogLevel.
    */
    constexpr std::string_view to_string(LogLevel level) noexcept
    {
        switch (level)
        {
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
        }
    }

}