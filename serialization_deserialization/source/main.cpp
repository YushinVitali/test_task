#include <string>
#include <memory>

#include <list.hpp>
#include <list_node.hpp>
#include <message_recording.hpp>


namespace DS = DataStorage;


constexpr auto filename{ "./file.txt" };


static std::unique_ptr<DS::List> CreateList();


int main()
{
	std::unique_ptr<DS::List> list{ CreateList() };
	list->PrintList();

	FILE* file = fopen(filename, "wb");
	if(!file)
	{
		RecordErrorMessage(std::string{ "Error opening " } +
			filename + std::string{ " file!" } );
		return errno;
	}
	list->Serialize(file);
	fclose(file);

	file = fopen(filename, "rb");
	if(!file)
	{
		RecordErrorMessage(std::string{ "Error opening " } +
			filename + std::string{ " file!" } );
		return errno;
	}

	std::unique_ptr<DS::List> deserializableList{ new DS::List() };
	deserializableList->Deserialize(file);
	deserializableList->PrintList();
	fclose(file);

	return 0;
}


static std::unique_ptr<DataStorage::List> CreateList()
{
	std::unique_ptr<DS::List> list{ new DS::List() };

	for(size_t i = 0; i < 5; ++i)
	{
		list->PushBack(DS::CreateListNode("xyz_" + std::to_string(i)));
	}

	DS::ListNode* temp = list->Front();
	for(size_t i = 0; i < list->Size(); ++i)
	{
		if(i % 3 == 1)
		{
			temp->rand = nullptr;
		}
		else if(i % 3 == 2)
		{
			temp->rand = temp->prev;
		}
		else
		{
			temp->rand = temp->next;
		}
		temp = temp->next;
	}

	return list;
}
