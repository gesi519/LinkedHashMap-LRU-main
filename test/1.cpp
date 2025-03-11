#include "src.hpp"
#if defined (_UNORDERED_MAP_)  || (defined (_LIST_)) || (defined (_MAP_)) || (defined (_SET_)) || (defined (_UNORDERED_SET_))||(defined (_GLIBCXX_MAP)) || (defined (_GLIBCXX_UNORDERED_MAP))
BOOM :)
#endif
#include <iostream>
#include <cassert>
#include <string>
// if this is 1, output yes or no
//otherwise, output the exact num
#define STATUS 0

std::string c[]={
    "   pass!",
    "   error.",
    "test1: constructor",
    "test2: insert & expand",
    "test3: remove",
    "test4: find & correctness of insert and remove",
    "test6: clear",
    "Congratulations. Your submission has passed all correctness tests. Good job! :)",
    "test5: constructor(), ="
};

bool exists(sjtu::hashmap<int,int> map,sjtu::hashmap<int,int>::iterator i){
    return i!=map.end();
}

bool equal(int a,int b){
    return a == b ;
}

void integer_hashmap_memcheck_tester(){
    using value_type = sjtu::pair<int,int>;
    using mp = sjtu::hashmap<int,int>;
    const int n = 100000;
    // test: constructor
    if(STATUS)std::cout<<c[2];
    mp map;
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: insert and expand
    if(STATUS)std::cout<<c[3];
    for(int i=0;i<n;i++){
        map.insert(value_type(i,i));
    }
    for(int i=0;i<n;i+=4){
        map.insert(value_type(i,4*i));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: remove
    if(STATUS)std::cout<<c[4];
    for(int i=0;i<n;i+=3){
        map.remove(i);
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: find
    if(STATUS)std::cout<<c[5];
    for(int i=0;i<n;i++){
        mp::iterator it = map.find(i);
        if(STATUS == 0){
            if(it != map.end())
            std::cout<<(*it).second<<std::endl;
        }
        if(i % 3==0){
            if(it != map.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!equal(4*i,(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!equal(i,(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: constructor(), =
    if(STATUS)std::cout<<c[8];
    mp map2(map);
    map2.clear();
    map2 = map;
    for(int i=0;i<n;i++){
        mp::iterator it = map2.find(i);
        if(i%3==0){
            if(it != map2.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!equal(4*i,(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!equal(i,(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: clear
    if(STATUS)std::cout<<c[6];
    map.clear();
    map.clear();
    if(STATUS)std::cout<<c[0]<<std::endl;
}

int main(){
#ifdef _OUTPUT_
    freopen("1.out","w",stdout);
#endif
    integer_hashmap_memcheck_tester();
    std::cout << c[7] << std::endl;
}