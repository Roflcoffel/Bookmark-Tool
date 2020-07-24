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
the **format** is a c-style format string.  

**list** [name]  
lists all bookmarks created, or the best match for a specified **name**,
also displays the **id** of each pair.

**list** [name] **format**  
lists the best match for a specified **name**,  
and formats it according to **format** see notes for more info.

**add** name:value  
adds the specified **name:value** pair to the csv file.

**remove** id  
removes the specified pair from the csv file.

**inc** id  
increases the **value** of the pair with the specified **id**.

**edit** id:value  
changes the **value** of the pair with the specified **id**.

**undo**  
reverses the effect of the previous command.

### EXAMPLES
list all bookmarks:  

	bookmark list
	0 : default -> 0
	1 : wow     -> 1

add a new bookmark:

	bookmark add wow:1
	Added:
    	-> wow
    	-> 1
    
list a specific bookmark:

	bookmark list wow
	1 : wow -> 1

get only the id from a bookmark:  

	bookmark list wow "%d"
	1
    
remove a bookmark
 
 	bookmark remove 1
	Removed:
		-> wow

increase a value of a bookmark

	bookmark inc 1
	Increased:
		-> wow
		-> 2

change the value of a bookmark  

	bookmark edit 1:4
	Changed:
		-> wow
		-> 4

### NOTE
When doing an edit, the id comes first then the value.  
  
When using a **format**, the order of the variables are **id**, **padding**, **key**, **value**.  
the default format is "%d : %-*s -> %d\n".  
  
**padding** replaces the * in %-*s with a number, which adds padding to the right of the **key**.

use **%.s** to print any of the four variables as an empty string, so you can extract different parts of the ouput  
ex. to just get the value do: **"%.s%.s%.s%d"**  
  
if the **format** is malformed, this will likely result in a **segmentation fault**.
  
if you use the flag --dir-as-name, all underscores are always replaced with spaces.  
So you can use underscores in directory names.  