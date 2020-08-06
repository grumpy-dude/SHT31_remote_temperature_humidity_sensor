/*
 * SHT31.h
 *
 * Created: 2020-07-22 8:50:16 AM
 *  Author: Me
 */


#ifndef SHT31_H_
#define SHT31_H_


#ifdef __cplusplus
  #if __cplusplus >= 201103L
     extern "C" {
  #else
    #error "C++11 or later required"
  #endif /* __cplusplus >= 201103L */
#elif defined(__STDC_VERSION__)
  #if __STDC_VERSION__ < 201112L
    #error "C11 or later required"
  #endif /* __STDC_VERSION__ < 201112L */
#else
  #warning "CODE NOT INTENDED FOR THIS PROGRAMMING LANGUAGE/COMPILER OPTION"
#endif /* __cplusplus */


#include <i2c_types.h>


static const i2c_address_t SHT31_Default_Addr   = 0x44;
static const i2c_address_t SHT31_Alternate_Addr = 0x45;

/* From section 4.13 "Conversion of Signal Output" of Sensiron SHT3x datasheet */
static const uint32_t SHT31_Common_Conversion_Factor        = 65535L;
static const uint32_t SHT31_RH_Conversion_Factor            = 100L;
static const uint32_t SHT31_TCentigrade_Conversion_Factor   = 175L;
static const int32_t  SHT31_TCentigrade_Conversion_Offset   = -45L;
static const uint32_t SHT31_TFahrenheit_Conversion_Factor   = 315L;
static const int32_t  SHT31_TFahrenheit_Conversion_Offset   = -49L;


typedef enum {
    SHT31_Command_1ShotMeasure_Repeatability_High                       = 0x2400,
    SHT31_Command_1ShotMeasure_Repeatability_Medium                     = 0x240B,
    SHT31_Command_1ShotMeasure_Repeatability_Low                        = 0x2416,

    SHT31_Command_1ShotMeasure_Repeatability_High_Clock_Stretching      = 0x2C06,
    SHT31_Command_1ShotMeasure_Repeatability_Medium_Clock_Stretching    = 0x2C0D,
    SHT31_Command_1ShotMeasure_Repeatability_Low_Clock_Stretching       = 0x2C16,

    SHT31_Command_PeriodicMeasure500kps_Repeatability_High              = 0x2032,
    SHT31_Command_PeriodicMeasure500kps_Repeatability_Medium            = 0x2024,
    SHT31_Command_PeriodicMeasure500kps_Repeatability_Low               = 0x202F,

    SHT31_Command_PeriodicMeasure01mps_Repeatability_High               = 0x2130,
    SHT31_Command_PeriodicMeasure01mps_Repeatability_Medium             = 0x2126,
    SHT31_Command_PeriodicMeasure01mps_Repeatability_Low                = 0x212D,

    SHT31_Command_PeriodicMeasure02mps_Repeatability_High               = 0x2236,
    SHT31_Command_PeriodicMeasure02mps_Repeatability_Medium             = 0x2220,
    SHT31_Command_PeriodicMeasure02mps_Repeatability_Low                = 0x222B,

    SHT31_Command_PeriodicMeasure04mps_Repeatability_High               = 0x2334,
    SHT31_Command_PeriodicMeasure04mps_Repeatability_Medium             = 0x2322,
    SHT31_Command_PeriodicMeasure04mps_Repeatability_Low                = 0x2329,

    SHT31_Command_PeriodicMeasure10mps_Repeatability_High               = 0x2737,
    SHT31_Command_PeriodicMeasure10mps_Repeatability_Medium             = 0x2721,
    SHT31_Command_PeriodicMeasure10mps_Repeatability_Low                = 0x272A,

    SHT31_Command_PeriodicMeasureART                                    = 0x2B32,

    SHT31_Command_Break_StopPeriodicMeasure                             = 0x3093,

    SHT31_Command_SoftReset_ReInit                                      = 0x30A2,

    SHT31_Command_HeaterEnable                                          = 0x306D,
    SHT31_Command_HeaterDisable                                         = 0x3066,

    SHT31_Command_ClearStatusRegister                                   = 0x3041,
    SHT31_Command_ReadStatusRegister                                    = 0xF32D,
} SHT31_command_t;


typedef union __attribute__((packed)) {
    uint16_t status_as_word;
    struct {
        uint8_t status_low_byte;
        uint8_t status_high_byte;
    } status_as_bytes;
    struct {
        bool       write_data_checksum_fail    : 1;
        bool       command_fail                : 1;
        uint8_t    reserved1                   : 2;
        bool       system_reset_detected       : 1;
        uint8_t    reserved2                   : 5;
        bool       T_tracking_alert            : 1;
        bool       RH_tracking_alert           : 1;
        uint8_t    reserved3                   : 1;
        bool       heater_on                   : 1;
        uint8_t    reserved4                   : 1;
        bool       alert_pending               : 1;
    } status_bits;
} SHT31_status_register_t;
_Static_assert (sizeof(SHT31_status_register_t) == 2, "SHT31_status_register_t incorrect size");


bool                    SHT31Command                ( i2c_address_t SHT31_i2c_address, SHT31_command_t SHT31_command );
void                    SHT31Reset                  ( i2c_address_t SHT31_i2c_address );
SHT31_status_register_t SHT31Status                 ( i2c_address_t SHT31_i2c_address );
bool                    SHT31RawTemperatureHumidity ( i2c_address_t SHT31_i2c_adress, uint16_t* SHT31_raw_temperature_value, uint16_t* SHT31_raw_humidity_value );


#ifdef __cplusplus
    }
#endif


#endif /* SHT31_H_ */
