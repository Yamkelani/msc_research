import pyvisa
import time


CELL_MAX_VOLTAGE = 5.0
CELL_MAX_CURRENT = 2.0
charge_voltage = 4.2
charge_current = 1.0
CAPACITY = 6.8
# Initialize PyVISA resource manager
# rm = pyvisa.ResourceManager()

# # Connect to IT6012C (replace with actual VISA address)
# itech = rm.open_resource('USB0::0x2EC7::0x6000::804465012787740004::INSTR')

# # Check communication
# print(itech.query('*IDN?'))  # Query the device's identity

# # Set the function to battery mode
# itech.write('FUNC BATT')

# # Set charging voltage and current
# itech.write('BATT:CHAR:VOLT 4.2')
# itech.write('BATT:CHAR:CURR 1')

# # Turn on output to start charging
# itech.write('OUTP ON')

# # Monitor charging process
# try:
#     while float(itech.query('MEAS:VOLT?')) < 4.2:
#         print(f"Charging... Voltage: {itech.query('MEAS:VOLT?')} V")
#         time.sleep(10)

#     # Stop charging when voltage reaches 4.2V
#     itech.write('OUTP OFF')
#     print("Charging complete.")
    
# finally:
#     # Close connection
#     itech.close()

import pyvisa

# Initialize the PyVISA resource manager
rm = pyvisa.ResourceManager()

# Connect to the IT6012C device (replace with actual VISA address)
itech = rm.open_resource('USB0::0x2EC7::0x3622::803359022767110013::INSTR')  # Replace with the correct address

# Check communication with the device
print(itech.query('*IDN?'))  # Confirm device identity

# Set the voltage and current for battery charging
try:
            #check if the emulator is on
            emulator_status = int(itech.query("OUTP:STAT?").strip('\n'))
            print(f"The status of the emulator is {emulator_status}")

            if emulator_status == 0:
                #Set the device to act as a battery charger and set the charging values.
                itech.write("SYST:CLE")
                itech.write("BATT 0")
                itech.write("SYST:FUNC SOUR")
                itech.write("BATT:MODE CHAR")
                
                
                #itech.write("BATT 0")
                #Check if the instrument is already on battery mode if so. 
                if int(itech.query("BATT?").strip('\n'))  == 0:
                        pass
                    # itech.write("BATT 1")

                itech.write(f"BATT:CHAR:VOLT {charge_voltage}")
                itech.write(f"BATT:CHAR:CURR {charge_current}")


                itech.write("BATT:STOP:VOLT 4.6")
                itech.write("BATT:STOP:CURR 0.0")
                itech.write("BATT:STOP:CAP 6.0")

                itech.write("BATT:STOP:TIME 10.0")
                

                #Check if the voltage has been set successfully
                voltage = itech.query('BATT:CHAR:VOLT?')
                print(f"Charging voltage is: {voltage}")
                current = itech.query('BATT:CHAR:CURR?')
                print(f"Charging current is: {current}")



                itech.write("BATT 1")
                itech.write("OUTPUT ON")

                # if ((voltage <= CELL_MAX_VOLTAGE) and (voltage == charge_voltage)) and ((current <= CELL_MAX_CURRENT) and (current == charge_current)) :
                #     itech.write("OUTPUT ON")

                print("ERROR", itech.query("SYST:ERR?"))

except Exception as e:
            print(f"Failed to set up the instrument for the charging process because of this error: {e}")
# Query to check that the values are set correctly
'''
set_voltage = itech.query('BATT:CHAR:VOLT?')
set_current = itech.query('BATT:CHAR:CURR?')

print(f"Set Voltage: {set_voltage} V")
print(f"Set Current: {set_current} A")'''

# Output is NOT turned on yet, but the device display should show the set values.
# The user can now see the set voltage and current on the instrument screen before connecting the battery.
