#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <conio.h>
#include <memory>
#include <stdio.h>

using namespace std;

template <typename T>
struct AllocBuffer
{
	AllocBuffer<T>* next;
	uint8_t* mem;
	size_t size;
	size_t offset;
	long int ptr_counter;
};


template <typename T>
struct mallocator {
	const int BUFFER_SIZE = 1024*1024;

	using value_type = T;
	AllocBuffer<T>* rootBuffer;
	
	mallocator(){
		rootBuffer = nullptr;
		cout << "Allocator created: " << (int)this << "\n";
	}

	
	template <class U>
	mallocator(mallocator<U>& other) {
		rootBuffer = (AllocBuffer<T>*)other.rootBuffer;
		rootBuffer->ptr_counter++;														// Проблемы с многопоточностью?
		cout << "copy to " << (int)this << " from " << (int)&other << "\n";
	}

	AllocBuffer<T>* createBuffer()
	{
		cout << "create Buffer = ";
		auto ptr = malloc(sizeof(AllocBuffer<T>) + BUFFER_SIZE);
		if (ptr) {
			cout << ptr << '\n';

			AllocBuffer<T>* buff_ptr = reinterpret_cast<AllocBuffer<T>*>(ptr);
			buff_ptr->size = BUFFER_SIZE;
			buff_ptr->mem = reinterpret_cast<uint8_t *>(ptr) + sizeof(AllocBuffer<T>);
			buff_ptr->next = nullptr;
			buff_ptr->offset = 0;
			buff_ptr->ptr_counter = 1;

			return	buff_ptr;
		}
		cout << "[bad_alloc_buff]\n";
		throw std::bad_alloc();
	}

	T* PlaceInBuffer(AllocBuffer<T>* buffer, int n)
	{
		size_t size = n * sizeof(T);

		if (size > buffer->size)
		{
			cout << "[big_memory_needs]\n";
			throw std::bad_alloc();
		}

		if (buffer->offset + size <= buffer->size)
		{
			auto ptr = reinterpret_cast<T*>(buffer->mem + buffer->offset);			

			buffer->offset += size;
			cout << "Placed " << size << " bytes by alloc: " << int(this) << "\n";

			return ptr;
		}
		return nullptr;
	}

	T* allocate(std::size_t n) {
		if (rootBuffer == nullptr)
			rootBuffer = createBuffer();

		auto currBuff = rootBuffer;
		T* ptr;

		while (true)
		{
			ptr = PlaceInBuffer(currBuff, n);
			if (ptr == nullptr)
			{
				if (currBuff->next != nullptr)
				{
					currBuff = currBuff->next;
					continue;
				}
				else
				{
					auto newBuff = createBuffer();
					currBuff->next = newBuff;
					currBuff = newBuff;
					continue;
				}				
			}
			break;
		}
		return ptr;
	}
	
	~mallocator()
	{
		cout << "delete alloc: " << int(this) << "\n";
		rootBuffer->ptr_counter--;

		if (rootBuffer->ptr_counter == 0)
		{
			cout << "Start delete buffers\n";

			auto currBuff = rootBuffer;

			while (currBuff != nullptr)
			{
				auto next = currBuff->next;
				cout << "delete buff: " << currBuff << endl;
				free(currBuff);
				currBuff = next;
			}
		}
	}

	void deallocate(T* ptr, std::size_t n) {}
};


struct cmpByInt
{
	bool operator()(const int& a, const int&b) const
	{
		return a < b;
	}
};

int main()
{
	//cout << "Hell";

	auto m = map<int, int, cmpByInt, mallocator<pair<int, int>>>();

	m[5] = 4;
	m[2] = 1;

	m.~map();

	_getch();

	return 0;
}