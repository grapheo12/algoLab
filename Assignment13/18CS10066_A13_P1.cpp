/* Name: Shubham Mishra
 * Roll: 18CS10066
 */

#include "bits/stdc++.h"
using namespace std;

class BTree{
	public:
		string *keys;
		BTree **children;
		BTree *parent;
		int m, k;
		
		BTree(int m){
			keys = new string[m];
			children = new BTree*[m + 1];
			for (int i = 0; i <= m; i++)
				children[i] = NULL;
			parent = NULL;
			this -> m = m;
			k = 0;
		}

		BTree* insert(string key){
			int i;
			bool leaf = true;
			for (int i = 0; i <= m; i++){
				leaf = leaf && (children[i] == NULL);
			}

			if (!leaf){
				if (k < m){
					if (k == 0 || key < keys[0]){
						k++;
						for (int j = k; j > 0; j--)
							keys[j] = keys[j - 1];
						keys[0] = key;
					}else{
						for (int i = 0; i < k; i++){
							if (keys[i] < key && keys[i + 1] > key)
								break;
						}
						k++;
						for (int j = k; j > i + 1; j--){
							keys[j] = keys[j - 1];
						}
						keys[i + 1] = key;
					}

					// keys[k++] = key;
					return this;
				}else if (k == m){
					BTree *leftNode = new BTree(m);
					BTree *rightNode = new BTree(m);

					int k = 0;
					for (int i = 0; i < m / 2; i++){
						leftNode -> keys[k] = keys[i];
						leftNode -> children[k] = children[i];

						rightNode -> keys[k] = keys[i + m / 2];
						rightNode -> children[k] = children[i + m / 2];
						k++; 
					}

					rightNode -> children[k] = children[m];
					return overflowUp(leftNode, rightNode, keys[m / 2]);
				}
			}else{
				if (keys[0] > key){
					if (children[0] == NULL){
						children[0] = new BTree(m);
						children[0] -> parent = this;
					}

					children[0] = children[0] -> insert(key);
					return this;
				}

				for (i = 0; i < k - 1; i++){
					if (keys[i] < key && keys[i + 1] > key)
						break;
				}

				if (i == k - 1 && k < m){
					keys[k++] = key;
					return this;
				}else if (i == k - 1 && k == m)

				if (children[i + 1] == NULL){
					children[i + 1] = new BTree(m);
					children[0] -> parent = this;
				}
			}			
		}
		

		BTree* overflowUp(BTree* left, BTree* right, string s){
			if (parent == NULL){
				parent = new BTree(m);
				parent -> insert()
			}
		}

		bool search(string key){
			if (key < keys[0]){
				if (children[0] == NULL)
					return false;
				else
					return children[0] -> search(key);
			}

			for (int i = 0; i < k; i++){
				if (key == keys[i])
					return true;
				else if (key > keys[i]){
					if (children[i] == NULL)
						return false;
					else
						return children[0] -> search(key);
				}
			}
		}
};

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int m;
	cin << m;
	BTree *tree = new BTree[m - 1];

	//Search is implemented fully.
	//Insertion is half implemented.
	//OverflowUp function is incomplete.
	
	return 0;
}
