#ifndef LIST
#define LIST 1

#include <iostream>
using namespace std;

template <class T>
class List
{
private:
    class _Node
    {
    public:
        T data;
        _Node *next;
        _Node *prev;
        _Node() : next(nullptr), prev(nullptr) {}
    };
    _Node *head;
    _Node *tail;
    int _size;

    typedef _Node *Node;

public:
    List();
    ~List();
    List(const List<T> &);
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void remove(int);
    void clear();
    bool isEmpty();
    int size();
    T &operator[](int);
};

template <class T>
List<T>::List() : head(nullptr), tail(nullptr), _size(0)
{
}

template <class T>
List<T>::~List()
{
    clear();
}

template <class T>
List<T>::List(const List<T> &list)
{
    this->head = this->tail = nullptr;
    Node current = list.head;
    this->_size = 0;
    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
}

template <class T>
void List<T>::push_back(T node)
{
    Node newNode = new _Node;
    newNode->data = node;
    if (this->head == nullptr)
        this->head = this->tail = newNode;
    else
    {
        this->tail->next = newNode;
        this->tail->prev = this->tail;
        this->tail = newNode;
    }
    this->_size++;
}

template <class T>
void List<T>::push_front(T node)
{
    Node newNode = new _Node;
    newNode->data = node;
    if (this->head == nullptr)
        this->head = this->tail = newNode;
    else
    {
        newNode->next = this->head;
        this->head->prev = newNode;
        this->head = newNode;
    }
    this->_size++;
}

template <class T>
void List<T>::pop_back() // Xem xét
{
    try
    {
        if (isEmpty())
            throw "Danh sách trống";

        Node temp = this->tail;
        this->tail = this->tail->prev;
        delete temp;
        this->_size--;
    }
    catch (const string &msg)
    {
        cerr << msg << endl;
    }
}

template <class T>
void List<T>::pop_front()
{
    try
    {
        if (isEmpty())
            throw "Danh sách trống";

        Node temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->_size--;
    }
    catch (const string &msg)
    {
        cerr << msg << endl;
    }
}

template <class T>
void List<T>::remove(int index)
{
    try
    {
        if (isEmpty())
            throw "Danh sách trống";
        else if (index >= this->_size)
            throw "Vị trí không hợp lệ";
        else if (index == 0)
            pop_front();
        else if (index == this->_size - 1)
            pop_back();
        else
        {
            Node current = this->head;
            for (int i = 0; i < index - 1; i++)
                current = current->next;
            Node temp = current->next;
            current->next = temp->next;
            current->next->prev = current;
            delete temp;
            this->_size--;
        }
    }
    catch (const string &msg)
    {
        cerr << msg << endl;
    }
}

template <class T>
void List<T>::clear()
{
    while (head != nullptr)
    {
        Node temp = head;
        head = head->next;
        delete temp;
    }
    _size = 0;
}

template <class T>
bool List<T>::isEmpty()
{
    return _size == 0;
}

template <class T>
int List<T>::size()
{
    return _size;
}

template <class T>
T &List<T>::operator[](int index)
{
    try
    {
        if (index >= this->_size)
            throw "Vị trí không hợp lệ";
        Node temp = this->head;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        return temp->data;
    }
    catch (const string &msg)
    {
        cerr << msg << endl;
        return this->head->data;
    }
}

#endif