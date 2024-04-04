clear all;
clc;


%% Read in data for battery charging and discharging.
base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src";
model_path = "/matlab_code/models/";
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


bat_charge_seg = bat_charging_data(:,[3,5,6,7,8,9,10]);

bat_discharge_seg = bat_discharging_data(:,[3,5,6,7,8,9,10,11]);

%ACalculate other features such state of charge.

%Get training and test data
split = 0.70;
%data_len = 
split_num = round(split*height(bat_discharge_seg))
logMessage = sprintf('The split number is %0.5g records.\n', split_num);
fprintf(logFile, logMessage);

bat_discharge_train = bat_discharge_seg(1:split_num,:);
X_bat_discharge_train = bat_discharge_train(:,[1,2,3,4,5,6,7]);
Y_bat_discharge_train = bat_discharge_train(:,[8]);

logMessage = sprintf('Training data has a total of %0.5g records.\n', height(bat_discharge_train));
fprintf(logFile, logMessage);

bat_discharge_test = bat_discharge_seg(split_num:end,:);
num_recs_test = height(bat_discharge_test)
X_bat_discharge_test = bat_discharge_test(:,[1,2,3,4,5,6,7]) ;
Y_bat_discharge_test = bat_discharge_test(:,[8]) ;

logMessage = sprintf('Testing data has a total of %0.5g records.\n', num_recs_test);
fprintf(logFile, logMessage);

disp("The input X battery discharging training data is as follows");
disp(head(X_bat_discharge_train , 10));

disp("The Y target training data is as follows");
disp(head(Y_bat_discharge_train , 10));

disp("The input Y target test battery discharge data is as follows");
disp(head(X_bat_discharge_test, 10));
disp("The Y target test battery discharging data is as follows");
disp(head(Y_bat_discharge_test, 10));

%Train model.
disp("============================================================== Now training RUL prediction model ==============================================================================")

logMessage = sprintf('============================================================== Now training RUL prediction model ==============================================================================.\n', height(bat_discharge_test));
fprintf(logFile, logMessage);

rulModel = fitrgp(bat_discharge_train,'Capacity','KernelFunction','ardsquaredexponential',...
      'FitMethod','sr','PredictMethod','fic','Standardize',1);


logMessage = sprintf('Model informations is as follows.\n', rulModel);
fprintf(logFile, logMessage);


saveLearnerForCoder(rulMModel,'MyModel');

ypred = resubPredict(rulMdl);


disp("=============================================================RUL prediction model training has completed. ======================================================================")

disp("The trained model is shown below:")

print(rul_model)

% Close the log file
fclose(logFile);