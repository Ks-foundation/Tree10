// calc.c
#include "stdio.h"
#include "string.h"

void calc_main() {
    char input[100];
    int result = 0;

    printf("Simple Calculator\n");
    printf("Usage: [number] [operator] [number]\n");
    printf("Example: 2 + 3\n");

    while (1) {
        printf("calc> ");
        gets(input);
        
        if (strcmp(input, "exit") == 0) {
            break;
        }

        int num1, num2;
        char op;
        sscanf(input, "%d %c %d", &num1, &op, &num2);

        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = (num2 != 0) ? (num1 / num2) : 0;
                break;
            default:
                printf("Invalid operator\n");
                continue;
        }

        printf("Result: %d\n", result);
    }
}
