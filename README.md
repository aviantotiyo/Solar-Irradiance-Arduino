Berikut adalah file README dalam format markdown untuk kode di atas:

---

# Solar Panel and INA219 Sensor Measurement

This project uses an Arduino Uno, an Adafruit INA219 sensor, and a voltage divider to measure current, voltage, power, and irradiance of a solar panel. The results are displayed on the serial monitor.

## Components

- Arduino Uno
- Adafruit INA219 Sensor
- Resistors (30 kΩ and 7.5 kΩ for voltage divider)
- Solar Panel (260 mm x 350 mm)

## Circuit Diagram

1. **INA219 Connections**:
   - `VCC` to Arduino `5V`
   - `GND` to Arduino `GND`
   - `SDA` to Arduino `A4`
   - `SCL` to Arduino `A5`

2. **Voltage Divider Connections**:
   - The positive terminal of the solar panel to the 30 kΩ resistor (R1)
   - The junction of the 30 kΩ resistor and 7.5 kΩ resistor (R2) to Arduino `A0`
   - The negative terminal of the solar panel to the 7.5 kΩ resistor and then to ground

## Code Explanation

### Libraries

- `Wire.h`: Used for I2C communication.
- `Adafruit_INA219.h`: Library for the INA219 sensor.

### Constants

- `R1` and `R2`: Resistor values in kΩ for the voltage divider.
- `luasPanel`: Surface area of the solar panel in square meters.

### Setup

- Initializes the serial communication at 9600 baud rate.
- Initializes the INA219 sensor and checks if it is found.

### Loop

- Reads the shunt voltage, bus voltage, and current using the INA219 sensor.
- Calculates power in mW using the INA219 sensor data.
- Reads the voltage from the voltage divider connected to the solar panel.
- Calculates the power in watts using the voltage from the solar panel.
- Converts the power to irradiance in W/m² using the surface area of the solar panel.
- Prints the measurements to the serial monitor every 10 seconds.


## Output

The code will print the following data to the serial monitor:
- Bus Voltage (V)
- Shunt Voltage (V)
- Current (mA)
- Power measured by INA219 (mW)
- Solar Panel Voltage (V)
- Power calculated (W)
- Irradiance (W/m²)

## Notes

- Ensure that the voltage divider is correctly connected to the Arduino and the solar panel.
- Adjust the resistor values (R1 and R2) if needed based on your specific setup.
- Ensure that the INA219 sensor is properly connected and initialized.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---