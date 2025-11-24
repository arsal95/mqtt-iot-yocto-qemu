SYSTEMD_SERVICE_${PN} = "dropbear.service"

do_install_append() {
    install -d ${D}${systemd_unitdir}/system
    echo "[Unit]
Description=Dropbear SSH server
After=network.target

[Service]
ExecStart=/usr/sbin/dropbear -R -E -F
Restart=always

[Install]
WantedBy=multi-user.target" > ${D}${systemd_unitdir}/system/dropbear.service
}
