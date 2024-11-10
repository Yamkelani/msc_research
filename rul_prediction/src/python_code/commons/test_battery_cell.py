"""
This code is for charging and discharging any battery cell using the Itech regenerative power supply.
Remember to create a config file for the cell that you want to charge.
Specify the charging and discharging parameters as shown in the cell datasheet.
When running this code in the termina use the following command. Also make sure you are in th eright directory 
, where this file is located.
python .\test_battery_cell.py 001 ICR18650 
"""


import pyvisa as pvs
import pandas as pd
import logging
import datetime
import json
import sys

#Define the constants


REGEN_POWER_SUPPLY_ADDR_ITECH_IT6012C = 'USB0::0x2EC7::0x6000::804465012787740004::INSTR'
REGEN_POWER_SUPPLY_ADDR_ITECH_M3622 = 'USB0::0x2EC7::0x3622::803359022767110013::INSTR'
REGEN_POWER_SUPPLY_ADDR_ITECH_AEL_M3622  = 'USB0::0x2EC7::0x3622::803359022797450003::INSTR'
CELL_MAX_VOLTAGE = 5.0
CELL_MAX_CURRENT = 2.0
CAPACITY = 6.8

logger = logging.getLogger(__name__)
FileOutputHandler = logging.FileHandler('logs.log')

logger.addHandler(FileOutputHandler)

logger.warning("Warning.")



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

    def battery_charger(self, **charging_configs):
        try:
            test_cell = charging_configs['test_cell']
            #check if the emulator is on
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('/n'))
            print(f"The status of the emulator is {emulator_status}")

            if emulator_status == 0:
                #Clear system errors.
                print("Clearing errors")
                self.emulator.write("SYST:CLE")

                #Check if the instrument is already on battery mode if so. 
                if int(self.emulator.query("BATT?").strip('/n'))  == 1:
                        print("==========================Switching off battery mode for a fresh start=================")
                        self.emulator.write("BATT 0")
                
                print("==========================Setting emulator to source mode=================")
                self.emulator.write("SYST:FUNC SOUR")

                print("==========================Setting emulator to Battery mode=================")
                self.emulator.write("BATT:MODE CHAR")
                
                print(f"==========================Setting battery charging voltage to {charging_configs["charge_voltage"]} =================")
                self.emulator.write(f"BATT:CHAR:VOLT {charging_configs["charge_voltage"]}")

                print(f"==========================Setting battery charging current to: {charging_configs["charge_current"]} =================")
                self.emulator.write(f"BATT:CHAR:CURR {charging_configs["charge_current"]}")

                print(f"==========================Setting battery cut off voltage to: {charging_configs["stop_voltage"]} =================")
                self.emulator.write(f"BATT:STOP:VOLT {charging_configs['stop_voltage']}")
                
                print(f"==========================Setting battery cutt off current to: {charging_configs["stop_current"]} =================")
                self.emulator.write(f"BATT:STOP:CURR {charging_configs['stop_current']}")

                print(f"==========================Setting battery cut off capacity to: {charging_configs["stop_capacity"]} =================")
                self.emulator.write(f"BATT:STOP:CAP {charging_configs['stop_capacity']}")

                print(f"==========================Setting battery cut off time: {charging_configs["stop_time"]} =================")
                self.emulator.write(f"BATT:STOP:TIME {charging_configs['stop_time']}")
                

                #Check if the voltage has been set successfully
                voltage = self.emulator.query('BATT:CHAR:VOLT?')
                print(f"Charging voltage is: {voltage}")
                current = self.emulator.query('BATT:CHAR:CURR?')
                print(f"Charging current is: {current}")


                print(f"==========================Now switching on the emulator to start charging =================")
                self.emulator.write("BATT 1")
                self.emulator.write("OUTPUT ON")

                # if ((voltage <= CELL_MAX_VOLTAGE) and (voltage == charge_voltage)) and ((current <= CELL_MAX_CURRENT) and (current == charge_current)) :
                #     self.emulator.write("OUTPUT ON")

                output_status = int(self.emulator.query("OUTPUT?").strip("\n"))

                battery_charging_data = {} 
                record_key = 0

                while output_status == 1:
                    print(f"Entering record {record_key}")
                    record = {}
                    charge_record_key = test_cell+"char00"+str(record_key)
                    print(f"Entering record: {record_key}")
                    print(f"With record key {charge_record_key}")
                    record['Time_stamp'] = str(datetime.datetime.now())
                    record['Cell_voltage'] = self.emulator.query("MEAS:VOLT?").strip("\n")
                    record['Cell_current'] = self.emulator.query("MEAS:CURR?").strip("\n")
                    record['Cell_charging_capacity'] = self.emulator.query("MEAS:CAP?").strip("\n")
                    record['Ambient_temperature'] = self.emulator.query("MEAS:TEMP?").strip("\n")
                    print(record)
                    battery_charging_data[charge_record_key] = record
                    record_key += 1
                    output_status = int(self.emulator.query("OUTPUT?").strip("\n"))

                with open(f"{charging_configs['charge_data_path']}_charging_data_{str(datetime.datetime.now().date()).replace("-","_")}.json", "w") as outfile:
                    json.dump(battery_charging_data, outfile)

                print("Checking if any errors were generated during system configuration")
                print("ERROR", self.emulator.query("SYST:ERR?"))

        except Exception as e:
            print(f"Failed to set up the instrument for the charging process because of this error: {e}")


    def battery_discharge(self, **discharge_configs):
        try:
            #check if the emulator is on
            test_cell = discharge_configs['test_cell']
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('/n'))

            if emulator_status == 0:
                #Set the device to act as a batetry charger and set the charging values.
                #Check if the instrument is already on battery mode if so. 
                if int(self.emulator.query("BATT?").strip('/n'))  == 1:
                    self.emulator.write("BATT 0")
                
                print("==========================Setting emulator to Battery mode=================")
                self.emulator.write("BATT:MODE DISC")

                print(f"==========================Setting battery charging voltage to {discharge_configs["discharge_voltage"]} =================")
                self.emulator.write(f"BATT:DISC:VOLT {discharge_configs['discharge_voltage']}")

                print(f"==========================Setting battery charging current to {discharge_configs["discharge_current"]} =================")
                self.emulator.write(f"BATT:DISC:CURR {discharge_configs['discharge_current']}")

                print(f"==========================Setting battery cut off voltage to {discharge_configs["stop_voltage"]} =================")
                self.emulator.write(f"BATT:STOP:VOLT {discharge_configs['stop_voltage']}")

                print(f"==========================Setting battery cut off current to {discharge_configs["stop_current"]} =================")
                self.emulator.write(f"BATT:STOP:CURR {discharge_configs['stop_current']}")

                print(f"==========================Setting battery cut off capacity to {discharge_configs["stop_capacity"]} =================")
                self.emulator.write(f"BATT:STOP:CAP {discharge_configs['stop_capacity']}")
                
                print(f"==========================Setting battery cut off time {discharge_configs["stop_time"]} =================")
                self.emulator.write(f"BATT:STOP:TIME {discharge_configs['stop_time']}")

                print(f"==========================Now turning the Battery charge and output on emulator on to begin discharge process =================")
                self.emulator.write("BATT 1")
                self.emulator.write("OUTPUT 1")

                #Check if the voltage has been set successfully
                print("===========================Checking if the discharging voltage and current are set properly======================================")
                voltage = self.emulator.query('BATT:DISC:VOLT?').strip('/n')
                print(f"Discharging voltage is: {voltage}")
                current = self.emulator.query('BATT:DISC:CURR?')
                print(f"Discharging current is: {current}")

                #Measure and log the discharging data
                output_status = int(self.emulator.query("OUTP?").strip("\n"))

                battery_discharging_data = {} 
                record_key = 0

                while output_status == 1:
                    print(f"Entering record {record_key}")
                    record = {}
                    discharge_record_key = test_cell+"disc"+"00"+str(record_key)
                    print(f"With record key {discharge_record_key}")
                    record['Time_stamp'] = str(datetime.datetime.now())
                    record['Cell_disc_voltage'] = self.emulator.query("MEAS:VOLT?").strip("\n")
                    record['Cell_disc_current'] = self.emulator.query("MEAS:CURR?").strip("\n")
                    record['Cell_disc_capacity'] = self.emulator.query("MEAS:CAP?").strip("\n")
                    record['Ambient_temperature'] = self.emulator.query("MEAS:TEMP?").strip("\n")
                    print(record)
                    battery_discharging_data[discharge_record_key] = record
                    record_key += 1
                    output_status = int(self.emulator.query("OUTP?").strip("\n"))

            with open(f"{discharge_configs['discharge_data_path']}_dicharging_data_{str(datetime.datetime.now().date()).replace("-","_")}.json", "w") as outfile:
                    json.dump(battery_discharging_data, outfile)


        except Exception as e:
            print(f"Failed to set up the instrument for the discharging process because of this error: {e}")

    def log_measurements(self, operation ):
        battery_tests_ops = ("charging","discharging")
        if operation in battery_tests_ops:
            print(f"Currently running this process: {operation}")

            if operation == battery_tests_ops[0]:
                op = operation[:3].upper()
            elif operation == battery_tests_ops[1]:
                op = operation[:4].upper()

            # set_voltage = self.emulator.query(f"BATT:{op}:VOLT?")
            # set_current = self.emulator.query(f"BATT:{op}:CURR?")
            # set_time = self.emulator.query(f"BATT:{op}:TIME?")

        else:
            print(f"Invalid operation expection only these two operations {battery_tests_ops}")
                        
            

    def generate_pv_output():
        pass

def main(**kwaargs):

    test_num = str(sys.argv[1])
    cell_model = str(sys.argv[2])

    print(f"Running charge and discharge test {test_num} on cell {cell_model}.")

    #weather_data_paths = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/datasets/weather-2021.csv"
    base_path = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/python_code"

    
    config_path = base_path+"/configs/battery_cells/"+ cell_model+".json"
    print("Config path:", config_path)
    

    with open(config_path, 'r') as config_file:
        config = json.load(config_file)

    data_file_path = config['test']['output_path']+"test_"+test_num +"_cell_"+cell_model

    print("The data files will be written to this path: ", data_file_path)

    print("The test results data path is: ", data_file_path )

    solar_emulator = PVStorageEmulator(config['test']['emulator'])

    charging_configs = config['test']['Charge']

    discharging_configs = config['test']['Discharge']

    # print("==========================Starting Charging using the following Parameters============================")
    # print(charging_configs)
    # # #solar_emulator.get_device_status()
    # solar_emulator.battery_charger(
    #                                charge_data_path = data_file_path,
    #                                test_cell = cell_model,
    #                                charge_voltage = charging_configs['charge_voltage'],
    #                                charge_current = charging_configs['charge_current'],
    #                                stop_voltage = charging_configs['stop_voltage'],
    #                                stop_current = charging_configs['stop_current'],
    #                                stop_capacity = charging_configs['stop_capacity'],
    #                                stop_time = charging_configs['stop_time']
    #                                )
     
    # #wait for the charging process to finish
    # print("=================================================Charging is done ==========================================")

    print("==========================Now Discharging harging using the following Parameters============================")
    print(discharging_configs)

    solar_emulator.battery_discharge(
                                   discharge_data_path = data_file_path,
                                   test_cell = cell_model,
                                   discharge_voltage = discharging_configs['discharge_voltage'],
                                   discharge_current = discharging_configs['discharge_current'],
                                   stop_voltage = discharging_configs['stop_voltage'],
                                   stop_current = discharging_configs['stop_current'],
                                   stop_capacity = discharging_configs['stop_capacity'],
                                   stop_time = discharging_configs['stop_time']
    )


if __name__ == "__main__":
    main()