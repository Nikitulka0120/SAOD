#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int n, int A[])
{
    for (int i = 0; i < n; i++)
    {
        A[i] = i + 1;
    }
}

void FillDec(int n, int A[])
{
    for (int i = 0; i < n; i++)
    {
        A[i] = n - i;
    }
}

void FillRand(int n, int A[])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        A[i] = rand() % 100;
    }
}

int CheckSum(int n, int A[])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += A[i];
    }
    return sum;
}

int RunNumber(int n, int A[])
{
    if (n == 0)
        return 0;
    int series = 1;
    for (int i = 1; i < n; i++)
    {
        if (A[i] < A[i - 1])
        {
            series++;
        }
    }
    return series;
}

void PrintMas(int n, int A[])
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
int bubbleSort(int n, int A[])
{
    // printf("Контрольная сумма до сортировки:%d\n",CheckSum(n, A));
    // printf("Число серий до сортировки:%d\n",RunNumber(n, A));
    int C = 0;
    int M = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            C++;
            if (A[j] < A[j - 1])
            {
                M++;
                int temp = A[j];
                M++;
                A[j] = A[j - 1];
                M++;
                A[j - 1] = temp;
            }
        }
    }
    // printf("Контрольная сумма после сортировки:%d\n",CheckSum(n, A));
    // printf("Число серий после сортировки:%d\n",RunNumber(n, A));
    int trud = M + C;
    return trud;
}

int ShakerSortPrint(int n, int A[])
{
    printf("Контрольная сумма до сортировки:%d\n", CheckSum(n, A));
    printf("Число серий до сортировки:%d\n", RunNumber(n, A));
    int C = 0;
    int M = 0;
    int L = 0;
    int R = n - 1;
    int k = n - 1;
    do
    {
        for (int j = R; j > L; j--)
        {
            if (A[j] < A[j - 1])
            {
                M++;
                int temp = A[j];
                M++;
                A[j] = A[j - 1];
                M++;
                A[j - 1] = temp;
                k = j;
            }
        }
        L = k;
        for (int j = L; j < R; j++)
        {
            if (A[j] > A[j + 1])
            {
                M++;
                int temp = A[j];
                M++;
                A[j] = A[j + 1];
                M++;
                A[j + 1] = temp;
                k = j;
            }
        }
        R = k;
    } while (L < R);
    printf("Контрольная сумма после сортировки:%d\n", CheckSum(n, A));
    printf("Число серий после сортировки:%d\n", RunNumber(n, A));
    int trud = M + C;
    return trud;
}

int ShakerSort(int n, int A[])
{
    int C = 0;
    int M = 0;
    int L = 0;
    int R = n - 1;
    int k = n - 1;
    do
    {
        for (int j = R; j > L; j--)
        {
            C++;
            if (A[j] < A[j - 1])
            {
                M++;
                int temp = A[j];
                M++;
                A[j] = A[j - 1];
                M++;
                A[j - 1] = temp;
                k = j;
            }
        }
        L = k;
        for (int j = L; j < R; j++)
        {   
            C++;
            if (A[j] > A[j + 1])
            {
                M++;
                int temp = A[j];
                M++;
                A[j] = A[j + 1];
                M++;
                A[j + 1] = temp;
                k = j;
            }
        }
        R = k;
    } while (L < R);
    int trud = M + C;
    return trud;
}

int main()
{

    for (int i = 1; i < 6; i++)
    {
        int n = 100 * i;
        int A[n];
        printf("----------------------------------- Убывающий для %d эдементов -------------------------------------\n", n);
        FillDec(n, A);
        ShakerSortPrint(n, A);
        printf("----------------------------------- Случайный для %d эдементов -------------------------------------\n", n);
        FillRand(n, A);
        ShakerSortPrint(n, A);
        printf("----------------------------------- Возрастающий для %d эдементов -------------------------------------\n", n);
        FillInc(n, A);
        ShakerSortPrint(n, A);
    }
    printf("+---------+--------------------------------------+--------------------------------------+\n");
    printf("+         |       Пузырьковая сортировка         |         Шейкерная сортировка         |\n");
    printf("+    N    +-----------+-----------+--------------+-----------+--------------+-----------+\n");
    printf("|         | убывающий | случайный | возрастающий | убывающий | случайный | возрастающий |\n");
    printf("+---------+-----------+-----------+--------------+-----------+--------------+-----------+\n");

    for (int i = 1; i < 6; i++)
    {
        int strud;
        int n = 100 * i;
        int A[n];
        FillDec(n, A);
        strud = ShakerSort(n, A);
        FillRand(n, A);
        int strud_rand = ShakerSort(n, A);
        FillInc(n, A);
        int strud_inc = ShakerSort(n, A);
        FillDec(n, A);
        int btrud = bubbleSort(n, A);
        FillRand(n, A);
        int btrud_rand = bubbleSort(n, A);
        FillInc(n, A);
        int btrud_inc = bubbleSort(n, A);
        printf("| %6d  | %9d | %9d | %12d | %9d | %9d | %12d |\n", n, btrud, btrud_rand, btrud_inc, strud, strud_rand, strud_inc);
    }

    printf("+---------+-----------+-----------+--------------+-----------+--------------+-----------+\n");
}
