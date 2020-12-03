#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "Printer.h"

template <class... Args>
class CSVParser {
    std::ifstream file;
    int lines_to_skip;
    int lines_in_file;
    char separator;
    char guard;
    std::vector<std::tuple<Args...>> data;
    int find_line_count();
    void findLastLine();
    void castOff();
    std::vector<std::string> makeVectorOfArgs(const std::string& line);

public:
    class CSVIterator {
        friend class CSVParser;

        CSVParser<Args...>* parent;
        std::ifstream* input;
        std::string data;
        int index;

    public:
        explicit CSVIterator(CSVParser<Args...>& parent_)
            : parent(&parent_), input(&parent_.file), index(0) {
            parent->castOff();
            for (int i = 0; i <= parent->lines_to_skip; i++) {
                getline(*input, data);
            }
        }

        bool operator==(const CSVIterator& other) {
            if (this->index == other.index)
                return true;
            else
                return false;
        }

        bool operator!=(const CSVIterator& other) { return !(*this == other); }

        CSVIterator operator++() {
            index++;
            if (index > parent->lines_in_file) {
                index = parent->lines_in_file;
                return (*this);
            }

            parent->castOff();
            for (int i = 0; i <= index; i++) {
                getline(*input, data);
            }

            return (*this);
        }

        CSVIterator operator++(int) {
            CSVIterator temp = *this;
            ++(*this);
            return temp;
        }

        CSVIterator operator--() {
            index--;
            if (index < 0) {
                index = 0;
            }

            parent->castOff();

            for (int i = 0; i < index + 1; i++) {
                getline(*input, data);
            }
            return (*this);
        }

        CSVIterator operator--(int) {
            CSVIterator temp = *this;
            --(*this);
            return temp;
        }

        CSVIterator& operator=(const CSVIterator& other) {
            if (this == &other) {
                return *this;
            }
            this->data = other.data;
            this->index = other.index;
            this->parent = other.parent;
            this->input = other.input;
            return *this;
        }

        std::string operator*() { return data; }
    };

    CSVIterator begin() {
        CSVIterator result(*this);
        return result;
    }

    CSVIterator end() {
        CSVIterator result(*this);
        findLastLine();
        getline(file, result.data);
        result.index = lines_in_file;
        return result;
    }

    explicit CSVParser(const std::string& filename, int indent_ = 0,
        char separator_ = ',');

    ~CSVParser();

    void parse();

    int getNumberOfLines();

    std::vector<std::tuple<Args...>> get();

private:
    std::tuple<Args...> makeTuple(CSVIterator& iterator);
};

template <class... Args>
CSVParser<Args...>::CSVParser(const std::string& filename, int indent_,
    char separator_)
    : lines_to_skip(indent_), separator(separator_), guard('\"') {
    file.open(filename.c_str());
    if (!file) throw "Can't open file " + filename;

    if (lines_to_skip < 0) throw "Indent can't be less then 0!";

    lines_in_file = find_line_count();

    if (lines_to_skip > lines_in_file)
        throw "Indent can't be more then text length";

    lines_to_skip = indent_;
}

template <class... Args>
CSVParser<Args...>::~CSVParser() {
    file.close();
}

template <class... Args>
int CSVParser<Args...>::getNumberOfLines() {
    return lines_in_file;
}

template <class... Args>
std::vector<std::tuple<Args...>> CSVParser<Args...>::get() {
    return data;
}

template <class... Args>
int CSVParser<Args...>::find_line_count() {
    int count = 0;
    std::string line;

    while (!file.eof()) {
        getline(file, line);
        count++;
    }

    castOff();
    return count;
}

template <class... Args>
void CSVParser<Args...>::castOff() {
    file.clear();
    file.seekg(0, std::ios_base::beg);
}

template <class... Args>
void CSVParser<Args...>::findLastLine() {
    file.seekg(-1, std::ios_base::end);
    bool keepLooping = true;
    while (keepLooping) {
        char ch;
        file.get(ch);

        if ((int)file.tellg() <= 1) {
            file.seekg(0);
            keepLooping = false;
        }
        else if (ch == '\n') {
            keepLooping = false;
        }
        else {
            file.seekg(-2, std::ios_base::cur);
        }
    }
}

template <class... Args>
void CSVParser<Args...>::parse() {
    CSVParser<Args...>::CSVIterator iterator(*this);

    while (iterator != end()) {
        data.push_back(makeTuple(iterator));
        ++iterator;
    }
}

template <class... Args, size_t... index>
std::tuple<Args...> parse(std::vector<std::string> const& values,
    std::index_sequence<index...>) {
    return { stringToAny<Args>(values[index])... };
}

template <class... Args>
std::tuple<Args...> parseVector(std::vector<std::string> const& values) {
    return parse<Args...>(values, std::make_index_sequence<sizeof...(Args)>{});
}

template <class... Args>
std::vector<std::string> CSVParser<Args...>::makeVectorOfArgs(
    const std::string& line) {
    char c = 0;
    std::string buffer;
    std::vector<std::string> value;

    for (int i = 0; i < line.size() + 1; i++) {
        c = line[i];
        if (c == '%' || c == ' ') {
            continue;
        }

        if (c == guard) {
            c = line[++i];
            while (c != guard) {
                buffer += c;
                c = line[++i];
            }
            c = line[++i];
        }
        if (c == separator || c == '\n' || c == '\0') {
            value.push_back(buffer);
            buffer.clear();
        }
        else
            buffer += c;
    }
    return value;
}

template <class... Args>
std::tuple<Args...> CSVParser<Args...>::makeTuple(CSVIterator& iterator) {
    const std::string line = (*iterator);
    std::vector<std::string> value = makeVectorOfArgs(line);

    try {
        if (value.size() != sizeof...(Args)) throw "Bad count of Args";
    }
    catch (const char* error) {
        std::cerr << (std::string)error + " in line " +
            std::to_string(iterator.index + 1);
    }

    auto tuple = parseVector<Args...>(value);
    return tuple;
}

template <class T>
T stringToAny(std::string const& s);
template <>
int stringToAny<int>(std::string const& s) {
    return std::stoi(s);
}
template <>
long stringToAny<long>(std::string const& s) {
    return std::stol(s);
}
template <>
float stringToAny<float>(std::string const& s) {
    return std::stof(s);
}
template <>
double stringToAny<double>(std::string const& s) {
    return std::stod(s);
}
template <>
std::string stringToAny<std::string>(std::string const& s) {
    return s;
}