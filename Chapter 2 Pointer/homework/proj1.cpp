#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

int N = 10; // question num
const int N_max = 100;
int question_paras[N_max][2]; // question paras
char question_operaters[N_max]; // question operater list 
float question_answers[N_max]; // answer list of questions
float user_answers[N_max]; // user answer list of questions
bool correct_record[N_max]; // record correct question index
int bound[2]={0,0}; // para bound

bool complex_flag = true;

void get_bound(void)
{
    cout<<"Input the integral bound values a and b of [a,b):"<<endl;
    cout<<"a = ";
    cin>>bound[0];
    cout<<"b = ";
    cin>>bound[1];
}

void generate_questions()
{
    int oper_index = 0;
    srand((int)time(0)); // set random seed
    // rand()%(b-a)+a ==> [a,b)
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
        
        if (complex_flag)
        {   
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
                // Keep TWO decimal places
                question_answers[i] = round((float(question_paras[i][0]) / float(question_paras[i][1]))*100)/100.0;
            }
            else 
            {
                question_operaters[i]='*';
                question_answers[i] = question_paras[i][0] * question_paras[i][1];
            }
        }else
        {
            oper_index = rand()%2;
            if (oper_index == 0) 
            {
                question_operaters[i]='+';
                question_answers[i] = question_paras[i][0] + question_paras[i][1];
            }
            else
            {
                question_operaters[i]='-';
                question_answers[i] = question_paras[i][0] - question_paras[i][1];
            }
        }
    } 
}

int main()
{
    int correct = 0;

    cout<< "Do you want to play with Challenge Mode? (yes = 1, no = 0)"<<endl;
    cin >> complex_flag;
    
    N = 0;
    while (N <= 0)
    {
        cout<< "How many questions you want to deal with (N<100): "<<endl;
        cout<< "N = ";
        cin >> N;
        if (N <= 0)
            cout<<"Please make sure 'N > 0'"<<endl;
    }

    while (bound[0]>=bound[1])
    {
        get_bound();
        if (bound[0]>=bound[1])
            cout<<"Please make sure 'a > b'"<<endl;
    }
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
    cout<<"Your score is: "<< (correct*1.0/N)*100 <<endl;

    
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
