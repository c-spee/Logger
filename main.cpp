#include <Logger.h>
#include <ostream>

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

int main(int argc, char** argv)
{
    processName = argv[0];
    logger::Log log;
    log << info << "Hello! " << 10 << "! " << __FILE__ << "(" << __LINE__ << ")" << std::endl;
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
    return 0;
}
