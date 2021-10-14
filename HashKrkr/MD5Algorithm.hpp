//
//  MD5Algorithm.hpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#ifndef MD5Algorithm_hpp
#define MD5Algorithm_hpp

#include "pch.hpp"

class MD5Algorithm : public Algorithm {
private:
    MD5_CTX context;
    // 16 bytes MD5 hash
    unsigned char digest[16];
    // the 32 bytes hex representation of the MD5 hash
    std::string hash;
    
public:
    MD5Algorithm();
    
    std::string get_hash() const;
    
    virtual std::string create_hash(std::string&);
    virtual Algorithm* clone();
};

#endif /* MD5Algorithm_hpp */
