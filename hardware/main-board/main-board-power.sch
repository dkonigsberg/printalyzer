EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 2 4
Title "Printalyzer - Main Board (Power Supply and Control)"
Date ""
Rev "?"
Comp "LogicProbe.org"
Comment1 "Derek Konigsberg"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Project:Conn_PX0580-PC P1
U 1 1 5F98E141
P 1600 1300
AR Path="/5F98E141" Ref="P1"  Part="1" 
AR Path="/5F8B674D/5F98E141" Ref="P1"  Part="1" 
F 0 "P1" H 1600 1650 50  0000 C CNN
F 1 "Mains Power Input" H 1600 1550 50  0000 C CNN
F 2 "lib_fp:Bulgin_PX0580-PC" H 1600 810 50  0001 C CNN
F 3 "https://www.bulgin.com/products/pub/media/bulgin/data/IEC_connectors.pdf" H 2000 1300 50  0001 C CNN
F 4 "PWR ENT RCPT IEC320-C14 PNL SLDR" H 1600 1300 50  0001 C CNN "Description"
F 5 "Bulgin" H 1600 1300 50  0001 C CNN "Manufacturer"
F 6 "PX0580/PC" H 1600 1300 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 1600 1300 50  0001 C CNN "Supplier"
F 8 "708-1341-ND" H 1600 1300 50  0001 C CNN "Supplier PN"
	1    1600 1300
	1    0    0    -1  
$EndComp
$Comp
L Project:Conn_PX0675-PC P2
U 1 1 5F98F474
P 8050 1350
AR Path="/5F98F474" Ref="P2"  Part="1" 
AR Path="/5F8B674D/5F98F474" Ref="P2"  Part="1" 
F 0 "P2" H 8050 1700 50  0000 C CNN
F 1 "Enlarger Power Output" H 8050 1600 50  0000 C CNN
F 2 "lib_fp:Bulgin_PX0580-PC" H 8050 860 50  0001 C CNN
F 3 "https://www.bulgin.com/products/pub/media/bulgin/data/IEC_connectors.pdf" H 8450 1350 50  0001 C CNN
F 4 "PWR ENT RCPT IEC320-2-2F PANEL" H 8050 1350 50  0001 C CNN "Description"
F 5 "Bulgin" H 8050 1350 50  0001 C CNN "Manufacturer"
F 6 "PX0675/PC" H 8050 1350 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 8050 1350 50  0001 C CNN "Supplier"
F 8 "708-1351-ND" H 8050 1350 50  0001 C CNN "Supplier PN"
	1    8050 1350
	1    0    0    -1  
$EndComp
$Comp
L Project:Conn_PX0675-PC P3
U 1 1 5F98FD81
P 8050 2350
AR Path="/5F98FD81" Ref="P3"  Part="1" 
AR Path="/5F8B674D/5F98FD81" Ref="P3"  Part="1" 
F 0 "P3" H 8050 2700 50  0000 C CNN
F 1 "Safelight Power Output" H 8050 2600 50  0000 C CNN
F 2 "lib_fp:Bulgin_PX0580-PC" H 8050 1860 50  0001 C CNN
F 3 "https://www.bulgin.com/products/pub/media/bulgin/data/IEC_connectors.pdf" H 8450 2350 50  0001 C CNN
F 4 "PWR ENT RCPT IEC320-2-2F PANEL" H 8050 2350 50  0001 C CNN "Description"
F 5 "Bulgin" H 8050 2350 50  0001 C CNN "Manufacturer"
F 6 "PX0675/PC" H 8050 2350 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 8050 2350 50  0001 C CNN "Supplier"
F 8 "708-1351-ND" H 8050 2350 50  0001 C CNN "Supplier PN"
	1    8050 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:Fuse F1
U 1 1 5F99293E
P 2150 2200
F 0 "F1" V 2350 2150 50  0000 L CNN
F 1 "Main Fuse" V 2250 2000 50  0000 L CNN
F 2 "Fuse:Fuseholder_Cylinder-5x20mm_Bulgin_FX0457_Horizontal_Closed" V 2080 2200 50  0001 C CNN
F 3 "https://www.bulgin.com/products/pub/media/bulgin/data/Fuseholders.pdf" H 2150 2200 50  0001 C CNN
F 4 "FUSE HLDR CARTRIDGE 250V 10A PCB" H 2150 2200 50  0001 C CNN "Description"
F 5 "Bulgin" H 2150 2200 50  0001 C CNN "Manufacturer"
F 6 "FX0457" H 2150 2200 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 2150 2200 50  0001 C CNN "Supplier"
F 8 "708-1898-ND" H 2150 2200 50  0001 C CNN "Supplier PN"
	1    2150 2200
	0    -1   -1   0   
$EndComp
$Comp
L Device:Fuse F2
U 1 1 5F992D5F
P 2450 2550
F 0 "F2" H 2510 2596 50  0000 L CNN
F 1 "Internal Fuse" H 2510 2505 50  0000 L CNN
F 2 "Fuse:Fuseholder_Cylinder-5x20mm_Schurter_0031_8201_Horizontal_Open" V 2380 2550 50  0001 C CNN
F 3 "http://www.schurterinc.com/bundles/snceschurter/epim/_ProdPool_/newDS/en/typ_OGN.pdf" H 2450 2550 50  0001 C CNN
F 4 "FUSE BLOK CARTRIDGE 500V 10A PCB" H 2450 2550 50  0001 C CNN "Description"
F 5 "Schurter Inc." H 2450 2550 50  0001 C CNN "Manufacturer"
F 6 "0031.8201" H 2450 2550 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 2450 2550 50  0001 C CNN "Supplier"
F 8 "486-1258-ND" H 2450 2550 50  0001 C CNN "Supplier PN"
	1    2450 2550
	-1   0    0    1   
$EndComp
$Comp
L Project:G2RL-1A4-DC12 K1
U 1 1 5F996900
P 6500 1400
F 0 "K1" H 6830 1446 50  0000 L CNN
F 1 "Enlarger Relay" H 6100 1050 50  0000 L CNN
F 2 "lib_fp:Relay_SPST_Omron_G2RL-1A" H 6850 1350 50  0001 L CNN
F 3 "https://omronfs.omron.com/en_US/ecb/products/pdf/en-g2rl.pdf" H 6500 1400 50  0001 C CNN
F 4 "RELAY GEN PURPOSE SPST 12A 12V" H 6500 1400 50  0001 C CNN "Description"
F 5 "Omron" H 6500 1400 50  0001 C CNN "Manufacturer"
F 6 "G2RL-1A4 DC12" H 6500 1400 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 6500 1400 50  0001 C CNN "Supplier"
F 8 "Z2923-ND" H 6500 1400 50  0001 C CNN "Supplier PN"
	1    6500 1400
	1    0    0    -1  
$EndComp
$Comp
L Project:G2RL-1A4-DC12 K2
U 1 1 5F996F15
P 6850 2350
F 0 "K2" H 7180 2396 50  0000 L CNN
F 1 "Safelight Relay" H 6450 2000 50  0000 L CNN
F 2 "lib_fp:Relay_SPST_Omron_G2RL-1A" H 7200 2300 50  0001 L CNN
F 3 "https://omronfs.omron.com/en_US/ecb/products/pdf/en-g2rl.pdf" H 6850 2350 50  0001 C CNN
F 4 "RELAY GEN PURPOSE SPST 12A 12V" H 6850 2350 50  0001 C CNN "Description"
F 5 "Omron" H 6850 2350 50  0001 C CNN "Manufacturer"
F 6 "G2RL-1A4 DC12" H 6850 2350 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 6850 2350 50  0001 C CNN "Supplier"
F 8 "Z2923-ND" H 6850 2350 50  0001 C CNN "Supplier PN"
	1    6850 2350
	1    0    0    -1  
$EndComp
$Comp
L Project:NUD3112DMT1G U?
U 1 1 5F99946F
P 5550 2000
F 0 "U?" H 5550 2450 50  0000 C CNN
F 1 "NUD3112DMT1G" H 5550 1550 50  0000 C CNN
F 2 "Package_SO:SC-74-6_1.5x2.9mm_P0.95mm" H 4750 1400 50  0001 L CNN
F 3 "http://www.onsemi.com/pub/Collateral/NUD3112-D.PDF" H 5550 1900 50  0001 C CNN
F 4 "IC PWR DRIVER N-CHANNEL 1:1 SC74" H 5550 2000 50  0001 C CNN "Description"
F 5 "ON Semiconductor" H 5550 2000 50  0001 C CNN "Manufacturer"
F 6 "NUD3112DMT1G" H 5550 2000 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 5550 2000 50  0001 C CNN "Supplier"
F 8 "NUD3112DMT1GOSCT-ND" H 5550 2000 50  0001 C CNN "Supplier PN"
	1    5550 2000
	1    0    0    -1  
$EndComp
$Comp
L Project:PSK-6B-S12 PS?
U 1 1 5F98EA9A
P 3000 2950
F 0 "PS?" H 3000 3317 50  0000 C CNN
F 1 "PSK-6B-S12" H 3000 3226 50  0000 C CNN
F 2 "lib_fp:Converter_ACDC_CUI_PSK-6B" H 3000 2600 50  0001 C CNN
F 3 "https://www.cui.com/product/resource/psk-6b.pdf" H 3000 2550 50  0001 C CNN
F 4 "AC/DC CONVERTER 12V 6W" H 3000 2950 50  0001 C CNN "Description"
F 5 "CUI Inc." H 3000 2950 50  0001 C CNN "Manufacturer"
F 6 "PSK-6B-S12" H 3000 2950 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 3000 2950 50  0001 C CNN "Supplier"
F 8 "102-4151-ND" H 3000 2950 50  0001 C CNN "Supplier PN"
	1    3000 2950
	1    0    0    -1  
$EndComp
Text HLabel 4900 1800 0    50   Input ~ 0
RELAY_ENLARGER
Text HLabel 4900 2200 0    50   Input ~ 0
RELAY_SAFELIGHT
$Comp
L power:+12V #PWR?
U 1 1 5F9D7202
P 6300 1100
F 0 "#PWR?" H 6300 950 50  0001 C CNN
F 1 "+12V" H 6315 1273 50  0000 C CNN
F 2 "" H 6300 1100 50  0001 C CNN
F 3 "" H 6300 1100 50  0001 C CNN
	1    6300 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 5F9D78AE
P 6650 2050
F 0 "#PWR?" H 6650 1900 50  0001 C CNN
F 1 "+12V" H 6665 2223 50  0000 C CNN
F 2 "" H 6650 2050 50  0001 C CNN
F 3 "" H 6650 2050 50  0001 C CNN
	1    6650 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F9D8E8D
P 6300 1900
F 0 "#PWR?" H 6300 1650 50  0001 C CNN
F 1 "GND" H 6305 1727 50  0000 C CNN
F 2 "" H 6300 1900 50  0001 C CNN
F 3 "" H 6300 1900 50  0001 C CNN
	1    6300 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1700 6300 1700
Wire Wire Line
	6000 1900 6300 1900
Wire Wire Line
	6000 2100 6200 2100
Wire Wire Line
	6200 2100 6200 2650
Wire Wire Line
	6200 2650 6650 2650
$Comp
L power:GND #PWR?
U 1 1 5F9DE431
P 6050 2350
F 0 "#PWR?" H 6050 2100 50  0001 C CNN
F 1 "GND" H 6055 2177 50  0000 C CNN
F 2 "" H 6050 2350 50  0001 C CNN
F 3 "" H 6050 2350 50  0001 C CNN
	1    6050 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 2300 6050 2300
Wire Wire Line
	6050 2300 6050 2350
Wire Wire Line
	5100 1800 4900 1800
Wire Wire Line
	5100 2200 4900 2200
$Comp
L Regulator_Switching:R-78E3.3-0.5 U?
U 1 1 5F9E5987
P 2600 4000
F 0 "U?" H 2600 4242 50  0000 C CNN
F 1 "R-78E3.3-0.5" H 2600 4151 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_RECOM_R-78E-0.5_THT" H 2650 3750 50  0001 L CIN
F 3 "https://www.recom-power.com/pdf/Innoline/R-78Exx-0.5.pdf" H 2600 4000 50  0001 C CNN
F 4 "DC DC CONVERTER 3.3V 2W" H 2600 4000 50  0001 C CNN "Description"
F 5 "Recom Power" H 2600 4000 50  0001 C CNN "Manufacturer"
F 6 "R-78E3.3-0.5" H 2600 4000 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 2600 4000 50  0001 C CNN "Supplier"
F 8 "945-1661-5-ND" H 2600 4000 50  0001 C CNN "Supplier PN"
	1    2600 4000
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Switching:R-78E5.0-0.5 U?
U 1 1 5F9E6E96
P 2600 5000
F 0 "U?" H 2600 5242 50  0000 C CNN
F 1 "R-78E5.0-0.5" H 2600 5151 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_RECOM_R-78E-0.5_THT" H 2650 4750 50  0001 L CIN
F 3 "https://www.recom-power.com/pdf/Innoline/R-78Exx-0.5.pdf" H 2600 5000 50  0001 C CNN
F 4 "DC DC CONVERTER 5V 3W" H 2600 5000 50  0001 C CNN "Description"
F 5 "Recom Power" H 2600 5000 50  0001 C CNN "Manufacturer"
F 6 "R-78E5.0-0.5" H 2600 5000 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 2600 5000 50  0001 C CNN "Supplier"
F 8 "945-1648-5-ND" H 2600 5000 50  0001 C CNN "Supplier PN"
	1    2600 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F9EA7AC
P 2050 4150
F 0 "C?" H 2142 4196 50  0000 L CNN
F 1 "4.7uF" H 2142 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2050 4150 50  0001 C CNN
F 3 "https://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM21BC71H475KE11-01.pdf" H 2050 4150 50  0001 C CNN
F 4 "CAP CER 4.7UF 50V X7S 0805" H 2050 4150 50  0001 C CNN "Description"
F 5 "Murata Electronics" H 2050 4150 50  0001 C CNN "Manufacturer"
F 6 "GRM21BC71H475KE11L" H 2050 4150 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 2050 4150 50  0001 C CNN "Supplier"
F 8 "490-12757-1-ND" H 2050 4150 50  0001 C CNN "Supplier PN"
	1    2050 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F9EB67B
P 3100 4150
F 0 "C?" H 3192 4196 50  0000 L CNN
F 1 "10uF" H 3192 4105 50  0000 L CNN
F 2 "" H 3100 4150 50  0001 C CNN
F 3 "~" H 3100 4150 50  0001 C CNN
	1    3100 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F9EDFC4
P 3100 5150
F 0 "C?" H 3192 5196 50  0000 L CNN
F 1 "10uF" H 3192 5105 50  0000 L CNN
F 2 "" H 3100 5150 50  0001 C CNN
F 3 "~" H 3100 5150 50  0001 C CNN
	1    3100 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4300 3100 4300
Wire Wire Line
	3100 4300 3100 4250
Wire Wire Line
	2600 5300 3100 5300
Wire Wire Line
	3100 5300 3100 5250
Wire Wire Line
	2900 5000 3100 5000
Wire Wire Line
	3100 5000 3100 5050
Wire Wire Line
	2900 4000 3100 4000
Wire Wire Line
	3100 4000 3100 4050
$Comp
L power:GND #PWR?
U 1 1 5F9F14E3
P 3450 4300
F 0 "#PWR?" H 3450 4050 50  0001 C CNN
F 1 "GND" H 3455 4127 50  0000 C CNN
F 2 "" H 3450 4300 50  0001 C CNN
F 3 "" H 3450 4300 50  0001 C CNN
	1    3450 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F9F1BF5
P 3450 5300
F 0 "#PWR?" H 3450 5050 50  0001 C CNN
F 1 "GND" H 3455 5127 50  0000 C CNN
F 2 "" H 3450 5300 50  0001 C CNN
F 3 "" H 3450 5300 50  0001 C CNN
	1    3450 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 5300 3450 5300
Connection ~ 3100 5300
Wire Wire Line
	3100 4300 3450 4300
Connection ~ 3100 4300
$Comp
L power:+3.3V #PWR?
U 1 1 5F9F31BD
P 3450 4000
F 0 "#PWR?" H 3450 3850 50  0001 C CNN
F 1 "+3.3V" H 3465 4173 50  0000 C CNN
F 2 "" H 3450 4000 50  0001 C CNN
F 3 "" H 3450 4000 50  0001 C CNN
	1    3450 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5F9F405B
P 3450 5000
F 0 "#PWR?" H 3450 4850 50  0001 C CNN
F 1 "+5V" H 3465 5173 50  0000 C CNN
F 2 "" H 3450 5000 50  0001 C CNN
F 3 "" H 3450 5000 50  0001 C CNN
	1    3450 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 5000 3450 5000
Connection ~ 3100 5000
Wire Wire Line
	3100 4000 3450 4000
Connection ~ 3100 4000
$Comp
L power:+12V #PWR?
U 1 1 5F9F546C
P 1500 4000
F 0 "#PWR?" H 1500 3850 50  0001 C CNN
F 1 "+12V" H 1515 4173 50  0000 C CNN
F 2 "" H 1500 4000 50  0001 C CNN
F 3 "" H 1500 4000 50  0001 C CNN
	1    1500 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F9F6ADE
P 1500 4300
F 0 "#PWR?" H 1500 4050 50  0001 C CNN
F 1 "GND" H 1505 4127 50  0000 C CNN
F 2 "" H 1500 4300 50  0001 C CNN
F 3 "" H 1500 4300 50  0001 C CNN
	1    1500 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5F9FC449
P 1650 4150
F 0 "C?" H 1742 4196 50  0000 L CNN
F 1 "10uF" H 1742 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 1650 4150 50  0001 C CNN
F 3 "https://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM32EC72A106KE05-01.pdf" H 1650 4150 50  0001 C CNN
F 4 "CAP CER 10UF 100V X7S 1210" H 1650 4150 50  0001 C CNN "Description"
F 5 "Murata Electronics" H 1650 4150 50  0001 C CNN "Manufacturer"
F 6 "GRM32EC72A106KE05L" H 1650 4150 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 1650 4150 50  0001 C CNN "Supplier"
F 8 "490-16266-1-ND" H 1650 4150 50  0001 C CNN "Supplier PN"
	1    1650 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:L L?
U 1 1 5F9FE48E
P 1850 4000
F 0 "L?" V 2040 4000 50  0000 C CNN
F 1 "12uH" V 1949 4000 50  0000 C CNN
F 2 "" H 1850 4000 50  0001 C CNN
F 3 "https://recom-power.com/pdf/Accessories/RLS-126.pdf" H 1850 4000 50  0001 C CNN
F 4 "FIXED IND 12UH 800MA 420MOHM SMD" H 1850 4000 50  0001 C CNN "Description"
F 5 "Recom Power" H 1850 4000 50  0001 C CNN "Manufacturer"
F 6 "RLS-126" H 1850 4000 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 1850 4000 50  0001 C CNN "Supplier"
F 8 "945-3429-ND" H 1850 4000 50  0001 C CNN "Supplier PN"
	1    1850 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 4000 2050 4000
Wire Wire Line
	2050 4050 2050 4000
Connection ~ 2050 4000
Wire Wire Line
	2050 4000 2300 4000
Wire Wire Line
	1700 4000 1650 4000
Wire Wire Line
	1650 4050 1650 4000
Connection ~ 1650 4000
Wire Wire Line
	1650 4000 1500 4000
Wire Wire Line
	2600 4300 2050 4300
Connection ~ 2600 4300
Wire Wire Line
	1650 4250 1650 4300
Connection ~ 1650 4300
Wire Wire Line
	1650 4300 1500 4300
Wire Wire Line
	2050 4250 2050 4300
Connection ~ 2050 4300
Wire Wire Line
	2050 4300 1650 4300
Text Notes 1550 5750 0    50   ~ 0
Power input components have specifications\ndescribed in the regulator datasheet.
$Comp
L Device:C_Small C?
U 1 1 5FA170F2
P 2050 5150
F 0 "C?" H 2142 5196 50  0000 L CNN
F 1 "4.7uF" H 2142 5105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2050 5150 50  0001 C CNN
F 3 "https://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM21BC71H475KE11-01.pdf" H 2050 5150 50  0001 C CNN
F 4 "CAP CER 4.7UF 50V X7S 0805" H 2050 5150 50  0001 C CNN "Description"
F 5 "Murata Electronics" H 2050 5150 50  0001 C CNN "Manufacturer"
F 6 "GRM21BC71H475KE11L" H 2050 5150 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 2050 5150 50  0001 C CNN "Supplier"
F 8 "490-12757-1-ND" H 2050 5150 50  0001 C CNN "Supplier PN"
	1    2050 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR?
U 1 1 5FA17392
P 1500 5000
F 0 "#PWR?" H 1500 4850 50  0001 C CNN
F 1 "+12V" H 1515 5173 50  0000 C CNN
F 2 "" H 1500 5000 50  0001 C CNN
F 3 "" H 1500 5000 50  0001 C CNN
	1    1500 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FA1739C
P 1500 5300
F 0 "#PWR?" H 1500 5050 50  0001 C CNN
F 1 "GND" H 1505 5127 50  0000 C CNN
F 2 "" H 1500 5300 50  0001 C CNN
F 3 "" H 1500 5300 50  0001 C CNN
	1    1500 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5FA173AB
P 1650 5150
F 0 "C?" H 1742 5196 50  0000 L CNN
F 1 "10uF" H 1742 5105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 1650 5150 50  0001 C CNN
F 3 "https://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM32EC72A106KE05-01.pdf" H 1650 5150 50  0001 C CNN
F 4 "CAP CER 10UF 100V X7S 1210" H 1650 5150 50  0001 C CNN "Description"
F 5 "Murata Electronics" H 1650 5150 50  0001 C CNN "Manufacturer"
F 6 "GRM32EC72A106KE05L" H 1650 5150 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 1650 5150 50  0001 C CNN "Supplier"
F 8 "490-16266-1-ND" H 1650 5150 50  0001 C CNN "Supplier PN"
	1    1650 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:L L?
U 1 1 5FA173BA
P 1850 5000
F 0 "L?" V 2040 5000 50  0000 C CNN
F 1 "12uH" V 1949 5000 50  0000 C CNN
F 2 "" H 1850 5000 50  0001 C CNN
F 3 "https://recom-power.com/pdf/Accessories/RLS-126.pdf" H 1850 5000 50  0001 C CNN
F 4 "FIXED IND 12UH 800MA 420MOHM SMD" H 1850 5000 50  0001 C CNN "Description"
F 5 "Recom Power" H 1850 5000 50  0001 C CNN "Manufacturer"
F 6 "RLS-126" H 1850 5000 50  0001 C CNN "Manufacturer PN"
F 7 "Digi-Key" H 1850 5000 50  0001 C CNN "Supplier"
F 8 "945-3429-ND" H 1850 5000 50  0001 C CNN "Supplier PN"
	1    1850 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 5000 2050 5000
Wire Wire Line
	2050 5050 2050 5000
Connection ~ 2050 5000
Wire Wire Line
	2050 5000 2300 5000
Wire Wire Line
	1700 5000 1650 5000
Wire Wire Line
	1650 5050 1650 5000
Connection ~ 1650 5000
Wire Wire Line
	1650 5000 1500 5000
Wire Wire Line
	2600 5300 2050 5300
Wire Wire Line
	1650 5250 1650 5300
Connection ~ 1650 5300
Wire Wire Line
	1650 5300 1500 5300
Wire Wire Line
	2050 5250 2050 5300
Connection ~ 2050 5300
Wire Wire Line
	2050 5300 1650 5300
Connection ~ 2600 5300
$Comp
L power:+12V #PWR?
U 1 1 5FA1BD34
P 3700 2750
F 0 "#PWR?" H 3700 2600 50  0001 C CNN
F 1 "+12V" H 3715 2923 50  0000 C CNN
F 2 "" H 3700 2750 50  0001 C CNN
F 3 "" H 3700 2750 50  0001 C CNN
	1    3700 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FA1CC5A
P 3700 3150
F 0 "#PWR?" H 3700 2900 50  0001 C CNN
F 1 "GND" H 3705 2977 50  0000 C CNN
F 2 "" H 3700 3150 50  0001 C CNN
F 3 "" H 3700 3150 50  0001 C CNN
	1    3700 3150
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5FA1D68C
P 3500 2850
F 0 "#FLG?" H 3500 2925 50  0001 C CNN
F 1 "PWR_FLAG" H 3500 3023 50  0001 C CNN
F 2 "" H 3500 2850 50  0001 C CNN
F 3 "~" H 3500 2850 50  0001 C CNN
	1    3500 2850
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5FA1DAB7
P 3500 3050
F 0 "#FLG?" H 3500 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 3500 3223 50  0001 C CNN
F 2 "" H 3500 3050 50  0001 C CNN
F 3 "~" H 3500 3050 50  0001 C CNN
	1    3500 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 2850 3500 2850
Wire Wire Line
	3700 2850 3700 2750
Wire Wire Line
	3400 3050 3500 3050
Wire Wire Line
	3700 3050 3700 3150
Connection ~ 3500 3050
Wire Wire Line
	3500 3050 3700 3050
Connection ~ 3500 2850
Wire Wire Line
	3500 2850 3700 2850
$Comp
L power:Earth #PWR?
U 1 1 5FA39A0C
P 1600 1600
F 0 "#PWR?" H 1600 1350 50  0001 C CNN
F 1 "Earth" H 1600 1450 50  0001 C CNN
F 2 "" H 1600 1600 50  0001 C CNN
F 3 "~" H 1600 1600 50  0001 C CNN
	1    1600 1600
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5FA3A312
P 8050 1650
F 0 "#PWR?" H 8050 1400 50  0001 C CNN
F 1 "Earth" H 8050 1500 50  0001 C CNN
F 2 "" H 8050 1650 50  0001 C CNN
F 3 "~" H 8050 1650 50  0001 C CNN
	1    8050 1650
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5FA3A71B
P 8050 2650
F 0 "#PWR?" H 8050 2400 50  0001 C CNN
F 1 "Earth" H 8050 2500 50  0001 C CNN
F 2 "" H 8050 2650 50  0001 C CNN
F 3 "~" H 8050 2650 50  0001 C CNN
	1    8050 2650
	1    0    0    -1  
$EndComp
$Comp
L power:NEUT #PWR?
U 1 1 5FA3B1C5
P 2150 1250
F 0 "#PWR?" H 2150 1100 50  0001 C CNN
F 1 "NEUT" H 2165 1423 50  0000 C CNN
F 2 "" H 2150 1250 50  0001 C CNN
F 3 "" H 2150 1250 50  0001 C CNN
	1    2150 1250
	1    0    0    -1  
$EndComp
$Comp
L power:NEUT #PWR?
U 1 1 5FA3C444
P 7450 1300
F 0 "#PWR?" H 7450 1150 50  0001 C CNN
F 1 "NEUT" H 7465 1473 50  0000 C CNN
F 2 "" H 7450 1300 50  0001 C CNN
F 3 "" H 7450 1300 50  0001 C CNN
	1    7450 1300
	1    0    0    -1  
$EndComp
$Comp
L power:NEUT #PWR?
U 1 1 5FA3C998
P 7450 2300
F 0 "#PWR?" H 7450 2150 50  0001 C CNN
F 1 "NEUT" H 7465 2473 50  0000 C CNN
F 2 "" H 7450 2300 50  0001 C CNN
F 3 "" H 7450 2300 50  0001 C CNN
	1    7450 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 2300 7450 2350
Wire Wire Line
	7450 2350 7650 2350
Wire Wire Line
	7450 1300 7450 1350
Wire Wire Line
	7450 1350 7650 1350
Wire Wire Line
	2000 1300 2150 1300
Wire Wire Line
	2150 1300 2150 1250
$Comp
L Switch:SW_SPST J?
U 1 1 5FA44A38
P 1600 2200
F 0 "J?" H 1600 2435 50  0000 C CNN
F 1 "Power Switch" H 1600 2344 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-1sqmm_1x02_P5.4mm_D1.4mm_OD2.7mm" H 1600 2200 50  0001 C CNN
F 3 "~" H 1600 2200 50  0001 C CNN
	1    1600 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 1300 1200 2200
Wire Wire Line
	1200 2200 1400 2200
Wire Wire Line
	1800 2200 2000 2200
$Comp
L power:NEUT #PWR?
U 1 1 5FA3216F
P 2250 3000
F 0 "#PWR?" H 2250 2850 50  0001 C CNN
F 1 "NEUT" H 2265 3173 50  0000 C CNN
F 2 "" H 2250 3000 50  0001 C CNN
F 3 "" H 2250 3000 50  0001 C CNN
	1    2250 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3050 2250 3050
Wire Wire Line
	2250 3050 2250 3000
Wire Wire Line
	2450 2700 2450 2850
Wire Wire Line
	2450 2850 2600 2850
Wire Wire Line
	2300 2200 2450 2200
Wire Wire Line
	2450 2200 2450 2400
$Comp
L power:LINE #PWR?
U 1 1 5FA37BC0
P 2650 2100
F 0 "#PWR?" H 2650 1950 50  0001 C CNN
F 1 "LINE" H 2665 2273 50  0000 C CNN
F 2 "" H 2650 2100 50  0001 C CNN
F 3 "" H 2650 2100 50  0001 C CNN
	1    2650 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2200 2650 2200
Wire Wire Line
	2650 2200 2650 2100
Connection ~ 2450 2200
$Comp
L power:LINE #PWR?
U 1 1 5FA436A2
P 6700 1100
F 0 "#PWR?" H 6700 950 50  0001 C CNN
F 1 "LINE" H 6715 1273 50  0000 C CNN
F 2 "" H 6700 1100 50  0001 C CNN
F 3 "" H 6700 1100 50  0001 C CNN
	1    6700 1100
	1    0    0    -1  
$EndComp
$Comp
L power:LINE #PWR?
U 1 1 5FA43CF0
P 7050 2050
F 0 "#PWR?" H 7050 1900 50  0001 C CNN
F 1 "LINE" H 7065 2223 50  0000 C CNN
F 2 "" H 7050 2050 50  0001 C CNN
F 3 "" H 7050 2050 50  0001 C CNN
	1    7050 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1700 6700 1800
Wire Wire Line
	6700 1800 8450 1800
Wire Wire Line
	8450 1800 8450 1350
Wire Wire Line
	7050 2650 7050 2800
Wire Wire Line
	7050 2800 8450 2800
Wire Wire Line
	8450 2800 8450 2350
$EndSCHEMATC
