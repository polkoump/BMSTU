// заголовочный файл класса Vector (вариант 22, часть 1)
#pragma once
#include <iostream>

class Vector // Класс-вектор (элементы типа int)
{
    int *p = nullptr; // Указатель на динамический массив (элементы вектора)
    int n = 0;        // Размерность вектора (число элементов)
public:
    Vector();                         // Конструктор без параметров: пустой вектор (n = 0)
    Vector(const int *arr, int n);    // Конструктор на основе обычного массива размерности n
    Vector(const Vector &V);          // Конструктор копирования
    Vector(Vector &&V) noexcept;      // Конструктор перемещения
    ~Vector();                        // Деструктор

    int size() const { return n; }            // Размерность вектора
    const int *data() const { return p; }     // Адрес буфера (нужен для демонстрации копирования/перемещения)

    int &operator[](int index);               // Обращение к элементу по индексу (чтение и запись)
    const int &operator[](int index) const;   // Обращение к элементу константного вектора

    Vector &operator=(const Vector &V);       // Присваивание с копированием
    Vector &operator=(Vector &&V) noexcept;   // Присваивание с перемещением

    // Задание 22: операция < (Vector < Vector), результат bool.
    // Функция класса: первый операнд - объект класса, поэтому ее можно сделать членом класса
    bool operator<(const Vector &V) const;

    // Вставка в поток (cout или файл ostream) и извлечение из потока (cin или файл istream).
    // Первый операнд - поток, а не объект класса, поэтому функции дружественные (вне класса)
    friend std::ostream &operator<<(std::ostream &os, const Vector &V);
    friend std::istream &operator>>(std::istream &is, Vector &V);
};
