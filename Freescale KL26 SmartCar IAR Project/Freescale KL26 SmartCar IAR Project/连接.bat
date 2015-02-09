@echo off

subst y: /d

subst y: "E:\Freescale KL26SmartCar V2.0\Freescale KL26 SmartCar IAR Project\Freescale KL26 SmartCar IAR Project"

y:

md z:\freescaleV2prjtmp

xcopy Prj_Local z:\freescaleV2prjtmp /E /C /I /F /H /R /Y

mklink /d prj z:\freescaleV2prjtmp


