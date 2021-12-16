#ifndef LOGGER_FILEOUTPUT_H
#define LOGGER_FILEOUTPUT_H

#include <fstream>
#include <mutex>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

namespace {
std::mutex m_fileMutex{};
}

namespace logger {

template <typename T = IOutput> class FileOutput : public T {
public:
    template <typename... Args>
    FileOutput(const std::string& fileName, Args... args)
        : T(std::forward<Args>(args)...) {
        m_file.open(fileName, std::ios::app);
/*        if(SEM_FAILED == (m_semaphore = sem_open("logsem", O_CREAT, 0644, 1))) {
            std::cerr << "sem_open failed!";

        }*/
    }

    void write(const std::string& str) const override {
        T::write(str);
        std::lock_guard<std::mutex> fileLock{m_fileMutex};
        //sem_wait(m_semaphore);
        m_file.write(str.c_str(), str.length());
        //sem_post(m_semaphore);
    }

    ~FileOutput() { m_file.close(); }

private:
    mutable std::ofstream m_file;
    sem_t* m_semaphore{nullptr};
};
} // namespace logger
#endif // LOGGER_FILEOUTPUT_H
