#include "mqtt/Publisher.hpp"
#include <chrono>

using namespace std;

int main() {

    //const string BROKER = "tcp://localhost:1883";
    const string BROKER = "tcp://10.0.2.2:1883";
    const string CLIENT_ID = "iot-publisher-01";
    const string TOPIC = "home/temperature";

    try {
        Publisher pub(BROKER, CLIENT_ID, TOPIC);
        pub.connect();
        pub.publish_loop(chrono::seconds(2));
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}