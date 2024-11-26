#ifndef LIST
#define LIST 1

#include <iostream>

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
    class Iterator
    {
    private:
        Node current;

    public:
        Iterator(Node node) : current(node) {}
        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        T &operator*() { return current->data; }
        bool operator==(const Iterator &it) { return current == it.current; }
        bool operator!=(const Iterator &it) { return current != it.current; }
    };
    List();
    ~List();
    List(std::initializer_list<T>);
    List(const List<T> &);
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void remove(int);
    void clear();
    bool empty() const;
    int size() const;
    Iterator begin() const { return Iterator(this->head); }
    Iterator end() const { return Iterator(nullptr); }
    T &operator[](int) const;
    List<T> &operator=(const List<T> &list);
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
List<T>::List(std::initializer_list<T> list)
{
    this->head = this->tail = nullptr;
    this->_size = 0;
    for (auto &node : list)
        push_back(node);
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
    try
    {
        Node newNode = new _Node;
        newNode->data = node;
        if (this->head == nullptr)
            this->head = this->tail = newNode;
        else
        {
            newNode->prev = this->tail;
            this->tail->next = newNode;
            this->tail = newNode;
        }
        this->_size++;
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Lỗi cấp phát bộ nhớ" << std::endl;
    }
}

template <class T>
void List<T>::push_front(T node)
{
    try
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
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Lỗi cấp phát bộ nhớ" << std::endl;
    }
}

template <class T>
void List<T>::pop_back() // Xem xét
{
    try
    {
        if (empty())
            throw "Danh sách trống";

        Node temp = this->tail;
        this->tail = this->tail->prev;
        delete temp;
        this->_size--;
    }
    catch (const std::string &msg)
    {
        std::cerr << msg << std::endl;
    }
}

template <class T>
void List<T>::pop_front()
{
    try
    {
        if (empty())
            throw "Danh sách trống";

        Node temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->_size--;
    }
    catch (const std::string &msg)
    {
        std::cerr << msg << std::endl;
    }
}

template <class T>
void List<T>::remove(int index)
{
    try
    {
        if (empty())
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
    catch (const std::string &msg)
    {
        std::cerr << msg << std::endl;
    }
}

template <class T>
void List<T>::clear()
{
    while (this->head != nullptr)
    {
        Node temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    _size = 0;
}

template <class T>
bool List<T>::empty() const
{
    return _size == 0;
}

template <class T>
int List<T>::size() const
{
    return _size;
}

template <class T>
T &List<T>::operator[](int index) const
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
    catch (const std::string &msg)
    {
        std::cerr << msg << std::endl;
        return this->head->data;
    }
}

template <class T>
List<T> &List<T>::operator=(const List<T> &list)
{
    clear();
    Node current = list.head;
    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
    return *this;
}

#endif