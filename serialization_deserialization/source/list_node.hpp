#pragma once

#ifndef __LIST_NODE_HPP__
#define __LIST_NODE_HPP__


#include <string>


namespace DataStorage
{

struct ListNode
{
	ListNode* prev;
	ListNode* next;
	ListNode* rand;

	std::string data;
};


ListNode* CreateListNode(const std::string& data,
						 ListNode* prev = nullptr,
						 ListNode* next = nullptr,
						 ListNode* rand = nullptr);

} // namespace DataStorage

#endif // ! __LIST_NODE_HPP__
