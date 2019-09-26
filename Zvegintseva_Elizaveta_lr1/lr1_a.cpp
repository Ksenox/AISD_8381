#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int opening_bracket = 0;
int closing_bracket = 0;

int rec(string& str, ofstream& output)
{

	while (str.size())
	{
		//output << str << endl;
		cout << str << endl;
		cout << opening_bracket << endl;
		cout << closing_bracket << endl;

		if (((str[0] >= 97 && str[0] <= 122) || (str[0] >= 65 && str[0] <= 90)) && (str.size() == 1))
			return 0;

		if (str[0] == '(')
		{
			opening_bracket++;
			str = str.substr(1, str.size() - 1);
			int k = rec(str, output);
			str = str.substr(k, str.size() - k);
			if (str[0] == ')')
				continue;
			if (str[0] == '\0')
				return 0;
			if ((str[0] == '-' || str[0] == '*' || str[0] == '+') && ((str[1] >= 97 && str[1] <= 122) || str[1] == '(' || (str[0] >= 65 && str[0] <= 90)))
			{
				if (str[1] == '(')
					opening_bracket++;
				str = str.substr(2, str.size() - 2);
				continue;
			}

			if (str[0] != '*' && str[0] != '+' && str[0] != '-')
			{

				output << "Error1" << endl;
				cout << "Error1" << endl;
				exit(0);
			}

		}
		else
		{

			if (str[0] == ')')
			{
				if (str[1] >= 97 && str[1])
				{
					output << "Error2" << endl;
					cout << "Error2" << endl;
					exit(0);
				}

				closing_bracket++;
				str = str.substr(1, str.size() - 1);

				if ((str[0] == '-' || str[0] == '*' || str[0] == '+') && ((str[1] >= 97 && str[1] <= 122) || str[1] == '(' || (str[0] >= 65 && str[0] <= 90)))
				{
					if (str[1] == '(')
						opening_bracket++;
					str = str.substr(2, str.size() - 2);
					continue;
				}
				continue;
			}
			if ((str[0] >= 97 && str[0] <= 122) || (str[0] >= 65 && str[0] <= 90)) {
				if (str[1] == '*' || str[1] == '+' || str[1] == '-') {
					if ((str[2] >= 97 && str[2] <= 122) || (str[2] >= 65 && str[2] <= 90))
						return 3;
					else {
						str = str.substr(2, str.size() - 2);
						continue;
					}
				}
				else
					return 1;
			}
			output << "Error3" << endl;
			cout << "Error3" << endl;
			//output << str << endl;
			cout << str << endl;
			exit(0);

		}
	}


	return 0;
}

int main() {
	{

		ofstream output("/Users/Elizaveta/source/repos/lr1/output.txt");
		string com, str;

		cout << R"(Would u like to get input from "input.txt"? Y/N)" << endl;
		cin >> com;

		if (com[0] == 'Y') {
			cout << R"(Searching for it...)" << endl;
			ifstream input("input.txt", ifstream::in);
			if (input.fail()) {
				cout << "File is not certain." << endl;
				return 0;
			}
			getline(input, str);
		}
		else if (com[0] == 'N') {
			cout << R"(Then type the string!)" << endl;
			cin >> str;
		}
		else {
			cout << "Try once again..." << endl;
			return 0;
		}

		output << str << endl;
		cout << str << endl;
		rec(str, output);

		if (opening_bracket == closing_bracket) {
			output << "Correct" << endl;
			cout << "Correct" << endl;
		}
		else {
			output << "Invalid brackets" << endl;
			cout << "Invalid brackets" << endl;
		}
		return 0;
	}
}
