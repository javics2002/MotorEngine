@echo off 

set "RootDirectory=%CD%" 
set "zip=.\7zip\7za.exe" 

:loop

echo "El siguiente programa crear una copia comprimida o descomprida del origen de recursos definido."
set /p source="> Defina la ruta [./ruta/origen] : " 
set /p action="> Que accion desea aplicar? [com = comprimir / des = descomprimir] : " 

if "%action%"=="com" ( 

    %zip% a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on %source%.7z %source%/* 

) else if "%action%"=="des" ( 

    %zip% x %source%.7z -o%source% 

) 

set /p continue_option="> Desea continuar? [S/N]: "

if /i "%continue_option%"=="S" ( 
    
    cls
    goto loop 
    
) else ( 
    
    echo "Saliendo del programa..."
    pause 
    
)