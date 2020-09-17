#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -32767

typedef enum{OPERAND, OPERATOR, BLANK} optyp;

typedef struct {
    int data;
    char operator;
    optyp type;
} token;

typedef struct {
    int *stk;
    int top;
} Stack;

token getNextToken(char *str, int *pos){
    //Gives the next token present in the string
    //starting from *pos
    token newToken;

    switch(str[*pos]){
        case ' ':
            newToken.type = BLANK;
            *pos += 1;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
            newToken.operator = str[*pos];
            newToken.type = OPERATOR;
            *pos += 1;
            break;
        default:
            //It is going to be a number
            newToken.data = 0;
            while (str[*pos] >= '0' && str[*pos] <= '9'){
                newToken.data = newToken.data * 10 + str[*pos] - '0';
                *pos += 1;
            }
            newToken.type = OPERAND;
            break;
    }
    return newToken;
}


Stack * createStack(int length){
    //Initialize a stack of given length
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s -> stk = (int *)malloc(length * sizeof(int));
    s -> top = 0;   //Indicates empty stack
    return s;
}

int peek (Stack *stack){
    if (stack -> top > 0)
        return stack -> stk[stack -> top - 1];
    else    //Underflow
        return ERROR;    
}

int pop(Stack *stack){
    if (stack -> top > 0)
        return stack -> stk[--(stack -> top)];
    else    //Underflow
        return ERROR;
}

void push(Stack *stack, int op){
    //We are not checking for overflow because 
    //in any case the number of operators pushed 
    //will not be greater than the string length.
    stack -> stk[(stack -> top)++] = op;
}

int isEmpty(Stack *stack){
    return !(stack -> top);
}

int eval(char *str){
    int pos = 0;
    Stack *s = createStack(strlen(str));
    
    while (pos != strlen(str)){
        token next = getNextToken(str, &pos);
        if (next.type == OPERAND)
            push(s, next.data);
        else if (next.type == OPERATOR){
            int op2 = pop(s);
            int op1 = pop(s);
            switch (next.operator){
                case '+':
                    push(s, op1 + op2);
                    break;
                case '-':
                    push(s, op1 - op2);
                    break;
                case '*':
                    push(s, op1 * op2);
                    break;
                case '/':
                    push(s, op1 / op2);
                    break;
                case '%':
                    push(s, op1 % op2);
                    break;
            }
        }
    }

    return peek(s);
}

int main(){
    FILE *in = fopen("18CS10066_A2_P1_output.txt", "r");
    //FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("18CS10066_A2_P2_output.txt", "w");
    
    char str[50];
    while (!feof(in)){
        str[0] = '\0';
        fgets(str, 50, in);

        printf("%s\n", str);
        if (strlen(str) != 0){
            //printf("%s\n", str);
            str[strlen(str) - 1] = '\0';        //Absorbing the newline
            fprintf(out, "%d\n", eval(str));
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}