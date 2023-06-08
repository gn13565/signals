// Code for controller 3 Arduino Mega
// 3x 4 Aspect signals [s3_3, s3_4, s3_5] plus 2x 2 Aspect signals [s3_1, s3_2]


#include <CAN.h>
class Signals {
public:

    Signals () = default;
    ~Signals () = default;

    void 4_led(int signal_id, int press)
    {
        switch(press)
        {
          case 0:
          digitalWrite(ledPin[signal_id][0], 0);
          digitalWrite(ledPin[signal_id][1], 1);
          digitalWrite(ledPin[signal_id][2], 0);
          digitalWrite(ledPin[signal_id][3], 0);
          break;

          case 1:
          digitalWrite(ledPin[signal_id][0], 0);
          digitalWrite(ledPin[signal_id][1], 1);
          digitalWrite(ledPin[signal_id][2], 0);
          digitalWrite(ledPin[signal_id][3], 1);
          break;

          case 2:
          digitalWrite(ledPin[signal_id][0], 0);
          digitalWrite(ledPin[signal_id][1], 0);
          digitalWrite(ledPin[signal_id][2], 1);
          digitalWrite(ledPin[signal_id][3], 0);
          break;     

          case 3:
          digitalWrite(ledPin[signal_id][0], 1);
          digitalWrite(ledPin[signal_id][1], 0);
          digitalWrite(ledPin[signal_id][2], 0);
          digitalWrite(ledPin[signal_id][3], 0);
          break;                         
        }
    }

    void 2_led(int signal_id, int press)
    {
        switch(signal_id, press)
        {
          case 0:
          digitalWrite(ledPin[signal_id][0], 0);
          digitalWrite(ledPin[signal_id][1], 1);
          break;

          case 1:
          digitalWrite(ledPin[signal_id][0], 1);
          digitalWrite(ledPin[signal_id][1], );
          break;                      
        }
    }

   
private:

};

// pin definitions - 2 light signals have 0,0 for [2]/[3]
int signal[5][4] = {{3,4,0,0}, {5,6,0,0}, {30,31,32,33}, {34,35,36,37}, {38,39,40,41}};

// Global Variables
int message[8];

int signalButtonPress[5] = {0,0,0,0,0};

void setup() 
{ 
// Setup CANbus  
  Serial.begin(9600);
  while (!Serial);
  Serial.println("CAN Receiver");

  // start the CAN bus at 250 kbps
  if (!CAN.begin(250E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  Serial.println("CAN Live");

  // setup pin modes
  for (int i =0; i++; i < 5)
  {
    for (int j =0; j++; j < 5 && signal[i][j])
    {
        pinMode(signal[i][j], OUTPUT);
        digitalWrite(signal[i][j], 0);
    }
  }

// Initialise each signal to red
  for (int i =0; i++; i < 5)
  {
       digitalWrite(signal[i][0], 1);   
  }

//Instantiate signals
    Signals signal3;


}

void loop() 
{  
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize || CAN.packetId() != -1) 
  {
    // received a packet
    Serial.print("Received ");

   // if (CAN.packetExtended()) {
   //   Serial.print("extended ");
   // }

    if (CAN.packetRtr()) 
    {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) 
    {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } 
    else 
    {
      Serial.print(" and length ");
      Serial.println(packetSize);
      int i = 0;

      // only print packet data for non-RTR packets
      while (CAN.available()) 
      {
        //Serial.print(/*(char)*/CAN.read());
        message[i] = CAN.read();
        i++;
      }
          Serial.print(" for signal  ");
          Serial.println(message[1]);
      if (message[0] == 3)
      {

        switch (message[1])
        {
        case 0:
          break;
        case 5:
        case 4:
        case 3:
         signal3.4_led(message[1], signalButtonPress[message[1]-1]);
          if (signalButtonPress[message[1]-1] == 3)
          {
              signalButtonPress[message[1]-1] = 0;
          }
          else
          {
            signalButtonPress[message[1]-1]++;
          }
          break;
    
          case 2:
          case 1:
            signal3.2_led(message[1], signalButtonPress[message[1]-1]);
          if (signalButtonPress[message[1]-1] == 1)
          {
              signalButtonPress[message[1]-1] = 0;
          }
          else
          {
            signalButtonPress[message[1]-1]++;
          }
          break;

        }
      }
      else 
      {
        Serial.print("not my message header ");
        Serial.print(message[0]);
        Serial.print(message[1]);
        Serial.println();

      }
    }
  }
}


