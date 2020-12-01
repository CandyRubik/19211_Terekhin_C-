#ifndef FACTORY_H
#define FACTORY_H
#include <unordered_map>
#include <string>

//A.Alexandrescu "Modern Desing in C++"
template<class Product, class Block, class Creator>//typename(int,long,double)
class Factory {
public:

    Product* makeBlock(const Block& name, std::ifstream &file)
    {
        auto it = creators_.find(name);
        return it->second(file);
    };

    void addCreator(const Block& name, Creator c)
    {
        creators_.insert_or_assign(name, c);
    };

    static Factory& instance()
    {
        static Factory f;
        return f;
    };
private:
    Factory() = default;
    ~Factory() = default;
    Factory(const Factory&);
    Factory& operator= (const Factory&);
    std::unordered_map<Block, Creator> creators_;
};
#endif // FACTORY_H
