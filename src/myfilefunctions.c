#include "../include/myfilefunctions.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int wordCount(FILE* file, int* lines, int* words, int* chars)
{
    int c;
    int inWord = 0;

    if (file == NULL || lines == NULL || words == NULL || chars == NULL)
    {
        return -1;
    }

    *lines = 0;
    *words = 0;
    *chars = 0;

    while ((c = fgetc(file)) != EOF)
    {
        (*chars)++;

        if (c == '\n')
        {
            (*lines)++;
        }

        if (isspace(c))
        {
            inWord = 0;
        }
        else if (!inWord)
        {
            (*words)++;
            inWord = 1;
        }
    }

    if (ferror(file))
    {
        return -1;
    }

    return 0;
}

int mygrep(FILE* fp, const char* search_str, char*** matches)
{
    char* line = NULL;
    size_t length = 0;
    ssize_t read;
    int count = 0;

    if (fp == NULL || search_str == NULL || matches == NULL)
    {
        return -1;
    }

    *matches = NULL;

    rewind(fp);

    while ((read = getline(&line, &length, fp)) != -1)
    {
        if (strstr(line, search_str) != NULL)
        {
            char** temp = realloc(*matches,
                                  (count + 1) * sizeof(char*));

            if (temp == NULL)
            {
                free(line);

                for (int i = 0; i < count; i++)
                {
                    free((*matches)[i]);
                }

                free(*matches);
                *matches = NULL;

                return -1;
            }

            *matches = temp;

            (*matches)[count] = malloc((read + 1) * sizeof(char));

            if ((*matches)[count] == NULL)
            {
                free(line);

                for (int i = 0; i < count; i++)
                {
                    free((*matches)[i]);
                }

                free(*matches);
                *matches = NULL;

                return -1;
            }

            strcpy((*matches)[count], line);
            count++;
        }
    }

    free(line);

    if (ferror(fp))
    {
        for (int i = 0; i < count; i++)
        {
            free((*matches)[i]);
        }

        free(*matches);
        *matches = NULL;

        return -1;
    }

    return count;
}
