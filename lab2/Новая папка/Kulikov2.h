#pragma once
#include <string>
#include "Kulikov.h"
#include <vector>
#include <fstream>
#include "stdafx.h"

using namespace std;

class Kulikov2 // ��������� �� �������� �����
{
private:
	vector <Kulikov*> vect;
public:
	Kulikov2();
	~Kulikov2();

	void add_zay();// �������� ������
	void show_zay();//������ ��������
	void write2();
	void read2();
	void clear();
};

