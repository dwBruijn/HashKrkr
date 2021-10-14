//
//  SHA1Algorithm.cpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "SHA1Algorithm.hpp"

SHA1Algorithm::SHA1Algorithm() : Algorithm("SHA1", 40) {}

Algorithm* SHA1Algorithm::clone() {
    return new SHA1Algorithm();
}

inline std::string SHA1Algorithm::get_hash() const {
    return hash;
}

std::string SHA1Algorithm::create_hash(std::string& plain) {
    std::stringstream ss;
    
    // hash the plaintext string
    SHA1_Init(&context);
    SHA1_Update(&context, plain.c_str(), plain.length());
    SHA1_Final(digest, &context);
    
    // convert the 20 byte digest to a 40 byte hex string
    ss << std::hex;

     for( int i = 0 ; i < hash_len / 2; i++)
         ss << std::setw(2) << std::setfill('0') << (unsigned int)digest[i];

     return ss.str();
}
