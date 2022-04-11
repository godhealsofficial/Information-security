#include "stdafx.h"
#include <conio.h>
#include "Kulikov.h"
#include "Kulikov2.h"
#include "Kulikov2.h"
#include<iostream>
#include<string>
#include<fstream>


using namespace std;



int main()
{
	Kulikov2 K2;
	int a;
	setlocale(0, "Russian");

	while (1) //цикл по строкам
	{
		cout << "1-Добавить заявку " << endl;
		cout << "2-Вывести заявки" << endl;
		cout << "3-Считать заявки " << endl;
		cout << "4-Записать заявки в файл " << endl;
		cout << "5-Очистка " << endl << endl;
		cin >> a;
		system("cls");
		switch (a)
		{
		case 1:
		{
			K2.add_zay();
			break;
		}


		case 2:
		{
			K2.show_zay();
			break;
		}


		case 3:
		{
			K2.read2();
			break;
		}

		case 4:
		{
			K2.write2();
			break;
		}
		case 5:
		{
			K2.clear();
			break;
		}

		}

	}


	_getch();
	return 0;
}

