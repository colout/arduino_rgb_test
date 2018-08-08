uint16_t currentRGB[3] = { 0, 0 , 0 };
uint16_t targetRGB[3] = { 1024, 1024, 1024 };

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);

  Serial.begin(115200);
}



void loop() {
  for (int i=0; i<=2; i++) {
    if (currentRGB[i] < targetRGB[i]) {
      currentRGB[i] = currentRGB[i] + 1;
    } else {
      currentRGB[i] = currentRGB[i] - 1;
    } 
  }
  
  analogWrite(A0, currentRGB[0]);
  analogWrite(A1, currentRGB[1]);
  analogWrite(A2, currentRGB[2]);

  if (currentRGB[2] >= 255) {
    for (int i=0; i<=2; i++) {
      targetRGB[i] = 0;
    }
  }

  if (currentRGB[2] <= 0) {
    for (int i=0; i<=2; i++) {
      targetRGB[i] = 255;
    }
  }
  delay (10);
}
