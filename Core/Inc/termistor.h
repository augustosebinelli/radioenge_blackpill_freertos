/**
 * @brief Converts the voltage from a voltage divider circuit to temperature in degrees Celsius.
 * 
 * This function uses the Steinhart-Hart equation to calculate the temperature of a thermistor
 * based on the voltage measured from a voltage divider circuit.
 * 
 * Be careful when choosing the KY-013 voltage level. If 5000.0 millivolts (5.0 V) is used, bear in mind that the
 * voltage on the STM32F411 ADC Pin must not exceed 3300.0 millivolts (3.3 V). Thus, the current flowing on the KY-013
 * circuit should not exceed 330 uA. So, if the thermistor resistance becomes lower than 5151.52 ohms, the voltage on 
 * the ADC pin will be exceeded. For a 10 kohms NTC Thermistor, this represents a temperature higher than 105 oC.
 * 
 * @param Pin1Voltage_mV The supply voltage of the KY-013 (Pin 1, which has a - sign), in millivolts.
 * @param readVoltage_mV The voltage over the fixed resistor (divider_R) read on Pin 2, in millivolts.
 * 
 * @return The temperature in degrees Celsius.
 */
float DividerVoltageToDegreesCelsius(float Pin1Voltage_mV, float readVoltage_mV);