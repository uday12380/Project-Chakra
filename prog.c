int VRx = A0;

int VRy = A1;

int SW = 10;

 

int xPosition = 0;

int yPosition = 0;

int SW_state = 0;

int mapX = 0;

int mapY = 0;

 

String voice;

 

const int trigPin = 23;

const int echoPin = 25;

float duration, distance;

 

void setup() {

  pinMode(2, OUTPUT); // left backward

  pinMode(4, OUTPUT); // left forward

  pinMode(6, OUTPUT); // rgt backward

  pinMode(8, OUTPUT); // rgt forward

 

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  Serial.begin(9600);

 

  pinMode(VRx, INPUT);

  pinMode(VRy, INPUT);

  pinMode(SW, INPUT_PULLUP); 

 

  pinMode(13, OUTPUT);

}

 

void loop() {

  xPosition = analogRead(VRx);

  yPosition = analogRead(VRy);

  SW_state = digitalRead(SW);

  mapX = map(xPosition, 0, 1023, -512, 512);

  mapY = map(yPosition, 0, 1023, -512, 512);

 

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(100);

  digitalWrite(trigPin, LOW);

 

  duration = pulseIn(echoPin, HIGH);

  distance = (duration*.0343)/2;

 

  if(distance > 50){

  if(mapX < -230 && mapY > -10 && mapY < 0){            //move forward

    digitalWrite(2, LOW);digitalWrite(4, HIGH);digitalWrite(6, LOW);digitalWrite(8, HIGH);}

  else if(mapX > 230 && mapY > -10 && mapY < 0){      //move reverse

    digitalWrite(2, HIGH);digitalWrite(4, LOW);digitalWrite(6, HIGH);digitalWrite(8, LOW);}

  else if(mapY > 230 && mapX > -20 && mapX < 0){      //rotate left

    digitalWrite(4, LOW);digitalWrite(2, HIGH);digitalWrite(6, LOW);digitalWrite(8, HIGH);}

  else if(mapY < -230 && mapX > -20 && mapX < 0){      //rotate right

    digitalWrite(4, HIGH);digitalWrite(2, LOW);digitalWrite(6, HIGH);digitalWrite(8, LOW);}

  else if(mapX < -230 && mapY > 230){      //move left fwd

    digitalWrite(2,LOW);digitalWrite(4,LOW);digitalWrite(6,LOW);digitalWrite(8,HIGH);}

  else if(mapX > 230 && mapY > 230){      //move left reverse

    digitalWrite(2,LOW);digitalWrite(4,LOW);digitalWrite(6,HIGH);digitalWrite(8,LOW);}

  else if(mapX < -230 && mapY < -230){      //move right fwd

    digitalWrite(2,LOW);digitalWrite(4,HIGH);digitalWrite(6,LOW);digitalWrite(8,LOW);}

  else if(mapX > 230 && mapY < -230){      //move right reverse

    digitalWrite(2,HIGH);digitalWrite(4,LOW);digitalWrite(6,LOW);digitalWrite(8,LOW);}

  else {      //stop all motors

    digitalWrite(2,LOW);digitalWrite(4,LOW);digitalWrite(6,LOW);digitalWrite(8,LOW);}

 

  while(Serial.available()>0){

      delay(10);

      char c=Serial.read();

      if(c=='#'){

        break;}

      voice+=c;}

  if(voice=="forward"){            //move forward(all motors rotate in forward direction)

    digitalWrite(2, LOW);digitalWrite(4, HIGH);digitalWrite(6, LOW);digitalWrite(8, HIGH); delay(2000); stop();}

  else if(voice=="back"){      //move reverse (all motors rotate in reverse direction)

    digitalWrite(2, HIGH);digitalWrite(4, LOW);digitalWrite(6, HIGH);digitalWrite(8, LOW); delay(2000); stop();}

  else if(voice=="left"){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)

    digitalWrite(2, HIGH);digitalWrite(8, HIGH);digitalWrite(6, LOW);digitalWrite(4, LOW); delay(2000); stop();}

  else if(voice=="right"){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)

    digitalWrite(6, HIGH);digitalWrite(4, HIGH);digitalWrite(2, LOW);digitalWrite(8, LOW); delay(2000); stop();}

  if(voice.length()>0){

      Serial.println(voice);

       voice="";    //STOP (all motors stop)

    digitalWrite(2,LOW);digitalWrite(4,LOW);digitalWrite(6,LOW);digitalWrite(8,LOW);}

}

else{

  stop();

  digitalWrite(13, HIGH);delay(100);

  digitalWrite(13, LOW);}

}

void stop()
{ 

    digitalWrite(2, LOW);digitalWrite(4, LOW);digitalWrite(6, LOW);digitalWrite(8, LOW); }
