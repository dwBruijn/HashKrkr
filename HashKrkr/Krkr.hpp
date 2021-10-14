//
//  Krkr.hpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#ifndef Krkr_hpp
#define Krkr_hpp

#include "pch.hpp"

class Krkr {
private:
    // number of hashing threads
    const unsigned int thread_count;
    
    // vector to stop the thread pool
    std::vector<std::thread> thread_pool;
    
    // atomic bool to stop all runniing threads when the hash is matched to a plaintext string
    std::atomic<bool> found = false;
    
    // vector to store the plaintext strings loaded from the dictionary file
    std::vector<std::string> dictionary;
    
    // Algorithm pointer to store the algorithm used for cracking the provided hash
    Algorithm* algorithm;
    
    // string to store the plaintext string that matched the hash
    std::string matched;
    
    // Mutex and Conditional Variable to ensure that the threads dont run until the dictionary is loaded into memory
    std::mutex dictionary_mutex;
    std::condition_variable cv;
    
    // function used to create smaller size vectors to be fed to each thread instead of feeding the entire dictionary vector to all threads
    std::vector<std::string> slice_vector(std::vector<std::string> const, const unsigned long, const unsigned long);
    
    // thread function used to hash the plaintext strings in the dictionary slice and compare the hashed values to the provided hash
    void compare_hashes(std::vector<std::string>, std::string);
    
    template<typename Worker> void addWorker(Worker &&);
    
public:
    Krkr(const int, Algorithm*);
    ~Krkr();
    
    // function used to start hashing threads
    std::string start(std::string);
    
    // function used to load a dictionary file containing plaintext strings into memroy
    bool load_dictionary(const std::string);
};

#endif /* Krkr_hpp */
