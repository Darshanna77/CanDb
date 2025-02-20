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

void logMsg (std::string logMsg)
{
    std::cout << "CanDbRegTxCbk:" << logMsg << std::endl;
}

int parse_arguments(int NoOfArg,std::string path)
{
    if((NoOfArg > 2))
    {
        logMsg("No of Arguments doesnot match");
        return -1 ;
    }
    
    return 1;
}
int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    logMsg(" Started");
    if((argc == 1) ||(-1 == parse_arguments(argc,argv[1])))
    {
        logMsg("No of Arguments doesnot match");
        return 0;
    }
    else
    {
        Filepath= argv[1];
        logMsg("Path:"+ Filepath);
    }
    
    return 0;
}
