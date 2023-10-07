#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 22

#define push(stack, type, var) ({\
    if(type == INT) {\
        int* var_pointer = (int*)malloc(sizeof(int));\
        *var_pointer = var;\
        push_base(stack, (void*)var_pointer, INT);\
    } else if(type == FLOAT) {\
        float* var_pointer = (float*)malloc(sizeof(float));\
        *var_pointer = var;\
        push_base(stack, (void*)var_pointer, type);\
    } else if(type == CHAR) {\
        char* var_pointer = (char*)malloc(sizeof(char));\
        *var_pointer = var;\
        push_base(stack, (void*)var_pointer, CHAR);\
    }\
})

#define free_variant(var) free_variant_base(&var)

#define new_stack(max) new_stack_base((max+0 > 0 ? max : -1))

#define newline printf("\n")

#define clear_string(X) memset(X, 0, BUFFER_SIZE)

#define remove_last(str) str[strlen(str)-1] = '\0'

enum Type {NONE, INT, FLOAT, CHAR}; 

typedef struct {
    int type;
    void* value;
} Variant;

typedef struct Node {
    Variant variant;
    struct Node* next;
} Node;

typedef struct Stack_struct {
    int size;
    int max_size;
    Node* head;
} Stack_struct;

typedef Stack_struct* Stack;

Stack new_stack_base(int max_size) {
    Stack stack = (Stack)malloc(sizeof(Stack_struct));
    stack->size = 0;
    stack->max_size = max_size;
    stack->head = NULL;
    return stack;
}

Node* new_node(void* value, int type, Node* next) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(type > 3 || type < 0) {
        type = NONE;
        value = NULL;
    }
    node->variant.value = value;
    node->variant.type = type;
    node->next = next;
    return node;
}

void free_node(Node* node) {
    free(node->variant.value);
    free(node);
}

int push_base(Stack stack, void* value, int type) {
    if(stack->size >= stack->max_size && stack->max_size != -1) return 0;
    Node* node = new_node(value, type, NULL);

    if(stack->size <= 0) {
        stack->head = node;
        stack->size = 1;
        return 1;
    }

    Node* curr = stack->head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = node;
    stack->size++;
    return 1;
}

Variant node_to_variant(Node* node) {
    Variant result;
    result.type = node->variant.type;
    switch(result.type) {
        case INT:
            result.value = malloc(sizeof(int));
            memcpy(result.value, node->variant.value, sizeof(int));
            break;
        case FLOAT:
            result.value = malloc(sizeof(float));
            memcpy(result.value, node->variant.value, sizeof(float));
            break;
        case CHAR:
            result.value = malloc(sizeof(char));
            memcpy(result.value, node->variant.value, sizeof(char));
            break;
        default:
            result.value = NULL;
    }
    return result;
}

Variant pop(Stack stack) {
    Variant result = {NONE, NULL};
    if(stack->size <= 0) return result;
    Node* curr = stack->head;
    if(curr->next == NULL) {
        result = node_to_variant(curr);
        free_node(curr);
        stack->head = NULL;
        stack->size--;
        return result;
    }
    while(curr->next->next != NULL) {
        curr = curr->next;
    }
    result = node_to_variant(curr->next);
    free_node(curr->next);
    curr->next = NULL;
    stack->size--;
    return result;
}

Variant peek(Stack stack) {
    Variant result = {NONE, NULL};
    if(stack->size <= 0) return result;
    Node* curr = stack->head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    result = node_to_variant(curr);
    return result;
}

int is_empty(Stack stack) {
    return stack->size <= 0;
}

int is_full(Stack stack) {
    return (stack->size >= stack->max_size && stack->max_size != -1);
}

void free_stack(Stack stack) {
    Node* curr = stack->head;
    for(int i = 0; i < stack->size; i++) {
        Node* tmp = curr;
        curr = curr->next;
        free_node(tmp);
    }
    free(stack);
}

void print_stack(Stack stack) {
    if(stack->size <= 0) {
        printf("[]\n");
        return;
    }
    Node* curr = stack->head;
    printf("[");
    while(curr != NULL) {
        if(curr->variant.type == INT) {
            printf("%d", *(int*)curr->variant.value);
        } 
        else if(curr->variant.type == FLOAT) {
            printf("%.3f", *(float*)curr->variant.value);
        } 
        else if(curr->variant.type == CHAR) {
            printf("'%c'", *(char*)curr->variant.value);
        }
        else {
            printf("NONE");
        }
        if(curr->next != NULL){
            printf(", ");
        } else {
            printf("]\n");
        }
        curr = curr->next;
    }
}

void print_variant(Variant variant) {
    if(variant.type == INT) {
            printf("%d", *(int*)variant.value);
        } 
        else if(variant.type == FLOAT) {
            printf("%.3f", *(float*)variant.value);
        } 
        else if(variant.type == CHAR) {
            printf("'%c'", *(char*)variant.value);
        }
        else {
            printf("NONE");
        }
}

void free_variant_base(Variant* var) {
    free(var->value);
    var->value = NULL;
    var->type = NONE;
}

void dashes(int n) {
    for(int i = 0; i < n; i++) printf("-");
    printf("\n");
}

void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int only_numerals(char str[]) {
    int i = 0;
    while(str[i] != '\0' && str[i] != '\n') {
        if(str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

int only_numerals_and_dot(char str[]) {
    int i = 0;
    while(str[i] != '\0'&& str[i] != '\n') {
        if((str[i] < '0' && str[i] != '.') || str[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

void display_stack(Stack stack) {
    newline;
    dashes(20);
    printf("Your stack: (Current size: %d)", stack->size);
    if(stack->max_size > 0) {
        printf("(max size: %d)\n", stack->max_size);
    } else {
        printf("(max size: not limited)\n");
    }
    print_stack(stack);
    dashes(20);
    newline;
}

int take_max_element() {
    int choice;
    take_max_elements:
    printf("Enter the maximum number of elements (0 for a non-limited stack): ");
    if(scanf("%d", &choice) < 1) {
        printf("Invalid input...\n");
        flush();
        goto take_max_elements;
    }
    if(choice < 0) {
        printf("Number of elements has to be at least 0...\n");
        flush();
        goto take_max_elements;
    }
    flush();
    return choice;
}

int take_type() {
    int choice;
    take_type:
    printf("\nEnter the type of the element:\n");
    printf("1- Integer.\n");
    printf("2- Floating point.\n");
    printf("3- Character.\n");
    printf("Your choice: ");
    if(scanf("%d", &choice) < 1 || (choice > 3 || choice < 1)) {
        printf("Invalid input...\n");
        flush();
        goto take_type;
    }
    flush();
    return choice;
}

int is_valid_char(char str[]) {
    return strlen(str) == 3 && str[0] == '\'' && str[2] == '\'' && str[1] >= ' ' && str[1] <= '~';
}

int is_non_numeral(char str[]) {
    return strlen(str) == 1 && ((str[0] >= ' ' && str[0] <= '/') || (str[0] >= ':' && str[0] <= '~'));
}

int auto_push(Stack stack, char input[]) {
    if(stack->size >= stack->max_size && stack->max_size != -1) {
        printf("\nThe stack has reached the maximum capacity...\n");
    }
    else if(is_non_numeral(input)) {
        char c = input[0];
        push(stack, CHAR, c);
    }
    else if(is_valid_char(input)) {
        char c = input[1];
        push(stack, CHAR, c);
    }
    else if(only_numerals(input)) {
        int number = atoi(input);
        push(stack, INT, number);
    }
    else if(only_numerals_and_dot(input)) {
        float number = atof(input);
        push(stack, FLOAT, number);
    }
    else {
        return 0;
    }
    return 1;
}

void take_element_input_and_push(Stack stack, char buffer[]) {
    take_element_input_and_push:
    printf("\nIf you wish to push an integer, enter only numerals: {0-9}, if you wish to push a float, include a \".\" in your input, if you wish to push a char, include an apostrophy \"'\" before and after the element.\n");
    printf("\nEnter the value of the element: ");
    clear_string(buffer);
    fgets(buffer, BUFFER_SIZE-2, stdin);
    remove_last(buffer);
    if(!auto_push(stack, buffer)) {
        printf("\nInvalid input...\n");
        goto take_element_input_and_push;
    }
}

void display_operations() {
    printf("\nPick an operation:\n");
    printf("1- Push.\n");
    printf("2- Pop.\n");
    printf("3- Peek.\n");
    printf("4- Check if empty.\n");
    printf("5- Check if full.\n");
    printf("0- Exit.\n");
    printf("Your choice: ");
}

int take_operation() {
    int choice;
    take_operation:
    display_operations();
    if(scanf("%d", &choice) < 1 || (choice > 5 || choice < 0)) {
        printf("Invalid input...\n");
        flush();
        goto take_operation;
    }
    flush();
    return choice;
}

void display_pop_ele(Variant var, int size) {
    if(size <= 0) {
        printf("\nYou can't pop from an empty stack...\n");
    } else {
        printf("\nPopped the element: ");
        print_variant(var);
        newline;
    }
}

void display_peek_ele(Variant var, int size) {
    if(size <= 0) {
        printf("\nThere are no elements to peek...\n");

    } else {
        printf("\nPeeked the element: ");
        print_variant(var);
        newline;
    }
}

void display_is_empty(int is_empty) {
    if(is_empty) {
        printf("\nThe stack is indeed empty...\n");
    } else {
        printf("\nThe stack is not empty...\n");
    }
}

void display_is_full(int is_full) {
    if(is_full) {
        printf("\nThe stack is indeed full...\n");
    } else {
        printf("\nThe stack is not full...\n");
    }
}

int main() {
    int size;
    int status;
    Variant variant;
    char buffer[BUFFER_SIZE];
    int max_size = take_max_element();
    Stack main_stack = new_stack(max_size);

    start:
    display_stack(main_stack);
    int operation = take_operation();
    switch(operation) {
        case 0:
            free_stack(main_stack);
            printf("\n\nFarewell...\n\n");
            return 0;
        case 1:
            goto push;
        case 2:
            goto pop;
        case 3:
            goto peek;
        case 4:
            goto is_empty;
        case 5:
            goto is_full;
    }

    push:
    take_element_input_and_push(main_stack, buffer);
    goto start;

    pop:
    size = main_stack->size;
    variant = pop(main_stack);
    display_pop_ele(variant, size);
    free_variant(variant);
    goto start;

    peek:
    size = main_stack->size;
    variant = peek(main_stack);
    display_peek_ele(variant, size);
    free_variant(variant);
    goto start;

    is_empty:
    status = is_empty(main_stack);    
    display_is_empty(status);
    goto start;

    is_full:
    status = is_full(main_stack);    
    display_is_full(status);
    goto start;
}
