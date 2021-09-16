#!/bin/bash

cd CheckSum

javac -sourcepath src -d bin -classpath ../commons-codec-1.8.jar src/com/yerseg/checksum/CheckSum.java src/com/yerseg/checksum/UserMode.java src/com/yerseg/checksum/InteractiveMode.java src/com/yerseg/checksum/SimpleMode.java

java -classpath bin:../ com.yerseg.checksum.CheckSum

mkdir lib

cd lib

jar -xvf ../../commons-codec-1.8.jar org/

cd ..

cp -r bin/* lib/

jar -cef com.yerseg.checksum.CheckSum  ../checksum.jar  -C lib .

rm -r lib
