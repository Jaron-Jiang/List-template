#pragma once
#include<iostream>

enum
{
	quick,
	select,
	bubble,
	shell
};
template <class T>
class List
{
private:
	struct Data
	{
		T data;
		Data* next;
		Data* ahead;
	};
	int Size;
	Data* head;
	Data* end;
	Data* At(int index)//返回一个指向第index个元素的指针(index从1开始)
	{
		if (index > Size || index <= 0)
			return NULL;
		Data* p;
		if (2 * index <= Size)
		{
			p = head;
			for (int i = 2; i <= index; ++i)
			{
				p = p->next;
			}
		}
		else
		{
			p = end;
			for (int i = Size - 1; i >= index; --i)
			{
				p = p->ahead;
			}
		}
		return p;
	}

	static bool judge(T a, T b)//判断两个元素是否相同的内置函数，只对非结构体类型有效（用于unique的三个函数）
	{
		return a == b ? true : false;
	}

	static void Show(T a)//内置的展示列表内容的函数，只对非结构体类型有效（用于show函数）
	{
		std::cout << a << " ";
	}

	static bool cmp(T a, T b)////内置的展示列表内容的函数，只对非结构体类型有效（用于sort类函数和merge函数）
	{
		return a <= b ? true : false;
	}

	void swap(Data* p, Data* p1)
	{
		T s = p->data;
		p->data = p1->data;
		p1->data = s;
	}

	//快速排序
	bool quick_sort(int start, int final, bool(*cmp)(T, T) = cmp);
	//选择排序
	bool select_sort(int start, int final, bool(*cmp)(T, T) = cmp);
	//冒泡排序
	bool bubble_sort(int start, int final, bool(*cmp)(T, T) = cmp);
	//希尔排序
	bool shell_sort(int start, int final, bool(*cmp)(T, T) = cmp);
public:

	//构造函数，初始化一个空的列表
	List();
	//构造函数(也是拷贝构造函数)，将列表a中的全部数据复制到当前列表中（进行深拷贝）
	List(List& a);
	//构造函数，将列表a中从first到last位置的数据复制到当前列表中（进行深拷贝，first从1开始）
	List(List& a,int first,int last);

	//析构函数，释放列表中new的全部空间
	~List();

	//返回列表的长度
	int size();

	//在下标index位置插入数据val,插入成功返回true，否则返回false（index从0开始）
	bool insert(int index,T val);
	//将列表a中从first到last位置的数据复制到当前列表中（first从1开始）
	bool insert(List& a, int first, int last);
	//将列表a中的数据全部复制到当前列表中
	bool insert(List& a);

	//在尾部插入数据val
	bool push_back(T val);
	//在头部插入数据val
	bool push_front(T val);

	//删除尾部元素
	bool pop_back();
	//删除头部元素
	bool pop_front();

	//输出列表的全部数据   注意: 如果列表是非基本数据类型，则必须自己写要展示的东西的函数，然后把该函数当作参数传入show函数
	void show(void(*f)(T) = Show);

	//删除index的数据(index从0开始)
	bool erase(int index);
	//删除index1到index2的数据(index1从0开始，包括删除index2的数据)
	bool erase(int index1, int index2);
	//清空全部数据
	void clear();

	//查找index位置的数据，并返回，如果没有找到则返回第一个元素(index从0开始)
	T find(int index);
	//返回第一个元素，如果列表为空，则返回NULL
	T front();
	//返回最后一个元素，如果列表为空，则返回NULL
	T back();

	//判断列表是否为空，如果是则返回true，否则则返回false
	bool empty();

	//重载[]运算符，实现通过下标修改数据，如果下标大于实际长度，则返回第一个数据的引用
	T& operator[](const int index);
	//对类进行“=”运算符重载
	void operator=(List& a);

	//在尾部插入一个列表，同时去重，如果操作出现错误，返回false,使用函数指针cmp，当cmp返回true时，表示两个元素相同，需要去掉其中一个
	bool unique(List& a, bool(*cmp)(T, T) = judge);
	//对列表去重，如果操作出现错误返回fasle,使用函数指针cmp，当cmp返回true时，表示两个元素相同，需要去掉其中一个
	bool unique(bool(*cmp)(T, T) = judge);
	//在尾部插入数据，保证不重复，如果操作出现错误返回fasle,使用函数指针cmp，当cmp返回true时，表示两个元素相同，需要去掉其中一个
	bool unique(T val, bool(*cmp)(T, T) = judge);

	//交换下标index1与下标index2的数据(从0开始)
	bool swap(int index1,int index2);
	
	//选择排序并选择排序算法
	bool sort(int start,int final,int model,bool(*cmp)(T, T) = cmp);

	//差集运算A-B，即当前对象为A，输入的参数对象a即为B，进行A-B运算，*cmp为函数指针，用来判断两个元素是否相同，如果判断的是非基本数据类型，则需要自己传入判断函数
	void complement(List& a, bool(*cmp)(T,T) = cmp);	

	//将有序表a和有序表b中的元素合并放到当前列表中(注意该函数是为了保证新和成的列表是有序的，因此当前的列表应该是空的，如果非空，会被清空然后合并)
	bool merge(List& a, List& b, bool(*f)(T, T) = cmp);
	//将有序表a中的元素合并放到当前列表中(注意该函数是为了保证新和成的列表是有序的，因此当前的列表应该是有序的)
	bool merge(List& a, bool(*f)(T, T) = cmp);
};

template<class T>
List<T>::List()
{
	head = NULL;
	end = NULL;
	Size = 0;
}

template<class T>
List<T>::List(List& a)
{
	Data* p = a.head;
	while (p)
	{
		push_back(p->data);
		p = p->next;
	}
}

template<class T>
List<T>::List(List& a, int first, int last)
{
	insert(a,first,last);
}

template<class T>
List<T>::~List()
{
	clear();
}

template<class T>
int List<T>::size()
{
	return Size;
}

template<class T>
bool List<T>::insert(int index, T val)
{
	try
	{
		if (index > Size || index < 0)
			return false;
		Data* p = head;
		if (Size == 0 || index == 0)
		{
			push_front(val);
		}
		else if (index + 1 == Size)
		{
			push_back(val);
		}
		else
		{
			Data* p = At(index + 1);
			Data* s = new Data;
			s->data = p->data;
			s->ahead = p->ahead;
			s->next = p;
			p->ahead->next = s;
			p->ahead = s;
			Size++;
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
bool List<T>::insert(List& a, int first, int last)
{
	if (first > last || last > a.size() || first <= 0)
	{
		return false;
	}
	Data* p = a.At(first);
	Data* p1 = a.At(last)->next;
	do
	{
		push_back(p->data);
		p = p->next;
	} while (p != p1);
	return true;
}

template<class T>
bool List<T>::insert(List& a)
{
	if (a.size() == 0)
		return false;
	Data* p = a.At(1);
	do
	{
		push_back(p->data);
		p = p->next;
	} while (p);
	return true;
}

template<class T>
bool List<T>::push_back(T val)
{
	if (Size == 0)
	{
		try
		{
			Data* s = new Data;
			s->data = val;
			s->next = NULL;
			s->ahead = NULL;
			head = end = s;
			Size++;
		}
		catch (const std::exception&)
		{
			return false;
		}
		return true;
	}
	try
	{
		Data* s = new Data;
		s->data = val;
		s->next = NULL;
		s->ahead = end;
		end->next = s;
		end = s;
	}
	catch (const std::exception&)
	{
		return false;
	}
	Size++;
	return true;
}

template<class T>
bool List<T>::push_front(T val)
{
	Data* p = head;
	try
	{
		Data* s = new Data;
		s->data = val;
		s->next = head;
		s->ahead = NULL;
		if (Size == 0)
			end = s;
		else
			head->ahead = s;
		head = s;
	}
	catch (const std::exception&)
	{
		return false;
	}
	Size++;
	return true;
}

template<class T>
bool List<T>::pop_back()
{
	if (Size == 0)
		return false;

	Data* p = end;
	if (Size == 1)
	{
		head = end = NULL;
	}
	else
	{
		end = end->ahead;
		end->next = NULL;
	}
	delete p;
	Size--;
	return true;
}

template<class T>
bool List<T>::pop_front()
{
	if (Size == 0)
		return false;
	Data* p = head;
	if (Size == 1)
	{
		head = end = NULL;
	}
	else
	{
		head = head->next;
	}
	delete p;
	Size--;
	return true;
}

template<class T>
void List<T>::show(void(*f)(T))
{
	Data* p = head;
	while (p)
	{
		f(p->data);
		p = p->next;
	}
	std::cout << std::endl;
}

template<class T>
bool List<T>::erase(int index)
{
	if (index < 0 || index >= Size)
	{
		return false;
	}
	try
	{
		if (index == 0)
		{
			pop_front();
		}
		else if (index == Size - 1)
		{
			pop_back();
		}
		else
		{
			Data* p = At(index + 1);
			p->ahead->next = p->next;
			p->next->ahead = p->ahead;
			delete p;
			Size--;
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
bool List<T>::erase(int index1, int index2)
{
	if (index1 < 0 || index1 > index2 || index2 >= Size)
		return false;
	for (int i = index2; i >= index1; i--)
	{
		erase(i);
	}
	return true;
}

template<class T>
void List<T>::clear()
{
	Data* p;
	while (head)
	{
		p = head;
		head = head->next;
		delete p;
		Size--;
	}
	end = NULL;
}

template<class T>
T List<T>::find(int index)
{
	if (index >= Size)
		return head->data;
	Data* p = At(index + 1);
	return p->data;
}

template<class T>
T List<T>::front()
{
	return Size == 0 ? NULL : head->data;
}

template<class T>
T List<T>::back()
{
	return Size == 0 ? NULL : end->data;
}

template<class T>
bool List<T>::empty()
{
	return Size == 0 ? true : false;
}

template<class T>
T& List<T>::operator[](int index)
{
	if (index >= Size || index < 0)
	{
		return head->data;
	}
	Data* p = At(index + 1);
	return p->data;
}

template<class T>
void List<T>::operator=(List& a)
{
	clear();
	Data* p = a.head;
	while (p)
	{
		push_back(p->data);
		p = p->next;
	}
}

template<class T>
bool List<T>::unique(List& a, bool(*cmp)(T, T))
{
	try
	{
		Data* p = a.head;
		while (p)
		{
			unique(p->data,cmp);
			p = p->next;
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
bool List<T>::unique(bool (*cmp)(T,T))
{
	if (Size == 0 || Size == 1)
		return true;
	try
	{
		int index = 1;
		Data* p = head->next;
		Data* p1;
		while (p)
		{
			p1 = head;
			index++;
			while (p1 != p)
			{
				if (cmp(p1->data, p->data))
				{
					p = p->ahead;
					if (!erase(index))
					{
						return false;
					}
					index--;
					break;
				}
				p1 = p1->next;
			}
			p = p->next;
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
bool List<T>::unique(T val, bool(*cmp)(T, T))
{
	if (Size == 0)
	{
		push_back(val);
	}
	else
	{
		try
		{
			Data* p = head;
			while (p)
			{
				if (cmp(p->data, val))
					return true;
				p = p->next;
			}
			push_back(val);
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	return true;
}

template<class T>
bool List<T>::swap(int index1,int index2)
{
	if (index1 < 0 || index2 < 0 || index1 >= Size || index2 >= Size)
		return false;
	try
	{
		Data* p = At(index1 + 1);
		Data* p1 = At(index2 + 1);
		T tmp = p->data;
		p->data = p1->data;
		p1->data = tmp;
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
void List<T>::complement(List& a, bool(*cmp)(T, T))
{
	Data* p = head;
	Data* p1;
	for (int i = 0; i < Size; i++)
	{
		p = At(i + 1);
		p1 = a.head;
		for (int j = 0; j < a.size(); j++)
		{
			if (cmp(p->data, p1->data))
			{
				erase(i);
				i--;
				break;
			}
			p1 = p1->next;
		}
	}
}

template<class T>
bool List<T>::sort(int start, int final, int model, bool(*cmp)(T, T))
{
	if (start<0 || final >= Size || start>final)
	{
		return false;
	}
	switch (model)
	{
	case quick:
		return quick_sort(start, final, cmp);
	case select:
		return select_sort(start, final, cmp);
	case bubble:
		return bubble_sort(start,final,cmp);
	case shell:
		return shell_sort(start, final, cmp);
	default:
		return false;
	}
}

template<class T>
bool List<T>::select_sort(int start, int final, bool(*cmp)(T, T))
{
	Data* p = NULL;
	Data* p1;
	for (int i = start; i < final; i++)
	{
		p = (p == NULL ? At(i + 1) : p->next);
		p1 = p->next;
		for (int j = i + 1; j <= final; j++)
		{
			if (!cmp(p->data, p1->data))
			{
				swap(i, j);
			}
			p1 = p1->next;
		}
	}
	return true;
}

template<class T>
bool List<T>::quick_sort(int start,int final,bool(*cmp)(T,T))
{
	if(start < final)
	{
		Data* p = At(start + 2);
		Data* p1 = At(final + 1);
		Data* pre = p->ahead;
		int i = start + 2, j = final + 1;
		while (i <= j)
		{
			while (i <= j && cmp(p->data, pre->data))
			{
				p = p->next;
				++i;
			}
			while (i <= j && cmp(pre->data, p1->data))
			{
				p1 = p1->ahead;
				--j;
			}
			if (i <= j)
			{
				swap(p, p1);
				++i;
				p = p->next;
				--j;
				p1 = p1->ahead;
			}
		}
		swap(pre, p1);
		quick_sort(start, j - 2, cmp);
		quick_sort(j, final, cmp);
	}
	return true;
}

template<class T>
bool List<T>::bubble_sort(int start, int final, bool(*cmp)(T, T))
{
	bool flag;
	Data* p;
	for (int i = 1; i < Size; i++)
	{
		p = At(1);
		flag = true;
		for (int j = 0; j < Size - 1; j++)
		{
			if (!cmp(p->data, p->next->data))
			{
				swap(p, p->next);
				flag = false;
			}
			p = p->next;
		}
		if (flag)
			break;
	}
	return true;
}

template<class T>
bool List<T>::shell_sort(int start, int final, bool(*cmp)(T, T))
{
	int len = (int)ceil((final - start + 1) / 2.0);
	int s;
	Data* p = NULL;
	Data* p1 = NULL;
	while(len >= 1)
	{
		s = final - len;
		for (int i = start; i <= s; i++)
		{
			for (int j = i; j <= s; j += len)
			{
				p = (j == i ? At(j + 1) : p->next);
				p1 = (j == i ? At(j + len + 1) : p1->next);
				if (!cmp(p->data, p1->data))
				{
					swap(p,p1);
				}
			}
		}
		len /= 2;
	}
	return true;
}

template<class T>
bool List<T>::merge(List& a, List& b, bool(*f)(T, T))
{
	try
	{
		clear();
		Data* p1 = a.head;
		Data* p2 = b.head;
		while (p1&&p2)
		{
			if (f(p1->data, p2->data))
			{
				push_back(p1->data);
				p1 = p1->next;
			}
			else
			{
				push_back(p2->data);
				p2 = p2->next;
			}
		}
		Data* p = (p1 == NULL ? p2 : p1);
		while (p)
		{
			push_back(p->data);
			p = p->next;
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}

template<class T>
bool List<T>::merge(List& a, bool(*f)(T, T))
{
	try
	{
		Data* p1 = head;
		Data* p2 = a.head;
		while (p1&&p2)
		{
			if (f(p1->data, p2->data))
			{
				p1 = p1->next;
			}
			else
			{
				if (p1->ahead == NULL)
				{
					push_front(p2->data);
					p2 = p2->next;
				}
				else
				{
					Data* s = new Data;
					s->data = p2->data;
					s->next = p1;
					s->ahead = p1->ahead;
					p1->ahead->next = s;
					p1->ahead = s;
					p2 = p2->next;
				}
			}
		}
		while (p2)
		{
			push_back(p2->data);
			p2 = p2->next;
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}