/* Name: Shubham Mishra
 * Roll No: 18CS10066
 */

#include "bits/stdc++.h"
#define MAX_SIZE 100
#define MAX_LIT 50
using namespace std;

class formula{
	public:
		int type;
		int *lhs;
		int rhs;
		int n_lhs;
		/*Type:
			1 -> IMP x
			2 -> x AND y IMP z
			3 -> NEG x OR NEG y
		*/

		bool evaluate(bool *val){
			if (this -> type == 1){
				return val[rhs];
			}else if (this -> type == 2){
				bool res_lhs = true;
				for (int i = 0; i < this -> n_lhs; i++){
					res_lhs = res_lhs && val[lhs[i]];
				}

				if (res_lhs)
					return val[rhs];
				else
					return true;
			}else{
				bool res_lhs = true;
				for (int i = 0; i < this -> n_lhs; i++){
					res_lhs = res_lhs && val[lhs[i]];
				}

				return !res_lhs;
			}
		}

		formula(int type, int n_lhs){
			this -> type = type;
			this -> n_lhs = n_lhs;
			lhs = new int[n_lhs];
		}
};


int find_lit_index(char *lits, int *n, char c){
	for (int i = 0; i < *n; i++){
		if (c == lits[i])
			return i;
	}
	lits[*n] = c;
	*n = *n + 1;
	return *n - 1;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	/*Input parser
	 * Assumes all literals to be a single lowercase alphabet
	 */
	int n_stat;
	cin >> n_stat;
	getchar();
	formula **stmt = new formula*[n_stat];
	char lits[MAX_LIT];
	int n_lit = 0;
	char buff[MAX_SIZE];

	for (int i = 0; i < n_stat; i++){	
		scanf("%[^\n]s", buff);
		getchar();
		if (strncmp(buff, "IMP", 3) == 0){
			//Type 1
			stmt[i] = new formula(1, 1);
			stmt[i] -> rhs = find_lit_index(lits, &n_lit, buff[4]);
		}else if (strncmp(buff, "NEG", 3) == 0){
			//Type 3
			char buff_lit[MAX_LIT];
			int j = 0, k = 0;
			for (int j = 0; j < strlen(buff); j++){
				if (buff[j] >= 'a' && buff[j] <= 'z')
					buff_lit[k++] = buff[j];
			}

			stmt[i] = new formula(3, k);
			for (int j = 0; j < k; j++)
				stmt[i] -> lhs[j] = find_lit_index(lits, &n_lit, buff_lit[j]);
		}else{
			//Type 2
			char buff_lit[MAX_LIT];
			int j = 0, k = 0;
			for (int j = 0; j < strlen(buff); j++){
				if (buff[j] >= 'a' && buff[j] <= 'z')
					buff_lit[k++] = buff[j];
			}

			stmt[i] = new formula(2, k - 1);
			for (int j = 0; j < k - 1; j++)
				stmt[i] -> lhs[j] = find_lit_index(lits, &n_lit, buff_lit[j]);
			stmt[i] -> rhs = find_lit_index(lits, &n_lit, buff_lit[k - 1]);
		}

	}
	/*Parser end*/

	/*GreedyFrog(phi)*/

	bool ans[n_lit];
	bool assigned[n_lit];
	for (int i = 0; i < n_lit; i++){
		ans[i] = false;
		assigned[i] = false;
	}

	//All literals in Type 1 Statements are to be set true
	for (int i = 0; i < n_stat; i++){
		if (stmt[i] -> type == 1){
			ans[stmt[i] -> rhs] = true;
			assigned[stmt[i] -> rhs] = true;
		}
	}

	//Second pass for Type 2 statement
	//If any type 2 stmt is false,
	//Its RHS must be set fixedly to True
	for (int i = 0; i < n_stat; i++){
		if (stmt[i] -> type == 2 && !stmt[i] -> evaluate(ans)){
			ans[stmt[i] -> rhs] = true;
			assigned[stmt[i] -> rhs] = true;
			bool check = true;
			for (int j = 0; j <= i; j++){
				if (stmt[j] -> type == 2)
					check = check && stmt[j] -> evaluate(ans);
			}

			if (!check){
				cout << "unsatisfiable" << endl;
				return 0;
			}

		}
	}

	//Third Pass for Type 3 statement
	//If any type 3 statement is false
	//The statement will be always unsatisfiable
	for (int i = 0; i < n_stat; i++){
		if (stmt[i] -> type == 3 && !stmt[i] -> evaluate(ans)){
			cout << "unsatisfiable" << endl;
			return 0;
		}
	}

	for (int i = 0; i < n_lit - 1; i++){
		cout << lits[i] << " = " << (ans[i] ? "true" : "false") << ", ";
	}

	cout << lits[n_lit - 1] << " = " << (ans[n_lit - 1] ? "true" : "false") << "\nsatisfiable" << endl;

	return 0; 
}