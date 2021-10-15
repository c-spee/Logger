
#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <ostream>
#include <iostream>
#include <utility>
#include <strstream>

extern const char* getProcessName();
namespace logger
{
enum class Severity
{
    INFO,
    DEBUG,
    WARNING,
    ERR
};

class Log
{
private:
    class Logger
    {
    public:
        Logger(const char* processName, Severity severity);

        Logger(Logger const&) = delete;
        Logger& operator=(Logger const&) = delete;

//    Logger(Logger&& move) noexcept
//            : name_(std::exchange(move.name_, nullptr))
//    {
//        std::cout << __PRETTY_FUNCTION__ << " ---------- move" << std::endl;
//    }
//
//    Logger& operator=(Logger&& move) noexcept
//    {
//        name_ = std::exchange(move.name_, nullptr);
//        std::cout << __PRETTY_FUNCTION__ << " ---------- move" << std::endl;
//        return *this;
//    }

        template <typename T>
        Logger& operator<<(const T& value)
        {
            strStream << value;
            return *this;
        }

        Logger& operator<<(std::ostream& (*pf) (std::ostream&));

        ~Logger();

    private:
        static constexpr int bufferSize = 256;
        const char* name_;
        Severity severity_;
        std::strstream strStream;
        char streamBuffer[bufferSize];

        const char* getSeverityToString();
    };

public:
    Log()
    {
        processName_ = getProcessName();
    }

    Logger operator<<(const Severity svt)
    {
        if(NULL == processName_)
            processName_ = "..";
        return {processName_, svt};
    }
private:
    const char* processName_;
};

}

namespace
{
    auto info = logger::Severity::INFO;
    auto warning = logger::Severity::WARNING;
    auto err = logger::Severity::ERR;
    auto debug = logger::Severity::DEBUG;
}


#endif //LOGGER_LOGGER_H
