#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// // memory
// int **m;

int max(int x, int y) {
    if (x>y) return x;
    else if (y>x) return y;
    return x;
}

// 4
// 5
// 2 1 3 2
// 12 10 20 15

int bottom_up_dp(int n, int *s, int *v, int C)
{

    // // allocating memory t o m
    // m = (int **)malloc(sizeof(int *) * (n+1));

    // // m is a matrix of n rows and C columns
    // for(int i=0;i<=n;i++) {
    //     m[i] = (int *)malloc(sizeof(int) * (C+1));
    // }

    int m[100][100];
    
    //write your code here
    for (int item=1; item<=n; item++) {
        for (int capacity=1; capacity<=C; capacity++) {
            if (s[item] > capacity) m[item][capacity] = m[item-1][capacity];
            else m[item][capacity] = max(m[item-1][capacity], m[item-1][capacity-s[item]] + v[item]);
        }
    }

    return m[n][C];
}

 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;

    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}