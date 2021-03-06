EESchema Schematic File Version 2  date Fri 24 Sep 2010 12:07:20 PM EDT
LIBS:power
LIBS:device
LIBS:emg_sym
LIBS:linear
LIBS:stage4-cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 11 44
Title "Stage 4 / Copyright 2010 Timothy L Hanson "
Date "23 sep 2010"
Rev ""
Comp "This design is free: redistribute or modify under the GPL v. 3 or later"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 8800 4250 0    60   ~ 0
array spacing = 0.75"
Wire Wire Line
	6850 3350 6850 3550
Wire Wire Line
	6350 3550 6200 3550
Connection ~ 2100 4800
Wire Wire Line
	2100 5050 2100 4600
Connection ~ 6600 3950
Wire Wire Line
	6600 3950 7050 3950
Wire Wire Line
	7050 3950 7050 4000
Connection ~ 6250 5150
Wire Wire Line
	6250 5100 6250 5150
Connection ~ 7400 4600
Wire Wire Line
	8650 3700 8650 4600
Connection ~ 8650 3850
Wire Wire Line
	8550 3850 8650 3850
Connection ~ 6700 5150
Wire Wire Line
	7600 4000 7600 5150
Wire Wire Line
	4750 3600 4750 3650
Wire Wire Line
	6700 5150 6700 5050
Connection ~ 6600 2700
Connection ~ 6600 4600
Connection ~ 5550 4600
Wire Wire Line
	6050 4600 6050 4400
Connection ~ 5900 2700
Wire Wire Line
	6600 4000 6600 2700
Connection ~ 3400 4600
Wire Wire Line
	3400 4450 3400 4600
Wire Wire Line
	2900 4050 2750 4050
Connection ~ 2750 4050
Wire Wire Line
	5900 2700 5900 3100
Wire Wire Line
	3700 2700 3700 3450
Connection ~ 5450 2900
Wire Wire Line
	5450 3050 5450 2900
Wire Wire Line
	5550 4600 5550 3450
Wire Wire Line
	5550 3450 5600 3450
Wire Wire Line
	5600 3650 5250 3650
Connection ~ 4450 4600
Wire Wire Line
	5250 3650 5250 3550
Wire Wire Line
	4450 4200 3950 4200
Wire Wire Line
	4200 3150 4200 3200
Wire Wire Line
	3950 4200 3950 4150
Connection ~ 3950 3650
Wire Wire Line
	1950 3800 1900 3800
Wire Wire Line
	2450 3800 2500 3800
Wire Wire Line
	2500 3800 2500 3650
Wire Wire Line
	2500 3650 2750 3650
Wire Wire Line
	2750 3550 2500 3550
Wire Wire Line
	2500 3550 2500 3400
Wire Wire Line
	2500 3400 2450 3400
Wire Wire Line
	1950 3400 1900 3400
Wire Wire Line
	3700 3550 3750 3550
Wire Wire Line
	3750 3550 3750 3150
Wire Wire Line
	3700 4600 3700 3750
Wire Wire Line
	4200 3600 4200 3650
Connection ~ 3950 3150
Connection ~ 3950 4600
Wire Wire Line
	5450 3450 5450 3650
Connection ~ 5450 3650
Wire Wire Line
	6200 3550 6200 2900
Wire Wire Line
	6200 2900 5250 2900
Wire Wire Line
	5250 2900 5250 3050
Wire Wire Line
	2750 3750 2750 5150
Wire Wire Line
	5900 5150 5900 4000
Connection ~ 3700 4600
Wire Wire Line
	2900 4600 2900 4450
Wire Wire Line
	3400 4050 3400 2700
Connection ~ 3700 2700
Wire Wire Line
	5900 4000 6050 4000
Wire Wire Line
	6600 4600 6600 4400
Connection ~ 6050 4600
Connection ~ 5900 5150
Wire Wire Line
	6700 2700 6700 2900
Wire Wire Line
	6700 4600 6700 4500
Connection ~ 2900 4600
Wire Wire Line
	2750 3750 2650 3750
Wire Wire Line
	2650 3750 2650 3450
Wire Wire Line
	2650 3450 2750 3450
Wire Wire Line
	4200 3650 3700 3650
Wire Wire Line
	3750 3150 4750 3150
Wire Wire Line
	4750 3150 4750 3200
Connection ~ 4200 3150
Wire Wire Line
	3400 2700 7600 2700
Wire Wire Line
	7600 2700 7600 3550
Connection ~ 6700 2700
Wire Wire Line
	7400 4600 7400 3850
Wire Wire Line
	7400 3850 7600 3850
Connection ~ 6700 4600
Wire Wire Line
	8650 3700 8550 3700
Connection ~ 7600 5150
Wire Wire Line
	2750 5150 7600 5150
Wire Wire Line
	6250 4700 6250 4600
Connection ~ 6250 4600
Wire Wire Line
	7050 4400 7050 4600
Connection ~ 7050 4600
Wire Wire Line
	8650 4600 2100 4600
Wire Wire Line
	6850 3550 6950 3550
Wire Wire Line
	6950 3550 6950 3700
Wire Wire Line
	6950 3700 7600 3700
$Comp
L TP TP81
U 1 1 4B608417
P 1900 5050
AR Path="/4B5E1FC8/4B607A5C/4B608417" Ref="TP81"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B608417" Ref="TP72"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B608417" Ref="TP63"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B608417" Ref="TP54"  Part="1" 
F 0 "TP54" H 1900 5150 60  0000 C CNN
F 1 "V0" H 2100 5050 60  0000 C CNN
F 2 "TP" H 1750 5000 60  0000 C CNN
	1    1900 5050
	-1   0    0    1   
$EndComp
Text Notes 8800 4000 0    60   ~ 0
e.g. those used in small portable mice
Text Notes 8800 3900 0    60   ~ 0
need to find some very thin USB cable for this 
$Comp
L ZENER D30
U 1 1 4B608142
P 7050 4200
AR Path="/4B5E1FC8/4B607A5C/4B608142" Ref="D30"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B608142" Ref="D28"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B608142" Ref="D26"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B608142" Ref="D24"  Part="1" 
F 0 "D24" H 7050 4350 50  0000 C CNN
F 1 "uclamp33" H 7050 4050 40  0000 C CNN
F 2 "SOD-523" H 7000 4400 60  0000 C CNN
	1    7050 4200
	0    1    1    0   
$EndComp
$Comp
L ZENER D29
U 1 1 4B608130
P 6250 4900
AR Path="/4B5E1FC8/4B607A5C/4B608130" Ref="D29"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B608130" Ref="D27"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B608130" Ref="D25"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B608130" Ref="D23"  Part="1" 
F 0 "D23" H 6250 5050 50  0000 C CNN
F 1 "uclamp33" H 6250 4750 40  0000 C CNN
F 2 "SOD-523" H 6200 5100 60  0000 C CNN
	1    6250 4900
	0    1    1    0   
$EndComp
$Comp
L R R88
U 1 1 4B607E53
P 6600 3550
AR Path="/4B5E1FC8/4B607A5C/4B607E53" Ref="R88"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B607E53" Ref="R81"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B607E53" Ref="R74"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B607E53" Ref="R67"  Part="1" 
F 0 "R67" V 6680 3550 50  0000 C CNN
F 1 "33" V 6600 3550 50  0000 C CNN
F 2 "0402" V 6730 3500 60  0000 C CNN
	1    6600 3550
	0    1    1    0   
$EndComp
Text Notes 8800 3800 0    60   ~ 0
but it's easy!
Text Notes 8800 3700 0    60   ~ 0
to reuse the USB A connector here..
Text Notes 8800 3600 0    60   ~ 0
yea, I know it's not a good idea 
$Comp
L FCI_USB_B U185
U 1 1 4B607B9C
P 8050 3800
AR Path="/4B5E1FC8/4B607A5C/4B607B9C" Ref="U185"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B607B9C" Ref="U182"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B607B9C" Ref="U179"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B607B9C" Ref="U176"  Part="1" 
F 0 "U176" H 8000 3200 60  0000 C CNN
F 1 "FCI_USB_B" H 8000 3350 60  0000 C CNN
F 2 "FCI_USB_A" H 8050 3450 60  0000 C CNN
	1    8050 3800
	1    0    0    -1  
$EndComp
$Comp
L C C216
U 1 1 4B607777
P 4750 3400
AR Path="/4B5E1FC8/4B607A5C/4B607777" Ref="C216"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B607777" Ref="C207"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B607777" Ref="C198"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B607777" Ref="C189"  Part="1" 
F 0 "C189" H 4800 3500 50  0000 L CNN
F 1 "10uf" H 4800 3300 50  0000 L CNN
F 2 "0603" H 4550 3500 60  0000 C CNN
	1    4750 3400
	-1   0    0    1   
$EndComp
$Comp
L TP TP80
U 1 1 4B5E8458
P 1900 4800
AR Path="/4B5E1FC8/4B607A5C/4B5E8458" Ref="TP80"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E8458" Ref="TP71"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E8458" Ref="TP62"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E8458" Ref="TP53"  Part="1" 
F 0 "TP53" H 1900 4900 60  0000 C CNN
F 1 "V0" H 2100 4800 60  0000 C CNN
F 2 "TP" H 1750 4750 60  0000 C CNN
	1    1900 4800
	-1   0    0    1   
$EndComp
$Comp
L TP TP79
U 1 1 4B5E8450
P 1900 4600
AR Path="/4B5E1FC8/4B607A5C/4B5E8450" Ref="TP79"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E8450" Ref="TP70"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E8450" Ref="TP61"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E8450" Ref="TP52"  Part="1" 
F 0 "TP52" H 1900 4500 60  0000 C CNN
F 1 "V0" H 2100 4600 60  0000 C CNN
F 2 "TP" H 1750 4550 60  0000 C CNN
	1    1900 4600
	-1   0    0    1   
$EndComp
Text HLabel 6950 3550 2    60   Input ~ 0
OUT
Text HLabel 6700 4500 2    60   Input ~ 0
V0
Text HLabel 6700 5050 2    60   Input ~ 0
V-
Text HLabel 6700 2900 2    60   Input ~ 0
V+
$Comp
L TP TP82
U 1 1 4B5E83BB
P 6900 2700
AR Path="/4B5E1FC8/4B607A5C/4B5E83BB" Ref="TP82"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E83BB" Ref="TP73"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E83BB" Ref="TP64"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E83BB" Ref="TP55"  Part="1" 
F 0 "TP55" H 6900 2700 60  0000 C CNN
F 1 "V+" H 7100 2700 60  0000 C CNN
F 2 "TP" H 6750 2650 60  0000 C CNN
	1    6900 2700
	1    0    0    -1  
$EndComp
$Comp
L TP TP85
U 1 1 4B5E83A8
P 6900 5150
AR Path="/4B5E1FC8/4B607A5C/4B5E83A8" Ref="TP85"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E83A8" Ref="TP76"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E83A8" Ref="TP67"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E83A8" Ref="TP58"  Part="1" 
F 0 "TP58" H 6900 5150 60  0000 C CNN
F 1 "V-" H 7100 5150 60  0000 C CNN
F 2 "TP" H 6750 5100 60  0000 C CNN
	1    6900 5150
	1    0    0    -1  
$EndComp
$Comp
L TP TP84
U 1 1 4B5E8390
P 6900 4600
AR Path="/4B5E1FC8/4B607A5C/4B5E8390" Ref="TP84"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E8390" Ref="TP75"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E8390" Ref="TP66"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E8390" Ref="TP57"  Part="1" 
F 0 "TP57" H 6900 4600 60  0000 C CNN
F 1 "V0" H 7100 4600 60  0000 C CNN
F 2 "TP" H 6750 4550 60  0000 C CNN
	1    6900 4600
	1    0    0    -1  
$EndComp
$Comp
L C C219
U 1 1 4B5E837A
P 6600 4200
AR Path="/4B5E1FC8/4B607A5C/4B5E837A" Ref="C219"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E837A" Ref="C210"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E837A" Ref="C201"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E837A" Ref="C192"  Part="1" 
F 0 "C192" H 6650 4300 50  0000 L CNN
F 1 "1uf" H 6650 4100 50  0000 L CNN
F 2 "0402" H 6850 4200 60  0000 C CNN
	1    6600 4200
	1    0    0    -1  
$EndComp
$Comp
L C C218
U 1 1 4B5E8374
P 6050 4200
AR Path="/4B5E1FC8/4B607A5C/4B5E8374" Ref="C218"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E8374" Ref="C209"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E8374" Ref="C200"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E8374" Ref="C191"  Part="1" 
F 0 "C191" H 6100 4300 50  0000 L CNN
F 1 "1uf" H 6100 4100 50  0000 L CNN
F 2 "0402" H 6300 4200 60  0000 C CNN
	1    6050 4200
	1    0    0    -1  
$EndComp
$Comp
L C C212
U 1 1 4B5E8316
P 3400 4250
AR Path="/4B5E1FC8/4B607A5C/4B5E8316" Ref="C212"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E8316" Ref="C203"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E8316" Ref="C194"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E8316" Ref="C185"  Part="1" 
F 0 "C185" H 3450 4350 50  0000 L CNN
F 1 "1uf" H 3450 4150 50  0000 L CNN
F 2 "0402" H 3650 4250 60  0000 C CNN
	1    3400 4250
	1    0    0    -1  
$EndComp
$Comp
L C C211
U 1 1 4B5E82D0
P 2900 4250
AR Path="/4B5E1FC8/4B607A5C/4B5E82D0" Ref="C211"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E82D0" Ref="C202"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E82D0" Ref="C193"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E82D0" Ref="C184"  Part="1" 
F 0 "C184" H 2950 4350 50  0000 L CNN
F 1 "1uf" H 2950 4150 50  0000 L CNN
F 2 "0402" H 3150 4250 60  0000 C CNN
	1    2900 4250
	1    0    0    -1  
$EndComp
$Comp
L TP TP83
U 1 1 4B5E82A4
P 7050 3350
AR Path="/4B5E1FC8/4B607A5C/4B5E82A4" Ref="TP83"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E82A4" Ref="TP74"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E82A4" Ref="TP65"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E82A4" Ref="TP56"  Part="1" 
F 0 "TP56" H 7050 3350 60  0000 C CNN
F 1 "OUT" H 7250 3350 60  0000 C CNN
F 2 "TP" H 6900 3300 60  0000 C CNN
	1    7050 3350
	1    0    0    -1  
$EndComp
$Comp
L OPA348 U184
U 1 1 4B5E81FC
P 5850 3550
AR Path="/4B5E1FC8/4B607A5C/4B5E81FC" Ref="U184"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E81FC" Ref="U181"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E81FC" Ref="U178"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E81FC" Ref="U175"  Part="1" 
F 0 "U175" H 6050 3400 60  0000 C CNN
F 1 "LMV321" H 6200 3750 60  0000 C CNN
F 2 "SC-70-5" H 5550 3250 60  0000 C CNN
	1    5850 3550
	1    0    0    -1  
$EndComp
$Comp
L C C217
U 1 1 4B5E2EEF
P 5450 3250
AR Path="/4B5E1FC8/4B607A5C/4B5E2EEF" Ref="C217"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2EEF" Ref="C208"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2EEF" Ref="C199"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2EEF" Ref="C190"  Part="1" 
F 0 "C190" H 5500 3350 50  0000 L CNN
F 1 "270pf" H 5500 3150 50  0000 L CNN
F 2 "0402" H 5700 3250 60  0000 C CNN
	1    5450 3250
	1    0    0    -1  
$EndComp
$Comp
L R R87
U 1 1 4B5E2EB2
P 5250 3300
AR Path="/4B5E1FC8/4B607A5C/4B5E2EB2" Ref="R87"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2EB2" Ref="R80"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2EB2" Ref="R73"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2EB2" Ref="R66"  Part="1" 
F 0 "R66" V 5330 3300 50  0000 C CNN
F 1 "170k" V 5250 3300 50  0000 C CNN
F 2 "0402" V 5380 3250 60  0000 C CNN
	1    5250 3300
	-1   0    0    1   
$EndComp
$Comp
L R R86
U 1 1 4B5E2EA6
P 5000 3650
AR Path="/4B5E1FC8/4B607A5C/4B5E2EA6" Ref="R86"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2EA6" Ref="R79"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2EA6" Ref="R72"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2EA6" Ref="R65"  Part="1" 
F 0 "R65" V 5080 3650 50  0000 C CNN
F 1 "10k" V 5000 3650 50  0000 C CNN
F 2 "0402" V 5130 3600 60  0000 C CNN
	1    5000 3650
	0    1    1    0   
$EndComp
Text Notes 2200 3050 0    60   ~ 0
noise-cancel rolloff at ~ 4.8kHz
Text Notes 4250 4700 0    60   ~ 0
highpass at 1.3Hz
$Comp
L C C215
U 1 1 4B5E2BEE
P 4450 4400
AR Path="/4B5E1FC8/4B607A5C/4B5E2BEE" Ref="C215"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2BEE" Ref="C206"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2BEE" Ref="C197"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2BEE" Ref="C188"  Part="1" 
F 0 "C188" H 4500 4500 50  0000 L CNN
F 1 "22uf" H 4500 4300 50  0000 L CNN
F 2 "0805" H 4700 4400 60  0000 C CNN
	1    4450 4400
	1    0    0    -1  
$EndComp
$Comp
L C C214
U 1 1 4B5E2631
P 4200 3400
AR Path="/4B5E1FC8/4B607A5C/4B5E2631" Ref="C214"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2631" Ref="C205"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2631" Ref="C196"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2631" Ref="C187"  Part="1" 
F 0 "C187" H 4250 3500 50  0000 L CNN
F 1 "1.5nf" H 4250 3300 50  0000 L CNN
F 2 "0402" H 4200 3100 60  0000 C CNN
	1    4200 3400
	1    0    0    -1  
$EndComp
$Comp
L C C213
U 1 1 4B5E2425
P 3950 4400
AR Path="/4B5E1FC8/4B607A5C/4B5E2425" Ref="C213"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2425" Ref="C204"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2425" Ref="C195"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2425" Ref="C186"  Part="1" 
F 0 "C186" H 4000 4500 50  0000 L CNN
F 1 "22uf" H 4000 4300 50  0000 L CNN
F 2 "0805" H 4200 4400 60  0000 C CNN
	1    3950 4400
	1    0    0    -1  
$EndComp
$Comp
L R R84
U 1 1 4B5E23F1
P 3950 3400
AR Path="/4B5E1FC8/4B607A5C/4B5E23F1" Ref="R84"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E23F1" Ref="R77"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E23F1" Ref="R70"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E23F1" Ref="R63"  Part="1" 
F 0 "R63" V 4030 3400 50  0000 C CNN
F 1 "33k" V 3950 3400 50  0000 C CNN
F 2 "0402" V 4080 3350 60  0000 C CNN
	1    3950 3400
	-1   0    0    1   
$EndComp
$Comp
L R R85
U 1 1 4B5E23EA
P 3950 3900
AR Path="/4B5E1FC8/4B607A5C/4B5E23EA" Ref="R85"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E23EA" Ref="R78"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E23EA" Ref="R71"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E23EA" Ref="R64"  Part="1" 
F 0 "R64" V 4030 3900 50  0000 C CNN
F 1 "2.7k" V 3950 3900 50  0000 C CNN
F 2 "0402" V 4080 3850 60  0000 C CNN
	1    3950 3900
	-1   0    0    1   
$EndComp
$Comp
L TP TP78
U 1 1 4B5E23B7
P 1700 3800
AR Path="/4B5E1FC8/4B607A5C/4B5E23B7" Ref="TP78"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E23B7" Ref="TP69"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E23B7" Ref="TP60"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E23B7" Ref="TP51"  Part="1" 
F 0 "TP51" H 1700 3900 60  0000 C CNN
F 1 "IN+" H 1800 3800 60  0000 C CNN
F 2 "TP" H 1550 3750 60  0000 C CNN
	1    1700 3800
	-1   0    0    1   
$EndComp
$Comp
L TP TP77
U 1 1 4B5E23AE
P 1700 3400
AR Path="/4B5E1FC8/4B607A5C/4B5E23AE" Ref="TP77"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E23AE" Ref="TP68"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E23AE" Ref="TP59"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E23AE" Ref="TP50"  Part="1" 
F 0 "TP50" H 1700 3500 60  0000 C CNN
F 1 "IN-" H 1800 3400 60  0000 C CNN
F 2 "TP" H 1550 3350 60  0000 C CNN
	1    1700 3400
	-1   0    0    1   
$EndComp
$Comp
L R R83
U 1 1 4B5E2389
P 2200 3800
AR Path="/4B5E1FC8/4B607A5C/4B5E2389" Ref="R83"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2389" Ref="R76"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2389" Ref="R69"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2389" Ref="R62"  Part="1" 
F 0 "R62" V 2280 3800 50  0000 C CNN
F 1 "10k" V 2200 3800 50  0000 C CNN
F 2 "0402" V 2330 3750 60  0000 C CNN
	1    2200 3800
	0    1    1    0   
$EndComp
$Comp
L R R82
U 1 1 4B5E236D
P 2200 3400
AR Path="/4B5E1FC8/4B607A5C/4B5E236D" Ref="R82"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E236D" Ref="R75"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E236D" Ref="R68"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E236D" Ref="R61"  Part="1" 
F 0 "R61" V 2280 3400 50  0000 C CNN
F 1 "10k" V 2200 3400 50  0000 C CNN
F 2 "0402" V 2330 3350 60  0000 C CNN
	1    2200 3400
	0    1    1    0   
$EndComp
$Comp
L MAX4208 U183
U 1 1 4B5E2341
P 3200 3600
AR Path="/4B5E1FC8/4B607A5C/4B5E2341" Ref="U183"  Part="1" 
AR Path="/4B5E1FC8/4B6079F1/4B5E2341" Ref="U180"  Part="1" 
AR Path="/4B5E1FC8/4B6079DB/4B5E2341" Ref="U177"  Part="1" 
AR Path="/4B5E1FC8/4B5E2312/4B5E2341" Ref="U174"  Part="1" 
F 0 "U174" H 3200 3350 60  0000 C CNN
F 1 "MAX4208" H 3250 3850 60  0000 C CNN
F 2 "MSOP-8" H 3140 3290 60  0000 C CNN
	1    3200 3600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
