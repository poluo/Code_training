@echo off
set path=C:\Program Files (x86)\CodeBlocks\MinGW\bin
set include=C:\Program Files (x86)\CodeBlocks\MinGW\include
set lib=C:\Program Files (x86)\CodeBlocks\MinGW\lib


:menu
cls
title 选择执行的操作
echo --------------------------------------------------------
echo.
echo 1.build and run 
echo.
echo 2.build not run
echo.
echo 3.delete *.exe
echo.
echo 4.exit
echo.
set /p input=请选择：
if "%input%"=="1" cls&goto buildrun
if "%input%"=="2" cls&goto build
if "%input%"=="3" cls&goto del
if "%input%"=="4" cls&goto exit
:err
cls
echo 对不起，你的输入有误，请按任意键重新输入！
pause>nul
goto menu
:del
title DEL
g:
cd G:\code\commandline\source
del *.exe
echo delete success
goto menu
:buildrun
title BUILDRUN
g:
cd G:\code\commandline\source
gcc * -o cmd.exe
cmd.exe
goto menu
:build
title BUILD
g:
cd G:\code\commandline\source
gcc * -o cmd.exe
echo build success
goto menu
:exit
title EXIT
exit



