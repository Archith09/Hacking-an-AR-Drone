#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "udpsender.h"
#include <vector>
#include <mutex>
#include <thread>

class Controller{
public:
    Controller();
    ~Controller();
    void PrintInstruction() const;
    void Hover();
    void Takeoff();
    void Land();
    void Front();
    void Back();
    void Left();
    void Right();
    void FrontLeft();
    void FrontRight();
    void BackLeft();
    void BackRight();
protected:
    void SendCommandMsg(const std::string& command_msg, const std::string& command_name);
    void SendCommandMsgWork(const std::string& msg);
    std::string ConstructCommandMsg(const std::string& command,
        const std::vector<std::string>& params,
        int flag_deprecated=1);
private:
    Udpsender *sender;
    std::string cur_command;
    volatile bool sending;
    std::thread send_worker;
    int seq_num;
};

#endif