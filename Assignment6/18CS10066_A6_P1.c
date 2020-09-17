/* Name: Shubham Mishra
 * Roll: 18CS10066
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MAX_ROUTE_LENGTH 100
#define INPUT_FILE "Routes.txt"
#define OUTPUT_FILE "Output.txt"

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


int main(){
    AVLtree tree = NULL;

    FILE *fi = fopen(INPUT_FILE, "r");
    FILE *fo = fopen(OUTPUT_FILE, "w");

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
        printf("Detected route: %s\n", routeBuff);
        printf("Adding Route: %s\n", correctedRoute);
        tree = addNode(tree, correctedRoute);
    }
    
    fclose(fi);
    fprintf(fo, "%d\n", height(tree));
    preorderTraverse(fo, tree);
    fprintf(fo, "\n");

    return 0;
}