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

int main()
{
    printf("+---------------+----------------------------+--------------------------+--------------------------+-----------------------------+\n");
    printf("|    N (size)   | Теоретическая Трудоемкость | Трудоемкость (убывающий) | Трудоемкость (случайный) | Трудоемкость (возрастающий) |\n");
    printf("+---------------+----------------------------+--------------------------+--------------------------+-----------------------------+\n");

    for (int i = 1; i < 6; i++)
    {
        int trud;
        int n = 100 * i;
        int A[n];
        int theor = 3 * (n * (n - 1) / 2) + (n * (n - 1) / 2);
        FillDec(n, A);
        trud = bubbleSort(n, A);
        FillRand(n, A);
        int trud_rand = bubbleSort(n, A);
        FillInc(n, A);
        int trud_inc = bubbleSort(n, A);
        printf("| %12d  | %26d | %24d | %24d | %27d |\n", n, theor, trud, trud_rand, trud_inc);
    }

    printf("+---------------+----------------------------+--------------------------+--------------------------+-----------------------------+\n");
}
