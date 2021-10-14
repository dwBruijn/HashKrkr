//
//  Krkr.cpp
//  HashKrkr
//
//  Created by dwBruijn on 12/24/20.
//

#include "Krkr.hpp"

Krkr::Krkr(int thread_count, Algorithm* algorithm) : thread_count(thread_count), algorithm(algorithm) {
    thread_pool = std::vector<std::thread>(thread_count);
}

Krkr::~Krkr() {
    delete algorithm;
}

std::vector<std::string> Krkr::slice_vector(std::vector<std::string> const dictionary, const unsigned long start, const unsigned long end) {
    std::vector<std::string>::const_iterator first = dictionary.cbegin() + start;
    std::vector<std::string>::const_iterator last = dictionary.cbegin() + end;
    
    return std::vector<std::string>(first, last);
}

bool Krkr::load_dictionary(const std::string dictionary_path) {
    std::ifstream in(dictionary_path, std::ios::in);
    std::string line;
    
    if(!in.is_open()) {
        std::cout << "[!] Failed to open dictionary file: " << dictionary_path << std::endl;
        return false;
    } else {
        std::cout << "[~] Reading dictionary file content into memory..." << std::endl;
    }
    
    while(getline(in, line)) {
        if(line != "") {
            dictionary.emplace_back(line);
        }
    }
    std::cout << "[+] Done" << std::endl;
    
    in.close();
    
    std::unique_lock<std::mutex> lck(dictionary_mutex); // unlock dictionary mutex to start the hashing threads
    cv.notify_all();
    
    return !dictionary.empty();
}

void Krkr::compare_hashes(std::vector<std::string> dictionary_slice, std::string hash) {
    Algorithm* algorithm_clone = algorithm->clone();        // create a seperate instance of Algorithm for every thread to make it more thread safe
    std::string plaintext;
    
    for(int i = 0; i < dictionary_slice.size() && !found; i++) {
        plaintext = dictionary_slice[i];        // fetch a string from the dictionary to be hashed
        if(algorithm_clone->create_hash(plaintext) == hash) {
            matched = plaintext;        // found
            found = true;       // update atomic bool to stop the hashing threads
            break;
        }
    }
    
    delete algorithm_clone;
}

std::string Krkr::start(std::string hash) {
    if(found) {
        throw new std::invalid_argument("Instance of Krkr can only be used once, another instance must be created");
        return std::string();
    }
    
    std::unique_lock<std::mutex> lck(dictionary_mutex);     // lock dictionary mutex
    while(dictionary.size() == 0) {
        cv.wait(lck);       // wait while the dictionary is empty
    }
    
    std::cout << std::left << std::setw(20) << "[+] Threads: " << std::setw(4) << thread_count << std::endl;
        std::cout << std::left << std::setw(20) << "[+] Algorithm: " << std::setw(4) << *algorithm << std::endl;
        std::cout << std::left << std::setw(20) << "[+] Hash: " << std::setw(4) << hash << std::endl;
    
    std::transform(hash.begin(), hash.end(), hash.begin(), ::tolower);      // transform the provided hex hash to lower case
    
    std::cout << "[~] Cracking..." << std::endl;
    
    for(unsigned long thread_id = 0, start_index = 0; thread_id < thread_count; thread_id++) {       // loop over threads
        unsigned long end_index = start_index + (dictionary.size() / thread_count + (thread_id < dictionary.size() % thread_count ? 1 : 0));
        
        addWorker([=] {
            compare_hashes(slice_vector(dictionary, start_index, end_index), hash);
        });
        start_index = end_index;
    }
    
    for(auto&& thread : thread_pool) {      // loop over the thread pool
        if(thread.joinable()) {     // if thread is joinable
            thread.join();      // join it
        }
    }
    
    return matched;
}

// function used to add a new worker function to the thread pool
template<typename Worker> void Krkr::addWorker(Worker&& function) {
    // find a thread that ended
    for(auto&& thread : thread_pool) {
        if(thread.joinable()) {
            continue;       // thread still running so check another
        }
        thread = std::thread(function);     // start function in this thread
        return;
    }
    
    // if all threads are running wait for one to end
    for(auto&& thread : thread_pool) {
        if(!thread.joinable()) {        // dead thread or already joined
            continue;
        }
        thread.join()  ;     // rejoin thread
        thread = std::thread(function);     // start function in this thread
        return;
    }
}
