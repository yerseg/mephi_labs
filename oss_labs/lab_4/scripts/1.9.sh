#!/bin/bash
ps -eo cmd,%mem --sort=-%mem | head -n 6
