//файл реализации класса Vector (вариант 22, часть 1)
#include "Vector.h"
#include <iostream>
using namespace std;

// Конструктор без параметров: задает "пустой" вектор
Vector::Vector()
{
    p = nullptr;
    n = 0;
    cout << "  [Vector()]" << endl;
}

// Конструктор на основе обычного массива
Vector::Vector(const int *arr, int n)
{
    this->n = n;                  // Задаем число элементов
    this->p = new int[n];         // Выделяем память
    for (int i = 0; i < n; i++)   // Копируем элементы из обычного массива
        this->p[i] = arr[i];
    cout << "  [Vector(int*, n) n=" << n << "]" << endl;
}

// Конструктор копирования: создает НЕЗАВИСИМУЮ копию (новая память + копирование элементов)
Vector::Vector(const Vector &V)
{
    n = V.n;
    p = new int[n];               // Выделяем свою собственную память
    for (int i = 0; i < n; i++)
        p[i] = V.p[i];            // Копируем каждый элемент
    cout << "  [Vector(const Vector&) - КОПИРОВАНИЕ n=" << n << "]" << endl;
}

// Конструктор перемещения: "забирает" память у временного/перемещаемого объекта, ничего не копируя
Vector::Vector(Vector &&V) noexcept : p(V.p), n(V.n)
{
    // Исходный объект остается пустым, чтобы его деструктор не освободил чужую память
    V.p = nullptr;
    V.n = 0;
    cout << "  [Vector(Vector&&) - ПЕРЕМЕЩЕНИЕ n=" << n << "]" << endl;
}

// Деструктор: освобождает динамическую память
Vector::~Vector()
{
    cout << "  [~Vector() n=" << n << "]" << endl;
    delete[] p; // delete[] для nullptr безопасен
}

// Доступ к элементу по индексу (возвращаем ссылку, поэтому можно и читать, и записывать)
int &Vector::operator[](int index)
{
    return p[index];
}

const int &Vector::operator[](int index) const
{
    return p[index];
}

// Присваивание с копированием
Vector &Vector::operator=(const Vector &V)
{
    if (this != &V) // Защита от присваивания самому себе
    {
        delete[] p;           // Освобождаем память старого содержимого
        n = V.n;
        p = new int[n];       // Выделяем новую память
        for (int i = 0; i < n; i++)
            p[i] = V.p[i];    // Копируем элементы
    }
    cout << "  [operator=(const Vector&) - КОПИРОВАНИЕ]" << endl;
    return *this; // Возвращаем ссылку на текущий объект (допускает цепочку a = b = c)
}

// Присваивание с перемещением
Vector &Vector::operator=(Vector &&V) noexcept
{
    if (this != &V)
    {
        delete[] p;   // Освобождаем память старого содержимого
        p = V.p;      // Забираем указатель на чужой массив (без копирования элементов)
        n = V.n;
        V.p = nullptr; // Исходный вектор становится пустым
        V.n = 0;
    }
    cout << "  [operator=(Vector&&) - ПЕРЕМЕЩЕНИЕ]" << endl;
    return *this;
}

// Операция <: сравнение векторов последовательно по элементам
//  - элемент первого вектора меньше элемента второго  -> true
//  - элемент первого вектора больше элемента второго  -> false
//  - элементы равны                                    -> переход к следующей паре
//  - элементы в каком-либо векторе закончились         -> false
bool Vector::operator<(const Vector &V) const
{
    for (int i = 0; i < n && i < V.n; i++)
    {
        if (p[i] < V.p[i]) return true;
        if (p[i] > V.p[i]) return false;
    }
    return false;
}

// Вставка в поток: формат "n: (a0, a1, ...)"
ostream &operator<<(ostream &os, const Vector &V)
{
    os << V.n << ": (";
    for (int i = 0; i < V.n; i++)
    {
        if (i > 0) os << ", ";
        os << V.p[i];
    }
    os << ")";
    return os; // Возвращаем поток, чтобы можно было писать cout << a << b
}

// Извлечение из потока: сначала читается n, затем n целых чисел
istream &operator>>(istream &is, Vector &V)
{
    int k = 0;
    if (!(is >> k) || k < 0) return is; // Ошибка чтения - выходим (в потоке установлен флаг ошибки)
    int *tmp = new int[k];
    for (int i = 0; i < k; i++) is >> tmp[i];
    delete[] V.p;  // Освобождаем старое содержимое
    V.p = tmp;
    V.n = k;
    return is;
}
