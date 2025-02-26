#include <iostream>

#include "TreeMap.h"

int main() {

    TreeMap<std::string, int> treeMap;

    treeMap.print();

    treeMap.put("tokyo", 37468000);
    treeMap.put("delhi", 28514000);
    treeMap.put("shangai", 25582000);
    treeMap.put("sao paulo", 21650000);
    treeMap.put("mexico city", 21581000);
    treeMap.put("cairo", 20076000);
    treeMap.put("mumbai", 19980000);
    treeMap.put("beijing", 19618000);
    treeMap.put("dhaka", 19578000);
    treeMap.put("osaka", 19281000);

    treeMap.print();

    return 0;
}
