#include <list.hpp>

#include <sstream>
#include <exception>
#include <vector>

#include <message_recording.hpp>


namespace DataStorage
{

List::List()
	: m_head{ nullptr },
	  m_tail{ nullptr },
	  m_count{ 0 }
{
	m_sequentialNodeNumbers[nullptr] = 0;
}


List::~List()
{
	if(0 == m_count)
	{
		return;
	}
	if(1 == m_count)
	{
		delete m_head;
		return;
	}

	ListNode* node = m_tail;
	while(node)
	{
		ListNode* prevNode = node->prev;
		delete node;
		node = prevNode;
	}
}


void List::PushBack(ListNode *node)
{
	if(!node)
	{
		RecordErrorMessage("The node is nullptr!");
		return;
	}

	m_sequentialNodeNumbers[node] = m_count + 1;

	if(0 == m_count)
	{
		m_head = node;
		node->prev = nullptr;
		node->next = nullptr;

		m_tail = nullptr;
		++m_count;
		return;
	}
	else if(1 == m_count)
	{
		node->prev = m_head;
		node->next = nullptr;
		m_tail = node;

		m_head->next = m_tail;
		++m_count;
		return;
	}

	node->prev = m_tail;
	node->next = nullptr;

	m_tail->next = node;
	m_tail = node;
	++m_count;
}


void List::PrintList() const
{
	if(IsEmpty())
	{
		RecordInfoMessage("The list is empty.");
	}

	std::stringstream infoAboutList;
	infoAboutList << "The list contains: ";
	for(ListNode* node = m_head; node; node = node->next)
	{
		infoAboutList << node->data << " ";
	}
	RecordInfoMessage(infoAboutList.str());
}


void List::Serialize(FILE *file) const
{
	if(!file)
	{
		RecordErrorMessage("The file is not open!");
		return;
	}

	if(IsEmpty())
	{
		RecordInfoMessage("The list is empty!");
		return;
	}

	if(!fwrite(&m_count, sizeof(m_count), 1, file))
	{
		RecordErrorMessage("Failed to record the number of serializable nodes!");
		return;
	}

	for(ListNode* node = m_head; node; node = node->next)
	{
		SerializeListNode(file, node);

		try
		{
			auto sequenceNumberOfRandomNode{ m_sequentialNodeNumbers.at(node->rand) };
			if(!fwrite(&sequenceNumberOfRandomNode, sizeof(sequenceNumberOfRandomNode), 1, file))
			{
				RecordErrorMessage("Failed to record the sequence number of a random node!");
				return;
			}
		}
		catch(const std::out_of_range& exc)
		{
			RecordErrorMessage("Failed to get the correct sequence number of a random node! " +
				std::string{ exc.what() });
			return;
		}
	}
}


void List::Deserialize(FILE *file)
{
	if(!file)
	{
		RecordErrorMessage("The file is not open!");
		return;
	}

	size_t count{ 0 };
	if(!fread(&count, sizeof(count), 1, file))
	{
		RecordErrorMessage("Failed to count the number of saved nodes!");
		return;
	}

	// Array storing pointers to nodes.
	std::vector<ListNode*> associationNumberAndNode{ count + 1 };
	associationNumberAndNode[0] = nullptr;

	// An array storing the sequence number of a random node.
	std::vector<int64_t> relationOfNodeToRandomNode;
	relationOfNodeToRandomNode.reserve(count);

	for(size_t i = 1; i <= count; ++i)
	{
		ListNode* deserializedNode{ DeserializeListNode(file) };
		PushBack(deserializedNode);
		associationNumberAndNode[i] = deserializedNode;

		size_t sequenceNumberOfRandomNode{ 0 };
		if(!fread(&sequenceNumberOfRandomNode, sizeof(sequenceNumberOfRandomNode), 1, file))
		{
			RecordErrorMessage("Failed to read the sequence number of a random node!");
			return;
		}
		relationOfNodeToRandomNode.emplace_back(sequenceNumberOfRandomNode);
	}

	// Restore links to random nodes.
	for(size_t i = 1; i < associationNumberAndNode.size(); ++i)
	{
		// Since associationNumberAndNode stores a nullptr element,
		//	it is necessary to decrease the relationOfNodeToRandomNode index by 1.
		associationNumberAndNode[i]->rand = associationNumberAndNode[relationOfNodeToRandomNode[i - 1]];
	}
}


void List::SerializeListNode(FILE* file, ListNode* node) const
{
	if(!node)
	{
		RecordErrorMessage("The node is nullptr!");
		return;
	}

	size_t lengthData{ node->data.length() };
	if(!fwrite(&lengthData, sizeof(lengthData), 1, file))
	{
		RecordErrorMessage("Failed to write the number of characters of the string to the file!");
		return;
	}

	if(!fwrite(node->data.c_str(), lengthData, 1, file))
	{
		RecordErrorMessage("Failed to write string to file!");
		return;
	}
}


ListNode* List::DeserializeListNode(FILE* file) const
{
	size_t lengthData = 0;
	if(!fread(&lengthData, sizeof(lengthData), 1, file))
	{
		RecordErrorMessage("Failed to read the number of characters of the string from the file!");
		return nullptr;
	}

	char data[lengthData + 1];
	if(!fread(&data, lengthData, 1, file))
	{
		RecordErrorMessage("Failed to read the string from the file!");
		return nullptr;
	}
	data[lengthData + 1] = '\0';

	return CreateListNode(std::string{ data });
}

} // namespace DataStorage
