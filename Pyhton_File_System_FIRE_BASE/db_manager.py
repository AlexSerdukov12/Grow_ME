import firebase_admin
from firebase_admin import credentials
from firebase_admin import db

def initialize_firebase():
    # Path to your service account key JSON file
    cred = credentials.Certificate('C:/Users/alex/Desktop/growme-fc746-firebase-adminsdk-t0msz-c3ddad6207.json')

    # Initialize the Firebase Admin SDK
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://growme-fc746-default-rtdb.europe-west1.firebasedatabase.app/'
    })

def send_file_contents(file_path):
    # Read the contents of the file
    with open(file_path, 'r') as file:
        file_content = file.read()

    # Get a reference to the Firebase Realtime Database root
    ref = db.reference('/')

    # Push the file contents to the database and get the auto-generated key
    new_data_ref = ref.push(file_content)
    new_data_key = new_data_ref.key

    return new_data_key
def analyze_data():
    # Get a reference to the Firebase Realtime Database root
    ref = db.reference('/')

    # Retrieve the data from the database
    data = ref.get()

    # Perform your analysis on the data
    for key, value in data.items():
        # Convert the values to appropriate data types
        temperature = float(value.split('Temperature: ')[1].split(' C')[0])
        humidity = float(value.split('Humidity: ')[1].split('%')[0])
        fans = value.split('Fans : ')[1].split('\n')[0]
        water_level = float(value.split('Water level : ')[1].split('%')[0])
        ldr_value = int(value.split('LDR value is: ')[1].split('\n')[0])
        led = value.split('LED : ')[1].split('\n')[0]
        ph_value = float(value.split('PH value:')[1])

        # Perform analysis based on the retrieved data
        # Example: Calculate average temperature and humidity
        # ...

        # Print or store the analysis results
        print('Data key:', key)
        print('Temperature:', temperature)
        print('Humidity:', humidity)
        print('Fans:', fans)
        print('Water level:', water_level)
        print('LDR value:', ldr_value)
        print('LED:', led)
        print('PH value:', ph_value)
        print('---')


if __name__ == '__main__':
    # Example usage
    initialize_firebase()

    # Specify the path to the text file
    file_path = 'C:/Users/alex/Documents/PlatformIO/Projects/Grow_ME/sensors_reports.txt'

    # Send the contents of the text file to the database
    new_data_key = send_file_contents(file_path)

    print('New data key:', new_data_key)

    # Analyze the data
    analyze_data()
