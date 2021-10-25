#include <iostream>


void PrintToBinary(int64_t number);


int main()
{
	PrintToBinary(1257);
	PrintToBinary(-1257);

	return 0;
}


void PrintToBinary(int64_t number)
{
	// sizeof will give us the number of bytes.
	//	Сonvert bytes to bits, which is the dimensionality in binary.
	const int8_t numberSize{ sizeof(number) * 8 };
	for(int8_t i = numberSize - 1; i >= 0; --i)
	{
		std::cout << ((number >> i) & 1) ? '1' : '0';
	}
	std::cout << std::endl;
}
