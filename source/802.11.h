#ifndef _802_11_INCLUDED
#define _802_11_INCLUDED

#ifdef __cplusplus
  extern "C" {
#endif

typedef void (*MULTICAST_CALLBACK)(unsigned char *data, int length, unsigned char* from) ;

void Send802_11(unsigned char *data, int length) ;
void Handle802_11(unsigned char *data, int length) ;

typedef struct FRAMECONTROL
{
	unsigned short		version:2 ;
	unsigned short		type:2 ;
	unsigned short		subType:4 ;
	unsigned short		toStation:1 ;
	unsigned short		fromStation:1 ;
	unsigned short		moreFrag:1 ;
	unsigned short		retry:1 ;
	unsigned short		powerMgm:1 ;
	unsigned short		moreData:1 ;
	unsigned short		wep:1 ;
	unsigned short		ordered:1 ;
} FRAMECONTROL, *LPFRAMECONTROL ;

void WritePacket(unsigned char *data,int length) ;
void WriteSentPacket(unsigned char *data,int length) ;
void StopCapture(void) ;

void Resend802_11withNoAck(void) ;
void RegisterACK(void) ;
void Send802_11NeedACK(unsigned char *data, int length) ;
void Send802_11Data(unsigned char *toMAC,unsigned char *data, int length) ;

void SetChannel(unsigned char channel) ;
void IPC_RcvCompleteCheck(void) ;
void LWIFI_IPC_Callback(unsigned char *data, unsigned long length) ;

extern char ownMAC[6] ;

void UpdateMAC(unsigned char *mac) ;


#ifdef __cplusplus
  }
#endif

#endif
