// Simple Walk 2
//this sketch is an evolution of simple walking program for the Minion
// it moves towars the directon of estabilshing some basic control


#include <Servo.h> 
 
Servo lfoot;  // create servo object to control Left Foot
Servo rfoot;  // create servo object to control Right Foot
Servo lleg;  // create servo object to control Left Leg
Servo rleg;  // create servo object to control Right Leg

 
int hip = 90;    // variable to store the hip servo position 
int ankle = 90;    // variable to store the ankle servo position

int hipstep = 10;  // degree of movement of the hips
int anklestep = 5;  // degree of movement of ankles

int sequence = 0;  // variable to store current state of walking sequence
int walktime = 0;  // variable to store delay untill next step sequence

// Here's where we'll keep our channel values

int ch1; //input value for throttle
int ch2; //input value for steering

int throttle = 0;
int steering = 0;


//Setup commands

void setup() 
{ 
  
  pinMode(2, INPUT);// ch1 pins for pulsein to receve from rc remote
  pinMode(3, INPUT);// ch2
  
  lfoot.attach(8);  // attaches left foot to pin 8
  rfoot.attach(6);  // attaches right foot to pin 6
  lleg.attach(9);  // attaches left leg to pin 9
  rleg.attach(7);  // attaches right leg to pin 7
  //waist.attach(5);
  //hips.attache(4);
} 
 


//Primaty loop 
void loop() 
{ 
  
  ch1 = pulseIn(2, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(3, HIGH, 25000); // each channel


if(ch1 == 0, ch2 ==0){ // centers input values if pulsein times out, for when remote is disconected
  ch1 = 1400;
  ch2 = 1400;}
  
   
  throttle = map(ch1, 800, 2000, 0, 20);
  //hipstep = throttle;
  //anklestep = (throttle / 2);
  
  steering = map(ch2, 800, 2000, 0, 40);
  
  if(throttle == 10){
    Rest();
  }
  else{
    Walk();
  }
  
 delay(15);  // delay for servo to get in possiton.  this needs to be replaced with some type of counter function
  
}


//Functions

void Rest()  //function to return the walker to rest configeration from any possable state
{
  sequence = 0;  //reset the walk sequence
   
  if(ankle < 90)
  {
        rfoot.write(ankle); 
        lfoot.write(ankle);
        ankle = ankle + 5;
  }
    if ( ankle > 90){
        rfoot.write(ankle); 
        lfoot.write(ankle);
        ankle = ankle - 5;
  }
    if ( hip < (70 + steering)){
        lleg.write(hip);
        rleg.write(hip);
        hip = hip + 10;
  }
    if ( hip > (70 + steering)){
        lleg.write(hip);
        rleg.write(hip);
        hip = hip - 10;
  }
  
}
void Walk() {  //Function to allow the robot to walk forwards and backwards
  
   if(sequence == 0)  // Rotatates bolth ankles to lift right foot 
  { 

      if(ankle <= 115){      // checks to see if ankle is at 135 degrees
        rfoot.write(ankle); 
        lfoot.write(ankle);
        ankle = ankle + anklestep;
        
        
        //lleg.write(hip + steering);
        //rleg.write(hip + steering);
        
     if(steering < 28)
      lleg.write(hip + steering);

      if(steering > 28)
       rleg.write(hip + steering); 

      
      }
      else{
        if(throttle >= 10){
          sequence = 1;
        }
        else{
          sequence = 3;
        }
      }                      
  } 
  
    if(sequence == 1)  // Rotatates bolth hips to move right foot  
  {
      if(hip >= 45){  // was 25.  checks to see if hips are at 45 if not they are moved by the amount dictated in hipstep 
        lleg.write(hip);
        rleg.write(hip);
        hip = hip - hipstep;
      }
      else{  //once we reach 45, the sequence number is updated to 2
         if(throttle >= 10){
          sequence = 2;
        }
        else{
          sequence = 0; 
      }     
  }}
  
    if(sequence == 2)  // Rotatates bolth hips to lift left foot  
  { 

    if(ankle >= 75){    
      lfoot.write(ankle);
      rfoot.write(ankle); 
      ankle = ankle - anklestep;
      
      //rleg.write(hip + steering);
      //lleg.write(hip + steering);
      
      
      if(steering < 28)
      lleg.write(hip + steering);

      if(steering > 28)
       rleg.write(hip + steering);
      
    }
    else{
         if(throttle >= 10){
         sequence = 3;
          }
        else{
          sequence = 1;
          }      
  }}
  
   if(sequence == 3)  // Rotatates bolth ankles to lift right foot 
  { 
    if(hip <= 135){ //was 115
     lleg.write(hip);
     rleg.write(hip);
     hip = hip + hipstep;
    }
    else{
         if(throttle >= 10){
          sequence = 0;
          }
        else{
          sequence = 2;
          }
}}}


