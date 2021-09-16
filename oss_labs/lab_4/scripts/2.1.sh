#!/bin/bash
date +"%d.%m.%y  %H:%M" >> /tmp/run.log
echo 'Hello, World!'
cat /tmp/run.log | wc -l >&2

