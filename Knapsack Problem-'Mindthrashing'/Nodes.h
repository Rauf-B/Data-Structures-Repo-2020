#include <string>
using namespace std;
template <class T>
class Node {
private:
	string m_TaskName;
	int m_Time;
	int m_StageNo;
	int m_Points;
	Node<T>* m_NextPtr;
public:
	Node();
	Node(string, int, int, int);
	string GetTaskName();
	int GetTaskTime();
	int GetTaskStageNumber();
	int GetPoints();
	Node<T>* GetNext();
	void SetNext(Node<T>*);
	void SetTaskName(T);
	void SetTaskTime(int);
	void SetTaskStageNumber(int);
};

template <class T> Node<T>::Node() {
	m_TaskName = "null";
	m_Time = -999;
	m_StageNo = -99;
	m_NextPtr = nullptr;
	m_Points = -99;
}

template <class T> Node<T>::Node(string taskName, int time, int stageno, int points) {
	m_TaskName = taskName;
	m_Time = time;
	m_StageNo = stageno;
	m_NextPtr = nullptr;
	m_Points = points;
}

template <class T> string Node<T>::GetTaskName() { return m_TaskName; }
template <class T> int Node<T>::GetTaskTime() { return m_Time; }
template <class T> int Node<T>::GetTaskStageNumber() { return m_StageNo; }
template <class T> int Node<T>::GetPoints() { return m_Points; }
template <class T> Node<T>* Node<T>::GetNext() { return m_NextPtr; }
template <class T> void Node<T>::SetNext(Node<T>* tempPtr) { m_NextPtr = tempPtr; }



