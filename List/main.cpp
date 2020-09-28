#include "List.h"
#include<iostream>
#include<time.h>
#include<stdlib.h>
#define CLOCKS_PER_SEC ((clock_t)1000)
clock_t t1, t2, t3, t4, t5;
int main()
{
	srand(time(0));
	List<int>A;
	for (int i = 1; i < 100000; ++i)
		A.push_back(rand() % 10000);
	List<int>B(A);
	List<int>C(A);
	List<int>D(A);
	t1 = clock();
	//A.show();
	std::cout << "**********************************************************************" << std::endl;
	//A.sort(0, A.size() - 1, select);
	//A.show();
	std::cout << "----------------------------------------------------------------------" << std::endl;
	t2 = clock();
	//B.show();
	std::cout << "**********************************************************************" << std::endl;
	//B.sort(0, B.size() - 1, bubble);
	//B.show();
	std::cout << "----------------------------------------------------------------------" << std::endl;
	t3 = clock();
	//C.show();
	std::cout << "**********************************************************************" << std::endl;
	C.sort(0, C.size() - 1, quick);
	//C.show();
	std::cout << "----------------------------------------------------------------------" << std::endl;
	t4 = clock();
	//D.show();
	std::cout << "**********************************************************************" << std::endl;
	//D.sort(0, D.size() - 1, shell);
	//D.show();
	std::cout << "----------------------------------------------------------------------" << std::endl;
	t5 = clock();
	//std::cout << (double)(t2 - t1) / CLOCKS_PER_SEC << std::endl;
	std::cout << (double)(t3 - t2) / CLOCKS_PER_SEC << std::endl;
	std::cout << (double)(t4 - t3) / CLOCKS_PER_SEC << std::endl;
	std::cout << (double)(t5 - t4) / CLOCKS_PER_SEC << std::endl;
	return 0;
}