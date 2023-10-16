#written by Joshua Bettles
#0° remove sleep function from laptop
#1° Connect USB
#2° Run Code
#3° Wait
import serial
import datetime
import csv, os

def open_port():
    try: 
        s = serial.Serial('COM7', baudrate = 9600, timeout = 1)
        return s
    except:
        return -1  
    
def Read_Line(ser):
    line = ser.readline().decode('UTF-8').replace('\r\n','')
    ser.flush()
    return line
    
def Data_Logger():
    now = datetime.datetime.now()
    current_time = now.strftime("%H %M %S")
    name = 'data' + current_time
    path = os.path.join(os.path.dirname(os.path.realpath(__file__)), name)
    f = open(path, 'w')
    writer = csv.writer(f)
    writer.writerow(["Time", "Current", "Position", "Error", "Temperature"])
    f.close()
    ser = -1
    while ser == -1:
        ser = open_port()
        print(ser)
    while True:
        data = Read_Line(ser)
        
        if data:
            f = open(path, 'a')
            now = datetime.datetime.now()
            current_time = now.strftime("%H:%M:%S")
            try:
                Current, Pos, Error, Temp = data.split(',')
                print(Current)
                writer = csv.writer(f)
                writer.writerow([current_time, Current, Pos, Error, Temp])
            except:
                pass
            f.close()
    
if __name__ == '__main__':
    Data_Logger()

