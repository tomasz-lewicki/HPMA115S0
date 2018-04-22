#include "Arduino.h"

class Honeywell_hpma
{
public:
    Honeywell_hpma();
	~Honeywell_hpma();
	
    bool measure();
    void begin(HardwareSerial& serial);
	
    int get_pm2_5();
    int get_pm10();

private:
	HardwareSerial *_serial;
	
    unsigned int pm2_5=0;
    unsigned int pm10=0;
	
	unsigned int checksum=0;
	
};

extern Honeywell_hpma honeywell_hpma;
