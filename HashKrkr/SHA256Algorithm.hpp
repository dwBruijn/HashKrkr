//
//  SHA256Algorithm.hpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#ifndef SHA256Algorithm_hpp
#define SHA256Algorithm_hpp

#include "pch.hpp"

class SHA256Algorithm : public Algorithm {
private:
    SHA256_CTX context;
    // 32 bytes SHA256 hash
    unsigned char digest[32];
    // the 32 bytes hex representation of the SHA256 hash
    std::string hash;
    
public:
    SHA256Algorithm();
    
    std::string get_hash() const;
    
    virtual std::string create_hash(std::string&);
    virtual Algorithm* clone();
};

#endif /* SHA256Algorithm_hpp */
