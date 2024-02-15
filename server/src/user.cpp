#include <iostream>
#include <string>
#include <memory>
#include "../include/user.h"

namespace server{
    User::User(const std::string& name, const int& id):
                name_(std::make_shared<std::string>(name)),
                id_(std::make_shared<int>(id)){}
    User::~User(){}

    std::shared_ptr<std::string> User::GetName() const{
        return name_;
    }

    std::shared_ptr<int> User::GetId() const{
        return id_;
    }


} // namespace server