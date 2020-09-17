/* Name: Shubham Mishra
 * Roll No: 18CS10066
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Table{
	public:
		int size, h;
		int *arr;

		Table(int size, int h){
			/* Key space: [0, 99]
			 * Empty cell: -1
			 * Deleted cell: -2
			 */
			this -> arr = new int[size];
			this -> h = h;
			this -> size = size;
			for (int i = 0; i < size; i++)
				arr[i] = -1;
		}

		int hash(int k){
			return ((k % 10) + k / 10) % this -> size;
		}

		int find(int key){
			int k = this -> hash(key);
			for (int i = 0; i < this -> h; i++)
				if (this -> arr[(k + i) % this -> size] == key)
					return (k + i) % this -> size;
			return -1;
		}

		void del(int key){
			int idx = this -> find(key);
			if (idx != -1)
				this -> arr[idx] = -2;
		}

		void insert(int nkey){
			if (this -> find(nkey) != -1)
				return;


			int key = this -> hash(nkey);
			
			int k = key;
			do{
				if (this -> arr[k] < 0)
					break;
				k = (k + 1) % this -> size;
			}while (k != key);
			
			if (k == key && this -> arr[k] >= 0)
				cout << "InsertionError " << nkey << endl;

			if ((k - key + this -> size) % this -> size < this -> h)
				this -> arr[k] = nkey;
			else{
				int i = (k - this -> h + 1 + this -> size) % this -> size;
				for (int j = 0; j < h - 1; j++){
					if ((k - hash(this -> arr[i]) + this -> size) % this -> size < this -> h){
						this -> arr[k] = this -> arr[i];
						this -> arr[i] = -1;
						break;
					}else{
						i = (i + 1) % this -> size;
					}
				}

				if (i == k)
					cout << "InsertionError " << nkey << endl;
				else
					this -> insert(nkey);
			}
		}
		
		void printmap(){
			for (int i = 0; i < this -> size; i++){
				if (this -> arr[i] >= 0)
					cout << arr[i] << " ";
			}

			cout << endl;
		}

		void printbitmap(){
			for (int i = 0; i < this -> size; i++){
				for (int j = 0; j < this -> h; j++){
					if (hash(this -> arr[(i + j) % this -> size]) == i)
						cout << 1;
					else
						cout << 0;
				}
				cout << endl;
			}
		}

};


int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int size, h;
	cin >> size >> h;
	getchar();

	Table *m = new Table(size, h);
	char cmd[4];
	int num;
	int buff;
	
	while (!feof(stdin)){
		strcpy(cmd, " ");
		scanf("%s %d", cmd, &num);
		// cout << cmd << buff << endl;
		getchar();
		if (strcmp(cmd, "in") == 0){
			for (int i = 0; i < num; i++){
				cin >> buff;
				// cout << buff << endl;
				m -> insert(buff);
				getchar();
			}
			m -> printmap();
		}else if (strcmp(cmd, "del") == 0){
			for (int i = 0; i < num; i++){
				cin >> buff;
				m -> del(buff);
				getchar();
			}
			m -> printmap();
		}
		
	}

	m -> printbitmap();

	return 0;
}