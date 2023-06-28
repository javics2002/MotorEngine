@echo off

set "origen=.\Src\lib\Release\" 
set "destino=.\bin\Release\" 

set "origenD=.\Src\lib\Debug\" 
set "destinoD=.\bin\Debug\" 

cd .\Src

msbuild "lua.sln" /p:configuration=Debug
msbuild "lua.sln" /p:configuration=Release

cd..

rem Copia los binarios .dll
robocopy /NJH %origen% %destino% *.dll
robocopy /NJH %origenD% %destinoD% *.dll