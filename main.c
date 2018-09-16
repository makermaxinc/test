#include <asf.h>

void adc_register_setup(void)
{
	//Reset the ADC 
	ADC->ADC_CR = 0x01;
	//Get the mode register ready for conversion on channel 5
	//With a software trigger
	ADC->ADC_MR = 0x20050000;
	//Enable ADC Channel 5
	ADC->ADC_CHER = 0x20;
	//Enable End of Conversion (EOC) interrupt on channel 5
	ADC->ADC_IER = 0x20;
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
	board_init();
	//Setup the ADC to read on channel 5 with a SW trigger
	adc_register_setup();
	
	//Start ADC Conversion once
	ADC->ADC_CR = 0x2;
	printf("Testing");
	
	while (1) {
		
	}
}
