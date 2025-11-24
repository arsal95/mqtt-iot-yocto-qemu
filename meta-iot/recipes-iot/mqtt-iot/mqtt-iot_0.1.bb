SUMMARY = "MQTT IoT Demo - publisher & subscriber"
DESCRIPTION = "Simple MQTT publisher/subscriber demo packaged for Yocto."
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=e52f5a24a2ba35a65c16fc4b10c07c31"

SRC_URI = "file://mqtt-iot.tar.gz"
S = "${WORKDIR}"

inherit cmake pkgconfig

# Correct build-time dependencies
DEPENDS = "paho-mqtt-c paho-mqtt-cpp nlohmann-json"

# Runtime dependencies
RDEPENDS_${PN} = "paho-mqtt-c paho-mqtt-cpp nlohmann-json"

# Install binaries manually if your CMake project doesn't have install() commands
do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/mqtt_publisher ${D}${bindir}/mqtt_publisher
    install -m 0755 ${B}/mqtt_subscriber ${D}${bindir}/mqtt_subscriber
}
