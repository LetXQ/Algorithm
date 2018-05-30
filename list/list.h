#ifndef LIST_H_
#define LIST_H_
#include <string.h>
enum ErrNum
{
	ERR_NEW_FAILED = 1,
};

struct Data
{
	int m_iID = 0;
	std::string m_name = "";
};
struct Node
{
	Data* m_pData = NULL;
	Node* m_pNext = NULL;
};

class List
{
public:
	void destroy()
	{
		Node* p = NULL;
		while (m_pHead)
		{
			p = m_pHead;
			m_pHead = m_pHead->m_pNext;
			delete p;
		}
		m_pHead = NULL;
	}
	
	int head_insert(Data* data)
	{
		Node* new_elem = new(Node);
		if (!new_elem)
			return ERR_NEW_FAILED;
		new_elem->m_pData = data;

		if (m_pHead)
		{
			new_elem->m_pNext = m_pHead->m_pNext;
			m_pHead->m_pNext = new_elem;
		}
		else
		{
			m_pHead = new_elem;
		}
		m_iSize++;
	}

	void print_elems()
	{
		Node* tmp = m_pHead;
		while (tmp)
		{
			std::cout << "ID: " << m_pHead->m_pData->m_iID
				<< ", Name: " << m_pHead->m_pData->m_name << std::endl;
			tmp = tmp->m_pNext;
		}
	}
private:
	int m_iSize = 0;
	Node* m_pHead = NULL;
};


#endif