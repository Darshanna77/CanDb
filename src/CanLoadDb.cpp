#include <iostream>
#include <vector>
#include "../inc/json.hpp"
#include "../inc/CanDbUtil.hpp"
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>

using json = nlohmann::json;

// ...


void logMsg (std::string logMsg)
{
    std::cout << "CanDbLoad:" << logMsg << std::endl;
}

int parse_arguments(int NoOfArg,std::string path)
{
    if((NoOfArg > 2))
    {
        logMsg("No of Arguments doesnot match");
        return -1 ;
    }
    
    size_t dotPos = path.rfind('.');
    
    // If no dot is found or the dot is at the start, it's not a valid extension
    if (dotPos == std::string::npos || dotPos == 0) {
        logMsg("Argument shall be file path");
        return -1;
    }
    
    // Extract the extension from the filename
    std::string fileExt = path.substr(dotPos + 1);
    
    // Compare with the given extension (case insensitive)
    if(fileExt != "arxml")
    {
        logMsg("File extension shall be arxml");
        return -1 ;
    }
    return 1;
}
#define SHM_KEY 1234   // Shared memory key
#define SEM_KEY 5678   // Semaphore key
#define SHM_SIZE 1024  // Shared memory size

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
    
    
    logMsg("Database Extract Started");
    int result = system(" python3 ArxmlDataExtractor/arxml_data_extractor  -c ./cfg/config.yaml -i ./cfg/test.arxml -o ./build/gen/out.json");
    
    if(result == -1)
    {
        logMsg("Database Extract Failed");
    }
    else
    {
        logMsg("Database Extract Completed");
    }
    
    
    
    std::ifstream f("./build/gen/out.json");
    json data = json::parse(f);
    //std::cout << data<<std::endl;
    
    
    // auto ecupath = data.at("ECU/EcuName");
    // auto it_three = data.find("three");
    
    // std::cout << "ECU:" << (ecupath != data.end()) << '\n';
    // std::cout << "ECU:" << data["ECU"]["ConnectorsSpec"]["ConnectorName"] << '\n';
    
    
    // // Create some CanSig objects
    // CanSig sig1("Signal1", 8, 0, 0xFF, 0);
    // CanSig sig2("Signal2", 16, 1, 0xFFFF, 1);
    
    // // Put them in a vector
    // std::vector<CanSig> sigs = {sig1, sig2};
    
    // // Create a CanMsg object with the CanSig vector
    // CanMsg msg("Message1", "Data", 1000, 8, 0x123, sigs);
    
    // // Create a Bus object with the CanMsg vector
    // std::vector<CanMsg> msgs = {msg};
    // std::vector<CanMsg> msgs1 = {msg};
    // Bus bus("CAN Bus", "HighSpeed", 500000, 1000000, msgs,msgs1);
    
    // Just to print the Bus Name to verify the object creation
    // std::cout << "Bus Name: " << bus.Name << std::endl;
    
    // }
    
    // Create shared memory segment
    int shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
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

    
    // Write data to the shared memory
    const char* message = "Hello from shared memory darshan !";
    strcpy(shm_ptr, message);
    
   // sleep(100);  
    
    shmdt(shm_ptr);
    
    return 0;
}
