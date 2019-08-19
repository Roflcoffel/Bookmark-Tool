# Bookmark Tool

A simple C program for storing and retrieving a key:value pair from the terminal.

#### NAME
bookmark - store a mark tied to a name.

#### SYNOPSIS
bookmark [COMMAND] name:value

#### DESCRIPTION
Creates a name, value pair that is stored in a simple csv file.  
List all bookmarks or search for a specified string.

the *name* is always a string
the *value* is always a number

**list** *[name]*  
lists all bookmarks created, or the best match for a specified *name*. 

**add** *name:value*  
adds the specified *name:value* pair to the csv file.

**remove** *name*  
removes the specified *name* pair from the csv file.

**inc** *name*  
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