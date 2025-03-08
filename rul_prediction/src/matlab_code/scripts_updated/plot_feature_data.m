
rul_features = readtable("/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/features/rul_features.csv");
plot_features_data(rul_features, 'discharge_capacity', 'max_discharge_voltage');


function plot_features_data(feature_data, column1, column2)
    %Get data for the year 2021
    graph_title = [column1, '_vs', column2]
    graph_image = [column1,'_vs_', column2, '.png']
   
    %Get the time vector
    x_axis_col = feature_data{:,column1};

    %Get irradiation vector.
    y_axis_col = feature_data{:,column2};

    %Get the annual average solar irradiation
    %avg_temperature = mean(temperature);

    % Plot the weather against tier data 
    figure;

    plot(x_axis_col, y_axis_col, 'b', 'DisplayName', column2 );

    hold on;

    %Plot the average annual solar irradiation on the same axis with the solar irradiation
    %yline(avg_temperature, 'r','DisplayName', 'Average Temperature');
    xlabel(column1);
    ylabel(column2);
    title(graph_title);
    legend show;
    grid on;
    exportgraphics(gcf,graph_image,'Resolution',800);
    %disp(avg_temperature)
end
