#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 100

typedef struct Vertex {
    int Data;
    int balance;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

void Left_to_Right(Vertex *p) {
    if (p != NULL) {
        Left_to_Right(p->Left);
        printf("%d ", p->Data);
        Left_to_Right(p->Right);
    }
}

int Size(Vertex *p) {
    if (p == NULL) return 0;
    return 1 + Size(p->Left) + Size(p->Right);
}

int CheckSum(Vertex *p) {
    if (p == NULL) return 0;
    return p->Data + CheckSum(p->Left) + CheckSum(p->Right);
}

int Height(Vertex *p) {
    if (p == NULL) return 0;
    int lh = Height(p->Left);
    int rh = Height(p->Right);
    return 1 + (lh > rh ? lh : rh);
}

int PathLengthSum(Vertex *p, int level) {
    if (p == NULL) return 0;
    return level + PathLengthSum(p->Left, level + 1) + PathLengthSum(p->Right, level + 1);
}

float AverageHeight(Vertex *root) {
    if (root == NULL) return 0.0f;
    return (float)PathLengthSum(root, 1) / Size(root);
}

Vertex *BuildISDP(int L, int R, int A[]) {
    if (L > R) return NULL;
    int m = (L + R) / 2;
    Vertex *p = (Vertex *)malloc(sizeof(Vertex));
    p->Data = A[m];
    p->balance = 0;
    p->Left = BuildISDP(L, m - 1, A);
    p->Right = BuildISDP(m + 1, R, A);
    return p;
}

void insertSort(int n, int A[]) {
    for (int i = 1; i < n; i++) {
        int t = A[i];
        int j = i - 1;
        while (j >= 0 && t < A[j]) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = t;
    }
}

void generator(int arr[], int n) {
    srand(time(NULL));
    printf("\033[34mГенерация случайной последовательности:\033[0m\n");
    int count = 0;
    while (count < n) {
        int num = rand() % 1000;
        int unique = 1;
        for (int i = 0; i < count; i++) {
            if (arr[i] == num) {
                unique = 0;
                break;
            }
        }
        if (unique) {
            arr[count] = num;
            printf("%d ", num);
            count++;
        }
    }
    printf("\n");
}

void ll_rotation(Vertex **p) {
    Vertex *q = (*p)->Left;
    (*p)->Left = q->Right;
    q->Right = *p;
    (*p)->balance = 0;
    q->balance = 0;
    *p = q;
}

void lr_rotation(Vertex **p) {
    Vertex *q = (*p)->Left;
    Vertex *r = q->Right;

    if (r->balance < 0) (*p)->balance = 1;
    else (*p)->balance = 0;

    if (r->balance > 0) q->balance = -1;
    else q->balance = 0;

    r->balance = 0;

    q->Right = r->Left;
    (*p)->Left = r->Right;
    r->Left = q;
    r->Right = *p;
    *p = r;
}

void rl_rotation(Vertex **p) {
    Vertex *q = (*p)->Right;
    Vertex *r = q->Left;

    if (r->balance > 0) (*p)->balance = -1;
    else (*p)->balance = 0;

    if (r->balance < 0) q->balance = 1;
    else q->balance = 0;

    r->balance = 0;

    q->Left = r->Right;
    (*p)->Right = r->Left;
    r->Left = *p;
    r->Right = q;
    *p = r;
}

void rr_rotation(Vertex **p) {
    Vertex *q = (*p)->Right;
    (*p)->Right = q->Left;
    q->Left = *p;
    (*p)->balance = 0;
    q->balance = 0;
    *p = q;
}

int insert_AVL(int D, Vertex **p) {
    int growth = 0;
    if (*p == NULL) {
        *p = (Vertex *)malloc(sizeof(Vertex));
        (*p)->Data = D;
        (*p)->balance = 0;
        (*p)->Left = (*p)->Right = NULL;
        return 1;
    }

    if (D < (*p)->Data) {
        growth = insert_AVL(D, &(*p)->Left);
        if (growth) {
            if ((*p)->balance > 0) {
                (*p)->balance = 0;
                return 0;
            } else if ((*p)->balance == 0) {
                (*p)->balance = -1;
                return 1;
            } else {
                if ((*p)->Left->balance < 0)
                    ll_rotation(p);
                else
                    lr_rotation(p);
                return 0;
            }
        }
    } else if (D > (*p)->Data) {
        growth = insert_AVL(D, &(*p)->Right);
        if (growth) {
            if ((*p)->balance < 0) {
                (*p)->balance = 0;
                return 0;
            } else if ((*p)->balance == 0) {
                (*p)->balance = 1;
                return 1;
            } else {
                if ((*p)->Right->balance > 0)
                    rr_rotation(p);
                else
                    rl_rotation(p);
                return 0;
            }
        }
    }
    return 0;
}
void PrintStatString(const char *name, Vertex *root) {
    printf("| %-20s | %-10d | %-15d | %-10d | %-15.2f |\n",
           name, Size(root), CheckSum(root), Height(root), AverageHeight(root));
}

int main() {
    system("chcp 65001 > nul");

    int initial[N];
    int sorted[N];

    generator(initial, N);
    for (int i = 0; i < N; i++)
        sorted[i] = initial[i];

    insertSort(N, sorted);
    Vertex *ISDP = BuildISDP(0, N - 1, sorted);
    Vertex *AVL = NULL;
    for (int i = 0; i < N; i++)
        insert_AVL(initial[i], &AVL);

    printf("\n\033[34mОбход ИСДП:\033[0m\n");
    Left_to_Right(ISDP);
    printf("\n");

    printf("\033[34mОбход AVL:\033[0m\n");
    Left_to_Right(AVL);
    printf("\n\n");

    printf("\033[34mСтатистика деревьев:\033[0m\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-15s | %-10s | %-15s |\n",
           "Type", "Size", "CheckSum", "Height", "Avg Height");
    printf("--------------------------------------------------------------------------------------\n");

    PrintStatString("ISDP", ISDP);
    PrintStatString("AVL", AVL);
    printf("--------------------------------------------------------------------------------------\n");

    return 0;
}
