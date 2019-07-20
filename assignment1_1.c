//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<time.h>

int n; //global
struct node
{
  int data;
  struct node *xor_;
};
//---------------------------------------------------------------------------------------
// Bubble sort - without changing data field of any node
void sort_linked_list(struct node **head,struct node **tail)
{
   struct node *prev,*curr,*next;
   int i,j;
   for(i=1;i<n;i++)
   {
     curr = *head;
     next = (curr->xor_);
     prev = NULL;
     for(j=1;j<=(n-i);j++)
     {
       if((curr->data) > (next->data))
       {
             if(curr == *head)
              *head = next;
             if(next == *tail)
              *tail = curr;
             curr->xor_ = next->xor_;
             next->xor_ = curr;
             if(prev != NULL)
              prev->xor_ = next;
             prev = next;
             next = curr->xor_;
       }
       else
       {
         prev = curr;
         curr = next;
         next = next->xor_;
       }
     }

   }
}
//---------------------------------------------------------------------------------------
void traverse_from_front_to_end(struct node *head)
{
 printf("Doubly linked list traversed from front to end: ");
 struct node *b,*a,*prev,*curr,*next;
 int i;
 b = head->xor_;
 a = head;
 prev = a;
 curr = b;
 printf("%d,",a->data);
for(i=2;i<=n;i++)
{
    printf("%d,",curr->data);
    next = (struct node*)(((uintptr_t)prev)^((uintptr_t)(curr->xor_)));
    prev = curr;
    curr = next;
}
printf("\b \b\n");
}
//---------------------------------------------------------------------------------------
void traverse_from_end_to_front(struct node *tail)
{
  printf("Doubly linked list traversed from end to front: ");
  struct node *b,*a,*prev,*curr,*next;
  int i;
  b = tail->xor_;
  a = tail;
  prev = a;
  curr = b;
  printf("%d,",a->data);
  for(i=2;i<=n;i++)
  {
    printf("%d,",curr->data);
    next = (struct node*)(((uintptr_t)prev)^((uintptr_t)(curr->xor_)));
    prev = curr;
    curr = next;
  }
  printf("\b \b\n");
}
//---------------------------------------------------------------------------------------
void reverse(struct node **head, struct node **tail) // since it is symmetric
{
    (*head) = (struct node*)((uintptr_t)(*head) + (uintptr_t)(*tail));
    (*tail) = (struct node*)((uintptr_t)(*head) - (uintptr_t)(*tail));
    (*head) = (struct node*)((uintptr_t)(*head) - (uintptr_t)(*tail));
}
//--------------------------------------------------------------------------------------------
void sort(struct node **head, struct node **tail) //without change data field of any node.
{
  //changing this into a normal linked list by traversing
  struct node *curr,*prev,*next,*a;
  curr = (*head)->xor_;
  a = *head;
  prev = a;
  int i;
  for(i=2;i<=n;i++)
  {
    next = (struct node*)(((uintptr_t)prev)^((uintptr_t)(curr->xor_)));
    (curr->xor_) = next;
    prev = curr;
    curr = next;
  }
  *tail = prev;
  (*tail)->xor_ = NULL;
  //sorting this normal linked list without change data field of any node
  sort_linked_list(head,tail);
  //converting this back into XOR linked list
  a = *head;
  prev = a;
  next = a->xor_;
  curr = next;
  a->xor_ = (struct node*)(((uintptr_t)NULL)^((uintptr_t)(a->xor_)));
  for(i=2;i<=n;i++)
  {
    next = curr->xor_;
    curr->xor_ = (struct node*)(((uintptr_t)prev)^((uintptr_t)(curr->xor_)));
    prev = curr;
    curr = next;
  }
}
//---------------------------------------------------------------------------------------------
int main()
{
   //int n;
  srand(time(0)); //seeding
  struct node *a,*c,*head,*tail,*prev,*curr;
  printf("Enter n: ");
  scanf("%d",&n);
  a = (struct node*)malloc(sizeof(struct node));
  a->data = rand()%100; //not more than 2 digits
  head = a; //head
  prev = a;
  c = NULL;
  int i;
  for(i=2;i<=n;i++)
  {
      curr = (struct node*)malloc(sizeof(struct node));
      curr->data = rand()%100;
      prev->xor_ = (struct node*)(((uintptr_t)curr)^((uintptr_t)c)); //xor of previous
      c = prev;
      prev = curr;
  }
  tail = curr; //tail
  curr->xor_ = c;
  traverse_from_front_to_end(head);
  traverse_from_end_to_front(tail);
  reverse(&head,&tail);
  printf("Reversed ");
  traverse_from_front_to_end(head); //after reversing
  sort(&head,&tail);
  printf("Sorted ");
  traverse_from_front_to_end(head);
}

