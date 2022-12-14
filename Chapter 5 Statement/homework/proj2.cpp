#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;

int N = 10; // question num
const int N_max = 500; // 
int question_paras[N_max][2]; // question paras
char question_operaters[N_max]; // question operater list 
float question_answers[N_max]; // answer list of questions
float user_answers[N_max]; // user answer list of questions
bool correct_record[N_max]; // record correct question index
int bound[2] = {0,0}; // para bound
clock_t timer[N_max][2]; // record the system time 
float spend_time_list[N_max]; // record the time user give answers 
float spend_time_min = 1000; // 
bool complex_flag = true;



void read_file()
{
    ifstream fin;
	fin.open("InputFile.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "无法找到这个文件！" << endl;
		return;
	}
	char buff[1024] = { 0 };
	while (fin >> buff)
	{
		cout << buff <<endl;
	}
	fin.close();
}


int main(void)
{


}
