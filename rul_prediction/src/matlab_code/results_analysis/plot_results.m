% This script is used to plot the results from the experiments that were conducted on the lithium-ion batteiries.

base_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_experiments_data/cell2/csv/';
charge_file_path = [base_dir, 'test_summer_001_cell_2_model_IFR32700_charging_data_2024_12_04.csv'];
discharge_file_path = [base_dir, 'test_summer_001_cell_2_model_IFR32700_dicharging_data_2024_12_04.csv'];

charging_data = readtable(charge_file_path);
discharging_data = readtable(discharge_file_path);

%The following code plots all the required plots for analysis

% %Charge voltage plot
% title = 'Cell2 Cycle 2 charging voltage versus time';
% x_label = 'Time (s)';
% y_label = 'Voltage (V)';
% plot_file_name = 'Measure_charging_voltage_plot.png';
% plot_data(discharging_data, 'Time_stamp', 'Measured_cell_voltage', title, x_label, y_label, plot_file_name );

% %Charge current plot
% title = 'Cell2 Cycle 1 charging measured current versus time';
% x_label = 'Time (s)';
% y_label = 'Current (A)';
% plot_file_name = 'Measured_charging_current_plot.png';
% plot_data(discharging_data, 'Time_stamp', 'Measured_cell_current', title, x_label, y_label, plot_file_name );

% %Charge capacity vs voltage plot
% title = 'Cell2 Cycle 1 charging measured capacity versus voltage';
% x_label = 'Voltage (V)';
% y_label = 'Capacity (Ah)';
% plot_file_name = 'Measured_charging_capacity vs voltage_plot.png';
% plot_data(discharging_data, 'Measured_cell_voltage', 'Measured_cell_capacity', title, x_label, y_label, plot_file_name );

%Plot all the capacities in one set of axis.
plot_cycle_data(base_dir, 'dicharging')

%This function is for plotting a line graph for given parameters.
function plot_data(table_name, x_col, y_col, g_title, x_label, y_label , graph_file)
    plot(table_name.(x_col), table_name.(y_col) ) % Multiple columns
    xlabel(x_label);
    ylabel(y_label);
    %legend({'', 'Feature2'}) % Add legend
    title(g_title);
    % Adjust axis limits
    %xlim([min(table_name.(x_col)) max(table_name.(x_col))]) % Adjust X-axis limits
    %ylim([min(table_name.(y_col))-10 max(table_name.(y_col))+10]) % Add padding to Y-axis
    axis padded
    grid on
    exportgraphics(gcf, graph_file, 'Resolution', 300) % Saves as a PNG file

end

function plot_cycle_data(base_dir, extract)
    % Get a list of all battery cell discharge csv files in the folder
    discharge_files_list = dir(fullfile(base_dir, ['*' extract '*.csv']));

    % Initialize cell arrays to store extracted data
    time_stamp = [];  % Store all the time_stamp columns here
    cycle_discharge_capacity = {};   % Store all the measured capacity here
    cycle_files = {};   % Store each file name here

    cycles_to_plot = {'001','005','010','015','020','025', '030','035', '040','045', '050','055','060', '065','070',...
    '075','080','085','090','095','100'};

    files_to_read = {};

    for i = 1:length(discharge_files_list)
        % Get the filename
        filename = discharge_files_list(i).name;
        
        % Check if any of the keywords exist in the filename
        for j = 1:length(cycles_to_plot)
            if contains(filename, cycles_to_plot{j}, 'IgnoreCase', true)
                files_to_read{end+1} = filename;  % Add to the selected files list
                break;  % Stop checking once a match is found
            end
        end
    end


    % Read in each battery cell discharge file here 
    for i = 1:length(files_to_read)
        
        % read data into a table for easy processing
        cell_disch_path = fullfile(base_dir, discharge_files_list(i).name);
        cell_discharge_data = readtable(cell_disch_path);
        cell_discharge_data.Time_stamp = (0:0.5:(height(cell_discharge_data)-1)*0.5)';
        height(cell_discharge_data);
        
        % Extract the time stamp column which is common column in these datasets
        if i == 1
            time_stamp = cell_discharge_data.("Time_stamp");
        end
    
        [~, file_name, ~] = fileparts(cell_disch_path);
        cycle = extractBetween(file_name, 'summer_', '_cell');
        cycle_name = strcat('cycle_' , cycle );
        
        if ismember(cycle, cycles_to_plot)
            cycle_discharge_capacity{i} = abs(cell_discharge_data.("Measured_cell_voltage"));
        end  
        
        % Replace with the correct column name
        cycle_files{i} = cycle_name;  % Store the name of the cycle discharge file.
        
    end

    % Plot the measured capacities in one set of axes.
    figure('Position', [600, 600, 1000, 1000]);
    hold on; 

    cycle_discharge_capacity;
    max_length = max(cellfun(@length, cycle_discharge_capacity));

    length(cycle_discharge_capacity)

    % Pad shorter vectors with NaN
    for i = 1:length(cycle_discharge_capacity)
        cycle_discharge_capacity{i}(end+1:max_length) = 0; % Extends each vector to maxLength
    end

    % Also pad the common column if necessary
    if length(time_stamp) < max_length
        time_stamp(end+1:max_length) = NaN;
    end

    length(cycle_discharge_capacity)

    for i = 1:length(cycle_discharge_capacity)
        plot(time_stamp, cycle_discharge_capacity{i});
    end

    hold off;  % Done adding plots
    grid on;

    % Label the axes and add a title
    xlabel('Time');  % Replace with your common column label
    ylabel('Voltage');  % Replace with your feature label
    title('Comparison of measured discharge voltage across multipe cycles');

    % Show the legend
    ax = gca; % Get the current axes
    set(ax, 'Position', [0.1, 0.2, 0.8, 0.7]);  % [left, bottom, width, height]

    % Adjust the OuterPosition of the axes to increase the space around
    set(ax, 'OuterPosition', [0.05, 0.1, 0.9, 0.8]);  % [left, bottom, width, height]

    % Add legend and move it if needed
    legend('show', 'Location', 'bestoutside')
    
    axis padded
    graph_file = 'battery_discharge_voltage_for_all_cycles.png';
    exportgraphics(gcf, graph_file, 'Resolution', 1080)
end
