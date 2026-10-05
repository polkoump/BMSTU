//Смирнова Полина ИУ8-14\6
//Задание 2

#include <iostream>
#include <vector>
#include <string> //getline
#include <limits> //ignor

using namespace std;

struct Baggage {
    string name;
    double weight;  // в кг
};

struct Passenger {
    string fio;
    vector<Baggage> baggage;
};

void InputPassenger(Passenger& p, istream& in) // тк не нужно выводить данные, вводим пассажира (input)
{
    cout << "FIO: ";
    getline(in, p.fio); //прочитать, записать в p.fio

    int n;
    cout << "Number of baggage: ";
    in >> n; //количество багажа в n
    in.ignore(numeric_limits<streamsize>::max(), '\n'); //что бы не решил что строка пустаяб выбрасывает символы а max значит все

    for (int i = 0; i < n; i++) {
        Baggage b;
        cout << "Baggage name: ";
        getline(in, b.name);
        cout << "Weight (kg): ";
        in >> b.weight;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        p.baggage.push_back(b); //добавляет b в конец (тк вектор)
    }
}

void OutPassenger(const Passenger& p, ostream& out) { //нельзя менять пассажира, вывод данных одного пассажира
    out << "FIO: " << p.fio << endl;
    for (auto& b : p.baggage) // сам предмет кладем в baggage он сам определяет тип
        out << "  " << b.name << ": " << b.weight << " kg" << endl;
}

double TotalWeight(const Passenger& p) { // общий вес багажа пассажира
    double sum = 0;
    for (auto& b : p.baggage)
        sum += b.weight;
    return sum;
}

double AverageWeight(const Passenger& p) { // средний вес одного предмета у пассажира
    if (p.baggage.empty()) return 0; // если пусто то 0
    return TotalWeight(p) / p.baggage.size();
}

bool Baggage20(const Passenger& p) { // багаж состоит из одной вещи весом более 20 кг, bool хранит только два варианта
    return p.baggage.size() == 1 && p.baggage[0].weight > 20; // && значит и, оба условия
}

int main() {
    int n;
    vector<Passenger> v; // создаем список всех пассажиров

    cout << "Number of passengers: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < n; i++) {
        cout << "Passenger " << i + 1 << endl;
        Passenger p;
        InputPassenger(p, cin);
        v.push_back(p); //кладет заполненного пассажира p в список v
    }

    // вывод введённых данных для контроля
    cout << " info " << endl;
    for (auto& p : v)
        OutPassenger(p, cout);

    if (v.empty()) {
        cout << "No passengers." << endl;
        return 0;
    }
    // 1. Число пассажиров с багажом тяжелее 30 кг
    int over30 = 0;
    for (auto& p : v)
        if (TotalWeight(p) > 30) over30++;
    cout << "1) Passengers with baggage > 30 kg: " << over30 << endl;

    // 2. Есть ли пассажир с одной вещью весом > 20 кг
    bool found = false;
    for (auto& p : v)
        if (Baggage20(p)) { found = true; break; }
    cout << "2) Passenger with a single baggage > 20 kg: "
         << (found ? "yes" : "no") << endl;

    // 3. Средний вес багажа на пассажира
    double totalAll = 0;
    for (auto& p : v)
        totalAll += TotalWeight(p);
    double avg = totalAll / v.size();
    cout << "3) Average baggage weight passenger: " << avg << " kg" << endl;

    // 4. Количество пассажиров с весом багажа выше среднего
    int moreAvg = 0;
    for (auto& p : v)
        if (TotalWeight(p) > avg) moreAvg++;
    cout << "4) Passengers with baggage more average: " << moreAvg << endl;

    // 5. Количество пассажиров с более чем тремя вещами
    int more3 = 0;
    for (auto& p : v)
        if (p.baggage.size() > 3) more3++;
    cout << "5) Passengers with more 3 baggages: " << more3 << endl;

    // 6. Средний вес одного предмета для каждого пассажира
    cout << "6) Average weight for passenger:" << endl;
    for (auto& p : v)
        cout << "   " << p.fio << ": " << AverageWeight(p) << " kg" << endl;

    // 7. Пассажир с максимальным весом багажа
    const Passenger* best = &v[0];
    for (auto& p : v)
        if (TotalWeight(p) > TotalWeight(*best)) best = &p;
    cout << "7) Passenger with max baggage weight: " << best->fio << endl;
    return 0;
}
