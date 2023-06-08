import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time

# Fetch the service account key JSON file and database URL from Firebase console
cred = credentials.Certificate('C:/Users/alex/Desktop/growme-fc746-firebase-adminsdk-t0msz-c3ddad6207.json')
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://growme-fc746-default-rtdb.europe-west1.firebasedatabase.app/'
})

# Path to the sensors data file
file_path = 'C:/Users/alex/Documents/PlatformIO/Projects/Grow_ME/sensors_data.txt'

def send_data_to_firebase(data):
    # Update the existing data in the Firebase Realtime Database
    stats_ref = db.reference('statistics')
    stats_ref.update(data)
    print('Data updated in Firebase Realtime Database.')
def read_data():
    data = {
        'Temperature': [],
        'Humidity': [],
        'Fans': [],
        'Water level': [],
        'LDR value': [],
        'LED': [],
        'PH value': []
    }

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            line = line.strip()
            if line.startswith('Temperature'):
                temperature = float(line.split(':')[1].strip())
                data['Temperature'].append(temperature)
            elif line.startswith('Humidity'):
                humidity = float(line.split(':')[1].strip())
                data['Humidity'].append(humidity)
            elif line.startswith('Fans'):
                fans = int(line.split(':')[1].strip())
                data['Fans'].append(fans)
            elif line.startswith('Water level'):
                water_level = int(line.split(':')[1].strip())
                data['Water level'].append(water_level)
            elif line.startswith('LDR value'):
                ldr_value = int(line.split(':')[1].strip())
                data['LDR value'].append(ldr_value)
            elif line.startswith('LED'):
                led = int(line.split(':')[1].strip())
                data['LED'].append(led)
            elif line.startswith('PH value'):
                ph_value = float(line.split(':')[1].strip())
                data['PH value'].append(ph_value)

    return data

def calculate_statistics(data):
    statistics = {}
    for category, values in data.items():
        statistics[category] = {
            'Sum': sum(values),
            'Min': min(values),
            'Max': max(values),
            'Average': sum(values) / len(values)
        }
    return statistics

while True:
    sensor_data = read_data()
    if sensor_data:
        statistics = calculate_statistics(sensor_data)
        send_data_to_firebase(statistics)
        print('Statistics:', statistics)
    else:
        print('No data available.')
    time.sleep(10)