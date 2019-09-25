const int sensor_pin = A4;  // Soil moisture sensor O/P pin

double moisture_percentage = 0;
int textSent = 0; // 0 = text not sent, 1 = text sent

void setup() {
  //Serial.begin(9600); /* Define baud rate for serial communication */
  Particle.variable("moisture", moisture_percentage);
}

void loop() {
    int sensor_analog;
    sensor_analog = analogRead(sensor_pin);
    moisture_percentage = (sensor_analog);
    
    // If the moisture dips below 1000 send text
    if (moisture_percentage < 1000) {
        if (textSent == 0) {
            Particle.publish("twilio_sms", "Your plant water is low, water it", PRIVATE);
            textSent = 1;
        }
    }

    // If the moisture goes back up, reset textSent
    if (moisture_percentage > 1000) {
      textSent = 0;
    }
    
    delay(1000);
}
