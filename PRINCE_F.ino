#include <Keypad.h>

#define Password_Lenght 7 // Give enough room for six chars + NULL char

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master[Password_Lenght] = "123456";     //Change PASSWORD here
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool lamp= true;

byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2,}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

int relay = 9;

void setup()
{

  pinMode (relay, OUTPUT);
  digitalWrite (relay, LOW);
   
}

void loop()
{
  if (lamp == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      digitalWrite (relay, LOW);
     
      lamp = 1;
    }
  }

  else Open();
}

void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}



void Open()
{
 
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    //To hide your PASSWORD, make sure its the same lenght as your password
    Data[data_count] = customKey; // store char into data array
   
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if (!strcmp(Data, Master)) // equal to (strcmp(Data, Master) == 0)
    {
     
       digitalWrite (relay, HIGH);
     
      lamp = 0;
    }
    else
    {
      
      digitalWrite (relay, LOW);
      lamp = 1;
    }
    clearData();
  }
} 
