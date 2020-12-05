#include "SearchEngine.h"
int main() {
	SearchEngine<string> engine;
	engine.LoadDataFromFile();
	//engine1.DisplayDocInfo();
	char* query = new char[99999];
	char* tempQuery = new char[999];
	int i = 0, j = 0;
	int count = 0;
	cout << "Please enter -99 to END the program after a search. Or enter any additional query to continue execution.\n";
	cin.getline(query, 99999);
	//Building the menu here.
	while (query != "-99") {
		if (count > 0) {
			cout << "Please enter -99 to END the program after a search. Or enter any additional query to continue execution.\n";
			cin.getline(query, 99999);
		}
		while (query[i] != '\0') {
			if (query[i] != ' ') {
				tempQuery[j] = query[i];
				j++;
			}
			if (query[i + 1] == ' ' || query[i + 1] == '\0') {
				//basically just save tempQuery at this point.
				tempQuery[j] = '\0';
				string temp = tempQuery;
				cout << temp << endl;
				delete[]tempQuery;
				tempQuery = nullptr;
				tempQuery = new char[999];
				j = 0;
			}
			i++;
		}
	}
}