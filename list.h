#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif
#ifndef INITIALIZER_LIST_H
#define INITIALIZER_LIST_H
#include <initializer_list>
#endif
#ifndef ALGORITHM_H
#define ALGORITHM_H 
#include <algorithm>
#endif
#ifndef RANGE_H
#define RANGE_H
#include <range>
#endif
#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif
#ifndef CSTRING_H
#define CSTRING_H
#include <cstring>
#endif
#pragma warn - rvl

template <class Type>
class list
{
    Type *pointer = NULL;
    int size = 0;
    Type *first = NULL;
    Type *last = NULL;
    void exit_sequence()
    {
        exit(-1);
    }
    bool isPresentHelper(int l, int r, Type element)
    {
        if (l < r)
        {
            int mid = (l + r)/2;
            if (pointer[mid] == element)
                return true;
            else
            {
                if (pointer[mid] > element)
                {
                    return isPresentHelper(l, mid - 1, element);
                }
                else
                {
                    return isPresentHelper(mid + 1, r, element);
                }
            }
        }   
        return false;
    }

public:
    template <typename T1>
    friend std :: ostream& operator<<(std :: ostream &os, list<T1>&);
    template <typename T1>
    friend std :: ostream& operator<<(std :: ostream &os, list<T1>&&);
    friend std :: ostream& operator<<(ostream &os, list<std :: string>&);
    list() {}
    list(int n) 
    {
        this->pointer = new Type[n];
        this->first = pointer;
        this->last = this->first + n;
        size = n;
    }

    list(Type *__begin, Type *__end, int step = 1)
    {
        for (auto i = __begin; i != __end; i+=step)
        {
            this->append(*i);
        }
    }

    list(list<Type> &copy_from)
    {
        this->pointer = new Type[copy_from.size];
        this->first = this->pointer;
        this->last = this->pointer + copy_from.size;
        this->size = copy_from.size;
        for (int i = 0; i < copy_from.size; i++)
        {
            pointer[i] = copy_from.pointer[i];
        } 
    }

    list(std :: string &from)
    {
        this->pointer = new string[from.length()];
        copy(from.begin(), from.end(), pointer);
        this->last = this->pointer + from.length();
        this->size = from.length();
    }

    list(std :: string &&from)
    {
        this->pointer = new string[from.length()];
        copy(from.begin(), from.end(), pointer);
        this->last = this->pointer + from.length();
        this->size = from.length();
    }

    list(list<Type> &&copy_from)
    {
        this->pointer = new Type[copy_from.size];
        this->first = this->pointer;
        this->last = this->pointer + copy_from.size;
        this->size = copy_from.size;
        for (int i = 0; i < copy_from.size; i++)
        {
            pointer[i] = copy_from.pointer[i];
        } 
    }

    list(std ::initializer_list<Type> &&l)
    {
        pointer = new Type[l.size()];
        int k = 0;
        for (auto i = l.begin(); i != l.end(); i++)
        {
            pointer[k++] = *(const_cast<Type*>(i));
        }
        this->size = l.size();
        this->first = pointer;
        this->last = this->pointer + size;
    }

    list(std ::initializer_list<Type> &l)
    {
        pointer = new Type[l.size()];
        int k = 0;
        for (auto i = l.begin(); i != l.end(); i++)
        {
            pointer[k++] = *(const_cast<Type*>(i));
        }
        this->size = l.size();
        this->first = pointer;
        this->last = this->pointer + size;
    }

    int length()
    {
        return this->size;
    }

    void insert(Type element, int index)
    {
        if (index == this->size)
            this->append(element);
        else
        {
            try
            {
                if (index > this->size + 1)
                {
                    throw std :: invalid_argument("Index out of bound");
                }
                else
                {
                    list<int> temp;
                    if (index == 0)
                    {
                        temp = list<Type>({element}) + (*this);
                    }
                    else
                    {
                        list<Type> l1(this->slice(0, index));
                        list<Type> l2(this->slice(index, size));
                        l1.append(element);
                        temp = l1 + l2;
                    }
                    delete[] pointer;
                    pointer = new Type[++this->size];
                    copy(temp.begin(), temp.end(), pointer);
                    last = pointer + size;
                }
            }
            catch(std :: invalid_argument& err)
            {
                cout << err.what() << endl;
                exit_sequence();
            }
        }
    }

    void append(Type element)
    {
        ++size;
        Type *temp = new Type[size];
        if (pointer)
        {
            for (int i = 0; i < size - 1; i++)
            {
                temp[i] = pointer[i];
            }
            delete[] pointer;
            first = last = NULL;
        }
        pointer = temp;
        first = pointer;
        *(pointer + size - 1) = element; 
        last = pointer + size;
    }
    list<int> indexOf(Type element)
    {
        list<int> indexes;
        int index = -1;
        for (auto i = begin(); i != end(); i++)
        {
            if (*i == element)
            {
                index = i - begin();
                indexes.append(index);
            }
        }
        return indexes;
    }
    
    list<Type> operator+(list<Type> &&operand)
    {
        list<Type> l;
        for (auto i : *this)
        {
            l.append(i);
        }
        for (auto i : operand)
        {
            l.append(i);
        }
        return l;
    }

    list<Type> operator+(list<Type> &operand)
    {
        list<Type> l;
        for (auto i : *this)
        {
            l.append(i);
        }
        for (auto i : operand)
        {
            l.append(i);
        }
        return l;
    }

    list<Type> operator+(std :: initializer_list<Type> &&l)
    {
        list<Type> ret;
        for (auto i : *this)
            ret.append(i);
        for (auto i : l)
            ret.append(i);
        return ret;
    }

    list<Type> operator+(std :: initializer_list<Type> &l)
    {
        list<Type> ret;
        for (auto i : *this)
            ret.append(i);
        for (auto i : l)
            ret.append(i);
        return ret;
    }

    bool isEmpty()
    {
        if (this->size)
            return false;
        return true;
    }

    bool operator==(std :: initializer_list<Type> &&l)
    {
        if (size == l.size())
        {
            auto p = l.begin();
            for (auto i : *this)
            {
                if (i != *p)
                    return false;
                ++p;
            }
            return true;
        }
        return false;
    }

    list<Type> operator=(list<Type> &&l)
    {
        if (this->pointer)
        {
            delete[] this->pointer;
        }
        this->pointer = new Type[l.size];
        first = pointer;
        int k = 0;
            //copy(l.begin(), l.end(), pointer);
        for (auto i : l)
            pointer[k++] = i;
        this->size = l.size;
        last = pointer + size;
        return *this;
    }

    list<Type> operator=(list<Type> &l)
    {
        if (this->pointer)
        {
            delete[] this->pointer;
        }
        this->pointer = new Type[l.size];
            first = pointer;
            int k = 0;
            for (auto i : l)
                pointer[k++] = i;
            this->size = l.size;
            last = pointer + size;
        return *this;
    }

    list(range&& r)
    {
        int len = r.end() - r.begin();
        this->pointer = new Type[len];
        copy(r.begin(), r.end(),  pointer);
        this->size = len;
        first = pointer;
        last = pointer + size;
    }

    list(range &r)
    {
        int len = r.end() - r.begin();
        this->pointer = new Type[len];
        copy(r.begin(), r.end(),  pointer);
        this->size = len;
        first = pointer;
        last = pointer + size;
    }
    
    operator vector<int>()
    {
        std :: vector<int> v(this->size);
        copy(begin(), end(), v.begin());
        return v;
    }

    list<list<Type>> operator*(list<Type> &operand2)
    {
        list<list<Type>> res;
        for (auto i : *this)
        {
            for (auto j : operand2)
            {
                res.append({i, j});
            }
        }
        return res;
    }

    list<list<Type>> operator*(list<Type> &&operand2)
    {
        list<list<Type>> res;
        for (auto i : *this)
        {
            for (auto j : operand2)
            {
                res.append({i, j});
            }
        }
        return res;
    }

    list<Type> operator=(std :: initializer_list<Type> &&l)
    {
        if (pointer)
        {
            delete[] pointer;
            size = 0;
            first = last = NULL;
        }
        pointer = new Type[l.size()];
        int k = 0;
        for (auto i = l.begin(); i != l.end(); i++)
        {
            pointer[k++] = *(const_cast<Type*>(i));
        }
        this->size = l.size();
        first = pointer;
        last = pointer + l.size();
        return *this;
    }

    Type *begin()
    {
        return first;
    }

    Type *end()
    {
        return last;
    }

    void remove(Type element)
    {
        int index = -1;
        for (int i = 0; i < size && index == -1; i++)
        {
            if (pointer[i] == element)
            {
                index = i;
            }
        }
        try
        {
            if (index != -1)
            {
                int k = 0;
                Type *temp = new Type[size - 1];
                for (int i = 0; i < size; i++)
                {
                    if (i != index)
                    {
                        temp[k++] = pointer[i];
                    }
                }
                --size;
                delete[] pointer;
                pointer = temp;
                first = pointer;
                last = pointer + size;
            }
            else
            {
                throw std :: string("Element Not found");
            }
        }
        catch(std :: string &err)
        {
            std :: cout << err << std :: endl;
            exit_sequence();
        }
    }

    list<Type> slice(int start, int end, int step = 1)
    {
        list<Type> res;
        for (auto i : range(start, end, step))
        {
            res.append(this->operator[](i));
        }
        return res;
    }

    bool isPresent(Type element)
    {
        for (auto i : *this)
        {
            if (i == element)
            {
                return true;
            }
        }
        return false;
    }
    template <typename F>
    void sort(Type *start, Type * end, F&& lambda)
    {
        std :: sort(start, end, lambda);
    }

    void sort(Type* start, Type *end, bool (*predicate)(bool, bool))
    {
        std :: sort(start, end, predicate);
    }
    
    void sort(Type *start, Type * end)
    {
        std :: sort(start, end);
    }

    bool operator==(list<Type> &other)
    {
        if (this->size == other.size)
        {
            for (int i = 0; i < size; i++)
            {
                if (this->pointer[i] != other.pointer[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    int count(Type element)
    {
        int c = 0;
        for (auto i : *this)
        {
            if (i == element)
                ++c;
        }
        return c;
    }

    bool operator==(list<Type> &&other)
    {
        return (*this == other);
    }
    
    Type pop()
    {
        Type element;
        try
        {
            if (size == 0)
            {
                throw std :: string("Pop from empty list\n");
            }
            element = *(end() - 1);
            this->remove(element);
        }   
        catch(string &err)
        {
            cout << err;
            exit_sequence();
        }
        return element;
    }

    bool operator!=(list<Type> &other)
    {
        return !(this->operator==(other));
    }

    Type &operator[](int index)
    {
        try
        {
            if (index >= size)
            {
                throw std ::invalid_argument("Index out of range");
            }
        }
        catch (const std ::invalid_argument &err)
        {
            std ::cout << err.what() << std ::endl;
            exit_sequence();
        }
        return pointer[index];
    }
    
    ~list()
    {
        if (pointer)
        {
            delete[] pointer;
            pointer = NULL;
            first = last = NULL;
            size = 0;
        }
    }
};
template <class Type>
std ::ostream &operator<<(std ::ostream &os, list<Type> &arr)
{
    os << "[";
    int i = 0;
    int top = arr.size;
    for (i = 0; i < top - 1; i++)
    {
        os << arr.pointer[i] << ", ";
    }
    if (top != 0)
    {
        os << arr[top - 1];
    }
    os << "]";
    return os;
}

std :: ostream& operator<<(ostream& os, list<std :: string> &arr)
{
    os << "[";
    int i = 0;
    int top = arr.length();
    for (i = 0; i < top - 1; i++)
    {
        os << "'" << arr[i] << "'" << ", ";
    }
    if (top != 0)
    {
        os << "'" << arr[top - 1] << "'";
    }
    os << "]";
    return os;
}

template <class Type>
std ::ostream &operator<<(std ::ostream &os, list<Type> &&arr)
{
    os << arr;
    return os;
}
