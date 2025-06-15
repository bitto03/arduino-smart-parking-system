#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

// IR sensor pins
int IR1 = 2;
int IR2 = 3;

// Total parking slots
int Slot = 4;

// Flags for vehicle entry/exit detection
int flag1 = 0;
int flag2 = 0;

// DHT sensor setup
#define DHTPIN 5       // DHT data pin connected to digital pin 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Timer variables for screen switching
unsigned long lastSwitchTime = 0;
const unsigned long switchInterval = 5000; // 5 seconds
bool showSlotInfo = true;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo.attach(4);
  myservo.write(100); // Initial gate position (closed)

  dht.begin(); // Initialize DHT sensor

  lcd.setCursor(0, 0);
  lcd.print(" SMART PARKING ");
  lcd.setCursor(0, 1);
  lcd.print("   SYSTEM INIT  ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Handle car entering
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(0); // Open gate
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }
  }

  // Handle car exiting
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(0); // Open gate
      Slot = Slot + 1;
    }
  }

  // After movement complete, close gate and reset
  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(100); // Close gate
    flag1 = 0;
    flag2 = 0;
  }

  // Switch display every 5 seconds
  if (millis() - lastSwitchTime > switchInterval) {
    showSlotInfo = !showSlotInfo;
    lastSwitchTime = millis();
    lcd.clear();
  }

  if (showSlotInfo) {
    lcd.setCursor(0, 0);
    lcd.print("    WELCOME!    ");
    lcd.setCursor(0, 1);
    lcd.print("Slot Left: ");
    lcd.print(Slot);
  } else {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print((char)223); // Degree symbol
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(hum);
    lcd.print("%");
  }
}
