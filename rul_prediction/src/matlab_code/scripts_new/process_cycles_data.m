parent_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/cell3/';
cell = '3'
matlab_path = [parent_dir, 'unprocess_matlab_data/'];
csv_path = [parent_dir, 'unprocessed_data/'];
consolidated_path = [parent_dir, 'consolidated_data/consolidated_test_data_cell_',cell, '.csv']

mat_files_list = dir(fullfile(matlab_path, '*.mat'));
csv_files_list = dir(fullfile(csv_path, '*.csv'))
data = process_csv_files(csv_path, csv_files_list);
writetable(data, consolidated_path)


function em_data = process_csv_files(dir, paths)
    charge_columns = {'Battery_cell_model','Test_cell_number','Operation', 'Cycle', 'Time_stamp', 'Measured_cell_voltage',...
        'Measured_cell_current','Measured_cell_capacity', 'Charging_voltage',  'Charging_current', 'Ambient_temperature',...
         'Cell_temperature' }

    charging_data = table([],[],[],[],[],[],[],[],[],[],[],[], 'VariableNames', charge_columns)

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


    end

    em_data = charging_data;

end
