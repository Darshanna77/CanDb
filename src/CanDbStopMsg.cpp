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

using json = nlohmann::json;

void CanDbStopMsg_logMsg(std::string logMsg)
{
    std::cout << "CanDbStopMsg:" << logMsg << std::endl;
}

class CanDbStop
{
    public:
    class CanMsg msginfo;
};

class CanDbStop CanDbStopPrv;
int CanDbStopMsg_parsearguments(int argc, char *argv[])
{
    if(CanDbUtil_CheckIfBusNameValid(argv[1]) == -1)
    {
        CanDbStopMsg_logMsg("Bus Name Not valid");
        return -1;
    }
    
    int ret;
    ret=CanDbUtil_CheckIfCanMsgNameValid(argv[1],argv[2], &CanDbStopPrv.msginfo);
    if(ret == -1)
    {
        CanDbStopMsg_logMsg("Can Msg Name Not valid");
        return -1;
    }
    
    return 1;
}

#define  CANDBSTOPMSG_ARGLEN      0x03u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanDbStopMsg_logMsg("Started");
    if((argc < CANDBSTOPMSG_ARGLEN) || (argc > CANDBSTOPMSG_ARGLEN))
    {
        CanDbStopMsg_logMsg("Arguments Mismatch");
        CanDbStopMsg_logMsg("Usage: CanDbStopMsg <DbCanBusName> <DbMsgName>");
        return 0;
    }
    else if(-1 == CanDbStopMsg_parsearguments(argc,argv))
    {
        CanDbStopMsg_logMsg("Arguments Syntax error");
    }
    else
    {
        //Pass the request to stop sending the corresponding msg.
        
    }
    
    return 0;
}

