#include <iostream>

template<typename A>
class SmartPtr {
public:
	SmartPtr() = default;
	SmartPtr(A * a) : a_(a) {}
	~SmartPtr() { delete a_; }
	
	SmartPtr(const SmartPtr&) = delete;
	SmartPtr& operator= (const SmartPtr&) = delete;


	A& operator* () { return *a_; }
	A* operator-> () { return a_; }
	A* release () {/* отдает владение указателем |a_| */ 
		A* a = a_;
		a_ = nullptr;
		return a;
	}
	void reset (A *x) {/* берёт владение указателем |x|*/
		delete a_;
		a_ = x;
	}
	A* get() { return a_; }

private:
	A* a_ = nullptr;
};


int main()
{
	int array[2] = { 5, 6 };
	SmartPtr<int> p1(array);

	return 0;
}