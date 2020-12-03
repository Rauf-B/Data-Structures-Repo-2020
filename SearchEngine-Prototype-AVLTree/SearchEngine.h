#include <fstream>
#include "Header.h"

class Search_Engine {
private:
	AVLTree tree;
public:
	Search_Engine();
	void Create_Index();
	void Add_Doc_To_Index(string);
	void Display();
	void Search(string);
	~Search_Engine() {
		tree.~AVLTree();
	}
};

Search_Engine::Search_Engine() {
	tree = AVLTree();
}

void Search_Engine::Create_Index() {
	string fileName[] = { "Doc1.txt", "Doc2.txt", "Doc3.txt", "Doc4.txt" };
	int size = 4;

	for (int i = 0; i < size; i++)
	{
		Add_Doc_To_Index(fileName[i]);
	}
}

void Search_Engine::Add_Doc_To_Index(string fileName) {
	ifstream fin;
	string* termArr = new string[99];
	int termArrSize = 0;


	fin.open(fileName);

	if (!fin) {
		cout << "ERROR: " + fileName + " could not be opened!\n";
	}
	else {
		while (!fin.eof()) {
			string temp;
			fin >> temp;
			termArr[termArrSize] = temp;
			termArrSize++;
		}
		fin.close();
		//now search for TF

		for (int i = 0; i < termArrSize; i++) {
			string temp = termArr[i];
			int termFreq = 0;
			for (int j = 0; j < termArrSize; j++) {
				if (temp == termArr[j])
					termFreq++;
			}
			tree.Search(temp, fileName, termFreq);
		}

	}
}

void Search_Engine::Display() {
	tree.Display();
}

void Search_Engine::Search(string termName) {
	tree.SearchTerm(termName);
}
