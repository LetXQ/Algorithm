#ifndef LIST_H_
#define LIST_H_
#include "com_def.h"

struct Data
{
    Data(int _id = 0, const std::string& _name = "")
        : Id(_id)
        , name(_name)
    {}
    int Id = 0;
    std::string name = "";
};
struct Node
{
    ~Node()
    {
        std::cout << "Del id: " << data.Id << std::endl;
        p_next = nullptr;
//        if (p_next)
//        {
//            delete p_next;
//            p_next = nullptr;
//        }
    }

    Data data;
    Node* p_next = NULL;
};

class List
{
public:
    ~List()
    {
        std::cout << "deconstruct\n";
        this->Destroy();
    }
    void Destroy()
    {
        // Node的析构函数做了delete next操作，这里只需要delete头结点
        // 就能释放整个链表，但这就导致这种链表不能做删除节点操作
        // 如果Node没有析构函数，需要循环整个链表delete操作
//       delete m_pHead;
//        m_pHead = NULL;

        // 循环整个链表释放内存
        Node* p = nullptr;
        while (m_pHead) {
            p = m_pHead->p_next;
            delete m_pHead;
            m_pHead = p;
        }
        m_pHead = nullptr;
    }

    int HeadInsert(const Data& data)
    {
        Node* new_elem = new Node();
        if (!new_elem)
            return ERR_NEW_FAILED;
        new_elem->data = data;
        if (m_pHead)
        {
            new_elem->p_next = m_pHead;
            m_pHead = new_elem;
        }
        else
        {
            m_pHead = new_elem;
        }
        m_iSize++;
        return 0;
    }

    void PrintElems()
    {
        Node* tmp = m_pHead;
        std::cout << "List size: " << m_iSize << std::endl;
        while (tmp)
        {
            std::cout << "ID: " << tmp->data.Id
                      << ", Name: " << tmp->data.name << std::endl;
            tmp = tmp->p_next;
        }
    }

    int FindDataByPos(int pos, Data& data)
    {
        auto tmp = this->FindNodeByPos(pos);
        if (!tmp)
            return ERR_POS_INVALID;
        else
        {
            data = tmp->data;
            return 0;
        }
    }

    int InsertByPos(int pos, const Data& new_data)
    {
        if (pos <= 0 || pos > m_iSize)
            return ERR_POS_INVALID;
        if (1 == pos)
        {
            return this->HeadInsert(new_data);
        }
        else
        {
            auto tmp = this->FindNodeByPos(pos - 1);
            if (!tmp)
            {
                return ERR_POS_INVALID;
            }
            else
            {
                Node* new_elem = new Node();
                if (!new_elem)
                    return ERR_NEW_FAILED;
                new_elem->data = new_data;
                new_elem->p_next = tmp->p_next;
                tmp->p_next = new_elem;
            }
        }
        return 0;
    }

    int DeleteByPos(int pos, Data& del_data)
    {
        if (pos <= 0 || pos > m_iSize)
            return ERR_POS_INVALID;
        if (1 == pos)
        {
            Node* tmp = m_pHead;
            del_data = tmp->data;
            m_pHead = m_pHead->p_next;
            delete tmp;
            tmp = nullptr;
        }
        else
        {
            Node* pre = this->FindNodeByPos(pos -1);
            if (!pre)
                return ERR_POS_INVALID;
            Node* tmp = pre->p_next;
            pre->p_next = tmp->p_next;
            delete tmp;
            tmp = nullptr;
        }
        return 0;
    }

private:
    Node* FindNodeByPos(int pos)
    {
        int i = 1;
        Node* p = m_pHead;
        while(p && i < pos)
        {
            p =p->p_next;
            ++i;
        }

        if (p && i == pos)
        {
            return p;
        }
        return nullptr;
    }
private:
    int m_iSize = 0;
    Node* m_pHead = NULL;
};


#endif
