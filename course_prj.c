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
    strncpy(fio_a, a->FIO, sizeof(fio_a) - 1);
    fio_a[sizeof(fio_a) - 1] = '\0';
    strncpy(fio_b, b->FIO, sizeof(fio_b) - 1);
    fio_b[sizeof(fio_b) - 1] = '\0';

    for (int i = 0; fio_a[i]; i++)
        fio_a[i] = tolower((unsigned char)fio_a[i]);
    for (int i = 0; fio_b[i]; i++)
        fio_b[i] = tolower((unsigned char)fio_b[i]);

    int fio_cmp = strcmp(fio_a, fio_b);
    if (fio_cmp < 0)
    {
        return 1;
    }
    else if (fio_cmp > 0)
    {
        return 0;
    }

    char street_a[18], street_b[18];
    strncpy(street_a, a->street, sizeof(street_a) - 1);
    street_a[sizeof(street_a) - 1] = '\0';
    strncpy(street_b, b->street, sizeof(street_b) - 1);
    street_b[sizeof(street_b) - 1] = '\0';

    for (int i = 0; street_a[i]; i++)
        street_a[i] = tolower((unsigned char)street_a[i]);
    for (int i = 0; street_b[i]; i++)
        street_b[i] = tolower((unsigned char)street_b[i]);

    int street_cmp = strcmp(street_a, street_b);
    if (street_cmp < 0)
    {
        return 1;
    }
    else if (street_cmp > 0)
    {
        return 0;
    }

    return 1;
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

typedef record* (*GetRecordFunc)(int index, void *source);

void paginateRecords(void *source, int records_count, GetRecordFunc getRecord, const char *title)
{
    if (records_count == 0)
    {
        system("chcp 65001 > nul");
        printf("%s\n", title);
        printf("Нет данных для отображения.\n");
        return;
    }

    int current_page = 0;
    int input;

    do
    {
        system("cls");

        int pages_count = (records_count + RECORDS_ON_PAGE - 1) / RECORDS_ON_PAGE;
        if (current_page >= pages_count)
            current_page = pages_count - 1;
        if (current_page < 0)
            current_page = 0;

        int pageStart = current_page * RECORDS_ON_PAGE;
        int pageEnd = pageStart + RECORDS_ON_PAGE;
        if (pageEnd > records_count)
            pageEnd = records_count;

        system("chcp 65001 > nul");
        printf("%s\n", title);
        printf("Страница: %d/%d. Записи с %d по %d из %d.\n",
               current_page + 1, pages_count, pageStart + 1, pageEnd, records_count);
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("| %-6s | %-35s | %-23s | %-9s | %-8s | %-14s |\n",
               "№", "ФИО", "Улица", "Дом", "Квартира", "Дата");
        printf("-------------------------------------------------------------------------------------------------\n");
        system("chcp 866 > nul");

        for (int i = pageStart; i < pageEnd; i++)
        {
            record *r = getRecord(i, source);
            if (!r) continue;
            printf("| %-4d | %-32s | %-18s | %-6hd | %-8hd | %-10s |\n",
                   i + 1, r->FIO, r->street, r->House_number, r->Apartment_number, r->Date);
        }

        printf("-------------------------------------------------------------------------------------------------\n");
        system("chcp 65001 > nul");
        printf("\nУправление: 1 - предыдущая, 2 - следующая, 3 - начало, 4 - конец, 0 - выход\n");
        printf("Введите команду: ");
        scanf("%d", &input);

        if (input == 1 && current_page > 0)
            current_page--;
        else if (input == 2 && current_page < pages_count - 1)
            current_page++;
        else if (input == 3)
            current_page = 0;
        else if (input == 4)
            current_page = pages_count - 1;
        else if (input == 0)
            break;

    } while (1);
}

record* getRecordFromArray(int index, void *source)
{
    record *arr = (record*)source;
    return &arr[index];
}

record* getRecordFromPtrArray(int index, void *source)
{
    record **arr = (record**)source;
    return arr[index];
}

record* getRecordFromQueue(int index, void *source)
{
    tData *cur = (tData*)source;
    for (int i = 0; i < index && cur; i++)
        cur = cur->next;
    return cur ? cur->data : NULL;
}

void fillQ(tData **head, tData **tail, record *Records)
{
    for (int i = 0; i < N; i++)
    {
        AddToQueue(head, tail, &Records[i]);
    }
}

void BinarySearchAndFill(int n, record **records, const char *X, tData **head, tData **tail)
{
    int L = 0, R = n - 1;
    int m;
    while (L < R)
    {
        m = (L + R) / 2;
        if (strncasecmp(records[m]->FIO, X, 3) < 0)
        {
            L = m + 1;
        }
        else
        {
            R = m;
        }
    }
    if (R >= n || strncasecmp(records[R]->FIO, X, 3) != 0)
    {
        return;
    }
    int index = R;
    int count = 0;
    while (index < n && strncasecmp(records[index]->FIO, X, 3) == 0)
    {
        AddToQueue(head, tail, records[index]);
        index++;
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
    paginateRecords(allRecords, records_count, getRecordFromArray, "ВСЕ ЗАПИСИ");
    tData *head = NULL;
    tData *tail = NULL;
    fillQ(&head, &tail, allRecords);
    MergeSort(&head);
    tData *current = head;
    record **sortedPointers = malloc(records_count * sizeof(record *));

    for (int i = 0; i < records_count && current != NULL; i++)
    {
        sortedPointers[i] = current->data;
        current = current->next;
    }
    clear(head);
    paginateRecords(sortedPointers, records_count, getRecordFromPtrArray, "ОТСОРТИРОВАННЫЕ ЗАПИСИ");
    tData *SearchQ = NULL;
    char SearchKey[4];
    int scnresult;
    do
    {
        printf("Введите ровно 3 буквы фамилии для поиска (если символов будет больше 3х, остаток будет отброшен): ");
        system("chcp 866 > nul");
        scnresult = scanf("%3s", SearchKey);
        system("chcp 65001 > nul");
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        if (strlen(SearchKey) != 3)
        {
            printf("Введите именно 3 символа.\n");
            continue;
        }
        break;
    } while (1);
    tData *SearchHead = NULL;
    tData *SearchTail = NULL;
    BinarySearchAndFill(N, sortedPointers, SearchKey, &SearchHead, &SearchTail);
    paginateRecords(SearchHead, records_count, getRecordFromQueue, "РЕЗУЛЬТАТЫ ПОИСКА");
    free(sortedPointers);
    free(allRecords);
    fclose(fp);
    return 0;
}
