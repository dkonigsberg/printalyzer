EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "Printalyzer - Meter Probe"
Date ""
Rev "?"
Comp "LogicProbe.org"
Comment1 "Derek Konigsberg"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Project:RT9193 U?
U 1 1 5F8A0F5B
P 4200 3650
F 0 "U?" H 4200 3992 50  0000 C CNN
F 1 "RT9193" H 4200 3901 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 4200 3950 50  0001 C CIN
F 3 "https://www.richtek.com/assets/product_file/RT9193/DS9193-17.pdf" H 4200 3650 50  0001 C CNN
	1    4200 3650
	1    0    0    -1  
$EndComp
$Comp
L Project:TCS3472 U?
U 1 1 5F8A152C
P 1700 1850
F 0 "U?" H 1256 1771 50  0000 R CNN
F 1 "TCS3472" H 1256 1680 50  0000 R CNN
F 2 "lib_fp:AMS_TCS3472_DFN-6" H 1700 1350 50  0001 C CNN
F 3 "https://ams.com/documents/20143/36005/TCS3472_DS000390_3-00.pdf" H 2450 2150 50  0001 C CNN
	1    1700 1850
	1    0    0    -1  
$EndComp
$Comp
L Marquadt_Switch:SW_Key_6425_0101 SW?
U 1 1 5F8A2A8F
P 1650 3850
F 0 "SW?" H 1650 4135 50  0000 C CNN
F 1 "Sensor Button" H 1650 4044 50  0000 C CNN
F 2 "lib_fp:SW_Key_6425_0101" H 1650 4050 50  0001 C CNN
F 3 "https://www.marquardt-switches.com/PLM-uploads/kzeichnung/64250101_00_K.pdf" H 1650 4050 50  0001 C CNN
	1    1650 3850
	1    0    0    -1  
$EndComp
$Comp
L Interface_Expansion:P82B96 U?
U 1 1 5F8A31B7
P 3600 1950
F 0 "U?" H 3600 2567 50  0000 C CNN
F 1 "P82B96" H 3600 2476 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3600 1950 50  0001 C CNN
F 3 "http://www.nxp.com/documents/data_sheet/P82B96.pdf" H 3600 1950 50  0001 C CNN
	1    3600 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F8B85F3
P 3500 3700
F 0 "C?" H 3615 3746 50  0000 L CNN
F 1 "1uF" H 3615 3655 50  0000 L CNN
F 2 "" H 3538 3550 50  0001 C CNN
F 3 "~" H 3500 3700 50  0001 C CNN
	1    3500 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F8B8FD8
P 5100 3700
F 0 "C?" H 5215 3746 50  0000 L CNN
F 1 "1uF" H 5215 3655 50  0000 L CNN
F 2 "" H 5138 3550 50  0001 C CNN
F 3 "~" H 5100 3700 50  0001 C CNN
	1    5100 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5F8B9A07
P 4700 3900
F 0 "C?" H 4815 3946 50  0000 L CNN
F 1 "22nF" H 4815 3855 50  0000 L CNN
F 2 "" H 4738 3750 50  0001 C CNN
F 3 "~" H 4700 3900 50  0001 C CNN
	1    4700 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 3650 4700 3650
Wire Wire Line
	4700 3650 4700 3750
Wire Wire Line
	3800 3550 3500 3550
Wire Wire Line
	3800 3650 3800 3550
Connection ~ 3800 3550
Wire Wire Line
	4600 3550 5100 3550
$Comp
L power:GND #PWR?
U 1 1 5F8BE462
P 4700 4050
F 0 "#PWR?" H 4700 3800 50  0001 C CNN
F 1 "GND" H 4705 3877 50  0000 C CNN
F 2 "" H 4700 4050 50  0001 C CNN
F 3 "" H 4700 4050 50  0001 C CNN
	1    4700 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8BEDF3
P 5100 3850
F 0 "#PWR?" H 5100 3600 50  0001 C CNN
F 1 "GND" H 5105 3677 50  0000 C CNN
F 2 "" H 5100 3850 50  0001 C CNN
F 3 "" H 5100 3850 50  0001 C CNN
	1    5100 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8BF4E8
P 3500 3850
F 0 "#PWR?" H 3500 3600 50  0001 C CNN
F 1 "GND" H 3505 3677 50  0000 C CNN
F 2 "" H 3500 3850 50  0001 C CNN
F 3 "" H 3500 3850 50  0001 C CNN
	1    3500 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8C1BAD
P 4200 3950
F 0 "#PWR?" H 4200 3700 50  0001 C CNN
F 1 "GND" H 4205 3777 50  0000 C CNN
F 2 "" H 4200 3950 50  0001 C CNN
F 3 "" H 4200 3950 50  0001 C CNN
	1    4200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F8C2B7F
P 5100 3450
F 0 "#PWR?" H 5100 3300 50  0001 C CNN
F 1 "+3.3V" H 5115 3623 50  0000 C CNN
F 2 "" H 5100 3450 50  0001 C CNN
F 3 "" H 5100 3450 50  0001 C CNN
	1    5100 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F8C33B0
P 3800 3450
F 0 "#PWR?" H 3800 3300 50  0001 C CNN
F 1 "+5V" H 3815 3623 50  0000 C CNN
F 2 "" H 3800 3450 50  0001 C CNN
F 3 "" H 3800 3450 50  0001 C CNN
	1    3800 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3450 5100 3550
Connection ~ 5100 3550
Wire Wire Line
	3800 3450 3800 3550
Wire Wire Line
	4200 2050 4200 2250
Wire Wire Line
	4200 1650 4200 1850
$Comp
L power:+5V #PWR?
U 1 1 5F8C56D1
P 3000 1350
F 0 "#PWR?" H 3000 1200 50  0001 C CNN
F 1 "+5V" H 3015 1523 50  0000 C CNN
F 2 "" H 3000 1350 50  0001 C CNN
F 3 "" H 3000 1350 50  0001 C CNN
	1    3000 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8C593E
P 2900 2350
F 0 "#PWR?" H 2900 2100 50  0001 C CNN
F 1 "GND" H 2905 2177 50  0000 C CNN
F 2 "" H 2900 2350 50  0001 C CNN
F 3 "" H 2900 2350 50  0001 C CNN
	1    2900 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2250 2900 2250
Wire Wire Line
	2900 2250 2900 2350
$Comp
L Device:C C?
U 1 1 5F8C7475
P 1650 1400
F 0 "C?" V 1398 1400 50  0000 C CNN
F 1 "0.1uF" V 1489 1400 50  0000 C CNN
F 2 "" H 1688 1250 50  0001 C CNN
F 3 "~" H 1650 1400 50  0001 C CNN
	1    1650 1400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8C820C
P 1500 1400
F 0 "#PWR?" H 1500 1150 50  0001 C CNN
F 1 "GND" H 1505 1227 50  0000 C CNN
F 2 "" H 1500 1400 50  0001 C CNN
F 3 "" H 1500 1400 50  0001 C CNN
	1    1500 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5F8C87E4
P 1800 1250
F 0 "#PWR?" H 1800 1100 50  0001 C CNN
F 1 "+3.3V" H 1815 1423 50  0000 C CNN
F 2 "" H 1800 1250 50  0001 C CNN
F 3 "" H 1800 1250 50  0001 C CNN
	1    1800 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8C8F30
P 1800 2500
F 0 "#PWR?" H 1800 2250 50  0001 C CNN
F 1 "GND" H 1805 2327 50  0000 C CNN
F 2 "" H 1800 2500 50  0001 C CNN
F 3 "" H 1800 2500 50  0001 C CNN
	1    1800 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 2400 1800 2500
$Comp
L Connector_Generic:Conn_01x05 J?
U 1 1 5F8CB1BB
P 5150 2050
F 0 "J?" H 5230 2092 50  0000 L CNN
F 1 "Main Board Cable" H 5230 2001 50  0000 L CNN
F 2 "" H 5150 2050 50  0001 C CNN
F 3 "~" H 5150 2050 50  0001 C CNN
	1    5150 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F922946
P 4900 1200
F 0 "#PWR?" H 4900 1050 50  0001 C CNN
F 1 "+5V" H 4915 1373 50  0000 C CNN
F 2 "" H 4900 1200 50  0001 C CNN
F 3 "" H 4900 1200 50  0001 C CNN
	1    4900 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F922E28
P 4900 2300
F 0 "#PWR?" H 4900 2050 50  0001 C CNN
F 1 "GND" H 4905 2127 50  0000 C CNN
F 2 "" H 4900 2300 50  0001 C CNN
F 3 "" H 4900 2300 50  0001 C CNN
	1    4900 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1850 4900 1850
Wire Wire Line
	4950 2250 4900 2250
Wire Wire Line
	4900 2250 4900 2300
Text Label 4850 2150 2    50   ~ 0
BUTTON
Wire Wire Line
	4850 2150 4950 2150
Connection ~ 4200 2050
Wire Wire Line
	4200 1950 4200 1850
Connection ~ 4200 1850
$Comp
L Device:C C?
U 1 1 5F92FB8F
P 2850 1500
F 0 "C?" V 2598 1500 50  0000 C CNN
F 1 "0.1uF" V 2689 1500 50  0000 C CNN
F 2 "" H 2888 1350 50  0001 C CNN
F 3 "~" H 2850 1500 50  0001 C CNN
	1    2850 1500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F93106A
P 2700 1500
F 0 "#PWR?" H 2700 1250 50  0001 C CNN
F 1 "GND" H 2705 1327 50  0000 C CNN
F 2 "" H 2700 1500 50  0001 C CNN
F 3 "" H 2700 1500 50  0001 C CNN
	1    2700 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1850 2450 1850
Wire Wire Line
	2100 1950 2200 1950
Wire Wire Line
	3000 1950 3000 2050
$Comp
L Device:R R?
U 1 1 5F93E71C
P 2450 1600
F 0 "R?" H 2520 1646 50  0000 L CNN
F 1 "R" H 2520 1555 50  0000 L CNN
F 2 "" V 2380 1600 50  0001 C CNN
F 3 "~" H 2450 1600 50  0001 C CNN
	1    2450 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5F93EC8D
P 2200 1600
F 0 "R?" H 2270 1646 50  0000 L CNN
F 1 "R" H 2270 1555 50  0000 L CNN
F 2 "" V 2130 1600 50  0001 C CNN
F 3 "~" H 2200 1600 50  0001 C CNN
	1    2200 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1350 3000 1500
Connection ~ 3000 1500
Wire Wire Line
	3000 1500 3000 1650
Wire Wire Line
	1800 1250 1800 1400
Connection ~ 1800 1400
Wire Wire Line
	1800 1400 1800 1550
Wire Wire Line
	2450 1750 2450 1850
Connection ~ 2450 1850
Wire Wire Line
	2450 1850 3000 1850
Wire Wire Line
	2200 1750 2200 1950
Connection ~ 2200 1950
Wire Wire Line
	2200 1950 3000 1950
Wire Wire Line
	2200 1450 2200 1400
Wire Wire Line
	2200 1400 1800 1400
Wire Wire Line
	2450 1450 2450 1400
Wire Wire Line
	2450 1400 2200 1400
Connection ~ 2200 1400
NoConn ~ 2100 2050
$Comp
L power:GND #PWR?
U 1 1 5F9461F9
P 1350 3950
F 0 "#PWR?" H 1350 3700 50  0001 C CNN
F 1 "GND" H 1355 3777 50  0000 C CNN
F 2 "" H 1350 3950 50  0001 C CNN
F 3 "" H 1350 3950 50  0001 C CNN
	1    1350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 3850 1350 3850
Wire Wire Line
	1350 3850 1350 3950
$Comp
L Device:R R?
U 1 1 5F947252
P 2100 3550
F 0 "R?" H 2170 3596 50  0000 L CNN
F 1 "10K" H 2170 3505 50  0000 L CNN
F 2 "" V 2030 3550 50  0001 C CNN
F 3 "~" H 2100 3550 50  0001 C CNN
	1    2100 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F947727
P 2100 3400
F 0 "#PWR?" H 2100 3250 50  0001 C CNN
F 1 "+5V" H 2115 3573 50  0000 C CNN
F 2 "" H 2100 3400 50  0001 C CNN
F 3 "" H 2100 3400 50  0001 C CNN
	1    2100 3400
	1    0    0    -1  
$EndComp
Text Label 2250 3850 0    50   ~ 0
BUTTON
Wire Wire Line
	1850 3850 2100 3850
Wire Wire Line
	2100 3700 2100 3850
Connection ~ 2100 3850
Wire Wire Line
	2100 3850 2250 3850
Wire Wire Line
	4900 1200 4900 1850
Wire Wire Line
	4200 2050 4950 2050
Wire Wire Line
	4200 1950 4950 1950
$EndSCHEMATC
