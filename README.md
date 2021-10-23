# Arduino MKR1010 with Elasticsearch
We are using an Arduino MKR1010 to send sensor data to an elasticsearch server. The sensor used is an ultrasonic sensor but you can switch the code to any sensor you want. Also, the timestamp is being calculated on the arduino by connecting to a time server.

## Setup
To run this, you will need to change rename the file secrets-example.h into secrets.h and add your constants to the file using your own wifi secrets and your elasticsearch address/port.