//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int max(int a,int b)
{
	if(a > b)
	  return a;
	else
	  return b;
}

int part_1(int** x ,int rows , int cols)
{
   int i,j,temp,maxi,t1,t2;
   int count_games[rows][cols];
   for(i = 0; i < rows ; i++)
   {
   	 for(j = 0 ; j < cols ; j++)
   	 	count_games[i][j] = 0;
   } 
   
   for(i = rows-1 ; i >= 0 ;i--)
   {
   	  for(j = cols-1 ; j >= 0 ;j--)
      {   
      	t1 = t2 = 0;
      	if(j == cols-1 && i == rows-1)
      	{
      		count_games[i][j] = 1;
      	}
      	else if(j == cols-1)
      	{
           if(x[i][j] < x[i+1][j])
    	   count_games[i][j] = 1 + count_games[i+1][j];
      	}
      	else if(i == rows-1)
      	{
      	  if(x[i][j] < x[i][j+1])
    	   count_games[i][j] = 1 + count_games[i][j+1];
      	}
      	else
        {
          if(x[i][j] < x[i][j+1])
    	   t1 = 1 + count_games[i][j+1];
          if(x[i][j] < x[i+1][j])
   	        t2 = 1 + count_games[i+1][j];
   	      count_games[i][j] = max(t1 , t2);
     	}
      }
   }
    maxi = INT_MIN;
    for(i = 0 ; i < rows ; i++)
      {
      	for(j = 0 ; j < cols ; j++)
      	{
      		if(count_games[i][j] > maxi)
      			maxi = count_games[i][j];
      	}
      }
   return maxi;
}

int part_2_recursive(int **mat ,int **dp , int rows, int cols , int i , int j)
{
	if(dp[i][j] != 0)
		return dp[i][j];
	int t1,t2,t3,t4;
	t1 = 1;
	t2 = 1;
	t3 = 1;
	t4 = 1;
	if((j+1) < cols && mat[i][j] < mat[i][j+1])
		t1 = part_2_recursive(mat,dp,rows,cols,i,j+1)+1;
	if((j-1) >= 0 && mat[i][j] < mat[i][j-1])
		t2 = part_2_recursive(mat,dp,rows,cols,i,j-1)+1;
	if((i+1) < rows && mat[i][j] < mat[i+1][j])
		t3 = part_2_recursive(mat,dp,rows,cols,i+1,j)+1;
	if((i-1) >= 0 && mat[i][j] < mat[i-1][j])
		t4 = part_2_recursive(mat,dp,rows,cols,i-1,j)+1;
    dp[i][j] = max(max(t1 , t2) , max(t3 , t4));
    return dp[i][j];
}

int main()
{
	  int test,rows,cols,ans,i,j,maxi,i1,j1,temp;
	  FILE *fp_input,*fp_output;
    fp_input = fopen("input.txt","r");
    fp_output = fopen("output.txt","w");
    fscanf(fp_input,"%d",&test);
	  while(test--)
	 {
      fscanf(fp_input,"%d",&rows);
      fscanf(fp_input,"%d",&cols);
      int** x = (int**)malloc(rows * sizeof(int*));
      for (i=0; i<rows; i++)
      {
         x[i] = (int*)malloc(cols * sizeof(int));
      }
      int** dp = (int**)malloc(rows * sizeof(int*));
      for (i=0; i<rows; i++)
      {
         dp[i] = (int*)malloc(cols * sizeof(int));
      }
      for(i = 0 ; i < rows ; i++)
      {
      	for(j = 0 ; j < cols ; j++)
      	{
      	   fscanf(fp_input,"%d",&x[i][j]);
      	}
      }

      ans = part_1(x, rows, cols);
      fprintf(fp_output, "%d ", ans);
      printf("%d ", ans);

      for(i = 0 ; i < rows ; i++)
      {
      	for(j = 0 ; j < cols ; j++)
      	{
      	  dp[i][j] = 0;
      	}
      }
     
      ans = part_2_recursive(x,dp, rows, cols, 0, 0);
      fprintf(fp_output, "%d ", ans);
      printf("%d ", ans);
       //part 3
       maxi = INT_MIN;
       for(i = 0 ; i < rows ; i++)
       {
      	for(j = 0 ; j < cols ; j++)
      	{
          temp = part_2_recursive(x,dp, rows, cols,i, j);
      	  if(temp > maxi)
      	  	maxi = temp;
      	}
      }
      ans = maxi;
      fprintf(fp_output, "%d\n", ans);
      printf("%d\n", ans);
	}
	fclose(fp_output);
	fclose(fp_input);
	return 0;
}




