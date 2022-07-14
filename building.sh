#!/usr/bin/bash

NORMAL='\033[0m'
BOLD='\033[1m'
GREEN='\033[32m'
RED='\033[31m'
HOME=$(pwd)
IFS=$'\n'

for line in $(find . -name "main.c" | sed -e "s/\/main.c//" | sed -e "s/.\///")
do
	echo -e "${GREEN}${BOLD}Building ${line}...${NORMAL}"
	cd $line
	rm -rf build
	cmake -H. -Bbuild > /dev/null
	touch build/CMakeLog.txt
	cmake --build build 2> build/CMakeLog.txt
	if [ -s build/CMakeLog.txt ]
	then
		cat build/CMakeLog.txt
		echo -e "${RED}${BOLD}Build failed${NORMAL}\n"
	else
		echo -e "${GREEN}${BOLD}Build completed${NORMAL}\n"
	fi
	cd $HOME
done
