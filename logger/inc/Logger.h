
#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <memory>
#include <ostream>
#include <sstream>
#include <utility>

#include "IOutput.h"

extern const char* getProcessName();
namespace logger {
enum class Severity : uint8_t { info, debug, warning, error };

class Logger final {
private:
    class Log final {
    public:
        Log(const char* processName, std::string const& domainName, Severity sev,
            const std::shared_ptr<IOutput>& output);
        Log(Log const&) = delete;
        Log& operator=(Log const&) = delete;
        Log(Log&&) = delete;
        Log& operator=(Log&&) = delete;

        template <typename T> Log& operator<<(const T& value) {
            m_strStream << value;
            return *this;
        }

        Log& operator<<(std::ostream& (*pf)(std::ostream&));

        ~Log() noexcept;

    private:
        const char* m_name;
        Severity m_severity;
        std::stringstream m_strStream;
        const std::shared_ptr<IOutput>& m_output;

        const char* getSeverityToString() const noexcept;
    };

public:
    Logger(std::string const& domainName, const std::shared_ptr<IOutput>& output)
        : m_processName(getProcessName())
        , m_output(output)
        , m_domainName(domainName)
    {
    }

    Log operator<<(const Severity svt);

private:
    const char* m_processName;
    std::shared_ptr<IOutput> m_output;
    std::string m_domainName;
};

} // namespace logger


namespace {
auto info = logger::Severity::info;       // NOLINT
auto warning = logger::Severity::warning; // NOLINT
auto err = logger::Severity::error;         // NOLINT
auto debug = logger::Severity::debug;     // NOLINT
} // namespace

#endif // LOGGER_LOGGER_H
