// демонстрация работы класса Vector (вариант 22, часть 1)
// Входные данные читаются из input.txt, результаты выводятся в output.txt
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

// Вся демонстрация вынесена в функцию, чтобы деструкторы объектов вызывались
// при выходе из нее, пока cout еще перенаправлен в output.txt
void demo(ifstream &fin)
{

    // 1. Операция >> (ввод из файла) и << (вывод в файл) 
    cout << "=== 1. Ввод из input.txt (operator>>) ===" << endl;
    Vector A, B, C, D, E, F;
    fin >> A >> B >> C >> D >> E >> F;
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "E = " << E << " (пустой вектор)" << endl;
    cout << "F = " << F << endl;

    // 2. Операция
    cout << "\n=== 2. Операция [] ===" << endl;
    cout << "A[1] = " << A[1] << endl;
    A[1] = 20; // Запись через []
    cout << "После A[1] = 20: A = " << A << endl;
    A[1] = 2;  // Возвращаем исходное значение
    cout << "Вернули A[1] = 2: A = " << A << endl;

    //3. Операция < (задание 22) 
    cout << "\n=== 3. Операция < (Vector < Vector) ===" << endl;
    cout << "A < B : " << (A < B) << "   (1,2,3 и 1,2,5: 3 < 5 -> истина)" << endl;
    cout << "B < A : " << (B < A) << "   (5 > 3 -> ложь)" << endl;
    cout << "A < D : " << (A < D) << "   (все пары равны -> ложь)" << endl;
    cout << "A < C : " << (A < C) << "   (в C элементы закончились -> ложь)" << endl;
    cout << "C < A : " << (C < A) << "   (в C элементы закончились -> ложь)" << endl;
    cout << "A < F : " << (A < F) << "   (1 < 5 -> истина)" << endl;
    cout << "F < A : " << (F < A) << "   (5 > 1 -> ложь)" << endl;
    cout << "E < A : " << (E < A) << "   (пустой вектор -> ложь)" << endl;

    //4. Конструктор копирования и перемещения
    cout << "\n=== 4. Конструктор копирования и конструктор перемещения ===" << endl;
    const int *addrA = A.data();
    {
        cout << "Создаем копию: Vector copy(A);" << endl;
        Vector copy(A);
        cout << "  A    = " << A << endl;
        cout << "  copy = " << copy << endl;
        cout << "  Буфер у copy тот же, что у A? " << (copy.data() == addrA ? "да" : "нет (память выделена заново)") << endl;
        cout << "  A после копирования: " << A << " (не изменился)" << endl;

        const int *addrCopy = copy.data();
        cout << "Перемещаем: Vector moved(std::move(copy));" << endl;
        Vector moved(std::move(copy));
        cout << "  moved = " << moved << endl;
        cout << "  copy  = " << copy << " (исходный объект стал пустым)" << endl;
        cout << "  Буфер у moved тот же, что был у copy? " << (moved.data() == addrCopy ? "да (элементы не копировались)" : "нет") << endl;
        cout << "Выход из блока - вызовутся деструкторы moved и copy:" << endl;
    }

    // 5. Присваивание с копированием и перемещением
    cout << "\n=== 5. Присваивание с копированием и с перемещением ===" << endl;
    Vector X;
    cout << "Присваивание с копированием: X = B;" << endl;
    X = B;
    cout << "  X = " << X << ",  B = " << B << " (B не изменился)" << endl;
    cout << "  Буфер у X тот же, что у B? " << (X.data() == B.data() ? "да" : "нет (выполнено копирование элементов)") << endl;

    Vector Y;
    cout << "Присваивание с перемещением: Y = std::move(X);" << endl;
    const int *addrX = X.data();
    Y = std::move(X);
    cout << "  Y = " << Y << endl;
    cout << "  X = " << X << " (исходный вектор стал пустым)" << endl;
    cout << "  Буфер у Y тот же, что был у X? " << (Y.data() == addrX ? "да (элементы не копировались)" : "нет") << endl;

    // ---------- 6. Присваивание самому себе ----------
    cout << "\n=== 6. Присваивание самому себе ===" << endl;
    Vector &ref = D; // Ссылка нужна, чтобы компилятор не выдавал предупреждение
    D = ref;
    cout << "  D = " << D << " (данные сохранены)" << endl;

    cout << "\n=== Конец демонстрации, вызываются деструкторы ===" << endl;
}

int main()
{
    ifstream fin("input.txt");   // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin || !fout)
    {
        cerr << "Ошибка открытия файлов" << endl;
        return 1;
    }
    // Перенаправляем cout в файл, чтобы и сообщения конструкторов попали в output.txt
    streambuf *oldBuf = cout.rdbuf(fout.rdbuf());
    demo(fin);
    cout.rdbuf(oldBuf); // Возвращаем cout на консоль
    return 0;
}
