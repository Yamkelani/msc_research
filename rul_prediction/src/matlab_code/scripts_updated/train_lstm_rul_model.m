clear all;
clc;


%% Read in data for battery charging and discharging.
base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src";
model_path = "/matlab_code/models/lstm_rul_model.mat";
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
logMessage = sprintf('%s: Starting to run feature engineering script.\n', currentTime);
fprintf(logFile, logMessage);


%Reading in data
features_data = readtable([base_path,'/datasets/features/rul_features.csv']);


logMessage = sprintf('The rul prediction features data has a total of %0.5g records.\n', height(features_data));
fprintf(logFile, logMessage);

epochs = 50;   %number of times the model should iterate
number_of_responses = 1 % number of predicted responses.
initiaal_learn_rate = 0.005
sequence_length = "shortest"
Metrics="rmse"

%Get training and test data
split = 1.0;
%data_len = 
split_num = round(split*height(features_data))
logMessage = sprintf('The split number is %0.5g records.\n', split_num);
fprintf(logFile, logMessage);

training_set = features_data(1:split_num, :)
testing_set =  features_data(split_num:end,:);


lstm_training_options =  trainingOptions(
    MaxEpochs = epochs, ....
    ValidationData = {Xtrain, ytrain}, ...
    InitialLearnRate = initiaal_lear_rate,...
    SequestLength="shortest",...
    Metrics="rmse",...
    Plots="training-progress",...
    Verbose=true
);


lstm_net = trainnet(Xtrain, ytrain, net, options)

for i = 1:epochs

end

lstm_layer = [

]



logMessage = sprintf('Discharging data has a total of %0.5g records.\n', height(bat_discharging_data));
fprintf(logFile, logMessage);
