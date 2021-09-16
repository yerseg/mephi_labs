#!/bin/bash
while (true)
do
	read STR < ~/fifo1
	echo "$STR"
	sleep 1
done
