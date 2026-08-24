/*
** EPITECH PROJECT, 2026
** Blackbox
** File description:
** main
*/

#include "blackbox/Logger.hpp"

#include <chrono>
#include <thread>

int main()
{
    blackbox::Logger::instance().init("log/blackbox.log", blackbox::LogLevel::TRACE);

    LOG_INFO("Main program started");
    LOG_TRACE("Debug trace: x value = " << 42);
    LOG_DEBUG("Connection active on port " << 8080);
    LOG_WARN("Warning: CPU load is " << 87.5 << "%");
    LOG_ERROR("Error detected: " << "File not found");
    LOG_FATAL("Critical module shutdown");

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return 0;
}