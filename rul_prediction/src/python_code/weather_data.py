import pandas as pd

base_path = 'C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\'
path1 = base_path+"\weather_data_2021.csv"
path2 = base_path+"\weather_data_2022.csv"

solar_data1 = pd.read_csv(path1)
solar_data2 = pd.read_csv(path2)

