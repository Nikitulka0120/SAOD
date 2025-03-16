#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int n, int A[]) {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

int CheckSum(int n, int A[]) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

int RunNumber(int n, int A[]) {
    if (n == 0) return 0;
    int series = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) {
            series++;
        }
    }
    return series;
}

void PrintMas(int n, int A[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int selectionSort(int n, int A[]) {
    int C = 0, M = 0;
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            C++;
            if (A[j] < A[k]) {
                k = j;
            }
        }
        if (k != i) {
            M++;
            int temp = A[i];
            A[i] = A[k];
            A[k] = temp;
        }
    }
    return C + M;
}

int binaryV1(int n, int A[], int X, int *C) {
    int L = 0, R = n - 1;
    *C = 0;
    while (L <= R) {
        int m = (L + R) / 2;
        (*C)++;  // Считаем только одно сравнение за итерацию

        if (A[m] == X) {
            return m;
        } 
        (*C)++;
        if (A[m] < X) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }
    return -1;
}


int binaryV2(int n, int A[], int X, int *C) {
    int L = 0, R = n - 1;
    *C = 0;
    int m;
    while (L < R) {
        m = (L + R) / 2;
        (*C)++;
        if (A[m] < X) {
            L=m+1;
        } else {
            R = m;
        }
    }
    (*C)++;
    if (A[R]==X){
        return R;
    }
    else{
       return -1; 
    }
}


int main() {
    int X;
    printf("Введите число для поиска: ");
    scanf("%d", &X);
    
    printf("+------------+------------------+------------------+\n");
    printf("|     N      |    Сф I Версия   |    Сф II Версия  |\n");
    printf("+------------+------------------+------------------+\n");

    for (int i = 1; i <= 10; i++) {
        int C1, C2;
        int n = 100 * i;
        int A[n];
        FillInc(n, A);
        binaryV1(n, A, X, &C1);
        binaryV2(n, A, X, &C2);
        printf("| %10d | %16d | %16d |\n", n, C1, C2);
    }

    printf("+------------+------------------+------------------+\n\n\n\n\n");
    printf("Результаты 1 вверсии\n");
    for (int i = 1; i <= 10; i++) {
        int C;
        int n = 100 * i;
        int A[n];
        FillInc(n, A);
        int pos = binaryV1(n, A, X, &C);
        if (pos != -1) {
            printf("Элемент %d найден в массиве размером %d на позиции %d\n", X, n, pos);
        } else {
            printf("Элемент %d не найден в массиве размером %d\n", X, n);
        }
    }
    printf("+------------+------------------+\n\n\n\n\n");
    printf("Результаты 2 вверсии\n");
    for (int i = 1; i <= 10; i++) {
        int C;
        int n = 100 * i;
        int A[n];
        FillInc(n, A);
        int pos = binaryV2(n, A, X, &C);
        if (pos != -1) {
            printf("Элемент %d найден в массиве размером %d на позиции %d\n", X, n, pos);
        } else {
            printf("Элемент %d не найден в массиве размером %d\n", X, n);
        }
    }

    return 0;
}
