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
#include <memory>

// TODO:
// - make it in a thread
// - allow writing in a file
// - add config file
namespace GLTools {

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
            Logger(Logger &other) = delete;
            Logger(const Logger &other) = delete;
            Logger(Logger &&other) = delete;
            Logger(const Logger &&other) = delete;
            ~Logger();

            static std::unique_ptr<Logger> getInstance();  

            static void debug(const std::string &msg);
            static void info(const std::string &msg);
            static void warning(const std::string &msg);
            static void error(const std::string &msg);

            inline void setMode(const LOGGER_MODE &newMode) { m_currentMode = newMode; };
            inline LOGGER_MODE getMode() { return m_currentMode; };

            void write(const LOGGER_MODE &mode, const std::string &msg);

        private:
            Logger();

            static void staticWrite(const LOGGER_MODE &mode, const std::string &msg);

            LOGGER_MODE m_currentMode;
    };
}
