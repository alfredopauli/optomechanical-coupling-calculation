#!/bin/bash

set -xe
g++ -Wall -Wextra -o main src/*.cpp -I./include/ -lraylib
./main

