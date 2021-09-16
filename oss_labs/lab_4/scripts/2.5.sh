#!/bin/bash
find ~ -maxdepth 1 -type f -name "*.txt" -exec basename {} \;

find ~ -maxdepth 1 -type f -name "*.txt" | xargs du | cut -f1 > /tmp/help.txt

cat /tmp/help.txt | (
sum=0
while read n
do
	sum=$(($sum+$n))
done
echo $sum
)

find ~ -maxdepth 1 -type f -name "*.txt" | xargs wc -l | tr -s ' ' | cut -d' ' -f2 > /tmp/help.txt

cat /tmp/help.txt | (
sum=0
while read n
do
	sum=$(($sum+$n))
done
echo $sum
)

rm /tmp/help.txt

