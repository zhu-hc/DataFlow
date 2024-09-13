#include "HAL/HAL.h"

void HAL::UART_Init()
{
  Serial1.setTimeout(CONFIG_UART_TIMEOUT);
  Serial2.setTimeout(CONFIG_UART_TIMEOUT);
  Serial1.begin(115200, SERIAL_8N1, CONFIG_UART_RX_PIN, -1, false, CONFIG_UART_TIMEOUT);
  Serial2.begin(115200, SERIAL_8N1, CONFIG_UART_TX_PIN, -1, false, CONFIG_UART_TIMEOUT);
}

void HAL::UART_SetBaudRate(uint32_t baud)
{
  Serial1.updateBaudRate(baud);
  Serial2.updateBaudRate(baud);
}
