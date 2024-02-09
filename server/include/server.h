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
        void GetMessages();
        
        private:
        std::shared_ptr<httplib::Server> server_;
        std::vector<User> users_;
        std::vector<Message> messages_;
    };
} // namespace server

#endif // SERVER_H