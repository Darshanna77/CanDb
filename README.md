# CanDb
Currently Software  under development!!!!!

To Build:
make

To run:

CanLoadDb <path>
	Input: path of NIP file
	Output: Create a json file with Bus,Msg and signal list, 
		    Create a shared memory for extracted data.
	
CanRmDb
	Output: Clear the shared memory for last loaded database
	
CanMapDbCh  <DbCanBusName>  </dev/can*>

CanStart <DbCanBusName>  <LoadCfgPath.py>
	 Read from shared memory and Create a process and wait for inputs from other commands
	
CanStop
	Kill the main process.No further commands recieved.
	
CanDbSetMsg <DbCanBusName> <DbMsgName> <DbSigName=> <DbSigValType=RAW/SIGVAL>  <Sigval>
	Send the request to main process.
	
CanDbSendMsg <DbCanBusName> <DbMsgName> --optional<Rateinseconds>
	Send the request to main process.

CanDbRegTxCbk  <DbCanBusName> <DbMsgName>   <MsgCbk.py>

CanDbRegRxCbk  <DbCanBusName> <DbMsgName>   <MsgCbk.py>
