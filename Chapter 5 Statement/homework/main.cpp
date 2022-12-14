#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
	// your program continues here....
	
	
	return 0;
}

