#ifndef INPUT_TO_MIDI_H
#define INPUT_TO_MIDI_H

#include "adc.h"
#include "timer.h"
#include <stdbool.h>

// Find by trial and error.
#define ADC1_IN9_BUFFER_LENGTH (8)

TIMER_HandleTypeDef htimer1;
uint32_t adc1_in9_buffer[ADC1_IN9_BUFFER_LENGTH] = {0};
uint32_t adc1_in9_value = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	uint32_t firstValue = adc1_in9_buffer[0] >> 5;
	bool allValid = true;

	for (uint8_t bufferIndex = 0; bufferIndex < ADC1_IN9_BUFFER_LENGTH; bufferIndex++)
	{
		if (adc1_in9_buffer[bufferIndex] >> 5 != firstValue)
		{
			allValid = false;
			break;
		}
	}

	if (allValid && firstValue != adc1_in9_value)
	{
		adc1_in9_value = firstValue;
		TIMER_SetMillis(&htimer1, 127 - adc1_in9_value);
	}
}

void TIMER1_Callback()
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void input_to_midi_start()
{
	  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&adc1_in9_buffer, ADC1_IN9_BUFFER_LENGTH);

	  TIMER_Init(&htimer1, TIMER1_Callback, 0);
}

void input_to_midi_loop()
{
	TIMER_Update(&htimer1);
}


#endif
