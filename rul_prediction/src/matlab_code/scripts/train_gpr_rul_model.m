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

charge_columns = ["Ambient_temperature", "Voltage_measured", "Current_measured", "Temperature_measured", "Current_charge", "Voltage_charge", "Charge_Time"]
discharge_columns = ["Ambient_temperature", "Voltage_measured", "Current_measured", "Temperature_measured", "Current_load", "Voltage_load", "Discharge_time","Capacity"]
features = ["Ambient_temperature", "Voltage_measured", "Current_measured", "Temperature_measured", "Current_load", "Voltage_load"]


bat_charge_seg = bat_charging_data(:,charge_columns);

bat_discharge_seg = bat_discharging_data(:,discharge_columns);

%ACalculate other features such state of charge.

%Get training and test data
split = 0.70;
%data_len = 
split_num = round(split*height(bat_discharge_seg))
logMessage = sprintf('The split number is %0.5g records.\n', split_num);
fprintf(logFile, logMessage);

bat_discharge_train = bat_discharge_seg(1:split_num,:);
X_bat_discharge_train = bat_discharge_train(:,features);
Y_bat_discharge_train = bat_discharge_train(:,[8]);

logMessage = sprintf('Training data has a total of %0.5g records.\n', height(bat_discharge_train));
fprintf(logFile, logMessage);

bat_discharge_test = bat_discharge_seg(split_num:end,:);
num_recs_test = height(bat_discharge_test)
X_bat_discharge_test = bat_discharge_test(:,features) ;
Y_bat_discharge_test = bat_discharge_test(:,["Capacity"]) ;

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

try

    gpr_options = struct(...
    'KernelFunction', 'squaredexponential', ... % Kernel function (other options include 'matern52', 'matern32', 'matern12', etc.)
    'Sigma', 0.2, ... % Initial noise standard deviation
    'Standardize', true ... % Standardize inputs and outputs
);
    rulModel = fitrgp(bat_discharge_train,'Capacity','KernelFunction','ardsquaredexponential',...
        'FitMethod','sr','PredictMethod','fic','Standardize',1);

    currentTime = datestr(now, 'yyyy-mm-dd HH:MM:SS');   
    logMessage = sprintf('The model was generated at:  %s', currentTime );
    fprintf(logFile, logMessage);
    disp(rulModel)


    % Save the GPR model to a .mat file
    save(base_path+model_path, 'rulModel');

    %logMessage = sprintf('Model informations is as follows.\n', rulModel);
    %fprintf(logFile, logMessage);


    %saveLearnerForCoder(rulMModel,'rulModel');

    %ypred = resubPredict(rulModel);
catch ME 
    switch ME.identifier
        case 'MATLAB:UndefinedFunction'
            warning('Function is undefined.  Assigning a value of NaN.');
            logMessage = sprintf('Function is undefined.  Assigning a value of NaN.\n', rulModel);
            fprintf(logFile, logMessage);
            rulModel = NaN;
            ypred = NaN;

        case 'MATLAB:scriptNotAFunction'
            warning(['Attempting to execute script as function. '...
                'Running script and assigning output a value of 0.']);
            notaFunction;
            rulModel = 0;
            ypred = 0;
        otherwise
            rethrow(ME)
            fprintf(logFile,ME)
            
    end
end


disp("=============================================================RUL prediction model training has completed. ======================================================================")


% Close the log file
fclose(logFile);