/* Name: Shubham Mishra
 * Roll: 18CS10066
 * Assignment 7 Part 2
 */
#include <iostream>
#include <fstream>
#include <climits>

#define MIN(x, y) (x) > (y) ? (y) : (x)
#define MAX(x, y) (x) > (y) ? (x) : (y)

using namespace std;


int dp_opt(int start, int stop, int k, int** dp){
	/* Program logic follows from the recursive code.
	 * dp[i][j] = ans for i = stop - start + 1 number of test tubes and j tablets.
	 * We use Memoization (top-down) approach.
	 */

	if (k == 1)
		return dp[stop - start + 1][k] = (stop - start + 1);
	if (stop == start)
		return INT_MAX;
	if (dp[stop - start + 1][k] != -1)
		return dp[stop - start + 1][k];

	int ans = INT_MAX;

	int i;
	for (int i = start + 1; i <= stop; i++){
		int buff1, buff2;
		if (dp[i - start][k - 1] == -1)
			buff1 = MIN(dp_opt(start, i - 1, k - 1, dp), i - start);
		else
			buff1 = MIN(dp[i - start][k - 1], i - start);
		
		if (dp[stop - i][k] == -1)
			buff2 = MIN(dp_opt(i + 1, stop, k, dp), stop - i);
		else
			buff2 = MIN(dp[stop - i][k], stop - i);
		int buff = MAX(buff1, buff2);
		buff++;
		ans = MIN(ans, buff);
	}

	dp[stop - start + 1][k] = ans;
	return ans;
}

int main(){
	ifstream fi;
	ofstream fo;
	fi.open("input.txt");
	fo.open("output.txt");

	int testcases;
	fi >> testcases;

	while (testcases-- > 0){
		int n, k;
		fi >> k >> n;

		//Creating the dp table
		int **dp = new int*[n + 1];
		int i, j;
		for (i = 0; i < n + 1; i++){
			dp[i] = new int[k + 1];
			for (j = 0; j < k + 1; j++)
				dp[i][j] = -1;
		}

		fo << k << " " << n << " " << dp_opt(0, n - 1, k, dp) << endl;

		delete dp;
	}

	fi.close();
	fo.close(); 
	return 0;
}