#ifndef LOGGER_CONSOLEOUTPUT_H
#define LOGGER_CONSOLEOUTPUT_H

namespace logger {

template <typename T = IOutput> class ConsoleOutput : public T {
public:
    template <typename... Args>
    ConsoleOutput(Args... args)
        : T(std::forward<Args>(args)...) {}

    void write(const std::string& str) const override {
        std::cout << str;
        T::write(str);
    }
};
} // namespace logger
#endif // LOGGER_CONSOLEOUTPUT_H
