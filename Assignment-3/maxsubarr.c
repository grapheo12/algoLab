#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int calc_array_sum(int *arr, int l, int r){
	//Calculates sum of arr from index l to r
	int i;
	int ans = 0;
	for (i = l; i <= r; i++)
		ans += arr[i];

	return ans;
}	


int Max_Cross_Seg(int *part1, int n1, int *part2, int n2){
	/* Checks by brute force all sub-array sums that have the boundary element.
	 * Then returns the maximum of these sums.
	 */

	int maxlsum = INT_MIN;
	int maxrsum = INT_MIN;

	int i;
	for (i = n1 - 1; i >= 0; i--){
		int buff = calc_array_sum(part1, i, n1 - 1);
		if (buff > maxlsum)
			maxlsum = buff;
	}
	for (i = 0; i < n2; i++){
		int buff = calc_array_sum(part2, 0, i);
		if (buff > maxrsum)
			maxrsum = buff;
	}

	return (maxlsum + maxrsum);
}

int Max_Seg(int *arr, int n){
	int all_negative = 1;
	int max = INT_MIN;

	int i;
	for (i = 0; i < n; i++){
		if (arr[i] > 0){
			all_negative = 0;
			break;
		}else{
			if (max < arr[i])
				max = arr[i];
		}
	}

	if (all_negative)		//One Base Case
		return max;
	else if (n == 1)		//Another Base Case
		return arr[0];
	else{
		int lmax = Max_Seg(arr, n / 2);
		int rmax = Max_Seg(arr + n / 2, n - n / 2);
		int cmax = Max_Cross_Seg(arr, n / 2, arr + n / 2, n - n / 2);

		int max = lmax;
		if (rmax > max)
			max = rmax;
		if (cmax > max)
			max = cmax;

		return max;
	}

}

int main(){
	FILE *fp = fopen("input.txt", "rb");
	int n;

	fscanf(fp, "%d", &n);
	int *arr = (int*)malloc(n * sizeof(int));
	
	int i;
	for (i = 0; i < n; i++)
		fscanf(fp, "%d", arr + i);

	printf("%d\n", Max_Seg(arr, n));
	fclose(fp);
	return 0;
}