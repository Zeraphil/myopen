#include <cdefBF537.h>
#include "memory.h"
#include "util.h"
#include "lcd.h"
#include "ethernet.h"
#include "usb.h"

u32	g_rptr ; //recieve (SPORT) pointer.  (yea I know it's not a u32*)
u32	g_tptr ; // transmit (ethernet) pointer. (actually points to external sdram)
u16 	g_tchan ; //transmit channel counter
u32 g_excregs[14] ; //the regular data registers + pointer registers. 

int main() {
	// disable cache. no imem_control on this proc? 
	*pDMEM_CONTROL = 0x00001001; 
	asm volatile("csync"); 
	// disable the serial ports (for now)
	*pSPORT0_TCR1 = 0; 
	*pSPORT0_TCR2 = 0; 
	*pSPORT0_RCR1 = 0; 
	*pSPORT0_RCR2 = 0; 
	*pSPORT0_TCLKDIV = 0; 
	*pSPORT0_RCLKDIV = 0; 
	*pSPORT0_TFSDIV = 0; 
	*pSPORT0_RFSDIV = 0; 
	
	*pSPORT1_TCR1 = 0; 
	*pSPORT1_TCR2 = 0; 
	*pSPORT1_RCR1 = 0; 
	*pSPORT1_RCR2 = 0; 
	*pSPORT1_TCLKDIV = 0; 
	*pSPORT1_RCLKDIV = 0; 
	*pSPORT1_TFSDIV = 0; 
	*pSPORT1_RFSDIV = 0; 
	
	/* port mux: (page 862)
	0000 - default
	1110 - tsclk1,tfs1,dt1pri ; rsclk1,rfs1,dr1pri; dr1sec, dt1sec
	0000 - uart 1 tx/rx (but we don't actually use it)
	0000 - uart0 tx/rx ; dr0sec, dt0sec ; tfs0, dt0pri
	*/
	*pPORT_MUX = 0x0e00 ; 
	/* port f: 
	0	uart0 tx 		(peripheral enabled)
	1	uart0 rx 		(peripheral enabled)
	2	uart1 tx 		(gpio, input)
	3	uart1 rx 		(gpio, input)					0x3 0b0011 ; 0x0 0b0000 ; 0x0 0b0000
	4	lcd_cs			(gpio, output)
	5	nordic IRQ 	(gpio, input)
	6	nordic CSN	(gpio output)
	7	usb_gpx		(gpio input, usb output) 	0x0 0b0000 ; 0x5 0b0101 ; 0xa 0b1010
	8	usb_int			(gpio input, usb output)
	9	nordic CE		(gpio output)
	10 flash _cs		(peripheral spi output) (gpio output in bootloader?)
	11 mosi			(peripheral spi output)	0xc 0b1100 ; 0x2 0b0010 ; 0x1 0b0001
	12 miso			(peripheral spi input)
	13 sclk				(peripheral spi output)
	14 usb_ss			(gpio output, usb input)
	15 sr_load		(gpio output)					0x3 0b0011 ; 0xc 0b1100 ; 0x0 0b0000
	*/
	*pPORTF_FER = 0x3803 ;
	*pPORTFIO_DIR = 0xc650 ; 
	*pPORTFIO_INEN = 0x01a0 ; 
	/* port g:
	0-7	header		(gpio output)					0x00 ; 0xff ; 0x00
	8	dr1sec			(peripheral input)
	9	dt1sec			(gpio output)
	10 rsclk1			(peripheral input, slave)
	11 rfs1				(peripheral input, slave)	0xd 0b1101 ; 0x2 0b0010 ; 0x0
	12 dr1pri			(peripheral input)
	13 tsclk1			(peripheral output, master)
	14 tfs1				(peripheral output, master)
	15 dt1pri			(peripheral ,to ADCs)		0xf 0b1111 ; 0x0 ; 0x0
	*/
	*pPORTG_FER = 0xfd00 ; 
	*pPORTGIO_DIR = 0x02ff ; 
	*pPORTGIO_INEN = 0x0000 ; 
	/* port h:  all are hooked to the ethernet PHY */
	*pPORTH_FER = 0xffff ; 
	*pPORTHIO_DIR = 0 ; 
	*pPORTHIO_INEN = 0 ; 
	/* port j:  (controlled by PORT_MUX register, no gpio)
	0	mdc				(peripheral ethernet)
	1	mdio			(peripheral ethernet)
	2	twi sclk		(peripheral o.c.)
	3	twi sda			(peripheral o.c.)
	4	dr0sec			(peripheral input)
	5	nc				()
	6	rsclk0			(peripheral input, slave)
	7	rfs0				(peripheral input, slave)
	8	dr0pri			(peripheral input)
	9	tsclk0 			lcd_clk, peripheral output, master
	10 nc				()
	11 dt0pri			lcd_data, peripheral	
	*/
	LCD_init() ; 
	*pUART0_IER = 0; //turn off interrupts, turn them on later.
	*pUART0_MCR = 0; 
	*pUART0_LCR =  0x0080; //enable access to divisor latch. 
	*pUART0_DLL = 65; //see page 810 of the BF537 hardware ref. this is the lower byte of the divisor.
	*pUART0_DLH = 0;  //the system clock is 120Mhz. baud rate is 115200. 
	*pUART0_LCR = 0x0003; //parity disabled, 1 stop bit, 8 bit word. 
	*pUART0_GCTL = 0x0001; //enable the clock.
	printf_int("Myopen svn v.", /*SVN_VERSION{*/68/*}*/ ) ; 
	printf_str("\n"); 
	printf_str("checking SDRAM...\n"); 
	unsigned short* p; 
	p = 0; 
	int i; 
	for(i=0; i<4*1024*1024; i++){ //memory size = 32mbytes.
		(*p++) = 0x5555; 
		(*p++) = 0xAAAA; 
		(*p++) = 0x3333; 
		(*p++) = 0xCCCC; 
	}
	p = 0; 
	unsigned short s; 
	for(i=0; i<4*1024*1024; i++){
		s = *p++; 
		if(s!= 0x5555) {
			printf_hex("mem err @ ",i); 
			printf_hex("\ngot:", s); 
			printf_str("\n"); 
			delay(400000); 
		}
		s = *p++; 
		if(s!= 0xAAAA) printf_hex("mem err @ ",i); 
		s = *p++; 
		if(s!= 0x3333) printf_hex("mem err @ ",i); 
		s = *p++; 
		if(s!= 0xCCCC) printf_hex("mem err @ ",i); 
	}
	printf_str("memory check done.\n"); 
	//let's test the UART here. 
	//fix up the UART.  it will be useful for debugging. 
	usb_init(); 
	int etherr = bfin_EMAC_init(); 
	if(!etherr) DHCP_req	(); 
	//turn on the SPORTS last, as the ethernet has to be ready to blast out the data. 
	printf_str("turning on SPORTs\n"); 
	g_tchan = 0; 
	g_tptr = 0; 
	g_rptr = 0; 
	//set up the receive first, since it is controled by the transmit sport. 
	*pSPORT0_RCR2 = 0x0100 + 19; //enable second side, serial word length 20
	*pSPORT1_RCR2 = 0x0100 + 19; 
	/* RCR = 0100 0100 0000 0001
	sample data on rising edge, 
	early frame syncs,
	active high frame syncs,
	require frame sync for every word, 
	external frame sync, 
	msb first, 
	zero fill data, 
	external recieve clock,  
	enable. */
	*pSPORT0_RCR1 = 0x4401 ; 
	*pSPORT1_RCR1 = 0x4401 ; 
	//transmit port
	*pSPORT1_TCLKDIV = 149 ; //120Mhz / 300 = 400k / 25 = 16k / 4 = 4 ksps/ch
	*pSPORT1_TFSDIV = 24 ; //25 clocks between assertions of the frame sync
	*pSPORT1_TCR2 = 19; //word length 20, secondary disabled. 
	// TCR = 0100 0110 0000 0011
	*pSPORT1_TCR1 = 0x4603 ; 
	
	u8* data; 
	while(1) {
		if(!etherr) bfin_EMAC_recv( &data ); //listen for packets? (and respond)
		if(!etherr && bfin_EMAC_send_check() ){
			if(g_rptr < g_tptr) g_tptr = 0; 
			if(g_rptr - g_tptr >= 1024){//then we have at least one packet to send.
				data = udp_packet_setup(1024 + 4); 
				//copy the data from SDRAM.. (starting @ 0x0000 0000, looping 256k bytes)
				//include a copy of the tptr, so that we can (possibly) reorder it. 
				(*(u32*)data) = g_tptr; 
				data += 4; 
				memcpy((u8*)(g_rptr & 0x0003ffff), data, 1024); 
				g_tptr += 1024 ; 
				bfin_EMAC_send_nocopy(); 
			}
		}
		usb_intr(); //check to see if there are any USB events to respond to.
		*pPORTFIO_TOGGLE = 0x40 ; //toggle the nordic CSN pin.
	}
	return 0; 
}
void exception_report(unsigned long seqstat, unsigned long retx){
	printf_str("Exception!!\n"); 
	printf_hex("hwerr:", (seqstat >> 14) & 0x1f); 
	printf_str("\n"); 
	printf_hex("excause:", seqstat & 0x3f); 
	printf_str("\n"); 
	printf_hex("retx:", retx); 
	printf_str("\n"); 
	printf_hex("r0:", g_excregs[0]); 
	printf_str("\n"); 
	printf_hex("r1:", g_excregs[1]); 
	printf_str("\n"); 
	printf_hex("r2:", g_excregs[2]); 
	printf_str("\n"); 
	printf_hex("r3:", g_excregs[3]); 
	printf_str("\n"); 
	printf_hex("r4:", g_excregs[4]); 
	printf_str("\n"); 
	printf_hex("r5:", g_excregs[5]); 
	printf_str("\n"); 
	printf_hex("r6:", g_excregs[6]); 
	printf_str("\n"); 
	printf_hex("r7:", g_excregs[7]); 
	printf_str("\n"); 
	printf_hex("p0:", g_excregs[8]); 
	printf_str("\n"); 
	printf_hex("p1:", g_excregs[9]); 
	printf_str("\n"); 
	printf_hex("p2:", g_excregs[10]); 
	printf_str("\n"); 
	printf_hex("p3:", g_excregs[11]); 
	printf_str("\n"); 
	printf_hex("p4:", g_excregs[12]); 
	printf_str("\n"); 
	printf_hex("p5:", g_excregs[13]); 
	printf_str("\n"); 
	//would be nice to print out the registers, too. 
	while(1) {
		asm volatile("nop"); 
	}
}
