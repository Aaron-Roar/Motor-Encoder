//If Lower is on

void setup() {
    Serial.begin(9600);

    lightsInit();
    lightsOn();

    photoResInit();
    photoResOn();

    motorInit();
    motorPowPercent(0.20);
    delay(10000);

    readChannels();
    printWaveForm();

    Serial.print("Direction: ");
    Serial.println(determineDirection());

    Serial.print("Speed: ");
    Serial.println(avgSpeed());

}

void loop() {
//VOLTAGE FOR CURRENT MEASUREMENT
//    float voltage = (float)analogRead(A1) * ((float)5/(float)1023);
//    Serial.print("Voltage: ");
//    Serial.println(voltage);
}
