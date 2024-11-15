"""
This code is for charging and discharging any battery cell using the Itech regenerative power supply.
Remember to create a config file for the cell that you want to charge.
Specify the charging and discharging parameters as shown in the cell datasheet.
When running this code in the termina use the following command. Also make sure you are in th eright directory 
, where this file is located.
python .\test_battery_cell.py 001 ICR18650
python .\test_battery_cell.py 001 IFR32700 
"""


import pyvisa as pvs
import pandas as pd
import logging
import datetime
import time
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
        charge_columns = ['Battery_cell_model','Test_cell_number','Operation','Cycle','Time_stamp','Measured_cell_voltage','Measured_cell_current','Measured_cell_capacity','Charging_voltage','Charging_current','Ambient_temperature',"Cell_temperature"]
        discharge_columns = ['Battery_cell_model','Test_cell_number','Operation','Cycle','Time_stamp','Measured_cell_voltage','Measured_cell_current','Measured_cell_capacity','Discharging_voltage','Discharging_current','Ambient_temperature',"Cell_temperature"]
        self.charging_data = pd.DataFrame(columns = charge_columns) 
        self.discharging_data = pd.DataFrame(columns = discharge_columns) 
        self.seasons = ['summer','autum','winter','spring']

    def get_device_status(self):
        print("The divice status is:", self.emulator.query("'*IDN?'"))

    def ingest_irrad_data(paths):
        datasets = []
        for path in paths:
            datasets.append(pd.read_csv(path,header=0))
        return datasets

    def seasons_simulator(self):
        #Get season pv output
        #charge the battery cell
        self.battery_charge()
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

    def battery_charge(self, **charging_configs):
        try:
            test_cell = charging_configs['test_cell']
            charging_file_path = f"{charging_configs['charge_data_path']}_charging_data_{str(datetime.datetime.now().date()).replace("-","_")}"
            #check if the emulator is on
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('/n'))
            print(f"The status of the emulator is {emulator_status}")

            if emulator_status == 1:
                self.emulator.write("OUTP 0")
                emulator_status = int(self.emulator.query("OUTP:STAT?").strip('/n'))
            if emulator_status == 0:
                if int(self.emulator.query("BATT?").strip('/n'))  == 1:
                    self.emulator.write("BATT 0")
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

                battery_charging_data['charging_parameters'] = charging_configs
                record_key = 0

                while output_status == 1:
                    print(f"Entering record {record_key}")
                    record = {}
                    charge_record_key = test_cell+"char00"+str(record_key)
                    print(f"Entering record: {record_key}")
                    print(f"With record key {charge_record_key}")
                    record['Battery_cell_model'] = test_cell
                    record['Operation'] = 'Charging'
                    record['Cycle'] = charging_configs['test_cycle']
                    record['Test_cell_number'] = charging_configs['cell_num']
                    record['Time_stamp'] = str(datetime.datetime.now())
                    record['Measured_cell_voltage'] = self.emulator.query("MEAS:VOLT?").strip("\n")
                    record['Measured_cell_current'] = self.emulator.query("MEAS:CURR?").strip("\n")
                    record['Measured_cell_capacity'] = self.emulator.query("MEAS:CAP?").strip("\n")
                    record['Charging_voltage'] = charging_configs['charge_voltage']
                    record['Charging_current'] = charging_configs['charge_current']
                    record['Ambient_temperature'] = None
                    record['Cell_temperature'] = None
                    data_record = pd.DataFrame([record])
                    print(record)
                    self.log_measurements('charging', data_record )
                    battery_charging_data[charge_record_key] = record
                    record_key += 1
                    output_status = int(self.emulator.query("OUTPUT?").strip("\n"))
                    time.sleep(5)

                with open(charging_file_path+".json", "w") as outfile:
                    json.dump(battery_charging_data, outfile)

                self.charging_data.to_csv(charging_file_path+".csv")

                print("Checking if any errors were generated during system configuration")
                print("ERROR", self.emulator.query("SYST:ERR?"))

        except Exception as e:
            print(f"Failed to set up the instrument for the charging process because of this error: {e}")
            raise e


    def battery_discharge(self, **discharge_configs):
        try:
            #check if the emulator is on
            test_cell = discharge_configs['test_cell']
            discharging_file_path = f"{discharge_configs['discharge_data_path']}_dicharging_data_{str(datetime.datetime.now().date()).replace("-","_")}"
            emulator_status = int(self.emulator.query("OUTP:STAT?").strip('/n'))

            if emulator_status == 1:
                self.emulator.write("OUTP 0")
            if emulator_status == 0:
                if int(self.emulator.query("BATT?").strip('/n'))  == 1:
                    self.emulator.write("BATT 0")
                #Set the device to act as a batetry charger and set the charging values.
                #Check if the instrument is already on battery mode if so. 
                
                print("==========================Setting emulator to Battery mode=================")
                self.emulator.write("BATT:MODE DISC")

                print(f"==========================Setting battery discharging voltage to {discharge_configs["discharge_voltage"]} =================")
                self.emulator.write(f"BATT:DISC:VOLT {discharge_configs['discharge_voltage']}")

                print(f"==========================Setting battery discharging current to {discharge_configs["discharge_current"]} =================")
                self.emulator.write(f"BATT:DISC:CURR {discharge_configs['discharge_current']}")

                print(f"==========================Setting battery discharge cut off voltage to {discharge_configs["stop_voltage"]} =================")
                self.emulator.write(f"BATT:STOP:VOLT {discharge_configs['stop_voltage']}")

                print(f"==========================Setting battery discharge cut off current to {discharge_configs["stop_current"]} =================")
                self.emulator.write(f"BATT:STOP:CURR {discharge_configs['stop_current']}")

                print(f"==========================Setting battery discharge cut off capacity to {discharge_configs["stop_capacity"]} =================")
                self.emulator.write(f"BATT:STOP:CAP {discharge_configs['stop_capacity']}")
                
                print(f"==========================Setting battery discharge cut off time {discharge_configs["stop_time"]} =================")
                self.emulator.write(f"BATT:STOP:TIME {discharge_configs['stop_time']}")

                print(f"==========================Now turning the Battery process and output on emulator on to begin discharge process =================")
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
                battery_discharging_data['discharging_parameters'] = discharge_configs


                while output_status == 1:
                    print(f"Entering record {record_key}")
                    record = {}
                    discharge_record_key = test_cell+"disc"+"00"+str(record_key)
                    print(f"With record key {discharge_record_key}")
                    record['Battery_cell_model'] = test_cell
                    record['Operation'] = 'Discharging'
                    record['Cycle'] = discharge_configs['test_cycle']
                    record['Test_cell_number'] = discharge_configs['cell_num']
                    record['Time_stamp'] = str(datetime.datetime.now())
                    record['Measured_cell_voltage'] = self.emulator.query("MEAS:VOLT?").strip("\n")
                    record['Measured_cell_current'] = self.emulator.query("MEAS:CURR?").strip("\n")
                    record['Measured_cell_capacity'] = self.emulator.query("MEAS:CAP?").strip("\n")
                    record['Discharging_voltage'] = discharge_configs['discharge_voltage']
                    record['Discharging_current'] = discharge_configs['discharge_current']
                    record['Ambient_temperature'] = None
                    record['Cell_temperature'] = None

                    data_record = pd.DataFrame([record])
                    print(record)
                    battery_discharging_data[discharge_record_key] = record
                    self.log_measurements('discharging', data_record )
                    record_key += 1
                    output_status = int(self.emulator.query("OUTP?").strip("\n"))
                    time.sleep(5)

            

            with open(discharging_file_path+".json", "w") as outfile:
                    json.dump(battery_discharging_data, outfile)

            self.discharging_data.to_csv(discharging_file_path+".csv")


        except Exception as e:
            print(f"Failed to set up the instrument for the discharging process because of this error: {e}")
            raise e

    def log_measurements(self, operation, data ):
        if operation == 'charging':
            self.charging_data = pd.concat([self.charging_data, data])
        elif operation == 'discharging':
            self.discharging_data = pd.concat([self.discharging_data, data])
                        
            

    def generate_pv_output():
        pass

def main(**kwaargs):

    test_num = str(sys.argv[1])
    cell_model = str(sys.argv[2])
    test_cell_number = int(sys.argv[3])
    season = str(sys.argv[4])

    print(f"Running charge and discharge test {test_num} on cell {cell_model}.")

    #weather_data_paths = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/datasets/weather-2021.csv"
    base_path = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/python_code"

    
    config_path = base_path+"/configs/battery_cells/"+ cell_model+".json"
    
    with open(config_path, 'r') as config_file:
        config = json.load(config_file)

    data_file_path = config['test']['output_path']+"test_"+season+"_"+test_num +"_cell_"+str(test_cell_number)+"_model_"+cell_model

    print("The data files will be written to this path: ", data_file_path)

    print("The battery data path is: ", data_file_path )

    solar_emulator = PVStorageEmulator(config['test']['emulator'])

    charging_configs = config['test']['Charge']

    discharging_configs = config['test']['Discharge']

    print("==========================Starting Charging using the following Parameters============================")
    print(charging_configs)
    
    solar_emulator.battery_charge(
                                   test_cycle = test_num,
                                   cell_num = test_cell_number,
                                   charge_data_path = data_file_path,
                                   test_cell = cell_model,
                                   charge_voltage = charging_configs['charge_voltage'],
                                   charge_current = charging_configs['charge_current'],
                                   stop_voltage = charging_configs['stop_voltage'],
                                   stop_current = charging_configs['stop_current'],
                                   stop_capacity = charging_configs['stop_capacity'],
                                   stop_time = charging_configs['stop_time']
                                   )
    
    print("=================================================Charging is done ==========================================")

    #wait for the charging process to finish
   

    print("==========================Starting Discharging using the following Parameters============================")
    print(discharging_configs)

    solar_emulator.battery_discharge(
                                   test_cycle = test_num,
                                   cell_num = test_cell_number,
                                   discharge_data_path = data_file_path,
                                   test_cell = cell_model,
                                   discharge_voltage = discharging_configs['discharge_voltage'],
                                   discharge_current = discharging_configs['discharge_current'],
                                   stop_voltage = discharging_configs['stop_voltage'],
                                   stop_current = discharging_configs['stop_current'],
                                   stop_capacity = discharging_configs['stop_capacity'],
                                   stop_time = discharging_configs['stop_time']
    )

    time.sleep(300)

    print("=================================================Disharging is done ==========================================")
    

if __name__ == "__main__":
    main()