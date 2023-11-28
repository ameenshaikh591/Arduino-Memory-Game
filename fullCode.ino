int redLED = 13;
int redRead = 12;
int blueLED = 11;
int blueRead = 10;
int greenLED = 9;
int greenRead = 8;
int yellowLED = 7;
int yellowRead = 6;
int registerRead = 2;
int registerIn = 3;
int registerOut = 4;
int increment = 0;
int digitIncrement = 0;
int storedRecord[32];


void onAndOff()
{

  digitalWrite(redLED,HIGH);
  digitalWrite(blueLED,HIGH);
  digitalWrite(yellowLED,HIGH);
  digitalWrite(greenLED,HIGH);
  delay(2000);
  digitalWrite(redLED,LOW);
  digitalWrite(blueLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,LOW);
  delay(2000);

}

void setup() 
{

  Serial.begin(9600);
  randomSeed(analogRead(A2));

  pinMode(redRead, INPUT_PULLUP);
  pinMode(blueRead, INPUT_PULLUP);
  pinMode(greenRead, INPUT_PULLUP);
  pinMode(yellowRead, INPUT_PULLUP);

  pinMode(registerIn, OUTPUT);
  pinMode(registerOut, OUTPUT);
  pinMode(registerRead, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  pinMode(registerIn,LOW);
  shiftOut(registerRead,registerIn,LSBFIRST,0B00000000);
  pinMode(registerIn,HIGH);

  onAndOff();
  
}

void initialVariables() 
{
  increment = 0;
  digitIncrement = 0;
  storedRecord[32] = {0};
}

int readyToPlay()
{

  if (digitalRead(redRead) == 0)
  {
    while (digitalRead(redRead) == 0)
    {
      digitalRead(redRead);
    }
    return 1;
  }
  if (digitalRead(greenRead) == 0) 
  {
    while (digitalRead(greenRead) == 0)
    {
      digitalRead(greenRead);
    }
    return 1;
  }
  if (digitalRead(yellowRead) == 0) 
  {
    while (digitalRead(yellowRead) == 0)
    {
      digitalRead(yellowRead);
    }
    return 1;
  }
  if (digitalRead(blueRead) == 0) 
  {
    while (digitalRead(blueRead) == 0)
    {
      digitalRead(blueRead);
    }
    return 1;
  }
  return 0;

}

int intro()
{

  digitalWrite(redLED,HIGH);
  digitalWrite(blueLED,HIGH);
  digitalWrite(yellowLED,HIGH);
  digitalWrite(greenLED,HIGH);
  delay(150);
  if (readyToPlay() == 1)
    return 1;
  digitalWrite(redLED,LOW);
  digitalWrite(blueLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,LOW);
  delay(150);
  if (readyToPlay() == 1)
    return 1;
  digitalWrite(redLED,HIGH);
  digitalWrite(blueLED,HIGH);
  digitalWrite(yellowLED,HIGH);
  digitalWrite(greenLED,HIGH);
  delay(150);
  if (readyToPlay() == 1)
    return 1;
  digitalWrite(redLED,LOW);    
  digitalWrite(blueLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,LOW);
  if (readyToPlay() == 1)
    return 1;
  delay(600);
  if (readyToPlay() == 1)
    return 1;
  return 0;
}

void firstRound()
{

  int value = storedRecord[increment];
  if (value == 1)
  {
    digitalWrite(redLED,HIGH);
    delay(800);
    digitalWrite(redLED, LOW);
    delay(400);
  }
  else if (value == 2)
  {
    digitalWrite(blueLED,HIGH);
    delay(800);
    digitalWrite(blueLED, LOW);
    delay(400);
  }
  else if (value == 3)
  {
    digitalWrite(greenLED,HIGH);
    delay(800);
    digitalWrite(greenLED, LOW);
    delay(400);
  }
  else if (value == 4)
  {
    digitalWrite(yellowLED,HIGH);
    delay(800);
    digitalWrite(yellowLED, LOW);
    delay(400);
  }

}

void replayStorage() 
{

  for (int i = 0; i < increment + 1; i++) 
  {
    if (storedRecord[i] == 1)
    {
      digitalWrite(redLED,HIGH);
      delay(800);
      digitalWrite(redLED, LOW);
      delay(400);
    }
    else if (storedRecord[i] == 2)
    {
      digitalWrite(blueLED,HIGH);
      delay(800);
      digitalWrite(blueLED, LOW);
      delay(400);
    }
    else if (storedRecord[i] == 3)
    {
      digitalWrite(greenLED,HIGH);
      delay(800);
      digitalWrite(greenLED, LOW);
      delay(400);
    }
    else if (storedRecord[i] == 4)
    {
      digitalWrite(yellowLED,HIGH);
      delay(800);
      digitalWrite(yellowLED, LOW);
      delay(400);
    }
  }

}

int obtainResponse() 
{

  if (digitalRead(yellowRead) == LOW) {
      digitalWrite(yellowLED,HIGH);
      delay(800);
      digitalWrite(yellowLED,LOW);
      return 4;
    }
  else if (digitalRead(redRead) == LOW) {
      digitalWrite(redLED,HIGH);
      delay(800);
      digitalWrite(redLED,LOW);    
      return 1;
    }
  else if (digitalRead(greenRead) == LOW) {
      digitalWrite(greenLED,HIGH);
      delay(800);
      digitalWrite(greenLED,LOW);      
      return 3;
    }
  else if (digitalRead(blueRead) == LOW) {
      digitalWrite(blueLED,HIGH);
      delay(800);
      digitalWrite(blueLED,LOW);      
      return 2;
    }
  else {
      obtainResponse();
    }

}

int verifyMemory()
{

  for (int i = 0; i < increment + 1; i++) 
  { 
    int result = obtainResponse();
    int indexValue = storedRecord[i];
    if (indexValue != result)
      return 0;
    else {
      continue;
    }
  }
  return 1;

}

void changeDisplayDigits() 
{

  switch (digitIncrement) {
    case 1:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B00110000);
      digitalWrite(registerOut,HIGH);
      break;
    case 2:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B11011010);
      digitalWrite(registerOut,HIGH);
      break;
    case 3:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B01111010);
      digitalWrite(registerOut,HIGH);
      break;
    case 4:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B00110110);
      digitalWrite(registerOut,HIGH);
      break;
    case 5:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B01101110);
      digitalWrite(registerOut,HIGH);
      break;
    case 6:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B11101110);
      digitalWrite(registerOut,HIGH);
      break;
    case 7:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B00111000);
      digitalWrite(registerOut,HIGH);
      break;
    case 8:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B11111110);
      digitalWrite(registerOut,HIGH);
      break;
    case 9:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B00111110);
      digitalWrite(registerOut,HIGH);
      break;
    default:
      digitalWrite(registerOut,LOW);
      shiftOut(registerRead,registerIn,LSBFIRST,0B11111100);
      digitalWrite(registerOut,HIGH);
      digitIncrement = 0;
  }

}




void loop() 
{
  initialVariables();
  changeDisplayDigits();
  intro();
  while (intro() == 0) 
  {
    intro();
  }
  storedRecord[increment] = random(1,5);
  firstRound();
  int accurateMemory = verifyMemory();
  delay(150);
  while (accurateMemory == 1)
  { 
    increment++;
    digitIncrement++;
    changeDisplayDigits();
    storedRecord[increment] = random(1,5);
    replayStorage();
    accurateMemory = verifyMemory();
  }
}
