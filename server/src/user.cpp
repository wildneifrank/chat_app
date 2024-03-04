#include <iostream>
#include <string>
#include <memory>
#include "../include/user.h"

namespace server{
    User::User(const std::string& name, const int& id, const std::string& email, const std::string& token, const std::string& encrypted_password):
                name_(std::make_shared<std::string>(name)),
                id_(std::make_shared<int>(id)),
                email_(std::make_shared<std::string>(email)),
                encrypted_password_(std::make_shared<std::string>(encrypted_password)),
                token_(std::make_shared<std::string>(token))
                {}


    std::shared_ptr<std::string> User::GetName() const{
        return name_;
    }

    std::shared_ptr<int> User::GetId() const{
        return id_;
    }

    std::shared_ptr<std::string> User::GetToken() const{
        return token_;
    }

    void User::SetToken(const std::shared_ptr<std::string> token) {
        *token_ = *token;
    }

    std::shared_ptr<std::string> User::GetEncryptedPassword() const{
        return encrypted_password_;
    }

    std::shared_ptr<std::string> User::GetEmail() const{
        return email_;
    }

} // namespace server