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

void CanMapDbCh_logMsg(std::string logMsg)
{
    std::cout << "CanMapDbCh:" << logMsg << std::endl;
}

int CanMapDbCh_parsearguments(int argc, char *argv[])
{
    if(CanDbUtil_CheckIfBusNameValid(argv[1]) == -1)
    {
        CanMapDbCh_logMsg("Bus Name Not valid");
        return -1;
    }
    
    if(CanDbUtil_CheckIfCanDevUp(argv[2]) == -1)
    {
        CanMapDbCh_logMsg("Can Dev not up");
        return -1;
    }
    
    return 1;
}

#define  CANMAPDBCH_ARGLEN      0x03u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanMapDbCh_logMsg("Started");
    if((argc < CANMAPDBCH_ARGLEN) || (argc > CANMAPDBCH_ARGLEN))
    {
        CanMapDbCh_logMsg("Arguments Mismatch");
        CanMapDbCh_logMsg("Usage: CanMapDbCh <DbCanBusName> <DevName>");
        return 0;
    }
    else if(-1 == CanMapDbCh_parsearguments(argc,argv))
    {
        CanMapDbCh_logMsg("Arguments Syntax error");
    }
    else
    {
        //Pass the request to Map the Bus name with corresponding hardware.
        
    }
    
    return 0;
}

