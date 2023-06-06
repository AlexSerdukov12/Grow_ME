import serial
# Configure the serial port settings
serial_port = 'COM5'  # Replace 'COM5' with the actual port name
baud_rate = 9600
# Specify the file path
file_path = r'C:\Users\alex\Documents\PlatformIO\Projects\Grow_ME\sensors_reports.txt'
try:
    # Open the serial port
    ser = serial.Serial(serial_port, baud_rate)
    try:
        while True:
            # Read a line of data from the serial port
            line = ser.readline().decode().strip()
            # Open the file in write mode to overwrite the existing data
            with open(file_path, 'w') as file:
                # Write the line to the file
                file.write(line)
            # Print the data to the console
            print(line)
    except KeyboardInterrupt:
        pass
finally:
    # Close the serial port
    ser.close()
