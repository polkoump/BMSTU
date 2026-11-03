// Лабораторная работа № 2. Ввод-вывод в файлы
// Вариант 22. Структура «автобус»
//Смирнова Полина
#include <iostream>
#include <fstream>   // ifstream, ofstream
#include <string>
#include <vector>
#include <limits>    // numeric_limits (для очистки буфера ввода)
using namespace std;

struct BUS
{
	string Model;
	double Length;
	double Height;
	int MaxPassengers;
};

void write_bus_text(ostream& out, const BUS& b)
{
	out << b.Model << endl;
	out << b.Length << ' ' << b.Height << ' ' << b.MaxPassengers << endl;
}

bool read_bus_text(istream& in, BUS& b)
{
	getline(in, b.Model);
	in >> b.Length >> b.Height >> b.MaxPassengers;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	return static_cast<bool>(in);               // true, если без ошибок
}
//в двоичный поток:
// числа записываются как они хранятся в памяти
void write_bus_bin(ostream& out, const BUS& b)
{
	out.write(b.Model.c_str(), b.Model.size() + 1); // +1 - вместе с символом '\0'
	out.write(reinterpret_cast<const char*>(&b.Length), sizeof(b.Length));
	out.write(reinterpret_cast<const char*>(&b.Height), sizeof(b.Height));
	out.write(reinterpret_cast<const char*>(&b.MaxPassengers), sizeof(b.MaxPassengers));
}

bool read_bus_bin(istream& in, BUS& b)
{
	getline(in, b.Model, '\0');                 //  до нулевого символа
	in.read(reinterpret_cast<char*>(&b.Length), sizeof(b.Length));
	in.read(reinterpret_cast<char*>(&b.Height), sizeof(b.Height));
	in.read(reinterpret_cast<char*>(&b.MaxPassengers), sizeof(b.MaxPassengers));
	return static_cast<bool>(in);
}

void print_buses(ostream& out, const vector<BUS>& Buses)
{
	for (const auto& b : Buses)
		out << b.Model << ". Длина: " << b.Length << " м, высота: " << b.Height
		    << " м, вместимость: " << b.MaxPassengers << " пасс." << endl;
}

int main(int argc, const char* argv[])
{
	// ровно 4 параметра: имя программы, режим, способ открытия, имя файла
	if (argc != 4) {
		cerr << "Error: Use four parameters (write|read text|binary filename)\n";
		return 5;
	}
	const string mode(argv[1]);
	const string open_mode(argv[2]);
	const string file_name(argv[3]);

	if (open_mode != "text" && open_mode != "binary") {
		cerr << "Error: second parameter must be text or binary\n";
		return 5;
	}

	vector<BUS> Buses;
	int n;

	if (mode == "write")
	{
		cout << "n="; cin >> n;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Buses.resize(n);
		for (int i = 0; i < n; i++)
		{
			cout << "Bus N=" << (i + 1) << endl;
			cout << "Model: ";        getline(cin, Buses[i].Model);
			cout << "Length (m): ";   cin >> Buses[i].Length;
			cout << "Height (m): ";   cin >> Buses[i].Height;
			cout << "Max passengers: "; cin >> Buses[i].MaxPassengers;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (open_mode == "text")
		{
			ofstream fout(file_name);        // текстовый режим
			if (!fout) { cerr << "Error, can't open file" << endl; return 1; }
			fout << n << endl;
			for (const auto& b : Buses) write_bus_text(fout, b);
			fout.close();
		}
		else
		{
			ofstream fout(file_name, ios::binary); // двоичный режим
			if (!fout) { cerr << "Error, can't open file" << endl; return 1; }
			fout.write(reinterpret_cast<const char*>(&n), sizeof(n));
			for (const auto& b : Buses) write_bus_bin(fout, b);
			fout.close();
		}
	}
	else if (mode == "read")
	{
		if (open_mode == "text")
		{
			ifstream fin(file_name);
			if (!fin) { cout << endl << "Error, file not found" << endl; return 1; }
			fin >> n;
			fin.ignore(numeric_limits<streamsize>::max(), '\n'); // пропускаем конец строки после n
			Buses.resize(n);
			for (auto& b : Buses) read_bus_text(fin, b);
			fin.close();
		}
		else
		{
			ifstream fin(file_name, ios::binary);
			if (!fin) { cout << endl << "Error, file not found" << endl; return 1; }
			fin.read(reinterpret_cast<char*>(&n), sizeof(n));
			Buses.resize(n);
			for (auto& b : Buses) read_bus_bin(fin, b);
			fin.close();
		}
		print_buses(cout, Buses);
	}
	else
	{
		cerr << "Error: first parameter must be write or read\n";
		return 5;
	}
	return 0;
}
