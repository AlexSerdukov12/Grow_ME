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
    # Send the data to the Firebase Realtime Database
    db.reference('sensor-data').push().set(data)
    print('Data sent to Firebase Realtime Database.')

def read_data():
    data = {}
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.startswith('Temperature:'):
                temperature = line.split(':')[1].strip()
                data['Temperature'] = temperature
            elif line.startswith('Humidity:'):
                humidity = line.split(':')[1].strip()
                data['Humidity'] = humidity
            elif line.startswith('Fans :'):
                fan_state = line.split(':')[1].strip()
                data['Fans'] = fan_state
            elif line.startswith('Water level :'):
                water_level = line.split(':')[1].strip()
                data['Water level'] = water_level
            elif line.startswith('LDR value is:'):
                ldr_value = line.split(':')[1].strip()
                data['LDR value'] = ldr_value
            elif line.startswith('LED :'):
                led_state = line.split(':')[1].strip()
                data['LED'] = led_state
            elif line.startswith('PH value:'):
                ph_value = line.split(':')[1].strip()
                data['PH value'] = ph_value

    return data

while True:
    data = read_data()
    if data:
        send_data_to_firebase(data)
    time.sleep(13)  # Wait for 10 seconds before reading the file again
