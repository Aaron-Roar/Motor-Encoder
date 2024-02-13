//If Lower is on

float duty_cycle = 0.35;

void setup() {
    Serial.begin(9600);

    lightsInit();
    lightsOn();

    photoResInit();
    photoResOn();

    motorInit();
    motorPowPercent(duty_cycle);
    delay(10000);

//    readChannels();
//    printWaveForm();
//
//    Serial.print("Direction: ");
//    Serial.println(determineDirection());
//
//    Serial.print("Speed: ");
//    Serial.println(avgSpeed());
//
//    Serial.print("At Duty Cycle: ");
//    Serial.print(duty_cycle * 100);
//    Serial.println("%");

}

void loop() {
//VOLTAGE FOR CURRENT MEASUREMENT
    float voltage = (float)analogRead(A1) * ((float)5/(float)1023);
    float current = voltage/10;
    Serial.print("Voltage: ");
    Serial.println(voltage);
}
