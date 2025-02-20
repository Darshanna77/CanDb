#include <iostream>
#include <vector>
#include "../inc/json.hpp"
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>


#include <sys/ipc.h>
#include <sys/shm.h>

using json = nlohmann::json;

void CanDbUtil_logMsg (std::string logMsg)
{
    std::cout << "CanDbUtil:" << logMsg << std::endl;
}


int CanDbUtil_CheckIfBusNameValid(std::string inpBusname)
{
    return 1;
}

int CanDbUtil_CheckIfCanMsgNameValid(std::string inpBusname, std::string inpCanMsgname, class CanMsg *outMsgInfo)
{
    return 1;
}

int CanDbUtil_CheckIfCanSigNameValid(std::string inpBusname, std::string inpCanMsgname,std::string inpCanSigname, class CanSig *outSigInfo)
{
    return 1;
}


int CanDbUtil_CheckIfCanSigValValid(std::string inpBusname, std::string inpCanMsgname,std::string inpCanSigname,std::string inpCanSigVal)
{
    return 1;
}

int CanDbUtil_CheckIfCanDevUp(std::string inpBusname)
{
     return 1;
}