int LED_BUILTIN = 2;

const int output27 = 27;
const int LevelSensorPin = 34;
const int IndicatorPin = 2;

int WaterLevelValue = 9;
int level = 0;

//                      0    1    2    3    4    5
int LEVELarray [6] = {1125,1245,1450,1720,2080,2630} ;    // Array with the level reference values to determine the waterlevel
                                                          // the "0" level is applicable when there is no water in the reservoir
                                                          // the "5" level is applicable when the reservoir is full 


void initSerial() {
  uint32_t startTime = millis();

  Serial.begin(115200);
  delay(1000);
  while (!Serial && (millis() - startTime < 3000) ) {
    delay(10);
  }
  Serial.println("\nStarting ...");
  Serial.println("Serial port is ready!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  initSerial();

  pinMode(output27, OUTPUT);
  pinMode(IndicatorPin, OUTPUT);

  pinMode(LevelSensorPin, INPUT);


}  

void loop() {
  // put your main code here, to run repeatedly:
  /*
  Serial.println("HIGH");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.println("LOW");
  digitalWrite(LED_BUILTIN, LOW);
  */
  delay(500);
  MEASUREWATERLEVEL();
  INDICATEWATERLEVEL();
}

void MEASUREWATERLEVEL() {
  digitalWrite(output27, HIGH);           // make pin 27 HIGH
  delay(100);                             // allow the circuit to stabilize
  WaterLevelValue = analogRead(LevelSensorPin);  //Read data from analog pin and store it to WaterLevelvalue variable

  
  // for (int i = 0; i < 6 ; i++) {
    
  //   if ((WaterLevelValue > (LEVELarray[i] * 0.96)) && (WaterLevelValue < (LEVELarray[i] * 1.04)))              // allow a margin of 4% on the measured values to eliminate jitter and noise
  //   {
  //     level = i;
  //   }  
  // }

  digitalWrite(output27, LOW);           // make pin 27 LOW
  Serial.print("WaterLevelValue: ") ;Serial.print(WaterLevelValue);Serial.println();

  // Serial.print(" LEVELarray: "); Serial.print(level); Serial.print(" = "); Serial.print(LEVELarray[level]);Serial.print("   WaterLevelValue: "); Serial.print(WaterLevelValue); Serial.print("  Level: "); Serial.println(level);
  //// uncomment this code for determining the values to be put in the LEVELarray [] using the serial plotter and/or serial monitor or the ARDUINO IDE
   
}

void INDICATEWATERLEVEL() {
  if (WaterLevelValue > 1000) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}