#include "HPMA115S0.h"

Honeywell_hpma::Honeywell_hpma()
{
    pm2_5=0;
    pm10=0;
	
}

Honeywell_hpma::~Honeywell_hpma()
{
	delete _serial;
}

void Honeywell_hpma::begin(HardwareSerial &serial)
{
	_serial=&serial;
}

bool Honeywell_hpma::measure()
{
	/**
	 *  Function that tries to read Honeywell_hpma frames from _serial
	 *  To avoid UART buffer overflow it should be called at least every 200ms
	 */
	
	this->checksum=0;
	byte buffer[32];
	uint8_t attempts = 0;
	
	//if there was no start byte after 100 attempts, return false (fail)
	//this is to avoid infinite loop 
    while (_serial->available() && ++attempts < 100)
    {
		
		//discard data until start byte (0x42) comes 
		if(_serial->peek() != 0x42)
		{
			_serial->read(); //flush any byte that is not 0x42
			continue;
		}
		else 	
		{
			//A frame begining byte detected (0x42)
			if(_serial->available() < 32) delay(30); // give a chance for all bits to come
		}
		
		if(_serial->available() >= 32)
		{
			_serial->readBytes(buffer,32);
		}
		//if there is less than 32 bytes in buffer after 30ms something must have happened, abort
		else return false;
		
		for(int i=0;i<30;i++)
		{
			this->checksum+=buffer[i];
		}
		
		if(this->checksum != buffer[30]*256+buffer[31]) return false;
		
		
		/*
		//For debugging purposes you can display frame
		for(int i=0;i<32;i++)
		{
			this->checksum+=buffer[i];
			Serial.print(buffer[i]);
			Serial.print(' ');
		}
		

		Serial.println();
		
		*/
		
		this->pm2_5=buffer[6]*256+buffer[7];
		this->pm10=buffer[8]*256+buffer[9];
		
		return true;
    }
	return false;
}


int Honeywell_hpma::get_pm2_5()
    {
        return this->pm2_5;
    }

int Honeywell_hpma::get_pm10()
    {
        return this->pm10;
    }


	
Honeywell_hpma honeywell_hpma; //create an instance of pms3003

