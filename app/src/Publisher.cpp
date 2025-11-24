#include "mqtt/Publisher.hpp"
#include <iostream>
#include <thread>

using namespace std;

Publisher::Publisher(const string& broker,
                     const string& client_id,
                     const string& topic)
    : broker_(broker)
    , client_id_(client_id)
    , topic_(topic)
    , client_(broker, client_id)
    , rng_(random_device{}())
    , temp_dist_(18.0, 30.0)  // 18–30°C
{
}

Publisher::~Publisher() {
    try {
        if (client_.is_connected()) {
            client_.disconnect()->wait();
        }
    } catch (...) {}
}

void Publisher::connect() {
    try {
        cout << "[Publisher] Connecting to " << broker_ << "...\n";
        client_.connect()->wait();
        cout << "[Publisher] Connected!\n";
    } catch (const mqtt::exception& e) {
        cerr << "[Publisher] Connect failed: " << e.what() << '\n';
        throw;
    }
}

nlohmann::json Publisher::make_payload() {
    return {
        {"device", client_id_},
        {"temperature", temp_dist_(rng_)},
        {"unit", "C"},
        {"timestamp", time(nullptr)}
    };
}

void Publisher::publish_loop(chrono::seconds interval) {
    const int QOS = 1;

    while (true) {
        try {
            auto payload = make_payload();
            string msg_str = payload.dump();

            auto msg = mqtt::make_message(topic_, msg_str, QOS, false);
            client_.publish(msg)->wait();

            cout << "[Publisher] Published: " << msg_str << '\n';
        } catch (const mqtt::exception& e) {
            cerr << "[Publisher] Publish error: " << e.what() << '\n';
        }
        this_thread::sleep_for(interval);
    }
}
