/* DarkBlue LightControl
* on Atmega328P-PU / Arduino R3
*/

#include <IRLib.h>
#include <ClickButton\ClickButton.h>
#include <LightOut.h>

// Lights (pin)
const int lightCount = 4;
LightOut light[lightCount] = {
	LightOut(5),
	LightOut(6),
	LightOut(7),
	LightOut(8)
};

// Infrared Receiver
int RECV_PIN = 3;  //-- pwm
IRrecv My_Receiver(RECV_PIN);
IRdecode My_Decoder;
unsigned int Buffer[RAWBUF];

// Buttons
const int buttonCount = 4;
ClickButton button[4] = {
	ClickButton(0, LOW, CLICKBTN_PULLUP),
	ClickButton(1, LOW, CLICKBTN_PULLUP),
	ClickButton(2, LOW, CLICKBTN_PULLUP),
	ClickButton(4, LOW, CLICKBTN_PULLUP)
};
int btnFx[buttonCount] = { 0, 0, 0, 0 };

void setup()
{
  Serial.begin(9600);

  // IR Receiver
  My_Receiver.enableIRIn(); 
  My_Decoder.UseExtnBuf(Buffer);

  // Buttons
  for (int i = 0; i<buttonCount; i++)
  {
	  button[i].debounceTime = 20;   // Debounce timer in ms
	  button[i].multiclickTime = 250;  // Time limit for multi clicks
	  button[i].longClickTime = 1000; // Time until long clicks register
  }
  
}

void loop() {

	//-- IR received --------------------------------------------------------------------
	if (My_Receiver.GetResults(&My_Decoder)) {
		My_Decoder.decode();
		IRcodeRcv();
		delay(500);
		My_Receiver.resume();
	  }

	//-- Button Update --------------------------------------------------------------------
	for (int i = 0; i<buttonCount; i++)
	{
		button[i].Update();
		if (button[i].clicks != 0) btnFx[i] = button[i].clicks;
		if (button[i].clicks == 1)  //single click
		switch (btnFx[i]) {
			case 1: //single click
				light[i].toggle();
				break;
			case 2: //double click
				light[i].on();
				break;
			case -1: //hold 1s
				light[i].off();
				break;
			}
	}
}

void IRcodeRcv(void){
    if(My_Decoder.value == REPEAT) {return;}
    switch(My_Decoder.value){
	case 0xB59: light[0].toggle(); Serial.println("1 pressed"); break;
	case 0x80B59: light[1].toggle(); Serial.println("2 pressed"); break;
	case 0x40B59: light[2].toggle(); Serial.println("3 pressed"); break;
	case 0xC0B59: light[3].toggle(); Serial.println("4 pressed"); break;
    default: Serial.print("??: "); Serial.println(My_Decoder.value, HEX);
	}
}