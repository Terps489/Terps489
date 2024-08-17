@echo off
setlocal enabledelayedexpansion

REM 
set /a "count1=!random! %% 17 + 7"
set /a "count2=!random! %% 5 + 1"
set "numbers1="
set "numbers2="
for /l %%i in (1, 1, %count1%) do (
    set /a "num1=!random! %% 4 + 23"
    set "numbers1=!numbers1!!num1!&"
)
for /l %%i in (1, 1, %count2%) do (
    set /a "num2=!random! %% 10 + 31"
    set "numbers2=!numbers2!!num2!&"
)

REM 
set "link=file:///C:\Users\Admin\Desktop\git\project\project6.html?"
set "finalLink=%link%!numbers1!!numbers2!"
set "finalLink=!finalLink:~0,-1!" 

REM 
start chrome "%finalLink%"

endlocal
