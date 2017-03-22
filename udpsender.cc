#include "udpsender.h"

Udpsender::Udpsender() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket.");
    }

    server = gethostbyname(HOSTNAME);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host as %s\n", HOSTNAME);
        exit(0);
    }

    bzero((char*) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char*) server->h_addr,
        (char*) &serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(PORT);

    serverlen = sizeof(serveraddr);
}

void
Udpsender::SendMsg(const std::string& msg) {
#ifdef DEBUG
    //printf("[DEBUG]Sent: %s\n", msg.c_str());
#endif
    int n = sendto(sockfd, msg.c_str(), strlen(msg.c_str()), 0, (sockaddr*) &serveraddr, serverlen);
    if (n < 0) {
        error("ERROR in sendto");
    } else {
#ifdef DEBUG
        //printf("[DEBUG]Sent: %d\n", n);
#endif
    }
}

void
Udpsender::error(const std::string& msg) {
    perror(msg.c_str());
    exit(0);
}
