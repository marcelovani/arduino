// Sound Machine
// This app emulates the sound of Turbo when the car accelerates

void setup()
{
    // LED
    setupLED();

    // Player
    setupPlayer();

    // Accelerometer
    calibrateACC();

//detectChange(); //temp
}

void loop()
{
    readAccX(); //temp
    calcSma();
    detectChange();
    //plot();
}

// Plotter
void plot()
{
//    Serial.print(getThreshold());
//    Serial.print(",");

//    int r = 30;//getRange();
//    int i = 0;
//    int * data = getSma();
//    while(i < r) {
//      Serial.print(data[i]);
//      Serial.print(",");
//      i++;
//    }
//    
    Serial.println("");
}
