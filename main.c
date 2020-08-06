#include <atmel_start.h>
#include <stdio.h>
#include <util/delay.h>
#include <i2c_simple_master.h>
#include "SHT31.h"


// Define some constants for to use for fixed-point integer math
static const int32_t FixedPoint_3Places_Factor   = 1000L;
static const int32_t FixedPoint_2Places_Factor   = 100L;
static const int32_t FixedPoint_1Place_Reduction = 10L;
static const int32_t FixedPoint_Rounding_Factor  = 5L;


static const uint32_t V_Bandgap = 1080;     /* Calibrated "Vbg" in millivolts */
static const uint16_t ADC_Max   = 1024;     /* From section 28.7 "ADC Conversion Result" of ATmega328 datasheet */


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
    _delay_ms( 2 );

    SHT31Reset( SHT31_Default_Addr );

    SHT31_status_register_t SHT31_status = SHT31Status( SHT31_Default_Addr );
    if( SHT31_status.status_as_word != 0xFFFF )
    {
        printf( "SHT31 status: 0x%04X\r\n", SHT31_status.status_as_word );
        printf( "  Write data checksum fail: %u\r\n", SHT31_status.status_bits.write_data_checksum_fail );
        printf( "  Command fail:             %u\r\n", SHT31_status.status_bits.command_fail );
        printf( "  System reset detected:    %u\r\n", SHT31_status.status_bits.system_reset_detected );
        printf( "  T tracking alert:         %u\r\n", SHT31_status.status_bits.T_tracking_alert );
        printf( "  RH tracking alert:        %u\r\n", SHT31_status.status_bits.RH_tracking_alert );
        printf( "  Heater on:                %u\r\n", SHT31_status.status_bits.heater_on );
        printf( "  Alert pending:            %u\r\n", SHT31_status.status_bits.alert_pending );
    }


	/* Replace with your application code */
	while( true )
    {
        printf( "\r\n" );

        ADC_0_start_conversion();
        _delay_ms( 2 );
        if( ADC_0_is_conversion_done() )
        {
            uint32_t vcc = ((ADC_Max * V_Bandgap) / ADC_0_get_conversion_result());
        	printf( "Vcc:         %lu.%02luV\r\n", vcc/FixedPoint_3Places_Factor, ((vcc%FixedPoint_3Places_Factor)+FixedPoint_Rounding_Factor)/FixedPoint_1Place_Reduction );
    	}


        uint16_t raw_temperature_value, raw_humidity_value;
        int32_t  temperature_C, temperature_F;
        uint32_t humidity_percent;

        if( SHT31RawTemperatureHumidity(SHT31_Default_Addr, &raw_temperature_value, &raw_humidity_value) )
        {
            temperature_F = (SHT31_TFahrenheit_Conversion_Offset * FixedPoint_2Places_Factor) + ((raw_temperature_value * SHT31_TFahrenheit_Conversion_Factor * FixedPoint_2Places_Factor) / SHT31_Common_Conversion_Factor);
            temperature_C = (SHT31_TCentigrade_Conversion_Offset * FixedPoint_2Places_Factor) + ((raw_temperature_value * SHT31_TCentigrade_Conversion_Factor * FixedPoint_2Places_Factor) / SHT31_Common_Conversion_Factor);
            printf( "Temp:        %li.%liF (", (temperature_F/FixedPoint_2Places_Factor), ((temperature_F%FixedPoint_2Places_Factor)+FixedPoint_Rounding_Factor)/FixedPoint_1Place_Reduction );
            printf(           "%li.%liC)\r\n", (temperature_C/FixedPoint_2Places_Factor), ((temperature_C%FixedPoint_2Places_Factor)+FixedPoint_Rounding_Factor)/FixedPoint_1Place_Reduction );

            humidity_percent = (raw_humidity_value * SHT31_RH_Conversion_Factor * FixedPoint_3Places_Factor) / SHT31_Common_Conversion_Factor;
            printf( "Humidity:    %lu.%02lu%%\r\n", humidity_percent/FixedPoint_3Places_Factor,
            ((humidity_percent%FixedPoint_3Places_Factor)+FixedPoint_Rounding_Factor)/FixedPoint_1Place_Reduction );
        }


    	_delay_ms( 3000 );
	}
}
