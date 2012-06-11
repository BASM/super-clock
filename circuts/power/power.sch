EESchema Schematic File Version 2  date Пнд 11 Июн 2012 21:15:50
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:myreguls
LIBS:power-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "11 jun 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 7805_123 U1
U 1 1 00000000
P 4650 3500
F 0 "U1" H 4800 3304 60  0000 C CNN
F 1 "7805_123" H 4650 3700 60  0000 C CNN
	1    4650 3500
	1    0    0    -1  
$EndComp
Connection ~ 4650 4050
Wire Wire Line
	5050 3650 5050 3450
Wire Wire Line
	5550 3650 5550 3850
Wire Wire Line
	4250 4050 5050 4050
Wire Wire Line
	4250 3650 4250 3450
Wire Wire Line
	4250 3450 3750 3450
Wire Wire Line
	3750 3650 3750 3850
Wire Wire Line
	4650 3750 4650 4150
Wire Wire Line
	5050 3450 5550 3450
$Comp
L GND #PWR01
U 1 1 4FD61F8E
P 4650 4150
F 0 "#PWR01" H 4650 4150 30  0001 C CNN
F 1 "GND" H 4650 4080 30  0001 C CNN
	1    4650 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 4FD61F81
P 3750 3850
F 0 "#PWR02" H 3750 3850 30  0001 C CNN
F 1 "GND" H 3750 3780 30  0001 C CNN
	1    3750 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 4FD62158
P 5550 3850
F 0 "#PWR03" H 5550 3850 30  0001 C CNN
F 1 "GND" H 5550 3780 30  0001 C CNN
	1    5550 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P2
U 1 1 4FD61F6E
P 5900 3550
F 0 "P2" V 5850 3550 40  0000 C CNN
F 1 "CONN_2" V 5950 3550 40  0000 C CNN
	1    5900 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 4FD62159
P 3400 3550
F 0 "P1" V 3350 3550 40  0000 C CNN
F 1 "CONN_2" V 3450 3550 40  0000 C CNN
	1    3400 3550
	-1   0    0    1   
$EndComp
$Comp
L C C2
U 1 1 4FD61EE4
P 5050 3850
F 0 "C2" H 5100 3950 50  0000 L CNN
F 1 "0.1" H 5100 3750 50  0000 L CNN
	1    5050 3850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4FD6215A
P 4250 3850
F 0 "C1" H 4300 3950 50  0000 L CNN
F 1 "0.33" H 4300 3750 50  0000 L CNN
	1    4250 3850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
