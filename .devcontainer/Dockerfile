FROM ghcr.io/zephyrproject-rtos/zephyr-build:latest

WORKDIR /workspaces/esp-servo-drver-zephyr

# Copy the west manifest
COPY west.yml .

# Initialize West workspace with this app as the manifest repository
RUN west init -l .

# Update to fetch Zephyr and dependencies
RUN west update

# Fetch ESP32 binary blobs
RUN west blobs fetch hal_espressif
