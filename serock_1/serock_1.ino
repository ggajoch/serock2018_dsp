volatile int period = 0;

ISR(TIMER1_COMPA_vect) {
  static int cnt = 0;
  if (++cnt > period) {
    cnt = 0;
    
    PINB |= (1 << PB7);
    Serial.println(ADC);
  }  
}

void setup() {
  Serial.begin(115200);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADSC);

  while ((ADCSRA & (1<<ADIF))==0);
  
  // put your setup code here, to run once:
  TCCR1A = (1 << WGM11) | (1 << WGM10);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
  OCR1A = 249;
  TIMSK1 = (1 << OCIE1A);
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int now = Serial.parseInt();
    if (now > 0) {
      period = now-1;
    }
  }
}
