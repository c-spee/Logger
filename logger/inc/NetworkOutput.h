#ifndef LOGGER_NETWORKOUTPUT_H
#define LOGGER_NETWORKOUTPUT_H

#include <fstream>
#include <memory.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace logger {
constexpr int m_loggingServicePort = 8989;

template <typename T = IOutput> class NetworkOutput : public T {
public:
    template <typename... Args>
    NetworkOutput(Args... args)
        : T(std::forward<Args>(args)...) {
        if ( (m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            std::cerr << "socket creation failed";
        }
        memset(&m_servaddr, 0, sizeof(m_servaddr));

        // Filling server information
        m_servaddr.sin_family = AF_INET;
        m_servaddr.sin_port = htons(m_loggingServicePort);
        m_servaddr.sin_addr.s_addr = INADDR_ANY;
    }

    void write(const std::string& str) const override {
        T::write(str);
        sendto(m_sockfd, str.data(), str.length(),
               0, (const struct sockaddr *) &m_servaddr,
               sizeof(m_servaddr));
    }

    ~NetworkOutput() {}

private:
    int m_sockfd;
    struct sockaddr_in m_servaddr{};
};
} // namespace logger
#endif // LOGGER_NETWORKOUTPUT_H
