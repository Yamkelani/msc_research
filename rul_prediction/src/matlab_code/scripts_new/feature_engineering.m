clear all;
clc;


%% Read in data for battery charging and discharging.
base_path = "/home/yamukelani/source_code/msc_research/rul_prediction/src";
model_path = "/matlab_code/models/";
model_name = "rul_model"

%Reading in data
bat_charging_data = readtable(base_path+"/datasets/all_batteries_charging_data.csv");
bat_discharging_data = readtable(base_path+"/datasets/all_batteries_discharging_data.csv");


bat_charge_seg = bat_charging_data(:,[3,5,6,7,8,9,10]);

bat_discharge_seg = bat_discharging_data(:,[3,5,6,7,8,9,10,11]);

%ACalculate other features such state of charge.

%Get training and test data
split = 0.80;
%data_len = 

bat_discharge_train = bat_discharge_seg(1:round(split*height(bat_discharge_seg)),:);
X_bat_discharge_train = bat_discharge_train(:,[1,2,3,4,5,6,7]);
Y_bat_discharge_train = bat_discharge_train(:,[8]);

bat_discharge_test = bat_discharge_seg(round(split*height(bat_discharge_seg)):end,:);
X_bat_discharge_test = bat_discharge_test(:,[1,2,3,4,5,6,7]) ;
Y_bat_discharge_test = bat_discharge_test(:,[8]) ;

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
rulModel = fitrgp(bat_discharge_train,'Capacity','KernelFunction','ardsquaredexponential',...
      'FitMethod','sr','PredictMethod','fic','Standardize',1);

saveLearnerForCoder(rulMModel,'MyModel');

ypred = resubPredict(rulMdl);


disp("=============================================================RUL prediction model training has completed. ======================================================================")

disp("The trained model is shown below:")

print(rul_model)
