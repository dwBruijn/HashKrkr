//
//  Algorithm.hpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "pch.hpp"

class Algorithm {
protected:
    std::string name;
    unsigned int hash_len;
    
public:
    Algorithm(std::string, unsigned int);
    virtual ~Algorithm() = default;
    virtual Algorithm* clone() = 0;
    
    
    std::string get_name() const;
    unsigned int get_hash_len() const;
    
    virtual std::string create_hash(std::string&) = 0;
    
    friend std::ostream& operator<<(std::ostream&, const Algorithm&);
};


#endif /* Algorithm_hpp */
