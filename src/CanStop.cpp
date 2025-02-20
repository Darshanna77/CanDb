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

void CanStop_logMsg(std::string logMsg)
{
    std::cout << "CanStop:" << logMsg << std::endl;
}

#define  CANSTOP_ARGLEN      0x01u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanStop_logMsg("Started");
    if((argc < CANSTOP_ARGLEN) || (argc > CANSTOP_ARGLEN))
    {
        CanStop_logMsg("Arguments Mismatch");
        CanStop_logMsg("Usage: CanStop ");
        return 0;
    }
    else
    {
        //Pass the request to stop CAN Db engine.
        
    }
    
    return 0;
}

