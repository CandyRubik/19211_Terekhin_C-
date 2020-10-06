#pragma once
#include <vector>
#include <algorithm>
#include <unordered_map>
typedef unsigned int uint;

enum class Trit_value {
    UNKNOWN = 0x00, // 0
    TRUE = 0x01, // 1
    FALSE = 0x02 // 2
};

class Trit_set {
public:
    explicit Trit_set(size_t capacity_ = 0); /*Default Ctor*/

    Trit_set(Trit_set const& T); /*Copy Ctor*/

    class Trit { /* Subclass */
    public:
        uint& Trit_block; // reference to 16 trits
        size_t index_in_block; // index in 16 trits
        bool is_initialized; // this field show status of initilizing trit with index index_in_block
        Trit_set* obj; // this field need to make resize if we assign Trit_vlaue::UNKNOWN

        Trit(uint& Trit_block_, size_t index_in_block_, bool is_initialized_, Trit_set* obj_); /* Ctor of subclass */

        void swap(Trit& T);

        Trit& operator= (Trit const& T);

        Trit_value operator!(); // overload for unary '!'

        Trit_value operator&(Trit_value second); // binary '&' operation

        Trit_value operator|(Trit_value second); // binary '|' operation 

        Trit_value get_value(); // get value for printing

        Trit& operator= (Trit_value value); // overload of binary '='
    };

    void swap(Trit_set& T); // special swap object function

    Trit_set& operator= (Trit_set const& T); // operator = for objects

    size_t size() const; // method which return capacity of array

    Trit operator[] (size_t index);

    Trit_set& operator!(); // unar operator '!' for set

    Trit_set operator&(Trit_set& second); // binary operator '&' for set
    Trit_set operator|(Trit_set& second); // binary operator '|' for set

    void shrink(); // this method reallocate memory

    size_t length(); // this method returns place of last !UNKNOWN trit 

    void trim(size_t last_index); // this method forgets all the contents of the array starting from the 
                                 //index passed by the argument

    size_t cardinality(Trit_value value); // this method returns quantity of Trit_value in argument
                                         // in the case of Trit_value::UNKNOWN this method returns quantity of 
                                         //Trit_value::UNKNOWN before significant trit

    std::unordered_map<Trit_value, size_t> cardinality(); // this method is overload of previous method,
                                                         // this method returns unordered_map with
                                                         // Key = Trit_value, Val = cardinality(Trit_value)
private:
    size_t capacity;
    std::vector<uint> data;
    size_t old_capacity;
    void resize(size_t new_capacity);
};