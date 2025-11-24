#pragma once

#include <mqtt/async_client.h>
#include <nlohmann/json.hpp>
#include <string>
#include <random>
#include <chrono>


class Publisher {
public:
    Publisher(const std::string& broker,
              const std::string& client_id,
              const std::string& topic);
    ~Publisher();

    void connect();
    void publish_loop(std::chrono::seconds interval = std::chrono::seconds(2));

private:
    std::string broker_;
    std::string client_id_;
    std::string topic_;
    mqtt::async_client client_;
    std::mt19937 rng_;
    std::uniform_real_distribution<> temp_dist_;

    nlohmann::json make_payload();
};

