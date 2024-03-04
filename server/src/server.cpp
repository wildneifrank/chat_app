#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include "../include/server.h"
#include "../include/auth.h"

namespace server
{
    Server::Server() : auth_(std::make_shared<Auth>()),
                           server_(std::make_shared<httplib::Server>()),
                       json_data_(std::make_shared<nlohmann::json>())
    {
    }

    void Server::InitializationServer()
    {
        server_->Options("/", [&](const httplib::Request &req, httplib::Response &res)
                         {
                             res.set_header("Access-Control-Allow-Origin", "*");
                             res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
                             res.set_header("Access-Control-Allow-Headers", "Content-Type");
                             res.status = 200; // Set status to 200 OK
                         });
        this->Login();
        this->Register();
        std::cout << "Server started successfully. Listening on port 8080" << std::endl;
        server_->listen("localhost", 8080);
    }

    void Server::Login()
    {
        server_->Post("/login", [&](const httplib::Request &req, httplib::Response &res)
                      {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            if (req.has_header("Content-Length") && req.body.length() > 0) {
                auto json_body = nlohmann::json::parse(req.body);
                std::string email = json_body["email"];
                std::string password = json_body["password"];
                try
                {
                    const auto token = auth_->SignIn(email, password);
                    nlohmann::json json_token;
                    json_token["token"] = *token;
                    res.set_content(json_token.dump(), "application/json");

                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error occurred: " << e.what() << '\n';
                }
            } else {
                res.set_content("No message provided in the request body", "text/plain");
            } });
    }
    void Server::Register()
    {
        server_->Post("/register", [&](const httplib::Request &req, httplib::Response &res)
                      {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            if (req.has_header("Content-Length") && req.body.length() > 0) {
                auto json_body = nlohmann::json::parse(req.body);
                std::string email = json_body["email"];
                std::string name = json_body["name"];
                std::string password = json_body["password"];
                try
                {
                    const auto token = auth_->SignUp(email,name, password);
                    nlohmann::json json_token;
                    json_token["token"] = token;
                    res.set_content(json_token.dump(), "application/json");

                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error occurred: " << e.what() << '\n';
                }
            } else {
                res.set_content("No message provided in the request body", "text/plain");
            } });
    }

    // void Server::PostMessages()
    // {
    //     server_->Post("/", [&](const httplib::Request &req, httplib::Response &res)
    //                   {
    //         res.set_header("Access-Control-Allow-Origin", "*");
    //         res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    //         res.set_header("Access-Control-Allow-Headers", "Content-Type");
    //         if (req.has_header("Content-Length") && req.body.length() > 0) {
    //             try {
                    
    //                 auto json_body = nlohmann::json::parse(req.body);

    //                 std::string text = json_body["text"];
    //                 std::string user_name = json_body["user_name"];
    //                 int user_id = this->NameAlreadyExists(user_name);
    //                 if(!(user_id)){
    //                     users_.push_back(User(user_name, *current_id_));
    //                     messages_.push_back(Message(text, *current_id_));
    //                     (*current_id_)++;
    //                 }
    //                 else{
    //                     messages_.push_back(Message(text, user_id));
    //                 }
    //                 res.set_content("Messages received successfully", "text/plain");
    //             } catch (const std::exception& e) {
    //                 res.set_content("Error parsing JSON body", "text/plain");
    //             }
    //         } else {
    //             res.set_content("No message provided in the request body", "text/plain");
    //         } });
    // }

    // void Server::GetData()
    // {
    //     server_->Get("/", [&](const httplib::Request &req, httplib::Response &res)
    //                  {
    //     res.set_header("Access-Control-Allow-Origin", "*");
    //     res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    //     res.set_header("Access-Control-Allow-Headers", "Content-Type");
    //     try {
    //         // Convert users_ vector to JSON
    //         nlohmann::json json_users;
    //         for (const auto& user : users_) {
    //             nlohmann::json json_user;
    //             json_user["name"] = *user.GetName();
    //             json_user["id"] = *user.GetId();
    //             json_users.push_back(json_user);
    //         }

    //         // Convert messages_ vector to JSON
    //         nlohmann::json json_messages;
    //         for (const auto& msg : messages_) {
    //             nlohmann::json json_msg;
    //             json_msg["text"] = *msg.GetText();
    //             json_msg["user"] = *msg.GetUserId();
    //             json_messages.push_back(json_msg);
    //         }

    //         (*json_data_)["users"] = json_users;
    //         (*json_data_)["messages"] = json_messages;

    //         // Set the JSON response
    //         res.set_content((*json_data_).dump(), "application/json");
    //     } catch (const std::exception& e) {
    //         res.set_content("Error converting data to JSON", "text/plain");
    //     } });
    // }

} // namespace server
