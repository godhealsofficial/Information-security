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
	cout << " �������� ����� ";
	cin >> Name;
	cout << " ������� ������� � ������� ������ ������� ���� ";
	cin >> Maps;
	cout << " ������� ��������� ������ ����� ";
	cin >> Balance;
	cout << " ������� ����������� ���������� ���������� ";
	cin >> Empl;
	system("cls");
}

void Kulikov::show()
{
	cout << endl << "����: " << Name << endl;
	cout << "�������������� �����: " << Maps << endl;
	cout << "��������� �������: " << Balance << endl;
	cout << "���-�� ����������: " << Empl << endl << endl;
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



