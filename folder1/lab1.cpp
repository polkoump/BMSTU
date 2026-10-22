//Смирнова Полина ИУ8-14\6
//Задание 1
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    double x;
    cout << "Enter x in [-1; 1]: ";
    cin >> x;

    if (fabs(x) > 1){
        cout << "Error: x must be in [-1; 1]" << endl;
        return 1;
    }

    double eps[4] = {1e-2, 1e-4, 1e-6, 1e-8};

    cout << fixed << setprecision(10);
    cout << "atan(x) = " << atan(x) << endl;
    cout << "Eps\tItert\tResult\t\tError" << endl;

    for (int k = 0; k < 4; k++) {
        double e = eps[k];
        double sum = 0.0;
        double t = x;
        int n = 0;

        while (fabs(t) >= e) {
            sum += t;
            n++;
            t = -t * x * x * (2.0 * n - 1) / (2.0 * n + 1);
        }

        cout << scientific << setprecision(1) << e << "\t";
        cout << fixed << setprecision(10);
        cout << n << "\t";
        cout << sum << "\t";
        cout << fabs(sum - atan(x)) << endl;
    }

    return 0;
}
