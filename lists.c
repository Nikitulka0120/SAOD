#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

typedef struct tData
{
    struct tData *next;
    int data;
} tData;

// 1. Разработать функции для создания стека:
void AddToStack(tData** head, int data)
{
    tData* p = (tData*)malloc(sizeof(tData));
    p->data = data;
    p->next = *head;
    *head = p;
}

// - заполнение стека возрастающими числами;
void fillIncStack(tData **head, int n)
{
    for (int i = 1; i <= n; i++)
    {
        AddToStack(head, i);
    }
}

// - заполнение стека убывающими числами;
void fillDecStack(tData** head, int n)
{
    for (int i = n; i >= 1; i--)
    {
        AddToStack(head, i);
    }
}

// - заполнение стека случайными числами;
void fillRanStack(tData** head, int n)
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
    {
        int ranNum = rand() % 100;
        AddToStack(head, ranNum);
    }
}

// 2. Разработать функции для создания очереди:
void AddToQueue(tData** head, tData** tail, int data)
{
    tData *p = (tData *)malloc(sizeof(tData));
    p->data = data;
    p->next = NULL;

    if (*tail == NULL)
    {
        *head = *tail = p;
    }
    else
    {
        (*tail)->next = p;
        *tail = p;
    }
}

// - заполнение очереди возрастающими числами;
void fillIncQueue(tData** head, tData** tail, int n)
{
    for (int i = 1; i <= n; i++)
    {
        AddToQueue(head, tail, i);
    }
}

// - заполнение очереди убывающими числами;
void fillDecQueue(tData** head, tData** tail, int n)
{
    for (int i = n; i >= 1; i--)
    {
        AddToQueue(head, tail, i);
    }
}

// - заполнение очереди случайными числами;
void fillRanQueue(tData** head, tData** tail, int n)
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
    {
        int ranNum = rand() % 100;
        AddToQueue(head, tail, ranNum);
    }
}

void delStackElement(tData** head)
{
    if (head != NULL)
    {
        tData *p = *head;
        *head = p->next;
        free(p);
    }
}

// 3. Разработать функции для работы со списком:
//  печать элементов списка;
void print_list(tData *head)
{
    tData *p = head;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// - подсчет контрольной суммы элементов списка;
int checksum(tData *head)
{
    int sum = 0;
    tData *p = head;
    while (p != NULL)
    {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

// - подсчет количества серий в списке
int count_series(tData *head)
{
    if (head == NULL)
    {
        return 0;
    }

    int count = 1;
    tData *p = head;

    while (p->next != NULL)
    {
        if (p->data > p->next->data)
        {
            count++;
        }
        p = p->next;
    }
    return count;
}

void clear(tData *head)
{
    tData *p = head;
    while (p != NULL)
    {
        tData *temp_p = p;
        p=p->next;
        free(temp_p);
    }
    printf("\n");
}

void print_forward_recursive(tData* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    print_forward_recursive(node->next);
}

int main() {
    //проверка стека возр
    tData* stack_head = NULL;
    fillIncStack(&stack_head, N);
    printf("Stack (Inc): ");
    print_list(stack_head);
    printf("Checksum: %d\n", checksum(stack_head));
    printf("Series count: %d\n", count_series(stack_head));
    clear(stack_head);

    //проверка стека убыв
    stack_head = NULL;
    fillDecStack(&stack_head, N);
    printf("Stack (dec): ");
    print_list(stack_head);
    printf("Checksum: %d\n", checksum(stack_head));
    printf("Series count: %d\n", count_series(stack_head));
    clear(stack_head);

    //проверка стека ранд
    stack_head = NULL;
    fillRanStack(&stack_head, N);
    printf("Stack (Ran): ");
    print_list(stack_head);
    printf("Checksum: %d\n", checksum(stack_head));
    printf("Series count: %d\n", count_series(stack_head));
    clear(stack_head);

    //проверка очереди возр
    tData* queue_head = NULL, *queue_tail = NULL;
    fillIncQueue(&queue_head, &queue_tail, N);
    printf("Inc (queue): ");
    print_list(queue_head);
    printf("Checksum: %d\n", checksum(queue_head));
    printf("Series count: %d\n", count_series(queue_head));
    clear(queue_head);

    //проверка очереди убыв
    queue_head = NULL; 
    queue_tail = NULL;
    fillDecQueue(&queue_head, &queue_tail, N);
    printf("Dec (queue): ");
    print_list(queue_head);
    printf("Checksum: %d\n", checksum(queue_head));
    printf("Series count: %d\n", count_series(queue_head));
    clear(queue_head);

    //проверка очереди ранд
    queue_head = NULL; 
    queue_tail = NULL;
    fillRanQueue(&queue_head, &queue_tail, N);
    printf("Ran (queue): ");
    print_list(queue_head);
    printf("Checksum: %d\n", checksum(queue_head));
    printf("Series count: %d\n", count_series(queue_head));
    clear(queue_head);

    
    return 0;
}
