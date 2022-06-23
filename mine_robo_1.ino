const int motor1A = 5;
const int motor1B = 6;
const int motor2A = 4;
const int motor2B = 3;
const int echoPin = 12;
const int trigPin = 13;
const int irPin = 9;
const int ledPin = 10;

int time = 1500;  

// defines variables
long duration; 
float distance; 
float turningTime = 2000;
float mineStop = 5000;
float mineOver = 500;
bool turnCounter = 1;



void setup()
{
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
  
  pinMode (irPin, INPUT);
  pinMode (ledPin, OUTPUT);
  
}

//fuctions for moving and turning
void forward() 
{ 
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,LOW);
 
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor2B,LOW);
}

void turnLeft() 
{ 
  digitalWrite(motor1A,HIGH);
  digitalWrite(motor1B,LOW);
 
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);
}

void turnRight() 
{ digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
 
  digitalWrite(motor2A,HIGH);
  digitalWrite(motor2B,LOW);
}

void backward()
{ digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,HIGH);
 
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,HIGH);
}

void stop()
{ digitalWrite(motor1A,LOW);
  digitalWrite(motor1B,LOW);
 
  digitalWrite(motor2A,LOW);
  digitalWrite(motor2B,LOW);
}

void turn()
{
  if(turnCounter==1)
  {
    turnLeft();
    turnCounter=!turnCounter;
  }
  else
  {
    turnRight();
    turnCounter=!turnCounter;
  }
}

//functions for detecting distance from wall
float readDistance()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.0343 / 2.0;
  return distance;
}

//function to sense mines
void infra()
{
  if (digitalRead(irPin)==LOW)
  {
    digitalWrite (ledPin,HIGH);
    stop();
    delay(mineStop);
    forward();
    delay(mineOver);
  }
  else
  {
    digitalWrite (ledPin, LOW);
    forward();
  }
     
}

void checkWall()
{
  Serial.print("\n This distance is ");
  Serial.print(readDistance());
  if (readDistance()<30)
  {
    turn();
    delay(turningTime);
  }
  else
  {
    forward();
  }
    
}

//main loop

void loop()
{
 forward();
 infra();  
 checkWall();
}