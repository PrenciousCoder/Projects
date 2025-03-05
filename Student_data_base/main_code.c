#include <stdio.h>
#include <stdlib.h>


//!Struct for marks
struct Subjects{
    int physics;
    int chemistry;
    int math;
    int german;
    int comp_sci;
};

//!Student struct
struct Student{
    int student_id;
    char name[50];
    int age;
    struct Subjects subjects;

};

