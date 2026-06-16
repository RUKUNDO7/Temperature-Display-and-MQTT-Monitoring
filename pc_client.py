import serial
import paho.mqtt.client as mqtt

# Serial Port
ser = serial.Serial('COM6', 9600)

# MQTT Broker
BROKER = "157.173.101.159"   # VPS IP
PORT = 1883
TOPIC = "spe/temperature"

client = mqtt.Client()
client.connect(BROKER, PORT, 60)

print("Monitoring Temperature...\n")

while True:
    try:
        data = ser.readline().decode().strip()

        if data:
            print("Temperature:", data, "°C")

            client.publish(TOPIC, data)

    except KeyboardInterrupt:
        break

ser.close()
client.disconnect()