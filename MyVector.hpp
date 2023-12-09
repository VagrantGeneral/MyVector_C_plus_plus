#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP
#include<string.h>
#include<stdlib.h> // malloc free ; exit;
#include<iostream>

template<class _Ty>	// _Ty char , int ,short ,double;// class   char *;
class MyVector {
private:
	_Ty* data; //  
	size_t cursize;//�ִ�Ԫ�ظ���
	size_t capacity;//���Ԫ�ظ���

	//���ݺ���
	bool IncSize() {
		size_t count = capacity * incsize;//�������ݺ�Ķ������
		_Ty* newdata = (_Ty*)malloc(sizeof(_Ty) * count);//Ϊ�µ����ݷ���ռ�
		if (nullptr == newdata) {
			return false;
		}
		for (int i = 0; i < cursize; ++i) {
			//newdata[i] = data[i];	 // MyVector<Int> ivec;
			new(&newdata[i]) _Ty(std::move(data[i]));//��ѡ���ƶ����죩�����⿽�������󸳸��ռ䣩
		}
		for (int i = 0; i < cursize; ++i) {
			(&data[i])->~_Ty();//��ԭ�ռ��������
		}

		free(data);�ͷſռ�
		data = newdata;//�ı�ָ��
		capacity = count;
		return true;
	}

	static const size_t initsize = 10;//��ʼ����С
	static const size_t incsize = 2;//���ݱ���
	
	//���¿ռ�����ڴ�ռ䣬�����ʼ��
	static _Ty* GetMem(size_t objsize) {
		_Ty* newdata = (_Ty*)malloc(sizeof(_Ty) * objsize);
		if (nullptr == newdata) exit(EXIT_FAILURE);
		memset(newdata, 0, sizeof(_Ty) * objsize);
		return newdata;
	}
public:
	MyVector(size_t sz = initsize)
		:data(nullptr), cursize(0), capacity(sz) {
		//data = new _Ty[capacity];
		data = GetMem(capacity);
	}

	//�������죨������ֵ����
	MyVector(const MyVector& my) :data(nullptr) {
		cursize = my.cursize;
		capacity = my.capacity;
		data = GetMem(my.capacity);

		for (int i = 0; i < cursize; ++i) {

			new(&data[i]) _Ty(my.data[i]));

		}
	}	// MyVector<int> mlist(ylist);

	//�ƶ����죨������ֵ����
	MyVector(MyVector&& my)
		:data(my.data), cursize(my.cursize), capacity(my.capacity) {
		data = nullptr;
		cursize = 0;
		capacity = 0;
	}

	//������ֵ
	MyVector& operator=(const MyVector& my) {
		cursize = my.cursize;
		capacity = my.capacity;
		data = GetMem(my.capacity);

		for (int i = 0; i < cursize; ++i) {

			new(&data[i]) _Ty(my.data[i]));

		}
	}

	//�ƶ���ֵ
	MyVector& operator=(MyVector&& my) {
		
	}

	//
	~MyVector() {
		clear();    //  heap in obj ~_Ty();
		free(data); // .heap;
		data = nullptr;
		cursize = 0;
		capacity = 0;
		//delete[]data;	 //delete data;
	}

	size_t getsize() const { return cursize; }
	size_t getcapa() const { return capacity; }
	bool empty() const { return getsize() == 0; }
	bool full() const { return getsize() == getcapa(); }

	//��ָ��λ�ò���
	bool insert(int pos, const _Ty& val) {
		if (pos < 0 || pos > cursize) {
			return false;
		}
		if (full() && !IncSize()) {
			return false;
		}

		new(&data[cursize]) = _Ty();	//�����һ��λ�õ���һ��λ�ô���_Ty�ն���

		for (int i = cursize; i > pos; --i) {
			data[i] = std::move(data[i - 1]);
		}
		data[pos] = val;
		cursize += 1;
		return true;
	}

	//
	void push_back(const _Ty& val) {
		insert(cursize, val);
	}

	//
	bool erase(const size_t pos) {
		if (pos < 1 || pos > cursize - 1) {
			return false;
		}
		cursize -= 1;
		for (int i = pos; i < cursize; ++i) {
			data[i] = std::move(data[i + 1]);
		}
		return true;
	}

	//
	void pop_back() {
		erase(cursize - 1);
	}

	//�������е�ÿһ������ִ��������������
	void clear() {
		for (int i = 0; i < cursize; ++i) {
			(&data[i])->~_Ty();
		}
		cursize = 0;
	}

	//
	void swap(MyVector& vec) {
		std::swap(this->data, vec.data);
		std::swap(this->cursize, vec.cursize);
		std::swap(this->capacity, vec.capacity);
	}

	//
	void Print() const {
		std::cout << "Capa: " << capacity << std::endl;
		std::cout << "Cur: " << cursize << std::endl;
		std::cout << "data: " << std::endl;
		for (int i = 0; i < cursize; ++i) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}

};


#endif 
