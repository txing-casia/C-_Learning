#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

std::string numberbase="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::vector<std::string> readLinesFromFile(const std::string &filePath)
{
	std::fstream fs(filePath, std::fstream::in);
	if (!fs.is_open())
	{
		std::cout << "Cant open File\n";
	}
	else
	{
		std::vector<std::string> ret;
		std::string oneLine;
		while (std::getline(fs, oneLine))
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


// void ConvertT2N(int number,int n)
// {
//     stack<char> s;
//     if (number == 0) {  //特殊情况，当输入是0时，输出也是0，否则输入0时就卡那了
//         s.push(0);
//     } else {
//         while (number) {
//             s.push(number % n);
//             number /= n;
//         }
//     }
//     // 把栈中的余数输出
//     while (!s.empty()) {
//         printf("%d", s.top());
//         s.pop();
//     }
// }
int find_index(char N)
{
	/*查找字符 N 在 numberbase 中对应的序号*/
	int i = 0;
	while(i < numberbase.size())
	{
		if (numberbase[i] == N)
			break;
		// std::cout<<"numberbase[i]: "<<numberbase[i]<<std::endl;
		// std::cout<<"N: "<<N<<std::endl;
		i++;
	}
	return i;
}

std::vector<char> addition(std::vector<char> A, std::vector<char> B, int inputBase)
{
	/*加法运算*/
	int size_A = A.size();
	int size_B = B.size();
	int i_A = size_A - 2;
	int i_B = size_B - 2;
	int temp = 0;
	std::string res=""; //存储结果
	std::vector<char> output;

	std::cout<<size_A<<' '<<size_B;
	while (i_A >= 0 || i_B >= 0)
	{	
		if (i_A >= 0)
		{
			temp += find_index(A[i_A]);
			std::cout<<"A: "<<find_index(A[i_A])<<' '<<temp<<std::endl;
			i_A--;
		}
		if (i_B >= 0)
		{
			temp += find_index(B[i_B]);
			std::cout<<"B: "<<find_index(B[i_B])<<' '<<temp<<std::endl;
			i_B--;
		}
		res = numberbase[temp % inputBase] + res;
		temp /= inputBase;
		std::cout<<"res: "<<res<<std::endl;
	}
	
	for (int j = 0; j < res.length(); j++)
	{
		output.push_back(res[j]);
		// std::cout<<"res[j]: "<<res[j]<<' ';
	}
	return output;
}



int main(int argc, char *argv[])
{

	// only for demonstration
	// an example of running command could be : main input.txt 10 16
	std::cout << "Argument Number: " << argc << "\n"
			  << "They are: ";
	for (auto i = 0; i < argc; i++)
	{
		std::cout << argv[i] << " ";
	}
	std::cout << "\n";
	if (argc < 2 || argc > 4)
	{
		std::cout << "Not enough arguments!\n";
		std::cout << "Usage: Project2 inputFilename inputBase outputBase\n Example: Project2 testinput.txt 10 3\n";
		return -1;
	}
	std::string inputFilePath, result;
	std::vector<std::string> fileContent;
	int inputBase = 10;
	int outputBase = 10;

	inputFilePath = argv[1];
	if (argc > 2)
		inputBase = std::stoi(argv[2]);
	if (argc > 3)
		outputBase=std::stoi(argv[3]);

	fileContent=readLinesFromFile(inputFilePath);
	std::cout<< "InputBase "<<inputBase<<" OutputBase "<<outputBase<<'\n';
	std::cout<< "Data In original file:\n";
	
	for (const auto& lines:fileContent)
	{
		std::cout<<lines<<'\n';
	}
	////////////////////////////////////
	// your program continues here....
	////////////////////////////////////

	std::vector<char> A;
	std::vector<char> B;
	std::vector<char> results;
	int sign_A = 0, sign_B = 0; // A和B的符号，0：+； 1：-
	
	int i = 0;
	// 数据导入
	for (const auto& lines:fileContent)
	{
		if (i == 0)
		{	
			int j = 0;
			while ( j <= lines.size())
			{
				A.push_back(lines[j]);
				j++;
			}
		}else if (i == 1)
		{	
			int j = 0;
			while ( j <= lines.size())
			{
				B.push_back(lines[j]);
				j++;
			}
		}
		i++;
	}

	// 判断数据A的符号
	if (A[0] == '+')
	{
		sign_A = 0;
		A.erase(A.begin());
	}else if (A[0] == '-')
	{
		sign_A = 1;
		A.erase(A.begin());
	}

	// 判断数据B的符号
	if (B[0] == '+')
	{
		sign_B = 0;
		B.erase(B.begin());
	}else if (B[0] == '-')
	{
		sign_B = 1;
		B.erase(B.begin());
	}


	// while(i)
	// {
	// 	A[i] = conversion(lines);
	// 	i++;
	// }
	if (sign_A == 0 && sign_B == 0)
	{
		results = addition(A, B, inputBase);
	}else if ((sign_A == 1 && sign_B == 0) || (sign_A == 0 && sign_B == 1))
	{
		results = addition(A, B, inputBase);
	}else if (sign_A == 1 && sign_B == 1)
	{
		results = addition(A, B, inputBase);
	}
	
	// std::cout<<results.size()<<std::endl;
	// for (auto ii = results.begin(); ii != results.end(); ii++) 
	// {
	// 	std::cout << *ii << ' ';
	// }

	return 0;
}

