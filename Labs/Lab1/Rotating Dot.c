unsigned char currentB= 0x80;
unsigned char direction= 1;
void main() {
     PCON.OSCF = 1;
     CMCON = 0x07;

     TRISA = 0x01;
     TRISB = 0x00;

     PORTB = ;
     while(1)
     {
     
             if(RA0_bit == 0)
             {
                 delay_ms(200);
                 PORTB = PORTB>>1;

             }
             if(RA0_bit == 1)
             {
                 delay_ms(200);
                 PORTB = PORTB<<1;

             }
             if(RB0_bit == 1 & direction= 1)
             {
                RB7_bit == 1;
                direction=0;
             }
             if(RB7_bit == 1 & direction= 0)
             {
                RB0_bit == 1;
                direction=1;
             }
             
     }
     
     
}










