@Echo off
SET LOGFILE=MyLogFile.txt
echo Stampo i risultati
start index.html
:restart
timeout 5
call :scan >> %LOGFILE%
start main.exe
call :restart
exit /b 0

:scan
::scan delle reti attorno con canale, frequenza radio, Bssid e intensità segnale passate
netsh wlan show networks mode=bssid |^
findstr /I /R  "canale | bssid | segnale"