@echo off
:loop
set /p a=请输入文件名称：
>>Inc\fl_%a%.h echo #include "common.h"
>>Inc\fl_%a%.h echo #include "fl_cfg.h"
>>Inc\fl_%a%.h echo.
>>Inc\fl_%a%.h echo #ifndef _FL_%a%_
>>Inc\fl_%a%.h echo #define _FL_%a%_
>>Inc\fl_%a%.h echo.
>>Inc\fl_%a%.h echo.
>>Inc\fl_%a%.h echo.
>>Inc\fl_%a%.h echo #endif//_FL_%a%_
>>Src\fl_%a%.c echo #include "fl_%a%.h"
pause
goto loop