@echo off

mkdir build
pushd build

cl -FC -Zi ..\src\ls2.c /EHsc
popd

