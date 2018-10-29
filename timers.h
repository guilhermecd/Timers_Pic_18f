#ifndef TIMERS_H
#define TIMERS_H

struct timer{
    unsigned int milisseconds;
    unsigned char seconds;
    unsigned char minutes;
    unsigned char hours;
    unsigned char on_off;
}Timer0, Timer1, Timer3, Timer4;

//___________________________________________ configure timers___________________________________
void config_timer0(){//estouro de 1 em 1 segundos
    T0CON = 0b00000100;
    TMR0H = 0x0B;
    TMR0L = 0xDC;
    GIE_bit = 1;
    TMR0IE_bit = 0;
}

void config_timer1(){//estouro de 50 em 50 milisssegundos
    T1CON = 0b00010000;
    TMR1IF_bit = 0;
    TMR1H = 0x3C;
    TMR1L = 0xB0;
    TMR1IE_bit = 0;
    INTCON = 0xC0;
}

void config_timer3(){//estouro de 10 em 10 milissegundos
    T3CON = 0b00000000;
    TMR3IF_bit = 0;
    TMR3H = 0xB1;
    TMR3L = 0xE0;
    TMR3IE_bit = 0;
    INTCON = 0xC0;
}

void config_timer4(){//estouro de 1 em 1 milissegundos
    T4CON = 0b00111000;
    TMR4IE_bit = 0;
    PR4 = 249;
    INTCON = 0xC0;
}

//___________________________________________ init timers___________________________________
void init_timer0(){
    T0CON = 0b10000100;
    TMR0IE_bit = 1;
    Timer0.on_off = 1;
}

void init_timer1(){
    T1CON = 0b00010001;
    TMR1IE_bit = 0;
    Timer1.on_off = 1;    
} 

void init_timer3(){
    T3CON = 0b00000001;
    TMR3IE_bit = 1;
    Timer3.on_off = 1;    
}

void init_timer4(){
    T4CON = 0b00111100;
    TMR4IE_bit = 1;   
    Timer4.on_off = 1;        
}

//___________________________________________ stop timers___________________________________

void stop_timer0(){
    T0CON = 0b00000100;
    TMR0IE_bit = 0;
    Timer0.on_off = 0;    
}

void stop_timer1(){
    T1CON = 0b00010000;
    TMR1IE_bit = 0;   
    Timer1.on_off = 0;
}

void stop_timer3(){
    T3CON = 0b00000000;
    TMR3IE_bit = 0;
    Timer3.on_off = 0;        
}

void stop_timer4(){
    T4CON = 0b00111000;
    TMR4IE_bit = 0;   
    Timer4.on_off = 0;        
}

//___________________________________________ limpa timers___________________________________

void clear_timer0(){
    Timer0.milisseconds = 0;        
    Timer0.seconds = 0;
    Timer0.minutes = 0;
    Timer0.hours = 0;
}

void clear_timer1(){
    Timer1.milisseconds = 0;        
    Timer1.seconds = 0;
    Timer1.minutes = 0;
    Timer1.hours = 0;
}

void clear_timer3(){
    Timer3.milisseconds = 0;        
    Timer3.seconds = 0;
    Timer3.minutes = 0;
    Timer3.hours = 0;
}

void clear_timer4(){
    Timer4.milisseconds = 0;        
    Timer4.seconds = 0;
    Timer4.minutes = 0;
    Timer4.hours = 0;
}

//___________________________________________ interruption timers___________________________________


void timer_zero_interrupt(){////estouro de 1 em 1 segundos
    TMR0IF_bit = 0;
    TMR0H = 0x0B;
    TMR0L = 0xDC;
    Timer0.seconds += 1;
    if(Timer0.seconds >= 60){
        Timer0.minutes += 1;
        Timer0.seconds = 0;
    }
    if(Timer0.minutes >= 60){
        Timer0.hours += 1;
        Timer0.minutes = 0;
        if(Timer0.hours == 24){
            Timer0.hours = 0;
        }
    }    
}

void timer_one_interrupt(){//estouro de 50 em 50 milisssegundos
    TMR1IF_bit = 0;
    TMR1H = 0x3C;
    TMR1L = 0xB0;
    Timer1.milisseconds += 50;
    if(Timer1.milisseconds >= 1000){
        Timer1.seconds += 1;
        Timer1.milisseconds = 0;
    }
    if(Timer1.seconds >= 60){
        Timer1.minutes += 1;
        Timer1.seconds = 0;
    }
    if(Timer1.minutes >= 60){
        Timer1.hours += 1;
        Timer1.minutes = 0;
        if(Timer1.hours == 24){
            Timer1.hours = 0;
        }
    }    
}

void timer_three_interrupt(){//estouro de 10 em 10 milissegundos
    TMR3IF_bit = 0;
    TMR3H = 0xB1;
    TMR3L = 0xE0;
    Timer3.milisseconds += 10;
    if(Timer3.milisseconds >= 1000){
        Timer3.seconds += 1;
        Timer3.milisseconds = 0;
    }
    if(Timer3.seconds >= 60){
        Timer3.minutes += 1;
        Timer3.seconds = 0;
    }
    if(Timer3.minutes >= 60){
        Timer3.hours += 1;
        Timer3.minutes = 0;
        if(Timer3.hours == 24){
            Timer3.hours = 0;
        }
    }    
      
}

void timer_four_interrupt(){//estouro de 1 em 1 milissegundos
    TMR4IF_bit = 0;
    Timer4.milisseconds += 1;
    if(Timer4.milisseconds >= 1000){
        Timer4.seconds += 1;
        Timer4.milisseconds = 0;
    }
    if(Timer4.seconds >= 60){
        Timer4.minutes += 1;
        Timer4.seconds = 0;
    }
    if(Timer4.minutes >= 60){
        Timer4.hours += 1;
        Timer4.minutes = 0;
        if(Timer4.hours == 24){
            Timer4.hours = 0;
        }
    }   
}


void interrupt() {
    if (TMR0IF_bit){//estouro de 1 em 1 segundo
        timer_zero_interrupt();
    }
    if (TMR1IF_bit){ //estouro de 50 em 50 milissegundo
        timer_one_interrupt();
    }
    if (TMR3IF_bit){ //timer3 - estouro de 10 em 10 milissegundos
        timer_three_interrupt();
    }
    if (TMR4IF_bit){ //timer4 - estouro de 1 em 1 milissegundos
        timer_four_interrupt();
    }
}

#endif