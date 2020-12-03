#include "Node.h"
#include <fstream>
template <class T>
class Stack {
private:
	Node<T>* m_StackPtr;
public:
	Stack();
	void Push(string, int, int, int); //taskName, duration, stage number, points
	void Push(Node<T>);
	Node<T> Pop();
	void DisplayStackData(); //reads stack data and then displays it
	Node<T>* GetTopPtr();
	void FindFavourableStages(int time); //finds the data through iteration
	void Find(int time); //wrapper for RFindFavourableStages
	void RFindFavourableStages(int, Node<T>*, Node<T>*, int, int, int, int, Stack<T>, Stack<T>); // one of the two stacks is used to contain the stack built for every iteration. the other is used to contain the stack that would get the data copied when new highscore is there
	void CopyStack(Stack<T> obj);
	bool IsEmpty();
	void ReadDataFromFile();
	//need to add Recursive Pop and Search
};

template <class T> Stack<T>::Stack() {
	m_StackPtr = nullptr;
}

template <class T> bool Stack<T>::IsEmpty() {
	if (m_StackPtr == nullptr)
		return true;
	else
		return false;
}

template <class T> Node<T>* Stack<T>::GetTopPtr() { return m_StackPtr; }

template <class T> void Stack<T>::CopyStack(Stack<T> stack) {
	m_StackPtr = nullptr;

	while (!stack.IsEmpty())
		Push(stack.Pop());
}

template <class T> void Stack<T>::Push(string taskName, int duration, int stage, int points) {
	Node<T>* tempPtr = new Node<T>(taskName, duration, stage, points);
	if (m_StackPtr == nullptr) {
		m_StackPtr = tempPtr;
	}
	else {
		tempPtr->SetNext(m_StackPtr);
		m_StackPtr = tempPtr;
	}
}

template <class T> void Stack<T>::Push(Node<T> temp) {
	Node<T>* tempPtr = new Node<T>(temp.GetTaskName(), temp.GetTaskTime(), temp.GetTaskStageNumber(), temp.GetPoints());
	if (m_StackPtr == nullptr) {
		m_StackPtr = tempPtr;
	}
	else {
		tempPtr->SetNext(m_StackPtr);
		m_StackPtr = tempPtr;
	}
}

template <class T> Node<T> Stack<T>::Pop() {
	Node <T> temp = *(m_StackPtr);
	m_StackPtr = m_StackPtr->GetNext();
	return temp;
}

template <class T> void Stack<T>::DisplayStackData() {
	Node<T>* ptr = m_StackPtr;

	while (ptr != nullptr) {
		cout << ptr->GetTaskStageNumber() << " " << ptr->GetTaskName() << " " << ptr->GetTaskTime() << " " << ptr->GetPoints() << endl;
		ptr = ptr->GetNext();
	}
}

template <class T> void Stack<T>::FindFavourableStages(int time) {
	/*
		temp1 is being used to point to the stage of which the possible combinations are going to be made. temp2 traverses through the rest of the stack
		and makes all possible combinations with temp1.
		temp1 being null means there is no other stage to make combinations for
		temp2 being null means that the ptr has traversed through the stack as it always starts from the m_StackPtr (top Ptr)

	*/
	//We need a total of 3 pointers. temp1, temp2, temp3.
	Node<T>* temp1 = m_StackPtr; //this is the first pointer. it points to the number youre finding groups for
	int prevScore = 0; //highest score
	Stack<string> retStoreStages; //at the end of the search. this will store in the stack the most favourable stages

	while (temp1 != nullptr) {
		int iterationScore = 0; //score for each iteration
		int tempTime = time;
		Node<T>* temp2 = m_StackPtr; //temp2 will traverse through the stack for every temp1
		Stack<string> storeStages; //stores each time a stage that matches the checks is found
		for (int i = 0; temp2 != nullptr; i++) {
			if (temp1->GetNext() == nullptr && i == 0) {
				tempTime = tempTime - temp1->GetTaskTime(); //special case correction. 
				iterationScore = iterationScore + temp1->GetPoints();
			}
			if ((tempTime - temp2->GetTaskTime()) >= 0) {
				if (!(temp1 == temp2)) {
					tempTime = tempTime - temp2->GetTaskTime();
					iterationScore = iterationScore + temp2->GetPoints();
					storeStages.Push(*(temp2));
					if (iterationScore >= prevScore) {
						prevScore = iterationScore;
						retStoreStages.CopyStack(storeStages);
					}
				}
				temp2 = temp2->GetNext();
			}
			else if ((tempTime - temp2->GetTaskTime()) < 0 && tempTime <= 0) {
				temp2 = temp2;
				iterationScore = 0;
				tempTime = time;
			}
			else if ((tempTime - temp2->GetTaskTime()) < 0 && tempTime > 0) {
				temp2 = temp2->GetNext();
			}
		}
		temp1 = temp1->GetNext();
	}
	cout << "HIGHEST POSSIBLE SCORE FOUND: " << prevScore << endl;
	cout << endl;
	cout << "FAVOURABLE TASKS TO DO:" << endl;
	retStoreStages.DisplayStackData();
}

template <class T> void Stack<T>::RFindFavourableStages(const int time, Node<T>* temp1, Node<T>* temp2, int highestScore, int tempTime, int iterationScore, int count, Stack<T> retStack, Stack<T> tempStack) {
	//base case. Exit recursive loop when there is nothing else that is left to find

	if (temp1 == nullptr) {
		cout << "Exiting recursive Find..." << endl;
		cout << "Highest score found is: " << highestScore << endl;
		cout << "Favourable Tasks to do (Recursion Find):" << endl;
		retStack.DisplayStackData();
		return;
	}

	if (temp2 == nullptr) {
		Stack<T> tempNewStack;
		return RFindFavourableStages(time, temp1->GetNext(), m_StackPtr, highestScore, time, 0, count, retStack, tempNewStack);
	}

	//cout << temp1->GetTaskName() << endl;
	//cout << temp2->GetTaskName() << endl;
	//cout << endl;

	if (temp1->GetNext() == nullptr && count == 0) {
		tempTime = tempTime - temp1->GetTaskTime(); //special case correction. 
		iterationScore = iterationScore + temp1->GetPoints();
		count++;
		tempStack.Push(*temp1);
	}
	if ((tempTime - temp2->GetTaskTime()) >= 0) { //this condition checks if the remaining time - the next stage time is greater than zero or equal to it. if so, it considers the task
		//cout << temp1->GetTaskName() << endl;
		tempTime = tempTime - temp2->GetTaskTime();
		iterationScore = iterationScore + temp2->GetPoints();
		tempStack.Push(*temp2);
		if (iterationScore >= highestScore) {
			highestScore = iterationScore;
			//cout << temp2->GetTaskName() << endl;
			//cout << endl;
			retStack.CopyStack(tempStack);
		}
		//add recursive call here
		return RFindFavourableStages(time, temp1, temp2->GetNext(), highestScore, tempTime, iterationScore, count, retStack, tempStack);
	}
	else if ((tempTime - temp2->GetTaskTime()) < 0 && tempTime <= 0) { //incase the time is less than zero. the temp2 is made to where it is at
		//add recursive call here
		return RFindFavourableStages(time, temp1, temp2, highestScore, time, 0, count, retStack, tempStack);
	}
	else if ((tempTime - temp2->GetTaskTime()) < 0 && tempTime > 0) {
		//add recursive call here
		return RFindFavourableStages(time, temp1, temp2->GetNext(), highestScore, tempTime, iterationScore, count, retStack, tempStack);
		//temp2 = temp2->GetNext();
	}
}

template <class T> void Stack<T>::Find(int time) {
	Stack<string> retStack;
	RFindFavourableStages(time, m_StackPtr, m_StackPtr, 0, time, 0, 0, retStack, retStack);
}

template <class T> void Stack<T>::ReadDataFromFile() {
	ifstream fin;
	fin.open("inputfile.txt");
	if (!fin) {
		cout << "Could not open file!\n";
	}
	else {
		while (!fin.eof()) {
			int stageno;
			string name;
			int time;
			int score;

			fin >> stageno;
			fin >> name;
			fin >> time;
			fin >> score;

			Push(name, time, stageno, score);
		}
	}
}