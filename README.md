# generic_dynamic_stack_c
generic_dynamic_stack_c

## Declaring a new stack:  
### Syntax:
```c
Stack myStack = new_stack(MAX_SIZE);
```
If you need to limit the size of the stack you can pass an integer value representing the maximum size, however, if you need it to have an unlimited size, you can either keep it empty or pass -1.

## Printing a stack:  
### Syntax:
```c
print_stack(myStack);  
```

## Pushing an element into a stack:  
### Syntax:  
```c
push(myStack, type, element);
```
"type" has to be one the types defined by the enum Type {NONE, INT, FLOAT, CHAR}, "element" can be any variable that has to match types with one of the enum types, you are also able to pass a variable as an element or by directly typing the data.
Examples on pushing:  
```c
push(myStack, INT, 100);
char c = 'L';
push(myStack, CHAR, c);
push(myStack, FLOAT, 3.14);
```
Another way to push an element is using the function "auto_push()", which automatically detects the type of the data that you are passing, however, it has to be written inside a string.  
### Syntax:
```c
auto_push(myStack, "YOUR_DATA_HERE");
```
### Examples:
```c
auto_push(myStack, "10")    // => this will push the integer 10 into the stack.
auto_push(myStack, "35.23") // => this will push the floating point 35.23 into the stack.
auto_push(myStack, "'H'")   // => this will push the character 'H' into the stack.
auto_push(myStack, "H")     // => this will do the same thing as above.
auto_push(myStack, "'0'")   // => this will push the character '0' to the stack.
auto_push(myStack, "0")     // => this will push the integer 0 into the stack unlike the example above.
```
So in a nutshell, here is how to push each type:
- int: If you need to push an integer you just have to input numerals, without including any other type of characters.
- float: If you want to push a floating point, you will just have to include a dot '.' in addition to numerals, no other characters.
- char: For pushing a character you have to include an apostrophy "'" before and after the character, or you can directly type the char, but in cases like numerals it would push an integer instead.

## Popping an element from the stack:
### Syntax: 
```c
pop(myStack);
```
Other than removing the last element, "pop()" also returns it in the form of a Variant, which is a struct that can hold any type of data, to access this return value, you need to declare a new Variant and assign the pop function to it.
### Syntax:
```c
Variant return_value = pop(myStack);
```
The Variant variable can be further used by applying some predefined functions to it like print_variant(), and it is also neccessary to free the Variant when its no longer needed to avoid memory leaks, for that you can use the function "free_variant()".
### Syntax:
```c
Variant myVariant = pop(myStack);
free_variant(myVariant)
```
## Peeking into the stack:
### Syntax:
```c
peek(myStack);
```
Just as "pop()" this will return the last element in the form of a Variant, except it wont actually remove it.

## Checking if a stack is empty/full:
### Syntax:
```c
int result1 = is_empty(myStack); // => will return 1 if empty, 0 if not.
int result2 =  is_full(myStack); // => will return 1 if  full, 0 if not.
```
Pretty self explainatory, "is_empty()" will return 1 if the stack is of size 0 and 1 if the size is greater than 0, on the other hand, "is_full()" will return 1 if the stack's size is equal to its maximum size, and 0 if its size is less than its maximum size.

## Freeing a stack:
After you're done with a stack, it is neccessary to free it to avoid memory leaks.
### Syntax:
```c
free_stack(myStack);
```
