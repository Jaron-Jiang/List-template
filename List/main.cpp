#pragma once
#include "List.h"
#include<iostream>
int main()
{
	List<int>L;
	for (int i = 1; i < 100; i *= 2)
		L.push_front(i);
	List<int>A;
	for (int i = 2; i < 256; i *= 2)
		A.push_back(i);
	A.show();
	L.show();
	A.complement(L);
	A.show();
	system("pause");
	return 0;
}