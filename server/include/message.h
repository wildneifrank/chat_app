#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include <memory>

namespace server {
    class Message{
        public:
        Message();
        ~Message();
        
        private:
        std::shared_ptr<std::string> text_;
        std::shared_ptr<int> user_id_;
    };
} // namespace server

#endif // MESSAGE_H