features_dir = '/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/features/';
features_file_name = 'rul_features.csv';

rul_data  = readtable([features_dir,features_file_name]);

%Gets the target variable in this case the remaining useful life (RUL)
rul = rul_data{:, 2};
rul_table = array2table(rul, 'VariableNames', {'cycle_rul'});

%Add feature names
feature_names = rul_data.Properties.VariableNames(1:end-1);
feature_labels = feature_names(features);

% Perfomers the feature selection process using the 
fsrmrmr_feature_selection(rul_data, rul_table, feature_labels, features_dir, features_file_name)
relieff_feature_selection(rul_data, rul, rul_table, feature_labels, features_dir, features_file_name)

function relieff_feature_selection(rul_data, rul, target_table, feature_labels, features_dir, features_file_name)
    rul_data_new = generate_features(rul_data);
    rul_features = rul_data_new(:, setdiff(1:width(rul_data_new), 2));
    [rlf_features, rul_weights] = relieff(rul_features, rul, 20);

    relieff_best_features = select_best_features(rlf_features, rul_weights);
    rul_relieff_selected_features = rul_data(:, relieff_best_features);
    rul_relieff_selected_features = [rul_relieff_selected_features, target_table];

    bar(rul_weights(rlf_features));
    xlabel('RUL Predictor rank');
    ylabel('RUL Predictor importance weight');
    title("RUL battery degradation feature selection using relieff algorithm")

    xticks(1:length(feature_labels));
    xticklabels(strrep(feature_labels, "_", "\_"));
    xtickangle(90);

    rul_relief_feature_table = table(feature_labels',rul_weights', 'VariableNames',{'Feature','Relief Score'}');
    writetable(rul_relief_feature_table, [features_dir,'rul_relief_relieff_scores.csv']);
    writetable(rul_relieff_selected_features, [features_dir,'rul_relieff_selected__features.csv']);


    set(gcf, 'Position', [100, 100, 1200, 600]); 

    saveas(gcf, "rul_feature_selection_using_relieff.png");

    plot_features(rul_weights);
end

%This function performs feature selection using the MRMR
function fsrmrmr_feature_selection(rul_data, target, feature_labels, features_dir, features_file_name)
    [features, fsrmrmr_scores] = fsrmrmr(rul_data, "cycle_rul");
    fsrmrmr_best_features = select_best_features(features, fsrmrmr_scores);
    rul_fsrmrmr_selected_features = rul_data(:, fsrmrmr_best_features);
    rul_fsrmrmr_selected_features = [rul_fsrmrmr_selected_features, target];%Create a bar plot to show the importance of each feature.
    bar(fsrmrmr_scores(features));
    xlabel("Rul feature rank")
    ylabel("Feature importance score")
    title("RUL battery degradation feature selection using MRMR algorithm")
    
    grid on;
    
    xticks(1:length(feature_labels));
    xticklabels(strrep(feature_labels, "_", "\_"));
    xtickangle(90);
    
    rul_feature_table = table(feature_labels',fsrmrmr_scores', 'VariableNames',{'Feature','MRMR Score'}');
    writetable(rul_feature_table, [features_dir,'rul_frmrmr_fsrmrmr_scores.csv'])
    writetable(rul_fsrmrmr_selected_features, [features_dir,'rul_fsrmrmr_selected__features.csv'])
    
    
    set(gcf, 'Position', [100, 100, 1200, 600]); 
    
    saveas(gcf, "rul_feature_selection_using_mrmr.png")

end

%This function plots a graph of features scores corresponding 
% to each feature to help the user select the features using elbow method.
function plot_features(weights)
    figure;
    plot(1:length(weights), sort(weights, 'descend'), '-o');
    xlabel('RUL features rank');
    ylabel('Feauture importance');
    title('RUL features importance using the elbow method');


    set(gcf, 'Position', [100, 100, 1200, 600]); 

    saveas(gcf, "Feature_seection_using_elbow_ethod.png");

end

%This function selects the best features based on the weights and score assigned to each feature.
function best_features = select_best_features(features, weights)
    avg_score = mean(weights);
    best_features = features(weights > avg_score);
    best_scores = weights(weights > avg_score);
end

%This function converts the features to numeric for processing 
function rul_features = generate_features(rul_data)
    for i = 1:width(rul_data)
        if iscategorical(rul_data{:,i}) || isstring(rul_data{:,i})
            rul_data{:,i} = double(categorical(rul_data{:,i}));
        end
    end

    rul_features = table2array(rul_data);
end


