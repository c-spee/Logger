#include <Logger.h>
#include <ostream>
#include <thread>
#include <iomanip>
#include "ConsoleOutput.h"
#include "FileOutput.h"
#include "NetworkOutput.h"

static char* processName;
static std::string processNameString;
const char* getProcessName()
{
    std::string processedNameString = processName;
    auto fileNameStart = processedNameString.find_last_of("/"); // unix
    processNameString = (fileNameStart == std::string::npos) ?
        processedNameString : processedNameString.substr(fileNameStart + 1);
    return processNameString.c_str();
}

static uint32_t nAllocations = 0;

void* operator new(size_t size)
{
    ++nAllocations;
    return malloc(size);
}

void* operator new[](size_t size)
{
    ++nAllocations;
    return malloc(size);
}

struct Person
{
    std::string name;
    uint32_t age;

    friend std::ostream &operator<<(std::ostream &os, const Person &person)
    {
        os << "name: " << person.name << " age: " << person.age;
        return os;
    }
};
/*
class ConsoleOutput : public logger::IOutput
{
public:
    ConsoleOutput(const logger::IOutput& output)
    : m_output(output)
    {
    }
    virtual void write(const std::string& str) const override{
        m_output.write(str);
        std::cout << str;
    }
private:
    const logger::IOutput& m_output;
};
*/

int main(int argc, char** argv)
{
    processName = argv[0];

    //logger::Logger log("TestModule", std::make_shared<ConsoleOutput>(logger::IOutput()));
    auto fileName = "//dev/shm/" + std::string(getProcessName()) + ".log";
    //auto output =  std::make_shared<logger::FileOutput<logger::ConsoleOutput<logger::IOutput>>>(fileName);
    //auto output =  std::make_shared<logger::FileOutput<logger::IOutput>>(fileName);
    auto output =  std::make_shared<logger::ConsoleOutput<>>();
    //auto output =  std::make_shared<logger::NetworkOutput<logger::FileOutput<logger::IOutput>>>(fileName);
    logger::Logger log("TestModule", output);
    log << info << "Hello World!";

    /*log << info << "Hello! " << 10 << "! " << __FILE__ << "(" << __LINE__ << ")" << std::endl;
    log << err << "Error:" << __FILE__ << "(" << __LINE__ << ") " << std::hex << 255;
    log << debug << "Some debugging info...";
    log << warning << "Some warnings to not to...";
    log << info;
    int x;
    float f = .99;
    log << info << x << " " << f;
    Person maria{"Maria", 23};
    log << info << maria;
    log << info << (1==1?10:20) << " " << std::boolalpha << ("azi" == "ieri");
    log << info << "I'm going to print something which should be more than 255 characters"
                   ", to see actually what happens when my log message is longer than the"
                   " buffer allocated for the strstream used by logger. strstream is anyway "
                   "marked as deprecated, but for the sake of speed is the main tool to "
                   "allocate on the stack instead of heap." << std::endl;
    log << info << "It's truncating? ";
    log << info << "Allocations: " << nAllocations << std::endl;
    //log << info << "commiting suicide ...." << 1/0;
    //std::cout << 1/0;
     */
    std::thread t0([&](){ for(int count = 100000; count --> 0;) log << info << "thread "
                << 0 << " "
                << std::setfill('0') << std::setw(3) << count
                << " " << std::this_thread::get_id(); });

    constexpr int loopCounter = 10;

    std::thread t1([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 1; });
    std::thread t2([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 2 << " " << std::this_thread::get_id(); });
    std::thread t3([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 3; });
    std::thread t4([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 4 << " " << std::this_thread::get_id(); });
    std::thread t5([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 5; });
    std::thread t6([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 6 << " " << std::this_thread::get_id(); });
    std::thread t7([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 7; });
    std::thread t8([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 8 << " " << std::this_thread::get_id(); });
    std::thread t9([&](){ for(int count = loopCounter; count --> 0;) log << info << "thread " << 9; });
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    log << info << " sizeof float: " << sizeof(float);
    log << info << " sizeof double: " << sizeof(double);
    log << info << " sizeof long double: " << sizeof(long double);
    return 0;
}
