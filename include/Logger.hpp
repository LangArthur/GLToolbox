/**
 * @file Logger.hpp
 * @author Arthur Lang (arthur.lang.pro@gmail.Com)
 * @brief Declaration of Logger class
 * @date 2022-08-24
 */

#pragma once

#include <string>
#include <iostream>
#include <vector>

// TODO:
// - make it in a thread
// - allow writing in a file
// - add config file
namespace GLTool {

    enum LOGGER_MODE {
        DEBUG, INFO, WARNING, ERROR
    };

    constexpr auto DEBUG_MESSAGE = "[DEBUG]";
    constexpr auto INFO_MESSAGE = "[INFO]";
    constexpr auto WARN_MESSAGE = "[WARN]";
    constexpr auto ERROR_MESSAGE = "[ERROR]";

    constexpr auto DEBUG_COLOR = "\x1B[34mT"; // blue
    constexpr auto INFO_COLOR = "\x1B[32mT"; // green
    constexpr auto WARN_COLOR = "\x1B[33mT"; // yellow
    constexpr auto ERROR_COLOR = "\x1B[31mT"; // red

    constexpr auto END_OF_LINE = "\033[0m\n";


    class Logger {
        public:
            Logger();
            ~Logger();

            void debug(const std::string &msg);
            void info(const std::string &msg);
            void warning(const std::string &msg);
            void error(const std::string &msg);

            inline void setMode(const LOGGER_MODE &newMode) { m_currentMode = newMode; };

        private:
            LOGGER_MODE m_currentMode;

    };
}
