#include <stdio.h>

struct person {
    char firstName [15];
    char lastName [15];
    
    struct {
        int age;
        float height;
        float weight;
        char firstName [15];
    } Info, *InfoPtr;

    // struct person personP;
} student1;
     
typedef struct person person_t;
person_t *studentPtr = &student1;
person_t **studentPtrPtr = &studentPtr;

int main() {
    studentPtr->Info.age = 21;
    printf("Accesing Age from studentPtr: %d\n", studentPtr->Info.age);
    printf("Accesing Age from studentPtrPtr: %d\n", (*studentPtrPtr)->Info.age);
    return 0;
}