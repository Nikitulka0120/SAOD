#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define N 4000
#define RecordsOnPage 20

typedef struct record
{
    char FIO[32];
    char Street[18];
    short int HouseNumber;
    short int ApartmentNumber;
    char Date[10];
} record;

typedef struct tData
{
    struct tData *Next;
    record *Data;
} tData;

typedef struct Vertex
{
    int Weight;
    bool Used;
    record *Data;
    struct Vertex *Left;
    struct Vertex *Right;
} Vertex;

typedef struct tQueue
{
    tData *Head;
    tData *Tail;
} tQueue;

int findPage(int pagesCount)
{
    int input;
    printf("Введите номер страницы на которую желеете перейти:");
    do
    {scanf("%d", &input);
        if (input<1 || input>pagesCount)
        {
            printf("Введите действительный диапазон от 1 до %d:",pagesCount);
        }
        else
            break;
    } while(1);
    return input-1;
}

int countQueue(tData *head)
{
    int count = 0;
    tData *current = head;
    while (current != NULL)
    {
        count++;
        current = current->Next;
    }
    return count;
}

void PrintTableHeader()
{
    system("chcp 65001 > nul");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("| %-8s | %-35s | %-23s | %-9s | %-8s | %-14s |\n",
           "№", "ФИО", "Улица", "Дом", "Квартира", "Дата");
    printf("---------------------------------------------------------------------------------------------------\n");
}

void PrintRow(int index, record *r)
{
    system("chcp 866 > nul");
    printf("| %-6d | %-32s | %-18s | %-6hd | %-8hd | %-10s |\n",
           index + 1, r->FIO, r->Street, r->HouseNumber, r->ApartmentNumber, r->Date);
}

int findRecord(int recordsOnPage, int recordsCount)
{
    int input;
    printf("Введите номер записи на которую желаеете перейти:");
    do
    {
        scanf("%d", &input);
        if (input<1 || input>recordsCount)
        {
            printf("Введите действительный диапазон от 1 до %d:",recordsCount);
        }
        else
            break;
    } while(1);
    return input/RecordsOnPage;
}

void AddToQueue(tData **head, tData **tail, record *data)
{
    tData *p = (tData *)malloc(sizeof(tData));
    p->Data =data;
    p->Next= NULL;

    if (*tail==NULL)
    {
        *head=*tail= p;
    }
    else
    {
        (*tail)->Next =p;
        *tail = p;
    }
}

void InitializeQueue(tQueue *q)
{
    q->Head=q->Tail= NULL;
}

void printPages(tData *head, const char *title)
{
    int recordsCount =countQueue(head);
    int currentPage = 0;
    int input;
    do
    {
        system("cls");
        int pagesCount = (recordsCount + RecordsOnPage - 1) / RecordsOnPage;
        if (currentPage>=pagesCount)
            currentPage=pagesCount-1;
        if (currentPage<0)
            currentPage=0;
        int pageStart=currentPage * RecordsOnPage;
        int pageEnd=pageStart + RecordsOnPage;
        if (pageEnd>recordsCount)
            pageEnd=recordsCount;
        system("chcp 65001 > nul");
        printf("%s\n", title);
        printf("Страница: %d/%d. Записи с %d по %d из %d.\n",
               currentPage + 1, pagesCount, pageStart + 1, pageEnd, recordsCount);
        PrintTableHeader();
        system("chcp 866 > nul");
        tData *current = head;
        for (int i = 0; i < pageStart && current != NULL; i++)
        {
        current = current->Next;}
        for (int i = pageStart; i < pageEnd && current != NULL; i++)
        {
            record *r = current->Data;
            PrintRow(i, r);
            current = current->Next;}
        printf("-------------------------------------------------------------------------------------------------\n");
        system("chcp 65001 > nul");
        printf("\nУправление: \n1 - предыдущая, \n2 - следующая, \n3 - начало, \n4 - конец, \n5 - перейти на страницу, \n6 - перейти к записи \n0 - выход (перейти к следующему этапу)\n");
        printf("Введите команду: ");
        scanf("%d", &input);

        if (input == 1 && currentPage>0)
            currentPage--;
        else if (input == 2 && currentPage<pagesCount-1)
            currentPage++;
        else if (input == 3)
            currentPage = 0;
        else if (input == 4)
            currentPage = pagesCount - 1;
        else if (input == 5)
            currentPage = findPage(pagesCount);
        else if (input == 6)
            currentPage = findRecord(RecordsOnPage, recordsCount);
        else if (input == 0)
            break;

    } while(1);
}

int less(const record *a, const record *b)
{
    char fio_a[32], fio_b[32];
    strncpy(fio_a, a->FIO, sizeof(fio_a) - 1);
    fio_a[sizeof(fio_a) - 1] = '\0';
    strncpy(fio_b, b->FIO, sizeof(fio_b) - 1);
    fio_b[sizeof(fio_b) - 1] = '\0';
    int fio_cmp = strcmp(fio_a, fio_b);
    if (fio_cmp < 0)
    {
        return 1;
    }
    else if (fio_cmp > 0)
    {
        return 0;
        
        }

    char street_a[18],street_b[18];
    strncpy(street_a, a->Street, sizeof(street_a) - 1);
    street_a[sizeof(street_a) - 1] = '\0';
    strncpy(street_b, b->Street, sizeof(street_b) - 1);
    street_b[sizeof(street_b) - 1] = '\0';
    int street_cmp = strcmp(street_a, street_b);
    if (street_cmp < 0)
    {return 1;}
    else if (street_cmp > 0)
    {return 0;}
    return 1;
}

void clear(tData *head)
{
    tData *p = head;
    while (p) {
    tData *tmp = p;
    p = p->Next;
    free(tmp->Data);
    free(tmp);}
}

void MergeSeries(tData **a, int q, tData **b, int r, tQueue *c)
{
    while (q>0 && r>0 && *a!=NULL && *b!=NULL)
    {if (less((*a)->Data, (*b)->Data))
        {
            if (c->Head == NULL)
            {
                c->Head = c->Tail = *a;}
            else
            {
                c->Tail->Next = *a;
                c->Tail =*a;
            }
            *a =(*a)->Next;
            q--;
        }
        else
        {
            if (c->Head == NULL)
            {
                c->Head = c->Tail = *b;}
            else
            {
                c->Tail->Next = *b;
                c->Tail = *b;
            }
            *b = (*b)->Next;
            r--;
        }
    }

    while (q>0 && *a!= NULL)
    {
        if (c->Head == NULL)
        {
            c->Head = c->Tail = *a;
        }
        else
        {
            c->Tail->Next = *a;
            c->Tail = *a;
        }
        *a = (*a)->Next;
        q--;
    }

    while (r>0 && *b != NULL)
    {
        if (c->Head == NULL)
        {
            c->Head = c->Tail = *b;
        }
        else
        {
            c->Tail->Next = *b;
            c->Tail = *b;
        }
        *b = (*b)->Next;
        r--;
    }

    if (c->Tail!= NULL)
    {
        c->Tail->Next = NULL;
    }
}

void SplitLists(tData *head, tData **a, tData **b, int *n)
{
    *a = head;
    *b = head->Next;
    tData *k = *a, *p = *b;
    *n = 1;
    while (p != NULL)
    {
        (*n)++;
        k->Next = p->Next;
        k = p;
        p = p->Next;
    }
}

void MergeSort(tData **S)
{
    if (*S == NULL || (*S)->Next == NULL)
    {
        return;
    }

    tQueue c[2];
    tData *a, *b;
    int n;
    SplitLists(*S, &a, &b, &n);

    for (int p = 1; p<n; p *= 2)
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

        a = c[0].Head;
        b = c[1].Head;
    }

    if (c[0].Tail != NULL)
    {
        c[0].Tail->Next = NULL;
    }
    *S = c[0].Head;
}

int* getWeights(tData *head) {
    int maxKey = 0;
    for (tData *current = head; current != NULL; current = current->Next) {
        if (current->Data->HouseNumber > maxKey) {
            maxKey = current->Data->HouseNumber;
        }
    }
    int *keyCounts = (int*)calloc(maxKey + 1, sizeof(int));
    for (tData *current = head; current != NULL; current = current->Next) {
        int key = current->Data->HouseNumber;
        if (key <= maxKey) {
            keyCounts[key]++;
        }
    }
    
    return keyCounts;
}

void BinarySearch(int n, record **records, const char *searchKey, tData **head, tData **tail)
{
    int L = 0, R = n - 1;
    int m;
    while (L < R)
    {
        m = (L+R)/2;
        if (strncasecmp(records[m]->FIO, searchKey, 3) < 0)
            {
                L = m+1;
            }
        else
        {
            R = m;
        }
    }
    if (R >= n || strncasecmp(records[R]->FIO, searchKey, 3) != 0)
    {
        return;
    }
    int index = R;
    int count = 0;
    while (index<n && strncasecmp(records[index]->FIO, searchKey, 3) == 0)
    {
        AddToQueue(head, tail, records[index]);
        index++;
        count++;
    }
}

tData *ReadDataToQueue(const char *filename, int *recordsCount)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {printf("Ошибка открытия файла!\n");
        return NULL;}
    tData *head = NULL, *tail = NULL;
    *recordsCount = 0;
    while (*recordsCount < N)
    {
        record *newRecord = malloc(sizeof(record));
        if (newRecord == NULL)
        {printf("Ошибка выделения памяти!\n");
            break;
        }
        if (fread(newRecord, sizeof(record), 1, fp) != 1)
        {
        free(newRecord);
            break;
        }
        AddToQueue(&head, &tail, newRecord);
        (*recordsCount)++;
    }
    fclose(fp);
    return head;
}

Vertex *AddVertex(Vertex *root, Vertex *vertex)
{
    if (root == NULL)
    {return vertex;}
    else if (vertex->Data->HouseNumber < root->Data->HouseNumber)
    {
    root->Left = AddVertex(root->Left, vertex);
    }
    else
    {
        root->Right = AddVertex(root->Right, vertex);}
    return root;
}

Vertex *BuildTree(tData *head)
{
    if (head == NULL)
        return NULL;
    int n = countQueue(head);
    int *keyCounts = getWeights(head);
    Vertex **V = (Vertex **)malloc(n * sizeof(Vertex *));
    int i = 0;
    for (tData *current = head; current != NULL; current = current->Next)
    {
        V[i] = (Vertex *)malloc(sizeof(Vertex));
        V[i]->Data = current->Data;
        V[i]->Weight = keyCounts[current->Data->HouseNumber];
        V[i]->Left = NULL;
        V[i]->Right = NULL;
        V[i]->Used = false;
        i++;
    }
    Vertex *Root = NULL;
    for (int i = 0; i < n; i++)
    {
        int max = 0;
        int Index = -1;
        for (int j = 0; j < n; j++)
        {
            if (V[j]->Weight > max && V[j]->Used == false)
            {
                max = V[j]->Weight;
                Index = j;
            }
        }
        if (Index != -1)
        {
            V[Index]->Used = true;
            Root = AddVertex(Root, V[Index]);
        }
    }
    free(V);
    free(keyCounts);
    return Root;
}

void PrintTree(Vertex *root, int *index)
{
    if (root == NULL)
        return;
    PrintTree(root->Left, index);
    PrintRow(*index, root->Data);
    (*index)++;
    PrintTree(root->Right, index);
}
void PrintTReeTable(Vertex *root, const char *title)
{
    printf("%s\n", title);
    PrintTableHeader();
    int index = 0;
    PrintTree(root, &index);
    printf("---------------------------------------------------------------------------------------------------\n");
}

void SearchInTree(Vertex *root, int key, int foundCounter)
{
    if (root == NULL)
        printf("-------------------------------------------------------------------------------------------------\n");
    if (key == root->Data->HouseNumber)
    {
        system("chcp 866 > nul");
        record *p = root->Data;
        PrintRow(foundCounter, p);
        foundCounter++;
        SearchInTree(root->Right, key, foundCounter);
    }
    if (key < root->Data->HouseNumber)
        SearchInTree(root->Left, key, foundCounter);
    else
        SearchInTree(root->Right, key, foundCounter);
}

void FreeTree(Vertex *root)
{
    if (root)
    {
        FreeTree(root->Left);
        FreeTree(root->Right);
        free(root);
    }
}

record **BuildIndex(tData *head, int recordsCount)
{
    record **indexArray = malloc(recordsCount * sizeof(record *));
    tData *current = head;
    for (int i = 0; i < recordsCount && current != NULL; i++)
    {
        indexArray[i] = current->Data;
        current = current->Next;
    }
    return indexArray;
}

void InputSearchKey(char *searchKey)
{
    do
    {
        printf("Введите 3 буквы  фамилии поиска: ");
        system("chcp 866 > nul");
        scanf("%3s", searchKey);
        system("chcp 65001 > nul");

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        if (strlen(searchKey) != 3)
        {
            printf("Введите именно 3 символа\n");
            continue;
        }
        break;
    } while (1);
}

int main()
{
    int recordsCount;
    tData *head = ReadDataToQueue("testBase4.dat", &recordsCount);
    if (head == NULL || recordsCount == 0)
    {
        printf("Не удалось прочитать данные\n");
        return 1;
    }
    printPages(head, "Считанная база данных");
    MergeSort(&head);
    printPages(head, "Остсортированные списки");
    record **indexArray = BuildIndex(head, recordsCount);
    char searchKey[4];
    InputSearchKey(searchKey);
    tData *searchHead = NULL;
    tData *searchTail = NULL;
    BinarySearch(recordsCount, indexArray, searchKey, &searchHead, &searchTail);
    if (searchHead != NULL)
    {
        printPages(searchHead, "Результат поиска");
    }
    Vertex *TreeRoot = BuildTree(searchHead);
    PrintTReeTable(TreeRoot, "Дерево построенное по номеру ома");
    int key;
    system("chcp 65001 > nul");
    printf("\nВведите номер дома для поиска: ");
    scanf("%d", &key);
    PrintTableHeader();
    SearchInTree(TreeRoot, key, 0);
    clear(head);
    clear(searchHead);
    free(indexArray);
    return 0;
}
