// pin ventilatorja
const int fanPin = 3;

// spremenljivka za merjenje casa
unsigned long previousMillis = 0;

boolean newData = false;

// zacetna vrednost pwm signala
int defaultValue = 200;

const byte stZnakov = 32;
char sprejetiZnaki[stZnakov];   // an array to store the received data

int potValue;

boolean manualOverride = true;

int prejsnjaVrednost = 0;

void setup() {
    pinMode(fanPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("ONLINE");
}


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


char readCharSerial(){
    byte sprejeto = -1;

    if(Serial.available()){
        sprejeto = Serial.parseInt();
         Serial.println("sprejeto");

    }

    return sprejeto;
}


void sendSerial(String message, int value){
    Serial.print(message);
    Serial.println(value);
}


int pwmValue = defaultValue;


unsigned int st = 0;

void loop() {

    int sprejeto = readIntSerial();

    //Serial.println(sprejeto);
    
    if(sprejeto == -2){
        manualOverride = true;
        //Serial.println("--RUNNING MAUAL--");
    }
    else if(sprejeto == -3){
        manualOverride = false;
       // Serial.println("--RUNNING FROM SERIAL PORT--");
    }


    if(manualOverride){
        potValue = analogRead(A0);
        //sendSerial("Potencimeter :", potValue);
        pwmValue = potValue/4;
        analogWrite(fanPin, pwmValue);

        if(st%1500 == 0){
           // sendSerial("Potencimeter :", potValue);
        }

        st++;
    }
    else{
        if(sprejeto == -3){
           pwmValue = defaultValue;
        }
        else if(sprejeto != -1){
            pwmValue = sprejeto;
        }
        analogWrite(fanPin, pwmValue);

        if(pwmValue != prejsnjaVrednost){
          //  sendSerial("Nova vrednost: ", pwmValue);
        }
        prejsnjaVrednost = pwmValue;
        
    }
    Serial.println(pwmValue);

    /*

    char sprejeto = readCharSerial();

    Serial.println(sprejeto);
    
    if(sprejeto == 'm'){
        manualOverride = true;
        Serial.println("Running manual");
        //sendSerial("Running manual", NULL);
    }
    else if(sprejeto == 's'){
        manualOverride = false;
        Serial.println("Running from serial port");
        //sendSerial("Running from serial port", NULL);
    }


    if(manualOverride){
        potValue = analogRead(A0);
        //sendSerial("Potencimeter :", potValue);
        analogWrite(fanPin, potValue/4);
    }
    else{
        int newPwm = readIntSerial();
        if(newPwm != -1) {
            analogWrite(fanPin, newPwm);
            sendSerial("Nova vrednost: ", newPwm);
        }
    }

    */


    
    

   // potValue = analogRead(A0);
    //sendSerial("Potencimeter :", potValue);




    /*
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        pwmValue -= 10;
    }
    */
    
}
