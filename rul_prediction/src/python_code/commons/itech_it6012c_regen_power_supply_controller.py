import pyvisa as pvs

resource_manager = pvs.ResourceManager()
itech_pws_supply = resource_manager.open_resource('USB0::0x2EC7::0x6000::804465012787740004::INSTR') 

import pandas as pd

#Define the constants


REGEN_POWER_SUPPLY_ADDR_ITECH6012C = 'USB0::0x2EC7::0x6000::804465012787740004::INSTR'
REGEN_POWER_SUPPLY_ADDR_ITECH3622 = 'USB0::0x2EC7::0x3622::803359022767110013::INSTR'
CELL_MAX_VOLTAGE = 4.2
CELL_MAX_CURRENT = 2.0
CAPACITY = 6

class PVStorageEmulator:

    def __init__(self, system_emulator):
        self.emulator_addr =system_emulator
        resource_manager = pvs.ResourceManager()
        self.emulator = resource_manager.open_resource(self.emulator_addr) 
        self.emulator.write("SYS:CLE")
        self.emulator.write("SYS:REM") 

    def get_device_status(self):
        self.emulator.query("'*IDN?'")

    def ingest_irrad_data(paths):
        datasets = []
        for path in paths:
            datasets.append(pd.read_csv(path,header=0))
        return datasets

    def seasons_simulator(self,season):
        #Get season pv output
        #charge the battery cell
        self.battery_charger()
        #Wait for 720000 sec (2 hours)
        self.battery_discharge()
        #record voltage, current and temperature data


    def pv_simulator(emulator):
        irrad_data = ingest_irrad_data()
        emulator.write("SOUR:MOD Solar")

    def get_pv_power():
        pass

    def get_pv_voltage():
        pass

    def get_pv_current():
        pass

    def battery_charger(self, charge_voltage, charge_current):
        try:
            #check if the emulator is on
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('\n'))

            if emulator_status == 0:
                #Set the device to act as a batetry charger and set the charging values.
                self.emulator.write("SOUR:FUNC BATT")
                self.emulator.write("BATT:MODE:CHAR")
                self.emulator.write(f"BATT:CHAR:VOLT {charge_voltage}")
                self.emulator.write(f"BATT:CHAR:CURR {charge_current}")

                #Check if the voltage has been set successfully
                voltage = self.emulator.query('BATT:CHAR:VOLT?')
                print(f"Charging voltage is: {voltage}")
                current = self.emulator.query('BATT:CHAR:CURR?')
                print(f"Charging current is: {current}")

                if ((voltage <= CELL_MAX_VOLTAGE) and (voltage == charge_voltage)) and ((current <= CELL_MAX_CURRENT) and (current == charge_current)) :
                    self.emulator.write("OUTPUT ON")

        except Exception as e:
            print(f"Failed to set up the instrument for the charging process because of this error: {e}")

        pass

    def battery_discharge():
        pass

    def log_measurements():
        pass

    def generate_pv_output():
        pass

def main(**kwaargs):

    #weather_data_paths = "C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\weather-2021.csv"

    res_manager = pvs.ResourceManager()
    emulator = res_manager.open_resource(REGEN_POWER_SUPPLY_ADDR)

    #Establish connection with the device
    

    #Get connected resources that we can program
    print(res_manager.list_resources())

    #Get identity of the device
    print(emulator.query('*IDN?'))

    #Get current measurements on the instrument
    print(emulator.query("MEAS?"))

    print(emulator.query("SYSTem:VERS?"))


if __name__ == "__main__":
    main()