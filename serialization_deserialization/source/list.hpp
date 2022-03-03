#pragma once

#ifndef __LIST_HPP__
#define __LIST_HPP__


#include <unordered_map>

#include <list_node.hpp>


namespace DataStorage
{

class List
{
public:
	List();
	~List();

	void PushBack(ListNode* node);

	void PrintList() const;

	void Serialize(FILE* file) const;
	void Deserialize(FILE* file);

public:
	inline bool IsEmpty() const
	{
		return 0 == m_count;
	}

	inline ListNode* Front() const
	{
		return m_head;
	}

	inline ListNode* Back() const
	{
		return m_tail;
	}

	inline size_t Size() const
	{
		return m_count;
	}

private:
	void SerializeListNode(FILE* file, ListNode* node) const;
	ListNode* DeserializeListNode(FILE* file) const;

private:
	std::unordered_map<ListNode*, size_t> m_sequentialNodeNumbers;

	ListNode* m_head;
	ListNode* m_tail;

	size_t m_count;
};

} // namespace DataStorage


#endif // ! __LIST_HPP__
