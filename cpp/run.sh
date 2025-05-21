#!/bin/bash

set -xe
g++ -o main src/*.cpp -I./include/ -lraylib
./main

