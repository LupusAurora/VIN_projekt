#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object


boolean newData = false;
const byte stZnakov = 32;
char sprejetiZnaki[stZnakov];   // an array to store the received data


int readIntSerial(){
    static int indeks = 0;
    // znak, do katerega iscemo stevila v bufferju
    char delimiter = '\n';
    char sprejeto;

    int prebranInt = -1;

    if (Serial.available() > 0) {
        sprejeto = Serial.read();

        if (sprejeto != delimiter) {
            sprejetiZnaki[indeks] = sprejeto;
            indeks++;
            if (indeks >= stZnakov) {
                indeks = stZnakov - 1;
            }
        }
        else {
            sprejetiZnaki[indeks] = '\0'; // terminate the string
            indeks = 0;
            newData = true;
        }
    }

    if(newData){
       prebranInt = atoi(sprejetiZnaki);
       newData = false;
    }
   
    return prebranInt;
}




void setup() {
    byte numDigits = 4;  
    byte digitPins[] = {7, 4, 3, 8};
    //                    a b  c  d  e f g dp
    byte segmentPins[] = {6,2,10,12,13,5,9,11};
    bool resistorsOnSegments = 0; 
    sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);

    Serial.begin(9600);
    Serial.println("DISPLAY ONLINE");

}

int prejsnjaVrednost = -2;

void loop() {
    //sevseg.setNumber(3141, 3);

    int prebrano = readIntSerial();

    if(prebrano != -1){
        sevseg.setNumber(prebrano);
        prejsnjaVrednost = prebrano;
  
    }
    else if(prejsnjaVrednost == -2){
            sevseg.setChars("null");
        }

    
    sevseg.refreshDisplay(); // Must run repeatedly
}
