@echo off
qcad.exe -no-gui -autostart scripts\Tools\MergeDrawings\MergeDrawings.js %0 %* 1>%temp%\merge.log 2>&1
type %temp%\merge.log
del %temp%\merge.log
