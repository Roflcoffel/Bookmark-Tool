#!/bin/bash
# Plays the next episode according to bookmark, and increments the value.
# Dep: vlc, bookmark, sel.sh

vlc $(sel.sh $(bookmark list --dir_as_value --value))