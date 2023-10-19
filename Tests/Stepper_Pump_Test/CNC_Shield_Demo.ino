
// CNC Shield Stepper  Control Demo
// Superb Tech
// www.youtube.com/superbtech

const int StepX = 11;
const int DirX = 11;

float a = 0;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(StepX,OUTPUT);
  pinMode(DirX,OUTPUT);
 }

}

void loop() {
  while (!Serial.available());
  digitalWrite(DirX, HIGH); // set direction, HIGH for clockwise, LOW for anticlockwise
  a = 0;
  a = Serial.readString().toInt();
  if(a>6){a=7;}
  steps = int(1707*a); // 1707 = 1 ml, a = 1;
  for(int x = 0; x<steps; x++) { // loop for 800 steps, 400*0.9 = 1 rotation; 1707 = 1 ml
    digitalWrite(StepX,HIGH);
    delayMicroseconds(1000);
    digitalWrite(StepX,LOW); 
    delayMicroseconds(1000);
  }
}
