/* Name: Shubham Mishra
 * Roll: 18CS10066
 * Assignment 7 Part 1
 */
#include <iostream>
#include <fstream>
#include <climits>

#define MIN(x, y) (x) > (y) ? (y) : (x)
#define MAX(x, y) (x) > (y) ? (x) : (y)
using namespace std;

int rec_opt(int start, int stop, int k){
	/* Base case: k = 1
	 * We must check one by one.
	 * Hence worst case ans is n.
	 *
	 * If k > 1, we can pick a position and
	 * Either do linear search or do recursive search for
	 * both parts left and right of that position.
	 * 
	 * Recursive definition:
	 * ans = MAX_INT
	 * for i = 1 -> m,
	 * 		buff1 = min(rec_opt(start, i - 1, k - 1), i - start + 1) //Dissolved in i
	 *		buff2 = min(rec_opt(i + 1, stop, k), stop - i) //Not dissolved
	 *		buff = max(buff1, buff2)	//Max as we are dealing with the worst case
	 *		ans = min(ans, buff)	
	 */

	if (k == 1)
		return (stop - start + 1);
	if (stop == start)
		return INT_MAX;

	int ans = INT_MAX;

	int i;
	for (int i = start + 1; i <= stop; i++){
		int buff1 = MIN(rec_opt(start, i - 1, k - 1), i - start);
		int buff2 = MIN(rec_opt(i + 1, stop, k), stop - i);
		int buff = MAX(buff1, buff2);
		buff++;
		ans = MIN(ans, buff);
	}

	return ans;
}

int main(){
	cout << rec_opt(0, 14, 2) << endl;
	cout << rec_opt(1, 15, 2) << endl;
	return 0;
}