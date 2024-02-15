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

        std::shared_ptr<std::string> GetName() const;
        std::shared_ptr<int> GetId() const;

        private:
        std::shared_ptr<std::string> name_;
        std::shared_ptr<int> id_;
    };
} // namespace server

#endif // USER_H