#include <stdio.h>
#include <stdlib.h>

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

void sort(node **head, node **tail){
	//Uses BubbleSort.
	int isSorted;
	while(1){
		isSorted = 1;
		node *h = *head;
		node *t = *tail;
		node *leftP;
		node *next = (node*)(h -> xor);
		if (next == NULL)
			return;
		
		if (h -> data > next -> data){
			isSorted = 0;
			node *next2 = (node*)((unsigned int)h ^ (next -> xor));
			h -> xor = (unsigned int)next2 ^ (unsigned int)next;
			next -> xor = (unsigned int)h;
			if (next2 != NULL){
				node *next3 = (node*)((unsigned int)next ^ (next2 -> xor));
				next2 -> xor = (unsigned int)next3 ^ (unsigned int)h;
			}
			*head = next;
			
			leftP = next;
			//traverse_from_front_to_end(*head);
		}else{
			leftP = h;
			h = next;
		}	
	
	
		while (1){
			//traverse_from_front_to_end(*head);
			next = (node*)((h -> xor) ^ (unsigned int)leftP);
			if (next == NULL)
				break;
			if (h -> data > next -> data){
				isSorted = 0;
				node *next2 = (node*)((unsigned int)h ^ (next -> xor));
				node *beforeP = (node*)((leftP -> xor) ^ (unsigned int)h);
				h -> xor = (unsigned int)next2 ^ (unsigned int)next;
				next -> xor = (unsigned int)h ^ (unsigned int)leftP;
				if (next2 != NULL){
					node *next3 = (node*)((unsigned int)next ^ (next2 -> xor));
					next2 -> xor = (unsigned int)next3 ^ (unsigned int)h;
				}
				leftP -> xor = (unsigned int)beforeP ^ (unsigned int)next;
				
				leftP = next;
			}else{
				leftP = h;
				h = next;
			}
		}
	
		if (isSorted)
			return;
	}
	
	
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
	
	sort(&head, &tail);
	
	traverse_from_front_to_end(head);
	
	return 0;
}
	 




