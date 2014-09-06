Ultrasonic Ranging Module HC - SR04
===================

This device is an ultrasonic ranging module which sends out 8 cycle bursts of 40KHz and then raises an echo. It can be used for proximity sensoring and other uses as a person wishes. Grab the [unofficial data sheet](http://users.ece.utexas.edu/~valvano/Datasheets/HCSR04b.pdf) for more details.

## Pins

* VCC
* GND
* Trig
* Echo

## Pins Functionality

The `VCC` pin should be connected to 5V supply from the board and `GND` should be connected to `GND` from the board and should not be left open. It is always advisable to first connect `GND` pin to the board before connecting the `VCC` pin.

The `Trig` and `Echo` pins are for data transfer. The ranging module works like a request-response model. Requests are sent over `Trig` pin and the response is received over `Echo` Pin.

These two pins can be connected anywhere on the digital pin rows on the board. I connected `Trig` to `13` and `Echo` to `12`.

After connecting, it is good to define these pin values as `const` in the sketch

    const int trigPin = 13;
    const int echoPin = 12;

## Working with the device

### Sending a request

As per the data sheet we first need to send a `HIGH` signal on the `Trig` pin for atleast `10μs`.

In Arduino we would need the following code:

    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    // After 10μs set the trig back to LOW
    digitalWrite(trigPin, LOW);
    
We are waiting for `5μs` after setting low and before making the
the `Trig` pin `HIGH`. This is not really required, but it is a
safe thing to do in case the device might be slower.

### Response

After the module recieves the requests it sends out 8 cycle burts of 40Khz and after it has processed the burts, it raises a `HIGH` pulse on the `Echo` pin. The duration of `HIGH` pulse is proportional to the distance.

We need to block on the `Echo` pin for `HIGH` pulse and measure the duration of the pulse. In Arduino we would simply use [`pulseIn`](http://arduino.cc/en/Reference/pulseIn) function which returns us the duration of the pulse.

    long highDuration = pulseIn (echoPin, HIGH);

### Calculating distance

After we got the duration of the pulse we would need a factor to convert from duration to distance. Everyone finds that factor to be different. Your best bet is to measure it yourself. Keep a scale between the object and the module and keep it at say 30 cms apart. Then measure the `highDuration` value. Your factor can be calculated by

    long pulseToDistanceFactor = highDuration / distance;
    
You need to calculate this one for your module and remember it. Then next time whenever you are using this module, you can compute the distance by simply 

    long distance = highDuration/pulseToDistanceFactor;
    
You can store `pulseToDistanceFactor` as a `#define` or as a `const` in the global scope. Always make it `const` in the global scope so that no other statement can modify it once it is set.


## Other information

#### Buying

* [SunFouder 2 pcs Ultrasonic Module HC-SR04 Distance Sensor for Arduino UNO MEGA R3 Mega2560 Duemilanove Nano Robot XBee ZigBee](http://www.amazon.com/gp/product/B00E0NXTJW/)
* [SainSmart HC-SR04 Ranging Detector Mod Distance Sensor (Blue)](http://www.amazon.com/SainSmart-HC-SR04-Ranging-Detector-Distance/dp/B004U8TOE6/)