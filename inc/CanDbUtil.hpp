#ifndef CANDBUTIL_HPP
#define CANDBUTIL_HPP

// Typedefs as per your request
typedef std::string CanSigName;
typedef uint8_t CanSigLen;
typedef uint32_t CanSigPos;

typedef std::string CanMsgName;
typedef std::string CanMsgType;

typedef std::string BusName;
typedef std::string BusType;

// CanSig class definition
class CanSig {
    public:
    CanSigName name;
    CanSigLen len;
    CanSigPos pos;
    uint32_t InitVal;
    uint32_t sigMask;
    
    // // Constructor for CanSig class
    // CanSig(CanSigName name, CanSigLen len, CanSigPos pos, uint32_t sigMask, uint32_t InitVal)
    // : name(name), len(len), pos(pos), sigMask(sigMask), InitVal(InitVal) {}
};

// CanMsg class definition
class CanMsg {
    public:
    CanMsgName name;   //CanFrame[*]CanFrameName
    CanMsgType type;
    uint32_t CanMsgCycRate;
    uint32_t CanMsgLen;    //CanFrame[*]CanFrameLen
    uint32_t CanMsgId;     //@(CanFrame[*]CanFrameRef --> String(Object or ref)  PDU[CanFrame[*]CanFrameRef]PduName
    
    std::vector<CanSig> CanSigVec;
    
    // Constructor for CanMsg class
    // CanMsg(CanMsgName name, CanMsgType type, uint32_t cycRate, uint32_t len, uint32_t msgId, std::vector<CanSig> canSigVec)
    // : name(name), type(type), CanMsgCycRate(cycRate), CanMsgLen(len), CanMsgId(msgId), CanSigVec(canSigVec) {}
};

//Cluster[*]CanClusterName, Cluster{CanClusterName

// Bus class definition
class Bus {
    public:
    BusName Name;      //=Cluster[*]CanClusterName
    BusType type;   //--
    uint32_t Baudrate;   //=Cluster[*]CanBaudrate
    uint32_t FdBaudrate;   //=Cluster[*]CanFDBaudrate
    std::vector<CanMsg> CanTxMsgVec; 
    std::vector<CanMsg> CanRxMsgVec;
    
    // Constructor for Bus class
    // Bus(BusName Name, BusType type, uint32_t Baudrate, uint32_t FdBaudrate, std::vector<CanMsg> canTxMsgVec,std::vector<CanMsg> canRxMsgVec)
    // : Name(Name), type(type), Baudrate(Baudrate), FdBaudrate(FdBaudrate), CanTxMsgVec(canTxMsgVec) ,CanRxMsgVec(canRxMsgVec){}
};

int CanDbUtil_CheckIfBusNameValid(std::string inpBusname);
int CanDbUtil_CheckIfCanMsgNameValid(std::string inpBusname, std::string inpCanMsgname, class CanMsg *outMsgInfo);
int CanDbUtil_CheckIfCanSigNameValid(std::string inpBusname, std::string inpCanMsgname,std::string inpCanSigname, class CanSig *outSigInfo);
int CanDbUtil_CheckIfCanSigValValid(std::string inpBusname, std::string inpCanMsgname,std::string inpCanSigname,std::string inpCanSigVal);
int CanDbUtil_CheckIfCanDevUp(std::string inpBusname);


uint64_t CanDbUtil_getMsgId(std::string inpBusname,std::string inpCanMsgname);

// using _MsgId= uint8_t;
using _CmdId= uint8_t;
using _SeqNum= uint32_t;
using _len = uint32_t;
using _datapacket = uint8_t *;



#define CMDID_CANLOADDB				0x01
#define CMDID_CANRMDB               0x02
#define CMDID_CANMAPDBCH            0x03
#define CMDID_CANSTART              0x04
#define CMDID_CANSTOP               0x05
#define CMDID_CANDBSETMSG           0x06
#define CMDID_CANDBSENDMSG          0x07
#define CMDID_CANDBREGTXCBK         0x08
#define CMDID_CANDBREGRXCBK         0x09

// 
class Msg {
    public:
	_CmdId CmdId;
	_SeqNum SeqNum;
	_len	len;
	_datapacket datapacket;
	Msg(_CmdId cmdid): CmdId(cmdid){}
};

// Macro to extract the lowest byte (Byte 0)
#define GET_BYTE_0(word)   ((word) & 0xFF)

// Macro to extract the second byte (Byte 1)
#define GET_BYTE_1(word)   (((word) >> 8) & 0xFF)

// Macro to extract the third byte (Byte 2)
#define GET_BYTE_2(word)   (((word) >> 16) & 0xFF)

// Macro to extract the highest byte (Byte 3)
#define GET_BYTE_3(word)   (((word) >> 24) & 0xFF)


// Macro to extract the lowest byte (Byte 0)
#define GET_BYTE_4(word)   (((word) >> 32) & 0xFF)

// Macro to extract the second byte (Byte 1)
#define GET_BYTE_5(word)  (((word) >> 40) & 0xFF)

// Macro to extract the third byte (Byte 2)
#define GET_BYTE_6(word)   (((word) >> 48) & 0xFF)

// Macro to extract the highest byte (Byte 3)
#define GET_BYTE_7(word)   (((word) >> 56) & 0xFF)


#define MAKE_WORD(byte0, byte1, byte2, byte3)   \
    (((byte3) << 24) | ((byte2) << 16) | ((byte1) << 8) | (byte0))

#endif