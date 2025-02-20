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
#include <mqueue.h>
#include <cstring>

#define RXQUEUE_NAME "/Reqmsg_queue"
#define TXQUEUE_NAME "/Respmsg_queue"

#define MAX_SIZE 1024

using json = nlohmann::json;

class CanDbMain
{
    public:
    class CanMsg msginfo;
};

class CanDbMain CanDbMainPrv;

void CanDbMain_logMsg(std::string logMsg)
{
    std::cout << "CanDbMain:" << logMsg << std::endl;
}

int CanDbMain_parsearguments(int argc, char *argv[])
{
    if(CanDbUtil_CheckIfBusNameValid(argv[1]) == -1)
    {
        CanDbMain_logMsg("Bus Name Not valid");
        return -1;
    }
    
    if(CanDbUtil_CheckIfCanMsgNameValid(argv[1],argv[2],&CanDbMainPrv.msginfo) == -1)
    {
        CanDbMain_logMsg("Can Msg Name Not valid");
        return -1;
    }
    
    return 1;
}

mqd_t mq;
mqd_t mq_response;

int CanDbMain_MsgQueueInit() {
    
    struct mq_attr attr;
    
    // Set up message queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    
    // Create and open message queue for receiving requests
    mq = mq_open(RXQUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == -1) {
        std::cerr << "Error opening message queue." << std::endl;
        return 1;
    }
    
    // Open message queue for sending the response
    mq_response = mq_open(TXQUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq_response == -1) {
        std::cerr << "Error opening message queue for response." << std::endl;
    } 
    
    return 0;
}

int CanDbMain_MsgQueueDeInit(void);
int CanDbMain_MsgQueueInit(void);
int CanDbMain_MsgQueueHandler(void);

int CanDbMain_MsgQueueDeInit() {
    // Close the message queue
    mq_close(mq);
    mq_unlink(RXQUEUE_NAME);
    mq_close(mq_response);
    mq_unlink(TXQUEUE_NAME);
    
    return 1;
}

int CanDbMain_MsgHandle(char *buffer,uint16_t bytes_received)
{
    
    _SeqNum seqnum= MAKE_WORD(buffer[4],buffer[3],buffer[2],buffer[1]);
    switch(buffer[0])
    {
        case CMDID_CANDBSETMSG:
        break;
    }
    return -1;
}

int CanDbMain_MsgQueueHandler(void) {
    char buffer[MAX_SIZE];
    while (true) {
        // Receive the request message from the client
        ssize_t bytes_received = mq_receive(mq, buffer, MAX_SIZE, NULL);
        if (bytes_received == -1) {
            std::cerr<< "Error receiving message" << std::endl;
            continue;
        }
        
        std::cout << "Server: RX Request:";
        for(int i=0;i< bytes_received;i++)
        std::cout<< " "<< (int)buffer[i]<< " ";
        std::cout<< std::endl;
        
        int RespLen;
        RespLen = sizeof(_CmdId) + sizeof(_SeqNum);
        
        if( CanDbMain_MsgHandle(buffer,bytes_received) != -1)
        {
            buffer[RespLen] = 0;
        }
        else
        {
            buffer[RespLen] = 0xff;
        }
        
        // Send the response back to the client
        if (mq_send(mq_response, buffer, RespLen +1, 0) == -1) {
            std::cerr << "Error sending response." << std::endl;
            } else {
            std::cout << "Server: TX Response:";
            for(int i=0;i< RespLen +1;i++)
            std::cout<< " "<<  (int) buffer[i]<< " ";
            std::cout<< std::endl;
        }
    }  
}


#define  CANDBMAIN_ARGLEN      0x03u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanDbMain_logMsg("Started");
    // if((argc < CANDBMAIN_ARGLEN) || (argc > CANDBMAIN_ARGLEN))
    // {
    // CanDbMain_logMsg("Arguments Mismatch");
    // CanDbMain_logMsg("Usage: CanDbMain <DbCanBusName> <DbMsgName>");
    // return 0;
    // }
    // else if(-1 == CanDbMain_parsearguments(argc,argv))
    // {
    // CanDbMain_logMsg("Arguments Syntax error");
    // }
    // else
    // {
    // //Start the main engine to process all requests.
    
    // }
    
    (void)CanDbMain_MsgQueueInit();
    (void)CanDbMain_MsgQueueHandler();
    (void)CanDbMain_MsgQueueDeInit();
    
    return 0;
}



