#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include "user.h"
#include "message.h"

namespace server {
    class Server{
        public:
        Server();
        ~Server();
        void InitializationServer();
        void PostMessages();
        void GetData();
        int NameAlreadyExists(const std::string& user_name);
        
        private:
        std::shared_ptr<httplib::Server> server_;
        std::vector<User> users_;
        std::vector<Message> messages_;
        std::shared_ptr<nlohmann::json> json_data_;
        std::shared_ptr<int> current_id_;
    };
} // namespace server

#endif // SERVER_H