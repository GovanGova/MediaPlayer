//
// Created by G on 6/7/2018.
//

#pragma once

#include "Script.h"
#include "Shape.h"

//create shape
template<class T>
std::shared_ptr<T> createAssetAndAdd(std::shared_ptr<Script> script){
    T* shape=new T();

    if(script!= nullptr){
        script->addAsset(shared_ptr<Element>(shape));
    }
    return shape;
}


//create text