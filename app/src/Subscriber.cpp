#include "mqtt/Subscriber.hpp"
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;

Subscriber::Subscriber(const string& broker,
                       const string& client_id,
                       const string& topic)
    : broker_(broker)
    , client_id_(client_id)
    , topic_(topic)
    , client_(broker, client_id)
{
    client_.set_callback(*this);
}

Subscriber::~Subscriber() {
    try {
        if (client_.is_connected()) {
            client_.disconnect()->wait();
        }
    } catch (...) {}
}

void Subscriber::connect_and_subscribe() {
    try {
        cout << "[Subscriber] Connecting to " << broker_ << "...\n";
        auto opts = mqtt::connect_options_builder()
                        .keep_alive_interval(chrono::seconds(20))
                        .clean_session(true)
                        .finalize();
        client_.connect(opts)->wait();
        cout << "[Subscriber] Connected!\n";

        client_.subscribe(topic_, 1)->wait();
        cout << "[Subscriber] Subscribed to '" << topic_ << "'\n";
    } catch (const mqtt::exception& e) {
        cerr << "[Subscriber] Error: " << e.what() << '\n';
        throw;
    }
}

void Subscriber::run_forever() {
    while (true) {
        this_thread::sleep_for(chrono::hours(1));
    }
}

void Subscriber::connected(const string& cause) {
    cout << "[Subscriber] Reconnected: " << cause << '\n';
}

void Subscriber::connection_lost(const string& cause) {
    cout << "[Subscriber] Connection lost: " << cause << '\n';
}

void Subscriber::message_arrived(mqtt::const_message_ptr msg) {
    cout << "\n[Subscriber] <<< MESSAGE RECEIVED >>>\n";
    cout << "Topic : " << msg->get_topic() << '\n';
    cout << "Raw   : " << msg->to_string() << "\n\n";

    try {
        auto j = nlohmann::json::parse(msg->to_string());
        cout << setw(4) << j << "\n\n";
    } catch (...) {
        cout << "(Invalid JSON)\n\n";
    }
}
