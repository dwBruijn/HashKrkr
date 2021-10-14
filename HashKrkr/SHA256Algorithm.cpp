//
//  SHA256Algorithm.cpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "SHA256Algorithm.hpp"

SHA256Algorithm::SHA256Algorithm() : Algorithm("SHA256", 64) {}

Algorithm* SHA256Algorithm::clone() {
    return new SHA256Algorithm();
}

inline std::string SHA256Algorithm::get_hash() const {
    return hash;
}

std::string SHA256Algorithm::create_hash(std::string& plain) {
    std::stringstream ss;
    
    // hash the plaintext string
    SHA256_Init(&context);
    SHA256_Update(&context, plain.c_str(), plain.length());
    SHA256_Final(digest, &context);
    
    // convert 32 byte digest to 64 byte hex string
    ss << std::hex;
    
    for(int i = 0; i < hash_len / 2; i++)
        ss << std::setw(2) << std::setfill('0') << (unsigned int)digest[i];
    
    return ss.str();
}
