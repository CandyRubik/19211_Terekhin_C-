#pragma once
#include <unordered_map>
#include <string>

//A.Alexandrescu "Modern Desing in C++"
template<class Product, class Block, class Creator>//typename(int,long,double)
class Factory {
public:

	Product* makeBlock(const Block& name) {
		auto it = creators_.find(name);
		return it->second();
	};

	void addCreator(const Block& name, Creator c) {
		creators_.insert_or_assign(name, c);
	};

	static Factory* getInstance() {
		static Factory f;//область видимости локальная,но время жизни до выхода из всей программы
		return &f;
	};
private:
	Factory() = default;
	~Factory() = default;
	Factory(const Factory&);
	Factory& operator= (const Factory&);
	std::unordered_map<Block, Creator> creators_;
};