### SPI driver

##### What is SPI ?

```
spi or Serial Peripheral Interface is communication protocol what does that mean ?
let's say you have MCU and heat sensor and you want to read some data from the sensor
you are not going to just plug it to the MCU and magiclay data will be available
sensor and MCU need to agree on how to send and read here come's spi to solve the problem
```

##### How ?

```
we could connect MCU to sensor with wire and sensor will send for example 5v means 1
0v means 0
```

![](./pics/spi_protocol_construct.png)

````
but you may see a problem here let's say heat sensor send data at rate of 10 values per second
and MCU read at rate of 20 values per
````

![](./pics/spi_timing_problem.jpg)

```
this problem solved by adding wire (clock) to sync between sensor and MCU
```

![](./pics/spi_clock.png)

```
and we need to add other wire so we can read and write
and usually we need to talk to more than one sensor so 
we will add other wire to select which sensor that MCU
is talking to
```

![](./pics/spi_theory_done.png)


#### Notes:

```
Clock polarity determines the state of the clock line when idle.
CPOL=0 Idle Low
CPOL=1 Idle High
```

````
The clock phase determines the clock edge on which the data will start
being sampled by the devices
CPHA=0: First clock edge
CPHA=1: Second clock edge
````

#### Info

![](./pics/board_pinout.png)

```
I have stm32f446ret and it has multiple spi pins

I will choose spi1 for now

- spi1_miso: PA6 or PB4
- spi1_mosi: PA7 or PB5
- spi1_sck: PA5 or PB3
- spi1_nss: PA4 or PA15

```

##### Block Diagram

![](./pics/block_diagram.png)

````
spi1 location well as you can see that spi1 is connected to APB2 and APB2 is connected
to AHB/APB bridge that in iteself connected to AHB1
AHB1 is connected to a clock that needs to be enabled
````

![](./pics/block_diagram_spi1.png)
![](./pics/why_enable_clocks.png)

##### development process

enable ahb1 clock for GPIOA

![](./pics/enable_gpio_clock.png)

enable apb2 aka spi1 clock

![](./pics/enable_apb2_spi_clock.png)
![](./pics/enable_apb2_spi_clock_set.png)


*info about GPIOA*

![](./pics/set_gpioa.png)
![](./pics/set_gpioa_moder.png)

```

it should be cleared first and set to alternate function

```
![](./pics/clear_gpioa_moder.png)

##### *What is alternate function*

```
- general purpose I/O pins are used for any general-purpose input or output use.
this could include usingi any pin as an input for a switch or using a pin an
output for an LED

- when a GPIO pin is used for any alternate purpose (SPI, USART,...) other than as a general purpose
then it is said to be in alternate function mode
```

```
pins are set to alternate function the question now which alternate function
that we need to preforem SPI or I2c for example

pins i will use are P4-P7 so we need the low register of GPIO alternate function
```

![](./pics/alternate_low_register.png)

```
the question now what value we should put AF0? AF1? ...AF15?
well we can get that data from datasheet from the pic below you can see
that AF5 is representing SPI1
```

![](./pics/alternate_function_map.png)

````
from info above we need to fill as the picture
````

![](./pics/alternate_function_set.png)


#### Configure the Actual SPI

````
unitl this point we just told the pins that we are going to use SPI
SPI boundary address
````

![](./pics/spi_boundary_address.png)

````
since we are using P4-P7 we will need spi register control 1
````

![](./pics/spi_cr1.png)


````
BIDMODE: determines whether the SPI will function as full duplex or half duplex
	* my spi driver will be full-duplex so i need to set bit 15 to 0

BIDIO: sets the direction of data transfer if we set to use half-duplex in this case we are not

CRCEN: configure cyclic redundcy check which i will not cover

CRCNEXT is related so ignore them also

DFF: dasta frame format	set it to 0 to indicate 8-bit data frame

RXONLY: receive only mode enabled set it to 0 for full duplex

SSM: `(Software slave management) bit 9 determines how the slave select pin
	is controlled there are two ways to manage the slave selec pin through hardware or
	through software
	when this bit is 0 SS is managed by hardware 1 managed by software`
LSBFIRST: frame format i will set to 0 for now i do not know what sensor i will use
		this may change later

SPE: SPI enable set it to 1

BR[2:0]: buad rate control i do not what sensor i will use i will choose randomly now
		 i will use 101 or Fpclk/64
MSTR: master selection should be 1

CPOL: 0
CPHA: 0


````

### Random info (this is just me reading more about spi of stm32)

```
**The STM32 SPI offers various operating modes**

- the communication speed can't exceed half of the internal bus frequency
- minimum of two wires is required to provide the serial data flow synchornized by clock signal in single direction
- an optional hardware slave select control signal can be added
- the data size andd transmit shift order are configurable
- clock signal polarity and phase also configurable
- polarity and timing adjustment of the slave select signal

- an spi data frame is defined by the SS signal, and no start or stop bits are used
	like other protocols (so every SCLK transfers a data bit)
	the master must drive the SS signal to a given slave in order to intiate a read
	or write After SS is asserted (typically low) eight or more clock transitions can
	be asserted depending on the number of bits that must be transferred
	Most SPI devices use units of 8-bits but any data size can be used
	in some devices SS assertion not only initiates a data frame, but also enables
	the device to a preform function for example some analog to digital converters use transition on SS to start a conversion
```
