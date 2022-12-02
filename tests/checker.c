#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    FILE * studentFp;
    FILE * solFp;

    solFp = fopen(argv[1], "r");
    studentFp = fopen(argv[2], "r");

    if(solFp == NULL){
        printf("Unable to open sol file: %s\n", argv[1]);
        return 1;
    }

    if (studentFp == NULL){
        printf("Unable to open student output file: %s\n",argv[2]);
        return 1;
    }

    char solByte = 0;
    char studentByte = 0;
    int lineCount = 0;

    while ((solByte = getc(solFp)) != EOF){
        studentByte = getc(studentFp);
        if(solByte == '\n'){
            lineCount++;
        }
        if(lineCount > 3){
            if(studentByte != solByte){
                printf("Student byte and sol byte does not match\n");
                return 1;
            }
        }
    }
    fclose(studentFp);
    fclose(solFp);
    return 0;
}