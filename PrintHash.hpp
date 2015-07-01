#ifndef PRINTHASH_HPP
#define PRINTHASH_HPP

#include <iostream>
#include "HashMap.hpp"

class PrintHash{
public:
    void print(HashMap &Hashy);
    PrintHash();

private:
    std::string line, input, key, value;
    bool debug;

};

#endif //PRINTHASH_HPP
