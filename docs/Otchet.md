## Московский государственный технический университет имени Н.Э. Баумана

# ОТЧЁТ ПО ЛАБОРАТОРНОЙ РАБОТЕ
## Циклические алгоритмы, структуры и шаблоны string и vector в C++

**Выполнила:** Смирнова Полина Игоревна  
**Проверил:** Барыкин Дмиртий Ваильевич  
**Группа:** ИУ8-14  
**Вариант:** 22

**Москва, 2026**

---

# Часть 1. Вычисление arctg(x)

## Цель работы

Научиться использовать циклы для вычисления функции с заданной точностью и посмотреть, как точность влияет на число итераций.

## Условие задачи

Для \(x \in [-1; 1]\) вычислить \(\operatorname{arctg}(x)\) с точностями \(10^{-2}\), \(10^{-4}\), \(10^{-6}\) и \(10^{-8}\) по ряду:

\[
\operatorname{arctg}(x) = x - \frac{x^3}{3} + \frac{x^5}{5} - \ldots
\]

Сравнить результат с точным значением функции `atan(x)` и определить число итераций.

## Текст программы

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double x;
    cout << "Enter x in [-1; 1]: ";
    cin >> x;

    // Проверяем, что x находится в допустимом диапазоне.
    if (fabs(x) > 1) {
        cout << "Error: x must be in [-1; 1]" << endl;
        return 1;
    }

    double eps[] = {1e-2, 1e-4, 1e-6, 1e-8};

    // atan(x) используем как точное контрольное значение.
    cout << fixed << setprecision(10);
    cout << "atan(x) = " << atan(x) << endl;
    cout << "Eps\\tIter\\tResult\\t\\tError" << endl;

    // Проверяем каждую заданную точность.
    for (double e : eps) {
        double sum = 0.0, t = x;
        int n = 0;

        // Складываем члены, пока их модуль не меньше точности.
        while (fabs(t) >= e) {
            sum += t;
            n++;

            // Вычисляем следующий член через предыдущий.
            t = -t * x * x * (2.0 * n - 1) / (2.0 * n + 1);
        }

        // Выводим число итераций, сумму и фактическую ошибку.
        cout << scientific << e << "\\t" << n << "\\t"
             << fixed << setprecision(10) << sum << "\\t"
             << fabs(sum - atan(x)) << endl;
    }

    return 0;
}
```

## Проверка работы программы

Контрольный пример: `x = 0,5`. Точное значение `atan(0,5) = 0,4636476090`.

Результат программы:

| Точность ε | Итерации | Результат | Погрешность |
|---|---:|---:|---:|
| 10⁻² | 2 | 0,4583333333 | 0,0053142757 |
| 10⁻⁴ | 5 | 0,4636842758 | 0,0000366668 |
| 10⁻⁶ | 8 | 0,4636472421 | 0,0000003669 |
| 10⁻⁸ | 11 | 0,4636476132 | 0,0000000042 |

Полученные значения близки к `atan(0,5)`, а погрешность во всех строках меньше заданной точности. Значит, программа работает корректно.

## Вывод

Реализовано вычисление `arctg(x)` с помощью ряда и цикла. При повышении точности число итераций увеличивается; около `x = ±1` ряд сходится медленнее.

---

# Часть 2. Структуры, string и vector

## Цель работы

Научиться создавать структуры в C++, хранить данные в `string` и `vector` и проверять условие для элементов массива.

## Условие задачи

Создать структуры «Пассажир» и «Багаж». Для каждого пассажира ввести ФИО и список вещей с весом. Вывести введённые данные и проверить, есть ли пассажир, у которого ровно одна вещь весит больше 20 кг.

## Текст программы

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Одна вещь багажа: название и вес.
struct Baggage {
    string name;
    double weight;
};

// Пассажир и список его вещей.
struct Passenger {
    string fio;
    vector<Baggage> baggage;
};

void InputPassenger(Passenger& p) {
    cout << "FIO: ";
    getline(cin, p.fio);

    int n;
    cout << "Number of baggage: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\\n');

    // Вводим название и вес каждой вещи.
    for (int i = 0; i < n; i++) {
        Baggage b;
        cout << "Baggage name: ";
        getline(cin, b.name);
        cout << "Weight (kg): ";
        cin >> b.weight;
        cin.ignore(numeric_limits<streamsize>::max(), '\\n');
        p.baggage.push_back(b);
    }
}

void OutPassenger(const Passenger& p) {
    cout << "FIO: " << p.fio << endl;
    for (const auto& b : p.baggage)
        cout << " " << b.name << ": " << b.weight << " kg" << endl;
}

// Условие: у пассажира одна вещь, и она тяжелее 20 кг.
bool Baggage20(const Passenger& p) {
    return p.baggage.size() == 1 && p.baggage[0].weight > 20;
}

int main() {
    int n;
    vector<Passenger> passengers;
    cout << "Number of passengers: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\\n');

    // Сохраняем данные всех пассажиров.
    for (int i = 0; i < n; i++) {
        Passenger p;
        InputPassenger(p);
        passengers.push_back(p);
    }

    // Выводим данные для проверки ввода.
    for (const auto& p : passengers)
        OutPassenger(p);

    bool found = false;
    for (const auto& p : passengers) {
        if (Baggage20(p)) {
            found = true;
            break;
        }
    }

    cout << "Passenger with a single baggage > 20 kg: "
         << (found ? "yes" : "no") << endl;

    return 0;
}
```

## Проверка работы программы

Контрольный пример: Иванов — две вещи (18,5 и 6 кг); Петров — одна вещь (25 кг); Сидорова — три вещи (10, 3,5 и 2 кг).

**Ожидаемый и полученный ответ:** `yes`, так как у Петрова одна вещь весом 25 кг, что больше 20 кг.

Дополнительные проверки:
- Одна вещь весом ровно 20 кг — `no`.
- Одна вещь весом 20,5 кг — `yes`.
- Пассажиров нет — `no`.

## Вывод

Созданы структуры для хранения информации о пассажирах и багаже. С помощью `string` и `vector` реализованы ввод, вывод и поиск пассажира по условию. Контрольный пример и дополнительные проверки дали ожидаемые результаты.
