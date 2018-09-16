#include <asf.h>

void adc_setup(void)
{
	//ADC clock setup
	adc_init(ADC, sysclk_get_main_hz(), sysclk_get_main_hz()/2, ADC_STARTUP_TIME_5);
	//Configure ADC tracking time, settling time and data transfer time
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_0, 0);
	//Setting 12 bits of resolution for the ADC
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	//Enabling ADC on channel 5
	adc_enable_channel(ADC, ADC_CHANNEL_5);
	//SW trigger with freerun off
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	//Enable End Of Conversion (EOC) interrupt on Channel 5
	adc_enable_interrupt(ADC, ADC_IER_EOC5);
	//Enable NVIC to accept interrupts from ADC
	NVIC_EnableIRQ(ADC_IRQn);
	//Send peripheral clock to ADC block
	pmc_enable_periph_clk(ID_ADC);
}

void ADC_Handler()
{
	// Lets read the value of ADC Channel 5 
	uint32_t result = adc_get_channel_value(ADC, ADC_CHANNEL_5);
}

int main (void)
{
	//Atmel SAM4s Board Setup
	board_init();
	
	//ADC Setup
	adc_setup();
	
	//Trigger ADC once and show the result in the ADC_Handler function
	adc_start(ADC);

	while (1) {
	}
}
