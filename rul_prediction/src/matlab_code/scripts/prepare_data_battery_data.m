%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This code reads in battery data and prepares it for the rul prediction model.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear; close all; clc

%Data paths and file names
base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/";
b0005_path = "B0005.mat";
b0006_path = "B0006.mat";
b0007_path = "B0007.mat";
b0018_path = "B0018.mat";

%Read in the data for each battery
b0005_data = load(base_path+b0005_path);
b0006_data = load(base_path+b0006_path);
b0007_data = load(base_path+b0007_path);
b0018_data = load(base_path+b0018_path);

% Generate all the battery charging datasets 
b0005_charge = generate_charge_dataset(b0005_data.B0005);
b0006_charge = generate_charge_dataset(b0006_data.B0006);
b0007_charge = generate_charge_dataset(b0007_data.B0007);
b0018_charge = generate_charge_dataset(b0018_data.B0018);

%Combine all the charge datasets into one dataset
battery_charge = [b0005_charge, b0006_charge, b0007_charge, b0018_charge];
writetable(battery_charge, base_path+"all_batteries_charging_data.csv");

% Generate all the battery discharging datasets 
b0005_discharge = generate_discharge_dataset(b0005_data.B0005);
b0006_discharge = generate_discharge_dataset(b0006_data.B0006);
b0007_discharge = generate_discharge_dataset(b0007_data.B0007);
b0018_discharge = generate_discharge_dataset(b0018_data.B0018);

%Combine all the charge datasets into one dataset
battery_discharge = [b0005_discharge, b0006_discharge, b0007_discharge, b0018_discharge];
writetable(battery_discharge, base_path+"all_batteries_discharging_data.csv");

%Some batteries continued from the first run into the second. We append 
%those to the first batch before continuing.

function charge_dataset = generate_charge_dataset(bat_struct)
    num_of_cycles = length(bat_struct.cycle);
    battery_data = table;
    for i = 1:num_of_cycles
        if strcmp(bat_struct.cycle(i).type,'charge')
            bat_temp = table(bat_struct.cycle(i).type,...
                bat_struct.cycle(i).ambient_temperature,...
                bat_struct.cycle(i).time,...
                bat_struct.cycle(1).data.Voltage_measured, ....
                bat_struct.cycle(i).data.Current_measured, ...
                bat_struct.cycle(i).data.Temperature_measured, ...
                bat_struct.cycle(i).data.Current_charge, ...
                bat_struct.cycle(i).data.Voltage_charge,...
                bat_struct.cycle(1).data.Time,...
                'VariableNames', {'Type','Ambient_temperature','Time','Voltage_measured', 'Current_measured', 'Temperature_measured','Current_charge','Voltage_charge','Charge_Time'});
            battery_data = [battery_data;bat_temp];
        end
    end
    charge_dataset = battery_data;
end

function discharge_dataset = generate_discharge_dataset(bat_struct)
    num_of_cycles = length(bat_struct.cycle);
    battery_data = table;
    for i = 1:num_of_cycles
        if strcmp(bat_struct.cycle(i).type,'discharge')
            bat_temp = table(bat_struct.cycle(i).type,...
                bat_struct.cycle(i).ambient_temperature,...
                bat_struct.cycle(i).time,...
                bat_struct.cycle(i).data.Voltage_measured, ...
                bat_struct.cycle(i).data.Current_measured, ...
                bat_struct.cycle(i).data.Temperature_measured, ...
                bat_struct.cycle(i).data.Current_load, ...
                bat_struct.cycle(i).data.Voltage_load,...
                bat_struct.cycle(i).data.Time,...
                bat_struct.cycle(i).data.Capacity,...
                'VariableNames', {'Type', 'Ambient_temperature','Time','Voltage_measured', 'Current_measured', 'Temperature_measured','Current_load', 'Voltage_load','Discharge_time', 'Capacity'});
            battery_data = [battery_data;bat_temp];
        end
    end
    discharge_dataset = battery_data;
end
