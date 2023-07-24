#define MC144111_DIN_PIN 2
#define MC144111_CLK_PIN 3
#define MC144111_ENB_PIN 4 

void shiftOut6bit(uint8_t level)
{  
  for(uint8_t i=0; i<6; i++)
  {
    if ((level & 0x20) == 0x20) 
			digitalWrite(MC144111_DIN_PIN, 1); 
    else 
			digitalWrite(MC144111_DIN_PIN, 0);
    delayMicroseconds(2);
    digitalWrite(MC144111_CLK_PIN, 1);    
    digitalWrite(MC144111_CLK_PIN, 0);
    delayMicroseconds(2);
    level <<= 1;
  }  
}

void setup()
{
  pinMode(MC144111_DIN_PIN, OUTPUT); 
  pinMode(MC144111_CLK_PIN, OUTPUT);
  pinMode(MC144111_ENB_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("input 4 numbers 0-63, as example: 1 2 3 4, where 4->R1 3->R2 2->R3 1->R4; no CR");
}

void loop()
{
  while (Serial.available())
  {
    uint8_t level = Serial.parseInt();    
    digitalWrite(MC144111_ENB_PIN, 0);
    shiftOut6bit(level);
    digitalWrite(MC144111_ENB_PIN, 1);
    Serial.println(level);
  }
}
