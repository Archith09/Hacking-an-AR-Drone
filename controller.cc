#include "controller.h"

Controller::Controller() :
    sender(new Udpsender()),
    sending(false),
    seq_num(INIT_SEQ_NUM)
{}

Controller::~Controller()
{
    this->Land();
    delete sender;
}

void
Controller::Takeoff()
{
    std::string msg = this->ConstructCommandMsg(CMD_REF, {TAKEOFF});
    this->SendCommandMsg(msg, "Takeoff");
}

void
Controller::Hover()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {HOVE_MODE, NO_DIR, NO_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "Hover");
}

void
Controller::Land()
{
    std::string msg = this->ConstructCommandMsg(CMD_REF, {LANDING});
    this->SendCommandMsg(msg, "Land");
}

void
Controller::Front()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, NO_DIR, FRONT_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "Front");
}

void
Controller::Back()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, NO_DIR, BACK_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "Back");
}

void
Controller::Left()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, FRONT_DIR, NO_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "Left");
}

void
Controller::Right()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, BACK_DIR, NO_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "Right");
}

void
Controller::FrontLeft()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, FRONT_DIR, FRONT_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "FrontLeft");
}

void
Controller::FrontRight()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, BACK_DIR, FRONT_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "FrontRight");
}

void
Controller::BackLeft()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, FRONT_DIR, BACK_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "BackLeft");
}

void
Controller::BackRight()
{
    std::string msg = this->ConstructCommandMsg(CMD_PCMD,
        {PROC_MODE, BACK_DIR, BACK_DIR, NO_DIR, NO_DIR}, 1);
    msg += this->ConstructCommandMsg(CMD_REF, {TAKEOFF}, 2);
    this->SendCommandMsg(msg, "BackRight");
}

void
Controller::SendCommandMsg(const std::string& command_msg, const std::string& command_name)
{
    if (sending) {
        sending = false;
#ifdef DEBUG
        std::cout << "[DEBUG]Waiting for earlier thread to finish." << std::endl;
#endif
        send_worker.join();
#ifdef DEBUG
        std::cout << "[DEBUG]Earlier thread finished." << std::endl;
#endif
    }
    sending = true;
    cur_command = command_name;
    send_worker = std::thread(&Controller::SendCommandMsgWork, this, command_msg);
#ifdef DEBUG
    std::cout << "[DEBUG]Sending thread started." << std::endl;
#endif
}

void
Controller::SendCommandMsgWork(const std::string& msg)
{
#ifdef DEBUG
    int counter = 0;
#endif
    while (sending) {
        sender->SendMsg(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(SENDING_INTERVAL));
#ifdef DEBUG
        counter++;
        std::cout<<'+';
        if (counter % 2000 == 0) {
            std::cout << "[STATE]Send " << counter << " times. " << std::endl;
            std::cout << "[STATE]Current msg: " << msg << std::endl;
            std::cout << "[STATE]Current state: " << cur_command << std::endl;
        }
#endif
    }
}

std::string
Controller::ConstructCommandMsg(const std::string& command,
    const std::vector<std::string>& params, int flag_deprecated)
{
    int flag = seq_num++;
    std::string commandMsg = "AT*" + command + "=" + std::to_string(flag);
    for (auto str : params) {
        commandMsg += "," + str;
    }
    commandMsg += "\r";

#ifdef DEBUG
    std::cout << "[DEBUG]Construct Command Message: " << commandMsg << std::endl;
#endif
    
    return commandMsg;
}

void
Controller::PrintInstruction() const
{
    std::cout << "Current Command: " << cur_command << std::endl;
    std::cout << "Available Commands:" << std::endl;
    std::cout << "[0] Hover\n[1] Takeoff\n[2] Land\n[3] Front Direction\n[4] Back Direction\n[5] Left Direction\n[6] Right Direction\n[7] Front-Left Direction\n[8] Front-Right Direction\n[9] Back-Left Direction\n[10] Back-Right Direction\n";
    std::cout << "Please input command: ";
}

