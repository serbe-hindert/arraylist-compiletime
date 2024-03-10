# arraylist
C23 compliant

(nerd version)
arraylist datastructure for datatype known at compile time via macros.
For datatypes only known during the runtime look at https://github.com/serbe-hindert/arraylist-runtime

## IMPORTANT: needs stdlib.h include, or some different implementations of malloc, realloc and free to function!!! These are not automatically included!
Affected are all the create and destroy functions, that use the heap for at least the elements field in the arraylist structure.

## Link library like
```
add_executable(your_project_name main.c /path/to/header/arraylist-compiletime.h)
```
