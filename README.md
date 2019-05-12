# Bookmark Tool

A simple C program for storing and retrieving a mark from the terminal.

#### NAME
bookmark - store a mark tied to a name.

#### SYNOPSIS
bookmark [OPTION] name:value

#### DESCRIPTION
creates a name, value pair that is stored in a simple csv file, list all  
bookmarks or specified.

the *name* is always a string
the *value* is always a number  

**list**  
lists all bookmarks created, or the best match for a specified *name*. 

**add**  
adds the specified *name:value* pair to the csv file.

**remove**  
removes the specified *name* pair from the csv file.

**inc**  
increases the *value* of the provided *name*

### EXAMPLES
list all bookmarks:  

	bookmark list

add a new bookmark:

	bookmark add wow:1
    
list a specific bookmark:

	bookmark list wow
    
remove a bookmark
 
 	bookmark remove wow

increase a value of bookmark

	bookmark inc wow
    
also remember bookmarks return string can easily be piped to awk and grep.