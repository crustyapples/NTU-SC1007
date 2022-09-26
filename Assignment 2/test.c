#include <stdio.h>
#include <stdlib.h>

int strLen(char s[]);
void reverseString(char *s);
void swapBrackets(char *s);

int main() {
    char s[] = "99+(88-77)*(66/(55-44)+33)";
    reverseString(s);
    swapBrackets(s);
    printf("%s",&s);
}

int strLen(char s[]) {
    int i=0;
    for (i=0; s[i] != '\0'; ++i);
    return i;
}

void reverseString(char *s)  
{  
    int i,t;  
    int len = strLen(s); 
      
    for (i = 0; i < len/2; i++)  
    {  
        t = s[i];  
        s[i] = s[len - i - 1];  
        s[len - i - 1] = t;  
    }  
}

void swapBrackets(char *s) {
    int i=0;
    while (s[i] != '\0') {
        if (s[i] == '(') {
            s[i] = ')';
        } else if (s[i] == ')') {
            s[i] = '(';
        }
        i++;
    }
}