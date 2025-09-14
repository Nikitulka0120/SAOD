
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define N 100

typedef struct Vertex
{
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

void Left_to_right(Vertex *p)
{
    if (p != NULL)
    {
        Left_to_right(p->Left);
        printf("%d ", p->Data);
        Left_to_right(p->Right);
    }
}

int Search(Vertex *p, int X)
{
    while (p != NULL)
    {
        {
            if (X < p->Data)
            {
                p = p->Left;
            }
            else if (X > p->Data)
            {
                p = p->Right;
            }
            else
                break;
        }
    }
    if (p != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Size(Vertex *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + Size(p->Left) + Size(p->Right);
    }
}

int CheckSum(Vertex *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return p->Data + CheckSum(p->Left) + CheckSum(p->Right);
    }
}

int Height(Vertex *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight = Height(p->Left);
        int rightHeight = Height(p->Right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

int PathLengthSum(Vertex *p, int level)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return level +
               PathLengthSum(p->Left, level + 1) +
               PathLengthSum(p->Right, level + 1);
    }
}

float AverageHeight(Vertex *root)
{
    if (root == NULL)
    {
        return 0.0f;
    }
    int total_path_length = PathLengthSum(root, 1);
    int tree_size = Size(root);
    return (float)total_path_length / tree_size;
}

void FillInc(int n, int A[])
{
    for (int i = 0; i < n; i++)
    {
        A[i] = i + 1;
    }
}

Vertex *BuildISDP(int L, int R, int A[])
{
    if (L > R)
    {
        return NULL;
    }
    else
    {
        int m = (L + R) / 2;
        Vertex *p = (Vertex *)malloc(sizeof(Vertex));
        p->Data = A[m];
        p->Left = BuildISDP(L, m - 1, A);
        p->Right = BuildISDP(m + 1, R, A);
        return p;
    }
}

int main()
{
    system("chcp 65001 > nul");
    int A[N];
    FillInc(N, A);
    Vertex *root= BuildISDP(0, 99, A);
    printf("Обход дерева:\n");
    Left_to_right(root);
    printf("\nРазмер дерева: %d\n",Size(root));
    printf("Контрольная сумма: %d\n",CheckSum(root));
    printf("Высота дерева %d\n",Height(root));
    printf("Средняя высота дерева: %.2f\n", AverageHeight(root));
}
