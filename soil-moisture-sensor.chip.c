#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Structure to hold chip state
typedef struct {
  pin_t pin;           // Analog output pin
  float moisture;      // Moisture attribute value (simulated)
} chip_data_t;

/// @brief Timer callback that updates analog output based on moisture level
void chip_timer_callback(void *data) 
{
  chip_data_t *chip_data = (chip_data_t*)data;
  
  // Read the current moisture attribute value
  float moisture = attr_read(chip_data->moisture);

  // Convert the moisture value (0-4096) to voltage (0-5V)
  float volts = 5 * (moisture / 4096.0);

  // Write the voltage to the analog output pin
  pin_dac_write(chip_data->pin, volts);
}

/// @brief Initializes the chip: sets up attributes, pin, and timer
void chip_init() 
{
  // Allocate memory for chip state
  chip_data_t *chip_data = (chip_data_t*)malloc(sizeof(chip_data_t));

  // Initialize the "moisture" control attribute with a default value
  chip_data->moisture = attr_init("moisture", 2910.0);

  // Initialize analog output pin
  chip_data->pin = pin_init("A0", ANALOG);

  // Set up a repeating timer to periodically update the analog output
  const timer_config_t config = 
  {
    .callback = chip_timer_callback,
    .user_data = chip_data,
  };

  timer_t timer_id = timer_init(&config);
  timer_start(timer_id, 1000, true); // Run every 1000ms
}
