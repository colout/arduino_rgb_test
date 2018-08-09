#include <bluefruit.h>

uint16_t currentRGB[3] = { 0, 0 , 0 };
uint16_t targetRGB[3] = { 1024, 1024, 1024 };


BLEDis bledis;
BLEHidAdafruit blehid;

uint8_t modifier;
uint8_t count;
uint8_t keycode[6] = { 0 };
bool anyKeyPressed;

bool keyPressedPreviously = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  Serial.begin(115200);
  
  keycode[0] = 0;
  keycode[1] = 0;
  keycode[2] = 0;
  keycode[3] = 0;
  keycode[4] = 0;
  keycode[5] = 0;
  
  Bluefruit.begin();

  // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Linksys");
  bledis.setManufacturer("Cisco Home and Office");
  bledis.setModel("Linksys WRT54GL");
  bledis.begin();
  blehid.begin();
  startAdv();
}


void startAdv(void) {
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void loop() {
  keycode[0] = HID_KEY_F;
  blehid.keyboardReport(0, keycode);

  keycode[0] = HID_KEY_U;
  blehid.keyboardReport(0, keycode);

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

  for (int i=0; i<=2; i++) {
    if (currentRGB[i] < targetRGB[i]) {
      currentRGB[i] = currentRGB[i] + 1;
    }
    if (currentRGB[i] > targetRGB[i]) {
      currentRGB[i] = currentRGB[i] - 1;
    } 
  }
  delay (1);
}
