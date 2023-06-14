@echo off
set EXES=.\..\..\Exe

cd .\Src

msbuild "lua.sln" /p:configuration=Debug
msbuild "lua.sln" /p:configuration=Release

rem XCOPY /y /s .\lib\Debug\lua_d.dll %EXES%
rem XCOPY /y /s .\lib\Release\lua.dll %EXES%

pause