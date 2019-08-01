//(c)ubc
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

 int Max_Cross_Seg(int *a,int n)
 {
    int i,sum,direct_left,direct_right,temp_sum,net;

    direct_left = direct_right = INT_MIN;
    
    temp_sum = 0; 
    for (i =(n-1)/2;i >= 0;i--) //left traversing
    { 
        temp_sum = temp_sum + a[i]; 
        if (temp_sum > direct_left) 
          direct_left = temp_sum; 
    } 

    temp_sum = 0; 
    for (i=(n+1)/2;i<=(n-1);i++) //right traversing
    { 
        temp_sum = temp_sum + a[i]; 
        if (temp_sum > direct_right) 
          direct_right = temp_sum; 
    } 

    net = direct_right +direct_left; // adding both

    return net;
 }

int maximum(int a, int b, int c)
 {
    if((a>=b) && (a>=c))
    	return a;
    else if(b >= c)
    	return b;
    else 
    	return c;
 }

 int Max_Seg(int *a,int n)
 {
 	int left_seg_max,right_seg_max,cross_seg_max;
 	int max_val,half;
    
    if(n <= 1)
    {
       max_val = a[0];
    }

    else
    { 
      if(n%2 == 0)
      	half = (n+1)/2;
      else
      	half = n/2;

      left_seg_max = Max_Seg(a,half); 
      right_seg_max = Max_Seg(a+half,n-half); 
      cross_seg_max = Max_Cross_Seg(a,n); 

      max_val = maximum(left_seg_max,right_seg_max,cross_seg_max);
    }

   return max_val;
 }
 
int main()
{
  // FILE *file_pointer;
  int n,i,max_val;
  //file_pointer = fopen("input.txt","r"); 
  scanf("%d",&n);
  int a[n];
  for(i=0;i<n;i++)
  {
  	scanf("%d",&a[i]);
  }
  max_val = Max_Seg(a,n);
  printf("%d\n",max_val);
 // fclose(file_pointer);
  return 0;
}