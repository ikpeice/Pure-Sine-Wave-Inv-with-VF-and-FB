
#include <sine_wave.hpp>

volatile bool dt = true, ct = true;
unsigned int steps = 200; // 50Hz
volatile unsigned int counter = 0;
int *dutyCycle_A = new int[MAX_STEPS];
int *dutyCycle_B = new int[MAX_STEPS];
int *_dutyCycle_A = new int[MAX_STEPS];
int *_dutyCycle_B = new int[MAX_STEPS];

ISR(TIMER1_OVF_vect){

    if(ct){
      OCR1B = dutyCycle_B[counter] - _dutyCycle_A[counter];
      OCR1A = 0;
    }
    else{
      OCR1A = dutyCycle_A[counter] - _dutyCycle_B[counter];
      OCR1B = 0;
    }
   // OCR1A = counterRegister/2;//dutyCycle_A[counter];
    counter++;
    if(counter==(steps/2)){
      ct = !ct;
      digitalWrite(10,ct);
      counter=0;
    }

}

SPWM::SPWM(int output_freq,int carrier_freq)
{
  _output_freq = output_freq;
  _carrier_freq = carrier_freq;

}

SPWM::~SPWM()
{
}
/*

*/
void SPWM::begin( bool verbros){
  debug = verbros;
  _carrier_period = ((1/(float)_carrier_freq) * 1000);
  counterRegister = (int)_carrier_period/timer_increament;
  float step = (1/(float)_output_freq)*1000;
  steps = (step / ((float)_carrier_period))*1000;

  // delete old buffer and reallocate memory with size = steps
  delete [] dutyCycle_A; 
  delete [] dutyCycle_B;
  dutyCycle_A = new int[steps];
  dutyCycle_B = new int[steps];

  float slope = 180/((float)steps/2); // get slope for max swing per half waveform
  for(unsigned int i=0; i<steps/2; i++){
    dutyCycle_A[i] = counterRegister * solve(TetaToradian(i*slope)); 
    dutyCycle_B[i] = counterRegister * solve(TetaToradian(i*slope)); 
  }

  if(debug){
    Serial.println("Setup duty done!");
    Serial.println("Output Freq: "+String(_output_freq)+"Hz");
    Serial.println("Carrier Period: "+String(_carrier_period)+"us");
    Serial.println("Timer counter: "+String(counterRegister));
    Serial.println("Steps: "+String(steps));
  }
  delay(10);
  
  setup_freq();
  stop();
  if(debug)Serial.println("Setup frequency done!");
}

bool SPWM::set_output_freq(int output_freq){
  // if(ON_flag){ // if inverter is running, return and do nothing
  //   return 0;
  // }
  if(output_freq<45 || output_freq>60){
    if(debug)
      Serial.println("Output frequency out of range");
    return 0;
  }
  _output_freq = output_freq;
  float step = (1/(float)_output_freq)*1000;
  steps = (step / ((float)_carrier_period))*1000;

  // delete old buffer and reallocate memory with size = steps
  delete [] dutyCycle_A; 
  delete [] dutyCycle_B;
  delete [] _dutyCycle_A;
  delete [] _dutyCycle_B;
  dutyCycle_A = new int[steps];
  dutyCycle_B = new int[steps];
  _dutyCycle_A = new int[steps];
  _dutyCycle_B = new int[steps];

  float slope = 180/((float)steps/2); // get slope for max swing per half waveform
  for(unsigned int i=0; i<steps/2; i++){
    dutyCycle_A[i] = counterRegister * solve(TetaToradian(i*slope)); 
    dutyCycle_B[i] = counterRegister * solve(TetaToradian(i*slope)); 
  }
  if(debug)Serial.println(steps);
  return 1;

}

bool SPWM::set_carrier_freq(int carrier_freq){
  if(ON_flag){ // if inverter is running, return and do nothing
    if(debug)Serial.println("--unsuccessful--");
    return 0;
  }
  if(carrier_freq<4){ //if carrier is less than 4KHz, return and do nothing
    if(debug)
      Serial.println("Carrier frequency too low");
    return 0;
  }
  _carrier_freq = carrier_freq;
  _carrier_period = ((1/(float)_carrier_freq) * 1000);
  counterRegister = (int)_carrier_period/timer_increament;
  float step = (1/(float)_output_freq)*1000;
  steps = (step / ((float)_carrier_period))*1000;

  // delete old buffer and reallocate memory with size = steps
  delete [] dutyCycle_A; 
  delete [] dutyCycle_B;
  delete [] _dutyCycle_A;
  delete [] _dutyCycle_B;
  dutyCycle_A = new int[steps];
  dutyCycle_B = new int[steps];
  _dutyCycle_A = new int[steps];
  _dutyCycle_B = new int[steps];

  float slope = 180/((float)steps/2); // get slope for max swing per half waveform
  for(unsigned int i=0; i<steps/2; i++){
    dutyCycle_A[i] = counterRegister * solve(TetaToradian(i*slope)); 
    dutyCycle_B[i] = counterRegister * solve(TetaToradian(i*slope));
  }
  return 1;  
}

void SPWM::setup_freq(){
    // Register initilisation, see datasheet for more detail.
    TCCR1A = 0b10100010;
       /*10 clear on match, set at BOTTOM for compA.
         10 clear on match, set at BOTTOM for compB.
         00
         10 WGM1 1:0 for waveform 15.
       */
    TCCR1B = 0b00011001;
       /*000
         11 WGM1 3:2 for waveform 15.
         001 no prescale on the counter.
       */
    TIMSK1 = 0b00000001;
       /*0000000
         1 TOV1 Flag interrupt enable. 
       */
    ICR1 = counterRegister;
    // ICR1H = 0x01;     // Period for 16MHz crystal, for a switching frequency of 100KHz for 200 subdevisions per 50Hz sin wave cycle.
    // ICR1L = 0xf4;
    sei();             // Enable global interrupts.
    DDRB = 0b00000110; // Set PB1 and PB2 as outputs.
    pinMode(13,OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(10,OUTPUT);
}

/*
  set_amplitude(float percent)
  Description: Sets your desired output voltage level in percentage
  @paramiter: percentage of the desired output
  @return: none
*/
void SPWM::set_amplitude(float percent){
  for(unsigned int i=0; i<steps/2; i++){
    _dutyCycle_A[i] = (percent/100)*dutyCycle_A[i]; 
    _dutyCycle_B[i] = (percent/100)*dutyCycle_B[i]; 
  }
}

char SPWM::intTochar(int num) {
    char c;
	switch (num)
	{
    case 0:
      c = '0';
      break;
    case 1:
      c = '1';
      break;
    case 2:
      c = '2';
      break;
    case 3:
      c = '3';
      break;
    case 4:
      c = '4';
      break;
    case 5:
      c = '5';
      break;
    case 6:
      c = '6';
      break;
    case 7:
      c = '7';
      break;
    case 8:
      c = '8';
      break;
    case 9:
      c = '9';
      break;
    default:
      break;
	}
    return c;
}

int SPWM::len(char s[]){
  int c=0;
  while(s[c]){
    c++;
  }
  return c;
}

void SPWM::floatTocharArray(char *s, double num) {
	int temp = 0;
	temp = num / 1000;
	s[0] = intTochar(temp);
	temp = (num / 100);
	temp %= 10;
	s[1] = intTochar(temp);
	temp = (num / 10);
	temp %= 10;
	s[2] = intTochar(temp);
	temp = (num);
	temp %= 10;
	s[3] = intTochar(temp);
	temp = (num * 10);
	temp %= 10;
	s[5] = intTochar(temp);
	temp = (num * 100);
	temp %= 10;
	s[6] = intTochar(temp);
  s[4]='.';
}

void SPWM::start(){
  TIMSK1 = 1;
  ON_flag = true;
  delay(500);
}

void SPWM::stop(){
  while(counter>0);
  TIMSK1 = 0;
  OCR1B = 0;
  OCR1A = 0;
  ON_flag = false;
  counter = 0;
}
