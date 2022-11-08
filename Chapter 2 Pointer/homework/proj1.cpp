#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

const int N = 3; // question num
int question_paras[N][2]; // question paras
char question_operaters[N]; // question operater list 
float question_answers[N]; // answer list of questions
float user_answers[N]; // user answer list of questions
bool correct_record[N]; // record correct question index
int bound[2]; // para bound

void get_bound(void)
{
    cout<<"Input the integral bound values a and b of [a,b):"<<endl;
    cout<<"a:";
    cin>>bound[0];
    cout<<"b:";
    cin>>bound[1];
}

void generate_questions()
{
    int oper_index = 0;
    srand((int)time(0)); // set random seed
    // rand()%(b-a)+a 来产生[a,b)
    for(int i=0;i<N;i++)
    {
        question_paras[i][0] = rand()%(bound[1]-bound[0])+bound[0];
        question_paras[i][1] = rand()%(bound[1]-bound[0])+bound[0];
        /*  
            0: +
            1: -
            2: *
            3: /
        */
        oper_index = rand()%4;
        if (oper_index == 0) 
        {
            question_operaters[i]='+';
            question_answers[i] = question_paras[i][0] + question_paras[i][1];
        }
        else if(oper_index == 1) 
        {
            question_operaters[i]='-';
            question_answers[i] = question_paras[i][0] - question_paras[i][1];
        }
        else if(oper_index == 2 and question_paras[i][1] != 0) 
        {
            question_operaters[i]='/';
            question_answers[i] = round((float(question_paras[i][0]) / float(question_paras[i][1]))*100)/100.0;
        }
        else 
        {
            question_operaters[i]='*';
            question_answers[i] = question_paras[i][0] * question_paras[i][1];
        }
        
    } 
}

int main()
{
    int correct = 0;
    get_bound();
    generate_questions();
    cout<<"Keep TWO decimal places, if the answer is NOT an integer"<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<question_paras[i][0]<<question_operaters[i]<<question_paras[i][1]<<'=';
        cin>>user_answers[i];

        if (user_answers[i] == question_answers[i])
        {
            correct_record[i] = true;
            correct ++;
        }
        else correct_record[i] = false;
    }
    cout<<"Correct Answer Number: "<< correct <<endl;
    cout<<"Wrong Answer Number: "<< N - correct <<endl;
    
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

}
