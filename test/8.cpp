#include "src.hpp"
#if defined (_UNORDERED_MAP_)  || (defined (_LIST_)) || (defined (_MAP_)) || (defined (_SET_)) || (defined (_UNORDERED_SET_))||(defined (_GLIBCXX_MAP)) || (defined (_GLIBCXX_UNORDERED_MAP))
BOOM :)
#endif
#include <iostream>
#include <cassert>
#include <string>
#include <random>
#include <ctime>
#include <unordered_map>
#include <list>

std::string c[]={
    "   pass!",
    "   error.",
    "test1: constructor",
    "test2: insert & expand",
    "test3: remove",
    "test4: find & correctness of insert and remove",
    "test6: clear",
    "Congratulations. Your submission has passed all correctness tests. Good job! :)",
    "test5: constructor(), =",
    "test7: memcheck",
    "test value_type: <Integer,Integer>",//c[10]
    "test value_type: <Integer,Matrix<int> >",//c[11]
    "init insert",
    "random remove",
    "double clear",
    "little fragment work",
};

void simple_lru_tester(){
    using value_type = sjtu::pair<Integer,Matrix<int> >;
    sjtu::lru tester(100);
    const int n=10000;
    for(int i=0;i<n;i++){
        tester.save(value_type( Integer(i),Matrix<int>(2,2,i)));
        tester.get(Integer(i-(i%99)));
    }
    tester.print();
}

int main(){
    #ifdef _OUTPUT_
    freopen("8.out","w",stdout);
#endif
    simple_lru_tester();
    std::cout << c[7] << std::endl;
}