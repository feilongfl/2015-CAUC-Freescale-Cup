@echo off
:loop
set /p a=请输入文件名称：
>>Inc\fl_%a%.h echo #include "common.h"
>>Inc\fl_%a%.h echo #include "fl_cfg.h"
>>Src\fl_%a%.c echo #include "fl_%a%.h"
pause
goto loop