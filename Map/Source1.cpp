//#include <iostream>
//#include <map>
//#include <functional>
//#include <string>
//#include <conio.h>
//#include <memory>
//#include <stdio.h>
//
//using namespace std;
//
//template <typename T>
//struct mallocator {
//#ifdef NDEBUG
//	static const bool debug = false;
//#else
//	static const bool debug = true;
//#endif
//
//	using value_type = T;
//
//	mallocator()
//	{
//		cout << "allocator alive! hahahaha";
//	}
//
//
//	template <class U>
//	mallocator(const mallocator<U>&) {}
//
//	T* allocate(std::size_t n) {
//		if (debug) { std::cout << "allocate(" << n << ") = "; }
//		if (n <= std::numeric_limits<std::size_t>::max() / sizeof(T)) {
//			auto ptr = std::malloc(n * sizeof(T));
//			if (ptr) {
//				if (debug) { std::cout << ptr << '\n'; }
//				return static_cast<T*>(ptr);
//			}
//		}
//		if (debug) { std::cout << "[bad_alloc]\n"; }
//		throw std::bad_alloc();
//	}
//	void deallocate(T* ptr, std::size_t n) {
//		if (debug) { std::cout << "deallocate(" << ptr << ", " << n << ")\n"; }
//		std::free(ptr);
//	}
//};
//
//
////template <typename T, typename U>
////inline bool operator == (const mallocator<T>&, const mallocator<U>&) {
////	return true;
////}
////
////template <typename T, typename U>
////inline bool operator != (const mallocator<T>& a, const mallocator<U>& b) {
////	return !(a == b);
////}
//
//
//int main()
//{
//	//cout << "Hell";
//
//	//mallocator<string> eeey;
//
//	map <string, int, mallocator <pair<string, int>>> myFirstMap;
//
//	myFirstMap.insert(pair<string, int>("hahahah", 10));
//
//	//// allocator for string values 
//	//allocator<string> myAllocator;
//
//	//// allocate space for three strings 
//	//string* str = myAllocator.allocate(3);
//
//	//// construct these 3 strings 
//	//myAllocator.construct(str, "Geeks");
//	//myAllocator.construct(str + 1, "for");
//	//myAllocator.construct(str + 2, "Geeks");
//
//	//cout << str[0] << str[1] << str[2];
//
//	//// destroy these 3 strings 
//	//myAllocator.destroy(str);
//	//myAllocator.destroy(str + 1);
//	//myAllocator.destroy(str + 2);
//
//	//// deallocate space for 3 strings 
//	//myAllocator.deallocate(str, 3);
//
//	_getch();
//
//	return 0;
//}