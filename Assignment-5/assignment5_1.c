//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
  char *symbol;
  int frequency ;
  struct node* next ;
  struct node* left ;
  struct node* right ;
};

struct node* head = NULL; //head of ll 
struct node* root = NULL; //root of Huffman tree

int is_empty_list()
{
  if(head == NULL)
   	 return 1;
  else
    return 0;
}

void add_node(int x,char *c) 
{
  struct node* temp = (struct node*)malloc(sizeof(struct node));
 	temp->frequency = x;
 	temp->symbol = c;
  temp->left = NULL;
  temp->right = NULL;
  temp->next = NULL;
 	if(is_empty_list())
  		head = temp;
 	 else
 	 {
 	 	temp->next = head;
 	 	head = temp;
 	 }
 	 return;
}
//-------------------------------------------------------------------------------------------------------
int compare_chars(char a,char b) //=1 if a>b
{
  if((a >= 97) && (b < 97))
   return 0;
  else if((a < 97) && (b >= 97))
    return 1;
  else if(a > b)
    return 1;
  else if(b > a)
    return 0;
  else
    return -1;
}

int compare(const char *curr,const char *next) //=1 iff curr > next
{
  int p,q;
  p = strlen(curr);
  q = strlen(next);
  if((p < q) && ((p == 1) || (q == 1)))
   return 1;
  else if((p > q) && ((p == 1) || (q == 1)))
   return 0;
  else if((p == 1) && (q == 1))
   {
      if(compare_chars(curr[0],next[0]) == 1)
        return 1;
      else if(compare_chars(curr[0],next[0]) == 0)
        return 0;
   }
   else 
   {
     if(strcmp(curr,next) > 0)
      return 1;
     else
      return 0;
   }
   return 0;
}

int dominance(struct node* curr,struct node* next)
{
	if((curr->frequency) > (next->frequency))
		return 1;
	else if((curr->frequency) < (next->frequency))
		return 0;
	else if((curr->frequency) == (next->frequency))
	{
		if(compare(curr->symbol,next->symbol) == 1) 
			return 1;
		else
			return 0;
	}
}

void sort_linked_list(struct node **head,int n)
{
   struct node *prev,*curr,*next;
   int i,j;
   for(i=1;i<n;i++)
   {
     curr = *head;
     next = (curr->next);
     prev = NULL;
     for(j=1;j<=(n-i);j++)
     {
       if(dominance(curr,next) == 1) //=1 (curr->frequency) > (next->frequency)
       {
             if(curr == *head)
              *head = next;
             curr->next = next->next;
             next->next = curr;
             if(prev != NULL)
              prev->next = next;
             prev = next;
             next = curr->next;
       }
       else
       {
         prev = curr;
         curr = next;
         next = next->next;
       }
     }

   }
   return;
}
//-------------------------------------------------------------------------------------------------------
void addfreq(char *str,int *freq)
{
	int i;
	int n = strlen(str);
	for(i=0;i<n;i++)
	{
		if(str[i] >= 97)
			freq[str[i]-97]++;
		else
			freq[26+(str[i]-48)]++;
	}
}

void print_list()
{
   struct node* curr = head;
    while(curr != NULL)
    {
      printf(" %s-%d ",curr->symbol,curr->frequency);
      curr = curr->next;
    }
    printf("\n");
    return;
}
//-------------------------------------------------------------------------------------------------------
void TreeTraverse(struct node* root,char* temp,char huffman_codes[][1000],int count_nodes,FILE** fp)
{
   char temp1[100];
   strcpy(temp1,"\0");
   strcpy(temp1,temp);
  if(root)
  {
    fprintf(*fp,"%s ",root->symbol);
    //printf("%s \n",root->symbol);
  }
  if((root->left == NULL) && (root->right == NULL)) //leaf
  {
    if((root->symbol)[0] >= 97)
      strcpy(huffman_codes[*(root->symbol) - 97],temp);
    else
      strcpy(huffman_codes[26 + (*(root->symbol) - 48)],temp);
  }
  else
  {
      TreeTraverse(root->left,strcat(temp,"0"),huffman_codes,count_nodes,fp);
      strcpy(temp,temp1);
      TreeTraverse(root->right,strcat(temp,"1"),huffman_codes,count_nodes,fp);
  }
  return;
}
//-------------------------------------------------------------------------------------------------------
void encode(char * message , char * encodedMessage,char huffman_codes[][1000])
{
  int i;
  char c;
  strcpy(encodedMessage,"\0");
  for(i=0;i<strlen(message);i++)
  {
    c = message[i];
    if(c >= 97)
      strcat(encodedMessage,huffman_codes[c-97]);
    else
      strcat(encodedMessage,huffman_codes[26+(c-48)]);
  }
  return;
}
//-------------------------------------------------------------------------------------------------------
void find_temp(char *temp,int j)
{
  if((j >= 0) && (j <= 25))
  {
    temp[0] = 'a' + j;
    temp[1] = '\0';
  }
  else
  {
    temp[0] = '0' + j;
    temp[1] = '\0';
  }
  return;
}

void decode( char * encodedMessage , char * decodedOutput, char huffman_codes[][1000])
{
   char cache[100],temp[10];
   strcpy(decodedOutput,"\0");
   strcpy(cache,"\0");
   int i,j;
   for(i=0;i<strlen(encodedMessage);i++)
   { 
      if(encodedMessage[i] == '1')
      strcat(cache,"1");
      else
      strcat(cache,"0");
      for(j=0;j<36;j++)
      {
         if(!strcmp(cache,huffman_codes[j]))
         {
            strcpy(temp,"\0");
            find_temp(temp,j);
            strcat(decodedOutput,temp);
            strcpy(cache,"\0");
         }
      }
   }
  return;
}
//-------------------------------------------------------------------------------------------------------
int main()
{
	  FILE *fp_in,*fp_out,*fp_encode,*fp_decode;
	  fp_in = fopen("log.txt", "r");
    fp_out = fopen("output.txt","w");
    int n_words,i,j;
    char huffman_codes[36][1000];
    char str[1000];
    int freq[36];
    for(i=0;i<36;i++)
      freq[i]  = 0;
    fscanf(fp_in,"%d",&n_words); 
    for(i=0;i<n_words;i++)
    {
       fscanf(fp_in,"%s",str);
       addfreq(str,freq);
    }
    char start = 'a';
    for(i=0;i<=25;i++)
    {
      fprintf(fp_out,"%c = %d ,",start,freq[i]);
      //printf("%c = %d\n",start,freq[i]);
      start++;
    }
    start = '0';
    for(i=26;i<=35;i++)
    {
      fprintf(fp_out,"%c = %d ,",start,freq[i]);
      //printf("%c = %d\n",start,freq[i]);
      start++;
    }
    fprintf(fp_out, "\n");
    char* temp;
    start = 'a';
    for(i=0;i<=25;i++)
    {
      temp = (char *)malloc(100*sizeof(char));
      temp[0] = start;
      temp[1] = '\0';
      add_node(freq[i],temp);
      start++;
    }
    start = '0';
    for(i=26;i<=35;i++)
    {
      temp = (char *)malloc(100*sizeof(char));
      temp[0] = start;
      temp[1] = '\0';
      add_node(freq[i],temp);
      start++;
    }

    sort_linked_list(&head,36);
    //print_list();

    int nodes_in_list = 36;
    int temp_freq = 0;
    int count_nodes = 1;
     
    while(nodes_in_list > 1)
    {
       struct node *left,*right;
       left = head;
       right = head->next;
       temp = (char *)malloc(100*sizeof(char));
       temp_freq = left->frequency + right->frequency;
       strcpy(temp,"N");
       char str[10];
       if(count_nodes/10 == 0)
        strcat(temp,"0");
       sprintf(str,"%d",count_nodes);
        count_nodes++;
       strcat(temp,str);
       strcpy(str,"\0");
       add_node(temp_freq,temp);
       head->left = left;
       head->right = right; 
       head->next = right->next;
       nodes_in_list--;
       if(nodes_in_list > 1)
       sort_linked_list(&head,nodes_in_list);
    }
    root = head;
    //print_list();

    char tree_temp[100];
    strcpy(tree_temp,"\0");
    TreeTraverse(root,tree_temp,huffman_codes,count_nodes,&fp_out);
     fprintf(fp_out, "\n");
     start = 'a';
    for(i=0;i<=25;i++)
    {
      fprintf(fp_out,"%c %s\n",start,huffman_codes[i]);
      //printf("%c ---> %s\n",start,huffman_codes[i]);
      start++;
    }
    start = '0';
    for(i=26;i<=35;i++)
    {
      fprintf(fp_out,"%c %s\n",start,huffman_codes[i]);
      //printf("%c ---> %s\n",start,huffman_codes[i]);
      start++;
    }

    fp_encode = fopen("encode.txt","r");
    char encodedMessage[1000];
    fscanf(fp_encode,"%d",&n_words); 
    for(i=0;i<n_words;i++)
    {
       fscanf(fp_encode,"%s",str);
       encode(str,encodedMessage,huffman_codes);
       fprintf(fp_out,"%s\n",encodedMessage);
       //printf("%s\n",encodedMessage);
    }

    fp_decode = fopen("decode.txt","r");//used results of encoding for checking correctness
    char decodedOutput[1000];
    fscanf(fp_decode,"%d",&n_words); 
    for(i=0;i<n_words;i++)
    {
       fscanf(fp_decode,"%s",str);
       decode(str,decodedOutput,huffman_codes);
       fprintf(fp_out,"%s\n",decodedOutput);
       //printf("%s\n",decodedOutput);
    }
    
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
