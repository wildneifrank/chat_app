#include <iostream>
#include <string>
#include <memory>
#include "../include/database.h"
#include "../include/user.h"
#include "../include/message.h"

namespace server {
    Database::Database():users_(std::vector<User>()),
                        messages_(std::vector<Message>())
                        {}
    
    std::vector<User> Database::GetUsers() const{
        return users_;
    }

    std::vector<Message> Database::GetMessages() const{
        return messages_;
    }

    void Database::CreateUser(User& user){
        users_.push_back(user);
    }

    void Database::PostMessage(Message& message){
        messages_.push_back(message);
    }
} // namespace server
