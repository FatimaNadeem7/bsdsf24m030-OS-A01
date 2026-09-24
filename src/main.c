#include <stdio.h>
#include <stdlib.h>

#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main()
{
    printf("--- Testing String Functions ---\n");

    char str1[100] = "Hello";
    char str2[] = " World";
    char copy[100];

    printf("Length of str1: %d\n", mystrlen(str1));

    mystrcpy(copy, str1);
    printf("After mystrcpy: %s\n", copy);

    mystrncpy(copy, "Programming", 6);
    copy[6] = '\0';
    printf("After mystrncpy: %s\n", copy);

    mystrcat(str1, str2);
    printf("After mystrcat: %s\n", str1);

    printf("\n--- Testing File Functions ---\n");

    FILE* file = fopen("test.txt", "r");

    if (file == NULL)
    {
        printf("Could not open test.txt\n");
        return 1;
    }

    int lines;
    int words;
    int chars;

    if (wordCount(file, &lines, &words, &chars) == 0)
    {
        printf("Lines: %d\n", lines);
        printf("Words: %d\n", words);
        printf("Characters: %d\n", chars);
    }

    rewind(file);

    char** matches = NULL;

    int count = mygrep(file, "Linux", &matches);

    if (count >= 0)
    {
        printf("Lines containing 'Linux': %d\n", count);

        for (int i = 0; i < count; i++)
        {
            printf("%s", matches[i]);
            free(matches[i]);
        }

        free(matches);
    }

    fclose(file);

    return 0;
}
