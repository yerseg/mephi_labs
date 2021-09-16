#!/bin/bash
echo "Домашний каталог пользователя 
${USER} 
содержит 
-обычных файлов: "
find ~ -maxdepth 1 -type f -not -name ".*" | wc -l
echo "-скрытых файлов: "
find ~ -maxdepth 1 -type f -name ".*" | wc -l

