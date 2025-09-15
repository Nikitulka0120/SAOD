#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 4000
#define RECORDS_ON_PAGE 20

typedef struct record
{
    char FIO[32];
    char street[18];
    short int House_number;
    short int Apartment_number;
    char Date[10];
} record;

typedef struct tData
{
    struct tData *next;
    record *data;
} tData;

void AddToQueue(tData **head, tData **tail, record *data)
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

void clear(tData *head)
{
    tData *p = head;
    while (p != NULL)
    {
        tData *temp_p = p;
        p = p->next;
        free(temp_p);
    }
}

typedef struct
{
    tData *head;
    tData *tail;
} tQueue;

int less(const record *a, const record *b)
{

    char fio_a[32], fio_b[32];
    strcpy(fio_a, a->FIO);
    strcpy(fio_b, b->FIO);
    
    for (int i = 0; fio_a[i]; i++) fio_a[i] = tolower(fio_a[i]);
    for (int i = 0; fio_b[i]; i++) fio_b[i] = tolower(fio_b[i]);
    
    int fio_cmp = strcmp(fio_a, fio_b);
    if (fio_cmp < 0) {
        return 1;
    } else if (fio_cmp > 0) {
        return 0;
    }
    
    char street_a[18], street_b[18];
    strcpy(street_a, a->street);
    strcpy(street_b, b->street);
    
    for (int i = 0; street_a[i]; i++) street_a[i] = tolower(street_a[i]);
    for (int i = 0; street_b[i]; i++) street_b[i] = tolower(street_b[i]);
    
    int street_cmp = strcmp(street_a, street_b);
    if (street_cmp < 0) {
        return 1;
    } else {
        return 0;
    }
}
void InitializeQueue(tQueue *q)
{
    q->head = q->tail = NULL;
}

void MergeSeries(tData **a, int q, tData **b, int r, tQueue *c)
{
    while (q > 0 && r > 0 && *a != NULL && *b != NULL)
    {
        if (less((*a)->data, (*b)->data))
        {
            if (c->head == NULL)
            {
                c->head = c->tail = *a;
            }
            else
            {
                c->tail->next = *a;
                c->tail = *a;
            }
            *a = (*a)->next;
            q--;
        }
        else
        {
            if (c->head == NULL)
            {
                c->head = c->tail = *b;
            }
            else
            {
                c->tail->next = *b;
                c->tail = *b;
            }
            *b = (*b)->next;
            r--;
        }
    }

    while (q > 0 && *a != NULL)
    {
        if (c->head == NULL)
        {
            c->head = c->tail = *a;
        }
        else
        {
            c->tail->next = *a;
            c->tail = *a;
        }
        *a = (*a)->next;
        q--;
    }

    while (r > 0 && *b != NULL)
    {
        if (c->head == NULL)
        {
            c->head = c->tail = *b;
        }
        else
        {
            c->tail->next = *b;
            c->tail = *b;
        }
        *b = (*b)->next;
        r--;
    }

    if (c->tail != NULL)
    {
        c->tail->next = NULL;
    }
}

void SplitLists(tData *head, tData **a, tData **b, int *n)
{
    *a = head;
    *b = head->next;

    tData *k = *a, *p = *b;
    *n = 1;

    while (p != NULL)
    {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

void MergeSort(tData **S)
{
    if (*S == NULL || (*S)->next == NULL)
    {
        return;
    }

    tQueue c[2];
    tData *a, *b;
    int n;
    SplitLists(*S, &a, &b, &n);

    for (int p = 1; p < n; p *= 2)
    {
        InitializeQueue(&c[0]);
        InitializeQueue(&c[1]);
        int i = 0, m = n;

        while (m > 0)
        {
            int q = (m >= p) ? p : m;
            m -= q;

            int r = (m >= p) ? p : m;
            m -= r;

            MergeSeries(&a, q, &b, r, &c[i]);

            i = 1 - i;
        }

        a = c[0].head;
        b = c[1].head;
    }

    if (c[0].tail != NULL)
    {
        c[0].tail->next = NULL;
    }
    *S = c[0].head;
}

void navigatePages(record *allRecords, int records_count)
{
    int current_page = 0;
    int input;

    do
    {
        system("cls");

        int pages_count = records_count / RECORDS_ON_PAGE;
        if (records_count % RECORDS_ON_PAGE != 0)
        {
            pages_count++;
        }

        if (current_page >= pages_count)
        {
            current_page = pages_count - 1;
        }
        if (current_page < 0)
        {
            current_page = 0;
        }

        int pageStart = current_page * RECORDS_ON_PAGE;
        int pageEnd = pageStart + RECORDS_ON_PAGE;
        if (pageEnd > records_count)
        {
            pageEnd = records_count;
        }
        system("chcp 65001 > nul");
        printf("Страница: %d/%d. Записи с %d по %d из %d.\n",
               current_page + 1, pages_count, pageStart + 1, pageEnd, records_count);
        printf("----------------------------------------------------------------------------------------\n");
        printf("|%-35s | %-23s | %-9hs | %-6hs | %-14s|\n",
               "ФИО", "Улица", "Дом", "Квартира", "Дата");
        printf("----------------------------------------------------------------------------------------\n");
        system("chcp 866 > nul");
        for (int i = pageStart; i < pageEnd; i++)
        {
            printf("|%-32s | %-18s | %-6hd | %-8hd | %-10s|\n",
                   allRecords[i].FIO,
                   allRecords[i].street,
                   allRecords[i].House_number,
                   allRecords[i].Apartment_number,
                   allRecords[i].Date);
            
        }
        printf("----------------------------------------------------------------------------------------\n");
        system("chcp 65001 > nul");
        printf("\nУправление: 1 - предыдущая, 2 - следующая, 3 - вернутся в начало, 4 - перейти в конец, 0 - выход (показать отсортированный список)\n");
        printf("Введите команду: ");

        scanf("%d", &input);

        if (input == 1 && current_page > 0)
        {
            current_page--;
        }
        else if (input == 2)
        {
            if (current_page < pages_count - 1)
            {
                current_page++;
            }
        }
        else if (input == 3)
        {
            current_page = 0;
        }
        else if (input == 4)
        {
            current_page = pages_count;
        }
        else if (input == 0)
        {
            break;
        }

    } while (1);
}

void fillQ(tData **head, tData **tail, record *Records)
{
    for (int i = 0; i < N; i++)
    {
        AddToQueue(head, tail, &Records[i]);
    }
}

int main()
{

    FILE *fp;
    fp = fopen("testBase4.dat", "rb");
    if (fp == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return 1;
    }
    record *allRecords = malloc(N * sizeof(record));
    int records_count = fread(allRecords, sizeof(record), 4000, fp);

    int current_page = 0;
    navigatePages(allRecords, N);
    tData *head = NULL;
    tData *tail = NULL;
    fillQ(&head, &tail, allRecords);
    MergeSort(&head);
    tData *current = head;
    for (int i = 0; i < records_count && current != NULL; i++)
    {
        allRecords[i] = *(current->data);
        current = current->next;
    }
    clear(head);
    navigatePages(allRecords, N);

    fclose(fp);
    return 0;
}
