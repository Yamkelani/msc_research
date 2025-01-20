%Prepare data


function prepare_matlab_data()    
    bat_data_dir = "C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\battery_experiments_data\experiments_data\matlab_datasets";
    
    mat_files_list = dir(fullfile(bat_data_dir, '*.mat'));
    
    
    for i = 1:length(mat_files_list)
        %get the file name
    
        file_name = mat_files_list(i).name;
    
        file_path = fullfile(bat_data_dir, file_name);
        %Display progress
        fprintf('File to load:  %s\n', file_name);
        test_data = load(file_path);
        logged_data = test_data.logsout;


        processed_data = preprocess_data(raw_data);
        writetable(process_data,'/csv_files/test_001_cell_1_model_if32700_charging_13_11_2024.csv')
    
    end
end
    
    

function battery_data = preprocess_data(raw_data)
    % this function structures the data in the required format
    battery_data = table(raw_data{1}.Values.Time, raw_data{2}.Values.Data, raw_data{3}.Values.Data, raw_data{4}.Values.Data)

    %rename columns
    battery_data.Properties.VariableNames = {'Time','Voltage','Current','Cell_temperature','Room_temperature'}

end






