#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{OPERAND, OPERATOR} optyp;

typedef struct {
    int data;
    char operator;
    int precedence;
    optyp type;
} token;

int precedence(char op){
    //Gives the absolute precedence value of an operator
    switch(op){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '(':
        case ')':
            return 3;
    }
}

//No need to implement isOperand because this is being
//done by the getNextToken function itself
token getNextToken(char *str, int *pos){
    //Gives the next token present in the string
    //starting from *pos
    token newToken;

    switch(str[*pos]){
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
            newToken.operator = str[*pos];
            newToken.type = OPERATOR;
            newToken.precedence = precedence(str[*pos]);
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

typedef struct {
    char *stk;
    int top;
} Stack;

Stack * createStack(int length){
    //Initialize a stack of given length
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s -> stk = (char *)malloc(length * sizeof(char));
    s -> top = 0;   //Indicates empty stack
    return s;
}

char peek (Stack *stack){
    if (stack -> top > 0)
        return stack -> stk[stack -> top - 1];
    else    //Underflow
        return '\0';    
}

char pop(Stack *stack){
    if (stack -> top > 0)
        return stack -> stk[--(stack -> top)];
    else    //Underflow
        return '\0';
}

void push(Stack *stack, char op){
    //We are not checking for overflow because 
    //in any case the number of operators pushed 
    //will not be greater than the string length.
    stack -> stk[(stack -> top)++] = op;
}

int isEmpty(Stack *stack){
    return !(stack -> top);
}

char * toRevPol(char *str){
    int len = strlen(str);
    char *ans = (char *)malloc(sizeof(char) * 3 * len);
    ans[0] = '\0';
    char buff[50];
    Stack *s = createStack(len);

    int pos = 0;
    token next;
    while (str[pos] != '\0'){
        next = getNextToken(str, &pos);
        if (next.type == OPERAND){
            sprintf(buff, "%d ", next.data);
            strcat(ans, buff);
        }else{
            if (next.operator == '(')
                push(s, next.operator);
            else if (next.operator == ')'){
                while (peek(s) != '(' && !isEmpty(s)){
                    sprintf(buff, "%c ", pop(s));
                    strcat(ans, buff);
                }
                pop(s);
            }else if (isEmpty(s) || precedence(peek(s)) < next.precedence)
                push(s, next.operator);
            else{
                while (precedence(peek(s)) >= next.precedence && !isEmpty(s)){
                    if (peek(s) != '('){
                        sprintf(buff, "%c ", pop(s));
                        strcat(ans, buff);
                    }else{
                        pop(s);
                        break;
                    }
                }
                push(s, next.operator);
            }
        }
    }

    while(!isEmpty(s)){
        sprintf(buff, "%c ", pop(s));
        strcat(ans, buff);
    }

    return ans;
}
int main(){
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("18CS10066_A2_P1_output.txt", "w");
    
    char str[50];
    while (!feof(in)){
        fscanf(in, "%s", str);
        fprintf(out, "%s\n", toRevPol(str));
        fgetc(in);
    }

    fclose(in);
    fclose(out);
    return 0;
}

