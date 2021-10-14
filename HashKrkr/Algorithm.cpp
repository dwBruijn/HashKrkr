//
//  Algorithm.cpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#include "Algorithm.hpp"

Algorithm::Algorithm(std::string name, unsigned int hash_len) : name(name), hash_len(hash_len) {}

inline std::string Algorithm::get_name() const {
    return name;
}

inline unsigned int Algorithm::get_hash_len() const {
    return hash_len;
}

std::ostream& operator<<(std::ostream& os, const Algorithm& algo) {
    return os << algo.name;
}
