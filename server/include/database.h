#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "user.h"
#include "message.h"

namespace server {
    class Database{
        public:
        Database();
        ~Database() = default;

        std::vector<User> GetUsers() const;
        std::vector<Message> GetMessages() const;
        void CreateUser(User& user);
        void PostMessage(Message& message);

        private:
        std::vector<User> users_;
        std::vector<Message> messages_;
    };
} // namespace server

#endif // DATABASE_H