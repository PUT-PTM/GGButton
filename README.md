## GGButton

# Overview

Simple .wav player stylized on GGButton created on STM32 microcontroller(STM32F407VG).

# Description

   Usefullnes and simplicity was the main target in creating this project. Music files are stored on SD card
and their number is limited to 8 due to 8 positon winder used in our model. Keep in mind that these files 
need to be named 0.WAV, 1.WAV [...] 7.WAV. SPI is used to comunicate SD module with STM32. 
Handling of our project is pretty straight forward - to play music push main button, to stop it push again. 
Twist winder to change song. To change audio volume, adjust potentiometer.
	
# Demo

// Tu będzie filmik kierowniku

# Tools

*CooCox CoIDE, Version: 1.7.8
*STM Studio

# How to run

1.Hardware needed:
	* STM32f4-DISCOVERY board,
	* SD Card Module and SD Card formatted to FAT32,
	* 1 switch,
	* 1 rotating 8 position swith(alternatively 8 normal swithes),
	* 1 rotary potentiometer,
	* Headphones or loudspeaker with male jack connector.
		
2.Connection instruction
		
	STM32 <---> SD Card Module
	GND   <---> GND
	3V    <---> 3V3
	PB11  <---> CS
	PB15  <---> MOSI
	PB13  <---> SCK
	PB14  <---> MISO
	GND   <---> GND
		
	PE9   <---> Main button
	
	PE1   <---> Rotating swith
	.
	.
	.
	PE9   <---> Rotating swith
		
	PA1   <---> Potentiometer
		 
3.How to run
	
* Download your audio files onto SD card(remember about proper naming).
* Build this project with CooCox CoIDE and Download Code to Flash.
	
# How to compile

* The only step is download the project and compile it with CooCox CoIDE.

# Attributions

- https://github.com/PUT-PTM/STMwavPlayerMR
- https://github.com/PUT-PTM/STMwavPlayer
- http://elm-chan.org/fsw/ff/00index_e.html
- http://stm32.eu/2012/05/09/obsluga-fat-w-mikrokontrolerach-stm32-obsluga-kart/

# License

* MIT

# Credits

* Norbert Wołowiec,		
* Gracjan Rutkowski.


The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Tomasz Mańkowski
