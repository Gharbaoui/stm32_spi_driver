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
````
