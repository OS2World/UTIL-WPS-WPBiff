/*
   Class TCPSock implementation

    Copyright VOS 1995
    Author: Vitaly S. Gumirov

    email: vos@ifshop.ict.nsk.su

*/

#include <tcpsock.hpp>

const char *empty_string="";

const char *ErrorMessages[]={
      "Invalid arguments",
      "Socket isn't initialized",
      "Error greeting from the server",
      "Invalid user name",
      "Invalid password",
      "STAT error",
      0
};

static const char OK_string[]="+OK";
static const long OK_len=sizeof(OK_string)-1;

void TCPSock::TCPSock_Init(struct hostent *hostnm_server, unsigned short server_port) throw(TCPSockError) {
     hostnm = hostnm_server;
     if (hostnm == (struct hostent *) 0)   {
        throw TCPSockError("Gethostbyname failed");
     } else {
        port=server_port;
        server.sin_family      = AF_INET;
        server.sin_port        = htons(port);
        server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);
        if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)   {
           throw TCPSockError("Socket()");
        }
     }
}

int TCPSock::connect() throw(TCPSockError) {
      int retVal=(::connect(s, (struct sockaddr *)&server, sizeof(server)));
      if(retVal<0) throw TCPSockError("connect");
      else return retVal;
}

int TCPSock::send(char * buf, int len, int flags) throw(TCPSockError) {
      int ret=(::send(s, buf, (!len)?strlen(buf):len , flags ));
      if(ret<0) throw TCPSockError("send");
      return ret;
}

int TCPSock::recv(char *buf, int buf_size, int flags) throw(TCPSockError) {
      int ret= (::recv(s, buf, buf_size, flags));
      if(ret<0) throw TCPSockError("recv");
      return ret;
}


const char * TCPSockError::sock_errmsg() {
   char *msg;
   switch(this->sock_errno()) {
     case  SOCEPERM           : msg="(SOCBASEERR+1)   /*Not owner*/";break;
     case  SOCESRCH           : msg="(SOCBASEERR+3)   /*No such process*/";break;
     case  SOCEINTR           : msg="(SOCBASEERR+4)   /*Interrupted system call*/";break;
     case  SOCENXIO           : msg="(SOCBASEERR+6)   /*No such device or address*/";break;
     case  SOCEBADF           : msg="(SOCBASEERR+9)   /*Bad file number*/";break;
     case  SOCEACCES          : msg="(SOCBASEERR+13)  /*Permission denied*/";break;
     case  SOCEFAULT          : msg="(SOCBASEERR+14)  /*Bad address*/";break;
     case  SOCEINVAL          : msg="(SOCBASEERR+22)  /*Invalid argument*/";break;
     case  SOCEMFILE          : msg="(SOCBASEERR+24)  /*Too many open files*/";break;
     case  SOCEPIPE           : msg="(SOCBASEERR+32)  /*Broken pipe*/";break;
     case  SOCEOS2ERR         : msg="(SOCBASEERR+100) /*OS/2 Error*/";break;
     case SOCEWOULDBLOCK     : msg="(SOCBASEERR+35)  /*Operation would block*/";break;
     case SOCEINPROGRESS     : msg="(SOCBASEERR+36)  /*Operation now in progress*/";break;
     case SOCEALREADY        : msg="(SOCBASEERR+37)  /*Operation already in progress*/";break;
     case SOCENOTSOCK        : msg="(SOCBASEERR+38)  /*Socket operation on non-socket*/";break;
     case SOCEDESTADDRREQ    : msg="(SOCBASEERR+39)  /*Destination address required*/";break;
     case SOCEMSGSIZE        : msg="(SOCBASEERR+40)  /*Message too long*/";break;
     case SOCEPROTOTYPE      : msg="(SOCBASEERR+41)  /*Protocol wrong type for socket*/";break;
     case SOCENOPROTOOPT     : msg="(SOCBASEERR+42)  /*Protocol not available*/";break;
     case SOCEPROTONOSUPPORT : msg="(SOCBASEERR+43)  /*Protocol not supported*/";break;
     case SOCESOCKTNOSUPPORT : msg="(SOCBASEERR+44)  /*Socket type not supported*/";break;
     case SOCEOPNOTSUPP      : msg="(SOCBASEERR+45)  /*Operation not supported on socket*/";break;
     case SOCEPFNOSUPPORT    : msg="(SOCBASEERR+46)  /*Protocol family not supported*/";break;
     case SOCEAFNOSUPPORT    : msg="(SOCBASEERR+47)  /*Address family not supported by protocol family*/";break;
     case SOCEADDRINUSE      : msg="(SOCBASEERR+48)  /*Address already in use*/";break;
     case SOCEADDRNOTAVAIL   : msg="(SOCBASEERR+49)  /*Can't assign requested address*/";break;
     case SOCENETDOWN        : msg="(SOCBASEERR+50)  /*Network is down*/";break;
     case SOCENETUNREACH     : msg="(SOCBASEERR+51)  /*Network is unreachable*/";break;
     case SOCENETRESET       : msg="(SOCBASEERR+52)  /*Network dropped connection on r";break;
     case  SOCECONNABORTED   : msg="(SOCBASEERR+53)  /*Software caused connection abort*/";break;
     case  SOCECONNRESET     : msg="(SOCBASEERR+54)  /*Connection reset by peer*/";break;
     case  SOCENOBUFS        : msg="(SOCBASEERR+55)  /*No buffer space available*/";break;
     case  SOCEISCONN        : msg="(SOCBASEERR+56)  /*Socket is already connected*/";break;
     case  SOCENOTCONN       : msg="(SOCBASEERR+57)  /*Socket is not connected*/";break;
     case  SOCESHUTDOWN      : msg="(SOCBASEERR+58)  /*Can't send after socket shutdown*/";break;
     case  SOCETOOMANYREFS   : msg="(SOCBASEERR+59)  /*Too many references: can't splice*/";break;
     case  SOCETIMEDOUT      : msg="(SOCBASEERR+60)  /*Connection timed out*/";break;
     case  SOCECONNREFUSED   : msg="(SOCBASEERR+61)  /*Connection refused*/";break;
     case  SOCELOOP          : msg="(SOCBASEERR+62)  /*Too many levels of symbolic links*/";break;
     case  SOCENAMETOOLONG   : msg="(SOCBASEERR+63)  /*File name too long*/";break;
     case  SOCEHOSTDOWN      : msg="(SOCBASEERR+64)  /*Host is down*/";break;
     case  SOCEHOSTUNREACH   : msg="(SOCBASEERR+65)  /*No route to host*/";break;
     case  SOCENOTEMPTY      : msg="(SOCBASEERR+66)  /*Directory not empty*/";break;
     default: msg="Error not defined";break;
   }
   static char buf[100];
   if(default_msg) {
      sprintf(buf,"%s : %s", msg,default_msg);
      return buf;
   } return msg;
}


const char * POP3SockError::sock_errmsg()
{
  if(errcode==POP3SockError::ERR_NULL) return TCPSockError::sock_errmsg();
  long ec=errcode-POP3SockError::MIN_ERRNO;
  if(ec>=0 && ec<sizeof(ErrorMessages))
      return ErrorMessages[ec];
  else
      return TCPSockError::sock_errmsg();
}


BOOL POP3Sock::logon()  throw(TCPSockError, POP3SockError)
{
  if(!IsInitialized()) {
      POP3SockError err("POP3Sock::logon()", POP3SockError::NOT_INITIALIZED );
      throw  err;
      return FALSE;
  }
  if(connect()<0) return FALSE;
  char buf[100];
  if(recv(buf, sizeof(buf))<0) return FALSE;
  if(!check_ok(buf) ) {
     throw POP3SockError( "POP3Sock::logon", POP3SockError::ERR_GREETING);
     return FALSE;
   }
  if(sock_printf("USER %s\r\n",user)<0) return FALSE;
  if(recv(buf, sizeof(buf))<0) return FALSE;
  if(!check_ok(buf) ) {
     throw POP3SockError( "POP3Sock::logon",POP3SockError::ERR_USER);
     return FALSE;
   }
  if(sock_printf("PASS %s\r\n",passwd)<0) return FALSE;
  if(recv(buf, sizeof(buf))<0) return FALSE;
  if(!check_ok(buf) ) {
     throw POP3SockError( "POP3Sock::logon",POP3SockError::ERR_PASSWD);
     return FALSE;
   }
   return TRUE;
}



long POP3Sock::number_of_msgs()
{
  char buf[100];
  if(sock_printf("STAT\r\n")<0) return FALSE;
  if(recv(buf, sizeof(buf))<0) return FALSE;
  if(!check_ok(buf) ) {
     return FALSE;
   }
   long msgNum=0;
    *(strchr(buf,'\r'))=0;
    sscanf(buf+OK_len,"%d",  &msgNum);
   return msgNum;
}

BOOL POP3Sock::quit()
{
  char buf[100];
  if(sock_printf("QUIT\r\n")<0) return FALSE;
  if(recv(buf, sizeof(buf))<0) return FALSE;
  if(!check_ok(buf) ) {
     return FALSE;
   }
   return TRUE;

}

BOOL POP3Sock::reset()
{
  char buf[100];
  if(sock_printf("RSET\r\n")<0) return FALSE;
  if(recv(buf, sizeof(buf))<0) return FALSE;
  if(!check_ok(buf) ) {
     return FALSE;
   }
   return TRUE;
}


BOOL POP3Sock::check_ok(char * buf) 
{ 
BOOL retVal= (strnicmp(buf, OK_string, OK_len)==0);
return retVal;
}

int TCPSock::sock_printf(char *format,...) {
va_list ap;
va_start(ap, format);

static   char buf[100];
vsprintf(buf,format,ap);
va_end(ap);

return this->send(buf);
}


