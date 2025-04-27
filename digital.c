#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_BUCKETS 256

typedef struct tData {
    struct tData *next;
    union {
        int Data;
        unsigned char digit[sizeof(int)];
    } data;
} tData;

typedef struct {
    tData *head;
    tData *tail;
} tQueue;

// Глобальные счётчики операций
int M_f = 0; // Перемещения
int C_f = 0; // Сравнения

void AddToQueue(tData **head, tData **tail, int data) {
    tData *p = (tData *)malloc(sizeof(tData));
    p->data.Data = data;
    p->next = NULL;

    if (*tail == NULL) {
        *head = *tail = p;
    } else {
        (*tail)->next = p;
        *tail = p;
    }
}

void fillDecQueue(tData **head, tData **tail, int n) {
    for (int i = n; i >= 1; i--) {
        AddToQueue(head, tail, i);
    }
}

void fillRanQueue(tData **head, tData **tail, int n) {
    srand(time(NULL));
    for (int i = 1; i <= n; i++) {
        int ranNum = rand() % 100;
        AddToQueue(head, tail, ranNum);
    }
}

void fillIncQueue(tData **head, tData **tail, int n) {
    for (int i = 1; i <= n; i++) {
        AddToQueue(head, tail, i);
    }
}

void print_list(tData *head) {
    tData *p = head;
    while (p != NULL) {
        printf("%d ", p->data.Data);
        p = p->next;
    }
    printf("\n");
}

void clear(tData *head) {
    tData *p = head;
    while (p != NULL) {
        tData *temp_p = p;
        p = p->next;
        free(temp_p);
    }
}

void InitializeQueue(tQueue *q) {
    q->head = q->tail = NULL;
    M_f++; // Операция инициализации
}

int checksum(tData *head) {
    int sum = 0;
    tData *p = head;
    while (p != NULL) {
        sum += p->data.Data;
        p = p->next;
    }
    return sum;
}

int count_series(tData *head) {
    if (head == NULL) return 0;
    int count = 1;
    tData *p = head;
    while (p->next != NULL) {
        if (p->data.Data > p->next->data.Data) {
            count++;
        }
        p = p->next;
    }
    return count;
}

tData* DigitalSort(tData *S, int bits) {
    tQueue queues[NUM_BUCKETS];
    tData *result = NULL;
    tData *last = NULL;
    
    for (int j = 0; j < bits; j++) {
        // Инициализация очередей
        for (int i = 0; i < NUM_BUCKETS; i++) {
            InitializeQueue(&queues[i]);
        }

        // Распределение по корзинам
        tData *current = S;
        while (current != NULL) {
            unsigned char d = current->data.digit[j];
            tData *next = current->next;
            
            if (queues[d].head == NULL) {
                queues[d].head = queues[d].tail = current;
            } else {
                queues[d].tail->next = current;
                queues[d].tail = current;
            }
            current->next = NULL;
            current = next;
            M_f += 3; // 3 операции перемещения
        }

        // Сборка обратно в список
        result = NULL;
        last = NULL;
        for (int i = 0; i < NUM_BUCKETS; i++) {
            C_f++; // Сравнение при проверке очереди
            if (queues[i].head != NULL) {
                if (result == NULL) {
                    result = queues[i].head;
                } else {
                    last->next = queues[i].head;
                }
                last = queues[i].tail;
                M_f += 2; // 2 операции перемещения
            }
        }
        
        S = result;
    }
    
    return result;
}

void printTestHeader() {
    printf("| %-5s | %-11s | %-11s | %-7s | %-7s | %-7s |\n", 
           "N", "Теор. (M+C)", "Факт. (M+C)", "Убыв.", "Случ.", "Возр.");
    printf("|-------|-------------|-------------|---------|---------|---------|\n");
}

void printTestRow(int n, int theory, int fact, int desc, int rand, int asc) {
    printf("| %-5d | %-11d | %-11d | %-7d | %-7d | %-7d |\n", 
           n, theory, fact, desc, rand, asc);
}

void testDigitalSort(int bits) {
    int sizes[] = {100, 200, 300, 400, 500};
    printf("\nТестирование цифровой сортировки (%d байта)\n", bits);
    printTestHeader();

    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int theory = 4 * bits * n; // Теоретическая оценка (4 операции на элемент на бит)
        int results[3] = {0};
        int fact_results[3] = {0};

        for (int t = 0; t < 3; t++) {
            tData *head = NULL, *tail = NULL;
            
            switch(t) {
                case 0: fillDecQueue(&head, &tail, n); break;
                case 1: fillRanQueue(&head, &tail, n); break;
                case 2: fillIncQueue(&head, &tail, n); break;
            }

            M_f = 0;
            C_f = 0;
            head = DigitalSort(head, bits);
            results[t] = M_f + C_f;
            fact_results[t] = 4 * bits * n + 2 * NUM_BUCKETS * bits; // Уточнённая оценка
            clear(head);
        }

        printTestRow(n, theory, fact_results[0], results[0], results[1], results[2]);
    }
}

void demoSort(int bits, int n) {
    tData *head = NULL, *tail = NULL;
    fillRanQueue(&head, &tail, n);
    
    printf("\nДемонстрация работы сортировки (%d элементов):\n", n);
    printf("Исходный список:\n");
    print_list(head);
    
    int sum_before = checksum(head);
    int series_before = count_series(head);
    printf("Контрольная сумма до сортировки: %d\n", sum_before);
    printf("Количество серий до сортировки: %d\n", series_before);
    
    M_f = C_f = 0;
    head = DigitalSort(head, bits);
    
    printf("\nОтсортированный список (M=%d, C=%d):\n", M_f, C_f);
    print_list(head);
    
    int sum_after = checksum(head);
    int series_after = count_series(head);
    printf("Контрольная сумма после сортировки: %d\n", sum_after);
    printf("Количество серий после сортировки: %d\n", series_after);
    
    clear(head);
}

int main() {
    // Тестирование для 4 байт (32 бита)
    testDigitalSort(4);
    
    // Демонстрация работы для 20 элементов (32 бита)
    demoSort(4, 20);

    // Тестирование для 2 байт (16 бит)
    testDigitalSort(2);
    
    // Демонстрация работы для 20 элементов (16 бит)
    demoSort(2, 20);
    
    return 0;
}
