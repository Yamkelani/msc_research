clear all;
clc;


%% Read in data for battery charging and discharging.
base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src";
model_path = "/matlab_code/models/gpr_rul_model.mat";
model_name = "rul_model";

% Define the log file name and path
logFileName = 'logfile.txt';

% Open the log file in append mode
logFile = fopen(logFileName, 'a');

% Check if the file was opened successfully
if logFile == -1
    error('Failed to open log file.');
end

% Get the current date and time
currentTime = datestr(now, 'yyyy-mm-dd HH:MM:SS');

% Write a log message to the file
logMessage = sprintf('%s: Starting to run Feature engineering script.\n', currentTime);
fprintf(logFile, logMessage);

% Perform your MATLAB computations here
% For example:
% result = someFunction();

%Reading in data
bat_charging_data = readtable(base_path+"/datasets/all_batteries_charging_data.csv");
bat_discharging_data = readtable(base_path+"/datasets/all_batteries_discharging_data.csv");


logMessage = sprintf('Charging data has a total of %0.5g records.\n', height(bat_charging_data));
fprintf(logFile, logMessage);

logMessage = sprintf('Discharging data has a total of %0.5g records.\n', height(bat_discharging_data));
fprintf(logFile, logMessage);
