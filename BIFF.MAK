#    Copyright VOS 1995
#    Author: Vitaly S. Gumirov
#
#  Compiler options:
#
#   /Ti  : Generate debugger information
#   /Sm  : Allow migration extensions
#   /Ss  : Allow '//' for comments
#   /Q   : Do not display logo
#   /Kb  : Produce basic diagnostic message
#   /W2  : Produce severe errors, errors and warnings
#   /Gm  : Link with the multithread version of library
#   /Gt  : Enavle all variables to be passed to 16-bit function.
#          Static & external variables are mapped into 16-bit segment.
#          Variables larger then 64k will be alligned on, but will still
#          cross, 64k boundary.
#   /C   : Compile only
#
#
#  Linker options:
#
#   /De  : Prepare for Debugging
#   /NOI : Preserve the case sensitivity

INCLUDE=$(INCLUDE);c:\tcpip\include
LIB=$(LIB);c:\tcpip\lib;
CPPFLAGS=/Fi+ /Si+ /Ti /DOS2 /Sm /Ss /Q  /W2 /Gm /Gt /C 
CC=icc 

all: biff.exe

biff.obj : biff.cpp tcpsock.hpp
  $(CC) $(CPPFLAGS)  biff.Cpp

tcpsock.obj : tcpsock.cpp tcpsock.hpp
  $(CC) $(CPPFLAGS) tcpsock.cpp

biff.exe: biff.obj biff.mak tcpsock.obj
  ilink /nofree biff tcpsock,biff.exe,NUL,os2386.lib so32dll.lib tcp32dll.lib,sock.def;
