#include <iostream>
#include <fstream>
class Array {
public:
	explicit Array(size_t initial_allocated = 1) : size_(initial_allocated), mem(new int[size_]), now_index(0) 
	{
		for (int i = 0; i < size_; i++)
		{
			mem[i] = 0;
		}
	}

	Array(Array const& a) : size_(a.size_), mem(new int[size_]), now_index(a.now_index)
	{
		for (int i = 0; i < size_; i++)
		{
			mem[i] = a.mem[i];
		}
	}

	~Array()
	{
		delete[] mem;
	}

	Array& operator=(Array const& a)
	{
		if (this != &a)
		{
			Array(a).swap(*this);
		}
		return *this;
	}

	void swap(Array& a)
	{
		std::swap(size_, a.size_);
		std::swap(now_index, a.now_index);
		std::swap(mem, a.mem);
	}

	void push_back(int number) 
	{
		if (size_ == now_index + 1) {
			resize(size_ * 2);
		}
		mem[now_index++] = number;
	}

	void read_array_from_file() {
		std::ifstream in("input.txt");
		if (!in.is_open()) {
			return;
		}
		Array a(10);
		while (in >> mem[now_index++]) {
			if (size_ == now_index + 1) {
				resize(size_ * 2);
			}
		}
		in.close();
	}

	void resize(size_t nsize)
	{
		Array t(nsize);
		size_t n = nsize > size_ ? size_ : nsize;
		for (size_t i = 0; i < n; i++)
			t.mem[i] = mem[i];
		swap(t);
	}

	size_t size() const 
	{ 
		return now_index + 1;
	}

	int & operator[](const size_t i)
	{
		return mem[i];
	}

	int& get(size_t i)
	{
		return mem[i];
	}
private:
	size_t now_index;
	size_t size_;
	int* mem;
};

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}