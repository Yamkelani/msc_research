charging_data_path = "C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\battery_experiments_data\experiments_data\test_001_cell_1_model_IFR32700_charging_data_2024_11_13.csv";
discharging_data_path = "C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\battery_experiments_data\experiments_data\test_001_cell_1_model_IFR32700_discharging_data_2024_11_13.csv";

charging_data = readtable(charging_data_path);
discharging_data = readtable(discharging_data_path);

%Plot charging data

plot(charging_data.Time_stamp,[charging_data.Measured_cell_capacity, charging_data.Measured_cell_current, charging_data.Measured_cell_voltage])

legend('Cell Capacity','Measured_Cell_Current','Measured_Cell_Voltage')

xlabel('Time')
ylabel('Battery_paramter')

plot(discharging_data.Time_stamp,[discharging_data.Measured_cell_capacity, discharging_data.Measured_cell_current, discharging_data.Measured_cell_voltage])
legend('Cell Capacity','Measured_Cell_Current','Measured_Cell_Voltage')

xlabel('Time')
ylabel('Battery_paramter')
