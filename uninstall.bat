@echo off
setlocal

rem Configuración de paradas
if /I "%1"=="" (

    set /p pause_option="> Quieres que se generen pausas? [S/N]: "

) else ( set "pause_option=%1" ) 



echo:
echo Se va ha proceder a borrar el directorio EXE de ./root_project:
if /i "%pause_option%"=="S" ( pause ) && echo:

rmdir /s /q .\Exe 2>nul && echo - Borrado el directorio ./Exe || echo - No se ha encontrado el directorio ./Exe 


echo:
echo Se va ha proceder a borrar el directorio LIB de ./root_project:
if /i "%pause_option%"=="S" ( pause ) && echo:

rmdir /s /q .\Lib 2>nul && echo - Borrado el directorio ./Lib || echo - No se ha encontrado el directorio ./Lib 


echo:
echo Se va ha proceder a borrar el directorio TEMP de ./root_project:
if /i "%pause_option%"=="S" ( pause ) && echo:

rmdir /s /q .\Temp 2>nul && echo - Borrado el directorio ./Temp || echo - No se ha encontrado el directorio ./Temp 



rem Proyecto ejecutable MAIN
echo:
echo Se va ha proceder a borrar el directorio ASSETS de ./root_project/Projects/Main/:
if /i "%pause_option%"=="S" ( pause ) && echo:

rmdir /s /q .\Projects\Main\Assets 2>nul && echo - Borrado el directorio ./Projects/Main/Assets || echo - No se ha encontrado el directorio ./Projects/Main/Assets  

if exist "./Projects/Main/*.cfg" ( 
    
    del ./Projects/Main/*.cfg 
    echo - Borrados los ficheros .cfg de ./Projects/Main/ 

) else (
    echo - No se han encontrado los ficheros .cfg de ./Projects/Main/ 
)



echo:
echo Se va ha proceder a borrar el registro general de la build del motor:
if /i "%pause_option%"=="S" ( pause ) && echo:

rem Elimina si existe el anterior registro general del motor
if exist "./build_Output.txt" (

    del "./build_Output.txt"
    echo - Borrado el registro general

) else (
    echo - No se ha encontrado el registro general 
)



echo:
echo Se va ha proceder a borrar el anterior registro de cada dependencia (si existe):
if /i "%pause_option%"=="S" ( pause ) && echo:


rem Establece las dependencias a tener en cuenta
set deps=Bullet CEGUI FMOD LuaBridge Ogre SDL
cd .\Dependencies

rem Borra los registros autogenereados en las dependencias
for %%i in (%deps%) do (

    if exist ".\%%i\build_Output.txt" ( 
        
        rem Elimina el anterior registro
        del ".\%%i\build_Output.txt"
        echo - Borrado el registro de %%i
        
    ) else (
        echo - No se encuentra el registro de %%i
    )

)



rem Borra los directorios autogenerados

rem ./bin
echo:
echo Se va ha proceder a borrar el directorio BIN de ./Dependencies:
if /i "%pause_option%"=="S" ( pause ) && echo:

rem directorios ./bin
for %%i in (%deps%) do (

    if "%%i"=="Bullet" (

        rd /s /q .\%%i\build\lib 2>nul && echo - El directorio bin de %%i se ha eliminado correctamente || echo - No se ha encontrado el directorio bin de %%i

    ) else (
        
        rem borrado recursivo del directorio sin añadir confirmación
        rd /s /q .\%%i\bin 2>nul && echo - El directorio bin de %%i se ha eliminado correctamente || echo - No se ha encontrado el directorio bin de %%i
        
    )

)

rem ./build
echo:
echo Se va ha proceder a borrar el directorio BUILD de ./Dependencies:
if /i "%pause_option%"=="S" ( pause ) && echo:

rem directorios ./build
for %%i in (%deps%) do (

    rem borrado recursivo del directorio sin añadir confirmación
    rd /s /q .\%%i\build 2>nul && echo - El directorio build de %%i se ha eliminado correctamente || echo - No se ha encontrado el directorio build de %%i

)



echo: && pause 
endlocal