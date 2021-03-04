int pwm_a = 3;
int pwm_b = 9;
int dir_a = 2;
int dir_b = 8;

int speed = 255;

void setup() {
    Serial.begin(9600);
    
    // Motors
    pinMode(pwm_a, OUTPUT);
    pinMode(pwm_b, OUTPUT);
    pinMode(dir_a, OUTPUT);
    pinMode(dir_b, OUTPUT);
    analogWrite(pwm_a, 0);
    analogWrite(pwm_b, 0);
}

void loop() {
    if (Serial.available() > 0) {
        int req = Serial.read();
        Serial.println(req);
        // Avancer
        if (req == 122) {
          digitalWrite(dir_a, LOW); 
          digitalWrite(dir_b, LOW);  
          
          analogWrite(pwm_a, speed);  
          analogWrite(pwm_b, speed);
        }
        
        // Reculer
        if (req == 115) {
          digitalWrite(dir_a, HIGH); 
          digitalWrite(dir_b, HIGH);  
          
          analogWrite(pwm_a, speed);  
          analogWrite(pwm_b, speed);
        }
        
        // Gauche
        if (req == 113) {
          digitalWrite(dir_a, HIGH); 
          digitalWrite(dir_b, LOW);  
          
          analogWrite(pwm_a, speed);  
          analogWrite(pwm_b, speed);
        }
        
        // Avancer Gauche
        if (req == 97) {
          digitalWrite(dir_a, LOW); 
          digitalWrite(dir_b, LOW);  
          
          analogWrite(pwm_a, speed / 6);
          analogWrite(pwm_b, speed);
        }
        
        // Droite
        if (req == 100) {
          digitalWrite(dir_a, LOW); 
          digitalWrite(dir_b, HIGH);  
          
          analogWrite(pwm_a, speed);  
          analogWrite(pwm_b, speed);
        }
        
        // Avancer Droite
        if (req == 101) {
          digitalWrite(dir_a, LOW); 
          digitalWrite(dir_b, LOW);  
          
          analogWrite(pwm_a, speed);
          analogWrite(pwm_b, speed / 6);
        }
        
        // Ne bouge plus
        if (req == 36) {
          digitalWrite(dir_a, LOW); 
          digitalWrite(dir_b, LOW);  
          
          analogWrite(pwm_a, 0);  
          analogWrite(pwm_b, 0);
        }
        
        // Vitesse 1
        if (req == 49) {
          speed = 85;
        }
        
        // Vitesse 2
        if (req == 50) {
          speed = 170;
        }
        
        // Vitesse 3
        if (req == 51) {
          speed = 255;
        }

    }
}
