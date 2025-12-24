#!/bin/bash

cd build

cmake ..
make

cd bin

while getopts "vs" opt; do
    case $opt in
        v)
            valgrind --leak-check=full --suppressions=../../opengl.supp ./Renderer
            ;;
        s)
            ./Renderer
            ;;
    esac
done
