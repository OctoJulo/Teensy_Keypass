//////////////////////////////////////////////////////////////////////
// KEYPASS V0.2											by Latruite	//
//////////////////////////////////////////////////////////////////////
// requis: 
//		- teensy
// 		- bp
//		- codeur rotatif decimal
//////////////////////////////////////////////////////////////////////
// ************************** Variables *************************** //
//////////////////////////////////////////////////////////////////////


#define BP1_PIN 12										// broche bp.
// SI readhexcodeV1
#define HEXCODE1_PIN 14									// A0	
#define HEXCODE2_PIN 15									// A1
#define HEXCODE4_PIN 16									// A2
#define HEXCODE8_PIN 17									// A3
// SI readhexcodeV2
//int hexcode_pin[] = {14, 15, 16, 17};

//////////////////////////////////////////////////////////////////////
// PASSWORDS: 
#define ARRAYSIZE 10	// nombre de mp
String password[ARRAYSIZE] = 
{ "ZERZER","un0!", "2eU:", "To4+", "CACACACAtre", 
"cinq", "6", "7", "8","9",
};

//////////////////////////////////////////////////////////////////////
void setup()  
{
	pinMode(BP1_PIN,INPUT);
 // SI readhexcodeV1
	pinMode(HEXCODE1_PIN,INPUT_PULLUP);
	pinMode(HEXCODE2_PIN,INPUT_PULLUP);
	pinMode(HEXCODE4_PIN,INPUT_PULLUP);
	pinMode(HEXCODE8_PIN,INPUT_PULLUP);
 // ou SI readhexcodeV2
	//for(int i = 0; i < 4; i++)
	//{
	//	pinMode(hexcode_pin[i], INPUT_PULLUP);
	//}

	Serial.begin(9600);
	Serial.println("Keypass V0.2");

	attachInterrupt(BP1_PIN, myIntFunc, RISING);	// attache une interuption sur le bp, lorsqu'il est relaché
	delay(500);
}
//////////////////////////////////////////////////////////////////////
void loop() {}

void myIntFunc()
{
	int selectedval = readhexcodeV1();
	sendPassword(selectedval);
	delay(1000);	
}

int readhexcodeV1()		// lit la valeur du codeur et la retourne sous forme d'octet
{
	int hexcode = 0;
	if (digitalRead(HEXCODE1_PIN) == LOW)
		hexcode += 1;
	if (digitalRead(HEXCODE2_PIN) == LOW)
		hexcode += 2;
	if (digitalRead(HEXCODE4_PIN) == LOW)
		hexcode += 4;
	if (digitalRead(HEXCODE8_PIN) == LOW)
		hexcode += 8;

	Serial.println(hexcode);
	return hexcode;
}

/*int readhexcodeV2()		// lit la valeur du codeur et la retourne sous forme d'octet
{
	int hexcode = 0;
	int bitValue[] = {1,2,4,8};
	for(int i = 0; i < 6; i++)  // cycle through all the pins
	{
		if(digitalRead(hexcode_pin[i]) == LOW)  // because all the bits are pre-loaded with zeros, only need to do something when we need to flip a bit high
		{
			hexcode = hexcode + bitValue[i];  // adding the bit position decimal equivalent flips that bit position
		}
	}
	Serial.println(hexcode);
	return hexcode;
}*/

void sendPassword(int code)		//en fonction du code d'entrée, ecrit un texte 
{
	Keyboard.print(password[code]);
	Keyboard.press(KEY_ENTER);
	delay(300); 
	Keyboard.release(KEY_ENTER);
	Serial.println(password[code]);
	Serial.println("password send..");

}
