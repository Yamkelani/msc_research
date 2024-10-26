import pyvisa as pvs
import pandas as pd
import time

#Define the constants


REGEN_POWER_SUPPLY_ADDR_ITECH_IT6012C = 'USB0::0x2EC7::0x6000::804465012787740004::INSTR'
REGEN_POWER_SUPPLY_ADDR_ITECH_M3622 = 'USB0::0x2EC7::0x3622::803359022767110013::INSTR'
CELL_MAX_VOLTAGE = 5.0
CELL_MAX_CURRENT = 2.0
CAPACITY = 6.8

class PVStorageEmulator:

    def __init__(self, instrument_addr):
        resource_manager = pvs.ResourceManager()
        self.emulator = resource_manager.open_resource(instrument_addr)  

    def get_device_status(self):
        print("The divice status is:", self.emulator.query("'*IDN?'"))

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
        #irrad_data = ingest_irrad_data()
        emulator.write("SOUR:MOD Solar")

    def get_pv_power():
        pass

    def get_pv_voltage():
        pass

    def get_pv_current():
        pass

    def battery_charger(self, **charging_parameters):
        try:
            #check if the emulator is on
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('\n'))
            print(f"The status of the emulator is {emulator_status}")

            if emulator_status == 0:
                #Clear system errors.
                self.emulator.write("SYST:CLE")

                #Check if the instrument is already on battery mode if so. 
                if int(self.emulator.query("BATT?").strip('\n'))  == 1:
                        self.emulator.write("BATT 0")
                
                self.emulator.write("SYST:FUNC SOUR")
                self.emulator.write("BATT:MODE CHAR")
                
                
                self.emulator.write(f"BATT:CHAR:VOLT {charging_parameters["charge_voltage"]}")
                self.emulator.write(f"BATT:CHAR:CURR {charging_parameters["charge_current"]}")


                self.emulator.write(f"BATT:STOP:VOLT {charging_parameters['stop_voltage']}")
                self.emulator.write(f"BATT:STOP:CURR {charging_parameters['stop_current']}")
                self.emulator.write(f"BATT:STOP:CAP {charging_parameters['stop_capacity']}")

                self.emulator.write(f"BATT:STOP:TIME {charging_parameters['stop_time']}")
                

                #Check if the voltage has been set successfully
                voltage = self.emulator.query('BATT:CHAR:VOLT?')
                print(f"Charging voltage is: {voltage}")
                current = self.emulator.query('BATT:CHAR:CURR?')
                print(f"Charging current is: {current}")



                self.emulator.write("BATT 1")
                self.emulator.write("OUTPUT ON")

                # if ((voltage <= CELL_MAX_VOLTAGE) and (voltage == charge_voltage)) and ((current <= CELL_MAX_CURRENT) and (current == charge_current)) :
                #     self.emulator.write("OUTPUT ON")

                print("ERROR", self.emulator.query("SYST:ERR?"))

        except Exception as e:
            print(f"Failed to set up the instrument for the charging process because of this error: {e}")


    def battery_discharge(self, discharge_voltage, discharge_current):
        try:
            #check if the emulator is on
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('\n'))

            if emulator_status == 0:
                #Set the device to act as a batetry charger and set the charging values.
                self.emulator.write("SYST:FUNC SOUR")
                #Check if the instrument is already on battery mode if so. 
                if int(self.emulator.query("BATT?").strip('\n'))  == 0:
                    self.emulator.write("BATT 1")

                self.emulator.write(f"BATT:CHAR:VOLT {discharge_voltage}")
                self.emulator.write(f"BATT:CHAR:CURR {discharge_current}")

                #Check if the voltage has been set successfully
                voltage = self.emulator.query('BATT:CHAR:VOLT?').strip('\n')
                print(f"Charging voltage is: {voltage}").strip("\n")
                current = self.emulator.query('BATT:CHAR:CURR?')
                print(f"Charging current is: {current}")

                if ((voltage <= CELL_MAX_VOLTAGE) and (voltage == discharge_voltage)) and ((current <= CELL_MAX_CURRENT) and (current == discharge_current)) :
                    self.emulator.write("OUTPUT ON")

        except Exception as e:
            print(f"Failed to set up the instrument for the charging process because of this error: {e}")

    def log_measurements(self, operation ):
        battery_tests_ops = ("charging","discharging")
        if operation in battery_tests_ops:
            print(f"Currently running this process: {operation}")

            if operation == battery_tests_ops[0]:
                op = operation[:3].upper()
            elif operation == battery_tests_ops[1]:
                op = operation[:4].upper()

            set_voltage = self.emulator.query(f"BATT:{op}:VOLT?")
            set_current = self.emulator.query(f"BATT:{op}:CURR?")
            set_time = self.emulator.query(f"BATT:{op}:TIME?")

        else:
            print(f"Invalid operation expection only these two operations {battery_tests_ops}")
                        
            

    def generate_pv_output():
        pass

def main(**kwaargs):

    #weather_data_paths = "C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\weather-2021.csv"
    charge_current = 4.2
    charge_voltage = 1.0
    load_voltage = 12.0
    load_current = 1.0

    solar_emulator = PVStorageEmulator(REGEN_POWER_SUPPLY_ADDR_ITECH_M3622)
    #solar_emulator.get_device_status()
    solar_emulator.battery_charger(charge_voltage = 3.7,
                                   charge_current = 3.4,
                                   stop_voltage = 4.2,
                                   stop_current = 5.0,
                                   stop_capacity = 5.44,
                                   stop_time = 120
                                   )
    #time.sleep(3600)
    #solar_emulator.battery_discharge(load_voltage, load_current)
    
    #wait for the charging process to finish


if __name__ == "__main__":
    main()