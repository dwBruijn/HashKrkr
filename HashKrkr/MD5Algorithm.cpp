//
//  MD5Algorithm.cpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "MD5Algorithm.hpp"

MD5Algorithm::MD5Algorithm() : Algorithm("MD5", 32) {}

Algorithm* MD5Algorithm::clone() {
    return new MD5Algorithm();
}

inline std::string MD5Algorithm::get_hash() const {
    return hash;
}

std::string MD5Algorithm::create_hash(std::string& plain) {
    std::stringstream ss;
    
    // hash the plaintext string
    MD5_Init(&context);
    MD5_Update(&context, plain.c_str(), plain.length());
    MD5_Final(digest, &context);
    
    // convert the 16 byte digest to a 32 byte hex string
    ss << std::hex;

     for( int i = 0 ; i < hash_len / 2; i++)
         ss << std::setw(2) << std::setfill('0') << (unsigned int)digest[i];

     return ss.str();
}
