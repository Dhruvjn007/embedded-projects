# RPi Pico with WiFi - Communicates with Arduino UNO R4 WiFi
# Pico acts as TCP CLIENT
# Pico sends: "Hi I am Raspberry Pi Pico"
# Arduino responds: "Hello I am Arduino UNO R4"
#
# Requirements:
#   - RPi Pico W (has built-in WiFi) OR Pico + ESP8266 module
#   - Both devices on same WiFi network
#   - Run the Arduino sketch first, note its IP address
#   - Replace ARDUINO_IP below with actual Arduino IP
#
# This file is for RPi Pico W (built-in WiFi)

import network
import socket
import time

# === CONFIGURE THESE ===
WIFI_SSID = "YourWiFiName"
WIFI_PASSWORD = "YourWiFiPassword"
ARDUINO_IP = "192.168.1.100"  # Replace with Arduino's IP from Serial Monitor
ARDUINO_PORT = 8080
# =======================

def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(WIFI_SSID, WIFI_PASSWORD)

    print("Connecting to WiFi", end="")
    for _ in range(20):
        if wlan.isconnected():
            break
        print(".", end="")
        time.sleep(0.5)

    if wlan.isconnected():
        print(f"\nConnected! Pico IP: {wlan.ifconfig()[0]}")
        return True
    else:
        print("\nFailed to connect to WiFi")
        return False

def talk_to_arduino():
    try:
        # Create TCP socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(5)
        sock.connect((ARDUINO_IP, ARDUINO_PORT))

        # Send greeting
        msg = "Hi I am Raspberry Pi Pico"
        sock.send(msg.encode())
        print(f"Pico says: {msg}")

        # Wait for Arduino's reply
        reply = sock.recv(128).decode().strip()
        print(f"Arduino says: {reply}")

        sock.close()

    except Exception as e:
        print(f"Connection error: {e}")

# Main
if connect_wifi():
    time.sleep(1)
    talk_to_arduino()
