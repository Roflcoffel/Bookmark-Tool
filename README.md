# Bookmark Tool

A simple C program for storing and retrieving a key:value pair from the terminal.

#### NAME
bookmark - store a mark tied to a name.

#### SYNOPSIS
bookmark [COMMAND] name:value

#### DESCRIPTION
Creates a name, value pair that is stored in a simple csv file.  
List all bookmarks or search for a specified string.

the **name** is a string, and acts as a key to the **value**.  
the **value** is a number, and is the part you want to remember.  
the **id** is a number, it is the index of a line in the csv file.    

**list** [name]  
lists all bookmarks created, or the best match for a specified **name**,
also displays the **id** of each pair.

**add** name:value  
adds the specified **name:value** pair to the csv file.

**remove** id  
removes the specified pair from the csv file.

**inc** id  
increases the **value** of the pair with the specified **id**

**edit** id:value  
changes the **value** of the pair with the specified **id**

### EXAMPLES
list all bookmarks:  

	bookmark list

add a new bookmark:

	bookmark add wow:1
    
list a specific bookmark:

	bookmark list wow
    
remove a bookmark
 
 	bookmark remove 1

increase a value of a bookmark

	bookmark inc 1

change the value of a bookmark  

	bookmark edit 1:4

### NOTE
When doing an edit, the id comes first then the value.
