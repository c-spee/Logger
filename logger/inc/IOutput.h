#ifndef LOGGER_IOUTPUT_H
#define LOGGER_IOUTPUT_H

#include <string>
#include <iostream>

namespace logger {
class IOutput {
public:
    IOutput() = default;
    IOutput(const IOutput&) = default;
    IOutput(IOutput&&) = default;
    IOutput& operator=(const IOutput&)& = default;
    IOutput& operator=(IOutput&&)& = default;
    virtual ~IOutput() noexcept = default;

    inline virtual void write(std::string const& str) const {static_cast<void>(str);}
};
} // namespace logger
#endif // LOGGER_IOUTPUT_H
