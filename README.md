# MQTT-IoT  
A lightweight MQTT Publisher/Subscriber application written in **C++**, packaged using **Yocto**, and executed inside a **QEMU ARM** virtual embedded system.

This project demonstrates a complete embedded workflow:

- Building an MQTT-enabled C++ application using **CMake**
- Creating a Yocto layer (`meta-iot`)
- Packaging the application as a Yocto recipe (`mqtt-iot_0.1.bb`)
- Including an MQTT broker (**Mosquitto**) inside the Yocto image
- Running everything on a virtual embedded board using **QEMU (qemuarm)**
- Using **Dropbear SSH** to log into the virtual device and run the MQTT apps
- **Publishing dummy temperature sensor data** from `mqtt_publisher`
- **Displaying the sensor data** on the `mqtt_subscriber`
