#import numpy as np
#import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.layers import LSTM
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error

def parse(x):
 return datetime.strptime(x, '%Y %m %d %H')

 class RULPredictionLSTM:
    def __init__(data_path):
        self.data_path = data_path

    def read_data_in():
         datasets = []

        if len(self.data_path) == 0:
            print("No data to read")
        elif len(self.data_path) > 1:
           
            for path in self.data_path:
                dataset = pd.read_csv(path)
                datasets.append(dataset)
        else:
            datasets.append(pd.read_csv(data_path[0]))


    def prepare_data()



def read_data_in():
    bat_charge_df = pd.read_csv(r"/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_charging_data.csv", usecols=[1], engine='python')
    bat_discharge_df = pd.read_csv(r"/home/yamukelani/source_code/msc_research/rul_prediction/src/datasets/battery_discharging_data.csv", usecols=[1], engine='python')
    plt.plot(bat_charge_df)
    
    return bat_charge_df, bat_discharge_df


# convert an array of values into a dataset matrix
def create_dataset(dataset, look_back=1):
	dataX, dataY = [], []
	for i in range(len(dataset)-look_back-1):
		a = dataset[i:(i+look_back), 0]
		dataX.append(a)
		dataY.append(dataset[i + look_back, 0])
	return np.array(dataX), np.array(dataY)

def main():
    battery_charge_df, battery_discharge_df = read_data_in()

    # reshape into X=t and Y=t+1
    look_back = 1
    trainX, trainY = create_dataset(train, look_back)
    testX, testY = create_dataset(test, look_back)

    # fix random seed for reproducibility
    tf.random.set_seed(7)

if __name__ == "__main__":
    main()
