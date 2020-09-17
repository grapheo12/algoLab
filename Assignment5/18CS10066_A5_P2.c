/* Name : Shubham Mishra
 * Roll No: 18CS10066
 * Assignment 5 Part 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INPUT_FILE "output.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_SYMBOL_LENGTH 100

struct _node{
	char *symbol;
	int frequency;
	struct _node *next;
	struct _node *left;
	struct _node *right;
};

typedef struct _node Node, *ll, *Tree;

ll createLlNode(ll head, char symbol, int frequency){
	ll newNode = (ll)malloc(sizeof(Node));

	newNode -> symbol = (char *)malloc(MAX_SYMBOL_LENGTH * sizeof(char));

	newNode -> symbol[0] = symbol;
	newNode -> symbol[1] = '\0';

	newNode -> frequency = frequency;

	newNode -> left = NULL;
	newNode -> right = NULL;

	if (head == NULL){
		newNode -> next = NULL;
		return newNode;
	}else{
		ll tmp = head;
		while (tmp -> next != NULL)
			tmp = tmp -> next;
		tmp -> next = newNode;

		return head;
	}
}


void traverseLl(ll head){
	ll tmp = head;
	while (tmp != NULL){
		printf("%s %d\n", tmp -> symbol, tmp -> frequency);
		tmp = tmp -> next;
	}
}

void sortLl(ll head, int size){
	//Sorts using selection sort.

	int curr_pos = 0;
	while (curr_pos < size){
		ll tmp = head;
		//Move to the index of curr_pos
		int i = curr_pos;
		while (--i > 0){
			tmp = tmp -> next;
		}
		int curr_freq = tmp -> frequency;


		//Compare all the next nodes for the min node
		i = curr_pos;
		ll tmp2 = tmp;
		int min_index = i;
		//Detect the minimum element
		while (tmp2 != NULL){
			if (tmp2 -> frequency < curr_freq){

				min_index = i;
				curr_freq = tmp2 -> frequency;
			}

			i++;
			tmp2 = tmp2 -> next;
		}

		//Go to the minimum element
		tmp2 = tmp;
		while (min_index > curr_pos){
			min_index--;
			tmp2 = tmp2 -> next;
		}

		//Now swap all values
		char tmp_symbol[MAX_SYMBOL_LENGTH];
		int tmp_freq;

		strcpy(tmp_symbol, tmp -> symbol);
		strcpy(tmp -> symbol, tmp2 -> symbol);
		strcpy(tmp2 -> symbol, tmp_symbol);

		tmp_freq = tmp -> frequency;
		tmp -> frequency = tmp2 -> frequency;
		tmp2 -> frequency = tmp_freq;

		//Go for the next element
		curr_pos++;
	}
}

Tree createTree(ll head){
	//Creates an Huffman encoding tree.
	//Pass a sorted Linked List.

	ll final_head = head;
	int n_count = 1;
	int size = 36;
	while (final_head -> next != NULL){
		Tree n = (Tree)malloc(sizeof(Node));
		n -> symbol = (char *)malloc(MAX_SYMBOL_LENGTH * sizeof(char));
		sprintf(n -> symbol, "N%d", n_count++);
		n -> left = final_head;
		n -> right = final_head -> next;
		n -> frequency = final_head -> frequency + final_head -> next -> frequency;
		

		n -> next = final_head -> next -> next;
		final_head = n;
		size -= 2;
		sortLl(final_head, size);
		
	}

	return (Tree)final_head;

}

void preorderTraversal(FILE *ostream, Tree root){
	if (root == NULL)
		return;
	fprintf(ostream, "%s ", root -> symbol);
	preorderTraversal(ostream, root -> left);
	preorderTraversal(ostream, root -> right);
}

void findEncoding(FILE *ostream, Tree root, char *current_num){
	if (root -> left == NULL && root -> right == NULL){
		fprintf(ostream, "%s\t%s\n", root -> symbol, current_num);
	}else{
		int len = strlen(current_num);
		current_num[len] = '0';
		current_num[len + 1] = '\0';

		findEncoding(ostream, root -> left, current_num);

		current_num[len] = '1';

		findEncoding(ostream, root -> right, current_num);

		current_num[len] = '\0';
	}
}
int main(){
	FILE *fo = fopen(INPUT_FILE, "r");

	ll head = NULL;
	char s;
	int freq;

	int i;
	for (i = 0; i < 36; i++){
		fscanf(fo, "%c=%d,", &s, &freq);

		printf("Symbol: %c, Frequency: %d\n", s, freq);
		head = createLlNode(head, s, freq);
	}

	// traverseLl(head);
	// printf("=====\n");
	sortLl(head, 36);
	traverseLl(head);

	Tree t = createTree(head);
	// traverseLl(t);
	//traverseLl(head);
	preorderTraversal(stdout, t);



	fclose(fo);

	FILE *fo2 = fopen(OUTPUT_FILE, "a");
	preorderTraversal(fo2, t);
	fprintf(fo2, "\n");

	fclose(fo2);

	char current_num[MAX_SYMBOL_LENGTH];
	current_num[0] = '\0';

	findEncoding(stdout, t, current_num);

	return 0;
}




