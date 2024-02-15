#include <iostream>
#include <string>
#include <memory>
#include "../include/message.h"

namespace server{
    Message::Message(const std::string& text, const int& user_id):
                    text_(std::make_shared<std::string>(text)),
                    user_id_(std::make_shared<int>(user_id)){}
    Message::~Message(){}

    auto Message::GetText(){
        return this->text_;
    }
    auto Message::GetUserId(){
        return this->user_id_;
    }
}
