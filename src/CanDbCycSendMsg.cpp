#include <iostream>
#include <vector>
#include "../inc/json.hpp"
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "../inc/CanDbUtil.hpp"
#include <cctype>

using json = nlohmann::json;

void CanDbCycSendMsg_logMsg(std::string logMsg)
{
    std::cout << "CanDbCycSendMsg:" << logMsg << std::endl;
}

bool isInteger(const std::string& str) {
    // Empty string is not a valid integer
    if (str.empty()) return false;

    // Check each character to see if it's a valid digit
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false; // If any character is not a digit, it's not an integer
        }
    }
    return true; // All characters are digits
}

class CanDbCycSendMsg
{
    public:
    class CanMsg msginfo;
};

class CanDbCycSendMsg CanDbCycSendMsgPrv;

int CanDbCycSendMsg_parsearguments(int argc, char *argv[])
{
    if(CanDbUtil_CheckIfBusNameValid(argv[1]) == -1)
    {
        CanDbCycSendMsg_logMsg("Bus Name Not valid");
        return -1;
    }
    
    int ret;
    ret=CanDbUtil_CheckIfCanMsgNameValid(argv[1],argv[2], &CanDbCycSendMsgPrv.msginfo);
    if(ret == -1)
    {
        CanDbCycSendMsg_logMsg("Can Msg Name Not valid");
        return -1;
    }


    if(!isInteger(std::string(argv[3])))
    {
        CanDbCycSendMsg_logMsg("Can Cycle time is Not Valid");
        return -1;
    }

    return 1;
}

#define  CANDBCYCSENDMSG_ARGLEN      0x04u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanDbCycSendMsg_logMsg("Started");
    if((argc < CANDBCYCSENDMSG_ARGLEN) || (argc > CANDBCYCSENDMSG_ARGLEN))
    {
        CanDbCycSendMsg_logMsg("Arguments Mismatch");
        CanDbCycSendMsg_logMsg("Usage: CanDbCycSendMsg <DbCanBusName> <DbMsgName> <CycTimeMilliSeconds>");
        return 0;
    }
    else if(-1 == CanDbCycSendMsg_parsearguments(argc,argv))
    {
        CanDbCycSendMsg_logMsg("Arguments Syntax error");
    }
    else
    {
        //Pass the request to set the signal value.
        int cycleTime;
        cycleTime=std::stoi(std::string(argv[3]));
        std::cout<< "CycleTime " <<cycleTime << std::endl;
        // Write the logic to pack the msg and send the request.
    }
    
    return 0;
}

