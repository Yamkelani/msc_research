%The directory where the weather data is stored
parent_dir = "/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/weather_datasets/";

%File name for the weather data for Johannesburg for the year 2021
file_name_2021_data = 'weather_data_2021.csv';
file_name_2022_data = 'weather_data_2022.csv';

%Creating the path for reading the data
file_path_2021 = parent_dir+file_name_2021_data;
file_path_2022 = parent_dir+file_name_2022_data;

%Read data for the 2021 and plot the solar vs time curve for the year 2021
weather_data_2021 = readtable(file_path_2021);
start_date_2021 = '01-Jan-2021';
end_date_2021 = '31-Dec-2021';
plot_solar_irrad_data(weather_data_2021, start_date_2021, end_date_2021, '2021');
plot_temperature_data(weather_data_2021, start_date_2021, end_date_2021, '2021');


%Read data for the 2021 and plot the solar vs time curve for the year 2021
weather_data_2022 = readtable(file_path_2022);
start_date_2022 = '01-Jan-2022';
end_date_2022 = '31-Dec-2022';
plot_solar_irrad_data(weather_data_2022, start_date_2022, end_date_2022, '2022');
plot_temperature_data(weather_data_2022, start_date_2022, end_date_2022, '2022');


function plot_solar_irrad_data(weather_data, start_date, end_date, year)
    %Get data for the year 2021
    graph_title = ['Solar irradiation vs time for the year ', year]
    graph_image = ['Solar_irradiation_vs_time_plot_year_', year,'.png']
    weather_data = weather_data((weather_data.Timestamp_UTC_0_ >= datetime(start_date) & weather_data.Timestamp_UTC_0_ <= datetime(end_date)),:);

    %Get the time vector
    time = weather_data{:,'Timestamp_UTC_0_'};

    %Get irradiation vector.
    solar_irrad = weather_data{:,'Solar_irradiation'};

    %Get the annual average solar irradiation
    avg_solar_irrad = mean(solar_irrad);

    % Plot the weather against tier data 
    figure;

    plot(time, solar_irrad, 'b', 'DisplayName', 'Solar Irradiation' );

    hold on;

    %Plot the average annual solar irradiation on the same axis with the solar irradiation
    yline(avg_solar_irrad, 'r','DisplayName', 'Average Solar irradation');
    xlabel('Time');
    ylabel('Solar irradiation (W/m^2)');
    title(graph_title);
    legend show;
    grid on;
    exportgraphics(gcf,graph_image,'Resolution',300);
    disp(avg_solar_irrad)
end


function plot_temperature_data(weather_data, start_date, end_date, year)
    %Get data for the year 2021
    graph_title = ['Temperature vs time for the year ', year]
    graph_image = ['Temperature_vs_time_plot_year_', year,'.png']
    weather_data = weather_data((weather_data.Timestamp_UTC_0_ >= datetime(start_date) & weather_data.Timestamp_UTC_0_ <= datetime(end_date)),:);

    %Get the time vector
    time = weather_data{:,'Timestamp_UTC_0_'};

    %Get irradiation vector.
    temperature = weather_data{:,'Temperature'};

    %Get the annual average solar irradiation
    avg_temperature = mean(temperature);

    % Plot the weather against tier data 
    figure;

    plot(time, temperature, 'b', 'DisplayName', 'Temperature' );

    hold on;

    %Plot the average annual solar irradiation on the same axis with the solar irradiation
    yline(avg_temperature, 'r','DisplayName', 'Average Temperature');
    xlabel('Time');
    ylabel('Temperature (°C)');
    title(graph_title);
    legend show;
    grid on;
    exportgraphics(gcf,graph_image,'Resolution',800);
    disp(avg_temperature)
end