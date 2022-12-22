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



// std::string convertoutputbase(std::string res, int outputbase)
// {
// 	int i = res.length()-1; 
// 	std::string ans="";
// 	do {
// 		temp += find_index(res[i]);
// 		num = res[];
// 		ans = numberbase[num % outputbase] + ans;
		
// 		num /= 26;
// 	} while(num);
// 	return ans;
// }


int find_index(char N)
{
	/*查找字符 N 在 numberbase 中对应的序号*/
	int i = 0;
	while(i < numberbase.size())
	{
		if (numberbase[i] == N // 输入是数字
			|| (numberbase[i] == char(N + 32) && isalpha(char(N + 32)) && isalpha(N)) //输入是大写字母
			|| (numberbase[i] == char(N - 32) && isalpha(char(N - 32)) && isalpha(N))) //输入是小写字母
			// std::cout<<"numberbase[i]: "<<numberbase[i]<<std::endl;
			// std::cout<<"char(N + 32): "<<char(N + 32)<<std::endl;
			// std::cout<<"N: "<<N<<std::endl;
			break;
		// std::cout<<"numberbase[i]: "<<numberbase[i]<<std::endl;
		// std::cout<<"N: "<<N<<std::endl;
		// std::cout<<"N: "<<char(N-32)<<std::endl;
		i++;
	}
	return i;
}

int find_bigger(std::vector<char> A, std::vector<char> B)
{
	int size_A = A.size();
	int size_B = B.size();
	int i_A = 0;
	int i_B = 0;
	if (size_A > size_B)
		return 0;
	else if (size_A < size_B)
		return 1;
	else if (size_A == size_B)
	{
		while (i_A <= size_A - 2)
		{
			if (A.at(i_A) > B.at(i_B))
				return 0;
			else if (A.at(i_A) < B.at(i_B))
				return 1;
			else if ((A.at(i_A) == B.at(i_B)) && (i_A != size_A - 2))
				i_A++;
			else if (i_A >= size_A - 2)
				return 0;
		}
	}

}

std::string covert_M2N(int M, int N, std::string str)
{
	int currentnum = 0;//当前位
	int mod = 0;//余数
	std::string quotient = str;//商串
	std::string result = "";//存放转换后的结果串
	std::string temp_quotient = "";//存放中间商串
	while(quotient.length() > 0)
	{
		temp_quotient = "";
		mod = 0;
		for(int i = 0; i < quotient.length(); i++)//该循环即从字符串的最高位开始做除法，具体参照整数除法的过程
		{
			currentnum = find_index(quotient[i]);
			if(currentnum == -1)
				return "Error,invilade";
			mod = mod * M + currentnum;
			temp_quotient += numberbase[mod / N];//存每一位上的商
			mod = mod % N;
		}
		result = numberbase[mod] + result;//将余数放入结果；
		int i = 0;
		quotient = temp_quotient;
		for(; i < quotient.length(); i++)
		{//去掉商前面的0
			if(quotient[i] != '0')
				break;
		}
		quotient = quotient.erase(0, i);
	}
	return result;
}

std::vector<char> addition(std::vector<char> A, std::vector<char> B, int inputBase, int outputBase)
{
	/*加法运算*/
	int size_A = A.size();
	int size_B = B.size();
	int i_A = size_A - 2;
	int i_B = size_B - 2;
	int temp = 0;
	std::string res=""; //存储结果
	std::vector<char> output;

	// std::cout<<size_A<<' '<<size_B;
	while (i_A >= 0 || i_B >= 0)
	{	
		if (i_A >= 0)
		{
			temp += find_index(A[i_A]);
			// std::cout<<"A: "<<find_index(A[i_A])<<' '<<temp<<std::endl;
			i_A--;
		}
		if (i_B >= 0)
		{
			temp += find_index(B[i_B]);
			// std::cout<<"B: "<<find_index(B[i_B])<<' '<<temp<<std::endl;
			i_B--;
		}
		res = numberbase[temp % inputBase] + res;
		temp /= inputBase;
		// std::cout<<"res: "<<temp<<std::endl;
	}
	res = numberbase[temp % inputBase] + res; // 最高位以上有进位
	res = covert_M2N(inputBase, outputBase, res);
	
	for (int j = 0; j < res.length(); j++)
	{
		output.push_back(res[j]);
		// std::cout<<"res[j]: "<<res[j]<<' ';
	}

	// for (int j = 0; j < res.length(); j++)
	// {	
	// 	if ((j == 0) && (res[j] == '0'))
	// 		continue;
	// 	output.push_back(res[j]);
	// 	// std::cout<<"res[j]: "<<res[j]<<' ';
	// }
	// std::cout<<"output.size()"<<output.size()<<std::endl;
	if (output.size() == 0)
		output.push_back('0');

	return output;
}

std::vector<char> subtraction(std::vector<char> A, std::vector<char> B, int sign_A, int sign_B, int inputBase, int outputBase)
{
	/*加法运算*/
	int size_A = A.size();
	int size_B = B.size();
	int i_A = size_A - 2;
	int i_B = size_B - 2;
	int temp = 0;
	int flag_bigger = 0;
	std::string res=""; //存储结果
	std::vector<char> output;
	flag_bigger = find_bigger(A,B);

	// std::cout<<i_A<<' '<<i_B<<std::endl;

	if (sign_A == 0 && sign_B == 1) // A:+, B:-
	{
		if (flag_bigger == 0) // |A| >= |B|
		{
			while (i_A >= 0 || i_B >= 0)
			{	
				if (i_A >= 0)
				{
					temp += find_index(A[i_A]);
					i_A--;
				}
				if (i_B >= 0)
				{
					temp -= find_index(B[i_B]);
					i_B--;
				}

				if (temp < 0) // 向上借1
				{
					res = numberbase[inputBase + temp] + res;
					temp = -1;
					// std::cout<<"res: "<<res<<std::endl;
				}else
				{
					res = numberbase[temp % inputBase] + res;
					temp /= inputBase;
					// std::cout<<"res: "<<res<<std::endl;
				}
			}
			// std::cout<<"res1: "<<res<<std::endl;
			res = numberbase[temp % inputBase] + res; // 最高位以上有进位

			res = covert_M2N(inputBase, outputBase, res);
			// std::cout<<"res2: "<<res<<std::endl;
		}
		else if (flag_bigger == 1) // |A| < |B|
		{
			while (i_A >= 0 || i_B >= 0)
			{	
				if (i_A >= 0)
				{
					// std::cout<<"A[i_A]: "<<A[i_A]<<' '<<i_A<<std::endl;
					temp -= find_index(A[i_A]);
					// std::cout<<"temp: "<<temp<<std::endl;
					i_A--;
				}
				if (i_B >= 0)
				{	
					temp += find_index(B[i_B]);
					// std::cout<<"B[i_B]: "<<B[i_B]<<' '<<i_B<<std::endl;
					// std::cout<<"temp: "<<temp<<std::endl;
					i_B--;
				}

				if (temp < 0) // 向上借1
				{
					res = numberbase[inputBase + temp] + res;
					temp = -1;
					// std::cout<<"res: "<<res<<std::endl;
				}else
				{
					
					res = numberbase[temp % inputBase] + res;
					temp /= inputBase;
					// std::cout<<"res: "<<res<<std::endl;
				}
			}
			// std::cout<<"res3: "<<res<<std::endl;
			res = numberbase[temp % inputBase] + res; // 最高位以上有进位

			res = covert_M2N(inputBase, outputBase, res);
			// std::cout<<"res4: "<<res<<std::endl;
			res = '-' + res;
		}
	}else // A:-, B:+
	{
		if (flag_bigger == 0) // |A| >= |B|
		{
			while (i_A >= 0 || i_B >= 0)
			{	
				if (i_A >= 0)
				{
					temp += find_index(A[i_A]);
					i_A--;
				}
				if (i_B >= 0)
				{
					temp -= find_index(B[i_B]);
					i_B--;
				}

				if (temp < 0) // 向上借1
				{
					res = numberbase[inputBase + temp] + res;
					temp = -1;
					// std::cout<<"res: "<<res<<std::endl;
				}else
				{
					res = numberbase[temp % inputBase] + res;
					temp /= inputBase;
					// std::cout<<"res: "<<res<<std::endl;
				}
			}
			// std::cout<<"res5: "<<res<<std::endl;
			res = numberbase[temp % inputBase] + res; // 最高位以上有进位
			
			res = covert_M2N(inputBase, outputBase, res);
			// std::cout<<"res6: "<<res<<std::endl;
			res = '-' + res;
		}
		else if (flag_bigger == 1) // |A| < |B|
		{
			while (i_A >= 0 || i_B >= 0)
			{	
				if (i_A >= 0)
				{
					temp -= find_index(A[i_A]);
					i_A--;
				}
				if (i_B >= 0)
				{
					temp += find_index(B[i_B]);
					i_B--;
				}

				if (temp < 0) // 向上借1
				{
					res = numberbase[inputBase + temp] + res;
					temp = -1;
					// std::cout<<"res: "<<res<<std::endl;
				}else
				{
					res = numberbase[temp % inputBase] + res;
					temp /= inputBase;
					// std::cout<<"res: "<<res<<std::endl;
				}
			}
			res = numberbase[temp % inputBase] + res; // 最高位以上有进位
	
			// std::cout<<"res7: "<<res<<std::endl;
			res = covert_M2N(inputBase, outputBase, res);
			// std::cout<<"res8: "<<res<<std::endl;
		}
	}
	
	
	for (int j = 0; j < res.length(); j++)
	{	
		if ((j == 0) && (res[j] == '0'))
			continue;
		output.push_back(res[j]);
		// std::cout<<"res[j]: "<<res[j]<<' ';
	}
	// std::cout<<"output.size()"<<output.size()<<std::endl;
	if (output.size() == 0)
		output.push_back('0');
	return output;
}

std::vector<char> addition_negative(std::vector<char> A, std::vector<char> B, int inputBase, int outputBase)
{
	/*加法运算*/
	int size_A = A.size();
	int size_B = B.size();
	int i_A = size_A - 2;
	int i_B = size_B - 2;
	int temp = 0;
	std::string res=""; //存储结果
	std::vector<char> output;

	// std::cout<<size_A<<' '<<size_B<<std::endl;
	while (i_A >= 0 || i_B >= 0)
	{	
		if (i_A >= 0)
		{
			temp += find_index(A[i_A]);
			// std::cout<<"A[i_A]: "<<A[i_A]<<' '<<temp<<std::endl;
			i_A--;
		}
		if (i_B >= 0)
		{	
			temp += find_index(B[i_B]);
			// std::cout<<"temp: "<<temp<<std::endl;
			i_B--;
		}
		res = numberbase[temp % inputBase] + res;
		temp /= inputBase;
		// std::cout<<"res: "<<res<<std::endl;
	}
	res = numberbase[temp % inputBase] + res; // 最高位以上有进位
	res = covert_M2N(inputBase, outputBase, res);
	res = '-' + res;

	// for (int j = 0; j < res.length(); j++)
	// {
	// 	output.push_back(res[j]);
	// }

	for (int j = 0; j < res.length(); j++)
	{	
		if ((j == 0) && (res[j] == '0'))
			continue;
		output.push_back(res[j]);
		// std::cout<<"res[j]: "<<res[j]<<' ';
	}

	// std::cout<<"output.size()"<<output.size()<<std::endl;
	if (output.size() == 0)
		output.push_back('0');

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
		outputBase = inputBase;
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

	//去除A前置的0
	int zero_flag = 0;
	while (zero_flag == 0)
	{
		if (A[0] == '0')
			A.erase(A.begin());
		else if (A.empty() || A[0] != '0')
			zero_flag = 1;
	}

	//去除B前置的0
	zero_flag = 0;
	while (zero_flag == 0)
	{
		if (B[0] == '0')
			B.erase(B.begin());
		else if (B.empty() || B[0] != '0')
			zero_flag = 1;
	}

	if (sign_A == 0 && sign_B == 0)
	{
		std::cout<<"addition"<<std::endl;
		results = addition(A, B, inputBase, outputBase);
	}else if ((sign_A == 1 && sign_B == 0) || (sign_A == 0 && sign_B == 1))
	{
		std::cout<<"subtraction"<<std::endl;
		results = subtraction(A, B, sign_A, sign_B, inputBase, outputBase);
	}else if (sign_A == 1 && sign_B == 1)
	{
		std::cout<<"addition_negative"<<std::endl;
		results = addition_negative(A, B, inputBase, outputBase);
	}
	
	std::cout<<"Result: ";
	for (auto num = results.begin(); num != results.end(); num++) 
	{
		std::cout << *num;
	}
	std::cout<<std::endl;
	return 0;
}

