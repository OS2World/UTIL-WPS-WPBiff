//    Copyright VOS 1996
//    Author: Vitaly S. Gumirov
//
// email: vos@ifshop.ict.nsk.su


#define  INCL_WINWORKPLACE
#define  INCL_DOSPROCESS
#include <os2.h>
#include <stdlib.h>
#include <time.h>
#include <tcpsock.hpp>

main(int argc, char *argv[])
{


    long interval=atol(getenv("POP3_INTERVAL"));
    char *obj_id=strdup(getenv("POP3_WPS_OBJECT"));
    HOBJECT hobj=WinQueryObject(obj_id);

    if(!hobj) {
      fprintf(stderr, "Object %s not found on your WPS\n", obj_id);
      return 1;
    }

    char *no_msgs_icon_file=strdup(getenv("POP3_NO_MAIL_ICON"));
    char *there_msgs_icon_file=strdup(getenv("POP3_MAIL_ICON"));

    long old_msgs=-1;

    do {
     try {
      POP3Sock pop3d(IP_Name(getenv("POP3_HOST"))
               , getenv("POP3_USER")
               , getenv("POP3_PASS"));
      pop3d.logon();
      long num_msgs;
      printf("There are %d message(s)\n",num_msgs=pop3d.number_of_msgs());
      if(old_msgs!=num_msgs) {
          old_msgs=num_msgs;
          char title[100], setup_str[100];
          switch(num_msgs) {
             case 0:  sprintf(title, getenv("POP3_NO_MSGS_TITLE") );
                      break;
             case 1: sprintf(title, getenv("POP3_1_MSG_TITLE") );
                     break;
             default:  sprintf(title,getenv("POP3_MSGS_TITLE"), num_msgs );

            }
          sprintf(setup_str, "TITLE=%s;ICONFILE=%s"
                , title
                , (num_msgs)?there_msgs_icon_file : no_msgs_icon_file );

          WinSetObjectData(hobj, setup_str);
      }
      pop3d.quit();
     }  catch(TCPSockError& _err) {
         printf("%s", _err.sock_errmsg());
     }

     DosSleep(interval*1000);
    } while(1);
 

 return 0;
}


