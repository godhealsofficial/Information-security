#pragma once
#include <string>
#include "Kulikov.h"
#include <vector>
#include <fstream>
#include "stdafx.h"

using namespace std;

class Kulikov2 // заявления на создание банка
{
private:
	vector <Kulikov*> vect;
public:
	Kulikov2();
	~Kulikov2();

	void add_zay();// добавить заявки
	void show_zay();//заявки показать
	void write2();
	void read2();
	void clear();
};

