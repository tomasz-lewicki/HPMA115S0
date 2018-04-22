

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial2.begin(9600);
}

void serialHandler()
{
    int index=0;
    int pm10;
    int pm2_5;
    char value=0;
    char previous_value;

    while(Serial2.available())
    {
        value = Serial2.read();
        Serial.print(value,HEX);
        Serial.print(' ');
        
        if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d))
        {
            Serial.print("Error at index:");
            Serial.print(index);
            //break;
        }

        if( index == 6 || index == 8)
        {
          previous_value = value;
        }

        if( index == 7)
        {
          pm2_5 = previous_value*256+value;
        }

        if( index == 9)
        {
          pm10 = previous_value*256+value;
        }
        
        ++index;
        
    }

    Serial.println();
    Serial.print("pm10:");
    Serial.println(pm10);
    Serial.print("pm2.5:");
    Serial.println(pm2_5);
}

void loop() {
    char value=0;
    char previous_value=0;
    int pm2_5;
    int pm10;

    if(Serial2.available()) serialHandler();

    delay(1000);
    //Serial.println(pm2_5);
    //Serial.println(pm10);
}


