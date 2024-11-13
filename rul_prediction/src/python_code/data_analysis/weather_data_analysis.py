import pandas as pd
import numpy as np
from statistics import mean

CALENDAR = {
    1:"January",
    2: "February",
    3:"March",
    4:"April",
    5:"May",
    6:"June",
    7:"July",
    8:"August",
    9:"September",
    10:"October",
    11:"November",
    12:"December"

}

def aggregate_data(data, output_path, season):
    data = data.groupby('Date',as_index = False).agg({"Irra":mean, "Temp":mean})
    data['Index'] = np.arange(1, len(data)+1)
    data['IrraSlope'] = 0
    data['TempSlope'] = 0
    data['Sec'] = 60
    data = data[['Index','IrraSlope','Irra','TempSlope','Temp','Sec']]

    print(f"Wtring data for the {season} season.")
    data_path = output_path+f"{season}_weather_data.csv"
    data.to_csv(data_path, index=False)
    print(len(data))
    print(data[:5])


def main():
    base_path = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/datasets/old_data_sets/"
    output_path = "C:/Users/yamzi/source_code/msc_research/rul_prediction/src/datasets/weather_data/"
    weather_data_2021 = pd.read_csv(base_path+"weather_data_2021.csv")
    weather_data_2022 = pd.read_csv(base_path+"weather_data_2022.csv")

    weather_data_2021_subset = weather_data_2021[['Timestamp (UTC+0)','Solar_irradiation', 'Temperature']]
    weather_data_2022_subset = weather_data_2022[['Timestamp (UTC+0)','Solar_irradiation', 'Temperature']]
    data_frames = [weather_data_2021_subset, weather_data_2022_subset]

    weather_data = pd.concat(data_frames)

    weather_data['Timestamp (UTC+0)'] = pd.to_datetime(weather_data['Timestamp (UTC+0)'])
    weather_data['Year'] = weather_data['Timestamp (UTC+0)'].dt.year
    weather_data['Month'] = weather_data['Timestamp (UTC+0)'].dt.month
    weather_data['Date'] = weather_data['Timestamp (UTC+0)'].dt.date
    weather_data['Month'] = weather_data['Month'].apply(lambda x : CALENDAR[x])
    weather_data = weather_data.rename(columns={"Temperature": "Temp", "Solar_irradiation": "Irra"})



    summer = weather_data[(weather_data['Month'] == 'January') | (weather_data['Month'] == 'February') | (weather_data['Month'] == 'December')]
    aggregate_data(summer, output_path, "summer")
    
    winter = weather_data[(weather_data['Month'] == 'June') | (weather_data['Month'] == 'July') | (weather_data['Month'] == 'August')]
    aggregate_data(winter, output_path, "winter")
    
    autum  = weather_data[(weather_data['Month'] == 'March') | (weather_data['Month'] == 'April') | (weather_data['Month'] == 'May')]
    aggregate_data(autum, output_path, "autum")

    spring = weather_data[(weather_data['Month'] == 'September') | (weather_data['Month'] == 'October') | (weather_data['Month'] == 'November')]
    aggregate_data(spring,output_path, "spring")

if __name__ == "__main__":
    main()
    