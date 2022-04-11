#include "stdafx.h"
#include "Kulikov.h"
#include <string>
#include "iostream"
#include <fstream>



using namespace std;

Kulikov::Kulikov()
{
};

Kulikov::~Kulikov()
{
};
void Kulikov::add()
{
	cout << " Название банка ";
	cin >> Name;
	cout << " Введите лакацию в которой хотите открыть банк ";
	cin >> Maps;
	cout << " Введите стартовый баланс банка ";
	cin >> Balance;
	cout << " Введите необходимое количество работников ";
	cin >> Empl;
	system("cls");
}

void Kulikov::show()
{
	cout << endl << "Банк: " << Name << endl;
	cout << "Местоположение банка: " << Maps << endl;
	cout << "Стартовый капитал: " << Balance << endl;
	cout << "Кол-во работников: " << Empl << endl << endl;
}


void Kulikov::write(ofstream& fout)
{
	fout << Name << endl;
	fout << Maps << endl;
	fout << Balance << endl;
	fout << Empl << endl;
}


void Kulikov::read(ifstream& fin)
{
	fin >> Maps;
	fin >> Name;
	fin >> Balance;
	fin >> Empl;

};



