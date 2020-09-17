/* Name: Shubham Mishra
 * Roll No: 18CS10066
 */
#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
using namespace std;

class Cell{
	public: 
		int val;
		int rank;
		Cell *parent;

		Cell(int value){
			//Make Set
			this -> val = value;
			this -> rank = 0;
			this -> parent = this;
		}

		Cell * find(){
			//Find Set
			Cell *tmp = this -> parent;
			while (tmp != this -> parent -> parent)
				tmp = this -> parent -> find();
			return tmp;
		}
};

void unionSet(Cell *sx, Cell *sy){
	//Union by rank
	Cell *xroot = sx -> find();
	Cell *yroot = sy -> find();

	if (xroot -> rank == yroot -> rank){
		yroot -> parent = xroot;
		xroot -> rank += 1;
	}else if (xroot -> rank < yroot -> rank)
		xroot -> parent = yroot;
	else
		yroot -> parent = xroot;
}

int printPath(Cell ***mat, int n, int i, int j, char **s, int *k, int mov){
	/*Mov determines the direction from which movement is occuring
	 *1 : Moved from top
	 *2 : Moved from bottom
	 *3 : Moved from left
	 *4 : Moved from right
	 */

	if (i == n - 1 && mat[0][0] -> find() == mat[i][j] -> find()){
		sprintf(s[(*k)], "(%d, %d)\n", i, j);
		(*k)++;
		return 1;
	}

	if (mat[i][j] -> find() == mat[0][0] -> find()){
		if (mov != 2 && i < n - 1 && printPath(mat, n, i + 1, j, s, k, 1)){
			sprintf(s[(*k)], "(%d, %d)\n", i, j);
			(*k)++;
			return 1;
		}else if (mov != 4 && j < n - 1 && printPath(mat, n, i, j + 1, s, k, 3)){
			sprintf(s[(*k)], "(%d, %d)\n", i, j);
			(*k)++;
			return 1;
		}else if (mov != 3 && j > 0 && printPath(mat, n, i, j - 1, s, k, 4)){
			sprintf(s[(*k)], "(%d, %d)\n", i, j);
			(*k)++;
			return 1;
		}else if (mov != 1 && i > 0 && printPath(mat, n, i - 1, j, s, k, 2)){
			sprintf(s[(*k)], "(%d, %d)\n", i, j);
			(*k)++;
			return 1;
		}
	}

	return 0;
}

int main(){
	ifstream fi;
	fi.open("input.txt");

	int n, buff;
	fi >> n;

	Cell *** mat = new Cell**[n];
	for (int i = 0; i < n; i++){
		mat[i] = new Cell*[n];
		for (int j = 0; j < n; j++){
			fi >> buff;
			mat[i][j] = new Cell(buff);
		}
	}

	for (int j = 1; j < n; j++)
		unionSet(mat[0][0], mat[0][j]);

	for (int i = 1; i < n; i++){
		for (int j = 0; j < n; j++){
			if (mat[i][j] -> val == 1){
				if (j > 0 && mat[i][j - 1] -> val == 1)
					unionSet(mat[i][j - 1], mat[i][j]);
				if (mat[i - 1][j] -> val == 1)
					unionSet(mat[i - 1][j], mat[i][j]);
			}
		}
	}

	fi.close();

	char **path = new char*[n * n];
	for (int i = 0; i < n * n; i++){
		path[i] = new char[100];
		strcpy(path[i], "");
	}

	int k;
	k = 0;
	cout << "Output of part 2" << endl;
	printPath(mat, n, 0, 0, path, &k, 3);

	for (; k >= 0; (k)--)
		cout << path[(k)] << endl;
	
	return 0;


}