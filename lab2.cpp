//Смирнова Полина ИУ8-14\6
//Задание 2, вариант 22

#include <iostream>
#include <vector>
#include <string> //getline
#include <limits> //ignore

using namespace std;

struct Baggage {
    string name;
    double weight;  // в кг
};

struct Passenger {
    string fio;
    vector<Baggage> baggage;
};

void InputPassenger(Passenger& p, istream& in) // ввод одного пассажира
{
    cout << "FIO: ";
    getline(in, p.fio);

    int n;
    cout << "Number of baggage: ";
    in >> n;
    in.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        Baggage b;
        cout << "Baggage name: ";
        getline(in, b.name);
        cout << "Weight (kg): ";
        in >> b.weight;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        p.baggage.push_back(b);
    }
}

void OutPassenger(const Passenger& p, ostream& out) { // вывод одного пассажира
    out << "FIO: " << p.fio << endl;
    for (auto& b : p.baggage)
        out << "  " << b.name << ": " << b.weight << " kg" << endl;
}

bool Baggage20(const Passenger& p) { // багаж состоит из одной вещи весом более 20 кг
    return p.baggage.size() == 1 && p.baggage[0].weight > 20;
}

int main() {
    int n;
    vector<Passenger> v; // список всех пассажиров

    cout << "Number of passengers: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        cout << "Passenger " << i + 1 << endl;
        Passenger p;
        InputPassenger(p, cin);
        v.push_back(p);
    }

    // вывод введённых данных для контроля
    cout << " info " << endl;
    for (auto& p : v)
        OutPassenger(p, cout);

    // 22. Есть ли пассажир с одной вещью весом > 20 кг
    bool found = false;
    for (auto& p : v)
        if (Baggage20(p)) { found = true; break; }
    cout << "Passenger with a single baggage > 20 kg: "
         << (found ? "yes" : "no") << endl;

    return 0;
}
