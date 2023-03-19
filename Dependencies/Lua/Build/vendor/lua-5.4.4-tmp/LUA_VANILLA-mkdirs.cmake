# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4"
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4/src/LUA_VANILLA-build"
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4"
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4-tmp"
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4-stamp"
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4"
  "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/34690/OneDrive/Documentos/TERCERODECARRERA/SEGUNDOCUATRIMESTRE/PROYECTOSIII/P3-Motor/Dependencies/Lua/Build/vendor/lua-5.4.4-stamp${cfgdir}") # cfgdir has leading slash
endif()
