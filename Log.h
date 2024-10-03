#ifndef _SIMPLE_LOG_H
#define _SIMPLE_LOG_H

////////////////////////////////////////////////////////////////////////////////
//
// Request constant definitions.
//
////////////////////////////////////////////////////////////////////////////////

//General Log Requests
#define LOG_ALL													0xFFFFFFFF
#define LOG_NONE												0x00000000

//Exception Log Requests
#define LOG_EXCEPTION											0x80000000
#define LOG_ALERT												0x40000000
#define LOG_WARNNING											0x20000000
#define LOG_INFORMATION                                         0x10000000

//Buffer and Packet Log Requests
#define LOG_BUFFER												0x08000000
#define LOG_PACKET												0x04000000
#define LOG_XML_PACKET											0x04000000
#define LOG_PACKET_POOL											0x04000000

#define LOG_PACKET_MASK											0x03ff0000

//CMPP Packet Log Requests
#define LOG_CMPP_PACKET_MASK									LOG_PACKET_MASK
#define LOG_CMPP_PACKET											0x02000000
#define LOG_CMPP_CONNECT										0x00800000
#define LOG_CMPP_CONNECT_RESPONSE								0x00800000
#define LOG_CMPP_TERMINATE										0x00400000
#define LOG_CMPP_TERMINATE_RESPONSE								0x00400000
#define LOG_CMPP_ACTIVETEST										0x00200000
#define LOG_CMPP_ACTIVETEST_RESPONSE							0x00200000
#define LOG_CMPP_CANCEL											0x00100000
#define LOG_CMPP_CANCEL_RESPONSE								0x00100000
#define LOG_CMPP_QUERY											0x00080000
#define LOG_CMPP_QUERY_RESPONSE									0x00080000
#define LOG_CMPP_DELIVER										0x00040000
#define LOG_CMPP_DELIVER_RESPONSE								0x00040000
#define LOG_CMPP_STATUS_REPORT									0x00040000
#define LOG_CMPP_SUBMIT											0x00020000
#define LOG_CMPP_SUBMIT_RESPONSE								0x00020000
#define LOG_CMPP_FORWARD										0x00060000
#define LOG_CMPP_FORWARD_RESPONSE								0x00060000
#define LOG_CMPP_NACK_RESPONSE									0x00010000

//SMIAS Packet Log Requests
#define LOG_SMIAS_PACKET_MASK									LOG_PACKET_MASK
#define LOG_SMIAS_PACKET										0x02000000
#define LOG_SMIAS_CONNECT										0x00800000
#define LOG_SMIAS_CONNECT_RESPONSE								0x00800000
#define LOG_SMIAS_TERMINATE										0x00400000
#define LOG_SMIAS_TERMINATE_RESPONSE							0x00400000
#define LOG_SMIAS_ACTIVETEST									0x00200000
#define LOG_SMIAS_ACTIVETEST_RESPONSE							0x00200000
#define LOG_SMIAS_CANCEL										0x00100000
#define LOG_SMIAS_CANCEL_RESPONSE								0x00100000
#define LOG_SMIAS_QUERY											0x00080000
#define LOG_SMIAS_QUERY_RESPONSE								0x00080000
#define LOG_SMIAS_DELIVER										0x00040000
#define LOG_SMIAS_DELIVER_RESPONSE								0x00040000
#define LOG_SMIAS_STATUS_REPORT									0x00040000
#define LOG_SMIAS_SUBMIT										0x00020000
#define LOG_SMIAS_SUBMIT_RESPONSE								0x00020000
#define LOG_SMIAS_NACK_RESPONSE									0x00010000

//SMPP Packet Log Requests
#define LOG_SMPP_PACKET_MASK									LOG_PACKET_MASK
#define LOG_SMPP_PACKET											0x02000000
#define LOG_SMPP_OPTIONAL_PARAMETER								0x01000000
#define LOG_SMPP_ADDRESS										0x01000000
#define LOG_SMPP_BIND											0x00800000
#define LOG_SMPP_BIND_RESPONSE									0x00800000
#define LOG_SMPP_UNBIND											0x00400000
#define LOG_SMPP_UNBIND_RESPONSE								0x00400000
#define LOG_SMPP_ENQUIRE_LINK									0x00200000
#define LOG_SMPP_ENQUIRE_LINK_RESPONSE							0x00200000
#define LOG_SMPP_COMMAND										0x00180000
#define LOG_SMPP_COMMAND_RESPONSE								0x00180000
#define LOG_SMPP_SM												0x00060000
#define LOG_SMPP_SM_RESPONSE									0x00060000
#define LOG_SMPP_DATA_SM										0x00060000
#define LOG_SMPP_DATA_SM_RESPONSE								0x00060000
#define LOG_SMPP_SUBMIT_MULTI									0x00060000
#define LOG_SMPP_SUBMIT_MULTI_RESPONSE							0x00060000
#define LOG_SMPP_CANCEL_SM										0x00060000
#define LOG_SMPP_CANCEL_SM_RESPONSE								0x00060000
#define LOG_SMPP_QUERY_SM										0x00060000
#define LOG_SMPP_QUERY_SM_RESPONSE								0x00060000
#define LOG_SMPP_REPLACE_SM										0x00060000
#define LOG_SMPP_REPLACE_SM_RESPONSE							0x00060000
#define LOG_SMPP_GENERIC_NACK_RESPONSE							0x00010000
#define LOG_SMPP_OUTBIND										0x00010000
#define LOG_SMPP_ALERT_NOTIFICATION								0x00010000

//SGIP Packet Log Requests
#define LOG_SGIP_PACKET_MASK									LOG_PACKET_MASK
#define LOG_SGIP_PACKET											0x02000000
#define LOG_SGIP_BIND											0x00800000
#define LOG_SGIP_BIND_RESPONSE									0x00800000
#define LOG_SGIP_UNBIND											0x00400000
#define LOG_SGIP_UNBIND_RESPONSE								0x00400000
#define LOG_SGIP_TRACE											0x00080000
#define LOG_SGIP_TRACE_RESPONSE									0x00080000
#define LOG_SGIP_DELIVER										0x00040000
#define LOG_SGIP_DELIVER_RESPONSE								0x00040000
#define LOG_SGIP_REPORT											0x00040000
#define LOG_SGIP_REPORT_RESPONSE								0x00040000
#define LOG_SGIP_SUBMIT											0x00020000
#define LOG_SGIP_SUBMIT_RESPONSE								0x00020000
#define LOG_SGIP_USERRPT										0x00010000
#define LOG_SGIP_USERRPT_RESPONSE								0x00010000

//Functions Log Requests
#define LOG_UNWRAP_METHOD										0x00008000
#define LOG_WRAP_METHOD											0x00008000
#define LOG_ISVALID_METHOD										0x00004000
#define LOG_READ_METHOD											0x00002000
#define LOG_WRITE_METHOD										0x00002000
#define LOG_OUTPUT_METHOD										0x00001000
#define LOG_INPUT_METHOD										0x00001000

//Engine Log Requests
#define LOG_TUNNEL												0x00000800

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
// Including the definitions for general using.
//
// These definitions are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSimpleLog
{
	//Requests
	_UINT32 nRequests;

	//Recorder
	SimpleRecorder recorder;

	//Lock
	SimpleLock lock;
	//Sequence
	_INT32 nSequence;
}

SimpleLog;

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _BOOL InitializeLog(_STRING lpstrDirectory,_UINT32 nRequests);
extern _BOOL UninitializeLog();

extern _BOOL GetEventTraceID(_INT32* lpTraceID);
extern _BOOL TraceEvent(_INT32 nTraceID,_STRING lpstrEvent);

extern _BOOL CombinateEvent(_INT32 nHeadTraceID,_INT32 nTailTraceID);

extern _BOOL LogRequestedEvent(_STRING lpstrEvent,_UINT32 nRequests);
extern _BOOL LogRequestedFormat(_UINT32 nRequests,_STRING lpstrEvent,...);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the header file.
