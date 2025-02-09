#ifndef I2C_LINK_CONF_H_
#define I2C_LINK_CONF_H_

#include <stm32f4xx_hal.h>

//! Размер пакета передаваемого/принимаемого за одну транзакцию
#define I2C_LINK_PACKET_SIZE	(279)

//! Количество приёмных буферов (каждый по I2C_LINK_PACKET_SIZE байт)
#define I2C_LINK_RXBUF_COUNT	(5)
//! Размер мусорки для "приёма" лишних байт
/*! В эту мусорку отправляем то, что мастер нам даёт, но что нам некуда принять
	Размер имеет смысл ставить побольше, чтобы ради него было не стыдно запускать DMA */
#define I2C_LINK_RX_DUMP_SIZE	(20)

//! Количество отправных буферов (каждый по I2C_LINK_PACKET_SIZE байт)
#define I2C_LINK_TXBUF_COUNT (5)
//! Размер пачки нулей для отправки вместо пакетов
/*! Массив такого размера инициализируется нулями и циклически отправляется
	в тех случаях, когда мастер чего-то просит, но отправлять нам нечего.
Размер имеет смысл ставить побольше, чтобы ради него было не стыдно запускать DMA */
#define I2C_LINK_TX_ZEROS_SIZE	(20)

extern I2C_HandleTypeDef hi2c1;

//! халовский i2c-handle на котором осуществляется обмен
#define I2C_LINK_BUS_HANDLE (&hi2c1)

#endif /* I2C_LINK_CONF_H_ */
