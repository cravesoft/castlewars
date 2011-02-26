#ifndef MESSAGEQUEUE_INCLUDED
#define MESSAGEQUEUE_INCLUDED

#ifdef __cplusplus
  extern "C" {
#endif

#include <nds.h>

typedef void (*IPC_MSGCOMPLETECALLBACK_PROC)(void) ;
typedef void (*IPC_CUSTOMCALLBACK_PROC)(unsigned char *data, int length) ;
typedef void (*IPC_CHANNELCALLBACK)(unsigned char *data, unsigned long length) ;

//#define IPCTAG_DATA			(' ATD' & 0x00FFFFFF)
//#define IPCTAG_CHANNEL		(' NHC' & 0x00FFFFFF)
//#define IPCTAG_BSSSET		(' SSB' & 0x00FFFFFF)
//#define IPCTAG_MAC			(' CAM' & 0x00FFFFFF)
//#define IPCTAG_HINT			('TNIH' & 0xFFFFFFFF)
//#define IPCTAG_INIT			('tinI' & 0xFFFFFFFF)

#define IPCTAG_DATA			1
#define IPCTAG_CHANNEL		2
#define IPCTAG_BSSSET		3
#define IPCTAG_MAC			4
#define IPCTAG_HINT			5
#define IPCTAG_INIT			6
#define IPCTAG_ECHO			7

void IPC_IrqAll(void) ;
void IPC_SendMessage(char *data,unsigned long length) ;
bool IPC_GetMessage(char *data,unsigned long *length) ;
void IPC_WaitForAllSent(void) ;
int IPC_IsSendQueueEmpty(void) ;
void IPC_SetChannelCallback(unsigned long channel, IPC_CHANNELCALLBACK cb) ;
void IPC_SetMsgCompleteCallback(IPC_MSGCOMPLETECALLBACK_PROC callback) ;
void IPC_SetCustomCallback(IPC_CUSTOMCALLBACK_PROC callback) ;
void IPC_PassCustomMessage(unsigned char *data, int length) ;
int IPC_AllreadySending(unsigned char *data, int length) ;

int IPC_Init(void) ;

#ifdef __cplusplus
  }
#endif

#endif
