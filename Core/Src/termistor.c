#include <math.h>

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
float DividerVoltageToDegreesCelsius(float Pin1Voltage_mV, float readVoltage_mV)
{
    const float cA = 0.001129148; // Steinhart-Hart Equation coefficient A
    const float cB = 0.000234125; // Steinhart-Hart Equation coefficient B
    const float cC = 0.0000000876741; // Steinhart-Hart Equation coefficient C
    const float divider_R = 10e3; // Value of the KY-013 fixed resistor (10k ohms)
    float thermistor_R, logThermistor_R; // Thermistor resistance and the natural logarithm of the thermistor resistance
    float tempThermistor;    

    // Calculate the thermistor resistance
    thermistor_R = (Pin1Voltage_mV * divider_R - divider_R * readVoltage_mV) / (readVoltage_mV);    
    // Calculate the natural logarithm of the thermistor resistance
    logThermistor_R = log(thermistor_R);    
    // Calculate the temperature in Kelvin using the Steinhart-Hart Equation
    tempThermistor = 1.0 / (cA + cB * logThermistor_R + cC * logThermistor_R * logThermistor_R * logThermistor_R);    
    // Convert Kelvin to Celsius and return
    
    return tempThermistor - 273.15;
}