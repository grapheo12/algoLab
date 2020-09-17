/* Name: Shubham Mishra
 * Roll No: 18CS10066
 * PC No: 80
 */

#include <iostream>
#include <fstream>
using namespace std;

int main(){
	freopen("18CS10066-lt-output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);

	int n;
	cin >> n;

	int *price = new int[n];

	for (int i = 0; i < n; i++)
		cin >> price[i];

	int k;
	cin >> k;

	/* Solution using Dynamic Programming (Efficient Solution)
	 * ========================================================
	 * Define dp[i][j] = max profit obtained in {0...i} days with at most j transactions.
	 * dp[i][j] = max{dp[i - 1][j], //Make no more transactions
                      price[i] - price[0], //Make only one transaction in the first and ith day,
                      for l = 1 : i - 1, price[i] - price[l] + dp[l - 1][j - 1]}
     * Base cases: if i == 0 || j == 0, dp[i][j] = 0;
     * Answer: dp[n - 1][k]
     * Complexity: O(n^2 * k)
	 */

	int **dp = new int*[n];
	for (int i = 0; i < n; i++){
		dp[i] = new int[k + 1];
		for (int j = 0; j <= k; j++)
			dp[i][j] = 0;
	}

	for (int j = 0; j <= k; j++){
		for (int i = 0; i < n; i++){
			if (j == 0 || i == 0)
				dp[i][j] = 0;
			else{
				int profit = dp[i - 1][j] > price[i] - price[0] ? dp[i - 1][j] : price[i] - price[0];
				for (int l = 1; l < i; l++){
					if (profit < (price[i] - price[l] + dp[l - 1][j - 1]))
						profit = (price[i] - price[l] + dp[l - 1][j - 1]);
				}
				dp[i][j] = profit;
			}
		}
	}

	cout << dp[n - 1][k] << endl;
	return 0;
}