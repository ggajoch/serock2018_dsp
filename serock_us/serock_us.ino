#define trigPin A0
#define echoPin A1

volatile int period = 0;

ISR(TIMER1_COMPA_vect) {
  static int cnt = 0;
  if (++cnt > period) {
    cnt = 0;
    
    PINB |= (1 << PB7);

  }  
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // put your setup code here, to run once:
  TCCR1A = (1 << WGM11) | (1 << WGM10);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
  OCR1A = 249;
  TIMSK1 = (1 << OCIE1A);
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
    long czas;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    czas = pulseIn(echoPin, HIGH);
    Serial.println(czas);

  
  if (Serial.available() > 0) {
    int now = Serial.parseInt();
    if (now > 0) {
      period = now-1;
    }
  }
}
