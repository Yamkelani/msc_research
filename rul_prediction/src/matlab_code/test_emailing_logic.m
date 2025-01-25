% Run the Simulink model
simOut = sim('rul_data_acquisition_system');  % Replace 'your_model_name' with your model's name

% Get the current date and time
currentDateTime = datestr(now, 'yyyy-mm-dd_HH-MM-SS')

% Generate a filename with the current date and timestamp
filename = ['output_', currentDateTime, '.mat'];

% Save the simulation output to the file
save(filename, 'simOut');

disp(['Simulation data saved to: ', filename]);
