#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<string> readLinesFromFile(const string &filePath)
{
    // 这里复用上次作业提供的文件读取函数
	fstream fs(filePath, fstream::in);
	if (!fs.is_open())
	{
		cout << "Cant open File\n";
	}
	else
	{
		vector<string> ret;
		string oneLine;
		while (getline(fs, oneLine))
		{
			// compitiability with Linux and Windows, windows may end line with \r\n
			if (oneLine.size() && oneLine.back() == '\r')
				oneLine.pop_back();
			ret.push_back(oneLine);
		}
		return ret;
	}
	return {};
}

int main(int argc, char *argv[])
{
	string CodebookPath, InputFilePath, OutputFilePath;
	vector<string> CodebookContent, InputFileContent, OutputFileContent;
    vector<char> codebookwords, inputwords, outputwords;

    string numberbase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	CodebookPath = argv[1];
    InputFilePath = argv[2];
    OutputFilePath = argv[3];

    CodebookContent = readLinesFromFile(CodebookPath);
	InputFileContent = readLinesFromFile(InputFilePath);

	for(const auto& lines:CodebookContent)
	{
        int j = 0;
        while(j <= lines.size())
        {
            codebookwords.push_back(lines[j]);
            j++;
        }
    }

    cout << ">>> Input is: " << endl;
	for(const auto& lines:InputFileContent)
	{
        int j = 0;
        while(j <= lines.size())
        {
            inputwords.push_back(lines[j]);
            cout << lines[j];
            j++;
        }
        inputwords.push_back('\n');
        cout << '\n';
    }

	for(const auto& lines:OutputFileContent)
	{
        int j = 0;
        while(j <= lines.size())
        {
            outputwords.push_back(lines[j]);
            j++;
        }
    }

    ofstream outFile(OutputFilePath); // 输出流 


    cout << ">>> Output is:" << endl; 
    int flag_find = 0;
    for(int ii = 0; ii <= inputwords.size()-3; ii++)
    {   
        flag_find = 0;
        // cout << "ii: " << ii << endl;
        for(int jj = 0; jj < numberbase.size(); jj++)
        {
            // cout << "jj: " << jj << endl;
            if((numberbase[jj] == char(inputwords[ii]) && isalpha(char(inputwords[ii] + 32)) && isalpha(inputwords[ii])) //输入是大写字母
                && flag_find == 0)
            {
                if(islower(codebookwords[jj]))
                {
                    outputwords.push_back(char(codebookwords[jj]-32));
                    cout << char(codebookwords[jj]-32);
                    outFile << char(codebookwords[jj]-32);
                }else
                {
                    outputwords.push_back(codebookwords[jj]);
                    cout << codebookwords[jj] ;
                    outFile << char(codebookwords[jj]);
                }
                flag_find = 1;
                break;
            }else if((char(numberbase[jj]+32) == char(inputwords[ii]) && isalpha(char(inputwords[ii] - 32)) && isalpha(inputwords[ii]))
                && flag_find == 0) 
            {
                if(islower(codebookwords[jj]))
                {
                    outputwords.push_back(codebookwords[jj]);
                    cout << codebookwords[jj];
                    outFile << char(codebookwords[jj]);
                }else
                {
                    outputwords.push_back(char(codebookwords[jj]-32));
                    cout << char(codebookwords[jj]-32);
                    outFile << char(codebookwords[jj]-32);
                }
                flag_find = 1;
                break;
            }
        }
        if(flag_find == 0)
        {
            outputwords.push_back(inputwords[ii]);
            cout << inputwords[ii];
            outFile << char(inputwords[ii]);
        }
    }
    outFile.close();
    cout << endl;




    
}
