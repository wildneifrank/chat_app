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
        this->GetData();
        this->PostMessage();
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
        void Server::GetData()
    {
        server_->Get("/", [&](const httplib::Request &req, httplib::Response &res)
                     {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        try {
            // Convert users_ vector to JSON
            std::shared_ptr<nlohmann::json> json_data = std::make_shared<nlohmann::json>();
            const auto dataInfo = auth_->GetDataInfo();
            nlohmann::json json_users;
            for (const auto& user : dataInfo.users) {
                nlohmann::json json_user;
                json_user["name"] = *user.GetName();
                json_user["id"] = *user.GetId();
                json_user["token"] = *user.GetToken();
                json_user["email"] = *user.GetEmail();
                json_user["encryptedPassword"] = *user.GetEncryptedPassword();
                json_users.push_back(json_user);
            }

            // Convert messages_ vector to JSON
            nlohmann::json json_messages;
            for (const auto& msg : dataInfo.messages) {
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
        } });
    }

    void Server::PostMessage()
    {
        server_->Post("/", [&](const httplib::Request &req, httplib::Response &res)
                      {
            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type");
            if (req.has_header("Content-Length") && req.body.length() > 0) {
                auto json_body = nlohmann::json::parse(req.body);
                std::string email = json_body["email"];
                std::string message = json_body["message"];
                std::string full_token = req.get_header_value("Authorization");
                std::string token = full_token.substr(7);
                try
                {
                    auth_->HandleMessage(email, message, token);
                    res.set_content("Message received successfully", "text/plain");
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error occurred: " << e.what() << '\n';
                }
            } else {
                res.set_content("No message provided in the request body", "text/plain");
            } });
    }
 

} // namespace server
