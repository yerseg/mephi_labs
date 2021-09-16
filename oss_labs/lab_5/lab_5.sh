#!/bin/bash
ps -eo euid,ruid,comm | tail -n +2 >temp.out #tail чтобы не учитывать строку "EUID RUID COMMAND"
exec 0<temp.out
while read euid ruid command
do
	if [[ $euid != $ruid ]]; then
		echo "process $command's euid differs from ruid"
	fi
done
rm temp.out
