#include "Trit_set.h"

Trit_set::Trit_set(size_t capacity_) : capacity(capacity_), data(std::vector<uint>(ceil((double)capacity * 2 / sizeof(uint) / 8))), old_capacity(capacity) /*Default Ctor*/
{
	std::fill(std::begin(data), std::end(data), 0); // fill the array '0'
}

Trit_set::Trit_set(Trit_set const& T) : capacity(T.capacity), data(std::vector<uint>(ceil((double)capacity * 2 / sizeof(uint) / 8))), old_capacity(T.old_capacity) /*Copy Ctor*/
{
	std::copy(T.data.begin(), T.data.end(), data.begin()); // copy from T to *this
}


Trit_set::Trit::Trit(uint& Trit_block_, size_t index_in_block_, bool is_initialized_, Trit_set* obj_) : Trit_block(Trit_block_), index_in_block(index_in_block_), is_initialized(is_initialized_), obj(obj_) {} /* Ctor of subclass */

void Trit_set::Trit::swap(Trit& T)
{
	std::swap(T.Trit_block, Trit_block);
	std::swap(T.index_in_block, index_in_block);
	std::swap(T.is_initialized, is_initialized);
}

Trit_set::Trit& Trit_set::Trit::operator= (Trit const& T)
{
	if (this != &T)
		Trit(T).swap(*this);
	return *this;
}

Trit_value Trit_set::Trit::operator!() // overload for unary '!'
{
	switch (this->get_value())
	{
	case Trit_value::UNKNOWN:
		return Trit_value::UNKNOWN;
	case Trit_value::TRUE:
		return Trit_value::FALSE;
	case Trit_value::FALSE:
		return Trit_value::TRUE;
	}
}

Trit_value Trit_set::Trit::operator&(Trit_value second) // binary '&' operation
{
	switch (this->get_value())
	{
	case Trit_value::UNKNOWN:
		switch (second)
		{
		case Trit_value::UNKNOWN:
			return Trit_value::UNKNOWN;
			break;
		case Trit_value::TRUE:
			return Trit_value::UNKNOWN;
			break;
		case Trit_value::FALSE:
			return Trit_value::FALSE;
			break;
		}
		break;
	case Trit_value::TRUE:
		switch (second)
		{
		case Trit_value::UNKNOWN:
			return Trit_value::UNKNOWN;
			break;
		case Trit_value::TRUE:
			return Trit_value::TRUE;
			break;
		case Trit_value::FALSE:
			return Trit_value::FALSE;
			break;
		}
		break;
	case Trit_value::FALSE:
		switch (second)
		{
		case Trit_value::UNKNOWN:
			return Trit_value::FALSE;
			break;
		case Trit_value::TRUE:
			return Trit_value::FALSE;
			break;
		case Trit_value::FALSE:
			return Trit_value::FALSE;
			break;
		}
		break;
	}
}

Trit_value Trit_set::Trit::operator|(Trit_value second) // binary '|' operation 
{
	switch (this->get_value())
	{
	case Trit_value::UNKNOWN:
		switch (second)
		{
		case Trit_value::UNKNOWN:
			return Trit_value::UNKNOWN;
			break;
		case Trit_value::TRUE:
			return Trit_value::TRUE;
			break;
		case Trit_value::FALSE:
			return Trit_value::UNKNOWN;
			break;
		}
	case Trit_value::TRUE:
		switch (second)
		{
		case Trit_value::UNKNOWN:
			return Trit_value::TRUE;
			break;
		case Trit_value::TRUE:
			return Trit_value::TRUE;
			break;
		case Trit_value::FALSE:
			return Trit_value::TRUE;
			break;
		}
	case Trit_value::FALSE:
		switch (second)
		{
		case Trit_value::UNKNOWN:
			return Trit_value::UNKNOWN;
			break;
		case Trit_value::TRUE:
			return Trit_value::TRUE;
			break;
		case Trit_value::FALSE:
			return Trit_value::FALSE;
			break;
		default:
			break;
		}
		break;
	}
}

Trit_value Trit_set::Trit::get_value() // get value for printing
{
	if (!is_initialized)
	{
		obj->resize(obj->old_capacity);
		return Trit_value::UNKNOWN;
	}
	uint value = 3;
	value &= Trit_block >> ((index_in_block) * 2); // get value from block of 16 trits 
	switch (value)
	{
	case 0:
		return Trit_value::UNKNOWN;
	case 1:
		return Trit_value::TRUE;
	case 2:
		return Trit_value::FALSE;
	}
}

Trit_set::Trit& Trit_set::Trit::operator= (Trit_value value) // overload of binary '='
{
	if (value == Trit_value::UNKNOWN && !this->is_initialized)
	{
		obj->resize(obj->old_capacity);
		return *this;
	}
	uint uvalue = static_cast<uint>(value) << ((index_in_block) * 2); // shift value to trit position
	Trit_block &= ~(3 << (index_in_block * 2)); // nullify trit value
	Trit_block |= uvalue; // write new trit value
	return *this;
}

void Trit_set::swap(Trit_set& T) // special swap object function
{
	std::swap(capacity, T.capacity);
	std::swap(data, T.data);
}

Trit_set& Trit_set::operator= (Trit_set const& T) // operator = for objects
{
	if (this != &T)
	{
		Trit_set(T).swap(*this);
	}
	return *this;
}

size_t Trit_set::size() const // method which return capacity of array
{
	return this->capacity;
}

Trit_set::Trit Trit_set::operator[] (size_t index)
{
	bool initialized = (index >= capacity) ? 0 : 1;
	if (!initialized)
	{
		old_capacity = capacity;
		resize(index + 1);
	}
	Trit a(data[index / 16], index % 16, initialized, this);
	return a;
}

Trit_set& Trit_set::operator!() // unar operator '!' for set
{
	for (size_t i = 0; i < capacity; i++) {
		Trit a(data[i / 16], i % 16, 1, this);
		a = !a;
	}
	return *this;
}

Trit_set Trit_set::operator&(Trit_set& second) // binary operator '&' for set
{
	size_t capacity_fot_new_object = (this->size() > second.size()) ? this->size() : second.size();
	Trit_set new_object(capacity_fot_new_object);
	for (size_t i = 0; i < capacity_fot_new_object; i++)
	{
		bool first_in = (i >= this->size()) ? 0 : 1;
		bool second_in = (i >= second.size()) ? 0 : 1;
		Trit first_trit(data[i / 16], i % 16, first_in, this);
		Trit second_trit(second.data[i / 16], i % 16, second_in, &second);
		Trit result(new_object.data[i / 16], i % 16, 1, &new_object);
		result = first_trit & second_trit.get_value();
	}
	return new_object;
}

Trit_set Trit_set::operator|(Trit_set& second) // binary operator '|' for set
{
	size_t capacity_fot_new_object = (this->size() > second.size()) ? this->size() : second.size();
	Trit_set new_object(capacity_fot_new_object);
	for (size_t i = 0; i < capacity_fot_new_object; i++)
	{
		bool first_in = (i >= this->size()) ? 0 : 1;
		bool second_in = (i >= second.size()) ? 0 : 1;
		Trit first_trit(data[i / 16], i % 16, first_in, this);
		Trit second_trit(second.data[i / 16], i % 16, second_in, &second);
		Trit result(new_object.data[i / 16], i % 16, 1, &new_object);
		result = first_trit | second_trit.get_value();
	}
	return new_object;
}

void Trit_set::shrink() // this method reallocate memory
{
	for (long long i = capacity - 1; i >= 0; i--)
	{
		Trit a(data[i / 16], i % 16, 1, this);
		if (a.get_value() != Trit_value::UNKNOWN)
		{
			resize(i + 1);
			return;
		}
	}
	resize(old_capacity);
}

size_t Trit_set::length() // this method returns place of last !UNKNOWN trit 
{
	for (long long i = capacity - 1; i >= 0; i--)
	{
		Trit a(data[i / 16], i % 16, 1, this);
		if (a.get_value() != Trit_value::UNKNOWN)
		{
			return i + 1;
		}
	}
}

void Trit_set::trim(size_t last_index) // this method forgets all the contents of the array starting from the 
							 //index passed by the argument
{
	resize(last_index + 1);
}

size_t Trit_set::cardinality(Trit_value value) // this method returns quantity of Trit_value in argument
									 // in the case of Trit_value::UNKNOWN this method returns quantity of 
									 //Trit_value::UNKNOWN before significant trit
{
	size_t cardinality = 0;
	if (value == Trit_value::UNKNOWN)
	{
		for (size_t i = 0; i < capacity; i++)
		{
			Trit a(data[i / 16], i % 16, 1, this);
			if (a.get_value() == Trit_value::UNKNOWN)
			{
				cardinality++;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		for (size_t i = 0; i < capacity; i++)
		{
			Trit a(data[i / 16], i % 16, 1, this);
			if (a.get_value() == value)
			{
				cardinality++;
			}
		}
	}
	return cardinality;
}

std::unordered_map<Trit_value, size_t> Trit_set::cardinality() // this method is overload of previous method,
													 // this method returns unordered_map with
													 // Key = Trit_value, Val = cardinality(Trit_value)
{
	std::unordered_map<Trit_value, size_t> trit_info;
	trit_info.insert(std::make_pair(Trit_value::TRUE, cardinality(Trit_value::TRUE)));
	trit_info.insert(std::make_pair(Trit_value::FALSE, cardinality(Trit_value::FALSE)));
	trit_info.insert(std::make_pair(Trit_value::UNKNOWN, cardinality(Trit_value::UNKNOWN)));
	return trit_info;
}

void Trit_set::resize(size_t new_capacity)
{
	if (new_capacity != this->capacity)
	{
		capacity = new_capacity;
		data.resize(ceil((double)capacity * 2 / sizeof(uint) / 8));
	}
}