EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 1 1
Title "Simpanel"
Date ""
Rev "A"
Comp ""
Comment1 "Copyright © Marc A. Pelletier 2020"
Comment2 "CC-BY-SA 3.0"
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	20000 14500 20800 14500
Connection ~ 20000 14500
$Comp
L power:GND #PWR0118
U 1 1 6DF586B1
P 20000 14500
F 0 "#PWR0118" H 20000 14250 50  0001 C CNN
F 1 "GND" H 20005 14327 50  0000 C CNN
F 2 "" H 20000 14500 50  0001 C CNN
F 3 "" H 20000 14500 50  0001 C CNN
	1    20000 14500
	1    0    0    -1  
$EndComp
Wire Wire Line
	20000 14100 19700 14100
Connection ~ 20000 14100
$Comp
L power:GND #PWR0109
U 1 1 6DF576B9
P 20000 14100
F 0 "#PWR0109" H 20000 13850 50  0001 C CNN
F 1 "GND" H 20005 13927 50  0000 C CNN
F 2 "" H 20000 14100 50  0001 C CNN
F 3 "" H 20000 14100 50  0001 C CNN
	1    20000 14100
	1    0    0    -1  
$EndComp
Wire Wire Line
	19700 14500 20000 14500
Wire Wire Line
	20800 14100 20000 14100
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 6D94D501
P 20800 14400
F 0 "H4" H 20900 14449 50  0001 L CNN
F 1 "MountingHole_Pad" H 20900 14403 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 20800 14400 50  0001 C CNN
F 3 "~" H 20800 14400 50  0001 C CNN
	1    20800 14400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 6D94C676
P 20800 14000
F 0 "H3" H 20900 14049 50  0001 L CNN
F 1 "MountingHole_Pad" H 20900 14003 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 20800 14000 50  0001 C CNN
F 3 "~" H 20800 14000 50  0001 C CNN
	1    20800 14000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 6D94B9A4
P 19700 14400
F 0 "H2" H 19800 14449 50  0001 L CNN
F 1 "MountingHole_Pad" H 19800 14403 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 19700 14400 50  0001 C CNN
F 3 "~" H 19700 14400 50  0001 C CNN
	1    19700 14400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 6D94AB69
P 19700 14000
F 0 "H1" H 19800 14049 50  0001 L CNN
F 1 "MountingHole_Pad" H 19800 14003 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 19700 14000 50  0001 C CNN
F 3 "~" H 19700 14000 50  0001 C CNN
	1    19700 14000
	1    0    0    -1  
$EndComp
Text Label 19200 12900 0    20   ~ 0
SW11
Text Label 19300 11350 0    20   ~ 0
SW10
Text Label 19300 10700 0    20   ~ 0
SW9
Text Label 19300 10050 0    20   ~ 0
SW8
Text Label 17400 12700 0    20   ~ 0
SW7
Text Label 17450 11350 0    20   ~ 0
SW6
Text Label 17450 10700 0    20   ~ 0
SW5
Text Label 17450 10050 0    20   ~ 0
SW4
Text Label 15400 11400 0    20   ~ 0
SW3
NoConn ~ 16900 9850
NoConn ~ 16900 10500
NoConn ~ 16900 11200
NoConn ~ 18700 9850
NoConn ~ 18700 10500
NoConn ~ 18700 11150
NoConn ~ 18700 11800
NoConn ~ 20550 11800
NoConn ~ 20550 11150
NoConn ~ 20550 10500
NoConn ~ 20550 9850
Wire Wire Line
	11500 3800 11500 6000
Wire Wire Line
	19350 12900 14800 12900
Wire Wire Line
	19350 12000 19350 12900
Wire Wire Line
	14850 12850 19150 12850
Wire Wire Line
	14900 12800 19100 12800
Wire Wire Line
	14950 12750 19050 12750
Wire Wire Line
	19150 11350 19150 12850
Wire Wire Line
	19350 11350 19150 11350
Wire Wire Line
	19100 10700 19350 10700
Wire Wire Line
	19050 10050 19350 10050
Wire Wire Line
	19100 10700 19100 12800
Wire Wire Line
	19050 10050 19050 12750
Wire Wire Line
	15000 12700 17500 12700
Wire Wire Line
	17300 11350 17500 11350
Wire Wire Line
	17250 10700 17500 10700
Wire Wire Line
	17200 10050 17500 10050
$Comp
L B3J-2100:B3J-2100 SW11
U 1 1 61D431B8
P 19350 11800
F 0 "SW11" H 19950 12065 50  0000 C CNN
F 1 "B3J-2100" H 19950 11974 50  0000 C CNN
F 2 "simpanel:B3J2100" H 20400 11900 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 20400 11800 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 20400 11700 50  0001 L CNN "Description"
F 5 "10.5" H 20400 11600 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 20400 11500 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 20400 11400 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 20400 11300 50  0001 L CNN "Arrow Part Number"
F 9 "" H 20400 11200 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 20400 11100 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 20400 11000 50  0001 L CNN "Mouser Price/Stock"
	1    19350 11800
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW10
U 1 1 61D41FFD
P 19350 11150
F 0 "SW10" H 19950 11415 50  0000 C CNN
F 1 "B3J-2100" H 19950 11324 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 20400 11250 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 20400 11150 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 20400 11050 50  0001 L CNN "Description"
F 5 "10.5" H 20400 10950 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 20400 10850 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 20400 10750 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 20400 10650 50  0001 L CNN "Arrow Part Number"
F 9 "" H 20400 10550 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 20400 10450 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 20400 10350 50  0001 L CNN "Mouser Price/Stock"
	1    19350 11150
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW9
U 1 1 61D40CBA
P 19350 10500
F 0 "SW9" H 19950 10765 50  0000 C CNN
F 1 "B3J-2100" H 19950 10674 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 20400 10600 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 20400 10500 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 20400 10400 50  0001 L CNN "Description"
F 5 "10.5" H 20400 10300 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 20400 10200 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 20400 10100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 20400 10000 50  0001 L CNN "Arrow Part Number"
F 9 "" H 20400 9900 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 20400 9800 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 20400 9700 50  0001 L CNN "Mouser Price/Stock"
	1    19350 10500
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW8
U 1 1 61D3E5A5
P 19350 9850
F 0 "SW8" H 19950 10115 50  0000 C CNN
F 1 "B3J-2100" H 19950 10024 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 20400 9950 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 20400 9850 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 20400 9750 50  0001 L CNN "Description"
F 5 "10.5" H 20400 9650 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 20400 9550 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 20400 9450 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 20400 9350 50  0001 L CNN "Arrow Part Number"
F 9 "" H 20400 9250 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 20400 9150 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 20400 9050 50  0001 L CNN "Mouser Price/Stock"
	1    19350 9850
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW7
U 1 1 61D48065
P 17500 11800
F 0 "SW7" H 18100 12065 50  0000 C CNN
F 1 "B3J-2100" H 18100 11974 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 18550 11900 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 18550 11800 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 18550 11700 50  0001 L CNN "Description"
F 5 "10.5" H 18550 11600 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 18550 11500 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 18550 11400 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 18550 11300 50  0001 L CNN "Arrow Part Number"
F 9 "" H 18550 11200 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 18550 11100 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 18550 11000 50  0001 L CNN "Mouser Price/Stock"
	1    17500 11800
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW6
U 1 1 61D46961
P 17500 11150
F 0 "SW6" H 18100 11415 50  0000 C CNN
F 1 "B3J-2100" H 18100 11324 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 18550 11250 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 18550 11150 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 18550 11050 50  0001 L CNN "Description"
F 5 "10.5" H 18550 10950 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 18550 10850 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 18550 10750 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 18550 10650 50  0001 L CNN "Arrow Part Number"
F 9 "" H 18550 10550 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 18550 10450 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 18550 10350 50  0001 L CNN "Mouser Price/Stock"
	1    17500 11150
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW5
U 1 1 61D45775
P 17500 10500
F 0 "SW5" H 18100 10765 50  0000 C CNN
F 1 "B3J-2100" H 18100 10674 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 18550 10600 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 18550 10500 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 18550 10400 50  0001 L CNN "Description"
F 5 "10.5" H 18550 10300 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 18550 10200 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 18550 10100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 18550 10000 50  0001 L CNN "Arrow Part Number"
F 9 "" H 18550 9900 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 18550 9800 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 18550 9700 50  0001 L CNN "Mouser Price/Stock"
	1    17500 10500
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW4
U 1 1 61D44595
P 17500 9850
F 0 "SW4" H 18100 10115 50  0000 C CNN
F 1 "B3J-2100" H 18100 10024 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 18550 9950 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 18550 9850 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 18550 9750 50  0001 L CNN "Description"
F 5 "10.5" H 18550 9650 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 18550 9550 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 18550 9450 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 18550 9350 50  0001 L CNN "Arrow Part Number"
F 9 "" H 18550 9250 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 18550 9150 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 18550 9050 50  0001 L CNN "Mouser Price/Stock"
	1    17500 9850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 635F6729
P 17400 12200
F 0 "#PWR0107" H 17400 11950 50  0001 C CNN
F 1 "GND" H 17405 12027 50  0000 C CNN
F 2 "" H 17400 12200 50  0001 C CNN
F 3 "" H 17400 12200 50  0001 C CNN
	1    17400 12200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 635F7775
P 19250 12200
F 0 "#PWR0106" H 19250 11950 50  0001 C CNN
F 1 "GND" H 19255 12027 50  0000 C CNN
F 2 "" H 19250 12200 50  0001 C CNN
F 3 "" H 19250 12200 50  0001 C CNN
	1    19250 12200
	1    0    0    -1  
$EndComp
Wire Wire Line
	19350 11800 19250 11800
Wire Wire Line
	19250 11800 19250 12200
Wire Wire Line
	19350 11900 19350 11800
Connection ~ 19350 11800
Wire Wire Line
	19350 11250 19350 11150
Wire Wire Line
	19350 11150 19250 11150
Wire Wire Line
	19250 11150 19250 11800
Connection ~ 19350 11150
Connection ~ 19250 11800
Wire Wire Line
	19350 10600 19350 10500
Wire Wire Line
	19350 10500 19250 10500
Wire Wire Line
	19250 10500 19250 11150
Connection ~ 19350 10500
Connection ~ 19250 11150
Wire Wire Line
	19350 9850 19350 9950
Wire Wire Line
	19350 9850 19250 9850
Wire Wire Line
	19250 9850 19250 10500
Connection ~ 19350 9850
Connection ~ 19250 10500
Wire Wire Line
	17500 11900 17500 11800
Wire Wire Line
	17500 11250 17500 11150
Wire Wire Line
	17500 10600 17500 10500
Wire Wire Line
	17500 9950 17500 9850
Wire Wire Line
	17500 9850 17400 9850
Wire Wire Line
	17400 9850 17400 10500
Connection ~ 17500 9850
Wire Wire Line
	17500 11800 17400 11800
Connection ~ 17500 11800
Connection ~ 17400 11800
Wire Wire Line
	17400 11800 17400 12200
Wire Wire Line
	17500 11150 17400 11150
Connection ~ 17500 11150
Connection ~ 17400 11150
Wire Wire Line
	17400 11150 17400 11800
Wire Wire Line
	17500 10500 17400 10500
Connection ~ 17500 10500
Connection ~ 17400 10500
Wire Wire Line
	17400 10500 17400 11150
Wire Wire Line
	17300 11350 17300 12650
Wire Wire Line
	17500 12000 17500 12700
Wire Wire Line
	17300 12650 15050 12650
Wire Wire Line
	17250 12600 15100 12600
Wire Wire Line
	17250 10700 17250 12600
Wire Wire Line
	17200 12550 15150 12550
Wire Wire Line
	17200 10050 17200 12550
Wire Wire Line
	15700 11400 15200 11400
Wire Wire Line
	15600 11200 15600 11600
Connection ~ 15600 11200
Connection ~ 15700 11200
Wire Wire Line
	15700 11200 15600 11200
Wire Wire Line
	15600 10500 15600 11200
Connection ~ 15600 10500
Connection ~ 15700 10500
Wire Wire Line
	15700 10500 15600 10500
Connection ~ 15700 9850
Wire Wire Line
	15600 9850 15600 10500
Wire Wire Line
	15700 9850 15600 9850
Wire Wire Line
	15700 9950 15700 9850
Wire Wire Line
	15700 10600 15700 10500
Wire Wire Line
	15700 11300 15700 11200
$Comp
L power:GND #PWR0105
U 1 1 635F5BAC
P 15600 11600
F 0 "#PWR0105" H 15600 11350 50  0001 C CNN
F 1 "GND" H 15605 11427 50  0000 C CNN
F 2 "" H 15600 11600 50  0001 C CNN
F 3 "" H 15600 11600 50  0001 C CNN
	1    15600 11600
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW2
U 1 1 61D4A935
P 15700 10500
F 0 "SW2" H 16300 10765 50  0000 C CNN
F 1 "B3J-2100" H 16300 10674 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 16750 10600 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16750 10500 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16750 10400 50  0001 L CNN "Description"
F 5 "10.5" H 16750 10300 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16750 10200 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16750 10100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16750 10000 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16750 9900 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16750 9800 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16750 9700 50  0001 L CNN "Mouser Price/Stock"
	1    15700 10500
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW3
U 1 1 61D4C095
P 15700 11200
F 0 "SW3" H 16300 11465 50  0000 C CNN
F 1 "B3J-2100" H 16300 11374 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 16750 11300 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16750 11200 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16750 11100 50  0001 L CNN "Description"
F 5 "10.5" H 16750 11000 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16750 10900 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16750 10800 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16750 10700 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16750 10600 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16750 10500 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16750 10400 50  0001 L CNN "Mouser Price/Stock"
	1    15700 11200
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 SW1
U 1 1 61D48F9B
P 15700 9850
F 0 "SW1" H 16300 10115 50  0000 C CNN
F 1 "B3J-2100" H 16300 10024 50  0000 C CNN
F 2 "simpanel:B3J2100" H 16750 9950 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16750 9850 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16750 9750 50  0001 L CNN "Description"
F 5 "10.5" H 16750 9650 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16750 9550 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16750 9450 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16750 9350 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16750 9250 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16750 9150 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16750 9050 50  0001 L CNN "Mouser Price/Stock"
	1    15700 9850
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 3400 11550 5600
$Comp
L eec:AS1130-BSST U2
U 1 1 5FD03C01
P 11900 3100
F 0 "U2" H 12500 3365 50  0000 C CNN
F 1 "AS1130-BSST" H 12500 3274 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 11900 3500 50  0001 L CNN
F 3 "http://www.ams.com/eng/content/download/185846/834724/105034" H 11900 3600 50  0001 L CNN
F 4 "MO-150" H 11900 3700 50  0001 L CNN "Code  JEDEC"
F 5 "Manufacturer URL" H 11900 3800 50  0001 L CNN "Component Link 1 Description"
F 6 "www.ams.com" H 11900 3900 50  0001 L CNN "Component Link 1 URL"
F 7 "Rev. 1.07" H 11900 4000 50  0001 L CNN "Datasheet Version"
F 8 "true" H 11900 4100 50  0001 L CNN "Error Detection"
F 9 "8-bit PWM & analog current control, dynamic headroom control" H 11900 4200 50  0001 L CNN "Features"
F 10 "2.5" H 11900 4300 50  0001 L CNN "LED Current per Output mA"
F 11 "2" H 11900 4400 50  0001 L CNN "LED to LED Matching "
F 12 "Surface Mount" H 11900 4500 50  0001 L CNN "Mounting Technology"
F 13 "132" H 11900 4600 50  0001 L CNN "Outputs"
F 14 "28-Pin Shrink Small Outline Package, 10.2 x 5.3 mm Body, 0.65 mm Pitch" H 11900 4700 50  0001 L CNN "Package Description"
F 15 "N/C, 07/2011" H 11900 4800 50  0001 L CNN "Package Version"
F 16 "true" H 11900 4900 50  0001 L CNN "Read back"
F 17 "2.7 to 5.5" H 11900 5000 50  0001 L CNN "Supply Voltage V"
F 18 "IC" H 11900 5100 50  0001 L CNN "category"
F 19 "4367283" H 11900 5200 50  0001 L CNN "ciiva ids"
F 20 "598dcdd5055ccc55" H 11900 5300 50  0001 L CNN "library id"
F 21 "AMS" H 11900 5400 50  0001 L CNN "manufacturer"
F 22 "SSOP-28" H 11900 5500 50  0001 L CNN "package"
F 23 "1394513892" H 11900 5600 50  0001 L CNN "release date"
F 24 "660BAB0B-1A30-45A6-8177-846E59C4C6EC" H 11900 5700 50  0001 L CNN "vault revision"
F 25 "yes" H 11900 5800 50  0001 L CNN "imported"
	1    11900 3100
	1    0    0    -1  
$EndComp
$Comp
L eec:AS1130-BSST U3
U 1 1 5FD05F4A
P 11900 5300
F 0 "U3" H 12500 5565 50  0000 C CNN
F 1 "AS1130-BSST" H 12500 5474 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 11900 5700 50  0001 L CNN
F 3 "http://www.ams.com/eng/content/download/185846/834724/105034" H 11900 5800 50  0001 L CNN
F 4 "MO-150" H 11900 5900 50  0001 L CNN "Code  JEDEC"
F 5 "Manufacturer URL" H 11900 6000 50  0001 L CNN "Component Link 1 Description"
F 6 "www.ams.com" H 11900 6100 50  0001 L CNN "Component Link 1 URL"
F 7 "Rev. 1.07" H 11900 6200 50  0001 L CNN "Datasheet Version"
F 8 "true" H 11900 6300 50  0001 L CNN "Error Detection"
F 9 "8-bit PWM & analog current control, dynamic headroom control" H 11900 6400 50  0001 L CNN "Features"
F 10 "2.5" H 11900 6500 50  0001 L CNN "LED Current per Output mA"
F 11 "2" H 11900 6600 50  0001 L CNN "LED to LED Matching "
F 12 "Surface Mount" H 11900 6700 50  0001 L CNN "Mounting Technology"
F 13 "132" H 11900 6800 50  0001 L CNN "Outputs"
F 14 "28-Pin Shrink Small Outline Package, 10.2 x 5.3 mm Body, 0.65 mm Pitch" H 11900 6900 50  0001 L CNN "Package Description"
F 15 "N/C, 07/2011" H 11900 7000 50  0001 L CNN "Package Version"
F 16 "true" H 11900 7100 50  0001 L CNN "Read back"
F 17 "2.7 to 5.5" H 11900 7200 50  0001 L CNN "Supply Voltage V"
F 18 "IC" H 11900 7300 50  0001 L CNN "category"
F 19 "4367283" H 11900 7400 50  0001 L CNN "ciiva ids"
F 20 "598dcdd5055ccc55" H 11900 7500 50  0001 L CNN "library id"
F 21 "AMS" H 11900 7600 50  0001 L CNN "manufacturer"
F 22 "SSOP-28" H 11900 7700 50  0001 L CNN "package"
F 23 "1394513892" H 11900 7800 50  0001 L CNN "release date"
F 24 "660BAB0B-1A30-45A6-8177-846E59C4C6EC" H 11900 7900 50  0001 L CNN "vault revision"
F 25 "yes" H 11900 8000 50  0001 L CNN "imported"
	1    11900 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	11750 6600 12000 6600
Connection ~ 12000 4500
Wire Wire Line
	12000 4500 12000 4400
Connection ~ 12000 4600
Wire Wire Line
	12000 4600 12000 4500
Wire Wire Line
	12000 4700 12000 4600
$Comp
L power:GND #PWR0103
U 1 1 62CBA5C1
P 13100 4900
F 0 "#PWR0103" H 13100 4650 50  0001 C CNN
F 1 "GND" H 13105 4727 50  0000 C CNN
F 2 "" H 13100 4900 50  0001 C CNN
F 3 "" H 13100 4900 50  0001 C CNN
	1    13100 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 62CBB729
P 13100 7100
F 0 "#PWR0104" H 13100 6850 50  0001 C CNN
F 1 "GND" H 13105 6927 50  0000 C CNN
F 2 "" H 13100 7100 50  0001 C CNN
F 3 "" H 13100 7100 50  0001 C CNN
	1    13100 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	13100 7100 13100 7000
Wire Wire Line
	13100 7000 13000 7000
Wire Wire Line
	13100 4900 13100 4800
Wire Wire Line
	13100 4800 13000 4800
$Comp
L power:GND #PWR0119
U 1 1 6C78DAD7
P 11950 6250
F 0 "#PWR0119" H 11950 6000 50  0001 C CNN
F 1 "GND" H 11955 6077 50  0000 C CNN
F 2 "" H 11950 6250 50  0001 C CNN
F 3 "" H 11950 6250 50  0001 C CNN
	1    11950 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 6250 11950 6200
Wire Wire Line
	11950 6200 12000 6200
Wire Wire Line
	11550 3400 12000 3400
Wire Wire Line
	11550 5600 12000 5600
Wire Wire Line
	12000 3800 11500 3800
Wire Wire Line
	11500 6000 12000 6000
NoConn ~ 12000 4000
Wire Wire Line
	12000 6700 11750 6700
Wire Wire Line
	11750 6700 11750 6600
Wire Wire Line
	12000 6800 11750 6800
Wire Wire Line
	11750 6800 11750 6700
Connection ~ 11750 6700
Wire Wire Line
	12000 6900 11750 6900
Wire Wire Line
	11750 6900 11750 6800
Connection ~ 11750 6800
Wire Wire Line
	13000 6800 13100 6800
Wire Wire Line
	13100 6800 13100 6900
Connection ~ 13100 7000
Wire Wire Line
	13000 6700 13100 6700
Wire Wire Line
	13100 6700 13100 6800
Connection ~ 13100 6800
Wire Wire Line
	13000 6600 13100 6600
Wire Wire Line
	13100 6600 13100 6700
Connection ~ 13100 6700
Wire Wire Line
	13000 4400 13100 4400
Wire Wire Line
	13100 4400 13100 4500
Connection ~ 13100 4800
Wire Wire Line
	13000 4700 13100 4700
Connection ~ 13100 4700
Wire Wire Line
	13100 4700 13100 4800
Wire Wire Line
	13000 4600 13100 4600
Connection ~ 13100 4600
Wire Wire Line
	13100 4600 13100 4700
Wire Wire Line
	10200 10050 15700 10050
Wire Wire Line
	15700 10700 15250 10700
Wire Wire Line
	15250 10700 15250 10100
Wire Wire Line
	15250 10100 10150 10100
Wire Wire Line
	15200 11400 15200 10150
Wire Wire Line
	15200 10150 10100 10150
Wire Wire Line
	15150 12550 15150 10200
Wire Wire Line
	15100 12600 15100 10250
Wire Wire Line
	15050 12650 15050 10300
Wire Wire Line
	15000 12700 15000 10350
Wire Wire Line
	14950 12750 14950 10400
Wire Wire Line
	14900 12800 14900 10450
Wire Wire Line
	14850 12850 14850 10500
Wire Wire Line
	14800 12900 14800 10550
Wire Wire Line
	10050 10200 15150 10200
Wire Wire Line
	10000 10250 15100 10250
Wire Wire Line
	9950 10300 15050 10300
Wire Wire Line
	9900 10350 15000 10350
Wire Wire Line
	9850 10400 14950 10400
Wire Wire Line
	9800 10450 14900 10450
Wire Wire Line
	9750 10500 14850 10500
Wire Wire Line
	9700 10550 14800 10550
Wire Wire Line
	11600 5400 12000 5400
Wire Wire Line
	11600 3200 12000 3200
Wire Wire Line
	11650 5300 12000 5300
Wire Wire Line
	11650 3100 12000 3100
Wire Wire Line
	11850 4400 12000 4400
Connection ~ 12000 4400
$Comp
L pecr11:PEC11R-4220F-S0024 ENC1
U 1 1 6922AA5D
P 14200 15400
F 0 "ENC1" H 14900 14435 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 14900 14526 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 14200 15800 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 14200 15900 50  0001 L CNN
F 4 "Enc" H 14200 16000 50  0001 L CNN "category"
F 5 "10mA" H 14200 16100 50  0001 L CNN "current rating"
F 6 "Yes" H 14200 16200 50  0001 L CNN "detend"
F 7 "Electromechanical" H 14200 16300 50  0001 L CNN "device class L1"
F 8 "Switches" H 14200 16400 50  0001 L CNN "device class L2"
F 9 "Encoders" H 14200 16500 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 14200 16600 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 14200 16700 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 14200 16800 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 14200 16900 50  0001 L CNN "height"
F 14 "yes" H 14200 17000 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 14200 17100 50  0001 L CNN "library id"
F 16 "Bourns" H 14200 17200 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 14200 17300 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 14200 17400 50  0001 L CNN "mouser part number"
F 19 "1" H 14200 17500 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 14200 17600 50  0001 L CNN "package"
F 21 "24" H 14200 17700 50  0001 L CNN "pulses per rev"
F 22 "yes" H 14200 17800 50  0001 L CNN "rohs"
F 23 "+70°C" H 14200 17900 50  0001 L CNN "temperature range high"
F 24 "30°C" H 14200 18000 50  0001 L CNN "temperature range low"
F 25 "5V" H 14200 18100 50  0001 L CNN "voltage rating DC"
	1    14200 15400
	-1   0    0    1   
$EndComp
$Comp
L pecr11:PEC11R-4220F-S0024 ENC2
U 1 1 6922EC85
P 14200 14250
F 0 "ENC2" H 14900 13285 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 14900 13376 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 14200 14650 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 14200 14750 50  0001 L CNN
F 4 "Enc" H 14200 14850 50  0001 L CNN "category"
F 5 "10mA" H 14200 14950 50  0001 L CNN "current rating"
F 6 "Yes" H 14200 15050 50  0001 L CNN "detend"
F 7 "Electromechanical" H 14200 15150 50  0001 L CNN "device class L1"
F 8 "Switches" H 14200 15250 50  0001 L CNN "device class L2"
F 9 "Encoders" H 14200 15350 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 14200 15450 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 14200 15550 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 14200 15650 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 14200 15750 50  0001 L CNN "height"
F 14 "yes" H 14200 15850 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 14200 15950 50  0001 L CNN "library id"
F 16 "Bourns" H 14200 16050 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 14200 16150 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 14200 16250 50  0001 L CNN "mouser part number"
F 19 "1" H 14200 16350 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 14200 16450 50  0001 L CNN "package"
F 21 "24" H 14200 16550 50  0001 L CNN "pulses per rev"
F 22 "yes" H 14200 16650 50  0001 L CNN "rohs"
F 23 "+70°C" H 14200 16750 50  0001 L CNN "temperature range high"
F 24 "30°C" H 14200 16850 50  0001 L CNN "temperature range low"
F 25 "5V" H 14200 16950 50  0001 L CNN "voltage rating DC"
	1    14200 14250
	-1   0    0    1   
$EndComp
$Comp
L pecr11:PEC11R-4220F-S0024 ENC3
U 1 1 69231399
P 14200 13100
F 0 "ENC3" H 14900 12135 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 14900 12226 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 14200 13500 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 14200 13600 50  0001 L CNN
F 4 "Enc" H 14200 13700 50  0001 L CNN "category"
F 5 "10mA" H 14200 13800 50  0001 L CNN "current rating"
F 6 "Yes" H 14200 13900 50  0001 L CNN "detend"
F 7 "Electromechanical" H 14200 14000 50  0001 L CNN "device class L1"
F 8 "Switches" H 14200 14100 50  0001 L CNN "device class L2"
F 9 "Encoders" H 14200 14200 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 14200 14300 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 14200 14400 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 14200 14500 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 14200 14600 50  0001 L CNN "height"
F 14 "yes" H 14200 14700 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 14200 14800 50  0001 L CNN "library id"
F 16 "Bourns" H 14200 14900 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 14200 15000 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 14200 15100 50  0001 L CNN "mouser part number"
F 19 "1" H 14200 15200 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 14200 15300 50  0001 L CNN "package"
F 21 "24" H 14200 15400 50  0001 L CNN "pulses per rev"
F 22 "yes" H 14200 15500 50  0001 L CNN "rohs"
F 23 "+70°C" H 14200 15600 50  0001 L CNN "temperature range high"
F 24 "30°C" H 14200 15700 50  0001 L CNN "temperature range low"
F 25 "5V" H 14200 15800 50  0001 L CNN "voltage rating DC"
	1    14200 13100
	-1   0    0    1   
$EndComp
$Comp
L pecr11:PEC11R-4220F-S0024 ENC4
U 1 1 69233DD6
P 14200 11950
F 0 "ENC4" H 14900 10985 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 14900 11076 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 14200 12350 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 14200 12450 50  0001 L CNN
F 4 "Enc" H 14200 12550 50  0001 L CNN "category"
F 5 "10mA" H 14200 12650 50  0001 L CNN "current rating"
F 6 "Yes" H 14200 12750 50  0001 L CNN "detend"
F 7 "Electromechanical" H 14200 12850 50  0001 L CNN "device class L1"
F 8 "Switches" H 14200 12950 50  0001 L CNN "device class L2"
F 9 "Encoders" H 14200 13050 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 14200 13150 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 14200 13250 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 14200 13350 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 14200 13450 50  0001 L CNN "height"
F 14 "yes" H 14200 13550 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 14200 13650 50  0001 L CNN "library id"
F 16 "Bourns" H 14200 13750 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 14200 13850 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 14200 13950 50  0001 L CNN "mouser part number"
F 19 "1" H 14200 14050 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 14200 14150 50  0001 L CNN "package"
F 21 "24" H 14200 14250 50  0001 L CNN "pulses per rev"
F 22 "yes" H 14200 14350 50  0001 L CNN "rohs"
F 23 "+70°C" H 14200 14450 50  0001 L CNN "temperature range high"
F 24 "30°C" H 14200 14550 50  0001 L CNN "temperature range low"
F 25 "5V" H 14200 14650 50  0001 L CNN "voltage rating DC"
	1    14200 11950
	-1   0    0    1   
$EndComp
Wire Wire Line
	14100 11950 14450 11950
$Comp
L power:GND #PWR0108
U 1 1 6A3B2D86
P 14200 15150
F 0 "#PWR0108" H 14200 14900 50  0001 C CNN
F 1 "GND" H 14205 14977 50  0000 C CNN
F 2 "" H 14200 15150 50  0001 C CNN
F 3 "" H 14200 15150 50  0001 C CNN
	1    14200 15150
	1    0    0    -1  
$EndComp
Wire Wire Line
	14100 15000 14200 15000
Wire Wire Line
	14200 15000 14200 15150
Wire Wire Line
	14200 15000 14200 14800
Wire Wire Line
	14200 14800 14100 14800
Connection ~ 14200 15000
Wire Wire Line
	14200 14800 14200 14700
Wire Wire Line
	14200 14700 14100 14700
Connection ~ 14200 14800
Wire Wire Line
	14200 14700 14200 13850
Wire Wire Line
	14200 13850 14100 13850
Connection ~ 14200 14700
Wire Wire Line
	14200 13850 14200 13650
Wire Wire Line
	14200 11250 14100 11250
Connection ~ 14200 13850
Wire Wire Line
	14100 11350 14200 11350
Connection ~ 14200 11350
Wire Wire Line
	14200 11350 14200 11250
Wire Wire Line
	14100 11550 14200 11550
Connection ~ 14200 11550
Wire Wire Line
	14200 11550 14200 11350
Wire Wire Line
	14100 12400 14200 12400
Connection ~ 14200 12400
Wire Wire Line
	14200 12400 14200 11550
Wire Wire Line
	14100 12500 14200 12500
Connection ~ 14200 12500
Wire Wire Line
	14200 12500 14200 12400
Wire Wire Line
	14100 12700 14200 12700
Connection ~ 14200 12700
Wire Wire Line
	14200 12700 14200 12500
Wire Wire Line
	14100 13550 14200 13550
Connection ~ 14200 13550
Wire Wire Line
	14200 13550 14200 12700
Wire Wire Line
	14100 13650 14200 13650
Connection ~ 14200 13650
Wire Wire Line
	14200 13650 14200 13550
Wire Wire Line
	12900 14900 12800 14900
Connection ~ 14200 11250
Wire Wire Line
	12900 11450 12800 11450
Connection ~ 12800 11450
Wire Wire Line
	12900 12600 12800 12600
Connection ~ 12800 12600
Wire Wire Line
	12800 12600 12800 11450
Wire Wire Line
	12900 13750 12800 13750
Connection ~ 12800 13750
Wire Wire Line
	12800 10900 14200 10900
Wire Wire Line
	14200 10900 14200 11250
Wire Wire Line
	12800 10900 12800 11450
Text Label 12800 15200 0    20   ~ 0
ENC1B
Text Label 12800 15300 0    20   ~ 0
ENC1A
Wire Wire Line
	12800 14900 12800 13750
Text Label 12650 14050 0    20   ~ 0
ENC2B
Text Label 12650 14150 0    20   ~ 0
ENC2A
Text Label 12650 12900 0    20   ~ 0
ENC3B
Text Label 12650 13000 0    20   ~ 0
ENC3A
Text Label 12650 11750 0    20   ~ 0
ENC4B
Text Label 12650 11850 0    20   ~ 0
ENC4A
Text Label 14250 14250 0    20   ~ 0
ENC2S
Text Label 14200 15400 0    20   ~ 0
ENC1S
Text Label 14300 13100 0    20   ~ 0
ENC3S
Text Label 14350 11950 0    20   ~ 0
ENC4S
Wire Wire Line
	12800 12600 12800 13750
Wire Wire Line
	14450 10750 14450 11950
Wire Wire Line
	14500 10700 14500 13100
Wire Wire Line
	14100 13100 14500 13100
Wire Wire Line
	14550 10650 14550 14250
Wire Wire Line
	14100 14250 14550 14250
Wire Wire Line
	14600 10600 14600 15400
Wire Wire Line
	14100 15400 14600 15400
Wire Wire Line
	12650 11750 12900 11750
Wire Wire Line
	12600 11850 12900 11850
Wire Wire Line
	12550 12900 12900 12900
Wire Wire Line
	12500 13000 12900 13000
Wire Wire Line
	12450 14050 12900 14050
Wire Wire Line
	12400 14150 12900 14150
Wire Wire Line
	12350 15200 12900 15200
Wire Wire Line
	12300 15300 12900 15300
Wire Wire Line
	9650 10600 14600 10600
Wire Wire Line
	9600 10650 14550 10650
Wire Wire Line
	9550 10700 14500 10700
Wire Wire Line
	9500 10750 14450 10750
Wire Wire Line
	9450 10800 12650 10800
Wire Wire Line
	12650 10800 12650 11750
Wire Wire Line
	9400 10850 12600 10850
Wire Wire Line
	12600 10850 12600 11850
Wire Wire Line
	9350 10900 12550 10900
Wire Wire Line
	12550 10900 12550 12900
Wire Wire Line
	9300 10950 12500 10950
Wire Wire Line
	12500 10950 12500 13000
Wire Wire Line
	9250 11000 12450 11000
Wire Wire Line
	12450 11000 12450 14050
Wire Wire Line
	9200 11050 12400 11050
Wire Wire Line
	12400 11050 12400 14150
Wire Wire Line
	9150 11100 12350 11100
Wire Wire Line
	12350 11100 12350 15200
Wire Wire Line
	9100 11150 12300 11150
Wire Wire Line
	12300 11150 12300 15300
Wire Wire Line
	11850 4400 11850 4300
Connection ~ 11750 6600
Text Label 15400 10700 0    20   ~ 0
SW2
Text Label 15400 10050 0    20   ~ 0
SW1
$Comp
L Device:Varistor_US R4
U 1 1 62660EE0
P 2025 4825
F 0 "R4" V 1983 4933 45  0000 L CNN
F 1 "CG0603MLC-05E" V 2067 4933 45  0001 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2055 4975 20  0001 C CNN
F 3 "" H 2025 4825 60  0001 C CNN
	1    2025 4825
	1    0    0    -1  
$EndComp
$Comp
L Device:Varistor_US R3
U 1 1 624B63EE
P 1775 4825
F 0 "R3" V 1733 4933 45  0000 C CNN
F 1 "CG0603MLC-05E" V 1817 4933 45  0001 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1805 4975 20  0001 C CNN
F 3 "" H 1775 4825 60  0001 C CNN
	1    1775 4825
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 627F8818
P 2775 4175
F 0 "R1" V 2570 4175 50  0000 C CNN
F 1 "22" V 2661 4175 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2815 4165 50  0001 C CNN
F 3 "~" H 2775 4175 50  0001 C CNN
	1    2775 4175
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R2
U 1 1 62814B5B
P 3075 4275
F 0 "R2" V 2870 4275 50  0000 C CNN
F 1 "22" V 2961 4275 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3115 4265 50  0001 C CNN
F 3 "~" H 3075 4275 50  0001 C CNN
	1    3075 4275
	0    1    1    0   
$EndComp
Wire Wire Line
	3225 4275 5175 4275
Wire Wire Line
	3400 4375 3400 3975
Wire Wire Line
	3400 3975 5175 3975
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 62A41C41
P 2300 5175
F 0 "FB1" V 2063 5175 50  0000 C CNN
F 1 "BLM21" V 2154 5175 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2230 5175 50  0001 C CNN
F 3 "~" H 2300 5175 50  0001 C CNN
	1    2300 5175
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 5175 2400 5175
Wire Wire Line
	800  4375 800  4275
Wire Wire Line
	1775 4275 2925 4275
Wire Wire Line
	1700 4175 2025 4175
Connection ~ 2025 4175
Wire Wire Line
	2025 4175 2625 4175
Wire Wire Line
	2925 4175 5175 4175
$Comp
L power:GND #PWR0101
U 1 1 62B7230F
P 2550 5300
F 0 "#PWR0101" H 2550 5050 50  0001 C CNN
F 1 "GND" H 2555 5127 50  0000 C CNN
F 2 "" H 2550 5300 50  0001 C CNN
F 3 "" H 2550 5300 50  0001 C CNN
	1    2550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 5175 2550 5300
Connection ~ 2550 5175
Wire Wire Line
	800  4375 800  5175
Connection ~ 800  4375
Wire Wire Line
	800  5175 1775 5175
Wire Wire Line
	1775 4275 1775 4675
Wire Wire Line
	2025 4175 2025 4675
Wire Wire Line
	2025 4975 2025 5175
Connection ~ 2025 5175
Wire Wire Line
	2025 5175 2200 5175
Wire Wire Line
	1775 4975 1775 5175
Connection ~ 1775 5175
Wire Wire Line
	1775 5175 2025 5175
$Comp
L power:VCC #PWR0111
U 1 1 62C7E4FE
P 3700 4575
F 0 "#PWR0111" H 3700 4425 50  0001 C CNN
F 1 "VCC" H 3715 4748 50  0000 C CNN
F 2 "" H 3700 4575 50  0001 C CNN
F 3 "" H 3700 4575 50  0001 C CNN
	1    3700 4575
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4775 3700 4575
$Comp
L Device:CP1 C1
U 1 1 62CBD24D
P 2775 4975
F 0 "C1" H 2890 5021 50  0000 L CNN
F 1 "47µf" H 2890 4930 50  0000 L CNN
F 2 "Capacitor_SMD:C_Elec_4x5.4" H 2775 4975 50  0001 C CNN
F 3 "~" H 2775 4975 50  0001 C CNN
	1    2775 4975
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 62CBDDD2
P 3225 4975
F 0 "C2" H 3340 5021 50  0000 L CNN
F 1 "100nf" H 3340 4930 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3263 4825 50  0001 C CNN
F 3 "~" H 3225 4975 50  0001 C CNN
	1    3225 4975
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 4825 3900 4475
Wire Wire Line
	3900 4475 5175 4475
Wire Wire Line
	2550 5175 2775 5175
Wire Wire Line
	3900 5175 3900 5125
Wire Wire Line
	3225 5125 3225 5175
Wire Wire Line
	2775 5125 2775 5175
Connection ~ 2775 5175
Wire Wire Line
	2775 4825 2775 4775
Connection ~ 2775 4775
Wire Wire Line
	3225 4825 3225 4775
Wire Wire Line
	5875 2875 5875 2800
Wire Wire Line
	5675 2800 5675 2875
Wire Wire Line
	5775 2875 5775 2800
Wire Wire Line
	5875 2800 5775 2800
Wire Wire Line
	5775 2800 5675 2800
Connection ~ 5775 2800
$Comp
L power:VCC #PWR0112
U 1 1 62DECD03
P 5675 2675
F 0 "#PWR0112" H 5675 2525 50  0001 C CNN
F 1 "VCC" H 5690 2848 50  0000 C CNN
F 2 "" H 5675 2675 50  0001 C CNN
F 3 "" H 5675 2675 50  0001 C CNN
	1    5675 2675
	1    0    0    -1  
$EndComp
Wire Wire Line
	5675 2800 5675 2675
Connection ~ 5675 2800
$Comp
L Device:C C3
U 1 1 62CBEB08
P 3900 4975
F 0 "C3" H 4015 5021 50  0000 L CNN
F 1 "1µf" H 4015 4930 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3938 4825 50  0001 C CNN
F 3 "~" H 3900 4975 50  0001 C CNN
	1    3900 4975
	1    0    0    -1  
$EndComp
Connection ~ 3225 4775
Connection ~ 3225 5175
Wire Wire Line
	3225 5175 3900 5175
Wire Wire Line
	2775 5175 3225 5175
Wire Wire Line
	2775 4775 3225 4775
$Comp
L Device:Crystal Y1
U 1 1 62E3E8E9
P 4675 3475
F 0 "Y1" V 4721 3344 50  0000 R CNN
F 1 "16MHz" V 4630 3344 50  0000 R CNN
F 2 "Crystal:Crystal_SMD_HC49-SD" H 4675 3475 50  0001 C CNN
F 3 "~" H 4675 3475 50  0001 C CNN
F 4 "C110562" V 4675 3475 50  0001 C CNN "LCSC"
	1    4675 3475
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4675 3325 5075 3325
Wire Wire Line
	5075 3325 5075 3375
Wire Wire Line
	5075 3375 5175 3375
Wire Wire Line
	4675 3625 5075 3625
Wire Wire Line
	5075 3625 5075 3575
Wire Wire Line
	5075 3575 5175 3575
$Comp
L Device:C C5
U 1 1 62E86B2A
P 4350 3625
F 0 "C5" V 4098 3625 50  0000 C CNN
F 1 "22pf" V 4189 3625 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4388 3475 50  0001 C CNN
F 3 "~" H 4350 3625 50  0001 C CNN
	1    4350 3625
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 62E87B53
P 4350 3325
F 0 "C4" V 4098 3325 50  0000 C CNN
F 1 "22pf" V 4189 3325 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4388 3175 50  0001 C CNN
F 3 "~" H 4350 3325 50  0001 C CNN
	1    4350 3325
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 3325 4675 3325
Connection ~ 4675 3325
Wire Wire Line
	4500 3625 4675 3625
Connection ~ 4675 3625
Wire Wire Line
	4200 3325 4200 3625
Wire Wire Line
	4200 3750 4200 3625
Connection ~ 4200 3625
$Comp
L power:GND #PWR0113
U 1 1 62EEA58A
P 4200 3750
F 0 "#PWR0113" H 4200 3500 50  0001 C CNN
F 1 "GND" H 4205 3577 50  0000 C CNN
F 2 "" H 4200 3750 50  0001 C CNN
F 3 "" H 4200 3750 50  0001 C CNN
	1    4200 3750
	1    0    0    -1  
$EndComp
NoConn ~ 5175 3775
Wire Wire Line
	5775 6875 5675 6875
$Comp
L power:GND #PWR0114
U 1 1 62F1CC44
P 6225 6900
F 0 "#PWR0114" H 6225 6650 50  0001 C CNN
F 1 "GND" H 6230 6727 50  0000 C CNN
F 2 "" H 6225 6900 50  0001 C CNN
F 3 "" H 6225 6900 50  0001 C CNN
	1    6225 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5775 6875 6225 6875
Wire Wire Line
	6225 6875 6225 6900
Connection ~ 5775 6875
Wire Wire Line
	9100 11150 9100 3175
Wire Wire Line
	9100 3175 6375 3175
Wire Wire Line
	9150 11100 9150 3275
Wire Wire Line
	9150 3275 6375 3275
Wire Wire Line
	9200 11050 9200 3375
Wire Wire Line
	9200 3375 6375 3375
Wire Wire Line
	9250 11000 9250 3475
Wire Wire Line
	9250 3475 6375 3475
Wire Wire Line
	9300 10950 9300 3575
Wire Wire Line
	9300 3575 6375 3575
Wire Wire Line
	9350 10900 9350 3675
Wire Wire Line
	9350 3675 6375 3675
Wire Wire Line
	9400 10850 9400 3775
Wire Wire Line
	9400 3775 6375 3775
Wire Wire Line
	9450 10800 9450 3875
Wire Wire Line
	9450 3875 6375 3875
Wire Wire Line
	11600 5975 11600 5400
Connection ~ 11600 5400
Wire Wire Line
	6375 5975 11600 5975
Wire Wire Line
	11600 3200 11600 5400
Wire Wire Line
	11775 6175 11775 5800
Wire Wire Line
	11775 5800 12000 5800
Wire Wire Line
	6375 6175 11775 6175
Wire Wire Line
	11725 6075 11725 3600
Wire Wire Line
	11725 3600 12000 3600
Wire Wire Line
	6375 6075 11725 6075
Wire Wire Line
	11650 5300 11650 5875
Connection ~ 11650 5300
Wire Wire Line
	6375 5875 11650 5875
Wire Wire Line
	11650 3100 11650 5300
Wire Wire Line
	9700 10550 9700 4475
Wire Wire Line
	9700 4475 6375 4475
Wire Wire Line
	9750 10500 9750 4575
Wire Wire Line
	9750 4575 6375 4575
Wire Wire Line
	9800 10450 9800 4675
Wire Wire Line
	9800 4675 6375 4675
Wire Wire Line
	9850 10400 9850 4775
Wire Wire Line
	9850 4775 6375 4775
Wire Wire Line
	9900 10350 9900 4975
Wire Wire Line
	9950 10300 9950 5075
Wire Wire Line
	10000 10250 10000 5175
Wire Wire Line
	10050 10200 10050 5275
Wire Wire Line
	10100 10150 10100 5375
Wire Wire Line
	10150 10100 10150 5475
Wire Wire Line
	10200 10050 10200 5575
Wire Wire Line
	9900 4975 6375 4975
Wire Wire Line
	9950 5075 6375 5075
Wire Wire Line
	10000 5175 6375 5175
Wire Wire Line
	10050 5275 6375 5275
Wire Wire Line
	10100 5375 6375 5375
Wire Wire Line
	10150 5475 6375 5475
Wire Wire Line
	10200 5575 6375 5575
Wire Wire Line
	9500 10750 9500 4375
Wire Wire Line
	9500 4375 6950 4375
Wire Wire Line
	9550 10700 9550 4275
Wire Wire Line
	9550 4275 6900 4275
Wire Wire Line
	9600 10650 9600 4175
Wire Wire Line
	9600 4175 6850 4175
Wire Wire Line
	9650 10600 9650 4075
Wire Wire Line
	9650 4075 6375 4075
$Comp
L Display_Character:SLR0363DWC1BD U4
U 1 1 63417190
P 16225 4225
F 0 "U4" H 16175 4842 50  0000 C CNN
F 1 "SLR0363DWC1BD" H 16175 4751 50  0000 C CNN
F 2 "simpanel:SLR0363DWC1BD" H 16175 4725 50  0001 C CNN
F 3 "" H 16175 4725 50  0001 C CNN
	1    16225 4225
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:SLR0363DWC1BD U6
U 1 1 6341B94D
P 19900 4200
F 0 "U6" H 19850 4817 50  0000 C CNN
F 1 "SLR0363DWC1BD" H 19850 4726 50  0000 C CNN
F 2 "simpanel:SLR0363DWC1BD" H 19850 4700 50  0001 C CNN
F 3 "" H 19850 4700 50  0001 C CNN
	1    19900 4200
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:SLR0363DWC1BD U5
U 1 1 634832BD
P 16250 5450
F 0 "U5" H 16200 6067 50  0000 C CNN
F 1 "SLR0363DWC1BD" H 16200 5976 50  0000 C CNN
F 2 "simpanel:SLR0363DWC1BD" H 16200 5950 50  0001 C CNN
F 3 "" H 16200 5950 50  0001 C CNN
	1    16250 5450
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:SLR0363DWC1BD U7
U 1 1 634832C3
P 19925 5425
F 0 "U7" H 19875 6042 50  0000 C CNN
F 1 "SLR0363DWC1BD" H 19875 5951 50  0000 C CNN
F 2 "simpanel:SLR0363DWC1BD" H 19875 5925 50  0001 C CNN
F 3 "" H 19875 5925 50  0001 C CNN
	1    19925 5425
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:SLR0363DWC1BD U8
U 1 1 634A62BF
P 16250 7500
F 0 "U8" H 16200 8117 50  0000 C CNN
F 1 "SLR0363DWC1BD" H 16200 8026 50  0000 C CNN
F 2 "simpanel:SLR0363DWC1BD" H 16200 8000 50  0001 C CNN
F 3 "" H 16200 8000 50  0001 C CNN
	1    16250 7500
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:SLR0363DWC1BD U9
U 1 1 634A62C5
P 19925 7475
F 0 "U9" H 19875 8092 50  0000 C CNN
F 1 "SLR0363DWC1BD" H 19875 8001 50  0000 C CNN
F 2 "simpanel:SLR0363DWC1BD" H 19875 7975 50  0001 C CNN
F 3 "" H 19875 7975 50  0001 C CNN
	1    19925 7475
	1    0    0    -1  
$EndComp
Wire Wire Line
	20950 4350 21025 4350
Wire Wire Line
	13050 2950 13050 3100
Wire Wire Line
	13050 3100 13000 3100
Wire Wire Line
	13000 3200 13100 3200
Wire Wire Line
	13100 3200 13100 3000
Wire Wire Line
	13100 3000 14900 3000
Wire Wire Line
	18650 3000 18650 4050
Wire Wire Line
	18650 4050 18750 4050
Wire Wire Line
	18750 3950 18700 3950
Wire Wire Line
	18700 3950 18700 2950
Wire Wire Line
	13050 2950 14950 2950
Wire Wire Line
	13000 3300 13150 3300
Wire Wire Line
	13150 3300 13150 3050
Wire Wire Line
	13150 3050 14850 3050
Wire Wire Line
	18600 3050 18600 4150
Wire Wire Line
	18600 4150 18750 4150
Wire Wire Line
	13000 3400 13200 3400
Wire Wire Line
	13200 3400 13200 3100
Wire Wire Line
	18550 3100 18550 4250
Wire Wire Line
	18550 4250 18750 4250
Wire Wire Line
	13000 3500 13250 3500
Wire Wire Line
	13250 3500 13250 3150
Wire Wire Line
	13250 3150 14750 3150
Wire Wire Line
	18500 3150 18500 4350
Wire Wire Line
	18500 4350 18750 4350
Wire Wire Line
	13000 3600 13300 3600
Wire Wire Line
	13300 3600 13300 3200
Wire Wire Line
	13300 3200 14700 3200
Wire Wire Line
	18450 3200 18450 4450
Wire Wire Line
	18450 4450 18750 4450
Wire Wire Line
	17275 4375 17325 4375
Wire Wire Line
	17325 4375 17325 2950
Connection ~ 17325 2950
Wire Wire Line
	17325 2950 18700 2950
Wire Wire Line
	17275 4475 17375 4475
Wire Wire Line
	17375 4475 17375 3000
Connection ~ 17375 3000
Wire Wire Line
	17375 3000 18650 3000
Wire Wire Line
	17275 4575 17425 4575
Wire Wire Line
	17425 4575 17425 3050
Connection ~ 17425 3050
Wire Wire Line
	17425 3050 18600 3050
Wire Wire Line
	13200 3100 14800 3100
Wire Wire Line
	17300 5600 17475 5600
Wire Wire Line
	17475 5600 17475 3100
Connection ~ 17475 3100
Wire Wire Line
	17475 3100 18550 3100
Wire Wire Line
	17300 5700 17525 5700
Wire Wire Line
	17525 5700 17525 3150
Connection ~ 17525 3150
Wire Wire Line
	17525 3150 18500 3150
Wire Wire Line
	17300 5800 17575 5800
Wire Wire Line
	17575 5800 17575 3200
Connection ~ 17575 3200
Wire Wire Line
	17575 3200 18450 3200
Wire Wire Line
	21025 4350 21025 3250
Wire Wire Line
	13350 3250 13350 3700
Wire Wire Line
	13350 3700 13000 3700
Wire Wire Line
	20950 4450 21075 4450
Wire Wire Line
	21075 4450 21075 3300
Wire Wire Line
	21075 3300 18350 3300
Wire Wire Line
	13400 3300 13400 3800
Wire Wire Line
	13400 3800 13000 3800
Wire Wire Line
	20950 4550 21125 4550
Wire Wire Line
	21125 4550 21125 3350
Wire Wire Line
	21125 3350 14550 3350
Wire Wire Line
	13450 3350 13450 3900
Wire Wire Line
	13450 3900 13000 3900
Wire Wire Line
	20975 5575 21175 5575
Wire Wire Line
	21175 5575 21175 3400
Wire Wire Line
	21175 3400 18300 3400
Wire Wire Line
	13500 3400 13500 4000
Wire Wire Line
	13500 4000 13000 4000
Wire Wire Line
	20975 5675 21225 5675
Wire Wire Line
	21225 5675 21225 3450
Wire Wire Line
	21225 3450 18250 3450
Wire Wire Line
	13550 3450 13550 4100
Wire Wire Line
	13550 4100 13000 4100
Wire Wire Line
	20975 5775 21275 5775
Wire Wire Line
	21275 5775 21275 3500
Wire Wire Line
	21275 3500 13600 3500
Wire Wire Line
	13600 3500 13600 4200
Wire Wire Line
	13600 4200 13000 4200
Wire Wire Line
	18700 3950 18700 5175
Wire Wire Line
	18700 5175 18775 5175
Connection ~ 18700 3950
Wire Wire Line
	18650 4050 18650 5275
Wire Wire Line
	18650 5275 18775 5275
Connection ~ 18650 4050
Wire Wire Line
	18600 4150 18600 5375
Wire Wire Line
	18600 5375 18775 5375
Connection ~ 18600 4150
Wire Wire Line
	18550 4250 18550 5475
Wire Wire Line
	18550 5475 18775 5475
Connection ~ 18550 4250
Wire Wire Line
	18500 4350 18500 5575
Wire Wire Line
	18500 5575 18775 5575
Connection ~ 18500 4350
Wire Wire Line
	18450 4450 18450 5675
Wire Wire Line
	18450 5675 18775 5675
Connection ~ 18450 4450
Wire Wire Line
	15100 5200 14950 5200
Wire Wire Line
	14950 5200 14950 2950
Connection ~ 14950 2950
Wire Wire Line
	14950 2950 17325 2950
Wire Wire Line
	14900 3000 14900 5300
Wire Wire Line
	14900 5300 15100 5300
Connection ~ 14900 3000
Wire Wire Line
	14900 3000 17375 3000
Wire Wire Line
	14850 3050 14850 5400
Wire Wire Line
	14850 5400 15100 5400
Connection ~ 14850 3050
Wire Wire Line
	14850 3050 17425 3050
Wire Wire Line
	14800 3100 14800 3975
Wire Wire Line
	14800 3975 15075 3975
Connection ~ 14800 3100
Wire Wire Line
	14800 3100 17475 3100
Wire Wire Line
	14750 3150 14750 4075
Wire Wire Line
	14750 4075 15075 4075
Connection ~ 14750 3150
Wire Wire Line
	14750 3150 17525 3150
Wire Wire Line
	14700 3200 14700 4175
Wire Wire Line
	14700 4175 15075 4175
Connection ~ 14700 3200
Wire Wire Line
	14700 3200 17575 3200
Wire Wire Line
	21025 3250 18400 3250
Wire Wire Line
	14650 3250 14650 4275
Wire Wire Line
	14650 4275 15075 4275
Connection ~ 14650 3250
Wire Wire Line
	14650 3250 13350 3250
Wire Wire Line
	14600 3300 14600 4375
Wire Wire Line
	14600 4375 15075 4375
Connection ~ 14600 3300
Wire Wire Line
	14600 3300 13400 3300
Wire Wire Line
	14550 3350 14550 4475
Wire Wire Line
	14550 4475 15075 4475
Connection ~ 14550 3350
Wire Wire Line
	14550 3350 13450 3350
Wire Wire Line
	14500 3400 14500 4575
Wire Wire Line
	14500 4575 15075 4575
Connection ~ 14500 3400
Wire Wire Line
	14500 3400 13500 3400
Wire Wire Line
	14450 3450 14450 4675
Wire Wire Line
	14450 4675 15075 4675
Connection ~ 14450 3450
Wire Wire Line
	14450 3450 13550 3450
Wire Wire Line
	14500 4575 14500 5800
Wire Wire Line
	14500 5800 15100 5800
Connection ~ 14500 4575
Wire Wire Line
	14450 4675 14450 5900
Wire Wire Line
	14450 5900 15100 5900
Connection ~ 14450 4675
Wire Wire Line
	18400 3250 18400 5775
Wire Wire Line
	18400 5775 18775 5775
Connection ~ 18400 3250
Wire Wire Line
	18400 3250 14650 3250
Wire Wire Line
	18350 3300 18350 5875
Wire Wire Line
	18350 5875 18775 5875
Connection ~ 18350 3300
Wire Wire Line
	18350 3300 14600 3300
Wire Wire Line
	18300 3400 18300 4550
Wire Wire Line
	18300 4550 18750 4550
Connection ~ 18300 3400
Wire Wire Line
	18300 3400 14500 3400
Wire Wire Line
	18250 3450 18250 4650
Wire Wire Line
	18250 4650 18750 4650
Connection ~ 18250 3450
Wire Wire Line
	18250 3450 14450 3450
Wire Wire Line
	13000 5300 14400 5300
Wire Wire Line
	14400 5300 14400 6250
Wire Wire Line
	14400 6250 17375 6250
Wire Wire Line
	18700 6250 18700 7225
Wire Wire Line
	18700 7225 18775 7225
Wire Wire Line
	13000 5400 14350 5400
Wire Wire Line
	14350 5400 14350 6300
Wire Wire Line
	14350 6300 17425 6300
Wire Wire Line
	18650 6300 18650 7325
Wire Wire Line
	18650 7325 18775 7325
Wire Wire Line
	13000 5500 14300 5500
Wire Wire Line
	14300 5500 14300 6350
Wire Wire Line
	14300 6350 17475 6350
Wire Wire Line
	18600 6350 18600 7425
Wire Wire Line
	18600 7425 18775 7425
Wire Wire Line
	13000 5600 14250 5600
Wire Wire Line
	14250 5600 14250 6400
Wire Wire Line
	21050 6400 21050 7625
Wire Wire Line
	21050 7625 20975 7625
Wire Wire Line
	13000 5700 14200 5700
Wire Wire Line
	14200 5700 14200 6450
Wire Wire Line
	21100 6450 21100 7725
Wire Wire Line
	21100 7725 20975 7725
Wire Wire Line
	13000 5800 14150 5800
Wire Wire Line
	14150 5800 14150 6500
Wire Wire Line
	21150 6500 21150 7825
Wire Wire Line
	21150 7825 20975 7825
Wire Wire Line
	13000 5900 14100 5900
Wire Wire Line
	14100 5900 14100 6550
Wire Wire Line
	14100 6550 14875 6550
Wire Wire Line
	18550 6550 18550 7525
Wire Wire Line
	18550 7525 18775 7525
Wire Wire Line
	13000 6000 14050 6000
Wire Wire Line
	14050 6000 14050 6600
Wire Wire Line
	14050 6600 14825 6600
Wire Wire Line
	18500 6600 18500 7625
Wire Wire Line
	18500 7625 18775 7625
Wire Wire Line
	13000 6100 14000 6100
Wire Wire Line
	14000 6100 14000 6650
Wire Wire Line
	14000 6650 14775 6650
Wire Wire Line
	18450 6650 18450 7725
Wire Wire Line
	18450 7725 18775 7725
Wire Wire Line
	13000 6200 13950 6200
Wire Wire Line
	13950 6200 13950 6700
Wire Wire Line
	13950 6700 14725 6700
Wire Wire Line
	18400 6700 18400 7825
Wire Wire Line
	18400 7825 18775 7825
Wire Wire Line
	13000 6300 13900 6300
Wire Wire Line
	13900 6300 13900 6750
Wire Wire Line
	13900 6750 14675 6750
Wire Wire Line
	18350 6750 18350 7925
Wire Wire Line
	18350 7925 18775 7925
Wire Wire Line
	14150 6500 14925 6500
Wire Wire Line
	14200 6450 14975 6450
Wire Wire Line
	14250 6400 15025 6400
Wire Wire Line
	17300 7650 17375 7650
Wire Wire Line
	17375 7650 17375 6250
Connection ~ 17375 6250
Wire Wire Line
	17375 6250 18700 6250
Wire Wire Line
	17300 7750 17425 7750
Wire Wire Line
	17425 7750 17425 6300
Connection ~ 17425 6300
Wire Wire Line
	17425 6300 18650 6300
Wire Wire Line
	17300 7850 17475 7850
Wire Wire Line
	17475 7850 17475 6350
Connection ~ 17475 6350
Wire Wire Line
	17475 6350 18600 6350
Wire Wire Line
	15100 7250 15025 7250
Wire Wire Line
	15025 7250 15025 6400
Connection ~ 15025 6400
Wire Wire Line
	15025 6400 17525 6400
Wire Wire Line
	15100 7350 14975 7350
Wire Wire Line
	14975 7350 14975 6450
Connection ~ 14975 6450
Wire Wire Line
	14975 6450 17575 6450
Wire Wire Line
	15100 7450 14925 7450
Wire Wire Line
	14925 7450 14925 6500
Connection ~ 14925 6500
Wire Wire Line
	14925 6500 17625 6500
Wire Wire Line
	15100 7550 14875 7550
Wire Wire Line
	14875 7550 14875 6550
Connection ~ 14875 6550
Wire Wire Line
	14875 6550 17675 6550
Wire Wire Line
	15100 7650 14825 7650
Wire Wire Line
	14825 7650 14825 6600
Connection ~ 14825 6600
Wire Wire Line
	14825 6600 17725 6600
Wire Wire Line
	15100 7750 14775 7750
Wire Wire Line
	14775 7750 14775 6650
Connection ~ 14775 6650
Wire Wire Line
	14775 6650 17775 6650
Wire Wire Line
	15100 7850 14725 7850
Wire Wire Line
	14725 7850 14725 6700
Connection ~ 14725 6700
Wire Wire Line
	14725 6700 17825 6700
Wire Wire Line
	15100 7950 14675 7950
Wire Wire Line
	14675 7950 14675 6750
Connection ~ 14675 6750
Wire Wire Line
	14675 6750 17875 6750
Wire Wire Line
	16900 11400 17150 11400
Wire Wire Line
	17150 11400 17150 10700
Wire Wire Line
	16900 10700 17150 10700
Connection ~ 17150 10700
Wire Wire Line
	17150 10700 17150 10050
Wire Wire Line
	16900 10050 17150 10050
Connection ~ 17150 10050
Wire Wire Line
	17150 10050 17150 9425
Wire Wire Line
	16900 11300 17100 11300
Wire Wire Line
	16900 10600 17050 10600
Wire Wire Line
	16900 9950 17000 9950
Wire Wire Line
	18700 12000 19000 12000
Wire Wire Line
	19000 12000 19000 11350
Wire Wire Line
	17150 9425 19000 9425
Wire Wire Line
	18700 11900 18950 11900
Wire Wire Line
	18700 11350 19000 11350
Connection ~ 19000 11350
Wire Wire Line
	19000 11350 19000 10700
Wire Wire Line
	18700 10700 19000 10700
Connection ~ 19000 10700
Wire Wire Line
	19000 10700 19000 10050
Wire Wire Line
	18700 10050 19000 10050
Connection ~ 19000 10050
Wire Wire Line
	19000 10050 19000 9425
Wire Wire Line
	18700 11250 18900 11250
Wire Wire Line
	18700 10600 18850 10600
Wire Wire Line
	18700 9950 18800 9950
Wire Wire Line
	18800 9950 18800 9375
Wire Wire Line
	20550 9950 20650 9950
Wire Wire Line
	20550 10600 20700 10600
Wire Wire Line
	20550 11250 20750 11250
Wire Wire Line
	20550 11900 20800 11900
Wire Wire Line
	19000 9425 20850 9425
Wire Wire Line
	20850 9425 20850 10050
Wire Wire Line
	20850 12000 20550 12000
Connection ~ 19000 9425
Wire Wire Line
	20550 11350 20850 11350
Connection ~ 20850 11350
Wire Wire Line
	20850 11350 20850 12000
Wire Wire Line
	20525 10700 20550 10700
Connection ~ 20850 10700
Wire Wire Line
	20850 10700 20850 11350
Connection ~ 20550 10700
Wire Wire Line
	20550 10700 20850 10700
Wire Wire Line
	20550 10050 20850 10050
Connection ~ 20850 10050
Wire Wire Line
	20850 10050 20850 10700
Wire Wire Line
	17475 7850 17475 9375
Wire Wire Line
	17475 9375 17100 9375
Wire Wire Line
	17100 9375 17100 11300
Connection ~ 17475 7850
Wire Wire Line
	17425 7750 17425 9325
Wire Wire Line
	17425 9325 17050 9325
Wire Wire Line
	17050 9325 17050 10600
Connection ~ 17425 7750
Wire Wire Line
	17375 7650 17375 9275
Wire Wire Line
	17375 9275 17000 9275
Wire Wire Line
	17000 9275 17000 9950
Connection ~ 17375 7650
Wire Wire Line
	17525 6400 17525 9375
Wire Wire Line
	17525 9375 18800 9375
Connection ~ 17525 6400
Wire Wire Line
	17525 6400 21050 6400
Wire Wire Line
	17575 6450 17575 9325
Wire Wire Line
	17575 9325 18850 9325
Wire Wire Line
	18850 9325 18850 10600
Connection ~ 17575 6450
Wire Wire Line
	17575 6450 21100 6450
Wire Wire Line
	17625 6500 17625 9275
Wire Wire Line
	17625 9275 18900 9275
Wire Wire Line
	18900 9275 18900 11250
Connection ~ 17625 6500
Wire Wire Line
	17625 6500 21150 6500
Wire Wire Line
	17675 6550 17675 9225
Wire Wire Line
	17675 9225 18950 9225
Wire Wire Line
	18950 9225 18950 11900
Connection ~ 17675 6550
Wire Wire Line
	17675 6550 18550 6550
Wire Wire Line
	17725 6600 17725 9175
Wire Wire Line
	17725 9175 20650 9175
Wire Wire Line
	20650 9175 20650 9950
Connection ~ 17725 6600
Wire Wire Line
	17725 6600 18500 6600
Wire Wire Line
	17775 6650 17775 9125
Wire Wire Line
	17775 9125 20700 9125
Wire Wire Line
	20700 9125 20700 10600
Connection ~ 17775 6650
Wire Wire Line
	17775 6650 18450 6650
Wire Wire Line
	17825 6700 17825 9075
Wire Wire Line
	17825 9075 20750 9075
Wire Wire Line
	20750 9075 20750 11250
Connection ~ 17825 6700
Wire Wire Line
	17825 6700 18400 6700
Wire Wire Line
	17875 6750 17875 9025
Wire Wire Line
	17875 9025 20800 9025
Wire Wire Line
	20800 9025 20800 11900
Connection ~ 17875 6750
Wire Wire Line
	17875 6750 18350 6750
Wire Wire Line
	17150 9425 13850 9425
Wire Wire Line
	13850 9425 13850 6400
Wire Wire Line
	13850 6400 13000 6400
Connection ~ 17150 9425
$Comp
L Connector_Generic:Conn_2Rows-21Pins J2
U 1 1 660E41F3
P 4375 7525
F 0 "J2" H 4425 8150 50  0000 C CNN
F 1 "Conn_2Rows-21Pins" H 4425 8151 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x11_P2.54mm_Vertical" H 4375 7525 50  0001 C CNN
F 3 "~" H 4375 7525 50  0001 C CNN
	1    4375 7525
	1    0    0    -1  
$EndComp
Wire Wire Line
	6375 6575 6625 6575
Wire Wire Line
	6625 6575 6625 7625
Wire Wire Line
	6625 7625 4675 7625
Wire Wire Line
	6375 6475 6675 6475
Wire Wire Line
	6675 6475 6675 7725
Wire Wire Line
	6675 7725 4675 7725
Wire Wire Line
	6375 6375 6725 6375
Wire Wire Line
	6725 6375 6725 7825
Wire Wire Line
	6725 7825 4675 7825
Wire Wire Line
	6375 6275 6775 6275
Wire Wire Line
	6775 6275 6775 7925
Wire Wire Line
	6775 7925 4675 7925
Wire Wire Line
	4675 7525 5125 7525
Wire Wire Line
	5125 7525 5125 6575
Wire Wire Line
	5125 6575 5175 6575
Wire Wire Line
	4675 7425 5075 7425
Wire Wire Line
	5075 7425 5075 6475
Wire Wire Line
	5075 6475 5175 6475
Wire Wire Line
	4675 7325 5025 7325
Wire Wire Line
	5025 7325 5025 6375
Wire Wire Line
	5025 6375 5175 6375
Wire Wire Line
	4675 7225 4975 7225
Wire Wire Line
	4975 7225 4975 6275
Wire Wire Line
	4975 6275 5175 6275
Wire Wire Line
	4675 7125 4925 7125
Wire Wire Line
	4925 7125 4925 6175
Wire Wire Line
	4925 6175 5175 6175
Wire Wire Line
	4675 7025 4875 7025
Wire Wire Line
	4875 7025 4875 6075
Wire Wire Line
	4875 6075 5175 6075
Wire Wire Line
	4175 7025 4125 7025
Wire Wire Line
	4125 7025 4125 5975
Wire Wire Line
	4125 5975 5175 5975
Wire Wire Line
	5175 5875 4075 5875
Wire Wire Line
	4075 5875 4075 7125
Wire Wire Line
	4075 7125 4175 7125
Wire Wire Line
	4025 5800 4025 7225
Wire Wire Line
	4025 7225 4175 7225
Wire Wire Line
	4175 7325 3975 7325
Wire Wire Line
	4175 7425 3925 7425
Wire Wire Line
	4175 7525 3875 7525
Wire Wire Line
	4175 7625 3825 7625
Wire Wire Line
	4175 7725 3775 7725
Wire Wire Line
	4175 7825 3725 7825
Wire Wire Line
	4175 7925 3675 7925
$Comp
L power:GND #PWR0115
U 1 1 66A553E5
P 3675 8250
F 0 "#PWR0115" H 3675 8000 50  0001 C CNN
F 1 "GND" H 3680 8077 50  0000 C CNN
F 2 "" H 3675 8250 50  0001 C CNN
F 3 "" H 3675 8250 50  0001 C CNN
	1    3675 8250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3675 8250 3675 8025
Wire Wire Line
	3675 8025 4175 8025
Wire Wire Line
	4025 5800 5075 5800
Wire Wire Line
	5075 5800 5075 5675
Wire Wire Line
	5075 5675 5175 5675
Wire Wire Line
	3975 5750 5025 5750
Wire Wire Line
	5025 5750 5025 5575
Wire Wire Line
	5025 5575 5175 5575
Wire Wire Line
	3975 5750 3975 7325
Wire Wire Line
	3925 5700 4975 5700
Wire Wire Line
	4975 5700 4975 5475
Wire Wire Line
	4975 5475 5175 5475
Wire Wire Line
	3925 5700 3925 7425
Wire Wire Line
	3875 5650 4925 5650
Wire Wire Line
	4925 5650 4925 5375
Wire Wire Line
	4925 5375 5175 5375
Wire Wire Line
	3875 5650 3875 7525
Wire Wire Line
	3825 5600 4875 5600
Wire Wire Line
	4875 5600 4875 5275
Wire Wire Line
	4875 5275 5175 5275
Wire Wire Line
	3825 5600 3825 7625
Wire Wire Line
	3775 5550 4825 5550
Wire Wire Line
	4825 5550 4825 5175
Wire Wire Line
	4825 5175 5175 5175
Wire Wire Line
	3775 5550 3775 7725
Wire Wire Line
	3725 5500 4775 5500
Wire Wire Line
	4775 5500 4775 5075
Wire Wire Line
	4775 5075 5175 5075
Wire Wire Line
	3725 5500 3725 7825
Wire Wire Line
	3675 5450 4725 5450
Wire Wire Line
	4725 5450 4725 4975
Wire Wire Line
	4725 4975 5175 4975
Wire Wire Line
	3675 5450 3675 7925
$Comp
L power:VCC #PWR0102
U 1 1 66F920A2
P 11850 4300
F 0 "#PWR0102" H 11850 4150 50  0001 C CNN
F 1 "VCC" H 11865 4473 50  0000 C CNN
F 2 "" H 11850 4300 50  0001 C CNN
F 3 "" H 11850 4300 50  0001 C CNN
	1    11850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	11750 6600 11750 6500
$Comp
L power:VCC #PWR0110
U 1 1 66F943A1
P 11750 6500
F 0 "#PWR0110" H 11750 6350 50  0001 C CNN
F 1 "VCC" H 11765 6673 50  0000 C CNN
F 2 "" H 11750 6500 50  0001 C CNN
F 3 "" H 11750 6500 50  0001 C CNN
	1    11750 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6375 5675 11550 5675
Wire Wire Line
	11550 5675 11550 5600
Connection ~ 11550 5600
$Comp
L Device:C C6
U 1 1 670AF4B8
P 3825 3300
F 0 "C6" H 3940 3346 50  0000 L CNN
F 1 "100nf" H 3940 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3863 3150 50  0001 C CNN
F 3 "~" H 3825 3300 50  0001 C CNN
	1    3825 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3825 3625 4200 3625
Wire Wire Line
	3825 2950 4150 2950
Wire Wire Line
	5075 2950 5075 3175
Wire Wire Line
	5075 3175 5175 3175
Wire Wire Line
	3825 3150 3825 2950
Wire Wire Line
	3825 3450 3825 3625
$Comp
L Switch:SW_Push SW12
U 1 1 67379726
P 3350 3300
F 0 "SW12" V 3396 3252 50  0000 R CNN
F 1 "SW_Push" V 3305 3252 50  0000 R CNN
F 2 "XKB5858-W-C:XKB5858WC" H 3350 3500 50  0001 C CNN
F 3 "~" H 3350 3500 50  0001 C CNN
	1    3350 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3350 3500 3350 3625
Wire Wire Line
	3350 3625 3825 3625
Connection ~ 3825 3625
Wire Wire Line
	3350 3100 3350 2950
Wire Wire Line
	3350 2950 3825 2950
Connection ~ 3825 2950
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 6749D83E
P 2550 3975
F 0 "#FLG0101" H 2550 4050 50  0001 C CNN
F 1 "PWR_FLAG" H 2550 4148 50  0000 C CNN
F 2 "" H 2550 3975 50  0001 C CNN
F 3 "~" H 2550 3975 50  0001 C CNN
	1    2550 3975
	1    0    0    -1  
$EndComp
Text Label 13150 2950 0    50   ~ 0
CSA0
Text Label 13200 3000 0    50   ~ 0
CSA1
Text Label 13250 3050 0    50   ~ 0
CSA2
Text Label 13300 3100 0    50   ~ 0
CSA3
Text Label 13350 3150 0    50   ~ 0
CSA4
Text Label 13400 3200 0    50   ~ 0
CSA5
Text Label 13450 3250 0    50   ~ 0
CSA6
Text Label 13500 3300 0    50   ~ 0
CSA7
Text Label 13550 3350 0    50   ~ 0
CSA8
Text Label 13600 3400 0    50   ~ 0
CSA9
Text Label 13650 3450 0    50   ~ 0
CSA10
Text Label 13700 3500 0    50   ~ 0
CSA11
Text Label 13100 5300 0    50   ~ 0
CSB0
Text Label 13100 5400 0    50   ~ 0
CSB1
Text Label 13100 5500 0    50   ~ 0
CSB2
Text Label 13100 5600 0    50   ~ 0
CSB3
Text Label 13100 5700 0    50   ~ 0
CSB4
Text Label 13100 5800 0    50   ~ 0
CSB5
Text Label 13100 5900 0    50   ~ 0
CSB6
Text Label 13100 6000 0    50   ~ 0
CSB7
Text Label 13100 6100 0    50   ~ 0
CSB8
Text Label 13100 6200 0    50   ~ 0
CSB9
Text Label 13100 6300 0    50   ~ 0
CSB10
Text Label 13100 6400 0    50   ~ 0
CSB11
Text Label 6475 3175 0    50   ~ 0
PA0
Text Label 6475 3275 0    50   ~ 0
PA1
Text Label 6475 3375 0    50   ~ 0
PA2
Text Label 6475 3475 0    50   ~ 0
PA3
Text Label 6475 3575 0    50   ~ 0
PA4
Text Label 6475 3675 0    50   ~ 0
PA5
Text Label 6475 3775 0    50   ~ 0
PA6
Text Label 6475 3875 0    50   ~ 0
PA7
Text Label 6475 4075 0    50   ~ 0
PB0
Text Label 6475 4175 0    50   ~ 0
PB1
Text Label 6475 4275 0    50   ~ 0
PB2
Text Label 6475 4375 0    50   ~ 0
PB3
Text Label 6475 4475 0    50   ~ 0
PB4
Text Label 6475 4575 0    50   ~ 0
PB5
Text Label 6475 4675 0    50   ~ 0
PB6
Text Label 6475 4775 0    50   ~ 0
PB7
Text Label 6475 4975 0    50   ~ 0
PC0
Text Label 6475 5075 0    50   ~ 0
PC1
Text Label 6475 5175 0    50   ~ 0
PC2
Text Label 6475 5275 0    50   ~ 0
PC3
Text Label 6475 5375 0    50   ~ 0
PC4
Text Label 6475 5475 0    50   ~ 0
PC5
Text Label 6475 5575 0    50   ~ 0
PC6
Text Label 6475 5675 0    50   ~ 0
PC7
Text Label 6475 6275 0    50   ~ 0
PD4
Text Label 6475 6375 0    50   ~ 0
PD5
Text Label 6475 6475 0    50   ~ 0
PD6
Text Label 6475 6575 0    50   ~ 0
PD7
Text Label 5075 5675 0    50   ~ 0
PE7
Text Label 5050 5575 0    50   ~ 0
PE6
Text Label 5000 5475 0    50   ~ 0
PE5
Text Label 5000 5375 0    50   ~ 0
PE4
Text Label 5000 5275 0    50   ~ 0
PE3
Text Label 5000 5175 0    50   ~ 0
PE2
Text Label 5000 5075 0    50   ~ 0
PE1
Text Label 5000 4975 0    50   ~ 0
PE0
Text Label 4625 5875 0    50   ~ 0
PF0
Text Label 4625 5975 0    50   ~ 0
PF1
Text Label 4700 7025 0    50   ~ 0
PF2
Text Label 4700 7125 0    50   ~ 0
PF3
Text Label 4700 7225 0    50   ~ 0
PF4
Text Label 4700 7325 0    50   ~ 0
PF5
Text Label 4700 7425 0    50   ~ 0
PF6
Text Label 4700 7525 0    50   ~ 0
PF7
Text Label 11850 5300 0    50   ~ 0
SCL
Text Label 11850 5400 0    50   ~ 0
SDA
Text Label 11825 5800 0    50   ~ 0
IRQB
Text Label 11775 3600 0    50   ~ 0
IRQA
Text Label 11775 3800 0    50   ~ 0
SYNC
Text Label 11775 3400 0    50   ~ 0
RSTN
Text Label 4925 3975 0    50   ~ 0
VBUS
Text Label 4925 4175 0    50   ~ 0
D+
Text Label 4925 4275 0    50   ~ 0
D-
Text Label 4925 4475 0    50   ~ 0
UCAP
Text Label 4825 3625 0    50   ~ 0
XTAL-
Text Label 4825 3325 0    50   ~ 0
XTAL+
Text Label 4825 2950 0    50   ~ 0
RESET
Text Label 1025 5175 0    50   ~ 0
SHIELD
Wire Wire Line
	14550 4475 14550 5700
Wire Wire Line
	14550 5700 15100 5700
Connection ~ 14550 4475
Wire Wire Line
	14600 4375 14600 5600
Wire Wire Line
	14600 5600 15100 5600
Connection ~ 14600 4375
Wire Wire Line
	14650 4275 14650 5500
Wire Wire Line
	14650 5500 15100 5500
Connection ~ 14650 4275
Wire Wire Line
	13000 6900 13100 6900
Connection ~ 13100 6900
Wire Wire Line
	13100 6900 13100 7000
Wire Wire Line
	12000 7000 11750 7000
Wire Wire Line
	11750 7000 11750 6900
Connection ~ 11750 6900
Wire Wire Line
	12000 4800 12000 4700
Connection ~ 12000 4700
Wire Wire Line
	13000 4500 13100 4500
Connection ~ 13100 4500
Wire Wire Line
	13100 4500 13100 4600
$Comp
L MCU_Microchip_AVR:AT90USB1286-AU U1
U 1 1 623A230D
P 5775 4875
F 0 "U1" H 5775 2786 50  0000 C CNN
F 1 "AT90USB1286-AU" H 5775 2695 50  0000 C CNN
F 2 "Package_QFP:TQFP-64_14x14mm_P0.8mm" H 5775 4875 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc7593.pdf" H 5775 4875 50  0001 C CNN
F 4 "C1337544" H 5775 4875 50  0001 C CNN "LCSC"
	1    5775 4875
	1    0    0    -1  
$EndComp
$Comp
L U-F-M5DW-Y-2:U-F-M5DW-Y-2 J1
U 1 1 6246A14F
P 1700 4375
F 0 "J1" H 2150 3710 50  0000 C CNN
F 1 "U-F-M5DW-Y-2" H 2150 3801 50  0000 C CNN
F 2 "U-F-M5DW-Y-2:UFM5DWY2" H 2450 4475 50  0001 L CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1903211730_Korean-Hroparts-Elec-U-F-M5DW-Y-2_C105422.pdf" H 2450 4375 50  0001 L CNN
F 4 "USB Connectors MicroUSBsocket RoHS" H 2450 4275 50  0001 L CNN "Description"
F 5 "3.15" H 2450 4175 50  0001 L CNN "Height"
F 6 "Korean Hroparts Elec" H 2450 4075 50  0001 L CNN "Manufacturer_Name"
F 7 "U-F-M5DW-Y-2" H 2450 3975 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 2450 3875 50  0001 L CNN "Mouser Part Number"
F 9 "" H 2450 3775 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 2450 3675 50  0001 L CNN "Arrow Part Number"
F 11 "" H 2450 3575 50  0001 L CNN "Arrow Price/Stock"
F 12 "C105422" H 1700 4375 50  0001 C CNN "LCSC"
	1    1700 4375
	-1   0    0    1   
$EndComp
Text Label 2150 4175 0    50   ~ 0
UD+
Text Label 2150 4275 0    50   ~ 0
UD-
Wire Wire Line
	2550 4375 2550 3975
Wire Wire Line
	2400 4700 2550 4700
Wire Wire Line
	2550 4700 2550 5175
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J3
U 1 1 60FC71E7
P 4650 2000
F 0 "J3" H 4700 2317 50  0000 C CNN
F 1 "ISP" H 4700 2226 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 4650 2000 50  0001 C CNN
F 3 "~" H 4650 2000 50  0001 C CNN
	1    4650 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1900 5375 1900
Wire Wire Line
	5375 1900 5375 2725
Wire Wire Line
	5375 2800 5675 2800
Wire Wire Line
	4450 2100 4150 2100
Wire Wire Line
	4150 2100 4150 2725
Connection ~ 4150 2950
Wire Wire Line
	4150 2950 5075 2950
Wire Wire Line
	6850 4175 6850 2375
Wire Wire Line
	6850 2375 4200 2375
Wire Wire Line
	4200 2375 4200 2000
Wire Wire Line
	4200 2000 4450 2000
Connection ~ 6850 4175
Wire Wire Line
	6850 4175 6375 4175
Wire Wire Line
	6900 4275 6900 2000
Wire Wire Line
	6900 2000 4950 2000
Connection ~ 6900 4275
Wire Wire Line
	6900 4275 6375 4275
Wire Wire Line
	4450 1900 4250 1900
Wire Wire Line
	4250 1900 4250 2425
Wire Wire Line
	4250 2425 6950 2425
Wire Wire Line
	6950 2425 6950 4375
Connection ~ 6950 4375
Wire Wire Line
	6950 4375 6375 4375
Wire Wire Line
	4950 2100 5050 2100
$Comp
L power:GND #PWR0116
U 1 1 6137190A
P 5050 2100
F 0 "#PWR0116" H 5050 1850 50  0001 C CNN
F 1 "GND" H 5055 1927 50  0000 C CNN
F 2 "" H 5050 2100 50  0001 C CNN
F 3 "" H 5050 2100 50  0001 C CNN
	1    5050 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R5
U 1 1 613725CA
P 4775 2725
F 0 "R5" V 4570 2725 50  0000 C CNN
F 1 "10k" V 4661 2725 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4815 2715 50  0001 C CNN
F 3 "~" H 4775 2725 50  0001 C CNN
	1    4775 2725
	0    1    1    0   
$EndComp
Wire Wire Line
	4925 2725 5375 2725
Connection ~ 5375 2725
Wire Wire Line
	5375 2725 5375 2800
Wire Wire Line
	4625 2725 4150 2725
Connection ~ 4150 2725
Wire Wire Line
	4150 2725 4150 2950
Wire Wire Line
	2550 4375 2775 4375
Wire Wire Line
	2775 4375 2775 4775
Connection ~ 2775 4375
Wire Wire Line
	2775 4375 3400 4375
Wire Wire Line
	3225 4775 3700 4775
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 6161E760
P 2550 4700
F 0 "#FLG0102" H 2550 4775 50  0001 C CNN
F 1 "PWR_FLAG" H 2550 4873 50  0000 C CNN
F 2 "" H 2550 4700 50  0001 C CNN
F 3 "~" H 2550 4700 50  0001 C CNN
	1    2550 4700
	1    0    0    -1  
$EndComp
Connection ~ 2550 4700
Wire Wire Line
	1775 4275 1700 4275
Connection ~ 1775 4275
Wire Wire Line
	2400 3975 1700 3975
Wire Wire Line
	2400 3975 2400 4700
Wire Wire Line
	2550 4375 1700 4375
Connection ~ 2550 4375
$EndSCHEMATC
