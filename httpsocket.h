/*httpSocket.h*/
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <sys/types.h>
#include   <sys/socket.h>
#include   <errno.h>
#include   <unistd.h>
#include   <netinet/in.h>
#include   <limits.h>
#include   <netdb.h>
#include   <arpa/inet.h>
#include   <ctype.h>
#include <string>
#if _MSC_VER > 1000
#pragma once
#endif
class  CHttpSocket
{
public:
int GetServerState();
int GetField(const char* szSession,char *szValue,int nMaxLength);
int GetResponseLine(char *pLine,int nMaxLength);
const char*GetResponseHeader(int &Length);
const char *FormatRequestHeader(const char *pServer,const char *pObject,long &Length,
char* pCookie=NULL,char *pReferer=NULL,
long nFrom=0,long nTo=0,
int nServerType=0);
int GetRequestHeader(char *pHeader,int nMaxLength) const;
bool SendRequest(const char* pRequestHeader = NULL,long Length = 0);
CHttpSocket();
virtual ~CHttpSocket();
bool SetTimeout(int nTime,int nType=0);
long Receive(char* pBuffer,long nMaxLength);
bool Connect(const char* szHostName,int nPort=80);
bool Socket();
bool CloseSocket();
protected:
char m_requestheader[1024];
char m_ResponseHeader[1024];
int m_port;
char m_ipaddr[256];
bool m_bConnected;
int m_s;
hostent *m_phostent;
int m_nCurIndex;//GetResponsLine();
bool m_bResponsed;
int m_nResponseHeaderSize;
};
