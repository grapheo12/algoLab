//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _treenode
{
 char * route ;
 struct _treenode * left ;
 struct _treenode * right ;
 int height;
};

int find_height(struct _treenode *temp) 
{ 
	if (temp == NULL) 
		return 0; 
	else
	return temp->height;
} 

int maximum(int a, int b) 
{ 
   if(a>b)
   	return a;
   else
   	return b;
} 

struct _treenode* make_new_node(char* route) 
{ 
	struct _treenode* temp = (struct _treenode*)malloc(sizeof(struct _treenode)); 
	temp->route = route; 
	temp->left = NULL; 
	temp->right = NULL; 
	temp->height = 1; 
	return temp; 
} 


struct _treenode *rotate_right(struct _treenode *q) 
{ 
	struct _treenode *p = q->left; 
	struct _treenode *temp = p->right; 
	p->right = q; 
	q->left = temp; 
	q->height = maximum(find_height(q->left),find_height(q->right))+1; 
	p->height = maximum(find_height(p->left),find_height(p->right))+1; 
	return p; 
} 

struct _treenode *rotate_left(struct _treenode *p) 
{ 
	struct _treenode *q = p->right; 
	struct _treenode *temp = q->left; 
	q->left = p; 
	p->right = temp; 
	p->height = maximum(find_height(p->left),find_height(p->right))+1; 
	q->height = maximum(find_height(q->left),find_height(q->right))+1; 
	return q; 
} 


int find_bal_(struct _treenode *temp) 
{ 
	if (temp == NULL) 
		return 0; 
	int x =  find_height(temp->left) - find_height(temp->right); 
	return x;
} 


struct _treenode* insert_node(struct _treenode* _treenode, char* route) 
{ 

	if (_treenode == NULL) 
		return make_new_node(route); 

	if (strcmp(route , _treenode->route) < 0) 
		_treenode->left = insert_node(_treenode->left, route); 

	else if (strcmp(route , _treenode->route) > 0) 
		_treenode->right = insert_node(_treenode->right, route); 

	else 
	    return _treenode; 

	_treenode->height = 1 + maximum(find_height(_treenode->left),find_height(_treenode->right)); 

	int bal_ = find_bal_(_treenode); 

	if (bal_ > 1 && (strcmp(route , _treenode->left->route) < 0))
		return rotate_right(_treenode); 


	if (bal_ < -1 && (strcmp(route , _treenode->right->route) > 0)) 
		return rotate_left(_treenode); 

	if (bal_ > 1 && (strcmp(route , _treenode->left->route) > 0))
	{ 
		_treenode->left = rotate_left(_treenode->left); 
		return rotate_right(_treenode); 
	} 

	if (bal_ < -1 && (strcmp(route , _treenode->right->route) < 0)) 
	{ 
		_treenode->right = rotate_right(_treenode->right); 
		return rotate_left(_treenode); 
	} 

	return _treenode; 
} 

void remove_errors(char *str)
{
   int l = strlen(str);
   int i,j = 0,end = l-1,k;
 
   for(i=0;i<(l-1);i++)
   {
      if(str[i] == str[i+1])
        {
        	for(k = i;k <= (end-1);k++)
        	{
        		str[k] = str[k+1];
        	}
        	str[end] = '\0';
        	end--;
        }
   }
   return;
}

void in_order_(struct _treenode *root) 
{ 
	if(root != NULL) 
	{ 
		in_order_(root->left); 
		printf("%s\n", root->route); 
		in_order_(root->right); 
	} 
	return;
} 

int search(struct _treenode* root, char* x)
{
	if(root == NULL)
		return 0;
	else if(strcmp(root->route,x) == 0)
		return 1;
	else if(strcmp(root->route, x) > 0)
		return search(root->left,x);
	else if(strcmp(root->route, x) < 0)
		return search(root->right,x);
}

void rule_1_(struct _treenode* root,char* temp,FILE** fp)
{
   char c = 'A';
   int i,j,k;
   char temp11[100];
   int l = strlen(temp);
   int ind,pos,nw=0;
   for(i=0;i<26;i++)
   {
   	  strcpy(temp11,"\0");
     for(pos = 0;pos <= l;pos++)
     {
       strcpy(temp11,"\0");
       temp11[pos] = c;
       j = 0;
       for(k=0;k<l;k++)
       {
       	 if(k!=pos)
       	 {
       	  temp11[j] = temp[k];
       	  j++;
       	}
       	if(k == pos)
       	{
       	  j++;
          temp11[j] = temp[k];
       	  j++;
       	}
       }
       if(pos != l)
       temp11[j] = '\0';
       else
       	temp11[j+1] = '\0';
       if(search(root,temp11) == 1)
       	fprintf( *fp,"%s ",temp11);
     }
       c++;
     }
     fprintf( *fp,"\n");
 }


void rule_2_(struct _treenode* root,char* temp,FILE** fp)
{
    int l = strlen(temp);
    int pos;
    char temp11[100];
    int j = 0,k;
     for(pos = 0;pos < l;pos++)
     {
       strcpy(temp11,"\0");
       j = 0;
       for(k=0;k<l;k++)
       {
       	 if(k!=pos)
       	 {
       	  temp11[j] = temp[k];
       	  j++;
       	}
       }
       temp11[j] = '\0';
       if(search(root,temp11) == 1)
       	fprintf( *fp,"%s ",temp11);
     }
    fprintf( *fp,"\n");
}

int main()
{
	FILE *fp_routes,*fp_query,*fp_output;
	struct _treenode *root = NULL; 
	fp_routes = fopen("Routes.txt","r");
	fp_query = fopen("Query.txt","r");
	fp_output = fopen("output.txt","w");
	int n_words,i;
	fscanf(fp_routes,"%d",&n_words); 
	char *temp;;
    for(i=0;i<n_words;i++)
    {
       temp =  (char *)malloc(100*sizeof(char));
       strcpy(temp,"\0");
       fscanf(fp_routes,"%s",temp);
       remove_errors(temp);
       //printf("%s\n",temp);
       root = insert_node(root,temp);
   }

   fscanf(fp_query,"%d",&n_words); 
   for(i=0;i<n_words;i++)
    {
       temp =  (char *)malloc(100*sizeof(char));
       strcpy(temp,"\0");
       fscanf(fp_query,"%s",temp);
       fprintf(fp_output,"Corrections for the route  \"%s\" : ",temp);
       remove_errors(temp);
       fprintf(fp_output,"%s\n",temp);
       //printf("%s\n",temp);
       if(search(root,temp) == 1) //found
       {
         fprintf(fp_output,"Searching for the route \"%s\" : found\n" ,temp);
         fprintf(fp_output, "\n");
       }
       else
       {
         fprintf(fp_output,"Searching for the route \"%s\" : not found\n" ,temp);
         fprintf(fp_output,"Alternate route suggestion:\n");
         fprintf(fp_output, "Rule 1:");
         rule_1_(root,temp,&fp_output);
         fprintf(fp_output, "Rule 2:");
         rule_2_(root,temp,&fp_output);
         fprintf(fp_output, "\n");
       }
   }
   //in_order_(root);
   fclose(fp_routes);
   fclose(fp_query);
   fclose(fp_output);
   return 0;
}


