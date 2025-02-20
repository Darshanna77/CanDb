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

#define SHM_KEY 1234   // Shared memory key
#define SEM_KEY 5678   // Semaphore key
#define SHM_SIZE 1024  // Shared memory size

using json = nlohmann::json;

void CanStart_logMsg(std::string logMsg)
{
    std::cout << "CanStart:" << logMsg << std::endl;
}

int CanStart_parsearguments(int argc, char *argv[])
{
    for(auto i=1;i<argc;i++)
    {
        if(CanDbUtil_CheckIfBusNameValid(argv[i]) == -1)
        {
            CanStart_logMsg("Bus Name Not valid """ + std::string(argv[i]) + """ ");
            return -1;
        }
    }
    return 1;
}

#define  CANSTART_ARGLEN      0x01u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanStart_logMsg("Started");
    if((argc <= CANSTART_ARGLEN))
    {
        CanStart_logMsg("Arguments Mismatch");
        CanStart_logMsg("Usage: CanStart <DbCanBusName1> <DbCanBusName2> <DbCanBusName3>... <DbCanBusName4>");
        return 0;
    }
    else if(-1 == CanStart_parsearguments(argc,argv))
    {
        CanStart_logMsg("Arguments Syntax error");
    }
    else
    {
        //Pass the request to start the mainDb evalauation.
            int shm_id = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }
    
    // Attach the shared memory segment
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }
    
    printf("Consumer: Read %s\n", shm_ptr);
    sleep(1);  
    
    shmdt(shm_ptr);

    }
    
    return 0;
}
