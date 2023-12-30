//#define LCD_ENABLED
//#include <main.h>

#include <display.hpp>
// LiquidCrystal_I2C lcd(0x07,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int rs = 25, en = 26, d4 = 27, d5 = 28, d6 = 29, d7 = 30;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Inv_Data *data;

String dis_data[] ={     
    "Status: ",
    "Output AC: ",
    "Input AC: ",
    "Bat. Volt: ",
    "Input Freq: ", 
    "Output Freq: ",  
    "Carrier Freq: ",
    "Output Power: "
      
};

    String Status_;
    String output_freq_; // 50Hz
    String input_freq_;
    String carrier_freq_; //7KHz
    String batt_volt_;
    String output_power_;
    String input_AC_;
    String output_AC_;

Display::Display()//Inv_Data *_data
{
    // data = _data;
}

Display::~Display()
{
}

void Display::clear(){
    lcd.clear();
}

void Display::begin(Inv_Data *_data){
    data = _data;
    lcd.begin(20,4);
    //lcd.backlight();
    lcd.clear();
    lcd.print("--SMART INVERTER--");
    lcd.setCursor(0,1);
    lcd.print("Vwersion 1.1.2");
}

Lines lines[8] = {
    {&dis_data[0],  &Status_},
    {&dis_data[1], &output_AC_},
    {&dis_data[2], &input_AC_},
    {&dis_data[3], &batt_volt_},
    {&dis_data[4],  &input_freq_},
    {&dis_data[5], &output_freq_},
    {&dis_data[6], &carrier_freq_},
    {&dis_data[7], &output_power_}

};
void Display::show(int key=0){
    // if(key<=0)return;
    static int i=0;
    lines->update();
    lcd.clear();

    lcd.setCursor(0,0);
    lines[i].show();
    lcd.setCursor(0,1);
    lines[i+1].show();
    lcd.setCursor(0,2);
    lines[i+2].show();
    lcd.setCursor(0,3);
    lines[i+3].show();
    if(key == 1)i++;
    if(key == 3)i--;
    if(i>=4){
        i = 4;
    }else if(i<0){
        i=0;
    }
}


void Lines::show(){
    lcd.print(*a);lcd.print(*b);
}
void Lines::update(){
    Status_ = (data->Status > 0)? "ON":"OFF";
    output_freq_ = String(data->output_freq); // 50Hz
    input_freq_ = String(data->input_freq);
    carrier_freq_ = String(data->carrier_freq); //7KHz
    batt_volt_ = String(data->batt_volt);
    output_power_ = String(data->output_power);
    input_AC_ = String(data->input_AC);
    output_AC_ = String(data->output_AC);   
}



