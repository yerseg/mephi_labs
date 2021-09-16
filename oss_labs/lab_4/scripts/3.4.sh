#!/bin/bash
echo "Каталоги:"
ls -al -- "$1" | grep ^d
echo "Обычные файлы:"
ls -al -- "$1" | grep ^-
echo "Символьные ссылки:"
ls -al -- "$1" | grep ^l
echo "Символьные устройства:"
ls -al -- "$1" | grep ^c
echo "Блочные устройства:"
ls -al -- "$1" | grep ^b
