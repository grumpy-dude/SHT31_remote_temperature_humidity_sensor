/**
 * \file
 *
 * \brief ADC Basic driver declarations.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#ifndef ADC_BASIC_H_INCLUDED
#define ADC_BASIC_H_INCLUDED

#include <compiler.h>
#include <adc_basic.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*adc_irq_cb_t)(void);

/** Datatype for the result of the ADC conversion */
typedef uint16_t adc_result_t;

//* Analog channel selection */
//typedef uint8_t adc_0_channel_t;
typedef enum {
	ADC_Channel_0			= 0x00,
	ADC_Channel_1			= 0x01,
	ADC_Channel_2			= 0x02,
	ADC_Channel_3			= 0x03,
	ADC_Channel_4			= 0x04,
	ADC_Channel_5			= 0x05,
	ADC_Channel_6			= 0x06,
	ADC_Channel_7			= 0x07,
	ADC_Channel_Temperature = 0x08,
	ADC_Channel_Vbg			= 0x0E,
	ADC_Channel_Gnd			= 0x0F
	} adc_0_channel_t;

int8_t ADC_0_init();

void ADC_0_enable();

void ADC_0_disable();

void ADC_0_start_conversion();

bool ADC_0_is_conversion_done();

adc_result_t ADC_0_get_conversion_result(void);

adc_result_t ADC_0_get_conversion(adc_0_channel_t channel);

uint8_t ADC_0_get_resolution();

#ifdef __cplusplus
}
#endif

#endif /* ADC_BASIC_H_INCLUDED */
