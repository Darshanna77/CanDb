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

#include <iostream>
#include <mqueue.h>
#include <cstring>
#include <unistd.h>

using json = nlohmann::json;

void CanDbSetMsg_logMsg(std::string logMsg)
{
    std::cout << "CanDbSetMsg:" << logMsg << std::endl;
}

class CanDbSetMsg
{
    public:
    uint8_t busid;
    class CanMsg msginfo;
    class CanSig siginfo;
    uint64_t inpsigval;
};

class CanDbSetMsg CanDbSetMsgPrv;

int CanDbSetMsg_parsearguments(int argc, char *argv[])
{
    CanDbSetMsgPrv.busid= CanDbUtil_CheckIfBusNameValid(argv[1]);
    if(CanDbSetMsgPrv.busid == -1)
    {
        CanDbSetMsg_logMsg("Bus Name Not valid");
        return -1;
    }
    int ret;
    ret=CanDbUtil_CheckIfCanMsgNameValid(argv[1],argv[2], &CanDbSetMsgPrv.msginfo);
    if(ret == -1)
    {
        CanDbSetMsg_logMsg("Can Msg Name Not valid");
        return -1;
    }
    
     ret =CanDbUtil_CheckIfCanSigNameValid(argv[1],argv[2],argv[3],&CanDbSetMsgPrv.siginfo);
    
    if(ret == -1)
    {
        CanDbSetMsg_logMsg("Can Signal Name Not valid");
        return -1;
    }
    
    if((std::string(argv[4]) != "RAW") && ((std::string(argv[4]) != "SIGVAL")))
    {
        CanDbSetMsg_logMsg("Signal Type Not valid");
        return -1;
    }
    
    if(std::string(argv[4]) == "RAW")
    {
        //Convert argv[5] to integer value 
        CanDbSetMsg_logMsg("Signal Type RAW");
        CanDbSetMsgPrv.inpsigval = std::stoi(argv[5]);
        return 1;
    }
    else
    {
        if(CanDbUtil_CheckIfCanSigValValid(argv[1],argv[2],argv[3],argv[4])== -1)
        {
            
        }
        else
        {
            CanDbSetMsg_logMsg("Signal Value """+ std::string(argv[4]) + """ Not Valid");
        }
        // use argv[5] as a string.
    }
    
    return 1;
}

#define TXQUEUE_NAME "/Reqmsg_queue"
#define RXQUEUE_NAME "/Respmsg_queue"

#define MAX_SIZE 1024

mqd_t mq;
mqd_t mq_response;

char buffer[MAX_SIZE];

int CanDbSetMsg_MsgQueInit(void)
{
    // Open the message queue for sending the request
    mq = mq_open(TXQUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        std::cerr << "Error opening message queue." << std::endl;
        return 1;
    }
    
    // Open the message queue for receiving the response
    mq_response = mq_open(RXQUEUE_NAME, O_RDONLY);
    if (mq_response == -1) {
        std::cerr << "Error opening message queue for response." << std::endl;
        return 1;
    }
    return 1;
}

int CanDbSetMsg_SendtoMsgQue(char *inpData,uint8_t inplen)
{
    // char *SendBuffer= NULL;
    
    // // Request memory for the variable
    // // using new operator
    // SendBuffer = new char[inplen + 10 ];
    // if (!SendBuffer)
    // std::cout << "allocation of memory failed\n";
    // else {
        
    // }
    
    // class Msg MsgBuf{CMDID_CANDBSETMSG};
    // uint8_t cnt{0};
    // MsgBuf.SeqNum=15;
    // MsgBuf.len=5;
    
    // SendBuffer[cnt++]=MsgBuf.CmdId;
    
    // SendBuffer[cnt++]=GET_BYTE_3(MsgBuf.SeqNum);
    // SendBuffer[cnt++]=GET_BYTE_2(MsgBuf.SeqNum);
    // SendBuffer[cnt++]=GET_BYTE_1(MsgBuf.SeqNum);
    // SendBuffer[cnt++]=GET_BYTE_0(MsgBuf.SeqNum);
    
    // SendBuffer[cnt++]=inplen; // + sizeof(MsgBuf.len) + sizeof(MsgBuf.SeqNum) + sizeof(MsgBuf.CmdId) ;
    
    // for(int i=0;i< inplen;i++)
    // SendBuffer[cnt++]=inpData[i];
    
    // Send a request to the server
    std::cout << "Client:Request:CMDID_CANDBSETMSG :";
    for(int i=0;i< inplen;i++)
        std::cout<< " "<< (int)inpData[i]<< " ";
    std::cout<< std::endl;
    
    if (mq_send(mq,inpData,inplen, 0) == -1) {
        std::cerr << "Error sending request." << std::endl;
        return 1;
    }
    
    // Receive the response from the server
    ssize_t bytes_received = mq_receive(mq_response, inpData, MAX_SIZE, NULL);
    if (bytes_received == -1) {
        std::cerr << "Error receiving response." << std::endl;
        return 1;
    }
    // Response in client
    std::cout << "Client: Response:CMDID_CANDBSETMSG";
    for(int i=0;i< bytes_received;i++)
    std::cout<< " "<<  (int)inpData[i]<< " ";
    std::cout<< std::endl;
    
    return 1;
}

int CanDbSetMsg_MsgQueDeInit(void)
{
    // Close the message queues
    mq_close(mq);
    mq_close(mq_response);
    
    return 0;
}


#define  CANDBSETMSG_ARGLEN      0x06u

int main(int argc, char *argv[]) {
    // argc is the number of arguments, including the program name
    std::string Filepath="";
    CanDbSetMsg_logMsg("Started");
    if((argc < CANDBSETMSG_ARGLEN) || (argc > CANDBSETMSG_ARGLEN))
    {
        CanDbSetMsg_logMsg("Arguments Mismatch");
        CanDbSetMsg_logMsg("Usage: CanDbSetMsg	<DbCanBusName> <DbMsgName>	<DbSigName> <DbSigValType=RAW/SIGVAL> <DbSigVal>");
        return 0;
    }
    else if(-1 == CanDbSetMsg_parsearguments(argc,argv))
    {
        CanDbSetMsg_logMsg("Arguments Syntax error");
    }
    else
    {
        //Pass the request to set the signal value.
        
    }
    
    CanDbSetMsg_MsgQueInit();
    
    char setmsgbuff[100];
    int cnt=0;
    uint64_t sigval[8]={0};
    setmsgbuff[cnt++]= CanDbSetMsgPrv.busid;
    CanDbSetMsgPrv.msginfo.CanMsgId=0x123456;
    setmsgbuff[cnt++]= GET_BYTE_3(CanDbSetMsgPrv.msginfo.CanMsgId);
    setmsgbuff[cnt++]= GET_BYTE_2(CanDbSetMsgPrv.msginfo.CanMsgId);
    setmsgbuff[cnt++]= GET_BYTE_1(CanDbSetMsgPrv.msginfo.CanMsgId);
    setmsgbuff[cnt++]= GET_BYTE_0(CanDbSetMsgPrv.msginfo.CanMsgId);
    CanDbSetMsgPrv.siginfo.len=8;
    CanDbSetMsgPrv.siginfo.pos=0;
    // setmsgbuff[cnt++]= (CanDbSetMsgPrv.siginfo.len); 
    // setmsgbuff[cnt++]= (CanDbSetMsgPrv.siginfo.pos); 
    
    if(1)
    {// If normal Can
        
    }
    else
    { //If CAN FD
        
    }
    
    int len;
    int pos;
    // unsigned long int sigval[8]={0};
    
    len=CanDbSetMsgPrv.siginfo.len;
    pos=CanDbSetMsgPrv.siginfo.pos;
    // Calculate total bits needed
    int total_bits = len + pos;
   
    // Number of 64-bit words (each word is 64 bits)
    int num_words = (total_bits + 63) / 64;
 
    // Set the bits (this represents the bitmask where the 'length' bits are set starting at 'pos')
    for (int i = 0; i < len; ++i) {
        int bit_index = i + pos;
        int word_index = bit_index / 64;
        int bit_offset = bit_index % 64;
        sigval[word_index] |= (1ULL << bit_offset);
        std::cout<<  (int)sigval[word_index] <<std::endl;
    }
    
    
    //TBD: for CAN FD
    setmsgbuff[cnt++]  =  GET_BYTE_7(sigval[0]) && GET_BYTE_7(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_6(sigval[0]) && GET_BYTE_6(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_5(sigval[0]) && GET_BYTE_5(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_4(sigval[0]) && GET_BYTE_4(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_3(sigval[0]) && GET_BYTE_3(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_2(sigval[0]) && GET_BYTE_2(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_1(sigval[0]) && GET_BYTE_1(CanDbSetMsgPrv.inpsigval<<pos);
    setmsgbuff[cnt++]  =  GET_BYTE_0(sigval[0]) && GET_BYTE_0(CanDbSetMsgPrv.inpsigval<<pos);
    
    
    CanDbSetMsg_SendtoMsgQue(setmsgbuff,cnt);
    CanDbSetMsg_MsgQueDeInit();
    
    return 0;
}

