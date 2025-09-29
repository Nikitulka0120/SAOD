#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 50
#define M 10

typedef struct Vertex
{
    int Data;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

void Top_to_bot(Vertex *p)
{
    if (p != NULL)
    {
        printf("%d ", p->Data);
        Top_to_bot(p->Left);
        Top_to_bot(p->Right);
    }
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
    printf("Генерация случайной последовательности: ");
    int count = 0;
    while (count < n)
    {
        int num = rand() % 100;
        int isUnique = 1;
        for (int i = 0; i < count; i++)
        {
            if (arr[i] == num)
            {
                isUnique = 0;
                break;
            }
        }
        if (isUnique)
        {
            arr[count] = num;
            count++;
            printf("%d ", num);
        }
    }
    printf("\n");
}

void add_DoubleSDP(Vertex **p, int Data)
{
    while (*p != NULL)
    {
        if (Data < (*p)->Data)
        {
            p = &((*p)->Left);
        }
        else if (Data > (*p)->Data)
        {
            p = &((*p)->Right);
        }
        else
        {
            return;
        }
    }
    if (*p == NULL)
    {
        *p = (Vertex *)malloc(sizeof(Vertex));
        (*p)->Data = Data;
        (*p)->Left = NULL;
        (*p)->Right = NULL;
    }
}

int delete_SDP(Vertex **p, int Data)
{
    while (*p != NULL)
    {
        if (Data < (*p)->Data)
        {
            p = &((*p)->Left);
        }
        else if (Data > (*p)->Data)
        {
            p = &((*p)->Right);
        }
        else
        {
            break;
        }
    }

    if (*p == NULL)
    {
        return 0;
    }

    Vertex *q = *p;

    if (q->Left == NULL)
    {
        *p = q->Right;
    }
    else if (q->Right == NULL)
    {
        *p = q->Left;
    }
    else
    {
        Vertex *r = q->Left;
        Vertex *s = q;
        if (r->Right == NULL)
        {
            r->Right = q->Right;
            *p = r;
        }
        else
        {
            while (r->Right != NULL)
            {
                s = r;
                r = r->Right;
            }
            s->Right = r->Left;
            r->Left = q->Left;
            r->Right = q->Right;
            *p = r;
        }
    }
    free(q);
    return 1;
}

int main()
{
    system("chcp 65001 > nul");
    int initial[N];
    generator(initial, N);
    printf("\n");

    Vertex *SDPRoot = NULL;
    for (int i = 0; i < N; i++)
    {
        add_DoubleSDP(&SDPRoot, initial[i]);
    }

    printf("Исходное дерево поиска (обход сверху вниз):\n");
    Top_to_bot(SDPRoot);
    printf("\n");

    printf("Исходное дерево поиска (обход слева направо):\n");
    Left_to_Right(SDPRoot);
    printf("\n");

    int toDelete = -1;
    int DeleteCounter = M;
    do
    {
        if (SDPRoot != NULL)
        {
            printf("\nВведите вершину для удаления из дерева:\n");
            scanf("%d", &toDelete);

            if (delete_SDP(&SDPRoot, toDelete))
            {
                printf("\nЭлемент %d успешно удален.\n", toDelete);
                DeleteCounter -= 1;

                printf("\nОбход дерева после удаления: ");
                Left_to_Right(SDPRoot);
                printf("\n");
            }
            else
            {
                printf("Элемент %d не найден в дереве.\n", toDelete);
            }
        }
        else
        {
            printf("Размер дерева не позволяет продолжить дальнейшее удаление!");
            break;
        }

    } while (DeleteCounter > 0);

    return 0;
}
