#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "user.h"

namespace server {
    class Auth{
        public:
        Auth();
        ~Auth() = default;


        void EncryptPassword();
        User GetUser(const int& id) const;
        bool UserAlreadyExists();  
        std::shared_ptr<std::string> SignIn(const std::string& email, const std::string& password) const;
        void SignOut(const std::string& email);


        private:
        std::vector<User> users_;
    };
} // namespace server

#endif // AUTH_H