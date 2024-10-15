#include "LList.h"

int main()
{
	LList list;

	list.insert_node(1);
	list.insert_node(3);
	list.insert_node(2);
	list.insert_node(10);
	list.insert_node(9);
	list.insert_node(8);
	list.insert_node(7);

	list.print_node();
	std::cout << "\n\n";

	list.delete_node(1);	// ��� ����
	list.print_node();
	std::cout << "\n\n";

	list.delete_node(8);	// ��� ���� ����
	list.print_node();
	std::cout << "\n\n";

	list.delete_node(3);	// ������ ����
	list.print_node();
	std::cout << "\n\n";

	list.delete_node(111);	// ���� ������ ����
	list.print_node();
	std::cout << "\n\n";

	return 0;
}