#include "mqtt/Subscriber.hpp"

using namespace std;

int main() {

    //const string BROKER = "tcp://localhost:1883";
    const string BROKER = "tcp://10.0.2.2:1883";
    const string CLIENT_ID = "iot-display-01";
    const string TOPIC = "home/temperature";

    try {
        Subscriber sub(BROKER, CLIENT_ID, TOPIC);
        sub.connect_and_subscribe();
        sub.run_forever();
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}