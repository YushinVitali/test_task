# Тестовое задание

---

## Toolchain

- IDE: Qt Creator
- Compiler: GCC 8.1.0
- CMake: 3.21
- Sandbox: MinGW64

## Задачи

1. Напишите функцию, которая принимает на вход знаковое целое число и печатает его двоичное представление, не используя библиотечных классов или функций.

2. Напишите функцию, удаляющую последовательно дублирующиеся символы в строке:

```cpp
void RemoveDups(char* str);

// пример использования
char data[] = “AAA BBB AAA”;
RemoveDups(data);
printf(“%s\n”, data); // “A B A”
```

3. Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл. Алгоритмическая сложность решения должна быть меньше квадратичной.

```cpp
// структуру ListNode модифицировать нельзя
struct ListNode {
    ListNode *      prev;
    ListNode *      next;
    ListNode *      rand; // указатель на произвольный элемент данного списка, либо NULL
    std::string     data;
};

class List {
public:
    void Serialize   (FILE * file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize (FILE * file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
    ListNode *      head;
    ListNode *      tail;
    int       count;
};
```