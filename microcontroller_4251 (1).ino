#include <Adafruit_LEDBackpack.h>
int lenMinutes = 0;
int lenSeconds = 0;

int tenthsOfMinutes = 0;
int onesOfMinutes = 0;
int tenthsOfSeconds = 0;
int onesOfSeconds = 0;

int potPin = A1;
int buttonPin = 6;
int push = 11;
int pirPin =12;
unsigned long buttonPressTime = 0;
bool colorChangeTriggered = false; 

Adafruit_7segment display = Adafruit_7segment();

void updateDisplay(int a, int b, int x, int y)
{
    display.writeDigitNum(0, a, false);
    display.writeDigitNum(1, b, false);
    display.writeDigitNum(3, x, false);
    display.writeDigitNum(4, y, false);
    display.writeDisplay();
}

void setup()
{
    display.begin(0x70);
    pinMode(2, OUTPUT);
    pinMode(potPin, INPUT);
    Serial.begin(9600);

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
   pinMode(12, INPUT);
}
void playTone(int toneFrequency, int toneDuration)
{
    tone(2, toneFrequency, toneDuration);
    delay(toneDuration);
}

void loop()
{
    float seconds = analogRead(potPin) / 1.705;

    int minutes = seconds / 60;
    float new_minutes = (seconds / 60) - minutes;
    int remSec = new_minutes * 60;
    // Serial.println(new_minutes);

    updateDisplay(minutes / 10, minutes % 10, remSec / 10, remSec % 10);

    int buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH)
    {
        lenMinutes = minutes;
        lenSeconds = 59;
        int lenSeconds1 = remSec;

        for (int seconds = lenSeconds1; seconds >= 0; seconds--)
        {

            tenthsOfSeconds = seconds / 10; // Calculate tenths of seconds
            onesOfSeconds = seconds % 10;   // Calculate ones of seconds

            updateDisplay(minutes / 10, minutes % 10, tenthsOfSeconds, onesOfSeconds);
            delay(100); // Delay for 1 second (1000 milliseconds) to simulate real time
        }

        for (int minutes = lenMinutes - 1; minutes >= 0; minutes--)
        {
            for (int seconds = lenSeconds; seconds >= 0; seconds--)
            {
                tenthsOfMinutes = minutes / 10; // Calculate tenths of minutes
                onesOfMinutes = minutes % 10;   // Calculate ones of minutes
                tenthsOfSeconds = seconds / 10; // Calculate tenths of seconds
                onesOfSeconds = seconds % 10;   // Calculate ones of seconds

                updateDisplay(tenthsOfMinutes, onesOfMinutes, tenthsOfSeconds, onesOfSeconds);
                delay(100); // Delay for 1 second (1000 milliseconds) to simulate real time
            }
        }
        playTone(261, 300); // C4
        playTone(261, 300); // C4
        playTone(392, 300); // G4
        playTone(392, 300); // G4
        playTone(440, 300); // A4
        playTone(440, 300); // A4
        playTone(392, 600); // G4
        playTone(349, 300); // F4
        playTone(349, 300); // F4
        playTone(330, 300); // E4
        playTone(330, 300); // E4
        playTone(294, 300); // D4
        playTone(294, 300); // D4
        playTone(261, 600); // C4
        tone(2, 0, 100);    // Stop tone
        delay(4000);
    }

   int button_State = digitalRead(push);

    if (button_State == HIGH)
    {
        // Turn on the lights with random colors
        for (int i = 8; i < 11; i++)
        {
            int randomNumber = random(2);
            digitalWrite(i, randomNumber);
        }
      	

        // Check if the button has been continuously pressed for 2 seconds
        if ((millis() - buttonPressTime) > 70)
        {
            // Turn off the lights
            for (int i = 8; i < 11; i++)
            {
                digitalWrite(i, LOW);
            }
            // Reset button press time
            buttonPressTime = millis();
            delay(2500); // Debounce delay
        }
    }
    else
    {
        // Reset button press time when the button is released
        buttonPressTime = millis();
    }
   
  
  int state = digitalRead(pirPin);
if (state == HIGH)
{
    for (int i = 8; i < 11; i+=2)
    {

        digitalWrite(i, HIGH);
    }
    Serial.println("Motion detected!");
  
  delay(5000);
  for (int i = 8; i < 11; i+=2)
    {

        digitalWrite(i, LOW);
    }
  
}
/* else if (state == LOW)
{
    for (int i = 8; i < 11; i++)
    {
        digitalWrite(i, LOW);
    }
    Serial.println("Not");
} */



        /* if (push_btn_state == HIGH && (millis() - buttonPressTime > 1000)) {
            for (int i = 8; i < 11; i++) {
                digitalWrite(i, LOW); // Turn off all LEDs connected to pins 8, 9, and 10
            }
            Serial.println("2 sec");
            buttonPressTime = millis(); // Reset button press time
            delay(2000); // Debounce delay
        } */

        /* if(push_btn_state == LOW){
          for (int i = 8; i < 11; i++) {
         digitalWrite(i, 0);
       }
       delay(500);
       }*/
    }
