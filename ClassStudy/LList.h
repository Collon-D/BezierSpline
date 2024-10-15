#pragma once
#ifndef __LLIST_H_
#define __LLIST_H_

#include <iostream>

struct Node
{
	int data;
	Node* next;
	Node* prev;
};

class LList
{
private:
	Node* m_head;
	int m_cnt;

public:
	LList();
	~LList();

public:
	int insert_node(int data);
	int delete_node(int data);
	void print_node();
	void count_node();
};

#endif
