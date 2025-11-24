#pragma once

#include <mqtt/async_client.h>
#include <string>

class Subscriber : public virtual mqtt::callback {
public:
    Subscriber(const std::string& broker,
               const std::string& client_id,
               const std::string& topic);
    ~Subscriber();

    void connect_and_subscribe();
    void run_forever();

    // Callback overrides
    void connected(const std::string& cause) override;
    void connection_lost(const std::string& cause) override;
    void message_arrived(mqtt::const_message_ptr msg) override;

private:
    std::string broker_;
    std::string client_id_;
    std::string topic_;
    mqtt::async_client client_;
};
