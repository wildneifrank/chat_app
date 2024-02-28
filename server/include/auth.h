#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "database.h"
#include "user.h"
#include "message.h"

struct DataInfo {
    std::vector<User> users;
    std::vector<Message> messages;
};


namespace server {
    class Auth{
        public:
        Auth();
        ~Auth() = default;

        std::shared_ptr<std::string> SignIn(const std::string& email, const std::string& password) const;
        void SignUp(const std::string& email, const std::string& name, const std::string& password);

        DataInfo GetDataInfo() const;

        private:
        bool UserAlreadyExists(const std::string& email) const;  
        std::string EncryptPassword(const std::string& password) const;
        User GetUser(const int& id) const;

        private:
        std::unique_ptr<Database> database_;
    };
} // namespace server

#endif // AUTH_H