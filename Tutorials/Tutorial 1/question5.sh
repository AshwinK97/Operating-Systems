#!/bin/bash

if [ "$1" == "loop" ];
then
	for i in {1..5}
	do 
		echo $1
		echo $i >> "count.log"
	done
fi

ps > processes.log
