/*
 * timer.c
 *
 *  Created on: 2020/6/9
 *      Author: Administrator
 */
#include"sys/alt_irq.h"
#include"alt_types.h"
#include"system.h"
#include<stdio.h>
#include<unistd.h>
#include<io.h>
int state=1;
int num=0;

void ButtonsISR(void*context,alt_u32 id)
{
	printf("1\n");
	int readpin;
	readpin=IORD(BUTTONS_BASE,3);
			//........./*clear.*/
	if(readpin==1){

	if(state==1)
		state=-1;
	else
		state=1;
	}
			IOWR(BUTTONS_BASE,3,0);
}
void TimerISR(void*context,alt_u32 id)
{
    printf("2\n");
    num=num+state;
    IOWR(LEDS_BASE,0,num);
	//writeanythingtocleartheIRQ
	IOWR(TIMER_BASE,0,0);

}
void Buttons_Interrupt_Enable(void)
{
	alt_irq_register(BUTTONS_IRQ, 0, ButtonsISR);
	IOWR(BUTTONS_BASE,3,0);
	IOWR(BUTTONS_BASE,2,0x1);
	printf("\n\nB I E\n\n");

}

void Timer_Interrupt_Enable(void)
{
int control_reg;
IOWR(TIMER_BASE,0,0);
IOWR(TIMER_BASE, 2, (short)(TIMER_FREQ & 0x0000ffff));
IOWR(TIMER_BASE, 3, (short)((TIMER_FREQ >> 16) & 0x0000ffff));
alt_irq_register(TIMER_IRQ, 0, TimerISR);
//control_reg= IORD(TIMER_BASE, 1);
//control_reg= control_reg| 0x01;
IOWR(TIMER_BASE, 1, 0x07);
printf("\n\nTimer interrupt enabled.\n\n");

}




int main(void){
	int c;
	Buttons_Interrupt_Enable();//PIO中斷致能副程式
	Timer_Interrupt_Enable();
	//Timer中斷致能副程式
	while(1){
		c++;
	}
	return(0);
}


