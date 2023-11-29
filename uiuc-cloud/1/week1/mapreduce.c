#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

void map(const char* line, WordCount* wordCounts, int* numWords) {
    char* token = strtok((char*)line, " \t\n\r");
    while (token != NULL) {
        int i;
        for (i = 0; i < *numWords; i++) {
            if (strcmp(wordCounts[i].word, token) == 0) {
                wordCounts[i].count++;
                break;
            }
        }
        if (i == *numWords) {
            strncpy(wordCounts[*numWords].word, token, MAX_WORD_LENGTH);
            wordCounts[*numWords].count = 1;
            (*numWords)++;
        }
        token = strtok(NULL, " \t\n\r");
    }
}

void reduce(WordCount* wordCounts, int numWords) {
    int i;
    for (i = 0; i < numWords; i++) {
        printf("%s: %d\n", wordCounts[i].word, wordCounts[i].count);
    }
}

int main() {
    FILE* file = fopen("./input.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    char line[1000];
    WordCount wordCounts[1000];
    int numWords = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        map(line, wordCounts, &numWords);
    }

    reduce(wordCounts, numWords);

    fclose(file);
    return 0;
}