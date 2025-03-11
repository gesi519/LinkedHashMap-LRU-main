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
    "test5: clear",
    "Congratulations. Your submission has passed all correctness tests. Good job! :)",
    "test6: constructor(), =",
    "test const iterator",
};

bool exists(sjtu::hashmap<int,int> map,sjtu::hashmap<int,int>::iterator i){
    return i!=map.end();
}

bool equal(int a,int b){
    return a== b;
}

void simple_linked_hashmap_tester(){
    using value_type = sjtu::pair<int,int>;
    using mp = sjtu::linked_hashmap<int,int>;
    const int n = 100;
    // test: constructor
    if(STATUS)std::cout<<c[2];
    mp map;
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: insert,remove and expand
    if(STATUS)std::cout<<c[3];
    for(int i=0;i<n;i++){
        map.insert(value_type(i,i));
    }
    if(STATUS)std::cout<<std::endl<<c[4];//test remove

    for(mp::iterator it = map.begin();it!=map.end();it++){
	    mp::iterator tmpit = it;
        it++;
        map.remove(tmpit);
        if(it == map.end()){
            break;
        }
        it++;
        if(it == map.end()){
            break;
        }
    }

    for(int i=0;i<n;i+=4){
        map.insert(value_type(i,4*i));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: counter

    int ct = 0;
    for(int i=0;i<n;i++){
        ct += map.count(i);
    }
    if(STATUS)std::cout<<"test: count:"<<ct<<std::endl;

    //test: iterator
    mp::iterator it = map.begin();
    while(it != map.end()){
        std::cout<<(*it).first<<" "<<(*it).second<<std::endl;
        it++;
    }

    //test: const iterator

    if(STATUS)std::cout<<c[9];
    mp::iterator iter;
    iter = map.begin();
    iter = map.end();
    mp::const_iterator const_iter;
    const_iter = map.cend();
    const_iter = map.cbegin();
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: find
    if(STATUS)std::cout<<c[5];
    for(int i=0;i<n;i++){
        mp::iterator it = map.find(i);
        if(STATUS == 0){
            if(it != map.end())
            std::cout<<(*it).second<<std::endl;
        }
        if(i%3==0 && i%4 != 0){
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
    //map2.clear();
    map2 = map;
    
    for(int i=0;i<n;i++){
        mp::iterator it = map2.find(i);
        if(i%3==0 && i%4 != 0){
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
    freopen("4.out","w",stdout);
#endif
    simple_linked_hashmap_tester();
    std::cout << c[7] << std::endl;
}
