#include <iostream>
#include <string>
#include <memory>
#include <random>
#include "../include/auth.h"
#include "../include/database.h"
#include "../include/message.h"
#include "../include/user.h"

namespace server {
    Auth::Auth():database_(std::make_unique<Database>()),
                current_id_(std::make_shared<int>(1)){
                }

    std::shared_ptr<std::string> Auth::SignIn(const std::string& email, const std::string& password) const{
        const auto user = this->GetUser(email);
        if(user == nullptr){
            throw std::invalid_argument("User is null");
        }
        const auto encrypted_password = this->EncryptPassword(password);
        if(encrypted_password == *(user->GetEncryptedPassword())){
            const std::shared_ptr<std::string> token  = std::make_shared<std::string>(this->GenerateToken());
            user->SetToken(token);
            return token;
        }
        throw std::invalid_argument("Password is invalid");
    }

    std::string Auth::SignUp(const std::string& email, const std::string& name, const std::string& password) const{
        const auto user = this->GetUser(email);
        if(!(user == nullptr)){
            throw std::invalid_argument("User already registered");
        }
        const auto token = this->GenerateToken();
        const auto encrypted_password = this->EncryptPassword(password);
        const auto newUser = new User(name, *current_id_, email, token, encrypted_password);
        database_->CreateUser(*newUser);
        (*current_id_)++;
        return token;
    }

    void Auth::HandleMessage(const std::string& email, const std::string& message, const std::string& token){
        const auto id = this->ValidateToken(email, token);
        if(!id){
            throw std::invalid_argument("token is invalid");
        }
        const auto messageInfo = new Message(message, *id);
        database_->PostMessage(*messageInfo);
    }

    DataInfo Auth::GetDataInfo() const {
        DataInfo data;
        data.users = database_->GetUsers();
        data.messages = database_->GetMessages();
        return data;
    }

    std::shared_ptr<int> Auth::ValidateToken(const std::string& email, const std::string& token) const{
        const auto user = this->GetUser(email);
        if(*(user->GetToken()) == token){
            return user->GetId();
        }
        return 0;
    }

    std::string Auth::EncryptPassword(const std::string& password) const {
        const int shift = 3;
        std::string encryptedPassword = password;

        for (char& c : encryptedPassword) {
            if (std::isalpha(c)) {
                char base = std::islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
        }

        return encryptedPassword;
    }

    std::shared_ptr<User> Auth::GetUser(const std::string& email) const{
        auto users = database_->GetUsers();
        for(const auto& user : users){
            if(*(user.GetEmail()) == email) {
                return std::make_shared<User>(user);
            }
        }
        return nullptr;
    }
    
    std::string Auth::GenerateToken() const{
        const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        const int length = 20; 
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, characters.size() - 1);
        
        std::string token;
        for (int i = 0; i < length; ++i) {
            token += characters[dis(gen)];
        }
        
        return token;
    }

} // namespace server
