//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int maximum(int a,int b)
{
  if(a > b)
   return a;
  else
   return b;
}

int capsule_recursive(int n , int k)
{ 
  /*
  Base cases :
  3
  -> if  n = 0 
    If there are no test tubes -- no trials needed
  -> if n = 1 
    If there is one test tube -- one trial needed 
  -> if k = 1
    We need n trials for one capsule and n test tubes 

  Recurrence relation :
  capsule_recursive(n,k) = 1 + minimum(max(capsule_recursive(p - 1, k -1), capsule_recursive(n-p , k)) for p = [1 to n] )
  
  Explanation of recurrence :
    consider pth test tube 
    if it dissolves we have to find in p-1 test tubes before it using k-1 capsules (we wasted 1 -> dissolved)
    if it does not dissolves we have to find in n - p  test tubes using k capsules (not dissolved)
    we have to find worst case -- we find max of them 
    we find min of all p i.e, optimal p -- critical
  */
  if (n == 0) 
    return 0;
  if(n == 1)
  	return 1;
  if (k == 1) 
	return n; 
  int p,min_trails, temp ,ans;
  min_trails = INT_MAX; 
  for (p = 1; p <= n; p++) 
  { 
      temp = maximum(capsule_recursive(p-1,k-1),capsule_recursive(n-p,k)); 
      if (temp < min_trails) 
	min_trails = temp; 
  } 
  ans = min_trails + 1; 
  return ans;
} 

int capsule_dp(int n , int k)
{ 

   int array[k+1][n+1];
   int i,j,p,temp;

  //initialize with base cases
  for (i = 1; i <= k; i++) 
  { 
    array[i][1] = 1; // n = 0
    array[i][0] = 0; // n = 1
  } 
  for (i = 1; i <= n; i++) 
    array[1][i] = i; // k = 1
  
  //bottom-up dp
  for (i = 2; i <= k; i++) 
  { 
    for (j = 2; j <= n; j++) 
    { 
      array[i][j] = INT_MAX; 
      for (p = 1; p <= j; p++) 
      { 
        temp = 1 + maximum(array[i-1][p-1], array[i][j-p]); 
        if (temp < array[i][j]) 
          array[i][j] = temp; 
      } 
    } 
  } 
	
  return array[k][n]; 
} 

int main()
{
   FILE *fp_input,*fp_output;
   int t,n,k,i,min_trails;
   fp_input = fopen("input.txt","r");
   fp_output = fopen("output.txt","w");

   fscanf(fp_input,"%d",&t);
   
   while(t--)
   {
      fscanf(fp_input,"%d",&k);
      fscanf(fp_input,"%d",&n);
      fprintf(fp_output,"%d ", k);
      fprintf(fp_output,"%d ", n);
      min_trails = capsule_recursive(n,k);
      fprintf(fp_output,"%d\n", min_trails);
   }

  fclose(fp_input);
  fclose(fp_output);
  return 0;
}

