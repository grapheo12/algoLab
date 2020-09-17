/* Name: Shubham Mishra
 * Roll: 18CS10066
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ABS(x) (x) > 0 ? (x) : -(x)
#define MAX_ROUTE_LENGTH 100
#define INPUT_FILE "Routes.txt"
#define OUTPUT_FILE "Output.txt"
#define QUERY_FILE "Query.txt"

typedef struct _treenode{
    char *route;
    struct _treenode *left;
    struct _treenode *right;
    int balancefactor;
} AVLtreenode, *AVLtree;

AVLtree rightRotate(AVLtree root){
    AVLtree newRoot = root -> left;
    AVLtree oldLR = root -> left -> right;
    newRoot -> right = root;
    root -> left = oldLR;

    return newRoot;
}

AVLtree leftRotate(AVLtree root){
    AVLtree newRoot = root -> right;
    AVLtree oldRL = root -> right -> left;
    newRoot -> left = root;
    root -> right = oldRL;

    return newRoot;
}

int height(AVLtree root){
    if (root == NULL){
        return 0;
    }else{
        return 1 + MAX(height(root -> left), height(root -> right));
    }
}

void inorderTraverse(FILE *ostream, AVLtree root){
    if (root == NULL) return;
    inorderTraverse(ostream, root -> left);
    fprintf(ostream, "%s\n", root -> route);
    inorderTraverse(ostream, root -> right);
}

void preorderTraverse(FILE *ostream, AVLtree root){
    if (root == NULL) return;
    fprintf(ostream, "%s\n", root -> route);
    preorderTraverse(ostream, root -> left);
    preorderTraverse(ostream, root -> right);
}

AVLtree successor(AVLtree root, AVLtree *parent){
    if (root -> right == NULL)
        return root;
    
    *parent = root;
    AVLtree ans = root -> right;
    while (ans -> left != NULL){
        *parent = ans;
        ans = ans -> left;
    }
    return ans;
}

AVLtree addNode(AVLtree root, char *route){
    if (root == NULL){
        AVLtree node = (AVLtree)malloc(sizeof(struct _treenode));
        node -> route = (char *)malloc(MAX_ROUTE_LENGTH * sizeof(char));
        strcpy(node -> route, route);
        node -> left = NULL;
        node -> right = NULL;
        node -> balancefactor = 0;
        return node;
    }else{
        if (strcmp(root -> route, route) < 0)
            root -> right = addNode(root -> right, route);
        else if (strcmp(root -> route, route) > 0)
            root -> left = addNode(root -> left, route);
        
        int h = height(root -> left) - height(root -> right);
        if (h != root -> balancefactor){
            if (h > 1){
                if (height(root -> left -> left) > height(root -> left -> right)){
                    root = rightRotate(root);
                }else  if (height(root -> left -> right) > height(root -> left -> left)){
                    root -> left = leftRotate(root -> left);
                    root = rightRotate(root);
                }
            }else if (h < -1){
                if (height(root -> right -> left) < height(root -> right -> right))
                    root = leftRotate(root);
                else  if (height(root -> right -> right) < height(root -> right -> left)){
                    root -> right = rightRotate(root -> right);
                    root = leftRotate(root);
                }
            }

            root -> balancefactor = height(root -> left) - height(root -> right);
        }

        return root;
    }
}

int search(AVLtree root, char *route){
	if (root == NULL)
		return 0;

	int cmp = strcmp(root -> route, route);
	if (cmp == 0)
		return 1;
	else if (cmp > 0)
		return search(root -> left, route);
	else
		return search(root -> right, route);
}

int rule1check(char *realPath, char *path){
	//realPath is the route found in the tree.
	//path is the corrected input path.
	if (strlen(realPath) - strlen(path) == 1){
		int ans = 0;
		int i, j;
		
		for (i = 0; i < strlen(realPath); i++){
			char newRoute[MAX_ROUTE_LENGTH];
			int k = 0;
			for (j = 0; j < strlen(realPath); j++){
				if (j != i)
					newRoute[k++] = realPath[j];
			}

			newRoute[k] = '\0';

			ans = ans || !(strcmp(path, newRoute));
		}

		return ans;
	}
	else
		return 0;
}

int rule2check(char *realPath, char *path){
	int ans = 0;
	int i, j;
	
	for (i = 0; i < strlen(path); i++){
		char curr = path[i];
		char newRoute[MAX_ROUTE_LENGTH];
		int k = 0;
		for (j = 0; j < strlen(path); j++){
			if (path[j] != curr)
				newRoute[k++] = path[j];
		}

		newRoute[k] = '\0';

		ans = ans || !(strcmp(realPath, newRoute));
	}

	return ans;
}

void rule1suggestion(FILE *ostream, AVLtree root, char *path){
	if (root == NULL)
		return;

	if (rule1check(root -> route, path))
		fprintf(ostream, "%s ", root -> route);

	rule1suggestion(ostream, root -> left, path);
	rule1suggestion(ostream, root -> right, path);
}

void rule2suggestion(FILE *ostream, AVLtree root, char *path){
	if (root == NULL)
		return;

	if (rule2check(root -> route, path))
		fprintf(ostream, "%s ", root -> route);

	rule2suggestion(ostream, root -> left, path);
	rule2suggestion(ostream, root -> right, path);
}


int main(){
	AVLtree tree = NULL;

    FILE *fi = fopen(INPUT_FILE, "r");
    FILE *fo = fopen(OUTPUT_FILE, "a");

    int n;
    fscanf(fi, "%d", &n);
    char routeBuff[MAX_ROUTE_LENGTH];
    char correctedRoute[MAX_ROUTE_LENGTH];
    while (n-- > 0){
        fscanf(fi, "%s", routeBuff);
        int i, j = 0;
        char current = routeBuff[0];
        correctedRoute[j++] = current;

        for (i = 1; i < strlen(routeBuff); i++){
            if (routeBuff[i] != current){
                current = routeBuff[i];
                correctedRoute[j++] = current;
            }
        }
        correctedRoute[j] = '\0';
        tree = addNode(tree, correctedRoute);
    }   
    fclose(fi);

    FILE *fq = fopen(QUERY_FILE, "r");
    fscanf(fq, "%d", &n);

    while (n-- > 0){
    	fscanf(fi, "%s", routeBuff);
        int i, j = 0;
        char current = routeBuff[0];
        correctedRoute[j++] = current;

        for (i = 1; i < strlen(routeBuff); i++){
            if (routeBuff[i] != current){
                current = routeBuff[i];
                correctedRoute[j++] = current;
            }
        }
        correctedRoute[j] = '\0';

        fprintf(fo, "Corrections for the route \"%s\" : %s\n", routeBuff, correctedRoute);
        fprintf(fo, "Searching for the route \"%s\" : ", correctedRoute);
        int found = search(tree, correctedRoute);

        if (found)
        	fprintf(fo, "Found\n");
        else{
        	fprintf(fo, "Not Found\n");

        	fprintf(fo, "Alternate route suggestion:\n");
        	fprintf(fo, "Rule 1: ");
        	rule1suggestion(fo, tree, correctedRoute);
        	fprintf(fo, "\n");

        	fprintf(fo, "Rule 2: ");
        	rule2suggestion(fo, tree, correctedRoute);
        	fprintf(fo, "\n");

        }


    }
    fclose(fq);
    fclose(fo);

    return 0;
}


