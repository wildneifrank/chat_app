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
    std::vector<server::User> users;
    std::vector<server::Message> messages;
};


namespace server {
    class Auth{
        public:
        Auth();
        ~Auth() = default;

        std::shared_ptr<std::string> SignIn(const std::string& email, const std::string& password) const;
        std::string SignUp(const std::string& email, const std::string& name, const std::string& password) const;
        void HandleMessage(const std::string& email, const std::string& message, const std::string& token);
        DataInfo GetDataInfo() const;

        private:
        std::shared_ptr<int> ValidateToken(const std::string& email, const std::string& token) const;
        std::string EncryptPassword(const std::string& password) const;
        std::shared_ptr<User> Auth::GetUser(const std::string& email) const;
        std::string GenerateToken() const;

        private:
        std::unique_ptr<Database> database_;
        std::shared_ptr<int> current_id_;
    };
} // namespace server

#endif // AUTH_H