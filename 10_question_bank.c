#include <stdio.h>

void generate_question_file() {
    FILE *file = fopen("question_bank.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "What is the output of printf(\"%%d\", 5+3);?\n");
    fprintf(file, "7\n8\n5\n3\n");
    fprintf(file, "B\n30\n1000\n");

    fprintf(file, "Which data type is used to store a single character in C?\n");
    fprintf(file, "char\nint\nfloat\ndouble\n");
    fprintf(file, "A\n30\n2000\n");

    fprintf(file, "Which loop executes at least once even if the condition is false?\n");
    fprintf(file, "for\ndo-while\nwhile\nnone\n");
    fprintf(file, "B\n30\n3000\n");

    fprintf(file, "Which header file is required for memory allocation functions like malloc?\n");
    fprintf(file, "stdio.h\nstdlib.h\nmath.h\nconio.h\n");
    fprintf(file, "B\n30\n5000\n");

    fprintf(file, "What is the time complexity of quicksort in the best case?\n");
    fprintf(file, "O(n^2)\nO(n log n)\nO(n)\nO(log n)\n");
    fprintf(file, "B\n30\n10000\n");

    fprintf(file, "What does the 'static' keyword signify in C?\n");
    fprintf(file, "Global variable\nLocal variable with persistent value\nCompile-time constant\nNone\n");
    fprintf(file, "B\n45\n20000\n");

    fprintf(file, "Which sorting algorithm has the worst case time complexity of O(n^2)?\n");
    fprintf(file, "Merge Sort\nHeap Sort\nQuick Sort\nBubble Sort\n");
    fprintf(file, "D\n45\n40000\n");

    fprintf(file, "Which concept allows function overloading in C?\n");
    fprintf(file, "Polymorphism\nEncapsulation\nFunction Pointers\nNone\n");
    fprintf(file, "C\n45\n80000\n");

    fprintf(file, "Which C function is used to deallocate memory?\n");
    fprintf(file, "malloc\ncalloc\nfree\nrealloc\n");
    fprintf(file, "C\n45\n160000\n");

    fprintf(file, "What is the maximum number of recursive calls allowed in C?\n");
    fprintf(file, "Depends on memory\n1000\n10^5\nInfinite\n");
    fprintf(file, "A\n45\n320000\n");

    fprintf(file, "Which of these is not a valid C storage class?\n");
    fprintf(file, "auto\nregister\ndefault\nstatic\n");
    fprintf(file, "C\n60\n640000\n");

    fprintf(file, "Which operator has the highest precedence in C?\n");
    fprintf(file, "&&\n||\n==\n()\n");
    fprintf(file, "D\n60\n1250000\n");

    fprintf(file, "Which C standard introduced the 'bool' data type?\n");
    fprintf(file, "C89\nC99\nC11\nC17\n");
    fprintf(file, "B\n60\n2500000\n");

    fprintf(file, "What is the purpose of volatile keyword in C?\n");
    fprintf(file, "Ignore optimizations\nMake variable constant\nPrevent overwriting\nNone\n");
    fprintf(file, "A\n60\n5000000\n");

    fprintf(file, "Which memory segment does dynamically allocated memory reside in?\n");
    fprintf(file, "Stack\nHeap\nCode\nRegister\n");
    fprintf(file, "B\n60\n10000000\n");

    fclose(file);
    printf("C questions file generated successfully as 'question_bank.txt'!\n");
}

int main() {
    generate_question_file();
    return 0;
}