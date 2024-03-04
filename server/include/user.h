#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <memory>

namespace server {
    class User{
        public:
        User(const std::string& name, const int& id, const std::string& email, const std::string& token, const std::string& encrypted_password);
        ~User() = default;

        std::shared_ptr<std::string> GetName() const;
        std::shared_ptr<int> GetId() const;
        std::shared_ptr<std::string> GetToken() const;
        std::shared_ptr<std::string> GetEncryptedPassword() const;
        std::shared_ptr<std::string> GetEmail() const;
        void SetToken(const std::shared_ptr<std::string> token);


        private:
        std::shared_ptr<std::string> email_;
        std::shared_ptr<std::string> encrypted_password_;
        std::shared_ptr<std::string> token_;
        std::shared_ptr<std::string> name_;
        std::shared_ptr<int> id_;
    };
} // namespace server

#endif // USER_H