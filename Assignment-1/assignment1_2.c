#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct list{
  struct list *XORadd;
  int data;
};

typedef struct list node;

void traverse_from_front_to_end(node *head);
void traverse_from_end_to_front(node *tail);
void reverse(node **head,node **tail);
void sort(node **head,node **tail);

int main()
{
  int n,x;
  node *head = NULL,*tail=NULL,*curr=NULL,*prev=NULL,*next=NULL;
  printf("Enter the value of n:");
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    {
      if(i==1)
	{
	  head=(node*)malloc(1*sizeof(node));
	  curr=head;
	  scanf("%d",&x);
	  head->data=x;
	}
      else
	{
	  next=(node*)malloc(1*sizeof(node));
	  curr->XORadd=(node*)(uintptr_t)((uintptr_t)prev^(uintptr_t)next);
	  scanf("%d",&x);
	  next->data=x;
	  prev=curr; curr=next;
	}
    }
  next=NULL;
  curr->XORadd=(node*)(uintptr_t)((uintptr_t)prev^(uintptr_t)next);
  tail=curr;
  traverse_from_front_to_end(head);
  printf("\n");
  sort(&head,&tail);
  traverse_from_front_to_end(head);
  traverse_from_end_to_front(tail);




}

void traverse_from_front_to_end(node *head)
{
  node *curr=NULL,*prev=NULL,*temp;
  curr=head;
  while(curr!=NULL)
    {
      printf("%d,",curr->data);
      temp=curr;
      curr=(node*)(uintptr_t)((uintptr_t)prev^(uintptr_t)(curr->XORadd));
      prev=temp;
    }
    printf("\n");
}

void traverse_from_end_to_front(node *tail)
{
   node *curr=NULL,*prev=NULL,*temp;
  curr=tail;
  while(curr!=NULL)
    {
      printf("%d,",curr->data);
      temp=curr;
      curr=(node*)(uintptr_t)((uintptr_t)prev^(uintptr_t)(curr->XORadd));
      prev=temp;
    }
    printf("\n");
}

void reverse(node **head,node **tail)
{
  node *temp;
  temp=*head;
  *head=*tail;
  *tail=temp;
}

void sort(node **head,node **tail)
{
    /*uses Bubble Sort*/
    node *p0,*p1,*p2,*p3,*p4,*p5,*temp;
    int count=1;
    while(count) //no comparisons = sorted list
    {
        count=0; // to count number of comparisons
        p0=p1=p2=p3=p4=p5=NULL;

        /*
            p3 and p2 will always be used for comparison
            p4 and p1 will be used to modify the XORadd of the exchanged nodes
            p0 and p5 will be used to modify the XORadd of p1 and p4 since their XORadd
            are affected by the exchanged nodes
                                                        */

        /*Initial condition to start from head*/
        p3=*head;
        p2=(*head)->XORadd;
        p1=(node*)(uintptr_t)((uintptr_t)p3^(uintptr_t)(p2->XORadd));
        p0=(node*)(uintptr_t)((uintptr_t)p2^(uintptr_t)(p1->XORadd));
        while(p2)
        {
            if((p2->data)<(p3->data))
            {
                count++;
                if(p3==*head)
                {
                    *head=p2;
                }

                /*because nodes are being exchanged*/

                temp=p2;
                p2=p3;
                p3=temp;

                /*modifying XORadd values*/

                if(p4) //p4 can assume NULL value
                {
                    p4->XORadd=(node*)(uintptr_t)((uintptr_t)p5^(uintptr_t)p3);
                }
                p3->XORadd=(node*)(uintptr_t)((uintptr_t)p4^(uintptr_t)p2);
                p2->XORadd=(node*)(uintptr_t)((uintptr_t)p3^(uintptr_t)p1);
                if(p1) //p1 can assume NULL value
                {
                    p1->XORadd=(node*)(uintptr_t)((uintptr_t)p2^(uintptr_t)p0);
                }
            }
            /*moving ahead*/
            p5=p4;
            p4=p3;
            p3=p2;
            p2=p1;
            p1=p0;
            if(p0)
            {
                p0=(node*)(uintptr_t)((uintptr_t)p2^(uintptr_t)(p0->XORadd));
            }
        }
    }

    /*to update tail*/

    node *curr=NULL,*prev=NULL;
    curr=*head;
    while(curr!=NULL)
    {
        temp=curr;
        curr=(node*)(uintptr_t)((uintptr_t)prev^(uintptr_t)(curr->XORadd));
        prev=temp;
    }
    *tail=prev;
}
