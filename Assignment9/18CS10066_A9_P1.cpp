/* Name: Shubham Mishra
 * Roll No: 18CS10066
 */
#include <iostream>
#include <fstream>
#include <climits>
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
			//Find Set using path compression
			while (this -> parent != this -> parent -> parent)
				this -> parent = this -> parent -> find();
			return this -> parent;
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




int main(){
	ifstream fi;
	//ofstream cout;
	fi.open("input.txt");
	//cout.open("output.txt");


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
	cout << "Output of Part 1" << endl;
	for (int j = 0; j < n; j++){
		if (mat[n - 1][j] -> val == 1 && mat[n - 1][j] -> find() == mat[0][0] -> find()){
			cout << "YES" << endl;
			return 0;
		}
	}

	cout << "NO" << endl;

	return 0;

}