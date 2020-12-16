#define ANTENNA 2 
#define CARD_ID 0x0001020304

volatile int bit_counter=0;
volatile int byte_counter=0;
volatile int half=0;

uint8_t data[8];

void data_card_ul() {
  uint64_t card_id = (uint64_t)CARD_ID;
  uint64_t data_card_ul = (uint64_t)0x1FFF; //first 9 bit as 1
  int32_t i;
  uint8_t tmp_nybble;
  uint8_t column_parity_bits = 0;
  for (i = 9; i >= 0; i--) { //5 bytes = 10 nybbles
    tmp_nybble = (uint8_t) (0x0f & (card_id >> i*4));
    data_card_ul = (data_card_ul << 4) | tmp_nybble;
    data_card_ul = (data_card_ul << 1) | ((tmp_nybble >> 3 & 0x01) ^ (tmp_nybble >> 2 & 0x01) ^\
      (tmp_nybble >> 1 & 0x01) ^ (tmp_nybble  & 0x01));
    column_parity_bits ^= tmp_nybble;
  }
  data_card_ul = (data_card_ul << 4) | column_parity_bits;
  data_card_ul = (data_card_ul << 1); //1 stop bit = 0
  for (i = 0; i < 8; i++) {
    data[i] = (uint8_t)(0xFF & (data_card_ul >> (7 - i) * 8));
  }
}

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
  data_card_ul();  
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
