@echo off
setlocal

set /p pause_option="> Quieres que se generen pausas? [S/N]: " 

cd .\Dependencies
set deps=Bullet CEGUI FMOD LuaBridge Ogre SDL

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

echo:
echo Se va ha proceder a borrar el directorio BUILD de ./Dependencies:
if /i "%pause_option%"=="S" ( pause ) && echo:

rem directorios ./build
for %%i in (%deps%) do (

    rem borrado recursivo del directorio sin añadir confirmación
    rd /s /q .\%%i\build 2>nul && echo - El directorio build de %%i se ha eliminado correctamente || echo - No se ha encontrado el directorio build de %%i

)

echo:
pause
endlocal