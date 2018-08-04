
@echo arg[0] = Portnummer , arg[1] = Baudrate , arg[2] = Stream der gesendet werden soll

:while

"%~dp0\main.exe" 6 9600 "-K1"


"%~dp0\main.exe" 6 9600 "-K2"


"%~dp0\main.exe" 6 9600 "-K3"


"%~dp0\main.exe" 6 9600 "-K4"


"%~dp0\main.exe" 6 9600 "-K5"


"%~dp0\main.exe" 6 9600 "-K6"


"%~dp0\main.exe" 6 9600 "-K7"


"%~dp0\main.exe" 6 9600 "-K8"


"%~dp0\main.exe" 6 9600 "-K9"


"%~dp0\main.exe" 6 9600 "-K10"


"%~dp0\main.exe" 6 9600 "-K11"


goto while

pause