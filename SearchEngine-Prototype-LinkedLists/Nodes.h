template <class T>
class Doc_Info {
private:
	Doc_Info<T>* next;
	Doc_Info<T>* prev;
	T data;
	T termFreq;

public:
	Doc_Info();
	Doc_Info<T>* GetNext();
	Doc_Info<T>* GetPrev();
	T GetData();
	T GetTermFrequency();
	void SetNext(Doc_Info<T>*);
	void SetPrev(Doc_Info<T>*);
	void SetData(T);
	void SetTermFrequency(T);
};

template <class T> Doc_Info<T>::Doc_Info() {
	next = nullptr;
	prev = nullptr;
	data = " ";
	termFreq = -99;
}
template <class T> Doc_Info<T>* Doc_Info<T>::GetNext() { return next; }
template <class T> Doc_Info<T>* Doc_Info<T>::GetPrev() { return prev; }
template <class T> T Doc_Info<T>::GetData() { return data; }
template <class T> T Doc_Info<T>::GetTermFrequency() { return termFreq; }
template <class T> void Doc_Info<T>::SetNext(Doc_Info<T>* next) { this->next = next; }
template <class T> void Doc_Info<T>::SetPrev(Doc_Info<T>* prev) { this->prev = prev; }
template <class T> void Doc_Info<T>::SetData(T data) { this->data = data; }
template <class T> void Doc_Info<T>::SetTermFrequency(T termFreq) { this->termFreq = termFreq; }


template <class T>
class Term_Info {
private:
	Term_Info<T>* next;
	Term_Info<T>* prev;
	Doc_Info<T>* ToDoc;
	T data;
public:
	Term_Info();
	Term_Info<T>* GetNext();
	Term_Info<T>* GetPrev();
	T GetData();
	Doc_Info<T>* GetToDoc();
	void SetNext(Term_Info<T>*);
	void SetPrev(Term_Info<T>*);
	void SetData(T);
	void SetToDoc(Doc_Info<T>*);

};

template <class T> Term_Info<T>::Term_Info() {
	next = nullptr;
	prev = nullptr;
	data = " ";
}
template <class T> Term_Info<T>* Term_Info<T>::GetNext() { return next; }
template <class T> Term_Info<T>* Term_Info<T>::GetPrev() { return prev; }
template <class T> T Term_Info<T>::GetData() { return data; }
template <class T> Doc_Info<T>* Term_Info<T>::GetToDoc() { return ToDoc; }
template <class T> void Term_Info<T>::SetNext(Term_Info<T>* next) { this->next = next; }
template <class T> void Term_Info<T>::SetPrev(Term_Info<T>* prev) { this->prev = prev; }
template <class T> void Term_Info<T>::SetData(T data) { this->data = data; }
template <class T> void Term_Info<T>::SetToDoc(Doc_Info<T>* ToDoc) { this->ToDoc = ToDoc; }