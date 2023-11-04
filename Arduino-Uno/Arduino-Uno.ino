#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <NewPing.h>


AF_DCMotor MotorLeft(1); //LEFT
AF_DCMotor MotorRight(4); //RIGHT
#define TRUE 1
#define FALSE 0

#define OPEN 1
#define CLOSED 0
#define PARTIAL -1

#define LEFT_OPEN 2
#define LEFT_CLOSED 1

#define RIGHT_OPEN 4
#define RIGHT_CLOSED 3

#define CLOSED_MEASURE 11 //measurment where curtain is considered closed (cm)
#define OPEN_MEASURE 62
#define MAX_DISTANCE 80 //Maximum measure distance for sensors (cm)

#define STABILITY_DELAY 2500 // Delay (in ms) right after motors stop running, and before the measure to confirm a succesful opening or closure of curtains

#define ISOPEN_TIME 0.2 //time isOpen() takes to run (estimated with the delays and iterations)
#define MAX_MOTOR_RUN 9.5 //time in seconds for the curtains to theoreticcaly open
#define MAX_BAIL_COUNT 1 //max number of bails before system reset.

uint8_t motorSpeed = 175;




SoftwareSerial ESP_Serial(17, 16); //Tx,Rx // A3, A2


NewPing left_sonar(14, 15, MAX_DISTANCE);
NewPing right_sonar(18, 19, MAX_DISTANCE);



void setup() {

  Serial.begin(9600); //Serial for debug
  ESP_Serial.begin(9600);


  //  delay(15 * 1000); //15 second delay to allow ESP to connect to WiFi
}

void loop() {
  while (ESP_Serial.available() > 0) //While new data is available
  {

    int incomingValue;
    int physicalMatch;

    int innerBail; //to exit from running motor loop
    int bailCount = 0; // number of bails, needed to reset entire system
    int iterations; //counts each iteration before bailing


    incomingValue = ESP_Serial.parseInt(); // assign incoming value to apply the change
    ESP_Serial.flush();  //Clear any rogue data after taking first Integer

    Serial.print("Data available : "); //For Debug
    Serial.println(incomingValue);


    physicalMatch = FALSE; //Assumes action is needed

    if (incomingValue == LEFT_OPEN || incomingValue == LEFT_CLOSED) { //if incomingValue is for left curtain

      if (incomingValue == LEFT_OPEN) { //command received to open blind
        Serial.print("OPEN LEFT CURTAIN");
        do {
          if (isOpen('L') == OPEN) //if curtain is already open
            physicalMatch = TRUE;

          Serial.print("physicalMatch = "); //DEBUG
          Serial.println(physicalMatch);


          if (physicalMatch == FALSE) { //if the curtain is not open

            iterations = 0;
            innerBail = FALSE;

            do {
              Serial.println("RUN LEFT MOTOR"); //Debug

              MotorLeft.run(FORWARD);     //turn on motor 1
              MotorLeft.setSpeed(motorSpeed);

              iterations = iterations + 1;

              if (iterations >= (MAX_MOTOR_RUN / ISOPEN_TIME)) { //if max iteration is exceeded
                bailCount = bailCount + 1; //
                innerBail = TRUE; //Bail!
                Serial.println("INNER BAIL!");
              }

            } while (isOpen('L') != OPEN && innerBail != TRUE);

            MotorLeft.run(RELEASE); //turn off motor 1
            delay(STABILITY_DELAY); //Stability delay

            if (isOpen('L') == OPEN) //Verify that the curtain is in fact open
              physicalMatch = TRUE;
          }
        } while (physicalMatch == FALSE && bailCount < MAX_BAIL_COUNT); // Repeat until we match Physical State with command
      }
      else if (incomingValue == LEFT_CLOSED) {

        do {
          if (isOpen('L') == CLOSED) //if curtain is already CLOSED
            physicalMatch = TRUE;


          if (physicalMatch == FALSE) { //if the curtain is not open

            iterations = 0;
            innerBail = FALSE;

            do {
              MotorLeft.run(BACKWARD);     //turn on motor 1
              MotorLeft.setSpeed(motorSpeed);

              iterations = iterations + 1;

              if (iterations >= (MAX_MOTOR_RUN / ISOPEN_TIME)) { //if max iteration is exceeded
                bailCount = bailCount + 1; //
                innerBail = TRUE; //Bail!
                Serial.println("INNER BAIL!");
              }

            } while (isOpen('L') != CLOSED && innerBail != TRUE); //repeat until we measure that it's closed

            MotorLeft.run(RELEASE); //turn off motor 1 once closed
            delay(STABILITY_DELAY); //Stability delay

            if (isOpen('L') == CLOSED) //Verify that the curtain is in fact closed
              physicalMatch = TRUE;
          }
        } while (physicalMatch == FALSE && bailCount < MAX_BAIL_COUNT); // Repeat until we match Physical State with command

      }

      // Serial.print("incomingValue for left curtain = "); //Debug
      // Serial.println(incomingValue); //Debug
    }
    else if (incomingValue == RIGHT_OPEN || incomingValue == RIGHT_CLOSED) { //si c'est pour le rideau DROIT

      if (incomingValue == RIGHT_OPEN) { //command received to open blind

        do {
          if (isOpen('R') == OPEN) //if curtain is already open
            physicalMatch = TRUE;


          if (physicalMatch == FALSE) { //if the curtain is not open

            iterations = 0;
            innerBail = FALSE;

            do {
              Serial.println("RUN RIGHT MOTOR");


              MotorRight.run(FORWARD);     //turn on motor 2
              MotorRight.setSpeed(motorSpeed);

              iterations = iterations + 1;

              if (iterations >= (MAX_MOTOR_RUN / ISOPEN_TIME)) { //if max iteration is exceeded
                bailCount = bailCount + 1; //
                innerBail = TRUE; //Bail!
                Serial.println("INNER BAIL!");
              }


            } while (isOpen('R') != OPEN && innerBail != TRUE); //repeat while it's not open

            MotorRight.run(RELEASE); //turn off motor 2
            delay(STABILITY_DELAY); //Stability delay

            if (isOpen('R') == OPEN) //Verify that the curtain is in fact open
              physicalMatch = TRUE;
          }
        } while (physicalMatch == FALSE && bailCount < MAX_BAIL_COUNT); // Repeat until we match Physical State with desired command
      }
      else if (incomingValue == RIGHT_CLOSED) {

        do {
          if (isOpen('R') == CLOSED) //if curtain is already CLOSED
            physicalMatch = TRUE;


          if (physicalMatch == FALSE) { //if the curtain is not open

            iterations = 0;
            innerBail = FALSE;

            do {
              MotorRight.run(BACKWARD);     //turn on motor 2
              MotorRight.setSpeed(motorSpeed);

              iterations = iterations + 1;

              if (iterations >= (MAX_MOTOR_RUN / ISOPEN_TIME)) { //if max iteration is exceeded
                bailCount = bailCount + 1; //
                innerBail = TRUE; //Bail!
                Serial.println("INNER BAIL!");
              }

            } while (isOpen('R') != CLOSED && innerBail != TRUE); //repeat until we measure that it's closed

            MotorRight.run(RELEASE); //turn off motor 2 once closed
            delay(STABILITY_DELAY); //Stability delay

            if (isOpen('R') == CLOSED) //Verify that the curtain is in fact closed
              physicalMatch = TRUE;
          }
        } while (physicalMatch == FALSE && bailCount < MAX_BAIL_COUNT); // Repeat until we match Physical State with command

        //Serial.print("rightCurtainState = "); //Debug
        //Serial.println(rightCurtainState); //Debug
      }
    }

/*
    if (incomingValue > 4 || incomingValue < 1) {
      delay(4000); // Delay in case of receiving rogue data
      Serial.println("Rogue data delay!");
      ESP_Serial.flush(); //flush rogue data
    }

    //Serial.println("End of data!"); //Debug
    delay(250); //Stability delay
    */


  }
}


int isOpen(char side) {

  double average;
  double measures[5];
  int ix;

  for (ix = 0; ix < 5; ix = ix + 1)
  {
    if (side == 'L')
      measures[ix] = left_sonar.ping_cm();
    else if (side == 'R')
      measures[ix] = right_sonar.ping_cm();

    delay(40);
  }

  bubble_sort(measures);

  average = (measures[1] + measures[2] + measures[3]) / 3;


  Serial.print("Average measure is : ");
  Serial.print(average);
  Serial.println(" cm"); //DEBUG

  if (average <= CLOSED_MEASURE && average > 0.0)
    return (CLOSED);
  else if (average >= OPEN_MEASURE && average <= MAX_DISTANCE)
    return (OPEN);
  else //IF THE BLIND IS PARTIALLY OPENED
    return (PARTIAL);

}


void bubble_sort(double tbl[]) {

  int nbr = 5; //size of array
  int pass; //to count number of passes
  int flag = TRUE; //indicate sort is complete early
  int ix; //indexing of array
  double temp; //temporary value

  for (pass = 1; pass < nbr && flag == TRUE; pass = pass + 1)
  {
    int nbr = 5; //size of array
    int pass; //to count number of passes
    int flag = TRUE ; //indicate sort is complete early
    int ix; //indexing of array
    double temp; //temporary value

    for (pass = 1; pass < nbr && flag == TRUE; pass = pass + 1)
    {
      flag = FALSE;

      for (ix = 0; ix < (nbr - pass); ix = ix + 1)
      {
        if (tbl[ix] > tbl[ix + 1]) //if current value is bigger than the next
        {
          //sink bigger value and float smaller value
          temp = tbl[ix + 1];
          tbl[ix + 1] = tbl[ix];
          tbl[ix] = temp;
          flag = TRUE;
        }
      }
    }
  }
}
