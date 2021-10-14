//
//  main.cpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#include <iostream>
#include "MD5Algorithm.hpp"
#include "SHA256Algorithm.hpp"
#include "SHA1Algorithm.hpp"
#include "Krkr.hpp"

int main(int argc, const char * argv[]) {
    std::string hash = "";
    std::string dictionary_path = "";
    unsigned int thread_count = 0;
    Algorithm* algorithm = nullptr;
    
    // read hash and identify the hashing algorithm
    while(algorithm == nullptr) {
        std::cout << "[~] Enter hash: ";
        std::cin >> hash;
        
        if(hash.length() == 32) {               // MD5
            algorithm = new MD5Algorithm();
        } else if(hash.length() == 40) {        // SHA1
            algorithm = new SHA1Algorithm();
        } else if(hash.length() == 64) {        // SHA256
            algorithm = new SHA256Algorithm();
        } else {
            std::cout << "[!] Unknown hashing algorithm" << std::endl;
            continue;
        }
        std::cout << "[+] Hashing algorithm: " << *algorithm << std::endl;
    }
    
    // read dictionary path
    std::cout << "[~] Enter Dictionary path: ";
    std::cin >> dictionary_path;
    
    // read thread count
    while(thread_count <= 0 || thread_count > 8) {
        std::cout << "[~] Enter thread count: ";
        std::cin >> thread_count;
        
        if(thread_count < 0 || thread_count > 8) {
            std::cout << "[!] keep thread count between 1 and 8" << std::endl;
        }
    }
    
    Krkr krkr(thread_count, algorithm);     // Create Krkr instance
    
    if(krkr.load_dictionary(dictionary_path)) {
        std::string plaintext = krkr.start(hash);
        if(plaintext.size() > 0) {
            std::cout << std::endl << std::endl << std::left << std::setw(20) << "[+] Hash cracked: " << std::setw(4) << plaintext << std::endl << std::endl;
        } else {
            std::cout << std::endl << std::endl << "[!] Hash not found in dictionary" << std::endl << std::endl;
        }
    }
    
    return 0;
}

