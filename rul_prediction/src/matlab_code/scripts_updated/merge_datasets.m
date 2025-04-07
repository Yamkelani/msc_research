base_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/consolidated/cell2/';

dataset_90_discharge = readtable([base_dir,'test_cell2_cycle_090_discharge_data.csv']);
cap_max = dataset_90_discharge(dataset_90_discharge.Time==1815,:)
% dataset_90A_discharge = readtable([base_dir,'test_cell2_cycle_090A_discharge_data.csv']);
% dataset_90B_discharge = readtable([base_dir,'test_cell2_cycle_090B_discharge_data.csv']);

% dataset_90A_discharge.Cycle = repmat({90}, height(dataset_90A_discharge), 1);
% dataset_90B_discharge.Cycle = repmat({90}, height(dataset_90B_discharge), 1);



% if ~iscell(dataset_90_discharge.Cycle)
%     dataset_90_discharge.Cycle = num2cell(dataset_90_discharge.Cycle);
% end
% if ~iscell(dataset_90A_discharge.Cycle)
%     dataset_90A_discharge.Cycle = num2cell(dataset_90A_discharge.Cycle);
% end
% if ~iscell(dataset_90B_discharge.Cycle)
%     dataset_90B_discharge.Cycle = num2cell(dataset_90B_discharge.Cycle);
% end


% dataset = [[dataset_90_discharge; dataset_90A_discharge]; dataset_90B_discharge];
writetable(cap_max, [base_dir, 'cap_max.csv'])

% disp(['The length of the first dataset: ',num2str(height(dataset_90_discharge))])
% disp(['The length of the second dataset: ',num2str(height(dataset_90A_discharge))])
% discycle_001_charge.Cycle = repmat({'1}, height(cycle_001_charge), 1);p(['The length of the third dataset: ',num2str(height(dataset_90B_discharge))]) 
% disp(['The length of the appended dataset: ',num2str(height(dataset))]) 
