# Arduino MKR1010 with Elasticsearch
We are using an Arduino MKR1010 to send sensor data to an elasticsearch server. The sensor used is an ultrasonic sensor but you can switch the code to any sensor you want.
Also, the timestamp is being calculated on the arduino by connecting to a time server.

## Setup
To run this, you will need to change the arduino_secrets.h constants to your wifi secrets and add your own elasticsearch server address/port.