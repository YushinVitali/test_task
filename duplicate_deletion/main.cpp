#include <iostream>
#include <cstring>


void RemoveDups(char* str);


int main()
{
	char data[]{ "AAA BBB AAA" };
	RemoveDups(data);
	std::cout << data << std::endl;

	return 0;
}


void RemoveDups(char* str)
{
	if(!str)
	{
		return;
	}

	size_t readableIndex{ 1 };
	size_t rewritableIndex{ 0 };
	for(; str[readableIndex] != '\0'; ++readableIndex)
	{
		if(str[rewritableIndex] != str[readableIndex])
		{
			str[++rewritableIndex] = str[readableIndex];
		}
	}
	str[++rewritableIndex] = '\0';
}
