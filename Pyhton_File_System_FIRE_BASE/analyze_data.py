import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import statistics

def initialize_firebase():
    # Path to your service account key JSON file
    cred = credentials.Certificate('C:/Users/alex/Desktop/growme-fc746-firebase-adminsdk-t0msz-c3ddad6207.json')

    # Initialize the Firebase Admin SDK
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://growme-fc746-default-rtdb.europe-west1.firebasedatabase.app/'
    })

def get_data():
    # Get a reference to the Firebase Realtime Database root
    ref = db.reference('/')

    # Retrieve the data from the database
    data = ref.get()

    return data

def analyze_data():
    data = get_data()

    temperatures = []
    humidities = []
    fan_durations = []
    water_levels = []
    ldr_values = []
    led_durations = []
    ph_values = []

    # Extract the values from the data and append them to the respective lists
    for value in data.values():
        temperature = float(value.split('Temperature: ')[1].split(' C')[0])
        humidity = float(value.split('Humidity: ')[1].split('%')[0])
        fan = value.split('Fans : ')[1].split('\n')[0]
        water_level = float(value.split('Water level : ')[1].split('%')[0])
        ldr_value = int(value.split('LDR value is: ')[1].split('\n')[0])
        led = value.split('LED : ')[1].split('\n')[0]
        ph_value = float(value.split('PH value:')[1])

        temperatures.append(temperature)
        humidities.append(humidity)
        fan_durations.append(fan)
        water_levels.append(water_level)
        ldr_values.append(ldr_value)
        led_durations.append(led)
        ph_values.append(ph_value)

    # Perform statistical analysis on the lists
    temperature_mean = statistics.mean(temperatures)
    temperature_median = statistics.median(temperatures)
    temperature_stddev = statistics.stdev(temperatures)
    humidity_mean = statistics.mean(humidities)
    humidity_median = statistics.median(humidities)
    humidity_stddev = statistics.stdev(humidities)
    fan_duration_mode = statistics.mode(fan_durations)
    water_level_mean = statistics.mean(water_levels)
    water_level_median = statistics.median(water_levels)
    water_level_stddev = statistics.stdev(water_levels)
    ldr_value_mean = statistics.mean(ldr_values)
    ldr_value_median = statistics.median(ldr_values)
    ldr_value_stddev = statistics.stdev(ldr_values)
    led_duration_mode = statistics.mode(led_durations)
    ph_value_mean = statistics.mean(ph_values)
    ph_value_median = statistics.median(ph_values)
    ph_value_stddev = statistics.stdev(ph_values)

    # Print the statistical results
    print('Temperature:')
    print('Mean:', temperature_mean)
    print('Median:', temperature_median)
    print('Standard Deviation:', temperature_stddev)
    print('------------------------')
    print('Humidity:')
    print('Mean:', humidity_mean)
    print('Median:', humidity_median)
    print('Standard Deviation:', humidity_stddev)
    print('------------------------')
    print('Fan Duration:')
    print('Mode:', fan_duration_mode)
    print('------------------------')
    print('Water Level:')
    print('Mean:', water_level_mean)
    print('Median:', water_level_median)
    print('Standard Deviation:', water_level_stddev)
    print('------------------------')
    print('LDR Value:')
    print('Mean:', ldr_value_mean)
    print('Median:', ldr_value_median)
    print('Standard Deviation:', ldr_value_stddev)
    print('------------------------')
    print('LED Duration:')
    print('Mode:', led_duration_mode)
    print('------------------------')
    print('pH Value:')
    print('Mean:', ph_value_mean)
    print('Median:', ph_value_median)
    print('Standard Deviation:', ph_value_stddev)

if __name__ == '__main__':
    initialize_firebase()
    analyze_data()
