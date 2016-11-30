IntervalTimer myTimer;
int heartbeat;
float timer_value = 1;
float timer_save[6];
int rssi[6];
int rssi_threshold = 315;
int pin[6] = {9,8,7,6,5,4};

void setup()
{
  Serial.begin(9600); //opens serial port, sets data rate to 9600 bps
  myTimer.begin(timer, 1000);  // increment timer every 0.001 seconds
  heartbeat = 1;
}

void timer(void)
{
  timer_value = timer_value + 0.001;
  for (int i = 0; i < 1; i++)   // for (int i = 0; i < 6; i++){
  {
    rssi[i] = analogRead(pin[i]);
    if (rssi[i] > rssi_threshold) {timer_save[i] = timer_value;}
  }
}

void loop()
{
  for (int i = 0; i < 7; i++){
    if (i == 6) 
    {
      Serial.print(" #");
      Serial.print("\t");
      Serial.print("202");
      Serial.print("\t");   
      Serial.print(heartbeat);
      Serial.print("\t");
      Serial.print("0");
      Serial.print("\t");
      Serial.println("xC249");
      delay(1000);
      heartbeat = heartbeat + 1;
     }
    else
    {    
      if (timer_save[i] > 0)
      {
        noInterrupts();
        Serial.print(" @");
        Serial.print("\t");
        Serial.print("202");
        Serial.print("\t");  
        Serial.print(heartbeat);
        Serial.print("\t");
        Serial.print("1002021");
        Serial.print("\t");
        Serial.print(timer_save[i], 3); // needs time stamp
        Serial.print("\t");
        Serial.print("22"); // needs number of times read??
        Serial.print("\t");
        Serial.print("111");
        Serial.print("\t");
        Serial.print(rssi[i]);
        Serial.print("\t");
        Serial.println("x5724");
        timer_save[i] = 0;
        interrupts();
        delay(1000);
        heartbeat = heartbeat + 1;
      }
    }
  }
}
