#!/bin/bash
# Plays the next episode according to bookmark, and increments the value
# Dep: vlc, bookmark, sel

bookmark_value=$(bookmark list --dir_as_name "%.s%.s%.s%d")
book_status=$?

sel_value=$(sel $bookmark_value)
sel_status=$?

if [ $book_status -gt 0 ]
then
	if [ $book_status -eq 127 ]
	then
		echo "bookmark command was not found!"
		exit 127
	else
		echo "bookmark failed!"
		exit 1
	fi
fi

if [ $sel_status -eq 0 ]
then
	if [ $sel_status -eq 127 ]
	then
		echo "sel command was not found!"
		exit 127
	else
		echo "sel failed!"
		exit 1
	fi
fi

id=$(bookmark list --dir_as_name "%d")

vlc $sel_value

bookmark inc $id