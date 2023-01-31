#include "Logger.hpp"

namespace GLTools
{
    std::unique_ptr<Logger> Logger::getInstance() {
        static Logger logger;
        static std::unique_ptr<Logger> instance(&logger);
        return std::move(instance);
    }

    Logger::Logger() {
        // read config when there will be one
    }

    Logger::~Logger() { }

    void Logger::debug(const std::string &msg) {
        static auto logger = Logger::getInstance();
        if (logger->getMode() <= DEBUG) {
            logger->write(LOGGER_MODE::DEBUG, msg);
        }
    }

    void Logger::info(const std::string &msg) {
        static auto logger = Logger::getInstance();
        if (logger->getMode() <= INFO) {
            logger->write(LOGGER_MODE::INFO, msg);
        }
    }

    void Logger::warning(const std::string &msg) {
        static auto logger = Logger::getInstance();
        if (logger->getMode() <= WARNING) {
            logger->write(LOGGER_MODE::WARNING, msg);
        }
    }

    void Logger::error(const std::string &msg) {
        static auto logger = Logger::getInstance();
        if (logger->getMode() <= ERROR) {
            logger->write(LOGGER_MODE::ERROR, msg);
        }
    }

    void write(const LOGGER_MODE &mode, const std::string &msg) {
        switch (mode)
        {
        case DEBUG:
            std::cout << DEBUG_COLOR << DEBUG_MESSAGE << msg << END_OF_LINE;
            break;
        case INFO:
            std::cout << INFO_COLOR << INFO_MESSAGE << msg << END_OF_LINE;
            break;
        case WARNING:
            std::cout << WARN_COLOR << WARN_MESSAGE << msg << END_OF_LINE;
            break;
        case ERROR:
            std::cout << ERROR_COLOR << ERROR_MESSAGE << msg << END_OF_LINE;
            break;
        default:
            break;
        }
    }
} // namespace GLTools

