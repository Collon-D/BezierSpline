#include "LList.h"

LList::LList() :
	m_head(nullptr),
	m_cnt(0)
{
}

LList::~LList()
{
	Node* nextNode = m_head;
	while (nextNode)
	{
		Node* deleteNode = nextNode;
		nextNode = nextNode->next;
		delete deleteNode;
	}
}

int LList::insert_node(int data)
{
	Node* newNode = new Node;

	if (m_head == nullptr)
	{
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = nullptr;

		m_head = newNode;
	}
	else
	{
		if (m_cnt == 1)
		{
			newNode->data = data;
			newNode->prev = m_head;
			newNode->next = nullptr;
			m_head->next = newNode;
		}
		else
		{
			newNode->data = data;
			newNode->prev = m_head;
			newNode->next = m_head->next;
			newNode->next->prev = newNode;
			m_head->next = newNode;
		}
	}
	
	m_cnt++;
	return 0;
}

int LList::delete_node(int data)
{
	Node* deleteNode = m_head->next;
	Node* prevNode = m_head;

	bool check = false;
	while (deleteNode)
	{
		if (m_head->data == data)
		{
			m_head = m_head->next;
			m_head->prev = nullptr;
			delete prevNode;
			check = true;
			break;
		}
		else
		{
			if (deleteNode->data == data)
			{
				prevNode->next = deleteNode->next;
				
				if (deleteNode->next != nullptr)
					deleteNode->next->prev = prevNode;
				delete deleteNode;
				check = true;
				break;
			}
			else
			{
				deleteNode = deleteNode->next;
				prevNode = prevNode->next;
			}
		}
	}

	if (!check) 
	{
		std::cout << "삭제할 데이터가 존재하지 않습니다." << std::endl;
	}
	else
	{
		m_cnt--;
	}

	return 0;
}

void LList::print_node()
{
	Node* nextNode = m_head;
	while (nextNode)
	{
		std::cout << nextNode->data << " ";
		nextNode = nextNode->next;
	}
	std::cout << std::endl;
	count_node();
}

void LList::count_node()
{
	std::cout << "리스트에 들어있는 노드 개수 : " << m_cnt << std::endl;
}
