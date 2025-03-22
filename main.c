#include <stdio.h>
#include <stdlib.h>

// Глобальные данные
long data[] = {4, 8, 15, 16, 23, 42};
size_t data_length = sizeof(data) / sizeof(data[0]);

// Функция для вывода целого числа
void print_int(long value) {
    printf("%ld ", value);
    fflush(stdout);
}

// Функция p: проверяет, является ли число нечетным
int p(long value) {
    return value & 1;
}

// Структура для хранения элементов списка
typedef struct Node {
    long value;
    struct Node* next;
} Node;

// Функция add_element: создает новый узел списка
Node* add_element(long value, Node* next) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        abort();
    }
    new_node->value = value;
    new_node->next = next;
    return new_node;
}

// Функция m: итеративно применяет функцию ко всем элементам списка
void m(Node* node, void (*func)(long)) {
    while (node) {
        func(node->value);
        node = node->next;
    }
}

// Функция f: итеративно фильтрует список по заданному условию
Node* f(Node* node, Node* acc, int (*predicate)(long)) {
    while (node) {
        if (predicate(node->value)) {
            acc = add_element(node->value, acc);
        }
        node = node->next;
    }
    return acc;
}

// Функция free_list: освобождает память, выделенную под связанный список
void free_list(Node* node) {
    while (node) {
        Node* temp = node;
        node = node->next;
        free(temp);
    }
}

// Главная функция
int main() {
    // Создаем связанный список из массива data
    Node* list = NULL;
    for (size_t i = 0; i < data_length; ++i) {
        list = add_element(data[data_length - 1 - i], list);
    }

    // Выводим все элементы списка
    m(list, print_int);
    puts("");

    // Фильтруем список, оставляя только нечетные числа
    Node* filtered_list = f(list, NULL, p);

    // Выводим отфильтрованный список
    m(filtered_list, print_int);
    puts("");

    // Освобождаем память
    free_list(list);
    free_list(filtered_list);

    return 0;
}