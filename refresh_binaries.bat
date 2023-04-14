@echo off
setlocal


rem Plataforma destino: 
set "platform=x64"


rem Copia iterativa de las .dll's a través del directorio .\Dependencies y sus subdirectorios: 

set "origen=.\Dependencies\*" 
set "destino=.\Exe\Main\%platform%" 

for /d %%d in (%origen%) do (

    if exist "%%d\bin\Debug" (
        robocopy /NJH "%%d\bin\Debug" "%destino%\Debug" "*.dll"
        if /i "%pause_option%"=="S" ( pause )
    )

    if exist "%%d\bin\Release" (
        robocopy /NJH "%%d\bin\Release" "%destino%\Release" "*.dll"
        if /i "%pause_option%"=="S" ( pause )
    )    

)


endlocal 
exit 