#pragma once

#include <tuple>
#include <iostream>

template <class Tuple, std::size_t size>
struct TupleSetter {
    static void print(const Tuple& t) {
        TupleSetter<Tuple, size - 1>::print(t);
        std::cout << ", " << std::get<size - 1>(t);
    }
};

template <class Tuple>
struct TupleSetter<Tuple, 1> {
    static void print(const Tuple& t) { std::cout << std::get<0>(t); }
};

template <class... Args>
void operator<<(std::ostream& out, const std::tuple<Args...>& t) {
    TupleSetter<decltype(t), sizeof...(Args)>::print(t);
}
