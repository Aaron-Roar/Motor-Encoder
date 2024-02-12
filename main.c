//If Lower is on

void setup() {
    Serial.begin(9600);

    lightsInit();
    lightsOn();

    photoResInit();
    photoResOn();

    motorInit();
    motorPowPercent(0.2);
    delay(10000);

    readChannels();
    printWaveForm();

    Serial.print("Direction: ");
    Serial.println(determineDirection());

    Serial.print("Speed: ");
    Serial.println(avgSpeed());

}

void loop() {
//    Serial.print("A: ");
//    Serial.println(readChannel(a_chan));
//
//    Serial.print("B: ");
//    Serial.println(readChannel(b_chan));
//    delay(200);
}
