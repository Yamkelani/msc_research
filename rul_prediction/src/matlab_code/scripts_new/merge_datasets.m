base_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/consolidated/cell2/';

dataset_90_discharge = readtable([base_dir,'test_cell2_cycle_090_discharge_data.csv']);
%dataset_90_discharge = dataset_90_discharge(1:3101,:);
cap1 = dataset_90_discharge(dataset_90_discharge.Time == 1815,:)
disp(['The length of the cycle 90 charge dataset: ',num2str(height(dataset_90_discharge))])

writetable(cap1, [base_dir, 'test_cap1.csv'])

% dataset_90_discharge = readtable([base_dir,'test_cell2_cycle_090_discharge_data.csv']);
% dataset_90A_discharge = readtable([base_dir,'test_cell2_cycle_090A_discharge_data.csv']);
% dataset_90B_discharge = readtable([base_dir,'test_cell2_cycle_090B_discharge_data.csv']);

% dataset_90A_discharge.Cycle = repmat({'090'}, height(dataset_90A_discharge), 1);
% dataset_90B_discharge.Cycle = repmat({'090'}, height(dataset_90B_discharge), 1);



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
% writetable(dataset, [base_dir, 'test_cell2_cycle_090_discharge_data.csv'])

% disp(['The length of the first dataset: ',num2str(height(dataset_90_discharge))])
% disp(['The length of the second dataset: ',num2str(height(dataset_90A_discharge))])
% disp(['The length of the third dataset: ',num2str(height(dataset_90B_discharge))]) 
% disp(['The length of the appended dataset: ',num2str(height(dataset))]) 
