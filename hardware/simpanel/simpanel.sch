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
$Comp
L eec:AS1130-BSST U1
U 1 1 5FD03C01
P 11850 3250
F 0 "U1" H 12450 3515 50  0000 C CNN
F 1 "AS1130-BSST" H 12450 3424 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 11850 3650 50  0001 L CNN
F 3 "http://www.ams.com/eng/content/download/185846/834724/105034" H 11850 3750 50  0001 L CNN
F 4 "MO-150" H 11850 3850 50  0001 L CNN "Code  JEDEC"
F 5 "Manufacturer URL" H 11850 3950 50  0001 L CNN "Component Link 1 Description"
F 6 "www.ams.com" H 11850 4050 50  0001 L CNN "Component Link 1 URL"
F 7 "Rev. 1.07" H 11850 4150 50  0001 L CNN "Datasheet Version"
F 8 "true" H 11850 4250 50  0001 L CNN "Error Detection"
F 9 "8-bit PWM & analog current control, dynamic headroom control" H 11850 4350 50  0001 L CNN "Features"
F 10 "2.5" H 11850 4450 50  0001 L CNN "LED Current per Output mA"
F 11 "2" H 11850 4550 50  0001 L CNN "LED to LED Matching "
F 12 "Surface Mount" H 11850 4650 50  0001 L CNN "Mounting Technology"
F 13 "132" H 11850 4750 50  0001 L CNN "Outputs"
F 14 "28-Pin Shrink Small Outline Package, 10.2 x 5.3 mm Body, 0.65 mm Pitch" H 11850 4850 50  0001 L CNN "Package Description"
F 15 "N/C, 07/2011" H 11850 4950 50  0001 L CNN "Package Version"
F 16 "true" H 11850 5050 50  0001 L CNN "Read back"
F 17 "2.7 to 5.5" H 11850 5150 50  0001 L CNN "Supply Voltage V"
F 18 "IC" H 11850 5250 50  0001 L CNN "category"
F 19 "4367283" H 11850 5350 50  0001 L CNN "ciiva ids"
F 20 "598dcdd5055ccc55" H 11850 5450 50  0001 L CNN "library id"
F 21 "AMS" H 11850 5550 50  0001 L CNN "manufacturer"
F 22 "SSOP-28" H 11850 5650 50  0001 L CNN "package"
F 23 "1394513892" H 11850 5750 50  0001 L CNN "release date"
F 24 "660BAB0B-1A30-45A6-8177-846E59C4C6EC" H 11850 5850 50  0001 L CNN "vault revision"
F 25 "yes" H 11850 5950 50  0001 L CNN "imported"
	1    11850 3250
	1    0    0    -1  
$EndComp
Connection ~ 22650 10000
Wire Wire Line
	22650 11250 22650 10000
Wire Wire Line
	22200 11250 22650 11250
Connection ~ 22650 8050
Wire Wire Line
	22650 10000 22650 8050
Wire Wire Line
	22200 10000 22650 10000
Wire Wire Line
	22200 10950 22200 10850
Wire Wire Line
	22200 9700 22200 9600
Connection ~ 22600 9400
Wire Wire Line
	22600 10650 22600 9400
Wire Wire Line
	22200 10650 22600 10650
Connection ~ 22600 8150
Wire Wire Line
	22600 9400 22600 8150
Wire Wire Line
	22200 9400 22600 9400
Wire Wire Line
	20000 9500 20000 8250
Connection ~ 20000 9500
Wire Wire Line
	20400 9500 20000 9500
Wire Wire Line
	19950 9700 19950 8450
Connection ~ 19950 9700
Wire Wire Line
	20400 9700 19950 9700
Wire Wire Line
	19900 9800 19900 8550
Connection ~ 19900 9800
Wire Wire Line
	20400 9800 19900 9800
Connection ~ 20000 8250
Wire Wire Line
	20000 10750 20000 9500
Wire Wire Line
	20400 10750 20000 10750
Connection ~ 19950 8450
Wire Wire Line
	19950 10950 19950 9700
Wire Wire Line
	20400 10950 19950 10950
Connection ~ 19900 10500
Wire Wire Line
	19900 11050 19900 10500
Wire Wire Line
	20400 11050 19900 11050
Connection ~ 19700 9300
Wire Wire Line
	19700 10550 19700 9300
Wire Wire Line
	20400 10550 19700 10550
Connection ~ 19700 8050
Wire Wire Line
	19700 9300 19700 8050
Wire Wire Line
	20400 9300 19700 9300
Connection ~ 19650 9400
Wire Wire Line
	19650 10650 19650 9400
Wire Wire Line
	20400 10650 19650 10650
Wire Wire Line
	19600 11000 19800 11000
Wire Wire Line
	19600 10600 20100 10600
Wire Wire Line
	19600 10500 19900 10500
Wire Wire Line
	19600 10700 19750 10700
Wire Wire Line
	17800 10700 17350 10700
Wire Wire Line
	17800 10900 17300 10900
Wire Wire Line
	17800 11000 17250 11000
Connection ~ 17800 11200
Wire Wire Line
	17800 11200 17150 11200
Wire Wire Line
	17800 10500 17000 10500
Wire Wire Line
	17800 10600 16950 10600
Wire Wire Line
	17300 9650 17300 10900
Wire Wire Line
	17250 9750 17250 11000
Wire Wire Line
	16950 9350 16950 10600
Connection ~ 19650 8150
Wire Wire Line
	19650 9400 19650 8150
Wire Wire Line
	20400 9400 19650 9400
Wire Wire Line
	20400 10100 20400 10000
Wire Wire Line
	20400 11350 20400 11250
Connection ~ 22750 8350
Connection ~ 22200 8350
Wire Wire Line
	22200 8350 22750 8350
Wire Wire Line
	22700 8750 22700 9300
Connection ~ 22700 8750
Wire Wire Line
	22700 7500 22700 8750
Wire Wire Line
	22200 8750 22700 8750
Connection ~ 22600 6800
Wire Wire Line
	22600 8150 22600 6800
Wire Wire Line
	22200 8150 22600 8150
Connection ~ 20000 7000
Wire Wire Line
	20000 8250 20000 7000
Wire Wire Line
	20400 8250 20000 8250
Connection ~ 19950 7200
Wire Wire Line
	19950 8450 19950 7200
Wire Wire Line
	20400 8450 19950 8450
Wire Wire Line
	19900 8550 19900 7300
Connection ~ 19900 8550
Wire Wire Line
	20400 8550 19900 8550
Wire Wire Line
	19850 8500 19850 8750
Wire Wire Line
	19850 8750 19850 9250
Connection ~ 19850 8750
Connection ~ 20400 8750
Wire Wire Line
	20400 8750 19850 8750
Connection ~ 22350 7300
Wire Wire Line
	22350 8550 22350 7300
Wire Wire Line
	22200 8550 22350 8550
Connection ~ 22300 7000
Wire Wire Line
	22300 8250 22300 7000
Wire Wire Line
	22200 8250 22300 8250
Connection ~ 19700 6800
Wire Wire Line
	19700 8050 19700 6800
Wire Wire Line
	20400 8050 19700 8050
Connection ~ 19650 6900
Wire Wire Line
	19650 8150 19650 6900
Wire Wire Line
	20400 8150 19650 8150
Wire Wire Line
	22200 8450 22200 8350
Wire Wire Line
	20400 8850 20400 8750
Wire Wire Line
	22750 7100 22750 8350
Connection ~ 22750 7100
Connection ~ 22200 7100
Wire Wire Line
	22200 7100 22750 7100
Connection ~ 22700 7500
Wire Wire Line
	22700 6250 22700 7500
Wire Wire Line
	22200 7500 22700 7500
Wire Wire Line
	22650 6900 22650 8050
Connection ~ 22650 6900
Wire Wire Line
	22200 6900 22650 6900
Connection ~ 20000 4700
Wire Wire Line
	20000 7000 20000 4700
Wire Wire Line
	20400 7000 20000 7000
Connection ~ 19950 5950
Wire Wire Line
	19950 7200 19950 5950
Wire Wire Line
	20400 7200 19950 7200
Wire Wire Line
	19900 7300 19900 6050
Connection ~ 19900 7300
Wire Wire Line
	20400 7300 19900 7300
Wire Wire Line
	19850 7500 19850 8500
Connection ~ 19850 7500
Connection ~ 20400 7500
Wire Wire Line
	20400 7500 19850 7500
Wire Wire Line
	22350 6050 22350 7300
Connection ~ 22350 6050
Wire Wire Line
	22350 4800 22350 6050
Wire Wire Line
	22200 7300 22350 7300
Connection ~ 22300 5750
Wire Wire Line
	22300 7000 22300 5750
Wire Wire Line
	22200 7000 22300 7000
Connection ~ 19700 5550
Wire Wire Line
	19700 6800 19700 5550
Wire Wire Line
	20400 6800 19700 6800
Connection ~ 19650 5650
Wire Wire Line
	19650 6900 19650 5650
Wire Wire Line
	20400 6900 19650 6900
Wire Wire Line
	22200 7200 22200 7100
Wire Wire Line
	20400 7600 20400 7500
Wire Wire Line
	22750 5850 22750 7100
Connection ~ 22750 5850
Connection ~ 22200 5850
Wire Wire Line
	22200 5850 22750 5850
Wire Wire Line
	22200 5950 22200 5850
Connection ~ 22700 6250
Wire Wire Line
	22200 6250 22700 6250
Wire Wire Line
	22650 5650 22650 6900
Connection ~ 22650 5650
Wire Wire Line
	22200 5650 22650 5650
Connection ~ 20050 4500
Wire Wire Line
	20050 5750 20050 4500
Wire Wire Line
	20400 5750 20050 5750
Wire Wire Line
	20100 5600 20100 6850
Wire Wire Line
	19950 5950 19950 3550
Wire Wire Line
	20400 5950 19950 5950
Wire Wire Line
	20050 4500 20050 3650
Wire Wire Line
	20400 4500 20050 4500
Wire Wire Line
	20000 4700 20000 3600
Wire Wire Line
	20400 4700 20000 4700
Wire Wire Line
	19600 4350 20100 4350
Wire Wire Line
	20100 4350 20100 5600
Connection ~ 20100 4350
Wire Wire Line
	19600 5600 20100 5600
Connection ~ 20100 5600
Wire Wire Line
	19600 6850 20100 6850
Wire Wire Line
	20100 6850 20100 8100
Connection ~ 20100 6850
Wire Wire Line
	19600 8100 20100 8100
Wire Wire Line
	20100 8100 20100 9350
Connection ~ 20100 8100
Wire Wire Line
	19600 9350 20100 9350
Wire Wire Line
	20100 9350 20100 10600
Connection ~ 20100 9350
Wire Wire Line
	19600 4950 20150 4950
Wire Wire Line
	20150 4950 20150 6200
Connection ~ 20150 4950
Wire Wire Line
	19600 6200 20150 6200
Wire Wire Line
	20150 6200 20150 7450
Connection ~ 20150 6200
Wire Wire Line
	19600 7450 20150 7450
Wire Wire Line
	20150 7450 20150 8700
Connection ~ 20150 7450
Wire Wire Line
	19600 8700 20150 8700
Wire Wire Line
	20150 8700 20150 9950
Connection ~ 20150 8700
Wire Wire Line
	19600 9950 20150 9950
Wire Wire Line
	19600 4550 20200 4550
Wire Wire Line
	20200 4550 20200 5800
Connection ~ 20200 4550
Wire Wire Line
	19600 5800 20200 5800
Wire Wire Line
	20200 5800 20200 7050
Connection ~ 20200 5800
Wire Wire Line
	19600 7050 20200 7050
Wire Wire Line
	20200 7050 20200 8300
Connection ~ 20200 7050
Wire Wire Line
	19600 8300 20200 8300
Wire Wire Line
	20200 8300 20200 9550
Connection ~ 20200 8300
Wire Wire Line
	19600 9550 20200 9550
Wire Wire Line
	19900 6050 19900 4800
Connection ~ 19900 6050
Wire Wire Line
	20400 6050 19900 6050
Wire Wire Line
	19850 6250 19850 7250
Connection ~ 19850 6250
Connection ~ 20400 6250
Wire Wire Line
	20400 6250 19850 6250
Wire Wire Line
	19850 6000 19850 6250
Wire Wire Line
	20400 6350 20400 6250
Connection ~ 22350 4800
Wire Wire Line
	22200 6050 22350 6050
Connection ~ 22300 4500
Wire Wire Line
	22300 5750 22300 4500
Wire Wire Line
	22200 5750 22300 5750
Connection ~ 19700 5500
Wire Wire Line
	19700 5550 19700 5500
Wire Wire Line
	20400 5550 19700 5550
Connection ~ 19650 4400
Wire Wire Line
	19650 5650 19650 4400
Wire Wire Line
	20400 5650 19650 5650
Wire Wire Line
	22750 4600 22750 5850
Connection ~ 22750 4600
Connection ~ 22200 4600
Wire Wire Line
	22200 4600 22750 4600
Wire Wire Line
	22200 4700 22200 4600
Wire Wire Line
	22700 5000 22700 6250
Connection ~ 22700 5000
Wire Wire Line
	22200 5000 22700 5000
Wire Wire Line
	22650 4400 22650 5650
Connection ~ 22650 4400
Wire Wire Line
	22200 4400 22650 4400
Connection ~ 19900 4800
Wire Wire Line
	20400 4800 19900 4800
Wire Wire Line
	19850 5000 19850 6000
Connection ~ 19850 5000
Connection ~ 20400 5000
Wire Wire Line
	20400 5000 19850 5000
Wire Wire Line
	20400 5100 20400 5000
Wire Wire Line
	22200 4800 22350 4800
Wire Wire Line
	22200 4500 22300 4500
Wire Wire Line
	19700 4300 19700 5500
Connection ~ 19700 4300
Wire Wire Line
	20400 4300 19700 4300
Connection ~ 19650 4250
Wire Wire Line
	19650 4400 19650 4250
Wire Wire Line
	20400 4400 19650 4400
Connection ~ 17350 9450
Wire Wire Line
	17350 10700 17350 9450
Connection ~ 17300 9650
Connection ~ 17250 9750
Connection ~ 19800 9750
Wire Wire Line
	19800 11000 19800 9750
Wire Wire Line
	17800 11300 17800 11200
Wire Wire Line
	19600 10900 19600 10800
Connection ~ 19750 9450
Wire Wire Line
	19750 10700 19750 9450
Connection ~ 17000 9250
Wire Wire Line
	17000 10500 17000 9250
Connection ~ 16950 9350
Connection ~ 19600 9550
Wire Wire Line
	19600 9650 19600 9550
Connection ~ 17350 8200
Wire Wire Line
	17350 9450 17350 8200
Wire Wire Line
	17800 9450 17350 9450
Connection ~ 17300 8400
Wire Wire Line
	17300 9650 17300 8400
Wire Wire Line
	17800 9650 17300 9650
Connection ~ 17250 8500
Wire Wire Line
	17250 9750 17250 8500
Wire Wire Line
	17800 9750 17250 9750
Connection ~ 17200 8700
Connection ~ 17800 9950
Wire Wire Line
	17200 9950 17200 8700
Wire Wire Line
	17800 9950 17200 9950
Wire Wire Line
	17800 10050 17800 9950
Connection ~ 19800 8000
Wire Wire Line
	19800 9750 19800 8000
Wire Wire Line
	19600 9750 19800 9750
Wire Wire Line
	19600 9450 19750 9450
Connection ~ 17000 8000
Wire Wire Line
	17000 9250 17000 8000
Wire Wire Line
	17800 9250 17000 9250
Connection ~ 16950 8100
Wire Wire Line
	16950 9350 16950 8100
Wire Wire Line
	17800 9350 16950 9350
Connection ~ 19600 8300
Wire Wire Line
	19600 8400 19600 8300
Connection ~ 17350 6950
Wire Wire Line
	17350 8200 17350 6950
Wire Wire Line
	17800 8200 17350 8200
Connection ~ 17300 7150
Wire Wire Line
	17300 8400 17300 7150
Wire Wire Line
	17800 8400 17300 8400
Connection ~ 17250 7250
Wire Wire Line
	17250 8500 17250 7250
Wire Wire Line
	17800 8500 17250 8500
Connection ~ 17200 7450
Connection ~ 17800 8700
Wire Wire Line
	17200 8700 17200 7450
Wire Wire Line
	17800 8700 17200 8700
Wire Wire Line
	17800 8800 17800 8700
Connection ~ 19850 8500
Wire Wire Line
	19600 8500 19850 8500
Connection ~ 19750 6750
Wire Wire Line
	17800 8000 17000 8000
Wire Wire Line
	17800 8100 16950 8100
Connection ~ 19600 7050
Wire Wire Line
	17800 6950 17350 6950
Wire Wire Line
	17800 7150 17300 7150
Wire Wire Line
	17800 7250 17250 7250
Connection ~ 17800 7450
Wire Wire Line
	17800 7450 17200 7450
Wire Wire Line
	19850 7250 19850 7500
Connection ~ 19850 7250
Wire Wire Line
	19600 7250 19850 7250
Wire Wire Line
	19800 6950 19800 8000
Connection ~ 19800 6950
Wire Wire Line
	19600 6950 19800 6950
Wire Wire Line
	17000 6750 17000 8000
Connection ~ 17000 6750
Wire Wire Line
	17800 6750 17000 6750
Wire Wire Line
	16950 6850 16950 8100
Connection ~ 16950 6850
Wire Wire Line
	17800 6850 16950 6850
Connection ~ 19600 5800
Wire Wire Line
	17350 5700 17350 6950
Connection ~ 17350 5700
Wire Wire Line
	17800 5700 17350 5700
Wire Wire Line
	17300 5900 17300 7150
Connection ~ 17300 5900
Wire Wire Line
	17800 5900 17300 5900
Wire Wire Line
	17250 6000 17250 7250
Connection ~ 17250 6000
Wire Wire Line
	17800 6000 17250 6000
Wire Wire Line
	17200 6200 17200 7450
Connection ~ 17200 6200
Connection ~ 17800 6200
Wire Wire Line
	17800 6200 17200 6200
Connection ~ 19850 6000
Wire Wire Line
	19600 6000 19850 6000
Wire Wire Line
	19800 5700 19800 6950
Connection ~ 19800 5700
Wire Wire Line
	19600 5700 19800 5700
Wire Wire Line
	17800 5500 17050 5500
Connection ~ 16950 5600
Wire Wire Line
	17800 5600 16950 5600
Connection ~ 19600 4550
Wire Wire Line
	17350 4450 17350 5700
Connection ~ 17350 4450
Wire Wire Line
	17800 4450 17350 4450
Wire Wire Line
	17300 4650 17300 5900
Connection ~ 17300 4650
Wire Wire Line
	17800 4650 17300 4650
Wire Wire Line
	17250 4750 17250 6000
Connection ~ 17250 4750
Wire Wire Line
	17800 4750 17250 4750
Wire Wire Line
	17200 4950 17200 6200
Connection ~ 17200 4950
Connection ~ 17800 4950
Wire Wire Line
	17800 4950 17200 4950
Wire Wire Line
	19850 4750 19850 5000
Connection ~ 19850 4750
Wire Wire Line
	19600 4750 19850 4750
Wire Wire Line
	19800 4450 19800 5700
Connection ~ 19800 4450
Wire Wire Line
	19600 4450 19800 4450
Wire Wire Line
	19900 10500 19900 9800
Wire Wire Line
	17050 4250 17050 5500
Connection ~ 17050 4250
Wire Wire Line
	17800 4250 17050 4250
Wire Wire Line
	17000 4350 17000 6750
Connection ~ 17000 4350
Wire Wire Line
	17800 4350 17000 4350
Wire Wire Line
	22750 10550 22200 10550
Wire Wire Line
	22700 9300 22200 9300
Wire Wire Line
	22650 8050 22200 8050
Wire Wire Line
	22600 6800 22200 6800
Wire Wire Line
	22550 5550 22200 5550
Wire Wire Line
	22500 4300 22200 4300
Wire Wire Line
	19600 9250 19850 9250
$Comp
L LTP-587HR:LTP-587HR DS16
U 1 1 5FD8D32B
P 20400 10550
F 0 "DS16" H 21300 10815 50  0000 C CNN
F 1 "LTP-587HR" H 21300 10724 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 22050 10650 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 22050 10550 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 22050 10450 50  0001 L CNN "Description"
F 5 "9.75" H 22050 10350 50  0001 L CNN "Height"
F 6 "Lite-On" H 22050 10250 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 22050 10150 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 22050 10050 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 22050 9950 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 22050 9850 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 22050 9750 50  0001 L CNN "Mouser Price/Stock"
	1    20400 10550
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS15
U 1 1 5FD8B571
P 20400 9300
F 0 "DS15" H 21300 9565 50  0000 C CNN
F 1 "LTP-587HR" H 21300 9474 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 22050 9400 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 22050 9300 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 22050 9200 50  0001 L CNN "Description"
F 5 "9.75" H 22050 9100 50  0001 L CNN "Height"
F 6 "Lite-On" H 22050 9000 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 22050 8900 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 22050 8800 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 22050 8700 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 22050 8600 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 22050 8500 50  0001 L CNN "Mouser Price/Stock"
	1    20400 9300
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS14
U 1 1 5FD8A45B
P 20400 8050
F 0 "DS14" H 21300 8315 50  0000 C CNN
F 1 "LTP-587HR" H 21300 8224 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 22050 8150 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 22050 8050 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 22050 7950 50  0001 L CNN "Description"
F 5 "9.75" H 22050 7850 50  0001 L CNN "Height"
F 6 "Lite-On" H 22050 7750 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 22050 7650 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 22050 7550 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 22050 7450 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 22050 7350 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 22050 7250 50  0001 L CNN "Mouser Price/Stock"
	1    20400 8050
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS13
U 1 1 5FD88D7A
P 20400 6800
F 0 "DS13" H 21300 7065 50  0000 C CNN
F 1 "LTP-587HR" H 21300 6974 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 22050 6900 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 22050 6800 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 22050 6700 50  0001 L CNN "Description"
F 5 "9.75" H 22050 6600 50  0001 L CNN "Height"
F 6 "Lite-On" H 22050 6500 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 22050 6400 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 22050 6300 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 22050 6200 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 22050 6100 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 22050 6000 50  0001 L CNN "Mouser Price/Stock"
	1    20400 6800
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS12
U 1 1 5FD87157
P 20400 5550
F 0 "DS12" H 21300 5815 50  0000 C CNN
F 1 "LTP-587HR" H 21300 5724 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 22050 5650 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 22050 5550 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 22050 5450 50  0001 L CNN "Description"
F 5 "9.75" H 22050 5350 50  0001 L CNN "Height"
F 6 "Lite-On" H 22050 5250 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 22050 5150 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 22050 5050 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 22050 4950 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 22050 4850 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 22050 4750 50  0001 L CNN "Mouser Price/Stock"
	1    20400 5550
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS11
U 1 1 5FD8490A
P 20400 4300
F 0 "DS11" H 21300 4565 50  0000 C CNN
F 1 "LTP-587HR" H 21300 4474 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 22050 4400 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 22050 4300 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 22050 4200 50  0001 L CNN "Description"
F 5 "9.75" H 22050 4100 50  0001 L CNN "Height"
F 6 "Lite-On" H 22050 4000 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 22050 3900 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 22050 3800 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 22050 3700 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 22050 3600 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 22050 3500 50  0001 L CNN "Mouser Price/Stock"
	1    20400 4300
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS10
U 1 1 5FD83301
P 17800 10500
F 0 "DS10" H 18700 10765 50  0000 C CNN
F 1 "LTP-587HR" H 18700 10674 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 19450 10600 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 19450 10500 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 19450 10400 50  0001 L CNN "Description"
F 5 "9.75" H 19450 10300 50  0001 L CNN "Height"
F 6 "Lite-On" H 19450 10200 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 19450 10100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 19450 10000 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 19450 9900 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 19450 9800 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 19450 9700 50  0001 L CNN "Mouser Price/Stock"
	1    17800 10500
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS9
U 1 1 5FD81C98
P 17800 9250
F 0 "DS9" H 18700 9515 50  0000 C CNN
F 1 "LTP-587HR" H 18700 9424 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 19450 9350 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 19450 9250 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 19450 9150 50  0001 L CNN "Description"
F 5 "9.75" H 19450 9050 50  0001 L CNN "Height"
F 6 "Lite-On" H 19450 8950 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 19450 8850 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 19450 8750 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 19450 8650 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 19450 8550 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 19450 8450 50  0001 L CNN "Mouser Price/Stock"
	1    17800 9250
	1    0    0    -1  
$EndComp
Wire Wire Line
	19600 8000 19800 8000
$Comp
L LTP-587HR:LTP-587HR DS8
U 1 1 5FD5F104
P 17800 8000
F 0 "DS8" H 18700 8265 50  0000 C CNN
F 1 "LTP-587HR" H 18700 8174 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 19450 8100 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 19450 8000 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 19450 7900 50  0001 L CNN "Description"
F 5 "9.75" H 19450 7800 50  0001 L CNN "Height"
F 6 "Lite-On" H 19450 7700 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 19450 7600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 19450 7500 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 19450 7400 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 19450 7300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 19450 7200 50  0001 L CNN "Mouser Price/Stock"
	1    17800 8000
	1    0    0    -1  
$EndComp
Wire Wire Line
	19600 6750 19750 6750
Wire Wire Line
	19600 7150 19600 7050
Wire Wire Line
	17800 7550 17800 7450
$Comp
L LTP-587HR:LTP-587HR DS7
U 1 1 5FD42E11
P 17800 6750
F 0 "DS7" H 18700 7015 50  0000 C CNN
F 1 "LTP-587HR" H 18700 6924 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 19450 6850 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 19450 6750 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 19450 6650 50  0001 L CNN "Description"
F 5 "9.75" H 19450 6550 50  0001 L CNN "Height"
F 6 "Lite-On" H 19450 6450 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 19450 6350 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 19450 6250 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 19450 6150 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 19450 6050 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 19450 5950 50  0001 L CNN "Mouser Price/Stock"
	1    17800 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	19600 5900 19600 5800
Wire Wire Line
	17800 6300 17800 6200
Wire Wire Line
	19700 5500 19600 5500
$Comp
L LTP-587HR:LTP-587HR DS6
U 1 1 5FD34550
P 17800 5500
F 0 "DS6" H 18700 5765 50  0000 C CNN
F 1 "LTP-587HR" H 18700 5674 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 19450 5600 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 19450 5500 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 19450 5400 50  0001 L CNN "Description"
F 5 "9.75" H 19450 5300 50  0001 L CNN "Height"
F 6 "Lite-On" H 19450 5200 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 19450 5100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 19450 5000 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 19450 4900 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 19450 4800 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 19450 4700 50  0001 L CNN "Mouser Price/Stock"
	1    17800 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	19600 4250 19650 4250
Wire Wire Line
	19600 4650 19600 4550
Wire Wire Line
	17800 5050 17800 4950
$Comp
L LTP-587HR:LTP-587HR DS5
U 1 1 5FD155E2
P 17800 4250
F 0 "DS5" H 18700 4515 50  0000 C CNN
F 1 "LTP-587HR" H 18700 4424 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 19450 4350 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 19450 4250 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 19450 4150 50  0001 L CNN "Description"
F 5 "9.75" H 19450 4050 50  0001 L CNN "Height"
F 6 "Lite-On" H 19450 3950 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 19450 3850 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 19450 3750 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 19450 3650 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 19450 3550 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 19450 3450 50  0001 L CNN "Mouser Price/Stock"
	1    17800 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	22750 8350 22750 9600
Wire Wire Line
	16950 5600 16950 6850
Wire Wire Line
	16950 3250 16950 5600
Wire Wire Line
	17000 3300 17000 4350
Wire Wire Line
	17050 3350 17050 4250
Wire Wire Line
	19650 3250 19650 4250
Wire Wire Line
	16950 3250 19650 3250
Wire Wire Line
	19700 3300 19700 4300
Wire Wire Line
	17000 3300 19700 3300
Wire Wire Line
	19750 3350 19750 6750
Wire Wire Line
	17050 3350 19750 3350
Wire Wire Line
	19800 3400 19800 4450
Wire Wire Line
	19850 3450 19850 4750
Wire Wire Line
	19900 3500 19900 4800
Wire Wire Line
	20100 3700 20100 4350
Wire Wire Line
	20150 3750 20150 4950
Wire Wire Line
	20200 3800 20200 4550
Wire Wire Line
	17350 3650 20050 3650
Wire Wire Line
	17350 3650 17350 4450
Wire Wire Line
	17300 3600 20000 3600
Wire Wire Line
	17300 3600 17300 4650
Wire Wire Line
	17250 3550 19950 3550
Wire Wire Line
	17250 3550 17250 4750
Wire Wire Line
	17200 3500 19900 3500
Wire Wire Line
	17200 3500 17200 4950
Wire Wire Line
	17150 3450 19850 3450
Wire Wire Line
	17150 3450 17150 11200
Wire Wire Line
	20200 3800 22750 3800
Connection ~ 20200 3800
Wire Wire Line
	22750 3800 22750 4600
Wire Wire Line
	20150 3750 22700 3750
Connection ~ 20150 3750
Wire Wire Line
	22700 3750 22700 5000
Wire Wire Line
	22300 3350 19750 3350
Wire Wire Line
	22300 3350 22300 4500
Connection ~ 19750 3350
Wire Wire Line
	22350 3400 19800 3400
Wire Wire Line
	22350 3400 22350 4800
Connection ~ 19800 3400
Wire Wire Line
	22650 3700 20100 3700
Wire Wire Line
	22650 3700 22650 4400
Connection ~ 20100 3700
Wire Wire Line
	22600 3650 20050 3650
Wire Wire Line
	22600 3650 22600 6800
Connection ~ 20050 3650
Wire Wire Line
	22550 3600 20000 3600
Wire Wire Line
	22550 3600 22550 5550
Connection ~ 20000 3600
Wire Wire Line
	22500 3550 19950 3550
Wire Wire Line
	22500 3550 22500 4300
Connection ~ 19950 3550
$Comp
L LTP-587HR:LTP-587HR DS1
U 1 1 60BD8C8F
P 14300 4250
F 0 "DS1" H 15200 4515 50  0000 C CNN
F 1 "LTP-587HR" H 15200 4424 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 15950 4350 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 15950 4250 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 15950 4150 50  0001 L CNN "Description"
F 5 "9.75" H 15950 4050 50  0001 L CNN "Height"
F 6 "Lite-On" H 15950 3950 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 15950 3850 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 15950 3750 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 15950 3650 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 15950 3550 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 15950 3450 50  0001 L CNN "Mouser Price/Stock"
	1    14300 4250
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS2
U 1 1 60BDF276
P 14300 5500
F 0 "DS2" H 15200 5765 50  0000 C CNN
F 1 "LTP-587HR" H 15200 5674 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 15950 5600 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 15950 5500 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 15950 5400 50  0001 L CNN "Description"
F 5 "9.75" H 15950 5300 50  0001 L CNN "Height"
F 6 "Lite-On" H 15950 5200 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 15950 5100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 15950 5000 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 15950 4900 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 15950 4800 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 15950 4700 50  0001 L CNN "Mouser Price/Stock"
	1    14300 5500
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS3
U 1 1 60BE0973
P 14300 6750
F 0 "DS3" H 15200 7015 50  0000 C CNN
F 1 "LTP-587HR" H 15200 6924 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 15950 6850 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 15950 6750 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 15950 6650 50  0001 L CNN "Description"
F 5 "9.75" H 15950 6550 50  0001 L CNN "Height"
F 6 "Lite-On" H 15950 6450 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 15950 6350 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 15950 6250 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 15950 6150 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 15950 6050 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 15950 5950 50  0001 L CNN "Mouser Price/Stock"
	1    14300 6750
	1    0    0    -1  
$EndComp
$Comp
L LTP-587HR:LTP-587HR DS4
U 1 1 60BE2D07
P 14300 8000
F 0 "DS4" H 15200 8265 50  0000 C CNN
F 1 "LTP-587HR" H 15200 8174 50  0000 C CNN
F 2 "LTP-587HR:DIPS1270W50P254L2500H975Q18N" H 15950 8100 50  0001 L CNN
F 3 "http://optoelectronics.liteon.com/upload/download/DS-30-97-273/P587hr.pdf" H 15950 8000 50  0001 L CNN
F 4 "LED Displays & Accessories Hi-Eff Red" H 15950 7900 50  0001 L CNN "Description"
F 5 "9.75" H 15950 7800 50  0001 L CNN "Height"
F 6 "Lite-On" H 15950 7700 50  0001 L CNN "Manufacturer_Name"
F 7 "LTP-587HR" H 15950 7600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "LTP-587HR" H 15950 7500 50  0001 L CNN "Arrow Part Number"
F 9 "https://www.arrow.com/en/products/ltp-587hr/lite-on-technology" H 15950 7400 50  0001 L CNN "Arrow Price/Stock"
F 10 "859-LTP-587HR" H 15950 7300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Lite-On/LTP-587HR?qs=gnaPJ2cis70An5vo3Hcuvw%3D%3D" H 15950 7200 50  0001 L CNN "Mouser Price/Stock"
	1    14300 8000
	1    0    0    -1  
$EndComp
Wire Wire Line
	14300 5050 14300 4950
Wire Wire Line
	14300 6300 14300 6200
Wire Wire Line
	14300 7550 14300 7450
Wire Wire Line
	16100 4650 16100 4550
Wire Wire Line
	16100 5900 16100 5800
Wire Wire Line
	16100 7150 16100 7050
Wire Wire Line
	16100 8400 16100 8300
Wire Wire Line
	14300 8800 14300 8700
Wire Wire Line
	16100 8000 16150 8000
Wire Wire Line
	16150 8000 16150 9100
Wire Wire Line
	16100 6750 16200 6750
Wire Wire Line
	16200 6750 16200 9150
Wire Wire Line
	16100 5500 16250 5500
Wire Wire Line
	16250 5500 16250 9200
Wire Wire Line
	16100 4250 16300 4250
Wire Wire Line
	16300 4250 16300 5700
Wire Wire Line
	14300 8100 13700 8100
Wire Wire Line
	13700 8100 13700 9150
Wire Wire Line
	13700 9150 16200 9150
Wire Wire Line
	14300 8000 13750 8000
Wire Wire Line
	13750 8000 13750 9200
Wire Wire Line
	16100 8200 16300 8200
Connection ~ 16300 8200
Wire Wire Line
	16300 8200 16300 9250
Wire Wire Line
	16100 8500 16350 8500
Wire Wire Line
	16350 8500 16350 9300
Wire Wire Line
	14300 8700 13900 8700
Wire Wire Line
	13900 8700 13900 9350
Connection ~ 14300 8700
Wire Wire Line
	14300 8500 13950 8500
Wire Wire Line
	13950 8500 13950 9400
Wire Wire Line
	14300 8400 14000 8400
Wire Wire Line
	14000 8400 14000 9450
Wire Wire Line
	14300 8200 14050 8200
Wire Wire Line
	14050 8200 14050 9500
Wire Wire Line
	16100 8100 16600 8100
Wire Wire Line
	16600 8100 16600 9550
Wire Wire Line
	16100 8700 16650 8700
Wire Wire Line
	16650 8700 16650 9600
Wire Wire Line
	16100 8300 16700 8300
Wire Wire Line
	16700 8300 16700 9650
Connection ~ 16100 8300
Wire Wire Line
	14300 6850 13650 6850
Wire Wire Line
	13650 6850 13650 9100
Wire Wire Line
	13650 9100 16150 9100
Wire Wire Line
	14300 6750 13750 6750
Wire Wire Line
	13750 6750 13750 8000
Connection ~ 13750 8000
Wire Wire Line
	16100 6950 16300 6950
Connection ~ 16300 6950
Wire Wire Line
	16300 6950 16300 8200
Wire Wire Line
	16100 7250 16350 7250
Wire Wire Line
	16350 7250 16350 8500
Connection ~ 16350 8500
Wire Wire Line
	14300 7450 13900 7450
Wire Wire Line
	13900 7450 13900 8700
Connection ~ 14300 7450
Connection ~ 13900 8700
Wire Wire Line
	14300 7250 13950 7250
Wire Wire Line
	13950 7250 13950 8500
Connection ~ 13950 8500
Wire Wire Line
	14300 7150 14000 7150
Wire Wire Line
	14000 7150 14000 8400
Connection ~ 14000 8400
Wire Wire Line
	14300 6950 14050 6950
Wire Wire Line
	14050 6950 14050 8200
Connection ~ 14050 8200
Wire Wire Line
	16100 6850 16600 6850
Wire Wire Line
	16600 6850 16600 8100
Connection ~ 16600 8100
Wire Wire Line
	16100 7450 16650 7450
Wire Wire Line
	16650 7450 16650 8700
Connection ~ 16650 8700
Wire Wire Line
	16100 7050 16700 7050
Wire Wire Line
	16700 7050 16700 8300
Connection ~ 16100 7050
Connection ~ 16700 8300
Wire Wire Line
	14300 5600 13650 5600
Wire Wire Line
	13650 5600 13650 6850
Connection ~ 13650 6850
Wire Wire Line
	14300 4350 13650 4350
Connection ~ 13650 5600
Wire Wire Line
	14300 5500 13700 5500
Connection ~ 13700 8100
Wire Wire Line
	14300 4250 13700 4250
Wire Wire Line
	13700 4250 13700 5500
Connection ~ 13700 5500
Wire Wire Line
	16100 5700 16300 5700
Connection ~ 16300 5700
Wire Wire Line
	16300 5700 16300 6950
Wire Wire Line
	16100 6000 16350 6000
Wire Wire Line
	16350 6000 16350 7250
Connection ~ 16350 7250
Wire Wire Line
	14300 6200 13900 6200
Wire Wire Line
	13900 6200 13900 7450
Connection ~ 14300 6200
Connection ~ 13900 7450
Wire Wire Line
	14300 6000 13950 6000
Connection ~ 13950 7250
Wire Wire Line
	14300 5900 14000 5900
Connection ~ 14000 7150
Wire Wire Line
	14300 5700 14050 5700
Connection ~ 14050 6950
Wire Wire Line
	14300 5050 13900 5050
Connection ~ 14300 5050
Connection ~ 13900 6200
Wire Wire Line
	14300 4750 13950 4750
Wire Wire Line
	13950 4750 13950 6000
Connection ~ 13950 6000
Wire Wire Line
	14300 4650 14000 4650
Wire Wire Line
	14000 4650 14000 5900
Connection ~ 14000 5900
Wire Wire Line
	14300 4450 14050 4450
Wire Wire Line
	14050 4450 14050 5700
Connection ~ 14050 5700
Wire Wire Line
	16100 4450 16250 4450
Wire Wire Line
	16250 4450 16250 5500
Connection ~ 16250 5500
Wire Wire Line
	16100 4750 16350 4750
Wire Wire Line
	16350 4750 16350 6000
Connection ~ 16350 6000
Wire Wire Line
	16100 4350 16600 4350
Wire Wire Line
	16600 4350 16600 5600
Connection ~ 16600 6850
Wire Wire Line
	16100 4950 16650 4950
Wire Wire Line
	16650 4950 16650 6200
Connection ~ 16650 7450
Wire Wire Line
	16100 4550 16700 4550
Wire Wire Line
	16700 4550 16700 5800
Connection ~ 16100 4550
Connection ~ 16700 7050
Wire Wire Line
	12950 3250 16950 3250
Connection ~ 16950 3250
Wire Wire Line
	12950 3350 13000 3350
Wire Wire Line
	13000 3350 13000 3300
Wire Wire Line
	13000 3300 17000 3300
Connection ~ 17000 3300
Wire Wire Line
	12950 3450 13050 3450
Wire Wire Line
	13050 3450 13050 3350
Wire Wire Line
	13050 3350 17050 3350
Connection ~ 17050 3350
Wire Wire Line
	12950 3550 13100 3550
Wire Wire Line
	13100 3550 13100 3400
Wire Wire Line
	13100 3400 19800 3400
Wire Wire Line
	12950 3650 13150 3650
Wire Wire Line
	13150 3650 13150 3450
Wire Wire Line
	13150 3450 17150 3450
Connection ~ 17150 3450
Wire Wire Line
	12950 3750 13200 3750
Wire Wire Line
	13200 3750 13200 3500
Wire Wire Line
	13200 3500 17200 3500
Connection ~ 17200 3500
Wire Wire Line
	12950 3850 13250 3850
Wire Wire Line
	13250 3850 13250 3550
Wire Wire Line
	13250 3550 17250 3550
Connection ~ 17250 3550
Wire Wire Line
	12950 3950 13300 3950
Wire Wire Line
	13300 3950 13300 3600
Wire Wire Line
	13300 3600 17300 3600
Connection ~ 17300 3600
Wire Wire Line
	12950 4050 13350 4050
Wire Wire Line
	13350 4050 13350 3650
Wire Wire Line
	13350 3650 17350 3650
Connection ~ 17350 3650
Wire Wire Line
	12950 4150 13400 4150
Wire Wire Line
	13400 4150 13400 3700
Wire Wire Line
	13400 3700 20100 3700
Wire Wire Line
	12950 4250 13450 4250
Wire Wire Line
	13450 4250 13450 3750
Wire Wire Line
	13450 3750 20150 3750
Wire Wire Line
	12950 4350 13500 4350
Wire Wire Line
	13500 4350 13500 3800
Wire Wire Line
	13500 3800 20200 3800
Wire Wire Line
	13750 5650 13750 6750
Connection ~ 13750 6750
Wire Wire Line
	13850 5850 13850 9300
Wire Wire Line
	14150 6450 14150 9600
Wire Wire Line
	14200 9650 14200 6550
$Comp
L eec:AS1130-BSST U2
U 1 1 5FD05F4A
P 11850 5450
F 0 "U2" H 12450 5715 50  0000 C CNN
F 1 "AS1130-BSST" H 12450 5624 50  0000 C CNN
F 2 "Package_SO:SSOP-28_5.3x10.2mm_P0.65mm" H 11850 5850 50  0001 L CNN
F 3 "http://www.ams.com/eng/content/download/185846/834724/105034" H 11850 5950 50  0001 L CNN
F 4 "MO-150" H 11850 6050 50  0001 L CNN "Code  JEDEC"
F 5 "Manufacturer URL" H 11850 6150 50  0001 L CNN "Component Link 1 Description"
F 6 "www.ams.com" H 11850 6250 50  0001 L CNN "Component Link 1 URL"
F 7 "Rev. 1.07" H 11850 6350 50  0001 L CNN "Datasheet Version"
F 8 "true" H 11850 6450 50  0001 L CNN "Error Detection"
F 9 "8-bit PWM & analog current control, dynamic headroom control" H 11850 6550 50  0001 L CNN "Features"
F 10 "2.5" H 11850 6650 50  0001 L CNN "LED Current per Output mA"
F 11 "2" H 11850 6750 50  0001 L CNN "LED to LED Matching "
F 12 "Surface Mount" H 11850 6850 50  0001 L CNN "Mounting Technology"
F 13 "132" H 11850 6950 50  0001 L CNN "Outputs"
F 14 "28-Pin Shrink Small Outline Package, 10.2 x 5.3 mm Body, 0.65 mm Pitch" H 11850 7050 50  0001 L CNN "Package Description"
F 15 "N/C, 07/2011" H 11850 7150 50  0001 L CNN "Package Version"
F 16 "true" H 11850 7250 50  0001 L CNN "Read back"
F 17 "2.7 to 5.5" H 11850 7350 50  0001 L CNN "Supply Voltage V"
F 18 "IC" H 11850 7450 50  0001 L CNN "category"
F 19 "4367283" H 11850 7550 50  0001 L CNN "ciiva ids"
F 20 "598dcdd5055ccc55" H 11850 7650 50  0001 L CNN "library id"
F 21 "AMS" H 11850 7750 50  0001 L CNN "manufacturer"
F 22 "SSOP-28" H 11850 7850 50  0001 L CNN "package"
F 23 "1394513892" H 11850 7950 50  0001 L CNN "release date"
F 24 "660BAB0B-1A30-45A6-8177-846E59C4C6EC" H 11850 8050 50  0001 L CNN "vault revision"
F 25 "yes" H 11850 8150 50  0001 L CNN "imported"
	1    11850 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	13650 5450 13650 5600
Wire Wire Line
	13650 4350 13650 5450
Connection ~ 13650 5450
Wire Wire Line
	12950 5450 13650 5450
Wire Wire Line
	13700 5550 13700 8100
Wire Wire Line
	13700 5500 13700 5550
Connection ~ 13700 5550
Wire Wire Line
	12950 5550 13700 5550
Wire Wire Line
	12950 5650 13750 5650
Wire Wire Line
	12950 5750 13800 5750
Wire Wire Line
	12950 5850 13850 5850
Wire Wire Line
	13900 5950 13900 6200
Wire Wire Line
	13900 5050 13900 5950
Connection ~ 13900 5950
Wire Wire Line
	12950 5950 13900 5950
Wire Wire Line
	13950 6050 13950 7250
Wire Wire Line
	13950 6000 13950 6050
Connection ~ 13950 6050
Wire Wire Line
	12950 6050 13950 6050
Wire Wire Line
	14000 6150 14000 7150
Wire Wire Line
	14000 5900 14000 6150
Connection ~ 14000 6150
Wire Wire Line
	12950 6150 14000 6150
Wire Wire Line
	14050 6250 14050 6950
Wire Wire Line
	14050 5700 14050 6250
Connection ~ 14050 6250
Wire Wire Line
	12950 6250 14050 6250
Wire Wire Line
	12950 6350 14100 6350
Wire Wire Line
	12950 6450 14150 6450
Wire Wire Line
	14200 6550 12950 6550
$Comp
L B3J-2100:B3J-2100 S1
U 1 1 61D48F9B
P 11300 10000
F 0 "S1" H 11900 10265 50  0000 C CNN
F 1 "B3J-2100" H 11900 10174 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 12350 10100 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 12350 10000 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 12350 9900 50  0001 L CNN "Description"
F 5 "10.5" H 12350 9800 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 12350 9700 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 12350 9600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 12350 9500 50  0001 L CNN "Arrow Part Number"
F 9 "" H 12350 9400 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 12350 9300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 12350 9200 50  0001 L CNN "Mouser Price/Stock"
	1    11300 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	13850 9300 12600 9300
Wire Wire Line
	12600 9300 12600 10100
Wire Wire Line
	12600 10100 12500 10100
Connection ~ 13850 9300
Wire Wire Line
	12600 10100 12600 10750
Wire Wire Line
	12600 10750 12500 10750
Connection ~ 12600 10100
Wire Wire Line
	12600 11450 12500 11450
Wire Wire Line
	12500 10200 12650 10200
Wire Wire Line
	12650 10200 12650 9100
Wire Wire Line
	12650 9100 13650 9100
Connection ~ 13650 9100
Wire Wire Line
	12600 10750 12600 11450
Connection ~ 12600 10750
Wire Wire Line
	12500 10850 12700 10850
Wire Wire Line
	12700 10850 12700 9150
Wire Wire Line
	12700 9150 13700 9150
Connection ~ 13700 9150
Wire Wire Line
	12500 11550 12750 11550
Wire Wire Line
	12750 11550 12750 9200
Wire Wire Line
	12750 9200 13750 9200
Connection ~ 13750 9200
$Comp
L arduino_shieldsNCL:ARDUINO_MEGA_SHIELD SHIELD1
U 1 1 62867352
P 7100 6700
F 0 "SHIELD1" H 7050 9337 60  0000 C CNN
F 1 "ARDUINO MEGA SHIELD" H 7050 9231 60  0000 C CNN
F 2 "arduino_shields:ARDUINO MEGA SHIELD" H 7100 6700 50  0001 C CNN
F 3 "" H 7100 6700 50  0001 C CNN
	1    7100 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 3250 11850 3250
Wire Wire Line
	11850 3250 11850 5450
Wire Wire Line
	11850 5450 11950 5450
Wire Wire Line
	11950 5550 11800 5550
Wire Wire Line
	11800 5550 11800 3350
Wire Wire Line
	11800 3350 11950 3350
$Comp
L power:VDD #PWR0101
U 1 1 62B22D1D
P 11650 4550
F 0 "#PWR0101" H 11650 4400 50  0001 C CNN
F 1 "VDD" H 11665 4723 50  0000 C CNN
F 2 "" H 11650 4550 50  0001 C CNN
F 3 "" H 11650 4550 50  0001 C CNN
	1    11650 4550
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0102
U 1 1 62B23991
P 11700 6750
F 0 "#PWR0102" H 11700 6600 50  0001 C CNN
F 1 "VDD" H 11715 6923 50  0000 C CNN
F 2 "" H 11700 6750 50  0001 C CNN
F 3 "" H 11700 6750 50  0001 C CNN
	1    11700 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11700 6750 11950 6750
Connection ~ 11950 4650
Wire Wire Line
	11950 4650 11950 4550
Connection ~ 11950 4750
Wire Wire Line
	11950 4750 11950 4650
Wire Wire Line
	11950 4850 11950 4750
Wire Wire Line
	11950 4550 11650 4550
Connection ~ 11950 4550
$Comp
L power:GND #PWR0103
U 1 1 62CBA5C1
P 13050 5050
F 0 "#PWR0103" H 13050 4800 50  0001 C CNN
F 1 "GND" H 13055 4877 50  0000 C CNN
F 2 "" H 13050 5050 50  0001 C CNN
F 3 "" H 13050 5050 50  0001 C CNN
	1    13050 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 62CBB729
P 13050 7250
F 0 "#PWR0104" H 13050 7000 50  0001 C CNN
F 1 "GND" H 13055 7077 50  0000 C CNN
F 2 "" H 13050 7250 50  0001 C CNN
F 3 "" H 13050 7250 50  0001 C CNN
	1    13050 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	13050 7250 13050 7150
Wire Wire Line
	13050 7150 12950 7150
Wire Wire Line
	13050 5050 13050 4950
Wire Wire Line
	13050 4950 12950 4950
$Comp
L B3J-2100:B3J-2100 S3
U 1 1 61D4C095
P 11300 11350
F 0 "S3" H 11900 11615 50  0000 C CNN
F 1 "B3J-2100" H 11900 11524 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 12350 11450 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 12350 11350 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 12350 11250 50  0001 L CNN "Description"
F 5 "10.5" H 12350 11150 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 12350 11050 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 12350 10950 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 12350 10850 50  0001 L CNN "Arrow Part Number"
F 9 "" H 12350 10750 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 12350 10650 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 12350 10550 50  0001 L CNN "Mouser Price/Stock"
	1    11300 11350
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S2
U 1 1 61D4A935
P 11300 10650
F 0 "S2" H 11900 10915 50  0000 C CNN
F 1 "B3J-2100" H 11900 10824 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 12350 10750 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 12350 10650 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 12350 10550 50  0001 L CNN "Description"
F 5 "10.5" H 12350 10450 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 12350 10350 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 12350 10250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 12350 10150 50  0001 L CNN "Arrow Part Number"
F 9 "" H 12350 10050 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 12350 9950 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 12350 9850 50  0001 L CNN "Mouser Price/Stock"
	1    11300 10650
	1    0    0    -1  
$EndComp
Wire Wire Line
	19750 6750 19750 8200
Wire Wire Line
	19600 8200 19750 8200
Connection ~ 19750 8200
Wire Wire Line
	19750 8200 19750 9450
Wire Wire Line
	22200 9500 22300 9500
Wire Wire Line
	22300 9500 22300 8250
Connection ~ 22300 8250
Wire Wire Line
	22200 9800 22350 9800
Wire Wire Line
	22350 9800 22350 8550
Connection ~ 22350 8550
Wire Wire Line
	22200 10750 22300 10750
Wire Wire Line
	22300 10750 22300 9500
Connection ~ 22300 9500
Wire Wire Line
	22200 11050 22350 11050
Wire Wire Line
	22350 11050 22350 9800
Connection ~ 22350 9800
Wire Wire Line
	22200 9600 22750 9600
Connection ~ 22200 9600
Connection ~ 22750 9600
Wire Wire Line
	22750 9600 22750 10550
Wire Wire Line
	22200 10850 22700 10850
Wire Wire Line
	22700 10850 22700 9300
Connection ~ 22200 10850
Connection ~ 22700 9300
Wire Wire Line
	20400 10000 19850 10000
Wire Wire Line
	19850 10000 19850 9250
Connection ~ 20400 10000
Connection ~ 19850 9250
Wire Wire Line
	20400 11250 19850 11250
Wire Wire Line
	19850 11250 19850 10000
Connection ~ 20400 11250
Connection ~ 19850 10000
Wire Wire Line
	19600 10800 20200 10800
Wire Wire Line
	20200 10800 20200 9550
Connection ~ 19600 10800
Connection ~ 20200 9550
Wire Wire Line
	19600 11200 20150 11200
Wire Wire Line
	20150 11200 20150 9950
Connection ~ 20150 9950
Wire Wire Line
	16100 5800 16700 5800
Connection ~ 16100 5800
Connection ~ 16700 5800
Wire Wire Line
	16700 5800 16700 7050
Wire Wire Line
	16100 6200 16650 6200
Connection ~ 16650 6200
Wire Wire Line
	16650 6200 16650 7450
Wire Wire Line
	16100 5600 16600 5600
Connection ~ 16600 5600
Wire Wire Line
	16600 5600 16600 6850
Wire Wire Line
	14100 6350 14100 9550
Wire Wire Line
	13800 5750 13800 9250
Wire Wire Line
	13750 9200 16250 9200
$Comp
L power:GND #PWR0105
U 1 1 635F5BAC
P 11200 11750
F 0 "#PWR0105" H 11200 11500 50  0001 C CNN
F 1 "GND" H 11205 11577 50  0000 C CNN
F 2 "" H 11200 11750 50  0001 C CNN
F 3 "" H 11200 11750 50  0001 C CNN
	1    11200 11750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11300 11450 11300 11350
Wire Wire Line
	11300 10750 11300 10650
Wire Wire Line
	11300 10100 11300 10000
Wire Wire Line
	11300 10000 11200 10000
Wire Wire Line
	11200 10000 11200 10650
Connection ~ 11300 10000
Wire Wire Line
	11300 10650 11200 10650
Connection ~ 11300 10650
Connection ~ 11200 10650
Wire Wire Line
	11200 10650 11200 11350
Wire Wire Line
	11300 11350 11200 11350
Connection ~ 11300 11350
Connection ~ 11200 11350
Wire Wire Line
	11200 11350 11200 11750
Wire Wire Line
	8000 6750 11550 6750
Wire Wire Line
	11550 6750 11550 5550
Wire Wire Line
	11550 5550 11800 5550
Connection ~ 11800 5550
Wire Wire Line
	8000 6850 11600 6850
Wire Wire Line
	11600 6850 11600 5450
Wire Wire Line
	11600 5450 11850 5450
Connection ~ 11850 5450
Wire Wire Line
	11300 10200 10900 10200
Wire Wire Line
	10900 10200 10900 7350
Wire Wire Line
	10900 7350 8000 7350
Wire Wire Line
	11300 10850 10850 10850
Wire Wire Line
	10850 10850 10850 7450
Wire Wire Line
	10850 7450 8000 7450
Wire Wire Line
	11300 11550 10800 11550
Wire Wire Line
	10800 11550 10800 7550
Wire Wire Line
	10800 7550 8000 7550
Wire Wire Line
	12800 10200 12800 12700
Wire Wire Line
	12800 12700 10750 12700
Wire Wire Line
	10750 12700 10750 7650
Wire Wire Line
	10750 7650 8000 7650
Wire Wire Line
	12850 10850 12850 12750
Wire Wire Line
	12850 12750 10700 12750
Wire Wire Line
	10700 12750 10700 7750
Wire Wire Line
	10700 7750 8000 7750
Wire Wire Line
	12900 12800 10650 12800
Wire Wire Line
	10650 12800 10650 7850
Wire Wire Line
	10650 7850 8000 7850
Wire Wire Line
	10600 12850 10600 7950
Wire Wire Line
	10600 7950 8000 7950
Wire Wire Line
	16700 9650 16450 9650
Wire Wire Line
	13100 12150 13100 12850
Wire Wire Line
	12900 11500 12900 12800
Wire Wire Line
	13000 10650 13000 11300
Connection ~ 13000 10650
Connection ~ 13100 10650
Wire Wire Line
	13100 10650 13000 10650
Wire Wire Line
	13000 11300 13000 11950
Connection ~ 13000 11300
Connection ~ 13100 11300
Wire Wire Line
	13100 11300 13000 11300
Wire Wire Line
	13000 11950 13000 12350
Connection ~ 13000 11950
Connection ~ 13100 11950
Wire Wire Line
	13100 11950 13000 11950
Connection ~ 13100 10000
Wire Wire Line
	13000 10000 13000 10650
Wire Wire Line
	13100 10000 13000 10000
Wire Wire Line
	13100 10100 13100 10000
Wire Wire Line
	13100 10750 13100 10650
Wire Wire Line
	13100 11400 13100 11300
Wire Wire Line
	13100 12050 13100 11950
Connection ~ 14850 10650
Connection ~ 14950 10000
Wire Wire Line
	14850 10000 14850 10650
Wire Wire Line
	14950 10000 14850 10000
Wire Wire Line
	14950 10000 14950 10100
Connection ~ 14850 11300
Connection ~ 14950 10650
Wire Wire Line
	14850 10650 14850 11300
Wire Wire Line
	14950 10650 14850 10650
Wire Wire Line
	14950 10750 14950 10650
Connection ~ 14850 11950
Connection ~ 14950 11300
Wire Wire Line
	14850 11300 14850 11950
Wire Wire Line
	14950 11300 14850 11300
Wire Wire Line
	14950 11400 14950 11300
Connection ~ 14950 11950
Wire Wire Line
	14950 12050 14950 11950
Wire Wire Line
	14850 11950 14850 12350
Wire Wire Line
	14950 11950 14850 11950
$Comp
L power:GND #PWR0106
U 1 1 635F7775
P 14850 12350
F 0 "#PWR0106" H 14850 12100 50  0001 C CNN
F 1 "GND" H 14855 12177 50  0000 C CNN
F 2 "" H 14850 12350 50  0001 C CNN
F 3 "" H 14850 12350 50  0001 C CNN
	1    14850 12350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 635F6729
P 13000 12350
F 0 "#PWR0107" H 13000 12100 50  0001 C CNN
F 1 "GND" H 13005 12177 50  0000 C CNN
F 2 "" H 13000 12350 50  0001 C CNN
F 3 "" H 13000 12350 50  0001 C CNN
	1    13000 12350
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S4
U 1 1 61D44595
P 13100 10000
F 0 "S4" H 13700 10265 50  0000 C CNN
F 1 "B3J-2100" H 13700 10174 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 14150 10100 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 14150 10000 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 14150 9900 50  0001 L CNN "Description"
F 5 "10.5" H 14150 9800 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 14150 9700 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 14150 9600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 14150 9500 50  0001 L CNN "Arrow Part Number"
F 9 "" H 14150 9400 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 14150 9300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 14150 9200 50  0001 L CNN "Mouser Price/Stock"
	1    13100 10000
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S5
U 1 1 61D45775
P 13100 10650
F 0 "S5" H 13700 10915 50  0000 C CNN
F 1 "B3J-2100" H 13700 10824 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 14150 10750 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 14150 10650 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 14150 10550 50  0001 L CNN "Description"
F 5 "10.5" H 14150 10450 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 14150 10350 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 14150 10250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 14150 10150 50  0001 L CNN "Arrow Part Number"
F 9 "" H 14150 10050 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 14150 9950 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 14150 9850 50  0001 L CNN "Mouser Price/Stock"
	1    13100 10650
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S6
U 1 1 61D46961
P 13100 11300
F 0 "S6" H 13700 11565 50  0000 C CNN
F 1 "B3J-2100" H 13700 11474 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 14150 11400 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 14150 11300 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 14150 11200 50  0001 L CNN "Description"
F 5 "10.5" H 14150 11100 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 14150 11000 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 14150 10900 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 14150 10800 50  0001 L CNN "Arrow Part Number"
F 9 "" H 14150 10700 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 14150 10600 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 14150 10500 50  0001 L CNN "Mouser Price/Stock"
	1    13100 11300
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S7
U 1 1 61D48065
P 13100 11950
F 0 "S7" H 13700 12215 50  0000 C CNN
F 1 "B3J-2100" H 13700 12124 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 14150 12050 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 14150 11950 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 14150 11850 50  0001 L CNN "Description"
F 5 "10.5" H 14150 11750 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 14150 11650 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 14150 11550 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 14150 11450 50  0001 L CNN "Arrow Part Number"
F 9 "" H 14150 11350 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 14150 11250 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 14150 11150 50  0001 L CNN "Mouser Price/Stock"
	1    13100 11950
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S8
U 1 1 61D3E5A5
P 14950 10000
F 0 "S8" H 15550 10265 50  0000 C CNN
F 1 "B3J-2100" H 15550 10174 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 16000 10100 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16000 10000 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16000 9900 50  0001 L CNN "Description"
F 5 "10.5" H 16000 9800 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16000 9700 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16000 9600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16000 9500 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16000 9400 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16000 9300 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16000 9200 50  0001 L CNN "Mouser Price/Stock"
	1    14950 10000
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S9
U 1 1 61D40CBA
P 14950 10650
F 0 "S9" H 15550 10915 50  0000 C CNN
F 1 "B3J-2100" H 15550 10824 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 16000 10750 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16000 10650 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16000 10550 50  0001 L CNN "Description"
F 5 "10.5" H 16000 10450 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16000 10350 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16000 10250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16000 10150 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16000 10050 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16000 9950 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16000 9850 50  0001 L CNN "Mouser Price/Stock"
	1    14950 10650
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S10
U 1 1 61D41FFD
P 14950 11300
F 0 "S10" H 15550 11565 50  0000 C CNN
F 1 "B3J-2100" H 15550 11474 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 16000 11400 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16000 11300 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16000 11200 50  0001 L CNN "Description"
F 5 "10.5" H 16000 11100 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16000 11000 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16000 10900 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16000 10800 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16000 10700 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16000 10600 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16000 10500 50  0001 L CNN "Mouser Price/Stock"
	1    14950 11300
	1    0    0    -1  
$EndComp
$Comp
L B3J-2100:B3J-2100 S11
U 1 1 61D431B8
P 14950 11950
F 0 "S11" H 15550 12215 50  0000 C CNN
F 1 "B3J-2100" H 15550 12124 50  0000 C CNN
F 2 "B3J-2100:B3J2100" H 16000 12050 50  0001 L CNN
F 3 "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets-20/DSA-391676.pdf" H 16000 11950 50  0001 L CNN
F 4 "Tactile Switches TACTILE SWITCH Mechanical Key Switch (Hinged)" H 16000 11850 50  0001 L CNN "Description"
F 5 "10.5" H 16000 11750 50  0001 L CNN "Height"
F 6 "Omron Electronics" H 16000 11650 50  0001 L CNN "Manufacturer_Name"
F 7 "B3J-2100" H 16000 11550 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "" H 16000 11450 50  0001 L CNN "Arrow Part Number"
F 9 "" H 16000 11350 50  0001 L CNN "Arrow Price/Stock"
F 10 "653-B3J-2100" H 16000 11250 50  0001 L CNN "Mouser Part Number"
F 11 "https://www.mouser.co.uk/ProductDetail/Omron-Electronics/B3J-2100?qs=yi%2F4cWNpNMyoOIlU7jaueg%3D%3D" H 16000 11150 50  0001 L CNN "Mouser Price/Stock"
	1    14950 11950
	1    0    0    -1  
$EndComp
Wire Wire Line
	16150 11400 16250 11400
Wire Wire Line
	16150 10750 16250 10750
Wire Wire Line
	16150 10100 16250 10100
Wire Wire Line
	16450 12150 16450 9650
Wire Wire Line
	16400 11500 16400 9600
Wire Wire Line
	16350 10850 16350 9550
Wire Wire Line
	16250 10100 16250 10750
Connection ~ 16250 10750
Wire Wire Line
	16250 10750 16250 11400
Connection ~ 16250 11400
Wire Wire Line
	16250 11400 16250 12050
Wire Wire Line
	16250 12050 16150 12050
Wire Wire Line
	14600 12150 14600 9450
Wire Wire Line
	14000 9450 14600 9450
Wire Wire Line
	14550 11500 14550 9400
Wire Wire Line
	13950 9400 14550 9400
Wire Wire Line
	14500 10850 14500 9350
Wire Wire Line
	13900 9350 14500 9350
Wire Wire Line
	14450 10200 14450 9250
Connection ~ 14450 9250
Wire Wire Line
	14450 9250 16300 9250
Wire Wire Line
	13800 9250 14450 9250
Wire Wire Line
	14400 9300 14400 10100
Connection ~ 14400 9300
Wire Wire Line
	13850 9300 14400 9300
Wire Wire Line
	12800 10200 13100 10200
Wire Wire Line
	12850 10850 13100 10850
Wire Wire Line
	12900 11500 13100 11500
Wire Wire Line
	10600 12850 13100 12850
Wire Wire Line
	14300 12150 14600 12150
Wire Wire Line
	14300 12050 14400 12050
Wire Wire Line
	14300 11500 14550 11500
Wire Wire Line
	14300 11400 14400 11400
Connection ~ 14400 11400
Wire Wire Line
	14400 11400 14400 12050
Wire Wire Line
	14300 10850 14500 10850
Wire Wire Line
	14300 10750 14400 10750
Connection ~ 14400 10750
Wire Wire Line
	14400 10750 14400 11400
Wire Wire Line
	14300 10200 14450 10200
Wire Wire Line
	14300 10100 14400 10100
Connection ~ 14400 10100
Wire Wire Line
	14400 10100 14400 10750
Wire Wire Line
	14650 10200 14650 12900
Wire Wire Line
	14700 10850 14700 12950
Connection ~ 16450 9650
Wire Wire Line
	14200 9650 16450 9650
Connection ~ 16400 9600
Wire Wire Line
	16400 9600 16650 9600
Wire Wire Line
	14150 9600 16400 9600
Connection ~ 16350 9550
Wire Wire Line
	16350 9550 16600 9550
Wire Wire Line
	14100 9550 16350 9550
Wire Wire Line
	16150 12150 16450 12150
Wire Wire Line
	16150 11500 16400 11500
Wire Wire Line
	16150 10850 16350 10850
Wire Wire Line
	16150 10200 16300 10200
Wire Wire Line
	14400 9300 16250 9300
Wire Wire Line
	16300 10200 16300 9500
Wire Wire Line
	14050 9500 16300 9500
Wire Wire Line
	16250 10100 16250 9300
Connection ~ 16250 10100
Connection ~ 16250 9300
Wire Wire Line
	16250 9300 16350 9300
Wire Wire Line
	14650 10200 14950 10200
Wire Wire Line
	14700 10850 14950 10850
Wire Wire Line
	14950 11500 14750 11500
Wire Wire Line
	14750 11500 14750 13000
Wire Wire Line
	10550 12900 10550 8050
Wire Wire Line
	10550 8050 8000 8050
Wire Wire Line
	10550 12900 14650 12900
Wire Wire Line
	10500 12950 10500 8900
Wire Wire Line
	10500 8900 8000 8900
Wire Wire Line
	10500 12950 14700 12950
Wire Wire Line
	10450 13000 10450 8800
Wire Wire Line
	10450 8800 8000 8800
Wire Wire Line
	10450 13000 14750 13000
Wire Wire Line
	14950 12150 14950 13050
Wire Wire Line
	14950 13050 10400 13050
Wire Wire Line
	10400 13050 10400 8700
Wire Wire Line
	10400 8700 8000 8700
$Comp
L 4xxx:4504 U5
U 1 1 663F2E1B
P 3250 5350
F 0 "U5" H 3250 4361 50  0000 C CNN
F 1 "4504" H 3250 4270 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3250 4050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4504b.pdf" H 2600 5000 50  0001 C CNN
	1    3250 5350
	1    0    0    -1  
$EndComp
$Comp
L 4xxx:4504 U4
U 1 1 666D5823
P 3250 7450
F 0 "U4" H 3250 6461 50  0000 C CNN
F 1 "4504" H 3250 6370 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3250 6150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4504b.pdf" H 2600 7100 50  0001 C CNN
	1    3250 7450
	1    0    0    -1  
$EndComp
$Comp
L 4xxx:4504 U3
U 1 1 666D7DCA
P 3250 9550
F 0 "U3" H 3250 8561 50  0000 C CNN
F 1 "4504" H 3250 8470 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3250 8250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4504b.pdf" H 2600 9200 50  0001 C CNN
	1    3250 9550
	1    0    0    -1  
$EndComp
$Comp
L 4xxx:4504 U6
U 1 1 666DA20D
P 3250 3250
F 0 "U6" H 3250 2261 50  0000 C CNN
F 1 "4504" H 3250 2170 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 3250 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/cd4504b.pdf" H 2600 2900 50  0001 C CNN
	1    3250 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 8600 8200 8600
Wire Wire Line
	8200 8600 8200 9450
Wire Wire Line
	3850 9450 3850 9250
Wire Wire Line
	3850 9250 3700 9250
Wire Wire Line
	8000 8500 8250 8500
Wire Wire Line
	8250 8500 8250 9500
Wire Wire Line
	3800 9500 3800 9450
Wire Wire Line
	3800 9450 3700 9450
Wire Wire Line
	8000 8400 8300 8400
Wire Wire Line
	8300 8400 8300 9550
Wire Wire Line
	3800 9550 3800 9650
Wire Wire Line
	3800 9650 3700 9650
Wire Wire Line
	8000 8300 8350 8300
Wire Wire Line
	8350 8300 8350 9600
Wire Wire Line
	3850 9600 3850 9850
Wire Wire Line
	3850 9850 3700 9850
Wire Wire Line
	8000 8200 8400 8200
Wire Wire Line
	3900 9650 3900 10050
Wire Wire Line
	3900 10050 3700 10050
Wire Wire Line
	3900 9150 3900 9050
Wire Wire Line
	3900 9050 3700 9050
Wire Wire Line
	3950 9050 3950 7950
Wire Wire Line
	3950 7950 3700 7950
Wire Wire Line
	4000 8950 4000 7750
Wire Wire Line
	4000 7750 3700 7750
Wire Wire Line
	4050 8850 4050 7550
Wire Wire Line
	4050 7550 3700 7550
Wire Wire Line
	4100 8700 4100 7350
Wire Wire Line
	4100 7350 3700 7350
Wire Wire Line
	4150 8600 4150 7150
Wire Wire Line
	4150 7150 3700 7150
Wire Wire Line
	4200 8500 4200 6950
Wire Wire Line
	4200 6950 3700 6950
Wire Wire Line
	4250 8400 4250 5850
Wire Wire Line
	4250 5850 3700 5850
Wire Wire Line
	4300 8300 4300 5650
Wire Wire Line
	4300 5650 3700 5650
Wire Wire Line
	4350 8200 4350 5450
Wire Wire Line
	4350 5450 3700 5450
Wire Wire Line
	4400 5250 3700 5250
Wire Wire Line
	4450 8000 4450 5050
Wire Wire Line
	4450 5050 3700 5050
Wire Wire Line
	4450 8000 6100 8000
Wire Wire Line
	6100 8100 4400 8100
Wire Wire Line
	4400 5250 4400 8100
Wire Wire Line
	4350 8200 6100 8200
Wire Wire Line
	4300 8300 6100 8300
Wire Wire Line
	4250 8400 6100 8400
Wire Wire Line
	4200 8500 6100 8500
Wire Wire Line
	4150 8600 6100 8600
Wire Wire Line
	4100 8700 6100 8700
Wire Wire Line
	4050 8850 6100 8850
Wire Wire Line
	4000 8950 6100 8950
Wire Wire Line
	3950 9050 6100 9050
Wire Wire Line
	3900 9150 6100 9150
Wire Wire Line
	3850 9450 8200 9450
Wire Wire Line
	3800 9500 8250 9500
Wire Wire Line
	3800 9550 8300 9550
Wire Wire Line
	3850 9600 8350 9600
Wire Wire Line
	3900 9650 8400 9650
Wire Wire Line
	8400 8200 8400 9650
Wire Wire Line
	4500 4850 3700 4850
Wire Wire Line
	4550 3750 3700 3750
Wire Wire Line
	8000 4550 8200 4550
Wire Wire Line
	8000 4850 8200 4850
Wire Wire Line
	4500 7750 4500 4850
Wire Wire Line
	4500 7750 6100 7750
Wire Wire Line
	4550 7550 4550 3750
Wire Wire Line
	4550 7550 6100 7550
Wire Wire Line
	8000 4950 8400 4950
Wire Wire Line
	8400 4950 8400 3550
Wire Wire Line
	3700 3550 8400 3550
Wire Wire Line
	8000 5050 8450 5050
Wire Wire Line
	8450 5050 8450 3350
Wire Wire Line
	3700 3350 8450 3350
Wire Wire Line
	8000 5250 8500 5250
Wire Wire Line
	8500 5250 8500 3150
Wire Wire Line
	8500 3150 3700 3150
$Comp
L pecr11:PEC11R-4220F-S0024 ENC1
U 1 1 6922AA5D
P 10650 6350
F 0 "ENC1" H 11350 5385 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 11350 5476 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 10650 6750 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 10650 6850 50  0001 L CNN
F 4 "Enc" H 10650 6950 50  0001 L CNN "category"
F 5 "10mA" H 10650 7050 50  0001 L CNN "current rating"
F 6 "Yes" H 10650 7150 50  0001 L CNN "detend"
F 7 "Electromechanical" H 10650 7250 50  0001 L CNN "device class L1"
F 8 "Switches" H 10650 7350 50  0001 L CNN "device class L2"
F 9 "Encoders" H 10650 7450 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 10650 7550 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 10650 7650 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 10650 7750 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 10650 7850 50  0001 L CNN "height"
F 14 "yes" H 10650 7950 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 10650 8050 50  0001 L CNN "library id"
F 16 "Bourns" H 10650 8150 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 10650 8250 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 10650 8350 50  0001 L CNN "mouser part number"
F 19 "1" H 10650 8450 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 10650 8550 50  0001 L CNN "package"
F 21 "24" H 10650 8650 50  0001 L CNN "pulses per rev"
F 22 "yes" H 10650 8750 50  0001 L CNN "rohs"
F 23 "+70°C" H 10650 8850 50  0001 L CNN "temperature range high"
F 24 "30°C" H 10650 8950 50  0001 L CNN "temperature range low"
F 25 "5V" H 10650 9050 50  0001 L CNN "voltage rating DC"
	1    10650 6350
	-1   0    0    1   
$EndComp
$Comp
L pecr11:PEC11R-4220F-S0024 ENC2
U 1 1 6922EC85
P 10650 5200
F 0 "ENC2" H 11350 4235 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 11350 4326 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 10650 5600 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 10650 5700 50  0001 L CNN
F 4 "Enc" H 10650 5800 50  0001 L CNN "category"
F 5 "10mA" H 10650 5900 50  0001 L CNN "current rating"
F 6 "Yes" H 10650 6000 50  0001 L CNN "detend"
F 7 "Electromechanical" H 10650 6100 50  0001 L CNN "device class L1"
F 8 "Switches" H 10650 6200 50  0001 L CNN "device class L2"
F 9 "Encoders" H 10650 6300 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 10650 6400 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 10650 6500 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 10650 6600 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 10650 6700 50  0001 L CNN "height"
F 14 "yes" H 10650 6800 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 10650 6900 50  0001 L CNN "library id"
F 16 "Bourns" H 10650 7000 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 10650 7100 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 10650 7200 50  0001 L CNN "mouser part number"
F 19 "1" H 10650 7300 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 10650 7400 50  0001 L CNN "package"
F 21 "24" H 10650 7500 50  0001 L CNN "pulses per rev"
F 22 "yes" H 10650 7600 50  0001 L CNN "rohs"
F 23 "+70°C" H 10650 7700 50  0001 L CNN "temperature range high"
F 24 "30°C" H 10650 7800 50  0001 L CNN "temperature range low"
F 25 "5V" H 10650 7900 50  0001 L CNN "voltage rating DC"
	1    10650 5200
	-1   0    0    1   
$EndComp
$Comp
L pecr11:PEC11R-4220F-S0024 ENC3
U 1 1 69231399
P 10650 4050
F 0 "ENC3" H 11350 3085 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 11350 3176 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 10650 4450 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 10650 4550 50  0001 L CNN
F 4 "Enc" H 10650 4650 50  0001 L CNN "category"
F 5 "10mA" H 10650 4750 50  0001 L CNN "current rating"
F 6 "Yes" H 10650 4850 50  0001 L CNN "detend"
F 7 "Electromechanical" H 10650 4950 50  0001 L CNN "device class L1"
F 8 "Switches" H 10650 5050 50  0001 L CNN "device class L2"
F 9 "Encoders" H 10650 5150 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 10650 5250 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 10650 5350 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 10650 5450 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 10650 5550 50  0001 L CNN "height"
F 14 "yes" H 10650 5650 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 10650 5750 50  0001 L CNN "library id"
F 16 "Bourns" H 10650 5850 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 10650 5950 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 10650 6050 50  0001 L CNN "mouser part number"
F 19 "1" H 10650 6150 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 10650 6250 50  0001 L CNN "package"
F 21 "24" H 10650 6350 50  0001 L CNN "pulses per rev"
F 22 "yes" H 10650 6450 50  0001 L CNN "rohs"
F 23 "+70°C" H 10650 6550 50  0001 L CNN "temperature range high"
F 24 "30°C" H 10650 6650 50  0001 L CNN "temperature range low"
F 25 "5V" H 10650 6750 50  0001 L CNN "voltage rating DC"
	1    10650 4050
	-1   0    0    1   
$EndComp
$Comp
L pecr11:PEC11R-4220F-S0024 ENC4
U 1 1 69233DD6
P 10650 2900
F 0 "ENC4" H 11350 1935 50  0000 C CNN
F 1 "PEC11R-4220F-S0024" H 11350 2026 50  0000 C CNN
F 2 "pecr11:Bourns-PEC11R-4220F-S0024-0-0-0" H 10650 3300 50  0001 L CNN
F 3 "https://www.bourns.com/docs/product-datasheets/pec11r.pdf?sfvrsn=bb617cbf_6" H 10650 3400 50  0001 L CNN
F 4 "Enc" H 10650 3500 50  0001 L CNN "category"
F 5 "10mA" H 10650 3600 50  0001 L CNN "current rating"
F 6 "Yes" H 10650 3700 50  0001 L CNN "detend"
F 7 "Electromechanical" H 10650 3800 50  0001 L CNN "device class L1"
F 8 "Switches" H 10650 3900 50  0001 L CNN "device class L2"
F 9 "Encoders" H 10650 4000 50  0001 L CNN "device class L3"
F 10 "ROTARY ENCODER MECHANICAL 24PPR" H 10650 4100 50  0001 L CNN "digikey description"
F 11 "PEC11R-4220F-S0024-ND" H 10650 4200 50  0001 L CNN "digikey part number"
F 12 "Incremental" H 10650 4300 50  0001 L CNN "encoder type"
F 13 "27.3mm" H 10650 4400 50  0001 L CNN "height"
F 14 "yes" H 10650 4500 50  0001 L CNN "lead free"
F 15 "456a2eefc9d34d73" H 10650 4600 50  0001 L CNN "library id"
F 16 "Bourns" H 10650 4700 50  0001 L CNN "manufacturer"
F 17 "Encoders 20mm SHAFT w/SWITCH" H 10650 4800 50  0001 L CNN "mouser description"
F 18 "652-PEC11R-4220F-S24" H 10650 4900 50  0001 L CNN "mouser part number"
F 19 "1" H 10650 5000 50  0001 L CNN "number of circuits"
F 20 "ENC_PTH_12MM5_13MM4" H 10650 5100 50  0001 L CNN "package"
F 21 "24" H 10650 5200 50  0001 L CNN "pulses per rev"
F 22 "yes" H 10650 5300 50  0001 L CNN "rohs"
F 23 "+70°C" H 10650 5400 50  0001 L CNN "temperature range high"
F 24 "30°C" H 10650 5500 50  0001 L CNN "temperature range low"
F 25 "5V" H 10650 5600 50  0001 L CNN "voltage rating DC"
	1    10650 2900
	-1   0    0    1   
$EndComp
Wire Wire Line
	8000 6250 9350 6250
Wire Wire Line
	8000 6150 9350 6150
Wire Wire Line
	9350 5100 8200 5100
Wire Wire Line
	8200 5100 8200 4850
Wire Wire Line
	8250 5000 8250 4750
Wire Wire Line
	8000 4750 8250 4750
Wire Wire Line
	9350 3950 8250 3950
Wire Wire Line
	8250 3950 8250 4650
Wire Wire Line
	8000 4650 8250 4650
Wire Wire Line
	8200 4550 8200 3850
Wire Wire Line
	8200 3850 9350 3850
Wire Wire Line
	5750 7650 5750 2800
Wire Wire Line
	5750 2800 9350 2800
Wire Wire Line
	5750 7650 6100 7650
Wire Wire Line
	9350 2700 5700 2700
Wire Wire Line
	5700 2700 5700 7850
Wire Wire Line
	5700 7850 6100 7850
Wire Wire Line
	10750 6350 10750 6550
Wire Wire Line
	10750 6550 8400 6550
Wire Wire Line
	8400 6550 8400 5450
Wire Wire Line
	8400 5450 8000 5450
Wire Wire Line
	10550 6350 10750 6350
Wire Wire Line
	10550 5200 10800 5200
Wire Wire Line
	10800 5200 10800 6600
Wire Wire Line
	10800 6600 8350 6600
Wire Wire Line
	8350 6600 8350 5550
Wire Wire Line
	8350 5550 8000 5550
Wire Wire Line
	10550 4050 10850 4050
Wire Wire Line
	10850 4050 10850 6650
Wire Wire Line
	10850 6650 8300 6650
Wire Wire Line
	8300 6650 8300 5650
Wire Wire Line
	8300 5650 8000 5650
Wire Wire Line
	10550 2900 10900 2900
Wire Wire Line
	10900 2900 10900 6700
Wire Wire Line
	10900 6700 8250 6700
Wire Wire Line
	8250 6700 8250 5750
Wire Wire Line
	8250 5750 8000 5750
$Comp
L power:GND #PWR0108
U 1 1 6A3B2D86
P 10650 6100
F 0 "#PWR0108" H 10650 5850 50  0001 C CNN
F 1 "GND" H 10655 5927 50  0000 C CNN
F 2 "" H 10650 6100 50  0001 C CNN
F 3 "" H 10650 6100 50  0001 C CNN
	1    10650 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 5950 10650 5950
Wire Wire Line
	10650 5950 10650 6100
Wire Wire Line
	10650 5950 10650 5750
Wire Wire Line
	10650 5750 10550 5750
Connection ~ 10650 5950
Wire Wire Line
	10650 5750 10650 5650
Wire Wire Line
	10650 5650 10550 5650
Connection ~ 10650 5750
Wire Wire Line
	10650 5650 10650 4800
Wire Wire Line
	10650 4800 10550 4800
Connection ~ 10650 5650
Wire Wire Line
	10650 4800 10650 4600
Wire Wire Line
	10650 2200 10550 2200
Connection ~ 10650 4800
Wire Wire Line
	10550 2300 10650 2300
Connection ~ 10650 2300
Wire Wire Line
	10650 2300 10650 2200
Wire Wire Line
	10550 2500 10650 2500
Connection ~ 10650 2500
Wire Wire Line
	10650 2500 10650 2300
Wire Wire Line
	10550 3350 10650 3350
Connection ~ 10650 3350
Wire Wire Line
	10650 3350 10650 2500
Wire Wire Line
	10550 3450 10650 3450
Connection ~ 10650 3450
Wire Wire Line
	10650 3450 10650 3350
Wire Wire Line
	10550 3650 10650 3650
Connection ~ 10650 3650
Wire Wire Line
	10650 3650 10650 3450
Wire Wire Line
	10550 4500 10650 4500
Connection ~ 10650 4500
Wire Wire Line
	10650 4500 10650 3650
Wire Wire Line
	10550 4600 10650 4600
Connection ~ 10650 4600
Wire Wire Line
	10650 4600 10650 4500
Wire Wire Line
	9350 5850 9250 5850
Connection ~ 10650 2200
Wire Wire Line
	9350 2400 9250 2400
Connection ~ 9250 2400
Wire Wire Line
	9350 3550 9250 3550
Connection ~ 9250 3550
Wire Wire Line
	9250 3550 9250 2400
Wire Wire Line
	9350 4700 9250 4700
Connection ~ 9250 4700
Wire Wire Line
	9250 4700 9250 4450
$Comp
L power:VDD #PWR0110
U 1 1 6B221F44
P 3450 6550
F 0 "#PWR0110" H 3450 6400 50  0001 C CNN
F 1 "VDD" H 3465 6723 50  0000 C CNN
F 2 "" H 3450 6550 50  0001 C CNN
F 3 "" H 3450 6550 50  0001 C CNN
	1    3450 6550
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0111
U 1 1 6B222BD6
P 3450 4450
F 0 "#PWR0111" H 3450 4300 50  0001 C CNN
F 1 "VDD" H 3465 4623 50  0000 C CNN
F 2 "" H 3450 4450 50  0001 C CNN
F 3 "" H 3450 4450 50  0001 C CNN
	1    3450 4450
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0112
U 1 1 6B223A4B
P 3450 2350
F 0 "#PWR0112" H 3450 2200 50  0001 C CNN
F 1 "VDD" H 3465 2523 50  0000 C CNN
F 2 "" H 3450 2350 50  0001 C CNN
F 3 "" H 3450 2350 50  0001 C CNN
	1    3450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 2350 3450 2350
Wire Wire Line
	3350 4450 3450 4450
Wire Wire Line
	3350 6550 3450 6550
$Comp
L power:VDD #PWR0113
U 1 1 6B4D3381
P 3450 8650
F 0 "#PWR0113" H 3450 8500 50  0001 C CNN
F 1 "VDD" H 3465 8823 50  0000 C CNN
F 2 "" H 3450 8650 50  0001 C CNN
F 3 "" H 3450 8650 50  0001 C CNN
	1    3450 8650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 6B4D3F4C
P 2600 10750
F 0 "#PWR0114" H 2600 10500 50  0001 C CNN
F 1 "GND" H 2605 10577 50  0000 C CNN
F 2 "" H 2600 10750 50  0001 C CNN
F 3 "" H 2600 10750 50  0001 C CNN
	1    2600 10750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 10750 2600 10450
Wire Wire Line
	2600 4150 3250 4150
Wire Wire Line
	3250 6250 2600 6250
Connection ~ 2600 6250
Wire Wire Line
	2600 6250 2600 4150
Wire Wire Line
	3250 8350 2600 8350
Connection ~ 2600 8350
Wire Wire Line
	2600 8350 2600 6250
Wire Wire Line
	3250 10450 2600 10450
Connection ~ 2600 10450
Wire Wire Line
	2600 10450 2600 8350
Wire Wire Line
	3350 8650 3450 8650
$Comp
L power:VCC #PWR0115
U 1 1 6B95D924
P 2250 2350
F 0 "#PWR0115" H 2250 2200 50  0001 C CNN
F 1 "VCC" H 2265 2523 50  0000 C CNN
F 2 "" H 2250 2350 50  0001 C CNN
F 3 "" H 2250 2350 50  0001 C CNN
	1    2250 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2350 2250 2350
Wire Wire Line
	2250 2350 2250 4450
Wire Wire Line
	2250 8650 3150 8650
Connection ~ 2250 2350
Wire Wire Line
	3150 6550 2250 6550
Connection ~ 2250 6550
Wire Wire Line
	2250 6550 2250 8650
Wire Wire Line
	3150 4450 2250 4450
Connection ~ 2250 4450
Wire Wire Line
	2250 4450 2250 6550
$Comp
L power:VCC #PWR0116
U 1 1 6BD1282F
P 5550 4600
F 0 "#PWR0116" H 5550 4450 50  0001 C CNN
F 1 "VCC" H 5565 4773 50  0000 C CNN
F 2 "" H 5550 4600 50  0001 C CNN
F 3 "" H 5550 4600 50  0001 C CNN
	1    5550 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 5250 5550 5250
Wire Wire Line
	5550 5250 5550 4600
$Comp
L power:GND #PWR0117
U 1 1 6BEF56D9
P 6000 9800
F 0 "#PWR0117" H 6000 9550 50  0001 C CNN
F 1 "GND" H 6005 9627 50  0000 C CNN
F 2 "" H 6000 9800 50  0001 C CNN
F 3 "" H 6000 9800 50  0001 C CNN
	1    6000 9800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 9800 6000 7400
Wire Wire Line
	6000 5050 6100 5050
Wire Wire Line
	6100 5150 6000 5150
Connection ~ 6000 5150
Wire Wire Line
	6000 5150 6000 5050
Wire Wire Line
	6100 7300 6000 7300
Connection ~ 6000 7300
Wire Wire Line
	6000 7300 6000 5150
Wire Wire Line
	6100 7400 6000 7400
Connection ~ 6000 7400
Wire Wire Line
	6000 7400 6000 7300
Wire Wire Line
	8000 4450 9250 4450
Connection ~ 9250 4450
Wire Wire Line
	9250 4450 9250 3550
$Comp
L power:GND #PWR0119
U 1 1 6C78DAD7
P 11900 6400
F 0 "#PWR0119" H 11900 6150 50  0001 C CNN
F 1 "GND" H 11905 6227 50  0000 C CNN
F 2 "" H 11900 6400 50  0001 C CNN
F 3 "" H 11900 6400 50  0001 C CNN
	1    11900 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	11900 6400 11900 6350
Wire Wire Line
	11900 6350 11950 6350
Wire Wire Line
	11500 1750 11500 3550
Wire Wire Line
	11500 3550 11950 3550
Wire Wire Line
	11500 3550 11500 5750
Wire Wire Line
	11500 5750 11950 5750
Connection ~ 11500 3550
Wire Wire Line
	6100 4750 6100 1750
Wire Wire Line
	6100 1750 11500 1750
Wire Wire Line
	11950 3950 11450 3950
Wire Wire Line
	11450 3950 11450 6150
Wire Wire Line
	11450 6150 11950 6150
Wire Wire Line
	8000 6550 8200 6550
Wire Wire Line
	8200 6550 8200 6500
Wire Wire Line
	8200 6500 10950 6500
Wire Wire Line
	10950 6500 10950 3750
Wire Wire Line
	10950 3750 11950 3750
Wire Wire Line
	8000 6650 8200 6650
Wire Wire Line
	8200 6650 8200 6800
Wire Wire Line
	8200 6800 11000 6800
Wire Wire Line
	11000 6800 11000 5950
Wire Wire Line
	11000 5950 11950 5950
Wire Wire Line
	9250 1850 10650 1850
Wire Wire Line
	10650 1850 10650 2200
Wire Wire Line
	9250 1850 9250 2400
NoConn ~ 11950 4150
NoConn ~ 14300 4550
NoConn ~ 14300 4850
NoConn ~ 16100 4850
NoConn ~ 16100 5050
NoConn ~ 16100 6100
NoConn ~ 16100 6300
NoConn ~ 14300 6100
NoConn ~ 14300 5800
NoConn ~ 17800 4550
NoConn ~ 17800 4850
NoConn ~ 17800 5800
NoConn ~ 17800 6100
NoConn ~ 19600 6100
NoConn ~ 19600 6300
NoConn ~ 19600 5050
NoConn ~ 19600 4850
NoConn ~ 20400 4900
NoConn ~ 20400 4600
NoConn ~ 22200 4900
NoConn ~ 22200 5100
NoConn ~ 22200 6150
NoConn ~ 22200 6350
NoConn ~ 20400 6150
NoConn ~ 20400 5850
NoConn ~ 20400 7100
NoConn ~ 20400 7400
NoConn ~ 22200 7400
NoConn ~ 22200 7600
NoConn ~ 22200 8650
NoConn ~ 22200 8850
NoConn ~ 20400 8650
NoConn ~ 20400 8350
NoConn ~ 19600 7350
NoConn ~ 19600 7550
NoConn ~ 19600 8600
NoConn ~ 19600 8800
NoConn ~ 17800 8600
NoConn ~ 17800 8300
NoConn ~ 17800 7350
NoConn ~ 17800 7050
NoConn ~ 16100 7350
NoConn ~ 16100 7550
NoConn ~ 14300 7350
NoConn ~ 14300 7050
NoConn ~ 14300 8600
NoConn ~ 14300 8300
NoConn ~ 16100 8600
NoConn ~ 16100 8800
NoConn ~ 17800 9550
NoConn ~ 17800 9850
NoConn ~ 17800 10800
NoConn ~ 17800 11100
NoConn ~ 19600 11300
NoConn ~ 19600 11100
NoConn ~ 20400 11150
NoConn ~ 20400 10850
NoConn ~ 22200 11350
NoConn ~ 22200 11150
NoConn ~ 22200 10100
NoConn ~ 22200 9900
NoConn ~ 20400 9900
NoConn ~ 20400 9600
NoConn ~ 16150 10000
NoConn ~ 16150 10650
NoConn ~ 16150 11300
NoConn ~ 16150 11950
NoConn ~ 14300 11950
NoConn ~ 14300 11300
NoConn ~ 14300 10650
NoConn ~ 14300 10000
NoConn ~ 12500 11350
NoConn ~ 12500 10650
NoConn ~ 12500 10000
NoConn ~ 8000 5950
NoConn ~ 8000 5850
NoConn ~ 6100 7050
NoConn ~ 6100 6950
NoConn ~ 6100 6850
NoConn ~ 6100 6750
NoConn ~ 6100 6650
NoConn ~ 6100 6550
NoConn ~ 6100 6450
NoConn ~ 6100 6350
NoConn ~ 6100 6150
NoConn ~ 6100 6050
NoConn ~ 6100 5950
NoConn ~ 6100 5850
NoConn ~ 6100 5750
NoConn ~ 6100 5650
NoConn ~ 6100 5550
NoConn ~ 6100 5450
NoConn ~ 6100 4850
NoConn ~ 8000 4350
NoConn ~ 3700 2750
NoConn ~ 3700 2950
NoConn ~ 2800 2950
NoConn ~ 2800 2750
Text Label 13450 3250 0    20   ~ 0
U1CS0
Text Label 13450 3300 0    20   ~ 0
U1CS1
Text Label 13450 3350 0    20   ~ 0
U1CS2
Text Label 13450 3400 0    20   ~ 0
U1CS3
Text Label 13450 3450 0    20   ~ 0
U1CS4
Text Label 13450 3500 0    20   ~ 0
U1CS5
Text Label 13450 3550 0    20   ~ 0
U1CS6
Text Label 13450 3600 0    20   ~ 0
U1CS7
Text Label 13450 3650 0    20   ~ 0
U1CS8
Text Label 13450 3700 0    20   ~ 0
U1CS9
Text Label 13500 3750 0    20   ~ 0
U1CS10
Text Label 13550 3800 0    20   ~ 0
U1CS11
Text Label 8000 6850 0    20   ~ 0
SCL
Text Label 8000 6750 0    20   ~ 0
SDA
Text Label 9250 6150 0    20   ~ 0
ENC1B
Text Label 9250 6250 0    20   ~ 0
ENC1A
Wire Wire Line
	9250 5850 9250 4700
Wire Wire Line
	9350 5000 8250 5000
Text Label 9100 5000 0    20   ~ 0
ENC2B
Text Label 9100 5100 0    20   ~ 0
ENC2A
Text Label 9100 3850 0    20   ~ 0
ENC3B
Text Label 9100 3950 0    20   ~ 0
ENC3A
Text Label 9100 2700 0    20   ~ 0
ENC4B
Text Label 9100 2800 0    20   ~ 0
ENC4A
Text Label 10700 5200 0    20   ~ 0
ENC2S
Text Label 10650 6350 0    20   ~ 0
ENC1S
Text Label 10750 4050 0    20   ~ 0
ENC3S
Text Label 10800 2900 0    20   ~ 0
ENC4S
Text Label 13350 5450 0    20   ~ 0
U2CS0
Text Label 13350 5550 0    20   ~ 0
U2CS1
Text Label 13350 5650 0    20   ~ 0
U2CS2
Text Label 13350 5750 0    20   ~ 0
U2CS3
Text Label 13350 5850 0    20   ~ 0
U2CS4
Text Label 13350 5950 0    20   ~ 0
U2CS5
Text Label 13350 6050 0    20   ~ 0
U2CS6
Text Label 13350 6150 0    20   ~ 0
U2CS7
Text Label 13350 6250 0    20   ~ 0
U2CS8
Text Label 13350 6350 0    20   ~ 0
U2CS9
Text Label 13350 6450 0    20   ~ 0
U2CS10
Text Label 13350 6550 0    20   ~ 0
U2CS11
Text Label 11850 5950 0    20   ~ 0
U2IRQ
Text Label 11850 6150 0    20   ~ 0
SYNC
Text Label 11850 5750 0    20   ~ 0
RST
Text Label 11700 3750 0    20   ~ 0
U1IRQ
Text Label 11000 10200 0    20   ~ 0
SW1
Text Label 11000 10850 0    20   ~ 0
SW2
Text Label 11000 11550 0    20   ~ 0
SW3
Text Label 13050 10200 0    20   ~ 0
SW4
Text Label 13050 10850 0    20   ~ 0
SW5
Text Label 13050 11500 0    20   ~ 0
SW6
Text Label 13000 12850 0    20   ~ 0
SW7
Text Label 14900 10200 0    20   ~ 0
SW8
Text Label 14900 10850 0    20   ~ 0
SW9
Text Label 14900 11500 0    20   ~ 0
SW10
Text Label 14800 13050 0    20   ~ 0
SW11
NoConn ~ 8000 7200
NoConn ~ 8000 7100
NoConn ~ 8000 6450
NoConn ~ 8000 6350
NoConn ~ 8000 5350
NoConn ~ 6100 4950
Wire Wire Line
	1050 5450 1050 3350
Wire Wire Line
	1750 5450 1850 5450
Wire Wire Line
	1000 5550 1000 3550
Wire Wire Line
	1000 3550 2800 3550
Wire Wire Line
	1750 5550 1900 5550
Wire Wire Line
	1900 5550 1900 3750
Wire Wire Line
	1900 3750 2800 3750
Wire Wire Line
	950  5650 950  4850
Wire Wire Line
	950  4850 2800 4850
Wire Wire Line
	1750 5750 2000 5750
Wire Wire Line
	1750 5850 2800 5850
Wire Wire Line
	1750 5950 2200 5950
Wire Wire Line
	1750 6050 2150 6050
Wire Wire Line
	2150 6050 2150 7150
Wire Wire Line
	2100 6150 2100 7950
Wire Wire Line
	2100 7950 2800 7950
Wire Wire Line
	1750 6250 2050 6250
Wire Wire Line
	2000 6350 2000 9250
Wire Wire Line
	1950 6450 1950 10050
Wire Wire Line
	1950 10050 2800 10050
Wire Wire Line
	1250 5350 1250 4450
Wire Wire Line
	1250 4450 1750 4450
Connection ~ 1750 4450
Wire Wire Line
	1750 4450 2250 4450
Wire Wire Line
	1750 4450 1750 5350
Wire Wire Line
	1250 6450 1150 6450
Wire Wire Line
	1150 6450 1150 9850
Wire Wire Line
	1150 9850 2800 9850
Wire Wire Line
	1050 6250 1050 9050
Wire Wire Line
	1050 9050 2800 9050
Wire Wire Line
	1000 6150 1000 7750
Wire Wire Line
	1000 7750 2800 7750
Wire Wire Line
	900  5950 900  6950
Wire Wire Line
	900  6950 2800 6950
Wire Wire Line
	850  6900 2350 6900
Wire Wire Line
	2350 6900 2350 5650
Wire Wire Line
	2350 5650 2800 5650
Wire Wire Line
	800  5750 800  6850
Wire Wire Line
	800  6850 2300 6850
Wire Wire Line
	2300 6850 2300 5450
Wire Wire Line
	2000 5050 2800 5050
Wire Wire Line
	2000 5050 2000 5750
Wire Wire Line
	2200 5950 2200 7350
Wire Wire Line
	2800 7150 2150 7150
Wire Wire Line
	2050 6250 2050 9450
Wire Wire Line
	2800 9250 2000 9250
Wire Wire Line
	2800 9450 2050 9450
Wire Wire Line
	2800 9650 1100 9650
Wire Wire Line
	1100 6350 1100 9650
Wire Wire Line
	2800 7350 2200 7350
Wire Wire Line
	2800 5450 2300 5450
Wire Wire Line
	2800 3150 1850 3150
Wire Wire Line
	1850 3150 1850 5450
Wire Wire Line
	2800 3350 1050 3350
Wire Wire Line
	2800 7550 950  7550
Wire Wire Line
	2800 5250 1950 5250
Wire Wire Line
	1950 5250 1950 5650
Wire Wire Line
	11950 6850 11700 6850
Wire Wire Line
	11700 6850 11700 6750
Connection ~ 11700 6750
Wire Wire Line
	11950 6950 11700 6950
Wire Wire Line
	11700 6950 11700 6850
Connection ~ 11700 6850
Wire Wire Line
	11950 7050 11700 7050
Wire Wire Line
	11700 7050 11700 6950
Connection ~ 11700 6950
Wire Wire Line
	12950 6950 13050 6950
Wire Wire Line
	13050 6950 13050 7150
Connection ~ 13050 7150
Wire Wire Line
	12950 6850 13050 6850
Wire Wire Line
	13050 6850 13050 6950
Connection ~ 13050 6950
Wire Wire Line
	12950 6750 13050 6750
Wire Wire Line
	13050 6750 13050 6850
Connection ~ 13050 6850
NoConn ~ 12950 7050
NoConn ~ 11950 7150
Wire Wire Line
	12950 4550 13050 4550
Wire Wire Line
	13050 4550 13050 4750
Connection ~ 13050 4950
Wire Wire Line
	12950 4850 13050 4850
Connection ~ 13050 4850
Wire Wire Line
	13050 4850 13050 4950
Wire Wire Line
	12950 4750 13050 4750
Connection ~ 13050 4750
Wire Wire Line
	13050 4750 13050 4850
NoConn ~ 12950 4650
NoConn ~ 11950 4950
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 6D94AB69
P 1350 1150
F 0 "H1" H 1450 1199 50  0001 L CNN
F 1 "MountingHole_Pad" H 1450 1153 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 1350 1150 50  0001 C CNN
F 3 "~" H 1350 1150 50  0001 C CNN
	1    1350 1150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 6D94B9A4
P 1350 1550
F 0 "H2" H 1450 1599 50  0001 L CNN
F 1 "MountingHole_Pad" H 1450 1553 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 1350 1550 50  0001 C CNN
F 3 "~" H 1350 1550 50  0001 C CNN
	1    1350 1550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 6D94C676
P 2450 1150
F 0 "H3" H 2550 1199 50  0001 L CNN
F 1 "MountingHole_Pad" H 2550 1153 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 2450 1150 50  0001 C CNN
F 3 "~" H 2450 1150 50  0001 C CNN
	1    2450 1150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 6D94D501
P 2450 1550
F 0 "H4" H 2550 1599 50  0001 L CNN
F 1 "MountingHole_Pad" H 2550 1553 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 2450 1550 50  0001 C CNN
F 3 "~" H 2450 1550 50  0001 C CNN
	1    2450 1550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 6D94E4A4
P 3550 1150
F 0 "H5" H 3650 1199 50  0001 L CNN
F 1 "MountingHole_Pad" H 3650 1153 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 3550 1150 50  0001 C CNN
F 3 "~" H 3550 1150 50  0001 C CNN
	1    3550 1150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H6
U 1 1 6D94F272
P 3550 1550
F 0 "H6" H 3650 1599 50  0001 L CNN
F 1 "MountingHole_Pad" H 3650 1553 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.7mm_Pad_Via" H 3550 1550 50  0001 C CNN
F 3 "~" H 3550 1550 50  0001 C CNN
	1    3550 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1250 2450 1250
Wire Wire Line
	2450 1250 1650 1250
Connection ~ 2450 1250
Wire Wire Line
	1350 1650 1650 1650
Wire Wire Line
	2450 1650 3550 1650
Connection ~ 2450 1650
$Comp
L power:GND #PWR0109
U 1 1 6DF576B9
P 1650 1250
F 0 "#PWR0109" H 1650 1000 50  0001 C CNN
F 1 "GND" H 1655 1077 50  0000 C CNN
F 2 "" H 1650 1250 50  0001 C CNN
F 3 "" H 1650 1250 50  0001 C CNN
	1    1650 1250
	1    0    0    -1  
$EndComp
Connection ~ 1650 1250
Wire Wire Line
	1650 1250 1350 1250
$Comp
L power:GND #PWR0118
U 1 1 6DF586B1
P 1650 1650
F 0 "#PWR0118" H 1650 1400 50  0001 C CNN
F 1 "GND" H 1655 1477 50  0000 C CNN
F 2 "" H 1650 1650 50  0001 C CNN
F 3 "" H 1650 1650 50  0001 C CNN
	1    1650 1650
	1    0    0    -1  
$EndComp
Connection ~ 1650 1650
Wire Wire Line
	1650 1650 2450 1650
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 6E344525
P 4950 1350
F 0 "J1" H 4868 1025 50  0000 C CNN
F 1 "Power" H 4868 1116 50  0000 C CNN
F 2 "Connector_Molex:Molex_Micro-Fit_3.0_43650-0300_1x03_P3.00mm_Horizontal" H 4950 1350 50  0001 C CNN
F 3 "~" H 4950 1350 50  0001 C CNN
	1    4950 1350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 6E346166
P 5250 1450
F 0 "#PWR0120" H 5250 1200 50  0001 C CNN
F 1 "GND" H 5255 1277 50  0000 C CNN
F 2 "" H 5250 1450 50  0001 C CNN
F 3 "" H 5250 1450 50  0001 C CNN
	1    5250 1450
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0121
U 1 1 6E347053
P 5250 1250
F 0 "#PWR0121" H 5250 1100 50  0001 C CNN
F 1 "VCC" H 5265 1423 50  0000 C CNN
F 2 "" H 5250 1250 50  0001 C CNN
F 3 "" H 5250 1250 50  0001 C CNN
	1    5250 1250
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR0122
U 1 1 6E6ED952
P 5450 1250
F 0 "#PWR0122" H 5450 1100 50  0001 C CNN
F 1 "VDD" H 5465 1423 50  0000 C CNN
F 2 "" H 5450 1250 50  0001 C CNN
F 3 "" H 5450 1250 50  0001 C CNN
	1    5450 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1250 5250 1250
Wire Wire Line
	5150 1350 5450 1350
Wire Wire Line
	5450 1350 5450 1250
Wire Wire Line
	5150 1450 5250 1450
Wire Wire Line
	1750 6350 2000 6350
Wire Wire Line
	1750 6450 1950 6450
Wire Wire Line
	1050 5450 1250 5450
Wire Wire Line
	1250 5550 1000 5550
Wire Wire Line
	1250 5750 800  5750
Wire Wire Line
	1250 5850 850  5850
Wire Wire Line
	1250 5950 900  5950
Wire Wire Line
	1250 6050 950  6050
Wire Wire Line
	1250 6250 1050 6250
Wire Wire Line
	1250 6350 1100 6350
Wire Wire Line
	850  5850 850  6900
Wire Wire Line
	950  6050 950  7550
Wire Wire Line
	1250 6150 1000 6150
Wire Wire Line
	1750 6150 2100 6150
Wire Wire Line
	1250 5650 950  5650
Wire Wire Line
	1750 5650 1950 5650
$Comp
L Connector_Generic:Conn_02x12_Top_Bottom J2
U 1 1 6EC2077D
P 1550 5950
F 0 "J2" H 1600 6667 50  0000 C CNN
F 1 "Conn_02x12_Top_Bottom" H 1600 6576 50  0000 C CNN
F 2 "Connector_Molex:Molex_Micro-Fit_3.0_43045-2400_2x12_P3.00mm_Horizontal" H 1550 5950 50  0001 C CNN
F 3 "~" H 1550 5950 50  0001 C CNN
	1    1550 5950
	-1   0    0    1   
$EndComp
$EndSCHEMATC
