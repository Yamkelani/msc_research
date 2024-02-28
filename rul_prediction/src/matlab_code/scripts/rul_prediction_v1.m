%Read in data 

%Clear environment and variable to Prepare
clc;
clear;

%Data path

base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets";
bat_discharge_path = base_path+"battery_discharging_data.csv";
bat_charge_path = base_path +"battery_charging_data.csv";


%Create the folder if it does not exist
battery_folder = "BatteryFolder";

if ~exist(battery_folder,"dir")
    mkdir(battery_folder);
end

battery_charge_data = readtable(bat_charge_path);
battery_discharge_data = readtable(bat_discharge_path);

%Rename columns
for pos=1:numel(battery_charge_data.Properties.VariableNames)
    battery_charge_data.Properties.VariableNames{pos} =  


disp("Battery discharge data is:")
disp(size(battery_data))
disp(head(battery_data,3))

%Prepare data for modelling

head(battery_data, 5);

bat_y = battery_data(:,[10]);

[train] = battery_data([1:(0.6*height(battery_data))],[4 5 6 7 8 9 10]);
[Xtrain] = train(:,[1:6]);
[Ytrain] =`train(:,[7]);

%head(Xtrain,10)

[test] = battery_data([1:(0.4*height(battery_data))],[4 5 6 7 8 9 10]);
[Xtest] =train(:,[1:6]);
[Ytest] =train(:,[7]);

model_name = "BatteryCellRULPrediction";

