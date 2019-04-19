#include<LRemote.h>

LRemoteSlider Motorslider;
LRemoteJoyStick stickLeft;
LRemoteJoyStick stickRight;
LRemoteButton ServoButton;
LRemoteButton MotorButton;

void setup(){


}

void loop(){
    if(!LRemote.connected()) {
    Serial.println("waiting for connection");
    digital_write(7, HIGH);
    delay(1000);
    digital_write(7, LOW);
    delay(1000);
    digital_write(7, HIGH);
    delay(1000);
    digital_write(7, LOW);
    delay(1000);
    } 

    else {
    delay(15);
    }
    LRemote.process();
}

void LRemote(){

    //LRemote UI Setting 
    LRemote.setName("LinkitRobot"); 
    LRemote.setOrientation(RC_LANDSCAPE);
    LRemote.setGrid(7,3);

    //Add Button

        //MotorButton
        MotorButton.setText("發射");
        MotorButton.setPos(3,0);
        MotorButton.setSize(1,3);
        MotorButton.setColor(RC_GREEN);
        MotorButton.addControl(Motorslider);
        //ServoButton
        ServoButton.setText("閘門")
        ServoButton.setPos(3,0);
        ServoButton.setSize(1,3);
        ServoButton.setColor(RC_GREEN);
        ServoButton.addControl(Motorslider);

    //Add Slider

        //Motorslider
        Motorslider.setPos(3,0);
        Motorslider.setSize(1,3);
        Motorslider.setColor(RC_GREEN);
        Motorslider.addControl(Motorslider);

    //Add JoyStick

        //stickLeft
        stickLeft.setPos(1,1);
        stickLeft.setSize(1,1);
        stickLeft.setColor(RC_ORANGE);
        LRemote.addControl(stickLeft);
        //stickRight
        stickRight.setPos(5,1);
        stickRight.setSize(1,1);
        stickRight.setColor(RC_BLUE);
        stickRight.addControl(stickRight);
}