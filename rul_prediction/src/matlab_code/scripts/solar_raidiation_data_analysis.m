figure;
summer_data = readtable("C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\weather_data\summer_weather_data.csv");
plot(summer_data.Timestamp_UTC, summer_data.Irra)

figure;
winter_data = readtable("C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\weather_data\winter_weather_data.csv");
plot(winter_data.Timestamp_UTC, winter_data.Irra)

figure;
autum_data = readtable("C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\weather_data\autum_weather_data.csv");
plot(autum_data.Timestamp_UTC, autum_data.Irra)

figure;
spring_data = readtable("C:\Users\yamzi\source_code\msc_research\rul_prediction\src\datasets\weather_data\spring_weather_data.csv");
plot(spring_data.Timestamp_UTC, spring_data.Irra)

temp1 = [summer_data; winter_data];
temp2 = [temp1;autum_data];
weather_data = [temp2; spring_data]
figure;
plot(weather_data.Timestamp_UTC, weather_data.Irra)

figure;
plot(weather_data.Timestamp_UTC, weather_data.Temp)
