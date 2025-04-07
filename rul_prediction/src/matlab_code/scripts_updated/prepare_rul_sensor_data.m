%This code reads in mat lab files that contain the data logs from simulink and 
% restructures then saves the data in a csv for further processing.
battery_model = "IFR32700";
cell_number = 'cell1';
prepare_matlab_data(cell_number, battery_model)

function prepare_matlab_data(cell_number, model)    
    base_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/';

    matlab_path = [cell_number,'/matlab/many_cycles/'];
    src_dir = [base_dir, matlab_path]
    dest_path = [base_dir, cell_number ,'/matlab/csv_files/'];
    
    
    mat_files_list = dir(fullfile(src_dir, '*.mat'));
    
    
    for i = 1:length(mat_files_list)
        %get the file name
        file_name = mat_files_list(i).name;
        split_file_name = split(file_name, '_');
        len1 = length(split_file_name);
        split_last = split(split_file_name{len1},'.');
        cycle_date = [split_last{1}, '-', split_file_name{len1-1}, '-', split_file_name{len1-2}];
        file_path = fullfile(src_dir, file_name);
        
        %Display filename before processing it for prgress tracking. 
        fprintf('File to load:  %s\n', file_name);
        
        batt_test_data = load(file_path)
        
        if isfield(batt_test_data, 'logsout')
            logged_data = batt_test_data.logsout;
        else
            logged_data = batt_test_data.data
        end

        target_file_name = strrep(file_name, '.mat', '');
        processed_data = preprocess_data(logged_data);
        processed_data.cell_model = repmat(model, height(processed_data), 1);
        processed_data.cell_number = repmat(split_file_name{4}, height(processed_data), 1);
        processed_data.cycle =  repmat(split_file_name{2}, height(processed_data), 1);
        processed_data.date =  repmat(cycle_date, height(processed_data), 1);
        writetable(processed_data,[dest_path,target_file_name,'.csv']);
    
    end
end
    
    

function battery_data = preprocess_data(raw_data)
    % this function structures the data in a tabular format to make it easier to be stored in a csv.
    battery_data = table(raw_data{1}.Values.Time,raw_data{1}.Values.Data, raw_data{2}.Values.Data, raw_data{3}.Values.Data, raw_data{4}.Values.Data);

    %rename columns
    battery_data.Properties.VariableNames = {'Time','Voltage','Current','Cell_temperature','Room_temperature'};

end






