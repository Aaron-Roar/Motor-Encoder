const char lights = 4;

void lightsInit() {
    pinMode(4, OUTPUT);
}

void lightsOn() {
    digitalWrite(4, HIGH);
}

void lightsOff() {
    digitalWrite(4, LOW);
}
