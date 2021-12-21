#include <tt.h>
#include <iostream>


int main(int argc, char *argv[])
{
	std::cout << "TTVM\n";
	if(!(argc==3 || argc==2))
	{
		std::cout << "[ERROR] wrong amount of parameters set\n";
		return 0;
	}
	for(int i=0; i<argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}
	return 0;
}