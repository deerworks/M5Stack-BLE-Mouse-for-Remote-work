#include <M5Stack.h>
#include <BleMouse.h>

#define DELAY_CONNECT  (60U * 1000U)
#define DELAY_DISCONN  (10U * 60U * 1000U)
#define DELAY_STARTUP  (5U * 1000U)

BleMouse blemouse("Bluetooth Macro Mouse");
unsigned int cnt;
bool state = false;

void setup() {
  M5.begin();
  M5.Power.begin();
  blemouse.begin();
  cnt = 0;
  m5.lcd.setTextSize(2);
  M5.Lcd.println("Start BLE Mouse");
}

void loop() {
  uint32_t delaytime = 0;
  M5.update();
  if(blemouse.isConnected())
  {
    delaytime = DELAY_CONNECT;
    if(!state)
    {
      M5.Lcd.println("Connected!!");
      state = true;
    }
    signed char x = 0;
    signed char y = 0;
    cnt++;
    cnt %= 4;
    switch(cnt)
    {
      case 0:
        x = 1;
        y = 0;
        break;
      case 1:
        x = 0;
        y = 1;
        break;
      case 2:
        x = -1;
        y = 0;
        break;
      case 3:
        x = 0;
        y = -1;
        break;
      default:
        x = 0;
        y = 0;
    }
    blemouse.move(x, y);
  }
  else
  {
    delaytime = DELAY_DISCONN;
    if(state)
    {
      M5.Lcd.println("Disconnected...");
      state = false;
    }
    else
    {
      delaytime = DELAY_STARTUP;
    }
  }
  delay(delaytime);
}