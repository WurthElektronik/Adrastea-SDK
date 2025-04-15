import paho.mqtt.client as mqtt
import json
import random
import time

# MQTT broker settings
BROKER = "test.mosquitto.org"
PORT = 1883
TOPIC_PUB = "myadrastea/sensors"
TOPIC_SUB = "myadrastea/#"

# MQTT callbacks
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe(TOPIC_SUB)

def on_message(client, userdata, msg):
    print(f"[RECEIVED] Topic: {msg.topic} | Payload: {msg.payload.decode()}")

# Create MQTT client and set callbacks
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Connect to broker
client.connect(BROKER, PORT, keepalive=60)

# Start MQTT loop in background
client.loop_start()

# Publish loop
device_ID = "359100540137978"
try:
    while True:
        payload = {
            "device_ID": device_ID,
            "pressure": f"{random.uniform(90.0, 105.0):.2f}",
            "humidity": f"{random.uniform(20.0, 60.0):.2f}",
            "temperature": f"{random.uniform(15.0, 35.0):.2f}",
            "acceleration": {
                "X": f"{random.uniform(-2.0, 2.0):.2f}",
                "Y": f"{random.uniform(-2.0, 2.0):.2f}",
                "Z": f"{random.uniform(-2.0, 2.0):.2f}"
            }
        }

        json_payload = json.dumps(payload)
        result = client.publish(TOPIC_PUB, json_payload)
        status = result[0]
        if status == 0:
            print(f"[PUBLISHED] {json_payload}")
        else:
            print(f"[ERROR] Failed to publish message")

        time.sleep(10)

except KeyboardInterrupt:
    print("Exiting...")
    client.loop_stop()
    client.disconnect()
