#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
}

void printForwardRecursive(tData *head)
{
    if (head == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", head->data);
    printForwardRecursive(head->next);
}

void printBackwardRecursive(tData *head)
{
    if (head == NULL) {
        return;
    }
    printBackwardRecursive(head->next);
    printf("%d ", head->data);
}

typedef struct {
    tData *head;
    tData *tail;
} tQueue;

// Инициализация очереди
void InitializeQueue(tQueue *q) {
    q->head = q->tail = NULL;
}

void MergeSeries(tData **a, int q, tData **b, int r, tQueue *c, int *cmp, int *move) {
    while (q > 0 && r > 0 && *a != NULL && *b != NULL) {
        (*cmp)++;
        if ((*a)->data <= (*b)->data) {
            if (c->head == NULL) {
                c->head = c->tail = *a;
            } else {
                c->tail->next = *a;
                c->tail = *a;
            }
            *a = (*a)->next;
            q--;
        } else {
            if (c->head == NULL) {
                c->head = c->tail = *b;
            } else {
                c->tail->next = *b;
                c->tail = *b;
            }
            *b = (*b)->next;
            r--;
        }
        (*move)++;
    }

    while (q > 0 && *a != NULL) {
        if (c->head == NULL) {
            c->head = c->tail = *a;
        } else {
            c->tail->next = *a;
            c->tail = *a;
        }
        *a = (*a)->next;
        q--;
        (*move)++;
    }

    while (r > 0 && *b != NULL) {
        if (c->head == NULL) {
            c->head = c->tail = *b;
        } else {
            c->tail->next = *b;
            c->tail = *b;
        }
        *b = (*b)->next;
        r--;
        (*move)++;
    }

    if (c->tail != NULL) {
        c->tail->next = NULL;
    }
}


void SplitLists(tData *head, tData **a, tData **b, int *n, int *move) {
    *a = head;
    *b = head->next;

    tData *k = *a, *p = *b;
    (*move)++;
    *n = 1; // Количество элементов

    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
        (*move)++;
    }
}

void MergeSort(tData **S, int *comparisons, int *moves) {
    // Пустой список или из одного элемента
    if (*S == NULL || (*S)->next == NULL) {
        return;
    }

    tQueue c[2];
    tData *a, *b;
    int n;
    SplitLists(*S, &a, &b, &n, moves);

    for (int p = 1; p < n; p *= 2) {
        InitializeQueue(&c[0]);
        InitializeQueue(&c[1]);
        int i = 0, m = n;

        while (m > 0) {
            // Определяем фактические размеры серий
            int q = (m >= p) ? p : m;
            m -= q;

            int r = (m >= p) ? p : m;
            m -= r;

            MergeSeries(&a, q, &b, r, &c[i], comparisons, moves);

            i = 1 - i;
        }

        a = c[0].head;
        b = c[1].head;
    }

    if (c[0].tail != NULL) {
        c[0].tail->next = NULL;
    }
    *S = c[0].head;
}

int main() {
    int n = 20;
    int m = 0;
    tData *stack = NULL, *a = NULL, *b = NULL;

    // Блок 1. Генерация случайного списка
    printf(ANSI_COLOR_GREEN "Создание случайного списка (размер %d):\n" ANSI_COLOR_RESET, n);
    fillRanStack(&stack, n);
    printf(ANSI_COLOR_CYAN "Исходный список:\n" ANSI_COLOR_RESET);
    print_list(stack);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n\n" ANSI_COLOR_RESET, checksum(stack), count_series(stack));

    // Блок 2. Разделение списка
    int moves = 0;
    printf(ANSI_COLOR_GREEN "Разделение списка на два подсписка:\n" ANSI_COLOR_RESET);
    SplitLists(stack, &a, &b, &m, &moves);

    printf(ANSI_COLOR_CYAN "Список A:\n" ANSI_COLOR_RESET);
    print_list(a);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n" ANSI_COLOR_RESET, checksum(a), count_series(a));

    printf(ANSI_COLOR_CYAN "Список B:\n" ANSI_COLOR_RESET);
    print_list(b);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n\n" ANSI_COLOR_RESET, checksum(b), count_series(b));

    // Блок 3. Слияние списков
    printf(ANSI_COLOR_GREEN "Процесс слияния списков:\n" ANSI_COLOR_RESET);
    int i = 0;
    tQueue c[2];
    InitializeQueue(&c[0]);
    InitializeQueue(&c[1]);
    int Cfact = 0, Mfact = 0;
    int Ctheor = 0, Mtheor = 0;

    printf(ANSI_COLOR_CYAN "Перед слиянием:\n" ANSI_COLOR_RESET);
    printf("m = %d\n", m);
    printf("Список A:\n");
    print_list(a);
    printf("Список B:\n");
    print_list(b);

    while (m > 0) {
        int q = (m >= 1) ? 1 : m;
        m -= q;
        int r = (m >= 1) ? 1 : m;
        m -= r;

        Ctheor += ((q < r ? q : r) + q + r - 1) / 2;
        Mtheor += q + r;

        MergeSeries(&a, q, &b, r, &c[i], &Cfact, &Mfact);
        i = 1 - i;
    }

    printf(ANSI_COLOR_CYAN "\nОчередь C[0]:\n" ANSI_COLOR_RESET);
    print_list(c[0].head);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n" ANSI_COLOR_RESET, checksum(c[0].head), count_series(c[0].head));

    printf(ANSI_COLOR_CYAN "Очередь C[1]:\n" ANSI_COLOR_RESET);
    print_list(c[1].head);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n" ANSI_COLOR_RESET, checksum(c[1].head), count_series(c[1].head));

    printf(ANSI_COLOR_MAGENTA
        "\nСложность слияния списков:\n"
        "Теоретическая: C = %d, M = %d\n"
        "Фактическая:   C = %d, M = %d\n\n"
        ANSI_COLOR_RESET, Ctheor, Mtheor, Cfact, Mfact);

    // Блок 4. Сортировка списка слиянием
    clear(stack);
    stack = NULL;

    printf(ANSI_COLOR_GREEN "Сортировка слиянием:\n" ANSI_COLOR_RESET);
    fillRanStack(&stack, n);

    printf(ANSI_COLOR_CYAN "Исходный случайный список:\n" ANSI_COLOR_RESET);
    print_list(stack);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n" ANSI_COLOR_RESET, checksum(stack), count_series(stack));
    printf("\n");

    Cfact = 0;
    Mfact = 0;
    MergeSort(&stack, &Cfact, &Mfact);

    printf(ANSI_COLOR_CYAN "Отсортированный список:\n" ANSI_COLOR_RESET);
    print_list(stack);
    printf(ANSI_COLOR_YELLOW "Контрольная сумма: %d, количество серий: %d\n" ANSI_COLOR_RESET, checksum(stack), count_series(stack));

    Ctheor = (int)(log2(n) * n);
    Mtheor = (int)(log2(n) * n);

    printf(ANSI_COLOR_MAGENTA
        "\nСложность сортировки:\n"
        "Теоретическая: C = %d, M = %d\n"
        "Фактическая:   C = %d, M = %d\n\n"
        ANSI_COLOR_RESET, Ctheor, Mtheor, Cfact, Mfact);

    // Блок 5. Таблица замеров
    printf(ANSI_COLOR_GREEN "Таблица замеров сложности сортировки:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "+================================================================+\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "|   N   |     M + C     |  Убывающий | Случайный |  Возрастающий |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "|       |  Теоретический|            |           |               |\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "+================================================================+\n" ANSI_COLOR_RESET);

    for (int j = 100; j <= 500; j += 100) {
        int Ttheor = (int)(2 * log2(j) * j);

        clear(stack);
        stack = NULL;
        Cfact = 0;
        Mfact = 0;
        fillRanStack(&stack, j);
        MergeSort(&stack, &Cfact, &Mfact);
        int Trand = Cfact + Mfact;

        clear(stack);
        stack = NULL;
        Cfact = 0;
        Mfact = 0;
        fillIncStack(&stack, j);
        MergeSort(&stack, &Cfact, &Mfact);
        int Tinc = Cfact + Mfact;

        clear(stack);
        stack = NULL;
        Cfact = 0;
        Mfact = 0;
        fillDecStack(&stack, j);
        MergeSort(&stack, &Cfact, &Mfact);
        int Tdec = Cfact + Mfact;

        printf("| %5d | %13d | %10d | %9d | %13d |\n", j, Ttheor, Tdec, Trand, Tinc);
        printf(ANSI_COLOR_CYAN "+================================================================+\n" ANSI_COLOR_RESET);
    }
}
