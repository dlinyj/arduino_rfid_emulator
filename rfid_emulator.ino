#define ANTENNA 2 

volatile int bit_counter=0;
volatile int byte_counter=0;
volatile int half=0;

unsigned char data_card[5][8] = {{0xFF,0xC5,0x38,0x2D,0x19,0xD1,0xC9,0x5A},    //test
                                {00xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},     // other cards
				{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},    //FF818000CAA974C8
				{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},    //FF 82 40 1 99 EE 94 1E (моя карта)
				{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}};    

unsigned char data[8];

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 3906.25 Hz (16000000/((4095+1)*1))
  OCR1A = 4095;
  // Prescaler 1
  TCCR1B |= (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  pinMode(ANTENNA, OUTPUT);    
  for (int i=0;i<8;i++) data[i]=data_card[3][i];
  setupTimer1();
  
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
        TCNT1=0;
	if (((data[byte_counter] << bit_counter)&0x80)==0x00) {
	    if (half==0) digitalWrite(ANTENNA, LOW);
	    if (half==1) digitalWrite(ANTENNA, HIGH);
	}
	else {
	    if (half==0) digitalWrite(ANTENNA, HIGH);
	    if (half==1) digitalWrite(ANTENNA, LOW);
	}
    
	half++;
	if (half==2) {
	    half=0;
	    bit_counter++;
	    if (bit_counter==8) {
	        bit_counter=0;
	        byte_counter=(byte_counter+1)%8;
		}
	}
}
