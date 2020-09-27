#pragma once
#include<iostream>

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
	Data* At(int index)//����һ��ָ���index��Ԫ�ص�ָ��(index��1��ʼ)
	{
		if (index > Size || index <= 0)
			return NULL;
		Data* p = head;
		for (int i = 2; i <= index; i++)
		{
			p = p->next;
		}
		return p;
	}
	static bool judge(T a, T b)//�ж�����Ԫ���Ƿ���ͬ�����ú�����ֻ�Էǽṹ��������Ч������unique������������
	{
		return a == b ? true : false;
	}
	static void Show(T a)//���õ�չʾ�б����ݵĺ�����ֻ�Էǽṹ��������Ч������show������
	{
		std::cout << a << " ";
	}
	static bool cmp(T a, T b)
	{
		return a <= b ? true : false;
	}
public:

	//���캯������ʼ��һ���յ��б�
	List();
	//���캯��(Ҳ�ǿ������캯��)�����б�a�е�ȫ�����ݸ��Ƶ���ǰ�б��У����������
	List(List& a);
	//���캯�������б�a�д�first��lastλ�õ����ݸ��Ƶ���ǰ�б��У����������first��1��ʼ��
	List(List& a,int first,int last);

	//�����������ͷ��б���new��ȫ���ռ�
	~List();

	//�����б�ĳ���
	int size();

	//���±�indexλ�ò�������val,����ɹ�����true�����򷵻�false��index��0��ʼ��
	bool insert(int index,T val);
	//���б�a�д�first��lastλ�õ����ݸ��Ƶ���ǰ�б��У�first��1��ʼ��
	bool insert(List& a, int first, int last);
	//���б�a�е�����ȫ�����Ƶ���ǰ�б���
	bool insert(List& a);

	//��β����������val
	bool push_back(T val);
	//��ͷ����������val
	bool push_front(T val);

	//ɾ��β��Ԫ��
	bool pop_back();
	//ɾ��ͷ��Ԫ��
	bool pop_front();

	//����б��ȫ������   ע��: ����б��Ƿǻ����������ͣ�������Լ�дҪչʾ�Ķ����ĺ�����Ȼ��Ѹú���������������show����
	void show(void(*f)(T) = Show);

	//ɾ��index������(index��0��ʼ)
	bool erase(int index);
	//ɾ��index1��index2������(index1��0��ʼ������ɾ��index2������)
	bool erase(int index1, int index2);
	//���ȫ������
	void clear();

	//����indexλ�õ����ݣ������أ����û���ҵ��򷵻ص�һ��Ԫ��(index��0��ʼ)
	T find(int index);
	//���ص�һ��Ԫ�أ�����б�Ϊ�գ��򷵻�NULL
	T front();
	//�������һ��Ԫ�أ�����б�Ϊ�գ��򷵻�NULL
	T back();

	//�ж��б��Ƿ�Ϊ�գ�������򷵻�true�������򷵻�false
	bool empty();

	//����[]�������ʵ��ͨ���±��޸����ݣ�����±����ʵ�ʳ��ȣ��򷵻ص�һ�����ݵ�����
	T& operator[](const int index);
	//������С�=�����������
	void operator=(List& a);

	//��β������һ���б�ͬʱȥ�أ�����������ִ��󣬷���false,ʹ�ú���ָ��cmp����cmp����trueʱ����ʾ����Ԫ����ͬ����Ҫȥ������һ��
	bool unique(List& a, bool(*cmp)(T, T) = judge);
	//���б�ȥ�أ�����������ִ��󷵻�fasle,ʹ�ú���ָ��cmp����cmp����trueʱ����ʾ����Ԫ����ͬ����Ҫȥ������һ��
	bool unique(bool(*cmp)(T, T) = judge);
	//��β���������ݣ���֤���ظ�������������ִ��󷵻�fasle,ʹ�ú���ָ��cmp����cmp����trueʱ����ʾ����Ԫ����ͬ����Ҫȥ������һ��
	bool unique(T val, bool(*cmp)(T, T) = judge);

	//�����±�index1���±�index2������(��0��ʼ)
	bool swap(int index1,int index2);
	
	//���������򣬽��±��start��final������final�������ݽ�����������ǽṹ�����͵����ݣ���Ҫ�Լ�д����ķ�ʽ����cmp����Ϊtrueʱ����ʾ��������Ҫ������У�����Ҫ��������
	bool sort(int start, int final, bool(*cmp)(T, T) = cmp);
	//���������򣬶��б��ȫ�����ݽ�����������ǽṹ�����͵����ݣ���Ҫ�Լ�д����ķ�ʽ����cmp����Ϊtrueʱ����ʾ��������Ҫ������У�����Ҫ��������
	bool sort(bool(*cmp)(T, T) = cmp);

	//�����A-B������ǰ����ΪA������Ĳ�������a��ΪB������A-B���㣬*cmpΪ����ָ�룬�����ж�����Ԫ���Ƿ���ͬ������жϵ��Ƿǻ����������ͣ�����Ҫ�Լ������жϺ���
	void complement(List& a, bool(*cmp)(T,T) = cmp);
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
bool List<T>::sort(int start, int final, bool(*cmp)(T, T))
{
	if (start >= final || final >= Size)
	{
		return false;
	}
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
bool List<T>::sort(bool(*cmp)(T, T))
{
	return sort(0, Size - 1, cmp);
}

template<class T>
void List<T>::complement(List& a,bool(*cmp)(T,T))
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