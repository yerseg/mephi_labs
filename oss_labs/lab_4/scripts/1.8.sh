#!/bin/bash
echo "Процессов пользователя ${USER}:"
ps -u ${USER} | wc -l
echo "Процессов пользователя root:"
ps -u root | wc -l

