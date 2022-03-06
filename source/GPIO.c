/**
 This is the source file for the GPIO device driver for Kinetis K64.
 It contains all the implementation for configuration functions and runtime functions.
 i.e., this is the application programming interface (API) for the GPIO peripheral.
 \author Axel Ramirez Herrera, ie727589@iteso.mx
 \		Oliver Rodea Aragon, 	ie7275492@iteso.mx
 \date	16/02/2022
 \todo
 Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "Bits.h"

static void (*gpio_C_callback)(void) = 0;
static void (*gpio_A_callback)(void) = 0;

/**This function sets the clock at selected port*/
uint8_t GPIO_clock_gating (gpio_port_name_t port_name)
{
  switch (port_name)
    /** Selecting the GPIO for clock enabling*/
    {
    case GPIO_A: /** GPIO A is selected*/
      SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
      break;
    case GPIO_B: /** GPIO B is selected*/
      SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
      break;
    case GPIO_C: /** GPIO C is selected*/
      SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
      break;
    case GPIO_D: /** GPIO D is selected*/
      SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
      break;
    case GPIO_E: /** GPIO E is selected*/
      SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
      break;
    default: /**If doesn't exist the option*/
      return (FALSE);
    } // end switch
  /**Successful configuration*/
  return (TRUE);
} // end function

/**This function sets as GPIO PORT and pin selected*/
uint8_t GPIO_pin_control_register (
    gpio_port_name_t port_name, uint8_t pin,
    const gpio_pin_control_register_t *pinControlRegister)
{

  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      PORTA->PCR[pin] = *pinControlRegister;
      break;
    case GPIO_B:/** GPIO B is selected*/
      PORTB->PCR[pin] = *pinControlRegister;
      break;
    case GPIO_C:/** GPIO C is selected*/
      PORTC->PCR[pin] = *pinControlRegister;
      break;
    case GPIO_D:/** GPIO D is selected*/
      PORTD->PCR[pin] = *pinControlRegister;
      break;
    case GPIO_E: /** GPIO E is selected*/
      PORTE->PCR[pin] = *pinControlRegister;
    default:/**If doesn't exist the option*/
      return (FALSE);
      break;
    }
  /**Successful configuration*/
  return (TRUE);
}

/**This function writes the GPIO port selected at the data given*/
void GPIO_write_port (gpio_port_name_t port_name, uint32_t data)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      GPIOA->PDOR = data;
      break;
    case GPIO_B:/** GPIO B is selected*/
      GPIOB->PDOR = data;
      break;
    case GPIO_C:/** GPIO C is selected*/
      GPIOC->PDOR = data;
      break;
    case GPIO_D:/** GPIO D is selected*/
      GPIOD->PDOR = data;
      break;
    case GPIO_E: /** GPIO E is selected*/
      GPIOE->PDOR = data;
    default:/**If doesn't exist the option*/
      return;
      break;
    }
}
/**This function returns the data at GPIO port selected*/
uint32_t GPIO_read_port (gpio_port_name_t port_name)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      return (GPIOA->PDIR);
      break;
    case GPIO_B:/** GPIO B is selected*/
      return (GPIOB->PDIR);
      break;
    case GPIO_C:/** GPIO C is selected*/
      return (GPIOC->PDIR);
      break;
    case GPIO_D:/** GPIO D is selected*/
      return (GPIOD->PDIR);
      break;
    case GPIO_E: /** GPIO E is selected*/
      return (GPIOE->PDIR);
    default:/**If doesn't exist the option*/
      return (FALSE);
      break;
    }
}

/**This function returns the value of the pin selected at the port also selected*/
uint8_t GPIO_read_pin (gpio_port_name_t port_name, uint8_t pin)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      return ((GPIOA->PDIR & 1<<pin) >> pin);
      break;
    case GPIO_B:/** GPIO B is selected*/
      return ((GPIOB->PDIR & 1<<pin) >> pin);
      break;
    case GPIO_C:/** GPIO C is selected*/
      return ((GPIOC->PDIR & 1<<pin) >> pin);
      break;
    case GPIO_D:/** GPIO D is selected*/
      return ((GPIOD->PDIR & 1<<pin) >> pin);
      break;
    case GPIO_E: /** GPIO E is selected*/
      return ((GPIOE->PDIR & 1<<pin) >> pin);
    default:/**If doesn't exist the option*/
      return (FALSE);
      break;
    }
}

/**This function sets to 1 the pin selected at selected port*/
void GPIO_set_pin (gpio_port_name_t port_name, uint8_t pin)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      GPIOA->PSOR |= 1 << pin;
      break;
    case GPIO_B:/** GPIO B is selected*/
      GPIOB->PSOR |= 1 << pin;
      break;
    case GPIO_C:/** GPIO C is selected*/
      GPIOC->PSOR |= 1 << pin;
      break;
    case GPIO_D:/** GPIO D is selected*/
      GPIOD->PSOR |= 1 << pin;
      break;
    case GPIO_E: /** GPIO E is selected*/
      GPIOE->PSOR |= 1 << pin;
    default:/**If doesn't exist the option*/
      return;
      break;
    }
}

/**This function sets to 0 the pin selected at selected port*/
void GPIO_clear_pin (gpio_port_name_t port_name, uint8_t pin)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      GPIOA->PCOR |= 1 << pin;
      break;
    case GPIO_B:/** GPIO B is selected*/
      GPIOB->PCOR |= 1 << pin;
      break;
    case GPIO_C:/** GPIO C is selected*/
      GPIOC->PCOR |= 1 << pin;
      break;
    case GPIO_D:/** GPIO D is selected*/
      GPIOD->PCOR |= 1 << pin;
      break;
    case GPIO_E: /** GPIO E is selected*/
      GPIOE->PCOR |= 1 << pin;
    default:/**If doesn't exist the option*/
      return;
      break;
    }
}

/**This function toggles the pin selected at selected port*/
void GPIO_toogle_pin (gpio_port_name_t port_name, uint8_t pin)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      GPIOA->PTOR |= 1 << pin;
      break;
    case GPIO_B:/** GPIO B is selected*/
      GPIOB->PTOR |= 1 << pin;
      break;
    case GPIO_C:/** GPIO C is selected*/
      GPIOC->PTOR |= 1 << pin;
      break;
    case GPIO_D:/** GPIO D is selected*/
      GPIOD->PTOR |= 1 << pin;
      break;
    case GPIO_E: /** GPIO E is selected*/
      GPIOE->PTOR |= 1 << pin;
    default:/**If doesn't exist the option*/
      return;
      break;
    }
}

/**This function sets the direction of the port selected*/
void GPIO_data_direction_port (gpio_port_name_t port_name, uint32_t direction)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      GPIOA->PDDR = direction;
      break;
    case GPIO_B:/** GPIO B is selected*/
      GPIOB->PDDR = direction;
      break;
    case GPIO_C:/** GPIO C is selected*/
      GPIOC->PDDR = direction;
      break;
    case GPIO_D:/** GPIO D is selected*/
      GPIOD->PDDR = direction;
      break;
    case GPIO_E: /** GPIO E is selected*/
      GPIOE->PDDR = direction;
    default:/**If doesn't exist the option*/
      return;
      break;
    }
}

/**This function sets the direction of the pin's port selected*/
void GPIO_data_direction_pin (gpio_port_name_t port_name, uint8_t state,
			      uint8_t pin)
{
  switch (port_name)
    {
    case GPIO_A:/** GPIO A is selected*/
      GPIOA->PDDR |= state << pin;
      break;
    case GPIO_B:/** GPIO B is selected*/
      GPIOB->PDDR |= state << pin;
      break;
    case GPIO_C:/** GPIO C is selected*/
      GPIOC->PDDR |= state << pin;
      break;
    case GPIO_D:/** GPIO D is selected*/
      GPIOD->PDDR |= state << pin;
      break;
    case GPIO_E: /** GPIO E is selected*/
      GPIOE->PDDR |= state << pin;
    default:/**If doesn't exist the option*/
      return;
      break;
    }
}

void GPIO_configure_switches(void)
{
	gpio_pin_control_register_t input_intr_config = GPIO_MUX1|GPIO_PE|GPIO_PS|INTR_FALLING_EDGE;

	GPIO_clock_gating (SW3_PORT);
	GPIO_clock_gating (SW2_PORT);

	GPIO_pin_control_register(SW3_PORT, SW3_PIN, &input_intr_config);
	GPIO_pin_control_register(SW2_PORT, SW2_PIN, &input_intr_config);

	//Configure SW3 and SW2 GPIOs as inputs
	GPIO_data_direction_pin (SW3_PORT, GPIO_INPUT, SW3_PIN);
	GPIO_data_direction_pin (SW2_PORT, GPIO_INPUT, SW2_PIN);
}

void GPIO_callback_init(gpio_port_name_t port_name,void (*handler)(void))
{
	if(GPIO_A == port_name)
	{
		gpio_A_callback = handler;
	}
	else
	{
		gpio_C_callback = handler;
	}
}

