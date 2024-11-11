import pandas as pd
import numpy as np

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
    weather_data['Month'] = weather_data['Month'].apply(lambda x : CALENDAR[x])
    weather_data['IrraSlope'] = 0
    weather_data['TempSlope'] = 0
    weather_data['Sec'] = 60
    weather_data = weather_data.rename(columns={"Temperature": "Temp", "Solar_irradiation": "Irra"})




    summer = weather_data[(weather_data['Month'] == 'January') | (weather_data['Month'] == 'February') | (weather_data['Month'] == 'December')]
    summer['Index'] = np.arange(1, len(summer)+1)
    summer = summer[['Index','IrraSlope','TempSlope','Sec','Temp','Irra']]
    summer.to_csv(output_path+"summer_weather_data.csv", index=False)
    print(len(summer))
    winter = weather_data[(weather_data['Month'] == 'June') | (weather_data['Month'] == 'July') | (weather_data['Month'] == 'August')]
    winter['Index'] = np.arange(1, len(winter)+1)
    winter = winter[['Index','IrraSlope','TempSlope','Sec','Temp','Irra']]
    winter.to_csv(output_path+"winter_weather_data.csv", index=False)
    print(len(winter))
    autum  = weather_data[(weather_data['Month'] == 'March') | (weather_data['Month'] == 'April') | (weather_data['Month'] == 'May')]
    autum['Index'] = np.arange(1, len(autum)+1)
    autum = autum[['Index','IrraSlope','TempSlope','Sec','Temp','Irra']]
    autum.to_csv(output_path+"autum_weather_data.csv", index=False)
    print(len(autum))
    spring = weather_data[(weather_data['Month'] == 'September') | (weather_data['Month'] == 'October') | (weather_data['Month'] == 'November')]
    spring['Index'] = np.arange(1, len(spring)+1)
    spring = spring[['Index','IrraSlope','TempSlope','Sec','Temp','Irra']]
    spring.to_csv(output_path+"spring_weather_data.csv", index=False)
    print(len(spring))

    print(summer[:5])

if __name__ == "__main__":
    main()
    