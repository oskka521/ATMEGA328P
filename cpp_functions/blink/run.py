import serial #pip install PySerial
import keyboard #pip install keyboard
import os, time


StartTask = True
UsbPort = "COM4"
Baudrate = 9600
Datasize = 8 
TerminateTime = 2

print("\nRUNNING SERIAL IN PYTHON, TIME = %s" %time.ctime(os.path.getmtime(__file__)))
try: 
    serialPort = serial.Serial(port = UsbPort, baudrate=Baudrate, bytesize= Datasize, 
                               timeout= TerminateTime, stopbits= serial.STOPBITS_ONE)
except: 
    print("Error Serial")
    run = False

serialString = ""                          
while(StartTask):

    try:
        if keyboard.is_pressed(' '): #space
            print('You Pressed Space To Exit')
            StartTask = False
    except:
        pass

    # Wait until there is data waiting in the serial buffer
    if(serialPort.in_waiting > 0):
        serialString = serialPort.readline()
        print(serialString.decode('Ascii').replace('\r\n', ''))
        #serialPort.write(b"Thank you for sending data \r\n")
