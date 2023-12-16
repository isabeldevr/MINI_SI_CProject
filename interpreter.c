#include "interpreter.h"
#define MAX_VARS 100 // Maximum number of variables


Variable variables[MAX_VARS]; // Array to store variables
int variable_count = 0;       // Count of stored variables


// Function to trim whitespace from a string
char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Write new null terminator
    *(end + 1) = '\0';

    return str;
}


// Function to execute the commands
void processNode(ASTNode* root, char* arguments[]){
    switch (root->token.name) {
        case PRINT:
            perform_print(arguments);
            break;
        case SET:
            perform_set(arguments);
            break;
        case ADD:
            perform_add(arguments);
            break;
        case ISEQUAL:
            perform_isequal(arguments);
            break;
        case IFGREATERTHAN:
            perform_ifgreaterthan(arguments);
            break;
        case IFLESSTHAN:
            perform_iflessthan(arguments);
            break;
        case MULTIPLY:
            perform_multiply(arguments);
            break;
        case DIVIDE:
            perform_divide(arguments);
            break;
        case SUBTRACT:
            perform_subtract(arguments);
            break;
        case COMPLAIN:
            perform_complain();
            break;
        default:
            printf("Error, unknown syntax.\n");
            break;
    }
}


// Function to transverse the AST
void interpreter(ASTNode* root){
    if (root == NULL) {
        return;
    }

    if (root->type == ROOT) {
        for (int i = 0; i < root->numChildNodes; i++) {
            ASTNode* child = root->childNodes[i];
            char * arguments[2] = {NULL, NULL};
            if (child->token.type == COMMAND) {
                for (int j = 0; j < child->numChildNodes; j++) {
                    ASTNode* child_of_child = child->childNodes[j];
                    arguments[j] = child_of_child->token.value;
                }
            } else if (child->token.type == MESSAGE_TYPE) {
                arguments[0] = child->token.value;
            }
            processNode(child, arguments);
        }
    }

    freeAST(root);
}




// Functions of individual commands

// Array of complaints
const char* complaints[] = {
        "Complain: Debugging this code is like finding a needle in a haystack.",
        "Complain: I keep getting segmentation faults and have no idea why.",
        "Complain: Why does C not have automatic garbage collection?",
        "Complain: Recompiling again because I missed a semicolon.",
        "Complain: Array indices starting at 0 always trips me up.",
        "Complain: Why are pointers so confusing?",
        "Complain: I thought I understood recursion until I had to use it in a project.",
        "Complain: I miss the simplicity of Python while coding in C.",
        "Complain: Multithreading is hard, race conditions are driving me crazy.",
        "Complain: Why do I have to manually manage memory in C?"
};
const int num_complaints = sizeof(complaints) / sizeof(complaints[0]);


void perform_complain() {
    // Generate a random index (without time-based seeding)
    int index = rand() % num_complaints;
    printf("%s\n", complaints[index]);
}

int is_number(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0; // Not a number
        }
    }
    return 1; // Is a number
}

void perform_print(char* arguments[]) {
    if (arguments[0] == NULL) {
        printf("Error: No argument provided for PRINT command.\n");
        return;
    }

    // Assume initially that the argument is not a variable
    int isVariable = 0;
    int value;

    // Search for the variable in the variables array
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, arguments[0]) == 0) {
            value = variables[i].value;
            isVariable = 1;
            break;
        }
    }

    // Print based on whether it's a variable or not
    if (isVariable) {
        printf("Printing %s: \n%s = %d", arguments[0], arguments[0], value);
    } else {
        printf("Printing: %s\n", arguments[0]);
    }
}


void perform_set(char* arguments[]) {
    // Check if arguments are NULL
    if (arguments[0] == NULL || arguments[1] == NULL) {
        printf("Error: Missing arguments in SET command.\n");
        return;
    }

    // Check if the variable name is too long
    if (strlen(arguments[0]) >= sizeof(variables[0].name)) {
        printf("Error: Variable name '%s' is too long.\n", arguments[0]);
        return;
    }

    // Check if variable with the same name already exists
    for (int i = 0; i < variable_count; i++) {
        if (strcmp(variables[i].name, arguments[0]) == 0) {
            // Variable exists, update its value
            variables[i].value = atoi(arguments[1]);
            printf("Variable '%s' updated to %d.\n", variables[i].name, variables[i].value);
            return;
        }
    }

    // Check if we have reached the maximum number of variables
    if (variable_count >= MAX_VARS) {
        printf("Error: Variable storage limit reached.\n");
        return;
    }

    // Add new variable
    strcpy(variables[variable_count].name, arguments[0]);
    variables[variable_count].value = atoi(arguments[1]);
    printf("Variable '%s' set to %d.\n", variables[variable_count].name, variables[variable_count].value);

    variable_count++;
}

void perform_add(char* arguments[]) {
    // Check if arguments are valid
    if (arguments[0] == NULL || arguments[1] == NULL) {
        printf("Error: Missing arguments for ADD command.\n");
        return;
    }

    // Trim whitespace from both arguments
    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    int var1, var2;
    int foundVar1 = 0, foundVar2 = 0;

    // Check if the first argument is a number
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        // Check if it's a variable
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        // If not a variable, print error and return
        if (!foundVar1) {
            printf("Error: '%s' is not a valid number or recognized variable.\n", trimmed_arg1);
            return;
        }
    }

    // Check if the second argument is a number
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
    } else {
        // Check if it's a variable
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        // If not a variable, print error and return
        if (!foundVar2) {
            fprintf(stderr, "Error: '%s' is not a valid number or recognized variable.\n", trimmed_arg2);
            printf("Error: '%s' is not a valid number or recognized variable.\n", trimmed_arg2);
            return;
        }
    }

    // Perform addition and print result
    printf("Add: %d + %d = %d\n", var1, var2, var1 + var2);
}


void perform_isequal(char* arguments[]) {
    if (arguments[0] == NULL || arguments[1] == NULL) {
        printf("Error: Missing arguments for ISEQUAL command.\n");
        return;
    }

    // Trim whitespace from both arguments
    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    int var1, var2;
    int foundVar1 = 0, foundVar2 = 0;

    // Check if the first argument is a number or a variable
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        if (!foundVar1) {
            printf("Error: Variable '%s' not found.\n", trimmed_arg1);
            return;
        }
    }

    // Check if the second argument is a number or a variable
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        if (!foundVar2) {
            printf("Error: Variable '%s' not found.\n", trimmed_arg2);
            return;
        }
    }

    // Perform the comparison
    if (var1 == var2) {
        printf("IsEqual: %d == %d\n", var1, var2);
    } else {
        printf("IsEqual: %d NOT EQUAL %d\n", var1, var2);
    }
}

void perform_ifgreaterthan(char* arguments[]) {
    if (arguments[0] == NULL || arguments[1] == NULL) {
        fprintf(stderr, "Error: Missing arguments for IFGREATERTHAN command.\n");
        return;
    }

    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    int var1 = 0, var2 = 0;
    int foundVar1 = 0, foundVar2 = 0;

    // Check for first argument
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        if (!foundVar1) {
            fprintf(stderr, "Error: Argument 1 ('%s') is not a valid number or recognized variable.\n", trimmed_arg1);
            return;
        }
    }

    // Check for second argument
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        if (!foundVar2) {
            fprintf(stderr, "Error: Argument 2 ('%s') is not a valid number or recognized variable.\n", trimmed_arg2);
            return;
        }
    }

    // Perform the comparison
    if (var1 > var2) {
        printf("Condition True: %d is greater than %d\n", var1, var2);
    }
    else {
        printf("Condition False: %d is not greater than %d\n", var1, var2);
    }
}

void perform_iflessthan(char* arguments[]){
    if (arguments[0] == NULL || arguments[1] == NULL) {
        fprintf(stderr, "Error: Missing arguments for IFGREATERTHAN command.\n");
        return;
    }

    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    int var1 = 0, var2 = 0;
    int foundVar1 = 0, foundVar2 = 0;

    // Check for first argument
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        if (!foundVar1) {
            fprintf(stderr, "Error: Argument 1 ('%s') is not a valid number or recognized variable.\n", trimmed_arg1);
            return;
        }
    }

    // Check for second argument
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        if (!foundVar2) {
            fprintf(stderr, "Error: Argument 2 ('%s') is not a valid number or recognized variable.\n", trimmed_arg2);
            return;
        }
    }

    // Perform the comparison
    if (var1 < var2) {
        printf("Condition True: %d is less than %d\n", var1, var2);
    }
    else {
        printf("Condition False: %d is not less than %d\n", var1, var2);
    }
}


void perform_multiply(char* arguments[]) {
    if (arguments[0] == NULL || arguments[1] == NULL) {
        fprintf(stderr, "Error: Missing arguments for MULTIPLY command.\n");
        return;
    }

    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    // Check if arguments are empty after trimming
    if (trimmed_arg1[0] == '\0' || trimmed_arg2[0] == '\0') {
        fprintf(stderr, "Error: Invalid arguments for MULTIPLY command.\n");
        return;
    }

    int var1, var2;
    int foundVar1 = 0, foundVar2 = 0;

    // Check if the first argument is a number or a variable
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        if (!foundVar1) {
            fprintf(stderr, "Error: '%s' is not a valid number or recognized variable.\n", trimmed_arg1);
            return;
        }
    }

    // Check if the second argument is a number or a variable
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        if (!foundVar2) {
            fprintf(stderr, "Error: '%s' is not a valid number or recognized variable.\n", trimmed_arg2);
            return;
        }
    }

    // Perform the multiplication
    printf("Multiply: %d * %d = %d\n", var1, var2, var1 * var2);
}

void perform_divide(char* arguments[]) {
    if (arguments[0] == NULL || arguments[1] == NULL) {
        fprintf(stderr, "Error: Missing arguments for DIVIDE command.\n");
        return;
    }

    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    // Check if arguments are empty after trimming
    if (trimmed_arg1[0] == '\0' || trimmed_arg2[0] == '\0') {
        fprintf(stderr, "Error: Invalid arguments for DIVIDE command.\n");
        return;
    }

    int var1 = 0, var2 = 0; // Initialize variables with default values
    int foundVar1 = 0, foundVar2 = 0;

    // Check if the first argument is a number or a variable
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        if (!foundVar1) {
            fprintf(stderr, "Error: Argument 1 ('%s') is not a valid number or recognized variable.\n", trimmed_arg1);
            return;
        }
    }

    // Check if the second argument is a number or a variable
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
        if (var2 == 0) {
            fprintf(stderr, "Error: Division by zero is not allowed.\n");
            return;
        }
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        if (!foundVar2) {
            fprintf(stderr, "Error: Argument 2 ('%s') is not a valid number or recognized variable.\n", trimmed_arg2);
            return;
        }
        if (var2 == 0) {
            fprintf(stderr, "Error: Division by zero is not allowed.\n");
            return;
        }
    }

    // Perform the division
    int result = var1 / var2;
    printf("Result of division: %d\n", result);
}


void perform_subtract(char* arguments[]) {
    if (arguments[0] == NULL || arguments[1] == NULL) {
        fprintf(stderr, "Error: Missing arguments for SUBTRACT command.\n");
        return;
    }

    char* trimmed_arg1 = trim_whitespace(arguments[0]);
    char* trimmed_arg2 = trim_whitespace(arguments[1]);

    // Check if arguments are empty after trimming
    if (trimmed_arg1 == NULL || trimmed_arg2 == NULL || trimmed_arg1[0] == '\0' || trimmed_arg2[0] == '\0') {
        fprintf(stderr, "Error: Invalid arguments for SUBTRACT command.\n");
        return;
    }

    int var1 = 0, var2 = 0; // Initialize variables with default values
    int foundVar1 = 0, foundVar2 = 0;

    // Check if the first argument is a number or a variable
    if (is_number(trimmed_arg1)) {
        var1 = atoi(trimmed_arg1);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg1) == 0) {
                var1 = variables[i].value;
                foundVar1 = 1;
                break;
            }
        }
        if (!foundVar1) {
            fprintf(stderr, "Error: Argument 1 ('%s') is not a valid number or recognized variable.\n", trimmed_arg1);
            return;
        }
    }

    // Check if the second argument is a number or a variable
    if (is_number(trimmed_arg2)) {
        var2 = atoi(trimmed_arg2);
    } else {
        for (int i = 0; i < variable_count; i++) {
            if (strcmp(variables[i].name, trimmed_arg2) == 0) {
                var2 = variables[i].value;
                foundVar2 = 1;
                break;
            }
        }
        if (!foundVar2) {
            fprintf(stderr, "Error: Argument 2 ('%s') is not a valid number or recognized variable.\n", trimmed_arg2);
            return;
        }
    }

    // Perform the subtraction
    int result = var1 - var2;
    printf("Result of Subtraction: %d\n", result);
}

