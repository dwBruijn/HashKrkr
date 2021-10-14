//
//  SHA1Algorithm.hpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#ifndef SHA1Algorithm_hpp
#define SHA1Algorithm_hpp

#include "pch.hpp"

class SHA1Algorithm : public Algorithm {
private:
    SHA_CTX context;
    // 20 bytes SHA1 hash
    unsigned char digest[20];
    // the 40 bytes hex representation of the SHA1 hash
    std::string hash;
    
public:
    SHA1Algorithm();
    
    std::string get_hash() const;
    
    virtual std::string create_hash(std::string&);
    virtual Algorithm* clone();
};


#endif /* SHA1Algorithm_hpp */
