parent_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/cell3/';
cell = '3'
matlab_path = [parent_dir, 'unprocess_matlab_data/'];
csv_path = [parent_dir, 'unprocessed_data/'];
charge_path = [parent_dir, 'consolidated_data/charge_consolidated_test_data_cell_',cell, '.csv']
discharge_path = [parent_dir, 'consolidated_data/discharge_consolidated_test_data_cell_',cell, '.csv']

mat_files_list = dir(fullfile(matlab_path, '*.mat'));
csv_files_list = dir(fullfile(csv_path, '*.csv'))
[charge_data, discharge_data] = process_csv_files(csv_path, csv_files_list);
writetable(charge_data, charge_path)
writetable(discharge_data, discharge_path)


function [charging_data, discharging_data] = process_csv_files(dir, paths)
    charge_columns = {'Battery_cell_model','Test_cell_number','Operation', 'Cycle', 'Time_stamp', 'Measured_cell_voltage',...
        'Measured_cell_current','Measured_cell_capacity', 'Charging_voltage',  'Charging_current', 'Ambient_temperature',...
         'Cell_temperature' }
    discharge_columns = {'Battery_cell_model','Test_cell_number','Operation', 'Cycle', 'Time_stamp', 'Measured_cell_voltage',...
            'Measured_cell_current','Measured_cell_capacity', 'Discharging_voltage',  'Discharging_current', 'Ambient_temperature',...
             'Cell_temperature' }

    charging_data = table([],[],[],[],[],[],[],[],[],[],[],[], 'VariableNames', charge_columns)
    discharging_data = table([],[],[],[],[],[],[],[],[],[],[],[], 'VariableNames', discharge_columns)

    for i = 1:length(paths)
        file_path = fullfile(dir, paths(i).name)
        opts = detectImportOptions(file_path);
        opts.VariableNamingRule = 'preserve';

        disp(['Adding file ', paths(i).name])

        if contains(file_path, '_charging')
            charge_data = readtable(file_path, opts);
            charge_data(:, 'Var1') = [];
            charge_data.Properties.VariableNames;
            charging_data = [charging_data; charge_data];
        end
        if contains(file_path, '_discharging')
            discharge_data = readtable(file_path, opts);
            discharge_data(:, 'Var1') = [];
            discharge_data.Properties.VariableNames
            discharging_data = [discharging_data; discharge_data];
        end


    end

end
