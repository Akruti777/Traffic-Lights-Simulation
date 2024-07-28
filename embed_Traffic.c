#include<reg51.h>

void T0M1delay(void);

sbit switch1 = P0^3;

int main(void) {
    int x;
    
    switch1 = 1; // make switch as input
    
    if (switch1 == 0) {
        P2 = 0x00; // pedestrian off
        P3 = 0x00;
        
        while (1) {
            P0 = 0x02; // traffic yellow
            P1 = 0x02;
            
            for (x = 0; x < 28; x++) { // 0.5 sec delay
                T0M1delay();
            }
            
            P0 = 0x00; // traffic green
            P1 = 0x00;
            
            for (x = 0; x < 28; x++) { // 0.5 sec delay
                T0M1delay();
            }
        }
    }
    else {
        while (1) {
            P0 = 0x01; // traffic red
            P1 = 0x01;
            P2 = 0X04; // pedestrian green
            P3 = 0X04;
            
            for (x = 0; x < 42; x++) { // 3 sec delay
                T0M1delay();
            }
            
            P0 = 0x02; // traffic yellow
            P1 = 0x02;
            P2 = 0X01; // pedestrian red
            P3 = 0X01;
            
            for (x = 0; x < 14; x++) { // 1 sec delay
                T0M1delay();
            }
						P0=0x04;//traffic go
						P1=0x04;
						P2=0X01;//pedestrian stop
						P3=0X01;
						for(x=0;x<42;x++){ //3 sec delay
								T0M1delay();
						}
						P0=0x02;//traffic yellow
						P1=0x02;
						P2=0X01;//pedestrian stop
						P3=0X01;
						for(x=0;x<14;x++){ //1 sec delay
								T0M1delay();
						}

        }
    }
}

void T0M1delay(void) {
    TMOD = 0x01; // timer 0, mode 1
    TH0 = 0x00; // initial value for 0.5 sec delay
    TL0 = 0x00;
    TR0 = 1; // start timer
    
    while (!TF0); // wait for timer overflow flag to set
    
    TF0 = 0; // clear timer overflow flag
    TR0 = 0; // stop timer
}