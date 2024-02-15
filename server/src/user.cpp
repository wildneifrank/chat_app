#include <iostream>
#include <string>
#include <memory>
#include "../include/user.h"

namespace server{
    User::User(const std::string& name, const int& id):
                name_(std::make_shared<std::string>(name)),
                id_(std::make_shared<int>(id)){}
    User::~User(){}

    auto User::GetName(){
        return this->name_;
    }

    auto User::GetId(){
        return this->id_;
    }


} // namespace server