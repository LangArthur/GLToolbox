#include "Logger.hpp"

namespace GLTool
{
    Logger::Logger() {
        // read config when there will be one
    }

    Logger::~Logger() { }

    void Logger::debug(const std::string &msg) {
        if (m_currentMode <= DEBUG) {
            std::cout << DEBUG_COLOR << DEBUG_MESSAGE << msg << END_OF_LINE;
        }
    }

    void Logger::info(const std::string &msg) {
        if (m_currentMode <= INFO) {
            std::cout << INFO_COLOR << INFO_MESSAGE << msg << END_OF_LINE;
        }
    }

    void Logger::warning(const std::string &msg) {
        if (m_currentMode <= WARNING) {
            std::cout << WARN_COLOR << WARN_MESSAGE << msg << END_OF_LINE;
        }
    }

    void Logger::error(const std::string &msg) {
        if (m_currentMode <= ERROR) {
            std::cout << ERROR_COLOR << ERROR_MESSAGE << msg << END_OF_LINE;
        }
    }

} // namespace GLTool

