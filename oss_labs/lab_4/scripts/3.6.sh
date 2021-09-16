#!/bin/bash
echo "$USER" "$HOME" "$(($(expr length "$USER") + $(expr length "$HOME")))"
