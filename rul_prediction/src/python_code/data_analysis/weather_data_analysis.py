import pandas as pd

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
    weather_data.rename(columns={"Temperature": "Temp", "Solar_irradiation": "Irra"})




    summer = weather_data[(weather_data['Month'] == 'January') | (weather_data['Month'] == 'February') | (weather_data['Month'] == 'December')]
    summer = summer[['IrraSlope','TempSlope','Sec','Temp','Irra']]
    winter = weather_data[(weather_data['Month'] == 'June') | (weather_data['Month'] == 'July') | (weather_data['Month'] == 'August')]
    autum  = weather_data[(weather_data['Month'] == 'March') | (weather_data['Month'] == 'April') | (weather_data['Month'] == 'May')]
    sprint = weather_data[(weather_data['Month'] == 'September') | (weather_data['Month'] == 'October') | (weather_data['Month'] == 'November')]


    print(summer[:5])

if __name__ == "__main__":
    main()
    