#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
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
        std::vector<User> users_;
        std::vector<Message> messages_;
    };
} // namespace server

#endif // SERVER_H