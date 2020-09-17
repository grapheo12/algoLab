/* Name: Shubham Mishra
 * Roll No: 18CS10066
 * Without using path compression
 */

#include <iostream>
#include <fstream>
#include <climits>
#include <cstring>
using namespace std;

class Cell{
	public: 
		int x;
		int y;
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

class multiBst{
	//Implementation of MultiSet
	public:
		int x;
		int y;
		int freq;
		multiBst *left;
		multiBst *right;

		multiBst(int x, int y){
			this -> x = x;
			this -> y = y;
			this -> freq = 1;
			this -> left = NULL;
			this -> right = NULL;
		}

		void insert(int x, int y){
			if (this -> x == x && this -> y == y)
				this -> freq += 1;
			else if (this -> x > x){
				if (this -> left == NULL)
					this -> left = new multiBst(x, y);
				else
					this -> left -> insert(x, y);
			}else if (this -> x <= x && this -> y > y){
				if (this -> left == NULL)
					this -> left = new multiBst(x, y);
				else
					this -> left -> insert(x, y);
			}else{
				if (this -> right == NULL)
					this -> right = new multiBst(x, y);
				else
					this -> right -> insert(x, y);
			}
		}

		void preorderTraverseMax(int *ans){
			if (*ans < this -> freq)
				*ans = this -> freq;
			if (this -> left != NULL)
				this -> left -> preorderTraverseMax(ans);
			if (this -> right != NULL)
				this -> right -> preorderTraverseMax(ans);
		}
};

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
			mat[i][j] -> x = i;
			mat[i][j] -> y = j;
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

	multiBst *t = new multiBst(0, 0);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (mat[i][j] -> val == 1 && !(i == 0 && j == 0)){
				t -> insert(mat[i][j] -> find() -> x, mat[i][j] -> find() -> y);
			}
		}
	}

	int ans = INT_MIN;
	t -> preorderTraverseMax(&ans);

	cout << "Output of part 4" << endl;
	cout << ans << endl;

}