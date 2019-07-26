//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//--------------------------------------------------------------------------------------------------------------
//stack for converting into RPN 
struct stack_node
{
  char data;
  struct stack_node* next;
};

struct stack_node* new_node(char c)
{
  struct stack_node* new_;
  new_ = (struct stack_node*)malloc(sizeof(struct stack_node));
  new_->data = c;
  new_->next = NULL;
  return new_;
}

int isEmpty(struct stack_node* stack)
{
  if(stack == NULL)
    return 1;
  else
    return 0;
}

void push(struct stack_node** stack,char c)
{
  struct stack_node* new_;
  new_ = new_node(c);
  new_->next = *stack;
  *stack = new_;
}

char pop(struct stack_node** stack)
{
  if(isEmpty(*stack)) //empty stack nothing to pop
    return 'N';
  char c;
  struct stack_node* temp;
  temp = *stack;
  c = (*stack)->data;
  (*stack) = (*stack)->next;
  free(temp);
  return c;
}

char peek(struct stack_node* stack)
{
  if(isEmpty(stack)) //empty stack nothing to peek
    return 'N';
  char c;
  c = stack->data;
  return c;
}
int precedence(char c)
{
  if((c == '(')||(c == ')'))
    return 3;
  else if((c == '/')||(c == '*')||(c == '%'))
    return 2;
  else if((c == '+')||(c == '-'))
    return 1;
  else
    return 0;
}

int isOperand(char* input)
{
  int i,digits;
  i=0;
  while((input[i] >= '0') && (input[i] <= '9'))
  {
    i++;
  }
  digits = i;
  return digits;
}
void convert(char* input,char* output)
{
  struct stack_node* stack;
  stack = NULL;
  int i,j,digits,k;
  char c;
  i = 0;
  j = 0;
  while(input[i] != '\0')
  {
   if(precedence(input[i]) == 0) //operand
    {
      digits = isOperand(&input[i]);
      for(k=1;k <= digits ;k++)
      {
        output[j] = input[i];
        i++;
        j++;
      }
      output[j] = ' ';
      j++;
    }
    else if((precedence(input[i]) == 2) || (precedence(input[i]) == 1)) //operator
    {
      if(isEmpty(stack))
      {
        push(&stack,input[i]);
        i++;
      }
      else
      {
        c = peek(stack);
        if(precedence(c) == 3)
        {
          push(&stack,input[i]);
          i++;
        }
        else if(precedence(input[i]) <= precedence(c))
        {
          c = pop(&stack);
          push(&stack,input[i]);
          output[j] = c;
          j++;
          i++;
          output[j] = ' ';
          j++;
        }
        else
        {
          push(&stack,input[i]);
          i++;
        }
      }
    }
    else if(input[i] == '(') // left parenthesis
    {
      push(&stack,input[i]);
      i++;
    }
    else if(input[i] == ')') // right parenthesis
    {
      i++;
      while(peek(stack) != '(')
      {
          c = pop(&stack);
          output[j] = c;
          j++;
          output[j] = ' ';
          j++;
      }
       c = pop(&stack);
    }
  }
  while(!isEmpty(stack))
    {
       c = pop(&stack);
       output[j] = c;
       j++;
       output[j] = ' ';
       j++;
    }
    output[j] = '\0';
}
//--------------------------------------------------------------------------------------------------------------
//stack1 for evaluating RPN 
struct stack_node1
{
  int data;
  struct stack_node1* next;
};

struct stack_node1* new_node1(int c)
{
  struct stack_node1* new_;
  new_ = (struct stack_node1*)malloc(sizeof(struct stack_node1));
  new_->data = c;
  new_->next = NULL;
  return new_;
}

int isEmpty1(struct stack_node1* stack1)
{
  if(stack1 == NULL)
    return 1;
  else
    return 0;
}

void push1(struct stack_node1** stack1,int c)
{
  struct stack_node1* new_;
  new_ = new_node1(c);
  new_->next = *stack1;
  *stack1 = new_;
}

int pop1(struct stack_node1** stack1)
{
  if(isEmpty1(*stack1)) //empty stack nothing to pop
    return INT_MIN;
  int c;
  struct stack_node1* temp;
  temp = *stack1;
  c = (*stack1)->data;
  (*stack1) = (*stack1)->next;
  free(temp);
  return c;
}

int peek1(struct stack_node1* stack1)
{
  if(isEmpty1(stack1)) //empty stack nothing to peek
    return INT_MIN;
  int c;
  c = stack1->data;
  return c;
}

int isOperator(char c)
{
  if((c == '/')||(c == '-')||(c == '+')||(c == '*')||(c == '%'))
    return 1;
  else
    return 0;
}

int evaluate(char *rpn)
{
  struct stack_node1* stack1;
  stack1 = NULL;
  int i,j,a,b,digits,extract,res;
  i = 0;
  while(rpn[i] != '\0')
  {
    if((rpn[i] >= '0') && (rpn[i] <= '9'))
    {
      digits = isOperand(&rpn[i]);
      extract = 0;
      for(j=1; j <= digits ;j++)
      {
        extract = extract*10 + (int)rpn[i] - (int)('0');
        i++;
      }
      push1(&stack1,extract);
    }
    else if(isOperator(rpn[i]))
    {
       a = pop1(&stack1);
       b = pop1(&stack1);
       if(rpn[i] == '+')
        res = a+b;
       else if(rpn[i] == '/')
        res = b/a;
       else if(rpn[i] == '%')
        res = b%a;
       else if(rpn[i] == '-')
        res = b-a;
       else if(rpn[i] == '*')
        res = a*b;
      push1(&stack1,res);
      i++;
    }
    else if(rpn[i] == ' ')
     i++;
  }
  return pop1(&stack1);
}
//--------------------------------------------------------------------------------------------------------------
int main()
{
  char input[100],rpn[100];
  int value;
  printf("Enter arithmetic expression   : ");
  scanf("%s",input);      // taking arithmetic expression string as input
  convert(input,rpn);     //converting into RPN
  printf("Reverse-Polish Notation (RPN) : ");
  printf("%s\n",rpn); 
  value = evaluate(rpn);  //evaluating RPN
  printf("Value after evaluating RPN    : ");
  printf("%d\n",value);
  return 0;
}

