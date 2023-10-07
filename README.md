# generic_dynamic_stack_c
generic_dynamic_stack_c

Declaring a new stack:
Syntax: 
- Stack myStack = new_stack(MAX_SIZE);
If you need to limit the size of the stack you can pass an integer value representing the maximum size.
However if you need it to have an unlimited size, you can either keep it empty or pass -1.

Printing a stack:
Syntax:
- print_stack(myStack);

Pushing an element into a stack:
Syntax: push(myStack, type, element); 
"type" has to be one the types defined by the enum Type {NONE, INT, FLOAT, CHAR}.
"element" can be any variable that has to match types with one of the enum types.
you are also able to pass a variable as an element or by directly typing the data.
Examples on pushing: 
- push(myStack, INT, 100);
- char c = 'L';
- push(myStack, CHAR, c);
- push(myStack, FLOAT, 3.14);

Another way to push an element is using the function "auto_push()".
This function automatically detects the type of the data that you are passing.
However it has to be written inside a string.
Syntax:
- auto_push(myStack, "YOUR_DATA_HERE");

Examples:
- auto_push(myStack, "10") => this will push the integer 10 into the stack.
- auto_push(myStack, "35.23") => this will push the floating point 35.23 into the stack.
- auto_push(myStack, "'H'") => this will push the character 'H' into the stack.
- auto_push(myStack, "H") => this will do the same thing as above.
- auto_push(myStack, "'0'") => this will push the character '0' to the stack.
- auto_push(myStack, "0") => this will push the integer 0 into the stack unlike the example above.

So in a nutshell, if you need to push an integer you just have input numerals,
without including any other type of characters.
If you want to push a floating point, you will just have to include a dot '.' in addition to numerals.
For pushing a character you have to include an apostrophy "'" before and after the character,
or you can just leave it without, but in cases like numerals it would push an integer instead.

Popping an element from the stack:
Syntax: 
- pop(myStack);
"pop()" other than removing the last element, pop also returns it in the form of a Variant, 
which is a struct that can hold any type of data, to access this return value,
you need to declare a new Variant and assign the pop function to it.
Syntax:
Variant return_value = pop(myStack);
The Variant variable can be further used by applying some predefined functions to it like print_variant().
It is also neccessary to free the Variant when its no longer needed to avoid memory leaks,
for that you can use the function "free_variant()".
Syntax:
- Variant myVariant = pop(myStack);
- free_variant(myVariant)

Peeking into the stack:
Syntax:
- peek(myStack);
Just as "pop()" this will return the last element in the form of a Variant, 
which is the Variant that is stored in the last node of the stack, except it wont actually remove it.

Checking if a stack is empty/full:
Syntax:
- int result1 = is_empty(myStack); // => will return 1 if empty, 0 if not.
- int result2 =  is_full(myStack); // => will return 1 if  full, 0 if not.

Freeing a stack:
After you're done with a stack, it is neccessary to free it to avoid memory leaks.
Syntax:
- free_stack(myStack);
