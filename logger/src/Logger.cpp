#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>

#include "Logger.h"
namespace logger
{
Log::Logger::Logger(const char* processName, Severity severity) :
    name_(processName),
    severity_(severity),
    strStream(&streamBuffer[0], bufferSize-2)
{
    memset(&streamBuffer[0], 0, bufferSize);

    constexpr int DATE_TIME_SIZE = 100;
    char s[DATE_TIME_SIZE];

    time_t t = time(NULL);
    struct tm * p = localtime(&t);
    strftime(s, DATE_TIME_SIZE, "%F %H:%M:%S", p);

    strStream << s << " " << name_ << " <" <<  std::this_thread::get_id() << ">" << getSeverityToString();
}

Log::Logger& Log::Logger::operator<<(std::ostream& (*pf) (std::ostream&))
{
        strStream << pf;
        return *this;
}

const char* Log::Logger::getSeverityToString()
{
    switch(severity_)
    {
        case Severity::INFO:
            return " [INF] ";
        case Severity::WARNING:
            return " [WRN] ";
        case Severity::ERR:
            return " [ERR] ";
        case Severity::DEBUG:
            return " [DBG] ";
    }
}

Log::Logger::~Logger()
{
        strStream << "\n";
        std::cout << strStream.str();
}
}

