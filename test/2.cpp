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
    "test5: constructor(), =",
    "test7: memcheck",
    "test value_type: <Integer,Integer>",//c[10]
    "test value_type: <Integer,Matrix<int> >",//c[11]
};

bool equal(Integer a,Integer b){
    return a.val == b.val;
}

void integer_hashmap_memcheck_tester(){
    using value_type = sjtu::pair<Integer,Integer>;
    using mp = sjtu::hashmap<Integer,Integer,Hash,Equal>;
    const int n = 10000;
    // test: constructor
    if(STATUS)std::cout<<c[2];
    mp map;
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: insert and expand
    if(STATUS)std::cout<<c[3];
    for(int i=0;i<n;i++){
        map.insert(value_type(Integer(i),Integer(i)));
    }
    for(int i=0;i<n;i+=4){
        map.insert(value_type(Integer(i),Integer(4*i)));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: remove
    if(STATUS)std::cout<<c[4];
    for(int i=0;i<n;i+=3){
        map.remove(Integer(i));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;
    
    //test: find
    if(STATUS)std::cout<<c[5];
    for(int i=0;i<n;i++){
        mp::iterator it = map.find(Integer(i));
        if(STATUS == 0){
            if(it != map.end())
            std::cout<<(*it).second.val<<std::endl;
        }
        if(i%3==0){
            if(it != map.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!equal(Integer(4 * i),(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!equal(Integer(i),(*it).second)){
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
        mp::iterator it = map2.find(Integer(i));
        if(i%3==0){
            if(it != map2.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!equal(Integer(4 * i),(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!equal(Integer(i),(*it).second)){
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

void big_hashmap_tester(){
    using value_type = sjtu::pair<Integer,Matrix<int> >;
    using mp = sjtu::hashmap<Integer,Matrix<int>,Hash,Equal>;
    const int n = 100000;
    // test: constructor
    if(STATUS)std::cout<<c[2];
    mp map;
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: insert and expand
    if(STATUS)std::cout<<c[3];
    for(int i=0;i<n;i++){
        map.insert(value_type(Integer(i),Matrix<int>(2,2,i)));
    }
    for(int i=0;i<n;i+=4){
        map.insert(value_type(Integer(i),Matrix<int>(2,2,4 * i)));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: remove
    if(STATUS)std::cout<<c[4];
    for(int i=0;i<n;i+=3){
        map.remove(Integer(i));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: find
    if(STATUS)std::cout<<c[5];
    for(int i=0;i<n;i++){
        mp::iterator it = map.find(Integer(i));
        if(STATUS == 0){
            if(it != map.end())
            std::cout<<(*it).second<<std::endl;
        }
        if(i%3==0){
            if(it != map.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!(Matrix<int>(2,2,4 * i)==(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!(Matrix<int>(2,2,i)==(*it).second)){
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
        mp::iterator it = map2.find(Integer(i));
        if(i%3==0){
            if(it != map2.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!(Matrix<int>(2,2,4 * i)==(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!(Matrix<int>(2,2,i)==(*it).second)){
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
    freopen("2.out","w",stdout);
#endif
    std::cout<<c[10]<<std::endl;
    integer_hashmap_memcheck_tester();
    std::cout<<c[11]<<std::endl;
    big_hashmap_tester();
    if(STATUS){
        std::cout<<c[9];
        if(Integer::counter == 0){
            std::cout<<c[0]<<std::endl;
        }
        else{
            std::cout<<c[1]<<std::endl;
            exit(0);
        }
    }
    std::cout << c[7] << std::endl;
}