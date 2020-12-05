#include "Lists.h"
#include <fstream>
#include <string>
template <class T>
class SearchEngine {
private:
	TermList<T> terms;
public:
	SearchEngine();
	void LoadDataFromFile(); //this function is used to load data from the files.
	void AddToTermList(string, string); //the vertical list or the term list. This is used to add a node to the list.
	bool IsTermUnique(string, string); //Checks if a term already exists in the termList or not.
	bool IsAStopWord(string);
	bool IsASpace(string);
	void AddDocInfo(string); //Makes the initial node for a newly added term in the termList
	void DisplayDocInfo(); //Debug function. Meant to display the terms and their adjoining lists containing TF and DocIds.
	void SetInitialFrequency(); //Called only when the term being added is a new term. Sets the frequency to 1.
	void IncreaseTermFrequency(Term_Info<T>*, string); //Increases the term frequency of a term that has been found to exist already in the program.
	void DoesPathExist(Term_Info<T>*, string); //When adding new Doc_Info nodes to the term. This function checks if the "path" or the DocID already exists. If it exists, it calls IncreaseTermFrequency() func. If not, it calls the AppendDocInfo() func.
	void AppendDocInfo(Term_Info<T>* term, string path); //Appends the already existing list of Doc_Info of a term.
	void DisplaySpecificTermInfo(Term_Info<T>*); //Goes through all the adjoining Doc_Info nodes of every term. 
	void SearchTermList(string); //this function is used to search the words inputted by the user.
};

template <class T> SearchEngine<T>::SearchEngine() {
}

template <class T> bool SearchEngine<T>::IsASpace(string term) {
	bool isSpace = false;
	if (term == " ") {
		isSpace = true;
	}
	return isSpace;
}

template <class T> bool SearchEngine<T>::IsAStopWord(string term) {
	string stopWords[] = { "of", "or", "and", "if", "the" };
	bool isStop = false;
	for (int i = 0; i < 5; i++) {
		if (term == stopWords[i]) {
			isStop = true;
			break;
		}
	}
	return isStop;
}

template <class T> void SearchEngine<T>::DisplaySpecificTermInfo(Term_Info<T>* ptr) {
	Doc_Info<T>* docPtr = ptr->GetToDoc();
	cout << ptr->GetData() << " ";
	while (docPtr->GetNext() != nullptr) {
		cout << docPtr->GetData() << " " << docPtr->GetTermFrequency() << " ";
		docPtr = docPtr->GetNext();
	}
	//for the one node that might get missed due to this check.
	cout << docPtr->GetData() << " " << docPtr->GetTermFrequency() << " ";
	cout << endl;
}

template <class T> void SearchEngine<T>::AppendDocInfo(Term_Info<T>* term, string path) {
	Doc_Info<T>* tempToDoc = term->GetToDoc();
	while (tempToDoc->GetNext() != nullptr) {
		tempToDoc = tempToDoc->GetNext();
	}
	Doc_Info<T>* newTemp = new Doc_Info<T>();
	newTemp->SetData(path);
	string freq = "" + to_string(1);
	newTemp->SetTermFrequency(freq);
	tempToDoc->SetNext(newTemp);
	newTemp->SetPrev(tempToDoc);
}


template <class T> void SearchEngine<T>::DoesPathExist(Term_Info<T>* term, string path) {
	Doc_Info<T>* tempToDoc = term->GetToDoc();
	bool isFound = false;
	if (tempToDoc != nullptr) {
		while (tempToDoc->GetNext() != nullptr) {
			if (tempToDoc->GetData() == path) {
				isFound = true;
				break;
			}
			tempToDoc = tempToDoc->GetNext();
		}
	}
	//second check as the loop above leaves one node out of the search
	if (!isFound) {
		if (tempToDoc->GetData() == path)
			isFound = true;
	}

	if (isFound)
		IncreaseTermFrequency(term, path);
	else
		AppendDocInfo(term, path);
}

template <class T> void SearchEngine<T>::IncreaseTermFrequency(Term_Info<T>* tempPtr, string path) {
	Doc_Info<T>* ptr = tempPtr->GetToDoc();
	bool isFound = false;
	if (tempPtr->GetToDoc() != nullptr) {
		while (ptr->GetNext() != nullptr) {
			if (ptr->GetData() == path) {
				isFound = true;
				break;
			}
		}
	}
	//second check as the loop above leaves one node out of the search
	if (!isFound) {
		if (ptr->GetData() == path)
			isFound = true;
	}

	if (isFound) {
		int num1 = stoi(ptr->GetTermFrequency());
		string text = "" + to_string(num1 + 1);
		ptr->SetTermFrequency(text);
	}
}

template <class T> void SearchEngine<T>::SetInitialFrequency() {
	string term = "" + to_string(1);
	terms.GetTail()->GetToDoc()->SetTermFrequency(term);
}

template <class T> bool SearchEngine<T>::IsTermUnique(string term, string path) {
	if ((terms.GetHead() == nullptr || terms.GetTail() == nullptr))
		return false;
	bool isFound = false;
	Term_Info<T>* tempNode = new Term_Info<T>();
	tempNode = terms.GetHead();

	while (tempNode->GetNext() != nullptr) {
		if (tempNode->GetData() == term) {
			isFound = true;
			break;
		}
		tempNode = tempNode->GetNext();
	}
	if (!isFound) {
		if (tempNode->GetData() == term) {
			isFound = true;
		}
	}
	//if the number is found. We will search the current path and then increase the term frequency in the list.
	if (isFound) {
		//cout << tempNode->GetData() << endl;
		DoesPathExist(tempNode, path);
	}
	return isFound;
}

template <class T> void SearchEngine<T>::AddToTermList(string term, string path) {
	Term_Info<T>* tempTerm = new Term_Info<T>();
	tempTerm->SetData(term);
	terms.AddNode(tempTerm);
	AddDocInfo(path);
	SetInitialFrequency();
}

template <class T> void SearchEngine<T>::AddDocInfo(string path) {
	Doc_Info<T>* docPtr = new Doc_Info<T>();
	docPtr->SetData(path);
	terms.GetTail()->SetToDoc(docPtr);
}

template <class T> void SearchEngine<T>::DisplayDocInfo() {
	Term_Info<T>* ptr = terms.GetHead();
	while (ptr->GetNext() != nullptr) {
		DisplaySpecificTermInfo(ptr);
		ptr = ptr->GetNext();
	}
	//for the last node that will be missed by the check:
	DisplaySpecificTermInfo(ptr);
}

template <class T> void SearchEngine<T>::LoadDataFromFile() {

	bool _isFound = false;
	string fileNames[4] = { "set1.txt", "set2.txt", "set3.txt", "set4.txt" };
	for (int i = 0; i < 4; i++) {
		if (i > 1) { break; }
		ifstream fin;
		fin.open(fileNames[i]);
		if (fin) {
			//cout << "File is open!\n";
			while (!fin.eof()) {
				string temp;
				fin >> temp;
				_isFound = IsTermUnique(temp, fileNames[i]);
				if (!_isFound) {
					AddToTermList(temp, fileNames[i]);
				}
			}
		}
		else {
			cout << "File could not be opened!\n";
		}
		//cout << "File closed!\n";
	}
	cout << endl;
}

template <class T> void SearchEngine<T>::SearchTermList(string term) {
	bool isFound = false;
	Term_Info<T>* tempNode = new Term_Info<T>();
	tempNode = terms.GetHead();

	while (tempNode->GetNext() != nullptr) {
		if (tempNode->GetData() == term) {
			isFound = true;
			break;
		}
		tempNode = tempNode->GetNext();
	}
	if (!isFound) {
		if (tempNode->GetData() == term) {
			isFound = true;
		}
	}

	if (isFound) {
		cout << "TERM FOUND! DISPLAYING INFO..." << endl;
		DisplaySpecificTermInfo(tempNode);
	}
	else {
		cout << "TERM NOT FOUND" << endl;
	}
}