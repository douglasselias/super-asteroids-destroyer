@echo off

cls
where /q cl || call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

rmdir /S /Q .\build
mkdir build
pushd .\build

set annoying_warnings=/wd4189 /wd4996 /wd4100 /wd4244 /wd4255 /wd5045 /wd4711 /wd4710 /wd4820

cl /nologo /Z7 /diagnostics:caret /fsanitize=address /Wall /WX /W4 %annoying_warnings% /MD ..\main.c /link ../vendor/raylib.lib

main

popd