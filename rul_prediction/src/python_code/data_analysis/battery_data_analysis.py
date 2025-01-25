import pandas as pd
import matplotlib.pyplot as plt



def main():
    charging_data_path = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/experiments_data/test_004_cell_ICR18650_charging_data_2024_11_12.csv"
    discharging_data_path = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/experiments_data/test_004_cell_ICR18650_discharging_data_2024_11_12.csv"
    battery_charging_data = pd.read_csv(charging_data_path)
    battery_charging_data = pd.read_csv(discharging_data_path) 

    #Plot the capacity, current and voltage curves
    # plot multiple columns such as population and year from dataframe
    battery_charging_data.plot(x="Time_stamp", y=["Measured_cell_voltage", "Measured_cell_current",  "Measured_cell_capacity"],
        kind="line", figsize=(100, 100))
 
    # display plot
    plt.show()





if __name__ == 'main':
    main()