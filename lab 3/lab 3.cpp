
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class MyExt {
    string error;
public:
    MyExt(string er) :error(er) {};
    void what()
    {
        cout <<"\nошибка!\n" << error << endl;
    }
};
template<typename T>
class MyList {
    struct Node {
        T item;
        Node* prev;
        Node* next;
        Node(Node* prev=nullptr,Node* next=nullptr) {
            this->prev = prev;
            this->next = next;
        }
        Node(T item, Node* prev = nullptr, Node* next = nullptr)
        {
            this->item = item;
            this->prev = prev;
            this->next;
        }
    };
    Node* first;
    Node* last;
    int Size;
public:
    MyList()
    {
        first = last = nullptr;
        Size = 0;
    }
    MyList(T item)
    {
        Node* temp = new Node(item);
        first = last = temp;
        Size = 1;
    }
    ~MyList()
    {
        Node* temp = first;
        Node* step;
        while (temp->next != nullptr);
        {
            step = temp->next;
            delete temp;
            temp = step;
        }
        delete last;
    }
    int size() { return Size; }
    void push_back(T item)
    {
        Node* temp = new Node(item);
        if (Size == 0) {
            first = last = temp;
        }
        else
        {
            last->next = temp;
            temp->prev = last;
            last = temp;
        }
        Size++;
    }
    void push_front(T item) {
        Node* temp = new Node(item);
        if (Size == 0) {
            first = last = temp;
        }
        else
        {
            first->prev = temp;
            temp->next = first;
            first = temp;
        }
        Size++;
    }
    T& operator[](int id)
    {
        if (id >= 0 && id < Size)
        {
            Node* temp = first;
            for (int i = 0; i != id; i++)
                temp = temp->next;
            return temp->item;
        }
        else
        {
            throw MyExt("operator []");
            exit(0);
        }
    }
    void pop_back()
    {
        if (Size != 0)
        {
            if (Size == 1)
            {
                delete first;
                delete last;
            }
            else
            {
                Node* temp = last->prev;
                temp->next = nullptr;
                delete last;
                last = temp;
            }
            Size--;
        }
        else
        {
            throw MyExt("контейнер пуст!");
                exit(0);
        }
    }
    void pop_front()
    {
        if (Size != 0)
        {
            if (Size == 1)
            {
                delete first;
                delete last;
            }
            else
            {
                Node* temp = first->next;
                temp->prev = nullptr;
                delete first;
                first = temp;
            }
            Size--;
        }
        else
        {
            throw MyExt("контейнер пуст!");
            exit(0);
        }
    }
    void pop(int id)
    {
        if (id >= 0 && id < Size)
        {
            Node* temp = first;
            if (id == 0)
                pop_front();
            else if (id == Size - 1)
                pop_back();
            else
            {
                for (int i = 0; i != id; i++)
                    temp = temp->next;
                Node* step = temp->prev;
                Node* step2 = temp->next;
                delete temp;
                step->next = step2;
                step2->prev = step;
                Size--;
            }
        }
        else
        {
            throw MyExt("неверный индекс");
            exit(0);
        }

    }
    Node* begin()
    {
        return first;
    }
    Node* end() {
        return last->next;
    }
    class iterator {
        Node* it;
    public:
        iterator(Node* temp):it(temp){}
        void operator =(Node* temp) {
            it = temp;
        }
        T operator *()
        {
            return it->item;
        }
        void operator ++()
        {
            if (it->next != nullptr)
                it = it->next;
            else
            {
                throw MyExt("данного эл нет!");
                exit(0);
            }
        }
        bool operator !=(Node* temp)
        {
            return (it == temp) ? false : true;
        }
    };
    void insert(T item, int id)
    {
        if (id >= 0 && id < Size)
        {
            Node* temp1 = new Node(item);
            Node* temp = first;
            if (id == 0)
                push_front(item);
            else if (id == Size - 1)
                push_back(item);
            else
            {
                for (int i = 0; i != id; i++)
                    temp = temp->next;
                Node* step = temp->prev;
                step->next = temp1;
                temp1->prev = step;
                temp1->next = temp;
                temp->prev = temp1;
                Size++;
            }
        }
        else
        {
            throw MyExt("неверный индекс");
            exit(0);
        }
    }
};
int main()
{
    setlocale(LC_ALL, "rus");
    string str;
    try
    {
        clock_t t;
        MyList<string> l;
        for (int i = 0; i < 100; i++)
            l.push_back(string());
        t = clock();
        cout << l.size() << endl;
        for (int i = 0; i < 1000;i++)
        {
            int n = rand() % 4;
            switch (n)
            {
            case 0:
            {
                l.push_back(string());
                cout << "push_back";
                break;
            }
            case 1:
            {
                l.push_front(string());
                cout << "push_front";
                break;
            }
            case 2:
            {
                l.pop_back();
                cout << "pop_back";
                break;
            }
            case 3:
            {
                l.pop_front();
                cout << "pop_front";
                break;
            }
            }
        }
        t = clock() - t;
        cout << l.size() << endl;
        cout << (double)t << "млс" << endl;
    }
    catch (MyExt er)
    {
        er.what();
    }
}


