                               WPBiff v 0.91
                 Copyright (c) Virtual Objects Software 1996


0. Introduction

This simple program changes the icon and the title of the WPS object you
specified according to the state of your mail box on POP3 server. Thepackage includes source code for those suffering from paranoya --
nobody should not get know your POP3 password!;-)  Moreover this
allows you to change the program for your need. However you are
not granted to use this code for developing of commercial software.


1. Packaging

readme         Obviously this readmy file:))
runBiff.cmd    Sample REXX script to start wpbiff
strtBiff.cmd   Yet another sample REXX prog
biff.cpp       biff sources C++ file
TCPSOCK.CPP    small helpful C++ class used by biff.cpp
SOCK.DEF       hmm, i don't really remember what's that:)
file_id.diz    for those using PCBoard & Co
biff.exe       refer to note bellow -- you'd run it directly from
               command line
tcpsock.hpp    C++ header file
mail_0.ico     this icon used by sample REXX scripts
mail_1.ico     this icon used by sample REXX scripts
biff.MAK       IBM VAC++ make file (run nmake ``biff.MAK'' :-)
tcpsock.obj    trash -- you can delete this file
wpbif091.txt   description


2. Usage

OK, let's talk about its usage. WPBiff is configured very simple via
OS/2 environment variables. The package includes some sample REXX
scripts used to start WPBiff. To try WPBiff you have to edit one of
this sample scripts and run it. The env variables need to be assigned
follow:

POP3_USER          -- your user name on POP3 server
POP3_PASS          -- your password on POP3 server
POP3_INTERVAL      -- interval between mail check
POP3_WPS_OBJECT    -- WPS ID of the object whose icon and title will be
                      changed

POP3_NO_MAIL_ICON  -- full path to the icon which will be assigned
                      to the above WPS object when there are no mail
                      for you on POP3 server

POP3_MAIL_ICON     -- full path to the icon which will be assigned
                      to the above WPS object when mail for you is
                      found on your POP3 server

POP3_NO_MSGS_TITLE -- title of the mentioned WPS object when there are
                      no messages

POP3_1_MSG_TITLE   -- title of the WPS object when there is only 1
                      message on the POP3 server

POP3_MSGS_TITLE    -- title of the WPS object when there are more then
                      1 messages on the server. This line should
                      include ``%d'' C-style format specifier which
                      will be replaced with the actual number of
                      messages. For example look at sample starting
                      REXX scripts.


Note: YOU SHOULD NOT START BIFF.EXE DIRECTLY FROM THE COMMAND LINE. Of
course this does not refer to those advanced users knowing what are
they doing:)


3. Acknowledgements

Actualy that was Peter Noskov (noskov@main.comcen-1.nsk.su) who forced
me to write this program. Some time ago I was developing a real WPS
class whose objects can check mail on POP3 server. But the project was
delayed because... well, you know how it used to be happened:) Once
Peter has came to me and said that he's quite bored by the biff program
he using. It was mbiff -- REXX script without source using rxsock lib.
This is shareware and requires registration after some evaluation
period. I'd be a pig  if I say that shareware idea is a bullshit. And
US$5 is not so big cost for such good prog as MailBiff. But if you'd
know what should you do to send this money somewhere in US from Russia
you'll rather sit down and spend one evening to write the similar
program.


