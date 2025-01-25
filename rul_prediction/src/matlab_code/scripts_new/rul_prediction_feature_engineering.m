%The features required for remaining useful ife prediction are as follows
% Charge time,
%discharge time,
%Max charge current
%max discharge current
%RUL 
%Capacity drop
%Capacity
%no of cycles
%time to max voltage (3.6V)
%CC time 
%CV time
%state of charge
%state of health
%average_room_temperature
%max_room_temperature
%max_cell_temperature
%average_cell_temperature

base_dir = "/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/consolidated/cell2";
csv_path = "";


%Can be obtained from the data sheet.
total_battery_cycles = 2800; 
nominal_capacity = 6.0; % This is the battery cell nominal capacity as per the data sheet.

feature_table_cols = {'cycle_no','cycle_rul','capacity','capacity_drop','cc_time','cycle_charge_time',...
'cv_time','soc','soh','charge_time','average_room_temperature','average_cell_temperature'};

rul_features = table('Size', [0, length(feature_table_cols)], ...
                   'VariableTypes', repmat("double", 1, length(feature_table_cols)), ...
                   'VariableNames', feature_table_cols)


data_files_list = dir(base_dir);
data_file_names = {data_files_list.name};
charge_data_files_list = data_file_names(contains(data_file_names, '_charge_','IgnoreCase',true));
disp(['Number of charge files is: ', num2str(length(charge_data_files_list))]);
discharge_data_files_list = data_file_names(contains(data_file_names, 'discharge','IgnoreCase',true));

disp(['Number of discharge file is:: ', num2str(length(discharge_data_files_list))]);

for i = 1:length(discharge_data_files_list)
    %get the file name
    disp("===============Charge files list======================")
    if i <= 100
        charge_data_file_name = charge_data_files_list(i)
    end;
    disp("===============Discharge files list======================")
    discharge_data_file_name = discharge_data_files_list(i)
    % split_file_name = split(em_file_name, '_');
    % cycle_number = split_file_name{3};
    % len1 = length(split_file_name);
    % split_last = split(split_file_name{len1})
end
% function dateset = generate_features(battery_charge_data, battery_discharge_data) 
%     %Add the features for each cycle. 
%     max_capacity = max(battery_charge_data.Measured_cell_capacity);                  
%     cycle_no = battery_charge_data.Cycle(1);
%     capacity = max_capacity;
%     capacity_drop_per_cycle = nominal_capacity - max_capacity ;
%     cell_rul = total_battery_cycles - cycle_no;
%     max_charge_time = max(battery_charge_data.Time);
%     cycle_soc = max_capacity/nominal_capacity;

%     %Get constant current
%     max_charge_voltage = max(battery_charge_data.Measured_voltage);
%     charge_cc_time = battery_charge_data.Time(battery_charge_data.Measured_voltage <= max_voltage);
%     time_to_max_voltage = cc_charge_time;

%     %Get constant voltage time
%     min_charge_voltage = min(battery_charge_data.Measured_voltage);
%     min_voltage_time = battery_charge_data.Time(battery_charge_data.Measured_voltage == min_voltage);
%     max_voltage_time = battery_charge_data.Time(battery_charge_data.Measured_voltage == max_voltage);
%     charge_cv_time = min_voltage_time - max_voltage_time;
%     avg_amb_temperature = mean(battery_charge_data.Room_temperature);
%     avg_cycle_cell_temperature = mean(battery_charge_data.Cell_temperature);
%     max_charge_room_temperature = max(battery_charge_data.Room_temperature);
%     max_charge_cell_temperature = max(battery_charge_data)
%     max_charge_current = max(battery_charge_data.Measured_cell_current);
%     max_charge_voltage = max(battery_charge_data.Measured_voltage);
%     max_discharge_current = max(battery_charge_data.Measured_cell_current);
%     max_discharge_voltage = max(battery_charge_data.Measured_voltage);
%     cycle_charge_time = max(battery_charge_data.Time);
%     cycle_discharge_time = max(battery_discharge_data.Time);
%     time_at_max_voltage = battery_charge_data.Time(battery_charge_data.Measured_voltage == max_voltage);

%     %Create the features dataset
%     rul_features = [rul_features; 
%     {
%         cycle_no,...
%         cell_rul,... 
%         capacity,... 
%         capacity_drop,...
%         cycle_charge_time,...
%         charge_cv_time,...
%         charge_cc_time,... 
%         min_charge_voltage,..
%         max_charge_voltage,...
%         max_charge_current,...
%         max_charge_voltage,...
%         max_charge_room_temperature,...
%         max_charge_cell_temperature,...
%         max_charge_room_temperature,...
%         avg_cell_temperature...
%         cycle_discharge_time,...
%         max_discharge_current,...
%         max_discharge_voltage,...
%         avg_cell_temperature,...
%         capacity_drop_per_cycle,...
%         cycle_soc,
%     }
%     ]



% rul_features.soc
% rul_features.soh
% rul_features.rul
% rul_features.charge_time



% function features = extract_battery_features()
%     charge_time = Measured_cell_capacity
