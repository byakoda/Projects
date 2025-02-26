#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "TreeMap.h"

class InvertedIndex {
public: // DO NOT CHANGE THIS PART.
    InvertedIndex();

    InvertedIndex(const InvertedIndex &obj);

    ~InvertedIndex();

    TreeMap<std::string, std::vector<int> > &getInvertedIndex();

    InvertedIndex &addDocument(const std::string &documentName,int docid);
    std::vector<int> search(const std::string &query);
    InvertedIndex & printInvertedIndex() const;

    InvertedIndex &operator=(const InvertedIndex &rhs);


private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

    bool contain_mi_la(const std::vector<int>& integers, int value) {
        for (size_t i = 0; i < integers.size(); ++i) {
            if (integers[i] == value) {
                return true;
            }
        }
        return false;
    }


    void sort_the_vector(std::vector<int> &integers){
        for(size_t i = 0; i < integers.size() - 1; ++i){
            for(size_t k = 0; k < integers.size() - i - 1; ++k){
                    if(integers[k] > integers[k+1]){
                        int temp = integers[k];
                        integers[k] = integers[k + 1];
                        integers[k + 1] = temp;
                    }
            }
        }
    }

private: // DO NOT CHANGE THIS PART.

    TreeMap<std::string, std::vector<int> > invertedIndex;

};

#endif //INVERTEDINDEX_H
