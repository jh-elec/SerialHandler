
@echo arg[0] = Portnummer , arg[1] = Baudrate , arg[2] = Stream der gesendet werden soll , arg[3] = Soll "\r\n" mit gesendet werden?

SET cnt=0


:while

SET /A cnt=cnt+1
"%~dp0\main.exe" 6 9600 "-K" OFF
"%~dp0\main.exe" 6 9600 %cnt%+'0' ON

timeout /t 1

goto while

pause