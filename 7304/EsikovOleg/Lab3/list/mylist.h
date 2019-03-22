#ifndef MYLIST_H
#define MYLIST_H

#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

using std::swap;

namespace stepik
{
template <class Type>
struct node
{
    Type value;
    node* next;
    node* prev;
    node(const Type& value, node<Type>* next, node<Type>* prev) : value(value), next(next), prev(prev) {}
};

template <class Type>
class list; //forward declaration

template <class Type>
class list_iterator
{
public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator() : m_node(NULL) {}

    list_iterator(const list_iterator& other) : m_node(other.m_node) {}

    list_iterator& operator = (const list_iterator& other)
    {
        m_node = other.m_node;
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        list_iterator temp(*this);
        ++(*this);
        return temp;
    }

private:
    friend class list<Type>;

    list_iterator(node<Type>* p) : m_node(p) {}

    node<Type>* m_node;
};

template <class Type>
class list
{
public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list() : m_head(nullptr), m_tail(nullptr) {}

    ~list()
    {
        clear();
    }

    list(const list& other) : list()
    {
        node<Type>* temp = other.m_head;
        while(temp)
        {
            push_back(temp->value);
            temp = temp->next;
        }
    }

    list(list&& other) : list()
    {
        if(this != &other)
        {
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
        }
    }

    list& operator = (const list& other)
    {
        if(this != &other)
        {
            list temp(other);
            std::swap(m_head, temp.m_head);
            std::swap(m_tail, temp.m_tail);
        }
        return *this;
    }

    void push_back(const value_type& value)
    {
        node<Type> *temp = new node<Type>(value, nullptr, nullptr);
        if(!empty())
        {
            temp->prev = m_tail;
            m_tail->next = temp;
            m_tail = temp;
        }
        else
        {
            m_head = temp;
            m_tail = temp;
        }
    }

    void push_front(const value_type& value)
    {
        node<Type> *temp = new node<Type>(value, nullptr, nullptr);
        if(!empty())
        {
            temp->next = m_head;
            m_head->prev = temp;
            m_head = temp;
        }
        else
        {
            m_head = temp;
            m_tail = temp;
        }
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(pos.m_node == nullptr)
        {
            push_back(value);
            return iterator(m_tail);
        }
        if(pos.m_node == m_head)
        {
            push_front(value);
            return iterator(m_head);
        }
        else
        {
            node<Type>* temp = new node<Type>(value, pos.m_node, pos.m_node->prev);
            pos.m_node->prev->next = temp;
            pos.m_node->prev = temp;
            return iterator(temp);
        }
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == NULL)
        {
            return NULL;
        }
        if(pos.m_node == m_head)
        {
            pop_front();
            return iterator(m_head);
        }
        if(pos.m_node == m_tail)
        {
            pop_back();
            return iterator(m_tail);
        }
        else
        {
            pos.m_node->prev->next = pos.m_node->next;
            pos.m_node->next->prev = pos.m_node->prev;
            node<Type>* temp = pos.m_node;
            iterator result(pos.m_node->next);
            delete temp;
            return result;
        }
    }

    reference front()
    {
        return m_head->value;
    }

    const_reference front() const
    {
        return m_head->value;
    }

    reference back()
    {
        return m_tail->value;
    }

    const_reference back() const
    {
        return m_tail->value;
    }

    void pop_front()
    {
        if(!empty())
        {
            if(size() == 1)
            {
                m_head = NULL;
                m_tail = NULL;
            }
            else
            {
                node<Type>* temp = m_head->next;
                temp->prev = nullptr;
                delete m_head;
                m_head = temp;
            }
        }
    }

    void pop_back()
    {
        if(!empty())
        {
            if(size() == 1)
            {
                m_head = NULL;
                m_tail = NULL;
            }
            else
            {
                node<Type>* temp = m_tail->prev;
                temp->next = nullptr;
                delete m_tail;
                m_tail = temp;
            }
        }
    }

    void clear()
    {
        while(m_head != NULL)
        {
            m_tail = m_head->next;
            delete m_head;
            m_head = m_tail;
        }
    }

    bool empty() const
    {
        if(m_head)
            return false;
        else
            return true;
    }

    size_t size() const
    {
        node<Type>* temp = m_head;
        size_t count = 0;
        while(temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    list::iterator begin()
    {
        return iterator(m_head);
    }

    list::iterator end()
    {
        return iterator();
    }

    friend void operator << (std::ostream& os, list& element)
    {
            node<Type>* temp = element.m_head;
            while(temp)
            {
                os << temp->value << " ";
                temp = temp->next;
            }
            os << std::endl;
    }

private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
    };
}// namespace stepik

#endif // MYLIST_H