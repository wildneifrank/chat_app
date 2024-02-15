#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <memory>

namespace server {
    class User{
        public:
        User(const std::string& name, const int& id);
        ~User();

        auto GetName();
        auto GetId();

        private:
        std::shared_ptr<std::string> name_;
        std::shared_ptr<int> id_;
    };
} // namespace server

#endif // USER_H