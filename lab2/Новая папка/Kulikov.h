#pragma once
#include <string> 

using namespace std;

class Kulikov // �������� �����
{
private:
	string Maps;
	string Name;
	int Balance;
	int Empl;// ���������
public:
	Kulikov();
	~Kulikov();
	void add();
	void show();
	void write(ofstream& fout);
	void read(ifstream& fin);


};
