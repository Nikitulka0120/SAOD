#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N 100
int heightDecreased = 0; 
typedef struct Vertex
{
    int Data;
    int balance;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

void ll_rotation(Vertex **p) {
    Vertex *q = (*p)->Left;
    (*p)->Left = q->Right;
    q->Right = *p;
    (*p)->balance = 0;
    q->balance = 0;
    *p = q;
}

void rr_rotation(Vertex **p) {
    Vertex *q = (*p)->Right;
    (*p)->Right = q->Left;
    q->Left = *p;
    (*p)->balance = 0;
    q->balance = 0;
    *p = q;
}

void Left_to_Right(Vertex *p)
{
    if (p != NULL)
    {
        Left_to_Right(p->Left);
        printf("%d ", p->Data);
        Left_to_Right(p->Right);
    }
}

void generator(int arr[], int n)
{
    srand(time(NULL));
    printf("\033[34mГенерация случайной последовательности:\033[0m\n");
    int count = 0;
    while (count < n)
    {
        int num = rand() % 1000;
        int unique = 1;
        for (int i = 0; i < count; i++)
        {
            if (arr[i] == num)
            {
                unique = 0;
                break;
            }
        }
        if (unique)
        {
            arr[count] = num;
            printf("%d ", num);
            count++;
        }
    }
    printf("\n");
}

void ll1_rotation(Vertex **p)
{
    Vertex *q = (*p)->Left;
    if (q->balance == 0)
    {
        q->balance = 1;
        (*p)->balance = -1;
        heightDecreased = 0;
    }
    else
    {
        q->balance = 0;
        (*p)->balance = 0;
        heightDecreased = 1;
    }
    (*p)->Left = q->Right;
    q->Right = *p;
    *p = q;
}

void lr_rotation(Vertex **p)
{
    Vertex *q = (*p)->Left;
    Vertex *r = q->Right;

    if (r->balance < 0)
        (*p)->balance = 1;
    else
        (*p)->balance = 0;

    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;

    r->balance = 0;

    q->Right = r->Left;
    (*p)->Left = r->Right;
    r->Left = q;
    r->Right = *p;
    *p = r;
}

void rl_rotation(Vertex **p)
{
    Vertex *q = (*p)->Right;
    Vertex *r = q->Left;

    if (r->balance > 0)
        (*p)->balance = -1;
    else
        (*p)->balance = 0;

    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;

    r->balance = 0;

    q->Left = r->Right;
    (*p)->Right = r->Left;
    r->Left = *p;
    r->Right = q;
    *p = r;
}

void rr1_rotation(Vertex **p)
{
    Vertex *q = (*p)->Right;
    if (q->balance == 0)
    {
        q->balance = -1;
        (*p)->balance = 1;
        heightDecreased = 0;
    }
    else
    {
        q->balance = 0;
        (*p)->balance = 0;
        heightDecreased = 1;
    }
    (*p)->Right = q->Left;
    q->Left = *p;
    *p = q;

}

int insert_AVL(int D, Vertex **p)
{
    int growth = 0;
    if (*p == NULL)
    {
        *p = (Vertex *)malloc(sizeof(Vertex));
        (*p)->Data = D;
        (*p)->balance = 0;
        (*p)->Left = (*p)->Right = NULL;
        return 1;
    }

    if (D < (*p)->Data)
    {
        growth = insert_AVL(D, &(*p)->Left);
        if (growth)
        {
            if ((*p)->balance > 0)
            {
                (*p)->balance = 0;
                return 0;
            }
            else if ((*p)->balance == 0)
            {
                (*p)->balance = -1;
                return 1;
            }
            else
            {
                if ((*p)->Left->balance < 0)
                    ll_rotation(p);
                else
                    lr_rotation(p);
                return 0;
            }
        }
    }
    else if (D > (*p)->Data)
    {
        growth = insert_AVL(D, &(*p)->Right);
        if (growth)
        {
            if ((*p)->balance < 0)
            {
                (*p)->balance = 0;
                return 0;
            }
            else if ((*p)->balance == 0)
            {
                (*p)->balance = 1;
                return 1;
            }
            else
            {
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

void BL(Vertex **p)
{
    if ((*p)->balance == -1)
    {
        (*p)->balance = 0;
        heightDecreased = 1;
    }
    else if ((*p)->balance == 0)
    {
        (*p)->balance = 1;
        heightDecreased = 0;
    }
    else if ((*p)->balance == 1)
    {
        if ((*p)->Right->balance >= 0)
        {
            rr1_rotation(p);
        }
        else
        {
            rl_rotation(p);
            heightDecreased = 1;
        }
    }
}

void BR(Vertex **p)
{
    if ((*p)->balance == 1)
    {
        (*p)->balance = 0;
        heightDecreased = 1;
    }
    else if ((*p)->balance == 0)
    {
        (*p)->balance = -1;
        heightDecreased = 0;
    }
    else if ((*p)->balance == -1)
    {
        if ((*p)->Left->balance <= 0)
        {
            ll1_rotation(p);
        }
        else
        {
            lr_rotation(p);
            heightDecreased = 1;
        }
    }
}


void del(Vertex **r, Vertex **q)
{
    if ((*r)->Right != NULL)
    {
        del(&(*r)->Right, q);
        if (heightDecreased)
            BR(r);
    }
    else
    {
        (*q)->Data = (*r)->Data;
        *q = *r;
        *r = (*r)->Left;
        heightDecreased = 1;
    }
}

void deleteAVL(int x, Vertex **p)
{
    if (*p == NULL)
        return;

    if (x < (*p)->Data)
    {
        deleteAVL(x, &(*p)->Left);
        if (heightDecreased)
            BL(p);
    }
    else if (x > (*p)->Data)
    {
        deleteAVL(x, &(*p)->Right);
        if (heightDecreased)
            BR(p);
    }
    else
    {
        Vertex *q = *p;
        if (q->Left == NULL)
        {
            *p = q->Right;
            heightDecreased = 1;
        }
        else if (q->Right == NULL)
        {
            *p = q->Left;
            heightDecreased = 1;
        }
        else
        {
            del(&(*p)->Left, &q);
            if (heightDecreased)
                BL(p);
        }

        free(q);
    }
}

int main()
{
    system("chcp 65001 > nul");
    int initial[N];
    generator(initial, N);
    Vertex *AVL = NULL;
    for (int i = 0; i < N; i++)
        insert_AVL(initial[i], &AVL);

    printf("\033[32m=== АВЛ-дерево ===\033[0m\n");
    
    int value;
    
    while (1) {
        printf("\033[34mТекущее дерево (симметричный обход):\033[0m\n");
        Left_to_Right(AVL);
        printf("\n");

        printf("\033[33mВведите значение вершины для удаления (или -1 для выхода): \033[0m");
        if (scanf("%d", &value) != 1) {
            printf("\033[31mОшибка ввода!\033[0m\n");
            while (getchar() != '\n');
            continue;
        }

        if (value == -1) {
            break;
        }

        int exists = 0;
        Vertex *current = AVL;
        while (current != NULL) {
            if (value == current->Data) {
                exists = 1;
                break;
            } else if (value < current->Data) {
                current = current->Left;
            } else {
                current = current->Right;
            }
        }
        
        if (!exists) {
            printf("\033[31mВершина %d не найдена в дереве!\033[0m\n\n", value);
            continue;
        }

        heightDecreased = 0;
        printf("\033[36mУдаляем вершину %d...\033[0m\n", value);
        deleteAVL(value, &AVL);

        printf("\033[32mДерево после удаления:\033[0m\n");
        Left_to_Right(AVL);
        printf("\n\n");

        if (AVL == NULL) {
            printf("\033[31mДерево стало пустым!\033[0m\n");
            break;
        }
    }

    printf("\033[32m=== Конечное состояние дерева ===\033[0m\n");
    Left_to_Right(AVL);
    printf("\nПрограмма завершена.\n");
    
    return 0;
}
