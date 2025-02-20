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

void CanRmDb_logMsg(std::string logMsg)
{
    std::cout << "CanRmDb:" << logMsg << std::endl;
}

#define  CANRMDB_ARGLEN      0x01u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanRmDb_logMsg("Started");
    if((argc < CANRMDB_ARGLEN) || (argc > CANRMDB_ARGLEN))
    {
        CanRmDb_logMsg("Arguments Mismatch");
        CanRmDb_logMsg("Usage: CanRmDb ");
        return 0;
    }
    else
    {
        //Pass the request to stop CAN Db engine.
        
    }
    
    return 0;
}

