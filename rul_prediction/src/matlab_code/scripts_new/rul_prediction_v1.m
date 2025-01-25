%Read in data 

%Clear environment and variable to Prepare
clc;
clear;


%Data path

base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src";
bat_discharge_path = base_path+"/datasets/battery_discharging_data.csv";
bat_charge_path = base_path +"/datasets/battery_charging_data.csv";


%Create the folder if it does not already exist
battery_folder = base_path+"/models";

if ~exist(battery_folder,"dir")
    mkdir(battery_folder);
end

battery_charge_data = readtable(bat_charge_path);
battery_discharge_data = readtable(bat_discharge_path);

%Rename columns
battery_charge_data = rename_columns(battery_charge_data , 'charge');
battery_discharge_data = rename_columns(battery_discharge_data , 'discharge');

disp(battery_charge_data.Properties.VariableNames)
disp(battery_discharge_data.Properties.VariableNames)

disp("Battery discharge data is:")
disp(size(battery_discharge_data))
disp(head(battery_discharge_data,3))


disp("Battery charging data is:")
disp(size(battery_charge_data))
disp(head(battery_charge_data,3))

%Prepare data for modelling
battery_data = join(battery_charge_data, battery_discharge_data)
head(battery_data, 5);

bat_y = battery_data(:,[10]);

[train] = battery_data([1:(0.6*height(battery_data))],[4 5 6 7 8 9 10]);
[Xtrain] = train(:,[1:6]);
%[Ytrain] =`train(:,[7]);

%head(Xtrain,10)

[test] = battery_data([1:(0.4*height(battery_data))],[4 5 6 7 8 9 10]);
[Xtest] = train(:,[1:6]);
%[Ytest] = train(:,[7]);

model_name = "BatteryCellRULPrediction";

function new_dataset = rename_columns(dataset, prefix)
    num_of_variables = length(dataset.Properties.VariableNames);
    varNames = cell(1, num_of_variables);

    for pos=1:num_of_variables
        varNames{pos} = [append(prefix,'_') dataset.Properties.VariableNames{pos}]; 
    end

    dataset.Properties.VariableNames = varNames;
    new_dataset = dataset;
end