#include "stdafx.h"
#include "Kulikov2.h"
#include <windows.h>
#include <locale.h>
#include <conio.h> 

Kulikov2::Kulikov2()
{
}


Kulikov2::~Kulikov2()
{
}


void Kulikov2::add_zay()
{
	Kulikov* N = new Kulikov;
	N->add();
	vect.push_back(N);

}


void Kulikov2::show_zay()
{
	for (auto N : vect)
		N->show();
}


void Kulikov2::write2()
{
	ofstream f("заявки.txt");
	f << vect.size() << endl;

	//CharToOemA(f,txt);

	for (auto N : vect)
		N->write(f);
	f.close();
}

void Kulikov2::read2()
{
	ifstream f("заявки.txt");
	int o;// переменная количества файлов для считки
	f >> o;
	for (int i = 0; i < o; i++)
	{
		Kulikov* N = new Kulikov;
		N->read(f);
		vect.push_back(N);

	}

	f.close();
}

void Kulikov2::clear()
{
	for (auto N : vect)
		delete N;
	vect.clear();
}






