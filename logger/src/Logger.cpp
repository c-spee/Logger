#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip>

#include "Logger.h"

namespace logger {

Logger::Log Logger::operator<<(const Severity svt) {
    if (nullptr == m_processName) {
        m_processName = "..";
    }
    return {m_processName, m_domainName, svt, m_output};
}

Logger::Log::Log(const char* const processName, std::string const& domainName, Severity const sev,
                 const std::shared_ptr<IOutput>& output)
    : m_name(processName)
    , m_severity(sev)
    , m_output(output) {

    // Use chrono::system_clock to get ms
    using namespace std::chrono;
    constexpr uint32_t mspersec = 1000U;
    auto const now = system_clock::now();
    const long ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count()%mspersec;
    std::time_t const time = std::chrono::system_clock::to_time_t(now);
    constexpr int32_t numberOfDigits = 3;
    m_strStream <<  std::put_time(std::localtime(&time), "%F %T.") << std::setfill('0') << std::setw(numberOfDigits) << ms << " ";
    m_strStream << m_name << " <" << std::this_thread::get_id() << ">"
                << " " << domainName << getSeverityToString();
}

Logger::Log& Logger::Log::operator<<(std::ostream& (*pf)(std::ostream&)) {
    m_strStream << pf;
    return *this;
}

const char* Logger::Log::getSeverityToString() const noexcept {
    switch (m_severity) {
    case Severity::info:
        return " [INF] ";
    case Severity::warning:
        return " [WRN] ";
    case Severity::error:
        return " [ERR] ";
    case Severity::debug:
        return " [DBG] ";
    }
    return "";
}

Logger::Log::~Log() noexcept {
    //std::cout << __PRETTY_FUNCTION__ << " " << std::this_thread::get_id() << std::endl
    //std::cout << "~Log " << std::endl;;
    m_strStream << std::endl;
    m_output->write(m_strStream.str());
}
} // namespace logger
