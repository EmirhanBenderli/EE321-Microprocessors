int ones = 0;
int tens = 0;
int hundreds = 0;
int run = 0;
int prev = 0;
int del = 10;
int i = 0;
void main() {
        PCON.OSCF = 1;
        TRISB = 0x00;
        PORTB = 0x00;
        TRISA = 0xE0;



        while(1){

            if(RA5_bit) {
                 while(RA5_bit){}
                 run = !run;

            }

            if(run) {

                    if(hundreds==9&tens==9&ones==9){
                          del=del*10;
                          hundreds=1;
                          tens=0;
                          ones=0;
                    }
                    for(i = 0;i<del;i++) {
                        delay_ms(1);
                    }
                    
                    PORTB = (ones<<4)+tens;
                    PORTA = hundreds;
                    ones++;



                    if(ones == 10) {
                            ones = 0;
                            tens++;
                            if(tens == 10) {
                                    tens = 0;
                                    hundreds++;
                                    hundreds%=10;
                            }
                    }


                    if(RA6_bit==1) {
                          ones=0;
                          tens=0;
                          hundreds=0;

                    }



            }
        }
}