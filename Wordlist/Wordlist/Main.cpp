#include <iostream>
#include <fstream>
using namespace std;

string toUppercase(string in);
string toLowercase(string in);


int main()
{
	//Variables
	string input, inFile, outFile, miscRules;
	ifstream inputFile;	fstream newFile;
	bool allUpper=false, allLower=false, multiples = false;
	int letterCountMin=0, letterCountMax=0, lineCount = 0;

	cout << "Input file name: ";
	cin >> inFile;

	cout << "Output file name: ";
	cin >> outFile;

	cout << "Minimum number of letters (>= 1): ";
	cin >> letterCountMin;
	if (letterCountMin <= 0) { letterCountMin = 1; }

	cout << "Maximum number of letters (>= 1): ";
	cin >> letterCountMax;
	if (letterCountMax <= 0) { letterCountMax = 1; }

	cout << "Additional rules ([N]one; [U]ppercase; [L]owercase; [E]xclude multiple letters): ";
	cin >> input;
	miscRules = toUppercase(input);

	for (int i = 0; i < miscRules.length(); i++)
	{
		switch (miscRules[i])
		{
		case 'U':
			allUpper = true;
			allLower = false;
			continue;
		case 'L':
			allLower = true;
			allUpper = false;
			continue;
		case 'E':
			multiples = true;
			continue;
		default:
			continue;
		}
	}

	inputFile.open(inFile);
	newFile.open(outFile, fstream::out);
	cout << "Opening File" << endl;
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			inputFile >> input;
			if (input.length() >= letterCountMin && input.length() <= letterCountMax)
			{
				int letterCount = 0;
				bool canWrite = true;
				if (multiples)
				{
					string temp = input;
					for (int x = 0; x < input.length(); x++)
					{
						letterCount = 0;
						for (int y = 0; y < temp.length(); y++)
						{
							if (input[x] == temp[y] && letterCount < 2)
							{
								letterCount++;
							}
						}
						if (letterCount > 1)
						{
							canWrite = false;
							break;
						}

					}
				}

				if (canWrite)
				{
					if (allUpper)
					{
						cout << "Writing: " << input << endl;
						newFile << toUppercase(input) << "\n";
					}
					else if (allLower)
					{
						cout << "Writing: " << input << endl;
						newFile << toLowercase(input) << "\n";
					}
					else
					{
						cout << "Writing: " << input << endl;
						newFile << input << "\n";
					}
				}
			}
		}
		cout << "Finished writing file." << endl;
		inputFile.close();
		newFile.close();

	}
	else
	{
		cout << "File not found!" << endl;
		newFile.close();
	}

	return 0;
}

string modifyString(string in, int mode)
{
	string out = "";
	switch (mode)
	{
	case 0://Uppercase
		for (int i = 0; i < in.length(); i++)
		{
			if (in.at(i) >= 97 && in.at(i) <= 122)
			{
				out += (in.at(i) - 32);
			}
			else if (in.at(i) >= 65 && in.at(i) <= 90)
			{
				out += (in.at(i));
			}
			else return "ERROR - Check there are no special characters";
		}
		break;
	case 1://Lowercase
		for (int i = 0; i < in.length(); i++)
		{
			if (in.at(i) >= 97 && in.at(i) <= 122)
			{
				out += (in.at(i));
			}
			else if (in.at(i) >= 65 && in.at(i) <= 90)
			{
				out += (in.at(i) + 32);
			}
			else return "ERROR - Check there are no special characters";
		}
		break;
	}
	return out;
}
string toUppercase(string in)
{
	return modifyString(in, 0);
}

string toLowercase(string in)
{
	return modifyString(in, 1);
}