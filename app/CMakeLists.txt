cmake_minimum_required(VERSION 3.14)
project(iot_stream_bridge LANGUAGES CXX)

# C++17 is required for modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PahoMqttCpp REQUIRED)
find_package(nlohmann_json REQUIRED)

# Include the public headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# === Publisher executable ===
add_executable(mqtt_publisher
    src/main_publisher.cpp
    src/Publisher.cpp
)
target_link_libraries(mqtt_publisher
    PahoMqttCpp::paho-mqttpp3
    nlohmann_json::nlohmann_json
)

# === Subscriber executable ===
add_executable(mqtt_subscriber
    src/main_subscriber.cpp
    src/Subscriber.cpp
)
target_link_libraries(mqtt_subscriber
    PahoMqttCpp::paho-mqttpp3
    nlohmann_json::nlohmann_json
)