#include <iostream>
#include <string>
#include <memory>
#include "../include/message.h"

namespace server{
    Message::Message(const std::string& text, const int& user_id):
                    text_(std::make_shared<std::string>(text)),
                    user_id_(std::make_shared<int>(user_id)){}
    Message::~Message(){}

    std::shared_ptr<std::string> Message::GetText() const{
        return text_;
    }
    std::shared_ptr<int> Message::GetUserId() const{
        return user_id_;
    }
} // namespace server
