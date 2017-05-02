//
// By Kyle McDonald
// From the instructables project at:
// http://www.instructables.com/id/DIY-3D-Controller/

#define resolution 8
#define mains 50 // 60: north america, japan; 50: most other places (DC frequency)

#define refresh 2 * 1000000 / mains // 2Mil / frequency 

void setup() {
  Serial.begin(115200); // Sets bits per second for data transmission

  // unused pins are fairly insignificant,
  // but pulled low to reduce unknown variables
  for(int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  for(int i = 8; i < 11; i++)
    pinMode(i, INPUT);

  startTimer();
}

void loop() {  
  Serial.print(time(8, B00000001), DEC);
  Serial.print(" ");
  Serial.print(time(9, B00000010), DEC);
  Serial.print(" ");
  Serial.println(time(10, B00000100), DEC);

} 

long time(int pin, byte mask) {
  unsigned long count = 0, total = 0;
  while(checkTimer() < refresh) {
    // pinMode is about 6 times slower than assigning
    // DDRB directly, but that pause is important
    pinMode(pin, OUTPUT); // Reconfigures pin as an output
    PORTB = 0; // Sets pin voltage to 0V
    pinMode(pin, INPUT); // Reconfigures pin as an input
    while((PINB & mask) == 0) // If voltage at the pin is less than 3.0V
      count++;
    total++;
  }
  startTimer();
  return (count << resolution) / total; // Average count value * 2^8.
}

extern volatile unsigned long timer0_overflow_count;

void startTimer() {
  timer0_overflow_count = 0;
  TCNT0 = 0;
}

unsigned long checkTimer() {
  return ((timer0_overflow_count << 8) + TCNT0) << 2; // TCNTO (8-bit) increments every clock tick, clock is 16Mhz, timer0_overflow_count ticks every time TCNTO overflows which is why we do <<8. (<<2 scales result)
}


