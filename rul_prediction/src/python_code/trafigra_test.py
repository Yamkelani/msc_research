import pandas as pd

input_data_dict = {
    'id':[1,1,1,1,2,2,2,3,3,3,4,4,4,5],
    'country': ['India','USA','South Africa','India','Australia','USA','South Africa','Australia', 'South Africa','South Africa','South Africa','USA','USA','Australia'],
    'value':[8.9,9.6,66,85.6,75.4,12.6,32.5,20.0,85.6,45.9,78.2,47.4,17.5,9.63]
}

data_df = pd.DataFrame(input_data_dict)

#Add priority column
country_prioties = {'India':1,'USA':2,'South Africa':3,'Australia':4}

data_df['country_priority'] = data_df['country'].map(country_prioties)

#To get the highest priotiry we group by id
high_priority_df = data_df.loc[data_df.groupby('id')['country_priority'].idxmax()]

print(high_priority_df)

