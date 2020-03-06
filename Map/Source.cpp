//#include <iostream>
//#include <memory>
//
//using namespace std;
//
//struct linear_allocator_t
//{
//	void* base_pointer;
//	size_t size;
//	size_t offset;
//
//	int la_init(linear_allocator_t* allocator, size_t memory_size)
//	{
//		if (memory_size == 0)
//			return 0;
//
//		allocator->offset = 0;
//		allocator->size = memory_size;
//		allocator->base_pointer = malloc(memory_size);
//		return allocator->base_pointer != NULL;
//	}
//
//	void la_allocate(linear_allocator_t* allocator, size_t allocated_size)
//	{
//		// Проверяем на достаточное количество памяти для выделения
//		if (allocator->offset + allocated_size > allocator->size)
//			return NULL;
//
//		// Проверяем на не нулевой размер и на выравнивание
//		if ((allocated_size == 0) || (allocator->size % allocated_size != 0))
//			return NULL;
//
//		size_t allocated_pointer = (size_t)allocator->base_pointer + allocator->offset;
//		allocator->offset += allocated_size;
//		return (void*)allocated_pointer;
//	}
//
//	// Данный аллокатор не поддерживает данную операцию(функция добавлена в качестве пояснения о существовании текущей операции)
//	void la_free(linear_allocator_t* allocator, void* pointer)
//	{
//		assert(false && "Current allocator does not support current method. Use la_reset()");
//	}
//
//	void la_reset(linear_allocator_t* allocator)
//	{
//		free(allocator->base_pointer);
//	}
//};
//
//typedef struct linear_allocator_t linear_allocator_t;
//
//struct vector_4d_t
//{
//	double x, y, z, w;
//};
//
//typedef struct vector_4d_t vector_4d_t;
//
//int main()
//{
//	// В данном примере фрагментация отсутствует
//	linear_allocator_t allocator;
//	la_init(&allocator, sizeof(vector_4d_t) * 100);
//	for (int32_t i = 0; i < 100; i++)
//	{
//		vector_4d_t* vector = (vector_4d_t*)la_allocate(&allocator, sizeof(vector_4d_t));
//		vector->x = vector->y = vector->z = vector->w = i;
//	}
//	la_reset(&allocator);
//	return EXIT_SUCCESS;
//}