/* 
  Sample rexx script to run WPS Biff 

*/


call RxFuncAdd 'SysLoadFuncs', "RexxUtil", "SysLoadFuncs"
call SysLoadFuncs

parse source . . src_prog


icon=filespec("drive", src_prog)||filespec("path", src_prog)||"mail_0.ico"

user='serge'

obj_id="<POP3_"||user||">"

rc=SysDestroyObject(obj_id);

rc=SysCreateObject("WPDataFile", "mail", "<WP_DESKTOP>", "ICONFILE="||icon||";OBJECTID="||obj_id);
if \rc then do
 say "Object was not created:("
 return 1;
end
env='OS2ENVIRONMENT'

icon1=filespec("drive", src_prog)||filespec("path", src_prog)||"mail_1.ico"

crlf=x2c('0d')||x2c('0a')
setlocal
call value 'POP3_HOST',"",env

 /* the variable `user' was assigned somewhere above*/
call value 'POP3_USER',user,env
call value 'POP3_PASS','zhopa',env
call value 'POP3_INTERVAL','60',env
call value 'POP3_WPS_OBJECT',obj_id,env
call value 'POP3_NO_MAIL_ICON',icon,env
call value 'POP3_MAIL_ICON',icon1,env
call value 'POP3_NO_MSGS_TITLE',"Empty mailbox",env
call value 'POP3_1_MSG_TITLE',"There is 1 message "crlf"for "||value('POP3_USER',,env)||"@"||value('POP3_HOST',,env),env
call value 'POP3_MSGS_TITLE',"There are %d messages "crlf"for "||value('POP3_USER',,env)||"@"||value('POP3_HOST',,env),env

'detach biff.exe'
endlocal

