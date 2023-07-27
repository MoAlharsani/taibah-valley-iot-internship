# Install Node-Red on AWS EC2 instance, and establishing MQTT connection between ESP32s and AWS IoT core

[Click here to go to the MQTT connection section](#mqtt-connection-esp32s-and-aws-iot-as-client-with-aws-iot-broker)


### Install Node-Red on AWS EC2 Instance

In this part, we will set up an Amazon EC2 instance and install Node-Red on it. Amazon EC2 (Elastic Compute Cloud) provides scalable computing capacity 
in the cloud, and Node-Red is a flow-based programming tool that allows us to easily connect devices, APIs, and online services.

## Install Node-Red on AWS EC2 Instance

1. **Create an AWS EC2 Instance:**
   - Sign in to your AWS account and navigate to the EC2 dashboard.
   - Click on "Launch Instance" to create a new EC2 instance.
   - Choose an Amazon Machine Image (AMI) that supports Ubuntu.
   - Configure the instance settings, such as instance type, VPC, subnet, and security groups. Make sure to add a new rule to allow incoming traffic on port 22 (SSH) and port 1880 (Node-Red).
   - Create or use an existing key pair for SSH access.

2. **Access the EC2 Instance via SSH:**
   - Download the .pem key file associated with your EC2 instance during the launch process.
   - Open PuTTY (or your preferred SSH client) and load the .pem key.
   - Enter the public IP address or DNS name of your EC2 instance.
   - Connect to the instance, and you should have a terminal window to the EC2 instance.


3. **Install Node.js and npm:**
   - Update the package manager and install Node.js and npm by running the following commands:
     ```bash
     sudo apt update
     sudo apt install -y nodejs npm
     ```

4. **Install Node-Red:**
   - Use npm to install Node-Red globally on the EC2 instance:
     ```bash
     sudo npm install -g --unsafe-perm node-red
     ```

5. **Start Node-Red:**
   - Start the Node-Red server by executing the following command:
     ```bash
     node-red
     ```

6. **Access Node-Red Dashboard:**
   - Open a web browser and navigate to your EC2 instance's public IP address or DNS name, followed by port 1880 (e.g., http://your_ec2_public_ip:1880).
   - You should see the Node-Red dashboard, and you can start creating flows and working with Node-Red.
#### Node-Red running on EC2, and accessed by my browser
| ![Dashboard Example](img/node_red_ec2.png) |
|:----------------------------------:|

#### EC2 terminal on PuTTY
| ![Dashboard Example](img/ec2_on_my_laptop.png) |
|:----------------------------------:|

## MQTT connection ESP32s and AWS IoT as client with AWS IoT broker


In this task, we will establish an MQTT connection between ESP32 devices and AWS IoT Core. AWS IoT Core is a managed cloud service that enables communication between IoT devices and the cloud.

### Prerequisites:

1. **Create an AWS IoT Core Thing:**
   - Sign in to your AWS account and navigate to AWS IoT Core.
   - Create a new IoT Core "Thing" to represent your ESP32 devices.
   - Note down the generated Thing name.

2. **Generate X.509 Certificates:**
   - Generate and download X.509 certificates for your ESP32 devices from AWS IoT Core.
   - Keep the certificate files (certificate, private key, and root CA certificate) secure, as they will be used for secure TLS communication.

### Setting Up ESP32:

1. **Install Required Libraries:**
   - Set up the ESP32 development environment if not already done.
   - Include the necessary libraries for WiFi, MQTT, and TLS secure communication.

2. **Upload the Sketch:**
   - Use the Arduino IDE or any compatible IDE to upload the sketch to the ESP32.
   - Modify the sketch to include your WiFi SSID, password, and AWS IoT Core endpoint (e.g., `a341dgduqrqsfy-ats.iot.eu-west-3.amazonaws.com`).
     
2. **Set Policies:**
   - Attach appropriate policies to the X.509 certificates used by your ESP32 devices as in the file certificates.h
   - The policies should allow the devices to publish data to the designated MQTT topics.
     
3. **Configure TLS and MQTT:**
   - Configure the WiFi connection and set up the WiFiClientSecure object.
   - Load the X.509 certificates into the WiFiClientSecure object to enable secure communication.

4. **Connect to AWS IoT Core:**
   - Establish a connection to the AWS IoT Core using the MQTT client (PubSubClient).
   - Use the generated Thing name as the client ID for MQTT connection.

5. **Publish Data:**
   - Read data from the sensors (e.g., potentiometer and MQ2 gas sensor).
   - Convert the sensor data to a string format and publish it to AWS IoT Core on specific MQTT topics.

6. **Subscribe:**
   - You can also subscribe to specific MQTT topics to receive commands or updates from AWS IoT Core.

Once the ESP32 devices are running the MQTT client and connected to AWS IoT Core, they will securely publish sensor data to AWS IoT Core. The data can be further processed, stored, or visualized using AWS services or integrated with other applications.

