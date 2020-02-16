/* rexx */


call RxFuncAdd 'SysLoadFuncs', "RexxUtil", "SysLoadFuncs"
call SysLoadFuncs

parse source . . src_prog

icon=filespec("drive", src_prog)||filespec("path", src_prog)||"mail_0.ico"

obj_id='<WP_PM_MAIL>'


rc=SysCreateObject('WPProgram','vit@ifshop', '<WP_DESKTOP>','EXENAME=s:\tcpip\pmmail\pmmail.exe;STARTUPDIR=s:\tcpip\pmmail\mail\vit;"ICONFILE="||icon||";OBJECTID=<WP_PM_MAIL>','u')
if \rc then do
 say "Object was not created:("
 /* return 1; */
end

env='OS2ENVIRONMENT'

icon1=filespec("drive", src_prog)||filespec("path", src_prog)||"mail_1.ico"

crlf=x2c('0d')||x2c('0a')
call value 'POP3_HOST','ns',env
call value 'POP3_USER','vit',env
call value 'POP3_PASS',',kzv,f',env
call value 'POP3_INTERVAL','10',env
call value 'POP3_WPS_OBJECT',obj_id,env
call value 'POP3_NO_MAIL_ICON',icon,env
call value 'POP3_MAIL_ICON',icon1,env
call value 'POP3_NO_MSGS_TITLE',"Нет ничего",env
call value 'POP3_1_MSG_TITLE',"Одно письмо"crlf"для "||value('POP3_USER',,env)||"@"||value('POP3_HOST',,env),env
call value 'POP3_MSGS_TITLE',"Всего %d писем"||crlf||"для "||value('POP3_USER',,env)||"@"||value('POP3_HOST',,env),env

'detach Biff.exe'

