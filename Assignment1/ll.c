#include <stdio.h>
#include <stdlib.h>
/*Only sorting is left to be implemented*/
typedef struct {
	int data;
	unsigned int xor;
} node;

void insertNode(node **head, int value){
	//Always insert at the front.
	node *newNode = (node*)malloc(sizeof(node));
	newNode -> data = value;
	newNode -> xor = 0 ^ (unsigned int)(*head);
	
	(*head) -> xor = (unsigned int)newNode ^ ((*head) -> xor);
	*head = newNode;
}

node * createList(int value){
	//Create the first element of the list.
	node *newNode = (node*)malloc(sizeof(node));
	newNode -> data = value;
	newNode -> xor = 0;
	
	return newNode;
}

void traverse_from_front_to_end(node *head){
	/* Since x ^ (x ^ y) = y.
	 * So we can XOR current element with xor stored in next to get the next -> next pointer.
	 * Iteration stops if we get the next to be 0, ie, NULL
	 */
	 printf("%d ", head -> data);
	 node *next = (node*)(head -> xor);
	 
	 while (next != NULL){
	 	printf("%d ", next -> data);
	 	node *tmp = next;
	 	next = (node*)(next -> xor ^ (unsigned int)head);
	 	head = tmp;
	 }
	 
	 printf("\n");
} 

/*In the following two functions we use the logic
 *that a doubly linked list is bidirectional and
 *XOR operation is commutative
 */
 
void traverse_from_end_to_front(node *tail){
	//Employ the same logic as before.
	traverse_from_front_to_end(tail);
}

void reverse(node **head, node **tail){
	//Swapping the head and tail pointers should reverse the list logically.
	node *tmp = *head;
	*head = *tail;
	*tail = tmp;
}


node * bubble(node *head, node *tail, node* leftP){
	node *tmp = head;
	node *next = (node*)((unsigned int)leftP ^ (tmp -> xor));
	
	if (next == NULL)
		return *head;
		
	if (tmp -> data > next -> data){
		head = next;
		//Perform a swap.
		node *nextNext = (node*)((unsigned int)tmp ^ (next -> xor));
		if (nextNext != NULL){
			node *next3 = (node*)((unsigned int)next ^ (nextNext -> xor));
		
			next -> xor = (unsigned int)leftP ^ (unsigned int)tmp;
		//printf("%d\n", nextNext -> data);
			tmp -> xor = (unsigned int)next ^ (unsigned int)nextNext;
		
			nextNext -> xor = (unsigned int)tmp ^ (unsigned int)next3;
			
			  
		}else{
			tmp -> xor = (unsigned int)next;
			next -> xor = (unsigned int)tmp ^ (unsigned int)leftP;
		}
						
	}
	
	tmp = head;
	next = (node*)((unsigned int)leftP ^ (tmp -> xor));
	
	return bubble(next, tail, tmp);
	
}


int main(){
	node *head, *tail;
	int i;
	int n;
	printf("Please enter the value of n:  ");
	scanf("%d", &n);
	
	head = createList(rand() / 2000000);
	tail = head;
	for (i = 0; i < n - 1; i++)
		insertNode(&head, rand() / 2000000);
	
	traverse_from_end_to_front(tail);
	traverse_from_front_to_end(head);
	
	reverse(&head, &tail);
	
	traverse_from_end_to_front(tail);
	traverse_from_front_to_end(head);
	
	//head = bubble(head, tail, NULL);
	//traverse_from_front_to_end(head);
	
	return 0;
}
	 




