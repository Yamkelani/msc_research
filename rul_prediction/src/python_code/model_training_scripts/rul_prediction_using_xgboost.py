"""
This code creates an xGboost model , trains and test it. Then performs hyperamete tuning to obtain the 
best performing paramters for this model, and uses the best paramters to re train the model.
"""

from sklearn.metrics import accuracy_score, mean_squared_error, mean_absolute_error
import xgboost as xgb
from sklearn.model_selection import train_test_split, GridSearchCV
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

rul_features = pd.read_csv('/rul_fsrmrmr_selected__features.csv')
X_dataset = rul_features.drop(columns=['cycle_rul'])
y_dataset = rul_features['cycle_rul']

#Generate the training and testing datasets
X_train,  X_test, y_train, y_test = train_test_split(X_dataset, y_dataset, test_size=0.3, random_state=42)

X_train

#Convert the dataset into a Dmatrix that is optimizable for xgboost
rul_train_xgb = xgb.DMatrix(X_train, y_train, enable_categorical=True)
rul_test_xgb = xgb.DMatrix(X_test, y_test, enable_categorical=True)

X_train.shape

y_train.shape

#Training the model
boost_rounds = 100

model_parameters = {
    'objective':'reg:absoluteerror',
    'max_depth':3,
    'learning_rate':0.25,
    'n_estimators':100,
    'random_state':42,
    'eval_metric':'mae'
}

rul_model = xgb.train(
    params = model_parameters,
    dtrain = rul_train_xgb,
    num_boost_round = boost_rounds
)

#Predict the rul
pred_rul = rul_model.predict(rul_test_xgb)
pred_rul = pred_rul.astype(int)
accuracy = accuracy_score(y_test, pred_rul)
print("The accuracy of the model is:", (accuracy * 100.0))

#Hyper paramater tuning the xgboost due to the poor performance recorded above
hyper_param = {
    'n_estimators':[100,150,200, 300],
    'max_depth': [3,6,9,12,15],
    'learning_rate': [0.01, 0.05, 0.1, 0.2, 0.25, 0.3,0.35, 0.40, 0.45,0.50]
}

rul_grid_search = GridSearchCV(
    estimator = xgb.XGBRegressor(objective='reg:squarederror', random_state=42),
    param_grid = hyper_param,
    scoring = 'neg_mean_squared_error',
    cv=5,
    verbose = 2
)

rul_grid_search.fit(X_train, y_train)
print(rul_grid_search.best_params_)

best_parameters = rul_grid_search.best_params_
best_parameters

rul_final_model = xgb.XGBRegressor(**best_parameters, objective='reg:squarederror')
rul_final_model.fit(X_train, y_train)

# Final rul predictions
y_pred_rul = rul_final_model.predict(X_test)

# Final MSE
rul_mse = mean_squared_error(y_test, y_pred_rul)
print(f'Final MSE: {rul_mse:.2f}')


# Final RMSE
rul_mae = mean_absolute_error(y_test, y_pred_rul)
print(f'Final MAE: {rul_mae:.2f}')

# Plot the true and predicted values
plt.figure(figsize=(10, 6))
plt.plot(y_test.values, label='True RUL', marker='o')
plt.plot(y_pred_rul, label='Predicted RUL', marker='*')

# Add labels and a legend
plt.xlabel('Feature sample index')
plt.ylabel('Remaining Useful Life (RUL)')
plt.legend()
plt.grid()
plt.title('True vs Predicted RUL')

