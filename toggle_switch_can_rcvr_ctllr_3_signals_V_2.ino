// Code for controller 3 Arduino Mega
// 4x 4 Aspect signals plus 2x 2 Aspect signals


#include <CAN.h>
int message[8];

// pin definitions

// Signal 3.1
int ledPin15 = 3;  // Red
int ledPin16 = 4;  // Green
int signal1ButtonPress = 0;

// Signal 3.2
int ledPin13 = 5;  // Red
int ledPin14 = 6;  // Green
int signal2ButtonPress = 0;

// Signal 3.3
int ledPin9 = 30;  // Red
int ledPin10 = 31;  // Yellow-B
int ledPin11 = 32  // Green
int ledPin12 = 33; // Yellow-T
int signal3ButtonPress = 0;

// Signal 3.4
int ledPin5 = 26;  // Red
int ledPin6 = 27;  // Yellow-B
int ledPin7 = 28;  // Green
int ledPin8 = 29;  // Yellow-T
int signal4ButtonPress = 0;

// Signal 3.5
int ledPin1 = 22;  // Red
int ledPin2 = 23;  // Yellow-B
int ledPin3 = 24;  // Green
int ledPin4 = 25;  // Yellow-T
int signal5ButtonPress = 0; 


// global variables

void setup() 
{ 
// Setup CANbus  
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  Serial.println("CAN Live");

  // setup pin modes
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  pinMode(ledPin11, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  pinMode(ledPin13, OUTPUT);
  pinMode(ledPin14, OUTPUT);
  pinMode(ledPin15, OUTPUT);
  pinMode(ledPin16, OUTPUT);


  digitalWrite(ledPin1, 1);
  digitalWrite(ledPin2, 0);
  digitalWrite(ledPin3, 0);
  digitalWrite(ledPin4, 0);
  digitalWrite(ledPin5, 1);
  digitalWrite(ledPin6, 0);
  digitalWrite(ledPin7, 0);
  digitalWrite(ledPin8, 0);
  digitalWrite(ledPin9, 1);
  digitalWrite(ledPin10, 0);
  digitalWrite(ledPin11, 0);
  digitalWrite(ledPin12, 0);
  digitalWrite(ledPin13, 1);
  digitalWrite(ledPin14, 0);
  digitalWrite(ledPin15, 1);
  digitalWrite(ledPin16, 0);

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
        //Serial.print(message[0]);
        //Serial.print(message[1]);
        //signal_Function();
        //i++;

        switch (message[1])
        {
        case 0:
          break;
        case 5:
          signalFunction(message[1], signal5ButtonPress);
          if (signal5ButtonPress == 3)
          {
              signal5ButtonPress = 0;
          }
          else
          {
            signal5ButtonPress++;
          }
          break;
          case 4:
          signalFunction(message[1], signal4ButtonPress);
          if (signal4ButtonPress == 3)
          {
              signal4ButtonPress = 0;
          }
          else
          {
            signal4ButtonPress++;
          }
          break;
          case 3:
          signalFunction(message[1], signal3ButtonPress);
          if (signal3ButtonPress == 3)
          {
              signal3ButtonPress = 0;
          }
          else
          {
            signal3ButtonPress++;
          }
          break;
          case 2:
          signalFunction(message[1], signal2ButtonPress);
          if (signal2ButtonPress == 1)
          {
              signal2ButtonPress = 0;
          }
          else
          {
            signal2ButtonPress++;
          }
          break;
          case 1:
          signalFunction(message[1], signal1ButtonPress);
          if (signal1ButtonPress == 1)
          {
              signal1ButtonPress = 0;
          }
          else
          {
            signal1ButtonPress++;
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



int signalFunction(int signal, int press)
{
  switch (signal)
  {
    case 0:

      break;

    case 5:

      switch (press)
        {
          case 0:
          digitalWrite(ledPin1, 0);
          digitalWrite(ledPin2, 1);
          digitalWrite(ledPin3, 0);
          digitalWrite(ledPin4, 0);
          break;

          case 1:
          digitalWrite(ledPin1, 0);
          digitalWrite(ledPin2, 1);
          digitalWrite(ledPin3, 0);
          digitalWrite(ledPin4, 1);
          break;

          case 2:
          digitalWrite(ledPin1, 0);
          digitalWrite(ledPin2, 0);
          digitalWrite(ledPin3, 1);
          digitalWrite(ledPin4, 0);
          break;     

          case 3:
          digitalWrite(ledPin1, 1);
          digitalWrite(ledPin2, 0);
          digitalWrite(ledPin3, 0);
          digitalWrite(ledPin4, 0);
          break;     

                    
        }  break;

    case 4:
    
      switch (press)
        {
          case 0:
          digitalWrite(ledPin5, 0);
          digitalWrite(ledPin6, 1);
          digitalWrite(ledPin7, 0);
          digitalWrite(ledPin8, 0);
          break;

          case 1:
          digitalWrite(ledPin5, 0);
          digitalWrite(ledPin6, 1);
          digitalWrite(ledPin7, 0);
          digitalWrite(ledPin8, 1);
          break;

          case 2:
          digitalWrite(ledPin5, 0);
          digitalWrite(ledPin6, 0);
          digitalWrite(ledPin7, 1);
          digitalWrite(ledPin8, 0);
          break;    

          case 3:
          digitalWrite(ledPin5, 1);
          digitalWrite(ledPin6, 0);
          digitalWrite(ledPin7, 0);
          digitalWrite(ledPin8, 0);
          break;    


        }  break;

    case 3:
    
      switch (press)
        {
          case 0:
          digitalWrite(ledPin9, 0);
          digitalWrite(ledPin10, 1);
          digitalWrite(ledPin11, 0);
          digitalWrite(ledPin12, 0);
          break;

          case 1:
          digitalWrite(ledPin9, 0);
          digitalWrite(ledPin10, 1);
          digitalWrite(ledPin11, 0);
          digitalWrite(ledPin12, 1);
          break;

          case 2:
          digitalWrite(ledPin9, 0);
          digitalWrite(ledPin10, 0);
          digitalWrite(ledPin11, 1);
          digitalWrite(ledPin12, 0);
          break; 
          
          
          case 4:
          digitalWrite(ledPin9, 0);
          digitalWrite(ledPin10, 0);
          digitalWrite(ledPin11, 1);
          digitalWrite(ledPin12, 0);
          break;             

        } break;

  case 2:

      switch (press)
        {
          case 0:
          digitalWrite(ledPin13, 0);
          digitalWrite(ledPin14, 1);
          break;

          case 1:
          digitalWrite(ledPin13, 1);
          digitalWrite(ledPin14, 0);
          break;
    
        }   break;

  case 1:

      switch (press)
        {
          case 0:
          digitalWrite(ledPin15, 0);
          digitalWrite(ledPin16, 1);
          break;

          case 1:
          digitalWrite(ledPin15, 1);
          digitalWrite(ledPin16, 0);
          break;
    
        }   break;
  }

  return;
    
  
}