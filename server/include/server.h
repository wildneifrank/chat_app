#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include "auth.h"

namespace server {
    class Server{
        public:
        Server();
        ~Server() = default;
        void InitializationServer();
        void Login();
        void Register();
        void GetData();
        void PostMessage();
        
        private:
        std::shared_ptr<Auth> auth_;
        std::shared_ptr<httplib::Server> server_;
        std::shared_ptr<nlohmann::json> json_data_;
    };
} // namespace server

#endif // SERVER_H