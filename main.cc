#include "controller.h"
#include <limits>

void TakeCommand(Controller *con) {
    con->PrintInstruction();
    int command;
    std::cin >> command;
    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    switch (command) {
        case 0:
            con->Hover();
            break;
        case 1:
            con->Takeoff();
            break;
        case 2:
            con->Land();
            break;
        case 3:
            con->Front();
            break;
        case 4:
            con->Back();
            break;
        case 5:
            con->Left();
            break;
        case 6:
            con->Right();
            break;
        case 7:
            con->FrontLeft();
            break;
        case 8:
            con->FrontRight();
            break;
        case 9:
            con->BackLeft();
            break;
        case 10:
            con->BackRight();
            break;
        default:
            break;
    }
}

int main() {
    Controller *controller = new Controller();
    while (true) {
        TakeCommand(controller);
    }
    return 0;
}