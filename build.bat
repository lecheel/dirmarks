@echo off
g++ -o dirmark -std=c++11 dirmarks.cpp
if exist dirmark.exe (
    move dirmark.exe c:\\usr64\bin
    color 2
    echo Done
    color 7
) else (
  color 4
  echo ---> build failed!!!
  color 7
)
echo on

