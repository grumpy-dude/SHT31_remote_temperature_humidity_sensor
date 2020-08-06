/*
 * SHT31.c
 *
 * Created: 2020-07-28 9:09:19 AM
 *  Author: Me
 */

#include <atmel_start.h>
#include <stdio.h>
#include <util/delay.h>
#include <i2c_simple_master.h>
#include "SHT31.h"

#ifdef DEBUG
    #define _DEBUG_PRINTF( ... )    printf( __VA_ARGS__ )
#else
    #define _DEBUG_PRINTF( ... )
#endif


bool SHT31Command( i2c_address_t SHT31_i2c_address, SHT31_command_t SHT31_command )
{
    i2c_error_t i2c_0_write_result;
    uint8_t     SHT31_command_bytes[2];


    // Ensure command bytes go over I2C bus in correct order, regardless of host architecture
    SHT31_command_bytes[0] = SHT31_command >> 8;
    SHT31_command_bytes[1] = SHT31_command &  0xFF;


    if( (i2c_0_write_result=I2C_0_writeNBytes(SHT31_i2c_address, SHT31_command_bytes, sizeof(SHT31_command_bytes))) ==
      I2C_NOERR )
    {
        return true;
    }


    _DEBUG_PRINTF( "SHT31Command fail: I2C error 0x%x\r\n", i2c_0_write_result );
    return false;
}


void SHT31Reset( i2c_address_t SHT31_i2c_address )
{
    if( true == SHT31Command(SHT31_i2c_address, SHT31_Command_SoftReset_ReInit) )
    {
        _delay_ms( 10 );
    }
    else
    {
        _DEBUG_PRINTF( "SHT31 Reset Fail\r\n" );
    }
}


SHT31_status_register_t SHT31Status( i2c_address_t SHT31_i2c_address )
{
    SHT31_status_register_t SHT31_status;


    SHT31_status.status_as_word = 0xFFFF;


    if( false == SHT31Command(SHT31_i2c_address, SHT31_Command_ReadStatusRegister) )
    {
        _DEBUG_PRINTF( "SHT31 Read Status Command Fail\r\n" );
    }
    else if( I2C_0_readNBytes(SHT31_i2c_address, &SHT31_status, sizeof(SHT31_status)) != I2C_NOERR )
    {
        _DEBUG_PRINTF( "I2C Read SHT31 Status fail\r\n" );
    }


    return SHT31_status;
}


bool SHT31RawTemperatureHumidity( i2c_address_t SHT31_i2c_adress, uint16_t* SHT31_raw_temperature_value, uint16_t* SHT31_raw_humidity_value )
{
	uint8_t SHT31_temp_hum_data[6];


    *SHT31_raw_temperature_value    = UINT16_MAX;
    *SHT31_raw_humidity_value       = UINT16_MAX;


	if( SHT31Command(SHT31_Default_Addr, SHT31_Command_1ShotMeasure_Repeatability_High) == false )
	{
		_DEBUG_PRINTF( "I2C Read SHT31 Temperature & Humidity command fail\r\n" );
		return false;
	}
	_delay_ms( 20 );

	if( I2C_0_readNBytes(SHT31_Default_Addr, SHT31_temp_hum_data, sizeof(SHT31_temp_hum_data)) != I2C_NOERR )
	{
		_DEBUG_PRINTF( "I2C Read SHT31 Temperature & Humidity fail\r\n" );
		return false;
	}


    *SHT31_raw_temperature_value    = (SHT31_temp_hum_data[0] << 8) | SHT31_temp_hum_data[1];
    *SHT31_raw_humidity_value       = (SHT31_temp_hum_data[3] << 8) | SHT31_temp_hum_data[4];


    return true;
}