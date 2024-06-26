#ifndef ARCaDIUS_Serial_H
#define ARCaDIUS_Serial_H

#include <Arduino.h>

enum operation {
  PUMP,
  SHUTTER,
  VALVE,
  MIXER,
  DETAIL,
  READ,
  EXTRACT,
  SYRINGE
};

enum SENSOR {
  TEMP,
  BUBBLE,
  LDS,
};


class ASerial {
  private:
    //Flushes the serial port of any unwanted data
    void serialFlush();

    //Checks to see if the receiver ID matches that of the device
    int CheckrID(String rID, int Device_ID);

    //Checks to see if the sender ID matches that of the listener
    int ChecksID(String sID, int Sender_ID);

    //Calculates the command packet size from the serial comms.
    int getPKSize(String rPK_Size);

    void ReturnDetails();

    int Device_ID;
    int Sender_ID;
    String sACK;
    String sBUSY;
    String sCONF;
    String DeviceDesc;

    int NumPump;
    int NumValve;
    int NumIrr;
    int NumTemp;
    int NumBubble;
    int NumLDS;
    int NumMixer;
    int NumSyringe;
    int intPin;
    int ResPin;
    bool isDeviceConnected;

    float* TempVal;
    float* BubbleVal;
    float* LDSVal;

    enum operation op;
    enum SENSOR Sensor;

    int pump;
    float pumpValue;
    int pumpDir;

    int valve;
    int valveToOpen;
    //IF NUMBER OF VALVES CHANGE, CHANGE ARRAY SIZE
    int valveStates[5];

    int mixer;
    float mixerSpeed;
    bool mixerDir;

    int shutter;
    int shutterPos;

    int extract;
    int extractPos;

    float syringeVolume;
    int syringeType;

    void Pump();
    void Mixer();
    void OpenOneValve();
    void OpenMultipleValves();
    void Shutter();
    void Extract();
    void Syringe();

    void readSensors();

    static ASerial * instance0_;

    int SerialrID;
    int SerialsID;
    int PK_Size = 0;
    String Command = "NaN";
    bool isWaiting;
    bool CMD = false;

    String rID = "NaN";
    String sID = "NaN";
    String rPK_Size = "NaN";

    String Data;

    static void serialInterrupt();
    static void reattach();
    void SerialLoop();

    int process();
    void analyse();

  public:
    ASerial(String DD, int rID, int sID, int P, int V, int I, int T, int B, int L, int M, int S, int Res);

    //Error handler
    void Error(int code);

    void updateSensors(SENSOR s, int Num, float Val);

    void Start();

    void print2Serial();
    void FinishedCommand();

    void SetState(bool s);
    bool GetState();

    void SetsID(int ID);
    int GetsID();
    int GetSerialsID();

    void SetrID(int ID);
    int GetrID();
    int GetSerialrID();

    int GetPKSize();

    int GetCommand();
    String GetData() {
      return Data;
    }
    bool GotCommand();
    void SetCommand(bool v) {
      CMD = v;
    }

    int getPump();
    float getPumpMls();
    bool getPumpDir();

    int getValve();

    int getMixer();
    int getMixerSpeed();
    bool getMixerDir();

    int getShutter();
    int getShutterPos();

    int getExtractPos();

    float getSyringeVolume();
    int getSyringeType();

    bool GetDeviceConnectedStatus();
};
#endif
