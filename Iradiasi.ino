#include <Wire.h>
#include <Adafruit_INA219.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD (alamat I2C 0x27, ukuran 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konstanta untuk resistor divider
const float R1 = 30.0;   // Nilai resistor R1 dalam kΩ
const float R2 = 7.5;    // Nilai resistor R2 dalam kΩ

// Luas panel surya dalam meter persegi
const float luasPanel = 0.26 * 0.35;  // Meter persegi

Adafruit_INA219 ina219;

void setup() {
  Serial.begin(9600);
  Serial.println("Measuring current, voltage, power, and irradiance with INA219 and solar panel ...");
  
  // Inisialisasi sensor INA219
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  
  // Inisialisasi LCD
  lcd.begin(16, 2);  // Menentukan ukuran LCD 16x2
  lcd.backlight();  // Menghidupkan backlight LCD
  
  // Setelah inisialisasi berhasil
  Serial.println("INA219 sensor initialized");
}

void loop() {
  float shuntVoltage = 0;
  float busVoltage = 0;
  float current_mA = 0;
  float power_mW = 0;

  // Membaca tegangan shunt (tegangan di sepanjang resistor pengukur arus)
  shuntVoltage = ina219.getShuntVoltage_mV() / 1000.0; // Konversi mV ke V

  // Membaca tegangan bus (tegangan di sepanjang solar panel)
  busVoltage = ina219.getBusVoltage_V();

  // Membaca arus dalam mA
  current_mA = ina219.getCurrent_mA();

  // Menghitung daya dalam mWatt
  power_mW = busVoltage * current_mA;

  // Membaca tegangan pada divider resistor untuk mendapatkan tegangan panel surya
  float voltage_solar_panel = analogRead(A0) * 5.0 / 1023.0; // Baca nilai ADC dan konversi ke tegangan (5V adalah tegangan referensi Arduino)

  // Menghitung daya panel surya dalam Watt
  float power_watt = voltage_solar_panel * voltage_solar_panel / (R2 / (R1 + R2));

  // Konversi daya ke iradiasi (Watt/m^2)
  float irradiance = power_watt / luasPanel;

  Serial.print("Bus Voltage:       "); Serial.print(busVoltage); Serial.println(" V");
  Serial.print("Shunt Voltage:     "); Serial.print(shuntVoltage); Serial.println(" V");
  Serial.print("Current:           "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power (INA219):    "); Serial.print(power_mW); Serial.println(" mW");
  Serial.print("Solar Panel Voltage: "); Serial.print(voltage_solar_panel); Serial.println(" V");
  Serial.print("Power (Calculated): "); Serial.print(power_watt); Serial.println(" W");
  Serial.print("Irradiance:        "); Serial.print(irradiance); Serial.println(" W/m^2");
  
  Serial.println("-----------------------");

  // Tampilkan hasil ke LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Irradiance:");
  lcd.setCursor(0, 1);
  lcd.print(irradiance, 2); // Menampilkan 2 digit desimal
  lcd.print(" W/m^2");

  delay(10000); // Delay 10 detik
}
