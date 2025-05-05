#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 1024

void generateRandomText(char *buffer, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?";
    for (size_t i = 0; i < size - 1; i++) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buffer[size - 1] = '\0';
}

int insertLinear(char *table, int tableSize, char key, int *seen) {
    if (seen[(unsigned char)key]) return 0;
    seen[(unsigned char)key] = 1;

    int h = key % tableSize;
    int collisions = 0;

    while (1) {
        if (table[h] == 0) {
            table[h] = key;
            return collisions;
        }
        collisions++;
        h = (h + 1) % tableSize;
        if (collisions >= tableSize) return collisions;
    }
}

int insertQuadratic(char *table, int tableSize, char key, int *seen) {
    if (seen[(unsigned char)key]) return 0;
    seen[(unsigned char)key] = 1;

    int h = key % tableSize;
    int d = 1;
    int collisions = 0;

    while (1) {
        if (table[h] == 0) {
            table[h] = key;
            return collisions;
        }
        collisions++;
        if (d > tableSize) return collisions;
        h = h + d;
        if (h >= tableSize)
            h = h - tableSize;
        d += 2;
    }
}

int searchLinear(char *table, int tableSize, char key) {
    int h = key % tableSize;
    int steps = 0;

    while (steps < tableSize) {
        if (table[h] == 0)
            return -1;
        if (table[h] == key)
            return h;
        h = (h + 1) % tableSize;
        steps++;
    }
    return -1;
}

int searchQuadratic(char *table, int tableSize, char key) {
    int h = key % tableSize;
    int d = 1;
    int steps = 0;

    while (steps < tableSize) {
        if (table[h] == 0)
            return -1;
        if (table[h] == key)
            return h;
        h = h + d;
        if (h >= tableSize)
            h = h - tableSize;
        d += 2;
        steps++;
    }
    return -1;
}

void printTable(char *table, int tableSize, const char *label) {
    printf("\nСодержимое таблицы (%s):\n", label);
    printf("---------------------------\n");
    printf("| Индекс | Символ | ASCII |\n");
    printf("---------------------------\n");
    for (int i = 0; i < tableSize; i++) {
        if (table[i] != 0)
            printf("| %6d |   %3c   |  %4d |\n", i, table[i], (int)table[i]);
        else
            printf("| %6d |   ---   |  ---- |\n", i);
    }
    printf("---------------------------\n");
}

void demoSearch(char *table, int size, char key, const char *label, int (*searchFunc)(char *, int, char)) {
    int pos = searchFunc(table, size, key);
    if (pos >= 0)
        printf("Поиск символа '%c' (%d) в таблице %s: найден в позиции %d\n", key, key, label, pos);
    else
        printf("Поиск символа '%c' (%d) в таблице %s: не найден\n", key, key, label);
}

int main() {
    srand(time(NULL));

    int primes[] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    int primesCount = sizeof(primes) / sizeof(primes[0]);

    char *text = malloc(N + 1);
    generateRandomText(text, N + 1);

    printf("Исследование коллизий при открытой адресации:\n");
    printf("=================================================================\n");
    printf("| Размер таблицы | Уникальных | Линейные пробы | Квадратичные пробы |\n");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < primesCount; i++) {
        int size = primes[i];

        char *linearTable = calloc(size, sizeof(char));
        char *quadraticTable = calloc(size, sizeof(char));

        int linearCollisions = 0;
        int quadraticCollisions = 0;
        int seenLinear[256] = {0};
        int seenQuadratic[256] = {0};
        int uniqueSymbols = 0;

        for (int j = 0; j < N; j++) {
            if (!seenLinear[(unsigned char)text[j]])
                uniqueSymbols++;
            linearCollisions += insertLinear(linearTable, size, text[j], seenLinear);
            quadraticCollisions += insertQuadratic(quadraticTable, size, text[j], seenQuadratic);
        }

        printf("| %14d | %10d | %16d | %20d |\n",
               size, uniqueSymbols, linearCollisions, quadraticCollisions);

        free(linearTable);
        free(quadraticTable);
    }

    printf("=================================================================\n");

    int demoSize = 53;
    int n = 60;
    char *linearDemo = calloc(demoSize, sizeof(char));
    char *quadraticDemo = calloc(demoSize, sizeof(char));
    int seenLinearDemo[256] = {0};
    int seenQuadraticDemo[256] = {0};

    for (int i = 0; i < n; i++) {
        insertLinear(linearDemo, demoSize, text[i], seenLinearDemo);
        insertQuadratic(quadraticDemo, demoSize, text[i], seenQuadraticDemo);
    }

    printTable(linearDemo, demoSize, "Линейные пробы");
    printTable(quadraticDemo, demoSize, "Квадратичные пробы");

    printf("\nДемонстрация поиска символов:\n");

    for (int i = 0; i < 5; i++) {
        char key = text[rand() % N];
        demoSearch(linearDemo, demoSize, key, "линейные", searchLinear);
        demoSearch(quadraticDemo, demoSize, key, "квадратичные", searchQuadratic);
        printf("---\n");
    }

    printf("Поиск несуществующего символа '$':\n");
    demoSearch(linearDemo, demoSize, '$', "линейные", searchLinear);
    demoSearch(quadraticDemo, demoSize, '$', "квадратичные", searchQuadratic);

    free(linearDemo);
    free(quadraticDemo);
    free(text);

    return 0;
}
