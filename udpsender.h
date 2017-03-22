#ifndef _UDPSENDER_H_
#define _UDPSENDER_H_

#include "defs.h"

class Udpsender{
public:
    Udpsender();
    void SendMsg(const std::string& msg);
protected:
    void error(const std::string& msg);
private:
    sockaddr_in serveraddr;
    hostent *server;
    int sockfd;
    int serverlen;
};

#endif