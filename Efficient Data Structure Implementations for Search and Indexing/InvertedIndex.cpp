#include "InvertedIndex.h"

#include <fstream>
#include <iostream>

InvertedIndex::InvertedIndex() {

}

InvertedIndex::InvertedIndex(const InvertedIndex &obj) {

    this->invertedIndex = obj.invertedIndex; // uses operator= of BST
}

InvertedIndex::~InvertedIndex() {

}

TreeMap<std::string, std::vector<int> >  &InvertedIndex::getInvertedIndex() {
    return invertedIndex;
}


InvertedIndex &InvertedIndex::addDocument(const std::string &documentName, int docid) {
    std::ifstream file(documentName.c_str(), std::ifstream::in);
    
    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << documentName << std::endl;
        return *this;
    }

    std::string word;
    
    while (file >> word) {
        // Check if the word is already in the inverted index
        if (invertedIndex.containsKey(word)){
            std::vector<int>& integers = invertedIndex[word];
            bool flag = true;
            for(size_t i = 0; i < integers.size(); i++){
                if(integers[i] == docid){
                    flag = false;
                    break;
                }
            }
            if(flag){
                integers.push_back(docid);
                sort_the_vector(integers);
            }
        }
        else{
            std::vector<int> integers_2;
            integers_2.push_back(docid);
            sort_the_vector(integers_2);
            invertedIndex.put(word, integers_2);
        }
    }

    file.close();
    return *this;

}

std::vector<int> InvertedIndex::search(const std::string &query) {
     
    
    std::vector<int> result_vector;
    
    std::vector<std::string> words;
    std::string word;
    
    for (size_t i = 0; i < query.size(); ++i) {
        char ch = query[i];
        if (ch == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word.push_back(ch);
        }
    }
    
    if (!word.empty()) {
        words.push_back(word);
    }

    for(size_t i = 0; i < words.size(); ++i){
        if(invertedIndex.containsKey(words[i])){
            std::vector<int> temp = invertedIndex[words[i]];
            for(size_t k = 0; k < temp.size(); k++){
                if(!contain_mi_la(result_vector, temp[k])){
                    result_vector.push_back(temp[k]);
                }
            }
        }
    }
    return result_vector;
}

InvertedIndex & InvertedIndex::printInvertedIndex() const {

    invertedIndex.print();

}

InvertedIndex &InvertedIndex::operator=(const InvertedIndex &rhs) {

    this->invertedIndex = rhs.invertedIndex; // uses operator= of BST

    return *this;
}
