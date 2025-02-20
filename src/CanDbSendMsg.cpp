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
class CanDbSendMsg
{
    public:
    class CanMsg msginfo;
};

class CanDbSendMsg CanDbSendMsgPrv;
void CanDbSendMsg_logMsg(std::string logMsg)
{
    std::cout << "CanDbSendMsg:" << logMsg << std::endl;
}

int CanDbSendMsg_parsearguments(int argc, char *argv[])
{
    int ret;
    if(CanDbUtil_CheckIfBusNameValid(argv[1]) == -1)
    {
        CanDbSendMsg_logMsg("Bus Name Not valid");
        return -1;
    }

    ret=CanDbUtil_CheckIfCanMsgNameValid(argv[1],argv[2], &CanDbSendMsgPrv.msginfo);
    
    if(ret == -1)
    {
        CanDbSendMsg_logMsg("Can Msg Name Not valid");
        return -1;
    }
    
    return 1;
}

#define  CANDBSENDMSG_ARGLEN      0x03u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanDbSendMsg_logMsg("Started");
    if((argc < CANDBSENDMSG_ARGLEN) || (argc > CANDBSENDMSG_ARGLEN))
    {
        CanDbSendMsg_logMsg("Arguments Mismatch");
        CanDbSendMsg_logMsg("Usage: CanDbSendMsg <DbCanBusName> <DbMsgName>");
        return 0;
    }
    else if(-1 == CanDbSendMsg_parsearguments(argc,argv))
    {
        CanDbSendMsg_logMsg("Arguments Syntax error");
    }
    else
    {
        //Pass the request to set the signal value.
        
    }
    
    return 0;
}

