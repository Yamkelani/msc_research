#!/bin/bash


# Define the target directory
target_directory="/home/yamukelani/source_code/msc_research/rul_prediction/src/matlab_code/models"

# Change to the target directory
cd "$target_directory" || { echo "Error: Cannot change to the target directory"; exit 1; }

# Check if the directory is empty
if [ "$(ls -A "$target_directory")" ]; then
    echo "The models directory is not empty. Check if there is already an existing trained model"
else
    echo "The models directory is empty. Running MATLAB script..."
    # Replace "your_matlab_script.m" with the name of your MATLAB script
    matlab -nodisplay -nosplash -nodesktop -r "run('/home/yamukelani/source_code/msc_research/rul_prediction/src/matlab_code/scripts/train_gpr_rul_model.m'); exit"
    echo "Feature engineering script execution completed."
fi