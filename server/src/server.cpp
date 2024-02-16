#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "../include/server.h"
#include "../include/user.h"
#include "../include/message.h"

namespace server {
    Server::Server():server_(std::make_shared<httplib::Server>()),
                    users_(std::vector<User>()),
                    messages_(std::vector<Message>()),
                    json_data_(std::make_shared<nlohmann::json>()),
                    current_id_(std::make_shared<int>(1))
                    {}
    Server::~Server(){}

    void Server::InitializationServer(){
        server_->Options("/", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 200; // Set status to 200 OK
        });
        this->PostMessages();
        this->GetData();
        std::cout << "Server started successfully. Listening on port 8080" << std::endl;
        server_->listen("localhost", 8080);
    }
    

    void Server::PostMessages() {
        server_->Post("/", [&](const httplib::Request& req, httplib::Response& res) {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            if (req.has_header("Content-Length") && req.body.length() > 0) {
                try {
                    
                    auto json_body = nlohmann::json::parse(req.body);

                    std::string text = json_body["text"];
                    std::string user_name = json_body["user_name"];
                    int user_id = this->NameAlreadyExists(user_name);
                    if(!(user_id)){
                        users_.push_back(User(user_name, *current_id_));
                        messages_.push_back(Message(text, *current_id_));
                        (*current_id_)++;
                    }
                    else{
                        messages_.push_back(Message(text, user_id));
                    }
                    res.set_content("Messages received successfully", "text/plain");
                } catch (const std::exception& e) {
                    res.set_content("Error parsing JSON body", "text/plain");
                }
            } else {
                res.set_content("No message provided in the request body", "text/plain");
            }
        });
    }

    void Server::GetData() {
    server_->Get("/", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        try {
            // Convert users_ vector to JSON
            nlohmann::json json_users;
            for (const auto& user : users_) {
                nlohmann::json json_user;
                json_user["name"] = *user.GetName();
                json_user["id"] = *user.GetId();
                json_users.push_back(json_user);
            }

            // Convert messages_ vector to JSON
            nlohmann::json json_messages;
            for (const auto& msg : messages_) {
                nlohmann::json json_msg;
                json_msg["text"] = *msg.GetText();
                json_msg["user"] = *msg.GetUserId();
                json_messages.push_back(json_msg);
            }

            (*json_data_)["users"] = json_users;
            (*json_data_)["messages"] = json_messages;

            // Set the JSON response
            res.set_content((*json_data_).dump(), "application/json");
        } catch (const std::exception& e) {
            res.set_content("Error converting data to JSON", "text/plain");
        }
    });
    }
    int Server::NameAlreadyExists(const std::string& user_name){
        for(const auto& user: users_){
            if(*user.GetName() == user_name){
                return *user.GetId();
            }
        }
        return 0;
    }

} // namespace server

