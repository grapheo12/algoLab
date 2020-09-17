#include <stdio.h>
#include <stdlib.h>

/*Part 1*/
struct node{
	int vertex;
	struct node* next;
};

struct Graph{
	int numVertices;
	struct node **adjLists;
};

typedef struct node node;
typedef struct Graph Graph;

Graph * createGraph(int v){
	//Creates empty graph with v no of vertices
	Graph *g = (Graph *)malloc(sizeof(Graph));
	g -> numVertices = v;
	g -> adjLists = (node **)malloc(v * sizeof(node *));

	int i;
	for (i = 0; i < v; i++)
		g -> adjLists[i] = NULL;

	return g;
}

void addEdge(Graph *g, int i, int j){
	//Adds an edge from i to j.
	//i, j follows 1 based indexing.

	if (g -> numVertices >= i && g -> numVertices >= j && i >= 1 && j >= 1){
		node *tmp = g -> adjLists[i - 1];
		g -> adjLists[i - 1] = (node *)malloc(sizeof(node));
		g -> adjLists[i - 1] -> vertex = j - 1;
		g -> adjLists[i - 1] -> next = tmp;

	}
}

void printGraph(Graph *g, FILE *fp){
	int i;
	for (i = 0; i < g -> numVertices; i++){
		fprintf(fp, "Node %d : ", i + 1);
		node *tmp = g -> adjLists[i];
		while (tmp != NULL){
			fprintf(fp, "%d ", tmp -> vertex + 1);
			tmp = tmp -> next;
		}
		fprintf(fp, "\n");
	}
}
/*END*/

/*Part 2*/
typedef struct{
	int from;		//id of a source vertex
	int to;			//id of a destination vertex
	int weight;		//weight of an edge
} Edge;

Edge * genGraph(int e){
	// //Interactive function that generates an Edge array graph from file
	// int v, e, i, j, k;
	// fscanf(fp, "%d %d", &v, &e);
	Edge *g = (Edge *)malloc(e * sizeof(Edge));
	
	// // printf(">>%d %d\n", v, e);
	// //Stores inDegree of all vertices
	// int *inDeg = (int *)malloc(v * sizeof(int));
	// for (k = 0; k < v; k++)
	// 	inDeg[k] = 0;

	// for (k = 0; k < e; k++){
	// 	fscanf(fp, "%d %d", &i, &j);
	// 	//i and j are 1 based indices
	// 	// printf("%d %d\n", i, j);
	// 	g[k].from = i;
	// 	g[k].to = j;

	// 	inDeg[j - 1] += 1;
	// }

	// for (k = 0; k < e; k++)
	// 	g[k].weight = inDeg[g[k].from - 1] + inDeg[g[k].to - 1];
	
	return g;	
}

void newEdge(Edge *e, int index, int i, int j){
	e[index].from = i;
	e[index].to = j;
	e[index].weight = 0;
}

int getInNodes(Graph *g, int i, int v){
	int in = 0, k;
	for (k = 0; k < v; k++){
		node *tmp = g -> adjLists[k];

		while (tmp != NULL){
			if (tmp -> vertex == i - 1)
				in++;
			tmp = tmp -> next;
		}
	}
	return in;
}
void updateWeights(Edge *e, Graph *g, int v, int edge){
	//Computes weights of edges in e from graph g
	int i = 0;
	for (i = 0; i < edge; i++){
		e[i].weight = getInNodes(g, e[i].from, v) + getInNodes(g, e[i].to, v);
	}
}

void mergeSort(Edge *g, int l, int r, Edge *buff){
	if (l >= r){
		return;
	}

	int mid = (l + r) / 2;
	// printf("%d %d %d \n", l, r, mid);
	mergeSort(g, l, mid, buff);

	mergeSort(g, mid + 1, r, buff);

	int i = l, j = mid + 1, k = 0;

	while (i <= mid && j <= r){
		int lscore = 0;
		int rscore = 0;
		
		if (g[i].from < g[j].from){
			lscore += 0;
			rscore += 200;
		}else if (g[i].from == g[j].from){
			lscore += 100;
			rscore += 100;
		}else{
			lscore += 200;
			rscore += 0;
		}

		if (g[i].weight < g[j].weight){
			lscore += 0;
			rscore += 20;
		}else if (g[i].weight == g[j].weight){
			lscore += 10;
			rscore += 10;
		}else{
			lscore += 20;
			rscore += 0;
		}

		if (g[i].to < g[j].to){
			lscore += 0;
			rscore += 2;
		}else if (g[i].to == g[j].to){
			lscore += 1;
			rscore += 1;
		}else{
			lscore += 2;
			rscore += 0;
		}

		if (lscore < rscore){
			// printf("%d\n", buff[k].from);
			buff[k].from = g[i].from;
			buff[k].to = g[i].to;
			buff[k].weight = g[i].weight;
			i++;
		}else{
			buff[k].from = g[j].from;
			buff[k].to = g[j].to;
			buff[k].weight = g[j].weight;
			j++;
		}
		k++;

	}

	while (i <= mid){
		buff[k].from = g[i].from;
		buff[k].to = g[i].to;
		buff[k].weight = g[i].weight;
		i++;
		k++;
	}

	while (j <= r){
		buff[k].from = g[j].from;
		buff[k].to = g[j].to;
		buff[k].weight = g[j].weight;
		j++;
		k++;
	}

	k = 0;
	for (i = l; i <= r; i++){
		g[i].from = buff[k].from;
		g[i].to = buff[k].to;
		g[i].weight = buff[k].weight;
		k++;
	}
}

void printEdges(Edge *g, int size, FILE *fp){
	int i;
	for (i = 0; i < size; i++){
		fprintf(fp, "%d %d %d\n", g[i].from, g[i].weight, g[i].to);
	}
}

int main(){
	
	/*Part1 I/O*/
	FILE *fi = fopen("input.txt", "r");
	FILE *fo = fopen("18CS10066_A4_output.txt", "w");
	int v, e, i, j;
	fscanf(fi, "%d %d", &v, &e);
	Graph *g = createGraph(v);
	Edge *g2 = genGraph(e);
	int k;
	for (k = 0; k < e; k++){
		fscanf(fi, "%d %d", &i, &j);
		addEdge(g, i, j);
		newEdge(g2, k, i, j);
	}

	updateWeights(g2, g, v, e);

	Edge *buff = (Edge *)malloc(e * sizeof(Edge));
	mergeSort(g2, 0, e - 1, buff);
	printEdges(g2, e, fo);
	 
	// printGraph(g, fo);
	fclose(fi);
	fclose(fo);
	/*END*/

	// /*Part2 I/O*/
	// FILE *fi = fopen("input.txt", "r");
	// FILE *fo = fopen("output.txt", "w");

	// Edge *g = genGraph(fi);
	// Edge *buff = (Edge *)malloc(10 * sizeof(Edge));
	// mergeSort(g, 0, 5, buff);
	// printEdges(g, 6, stdout);

	// fclose(fi);
	// fclose(fo);
	/*END*/

	return 0;

}
