// часть 2, вариант 22: наследование, статический и динамический полиморфизм
#include <iostream>
#include <vector>
using namespace std;

// Базовый класс - "вектор на плоскости"
class Vector2D
{
protected:            // Статус доступа protected: поля видны в производных классах
    double x, y;      // Координаты конца вектора (начало вектора в точке 0, 0)
public:
    Vector2D(double x, double y) : x(x), y(y) {} // Конструктор для инициализации полей
    virtual ~Vector2D() {}                       // Виртуальный деструктор (удаление через указатель на базовый класс)

    // Обычная (не виртуальная) функция печати: СТАТИЧЕСКОЕ связывание
    void printStatic() const
    {
        cout << "Vector2D: x=" << x << " y=" << y << endl;
    }

    // Виртуальная функция печати: ДИНАМИЧЕСКОЕ связывание
    virtual void print() const
    {
        cout << "Vector2D: x=" << x << " y=" << y << endl;
    }
};

// Производный класс - "вектор в трехмерном пространстве"
class Vector3D : public Vector2D
{
    double z; // Дополнительная координата
public:
    Vector3D(double x, double y, double z) : Vector2D(x, y), z(z) {} // Явный вызов конструктора базового класса

    // Переопределенная обычная функция (статическое связывание)
    void printStatic() const
    {
        cout << "Vector3D: ";
        Vector2D::printStatic();   // Сначала вызывается функция базового класса
        cout << "          z=" << z << endl;
    }

    // Переопределенная виртуальная функция (динамическое связывание)
    void print() const override
    {
        cout << "Vector3D: ";
        Vector2D::print();         // Сначала вызывается функция базового класса
        cout << "          z=" << z << endl;
    }
};

int main()
{
    Vector2D v2(1, 2);     // По одному объекту каждого класса
    Vector3D v3(3, 4, 5);

    cout << "=== 1. Вызовы через сами объекты ===" << endl;
    v2.print();
    v3.print();

    cout << "\n=== 2. Статический полиморфизм (функция НЕ virtual) ===" << endl;
    Vector2D *p = &v2;
    cout << "p -> объект Vector2D:" << endl;
    p->printStatic();
    p = &v3; // Указатель на базовый класс ссылается на объект производного класса
    cout << "p -> объект Vector3D (вызов определяется ТИПОМ УКАЗАТЕЛЯ):" << endl;
    p->printStatic(); // Вызовется функция Vector2D, координата z не печатается

    cout << "\n=== 3. Динамический полиморфизм (функция virtual) ===" << endl;
    p = &v2;
    cout << "p -> объект Vector2D:" << endl;
    p->print();
    p = &v3;
    cout << "p -> объект Vector3D (вызов определяется ТИПОМ ОБЪЕКТА):" << endl;
    p->print(); // Вызовется функция Vector3D, печатается и z

    cout << "\n=== 4. Вектор указателей на объекты разных классов ===" << endl;
    vector<Vector2D *> arr;               // Один контейнер - указатели на базовый класс
    arr.push_back(new Vector2D(1, 2));
    arr.push_back(new Vector3D(3, 4, 5));
    arr.push_back(new Vector2D(-1.5, 0));
    arr.push_back(new Vector3D(0, -2, 7.5));

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << "Элемент " << i << ":" << endl;
        arr[i]->print(); // Для каждого объекта вызывается "свой" вариант print
    }

    for (Vector2D *q : arr) delete q; // Освобождаем память (работает благодаря virtual ~Vector2D)
    return 0;
}
