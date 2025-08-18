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

int selectionSort(int n, int A[]) {
    int C=0;
    int M=0;
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            C++;
            if (A[j] < A[k]) { 
                k = j;
            }
        }
            M++;
            int temp = A[i];
            A[i] = A[k];
            A[k] = temp;
    }
    int trud = C+M;
    return trud;
}

int bubbleSort(int n, int A[])
{
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

int max_complexity(int n) {
    return (n * n) + n - 2;
}

int insertSort(int n, int A[]) {
    int C = 0;
    int M = 0;

    for(int i = 1; i < n; i++) {
        int t = A[i]; 
        int j = i - 1;
        M++;

        while (j >= 0 && t < A[j]) {
            C++;
            A[j + 1] = A[j];
            M++;
            j--;
        }
        if (j >= 0) {
            C++;
        }
        
        A[j + 1] = t;
        M++;
    }
    int trud = M+C;
    return trud;
}

int getMaxInterval(int n) {
    int h = 1;
    while (h < n) {
        h = 2 * h + 1;  
    }
    return h/2; 
}

int PrintMaxInterval(int n) {
    int h = 1;
    printf("%d ",h);
    while (h < n) {
        h = 2 * h + 1;
        if (h<n){
            printf("%d ",h);
        }
        
    }
    return h/2; 
}

int ShellSort(int n,int a[] ) {
    int T = 0, C = 0, M = 0;
    int k = getMaxInterval(n); 
    while (k >= 1) {
        for (int i = k; i < n; i++) { 
            M++;
            int t = a[i]; 
            int j = i - k; 

            while (j >= 0 && t < a[j]) { 
                C++;
                a[j + k] = a[j]; M++;
                j = j - k;
            }
        if (j >= 0) {
            C++;
        }

            a[j + k] = t; 
            M++;
        }

        k = (k - 1) / 2; 
    }
    T= M + C;
    return T;
}


int main()
{

    printf("+---------+-----------------------------+-----------------------------------------------+\n");
    printf("|    N     |         h1...hm по формуле Д.Кнута     |   insert M+C   |   Shell M+C      |\n");
    printf("+---------+-----------------------------+---------------+---------------+---------------+\n");

    for (int i = 1; i < 6; i++)
    {
        int n = 100 * i;
        int A[n];
        int max_trud=max_complexity(n);
        FillDec(n, A);
        int itrud = insertSort(n, A);
        FillDec(n, A);
        int strud = ShellSort(n, A);
        printf("| %6d  |", n);
        PrintMaxInterval(n);
        printf("| %6d  | %6d  |\n", itrud, strud);

    }

    printf("+---------+-----------+-----------+--------------+-----------+--------------+-----------+\n\n\n\n");

}
