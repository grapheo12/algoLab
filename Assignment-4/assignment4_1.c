//(c)ubc
#include<stdio.h>
#include<stdlib.h>

struct node
{
  int vertex;
  struct node* next;
};

struct Edge
{
  int from;
  int to;
  int weight;
};

struct Graph
{
  int numVertices;
  struct node** adjLists;
};

struct Graph* create_graph(int vertices)
{
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
  graph->numVertices = vertices; 
  graph->adjLists = (struct node**) malloc(vertices * sizeof(struct node*)); 
  int i; 
  for (i = 0; i < vertices; i++) 
    graph->adjLists[i] = NULL; 
  return graph; 
}


void add_edge(struct Graph* graph, int source, int destination) 
{ 
  struct node* new_node;
  new_node = (struct node*)malloc(sizeof(struct node)); 
  new_node->vertex = source; 
  new_node->next = NULL;
  if(graph->adjLists[destination] == NULL) //empty horizontal
    {
       graph->adjLists[destination] = new_node;
       new_node->next = NULL;
    }
    else //non empty
    {
       new_node->next = graph->adjLists[destination];
       graph->adjLists[destination] = new_node;
    }
} 

int find_weight(struct Graph* graph, int source)
{
  //printf("%d\n",source);
  if(graph->adjLists[source] == NULL) //empty horizontal
       return 0; 
   else   //non empty
   {
      int count = 0;
      struct node *current;
      current = graph->adjLists[source];  
     while (current != NULL)  
     {  
        count++;  
        current = current->next;  
     }  
    return count;  
   }      
 } 
//----------------------------------------------------------------------------------------------------------
int dominance(struct Edge l,struct Edge r) // =1 iff L[i] <= R[j]
{
   if(l.from > r.from)
    return 0;
   else if(l.from < r.from)
    return 1;
   else if(l.from == r.from)
   {
     if(l.weight > r.weight)
     return 0;
     else if(l.weight < r.weight)
     return 1;
     else if(l.from == r.from)
       { 
          if(l.to > r.to)
           return 0;
          else if(l.to < r.to)
           return 1;
          else
            return 1;
       }
   }
}

void merge(struct Edge* arr, int l, int m, int r) 
{
  int i, j, k; 
  int n1 = m - l + 1; 
  int n2 = r - m; 
  struct Edge L[n1], R[n2]; 

  for (i = 0; i < n1; i++) 
    L[i] = arr[l + i]; 
  for (j = 0; j < n2; j++) 
    R[j] = arr[m + 1+ j]; 

 
  i = 0; 
  j = 0; 
  k = l; 

  while (i < n1 && j < n2) 
  { 
    if(dominance(L[i],R[j])) // =1 iff L[i] <= R[j]
    { 
      arr[k] = L[i]; 
      i++; 
    } 
    else
    { 
      arr[k] = R[j]; 
      j++; 
    } 
    k++; 
  } 
  
  while (i < n1) 
  { 
    arr[k] = L[i]; 
    i++; 
    k++; 
  } 

  
  while (j < n2) 
  { 
    arr[k] = R[j]; 
    j++; 
    k++; 
  } 
}

void Merge_sort(struct Edge* arr,int l, int r)
{
   if (l < r) 
  { 
    int m = l+(r-l)/2; 
    Merge_sort(arr, l, m); 
    Merge_sort(arr, m+1, r); 
    merge(arr, l, m, r); 
  } 
}
//-----------------------------------------------------------------------------------------------------------
int main()
{
  FILE *file_pointer,*output_p;
  int vertices,edges;
  struct Graph *graph;
  file_pointer = fopen("input.txt", "r");
  output_p = fopen("output.txt","w");
  fscanf(file_pointer,"%d",&vertices);
  fscanf(file_pointer,"%d",&edges);
  int i,p,q;
  graph = create_graph(vertices);
  struct Edge array[edges];
  for(i=0;i<edges;i++)
  {
    fscanf(file_pointer,"%d",&p); 
      fscanf(file_pointer,"%d",&q);
      p--;
      q--;
      add_edge(graph,p,q);  
      array[i].from = p+1;
      array[i].to = q+1;
  }
   for(i=0;i<edges;i++) //finding weights
    {
       array[i].weight = find_weight(graph, array[i].from-1) + find_weight(graph, array[i].to-1);
    }
    Merge_sort(array, 0,edges - 1); //sorting
    for(i=0;i<edges;i++) //output 
    {
       fprintf(output_p,"%d %d %d\n",array[i].from,array[i].weight,array[i].to);  
    }
    fclose(file_pointer);
    fclose(output_p);
    return 0;
}

