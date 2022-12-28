

//------------------------------------------------------------------------------
#include "TC72_Tempr.h"
#include "spi.h"
#include "avr/io.h"
#include "util/delay.h"
//------------------------------------------------------------------------------
void TC72_Init()
{
  
  /* Initialize the SPI driver as Slave */
  SPI_initMaster();
  //make ss =0 no select slave
  PORTB = PORTB & (~(1<<4));
}
//------------------------------------------------------------------------------
int TC72_ReadTempr()
{ 
  int temprMSB,temprLSB; 
    
  SPI_sendReceiveByte(TEMPR_REG);                  //Access Tempr register for reading
  temprMSB = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
  temprLSB = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);


  
  return ( (temprMSB<<8) + temprLSB );
}
//------------------------------------------------------------------------------
float GetData(signed int tempr)
{
  float result = (float)(tempr>>8);      //Discard LSByte (Only holds fraction flag bits)
  char count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    count = count >> 6; 
    result = result + (count * 0.25);
  }
  
  return  (result*2);
}
//------------------------------------------------------------------------------
signed int Continous_reading(void){
	//make ss =1 select slave
	PORTB = PORTB | (1<<4);
	SPI_sendReceiveByte(CONTROL_REG);
	SPI_sendReceiveByte(START_CONV);      //Continous conversion
	//make ss =0 no select slave
	PORTB = PORTB & (~(1<<4));
	
	_delay_ms(300);
	
	//make ss =1 select slave
	PORTB = PORTB | (1<<4);
	SPI_sendReceiveByte(TEMPR_REG);                  //Access Tempr register for reading
	int temprMSB = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	int temprLSB = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	//make ss =0 no select slave
	PORTB = PORTB & (~(1<<4));
	return (signed int)((temprMSB<<8) + temprLSB);
}


