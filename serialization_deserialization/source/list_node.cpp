#include <list_node.hpp>


namespace DataStorage
{

ListNode* CreateListNode(const std::string& data,
	ListNode* prev /* = nullptr */,
	ListNode* next /* = nullptr */,
	ListNode* rand /* = nullptr */)
{
	ListNode* node = new ListNode;
	node->data = data;
	node->prev = prev;
	node->next = next;
	node->rand = rand;
	return node;
}

} // namespace DataStorage
