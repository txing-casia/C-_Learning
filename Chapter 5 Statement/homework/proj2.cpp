#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <chrono>
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



int main()
{
    int correct = 0;


    cout<<"Correct Answer Number: "<< correct <<endl;
    cout<<"Wrong Answer Number: "<< N - correct <<endl;
    cout<<"Your score is: "<< (correct*1.0/N)*100 <<endl;
    cout<<"The average spend time per question: "<<evarage_time<<'s'<<endl;
    cout<<"The minimal spend time for one question: "<<spend_time_min<<'s'<<endl;

    // print the question answers with wrong user answers 
    if (N - correct)
    {
        cout<<"Questions you give wrong answers: "<<endl;
        for(int i=0;i<N;i++)
        {
            if (not correct_record[i])
                cout<<question_paras[i][0]<<question_operaters[i]<<question_paras[i][1]<<'='<<question_answers[i]<<endl;
        }
    }
    cout<<"--end--"<<endl;

}
