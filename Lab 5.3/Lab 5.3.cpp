// Lab 5.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
// < Якимів Наталія > 
// Лабораторна робота № 5.2
// Варіант 7
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Функція k(x) згідно умови
double k(double x)
{
    if (fabs(x) >= 1)
    {
        return (exp(x) + sin(x)) / (cos(x * x) + 1);
    }
    else
    {
        double S = 1.0;   // перший член: x^0 / 0!
        double term = 1.0;

        for (int i = 1; i <= 5; i++)
        {
            term *= x / i;   // рекурентне співвідношення
            S += term;
        }
        return S;
    }
}

int main()
{
    double zn, zk;
    int n;

    cout << "z_poch = "; cin >> zn;
    cout << "z_kinec = "; cin >> zk;
    cout << "n = "; cin >> n;

    double dz = (zk - zn) / n;

    cout << fixed << setprecision(6);

    // Шапка таблиці
    cout << "+------------+----------------------------+" << endl;
    cout << "|     z      |     f(z)                   |" << endl;
    cout << "+------------+----------------------------+" << endl;

    for (double z = zn; z <= zk + 1e-12; z += dz)
    {
        double value = k(z * z + 1) - k(z * z - 1) + 2 * k(z);

        cout << "| " << setw(10) << z
            << " | " << setw(26) << value << " |" << endl;
    }

    cout << "+------------+----------------------------+" << endl;

    return 0;
}
