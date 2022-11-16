#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//memory
int *r;
int *r2;
int *first;
int *second;


int cr_bottom_up_dp_print(int *p, int n)
{
    //write your code here
    r[0] = 0;
    int k=0;

    for (int j=1;j<=n;j++) {
        for (int i=1;i<=j;i++)
        {
            int temp = p[i] + r[j-i];
            
            if (temp > r[j])
                r[j] = temp;
                r2[k] = temp;
                first[k] = j-i;
                second[k] = i;
                k++;
                // printf("revenue: %d,lengths: %d, %d\n",temp,j-i,i);
        }
    }

    for (int i = 0; i<=k; i++) {
        if (r[n] == r2[i]) {
            printf("revenue: %d,lengths: %d, %d\n",r2[i],first[i],second[i]);
            break;
        }
        
    }
    
    return r[n];
}

 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,4,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    r2 = malloc(sizeof(int) * (n+1));
    first = malloc(sizeof(int) * (n+1));
    second = malloc(sizeof(int) * (n+1));
    
    //set all memory elements to -1
    for (i=0; i<=n; i++)
        r[i] = -1;
   
    printf("The maximum value is: %d \n", cr_bottom_up_dp_print(p,n));
}