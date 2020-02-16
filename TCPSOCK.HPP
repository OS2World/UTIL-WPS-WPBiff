/*
   Class TCPSock interface

    Copyright VOS 1995
    Author: Vitaly S. Gumirov

    email: vos@ifshop.ict.nsk.su

*/

#include <os2.h>
#include <types.h>
#include <netinet\in.h>
#include <sys\socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

class IP_AbstractAddr {
   char * addr;
public:
   IP_AbstractAddr(char * a) { addr=a; }
   IP_AbstractAddr(const char * a) { addr=((char*)a);}
   IP_AbstractAddr(unsigned char * a){ addr=((char*)a);}
   IP_AbstractAddr(signed char * a){ addr=((char*)a);}
   IP_AbstractAddr(const unsigned char * a){ addr=((char*)a);}
   IP_AbstractAddr(const signed char * a){ addr=((char*)a);}
   char * _get_addr() {return addr; }
};

class IP_Name : public IP_AbstractAddr {
// name address;
public:
   IP_Name(char * a): IP_AbstractAddr(a) {};
   IP_Name(const char * a): IP_AbstractAddr((char*)a) {};
   IP_Name(unsigned char * a): IP_AbstractAddr((char*)a) {};
   IP_Name(signed char * a): IP_AbstractAddr((char*)a) {};
   IP_Name(const unsigned char * a): IP_AbstractAddr((char*)a) {};
   IP_Name(const signed char * a): IP_AbstractAddr((char*)a) {};
};


class IP_Addr : public IP_AbstractAddr {
// dotted address
public:
   IP_Addr(char * a): IP_AbstractAddr(a) {};
   IP_Addr(const char * a):IP_AbstractAddr((char*)a) {};
   IP_Addr(unsigned char * a): IP_AbstractAddr((char*)a) {};
   IP_Addr(signed char * a): IP_AbstractAddr((char*)a) {};
   IP_Addr(const unsigned char * a): IP_AbstractAddr((char*)a) {};
   IP_Addr(const signed char * a): IP_AbstractAddr((char*)a) {};
};

extern const char *empty_string;

class TCPSockError {
protected:
   char * default_msg;
   void _set_default_msg(char *msg) { if(msg) default_msg=strdup(msg); else default_msg=0; }
public:
   TCPSockError(char * d_msg=0) { _set_default_msg(d_msg); };
   TCPSockError(TCPSockError & from){ _set_default_msg(from.default_msg); };
   ~TCPSockError() { if(default_msg) delete default_msg; }

   virtual int sock_errno() { return ::sock_errno(); }
   void psock_errno(char *msg=0) { if(!msg) msg=default_msg; if(!msg) msg=""; ::psock_errno(msg);}
   virtual const char * sock_errmsg();
   
};

class TCPSock {
protected:
   unsigned short port;       /* server port */
   struct sockaddr_in server; /* server address */
   struct hostent *hostnm;    /* server host name information             */
   int s;                     /* client socket                            */

   void TCPSock_Init(struct hostent *hostnm_server, unsigned short server_port) throw(TCPSockError) ;
public:
   TCPSock(IP_Name srv, unsigned short server_port) {
      TCPSock_Init(gethostbyname(srv._get_addr()), server_port);
   }
   TCPSock(IP_Addr srv, unsigned short server_port) {
      char * s =srv._get_addr();
      TCPSock_Init(gethostbyaddr(s,strlen(s),AF_INET), server_port);
   }
   TCPSock(char * str_name, unsigned short server_port) {
      TCPSock_Init(gethostbyname(str_name), server_port);
   }

/*    ~TCPSock() {if(hostnm) delete hostnm; } */
   int connect() throw(TCPSockError);
   int sockclose() {return ::soclose(s);}
   int soclose() {return ::soclose(s);}
   int sock_errno() { return ::sock_errno(); }
   void psock_errno(char *msg) { ::psock_errno(msg); }
   int send(char * buf, int len=0, int flags=0) throw(TCPSockError); 
   int recv(char *buf, int buf_size, int flags=0) throw(TCPSockError) ;
   int sock_printf(char *format,...);
   BOOL IsInitialized() { 
	return ((hostnm != (struct hostent *)0) && s>=0 ); }

};

class POP3SockError: public TCPSockError {
public:
   enum POP3SockErrorCode { ERR_NULL=0, MIN_ERRNO=SOCBASEERR+100,
      INVALID_ARGUMENTS=MIN_ERRNO,
      NOT_INITIALIZED,
      ERR_GREETING,
      ERR_USER,
      ERR_PASSWD,
      ERR_STAT,
      MAX_ERRNO };
protected:
   POP3SockErrorCode errcode;
public:
   POP3SockError(POP3SockError & from): TCPSockError(from.default_msg), errcode(from.errcode) {}
   POP3SockError(char * msg, POP3SockErrorCode code=ERR_NULL ): TCPSockError(msg) { errcode=code; }
   virtual int sock_errno() {if(errcode!=ERR_NULL) return errcode; else return TCPSockError::sock_errno(); }
   virtual const char * sock_errmsg(); // overriden
};

class POP3Sock: public TCPSock {
   char * user;
   char * passwd;

public:
   POP3Sock(IP_Addr addr, char *_user, char * _passwd, unsigned short port=110) throw (POP3SockError):
      TCPSock(addr, port), user(_user), passwd(_passwd) {
      if(!_user || !_passwd) throw POP3SockError("POP3Sock",POP3SockError::INVALID_ARGUMENTS);
   }
   POP3Sock(IP_Name name, char *_user, char * _passwd, unsigned short port=110) throw (POP3SockError):
      TCPSock(name, port), user(_user), passwd(_passwd) {
      if(!_user || !_passwd) throw POP3SockError("POP3Sock",POP3SockError::INVALID_ARGUMENTS);
   }
   void _set_user(char *_user) throw(POP3SockError) {
      if(_user) user=_user;
      else throw POP3SockError("POP3Sock",POP3SockError::INVALID_ARGUMENTS);
   }
   void _set_passwd(char *_passwd) throw(POP3SockError) {
      if(_passwd) passwd=_passwd;
      else throw POP3SockError("POP3Sock",POP3SockError::INVALID_ARGUMENTS);
   }

   BOOL logon();
   BOOL quit();
   BOOL reset();
   long number_of_msgs();
   inline BOOL check_ok(char *buf);
};

