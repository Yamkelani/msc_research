battery_model = "IFR32700";
cell_number = 'cell2';

consolidate_charge_discharge_data(cell_number)

function consolidate_charge_discharge_data(cell_number)  
        base_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/';

        matlab_path = cell_number+"/matlab/csv_files/";
        csv_path = cell_number+"/csv/";
        em_src_dir = base_dir+csv_path;
        sim_src_dir = base_dir+matlab_path;
        dest_path = ['/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/consolidated/', cell_number];
        search_disch = 'dicharging';
        search_ch = 'charging';

        if ~exist(dest_path, 'dir')
            mkdir(dest_path);
        end
        
        
        em_files_list = dir(fullfile(em_src_dir, '*.csv'))
        sim_files_list = dir(fullfile(sim_src_dir, '*.csv'))
        
        
        for i = 1:length(em_files_list)
            %get the file name
            em_file_name = em_files_list(i).name;
            split_file_name = split(em_file_name, '_');
            cycle_number = split_file_name{3};
            len1 = length(split_file_name);
            split_last = split(split_file_name{len1},'.');

            for j = 1:length(sim_files_list)
                sim_file_name = sim_files_list(j).name;
                sim_items = split(sim_file_name, '_');
                sim_cycle = sim_items{2};
                if strcmp(cycle_number, sim_cycle)
                    sim_file_to_read = sim_file_name ;
                end

            end

            % cycle_date = [split_last{1}, '-', split_file_name{len1-1}, '-', split_file_name{len1-2}];
            em_file_path = fullfile(em_src_dir, em_file_name);
            sim_file_path = fullfile(sim_src_dir, sim_file_to_read);

	    disp(['Loading em file: ', em_file_name])	
            em_data =  readtable(em_file_path,'VariableNamingRule', 'preserve');
            em_data = removevars(em_data, {'Ambient_temperature', 'Cell_temperature'}) ;
            em_data.Time = (0:5:(height(em_data)-1)*5)';
	    disp(['Loading sim file: ', sim_file_to_read])
            sim_data = readtable(sim_file_path,'VariableNamingRule', 'preserve');

 	    if strcmp(search_disch, split_file_name{8})
                discharge = sim_data(height(em_data)+1:2*height(em_data),:);
                discharge = removevars(discharge, 'cell_model');
                discharge = removevars(discharge, 'cycle');
                discharge.Time = (0:5:(height(discharge)-1)*5)';
                cycle_data = join(em_data, discharge , 'Keys', 'Time');
                writetable(cycle_data, [dest_path,'/test_',cell_number,'_cycle_',cycle_number,'_discharge_data.csv'])
            end

            if strcmp(search_ch, split_file_name{8})
                charge = sim_data(1:height(em_data),:);
                charge.Time = (0:5:(height(charge)-1)*5)';
                cycle_charge_data = join(em_data, charge , 'Keys', 'Time');
                writetable(cycle_charge_data, [dest_path,'/test_',cell_number,'_cycle_',cycle_number,'_charge_data.csv'])
            end


            % %Display filename before processing it for prgress tracking. 
            % fprintf('File to load:  %s\n', file_name);
            % batt_tecst_data = load(file_path);
            % logged_data = batt_test_data.logsout;
            
    
            % target_file_name = strrep(file_name, '.mat', '');
            % processed_data = preprocess_data(logged_data);
            % writetable(processed_data,dest_path+target_file_name+'.csv');
        
        end
    end

