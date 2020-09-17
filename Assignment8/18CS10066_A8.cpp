/* Name: Shubham Mishra
 * Roll No: 18CS10066
 */
#include <iostream>
#include <fstream>
using namespace std;

/* For Part 2 */
int computePath(int **rooms, int m, int n, int i, int j, int **dp){
	int ans = 1;
	int maxVal = 0;

	if (dp[i][j] != -1)
		return dp[i][j];
	int buff;
	//Up
	if (i > 0 && rooms[i][j] < rooms[i - 1][j]){
		buff = computePath(rooms, m, n, i - 1, j, dp);
		if (maxVal < buff)
			maxVal = buff;
	}

	//Down
	if (i < m - 1 && rooms[i][j] < rooms[i + 1][j]){
		buff = computePath(rooms, m, n, i + 1, j, dp);
		if (maxVal < buff)
			maxVal = buff;
	}

	//Left
	if (j > 0 && rooms[i][j] < rooms[i][j - 1]){
		buff = computePath(rooms, m, n, i, j - 1, dp);
		if (maxVal < buff)
			maxVal = buff;
	}

	//Right
	if (j < n - 1 && rooms[i][j] < rooms[i][j + 1]){
		buff = computePath(rooms, m, n, i, j + 1, dp);
		if (maxVal < buff)
			maxVal = buff;
	}

	dp[i][j] = ans + maxVal;


	return dp[i][j];
}

/* For Part 3 */
void fillTable(int **rooms, int m, int n, int **dp){
	int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++)
			if (dp[i][j] == -1)
				dp[i][j] = computePath(rooms, m, n, i, j, dp);
	}
}

int main(){
	int t;
	ifstream fi;
	ofstream fo;
	fi.open("input.txt");
	fo.open("output.txt");

	
	fi >> t;
	while (t-- > 0){
		int m, n;
		fi >> m >> n;
		int **rooms = new int*[m];
		int **dp = new int*[m];
		int i, j;
		for (i = 0; i < m; i++){
			rooms[i] = new int[n];
			dp[i] = new int[n];
			for (j = 0; j < n; j++){
				fi >> rooms[i][j];
				dp[i][j] = -1;
			}
		}

		/* Part 1 */
		for (i = m - 1; i >= 0; i--){
			for (j = n - 1; j >= 0; j--){
				int ans = 1;
				int maxVal = 0;
				if (i < m - 1 && rooms[i][j] < rooms[i + 1][j]){
					if (dp[i + 1][j] > maxVal)
						maxVal = dp[i + 1][j];
				}
				if (j < n - 1 && rooms[i][j] < rooms[i][j + 1]){
					if (dp[i][j + 1] > maxVal)
						maxVal = dp[i][j + 1];
				}


				dp[i][j] = ans + maxVal;

			}
		}

		int maxGames = 0;
		for (i = 0; i < m; i++){
			for (j = 0; j < n; j++){
				if (dp[i][j] > maxGames)
					maxGames = dp[i][j];
			}
		}

		fo << maxGames << " ";
		/* Part 1 END */

		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				dp[i][j] = -1;

		/* Part 2 */

		fo << computePath(rooms, m, n, 0, 0, dp) << " ";

		/* Part 2 END */

		/* Part 3 */
		fillTable(rooms, m, n, dp);
		maxGames = 0;
		for (i = 0; i < m; i++){
			for (j = 0; j < n; j++){
				if (dp[i][j] > maxGames)
					maxGames = dp[i][j];
			}
		}

		fo << maxGames << endl;
		/* Part 3 END */

	}

	return 0;
}
