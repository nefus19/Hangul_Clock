#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <DS1302.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, 12, NEO_GRBW);

DS1302 Clock(2, 3, 4);

int iHour[14][3] = {{21, 18, -1}, 
  {15, 2, -1},  
  {23, 2, -1},  
  {5, 2, -1},   
  {4, 2, -1},   
  {14, 13, 2}, 
  {16, 13, 2}, 
  {6, 3, 2},    
  {22, 17, 2}, 
  {12, 7, 2},   
  {24, 2, -1},  
  {24, 15, 2},  
  {18, 19, -1}, 
  {24, 23, 2}    
};

int iMinute[12][4] = {{ -1, -1, -1, -1}, 
  {9, 0, -1, -1},   
  {10, 0, -1, -1}, 
  {10, 9, 0, -1},  
  {11, 1, 0, -1},  
  {11, 10, 9, 0},  
  {8, 1, 0, -1},   
  {8, 10, 9, 0},    
  {20, 10, 0, -1},  
  {20, 10, 9, 0},   
  {19, 10, 0, -1},
  {19, 10, 9, 0}   
};

int old_hd = -1;
int old_md = -1;

void setup()
{
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(100);

  for (int i = 0 ; i <= 26 ; i++)
  {
    strip.setPixelColor(i,  (i * 10) % 256, 255 - (i * 10) % 256 , 0 );
    strip.setPixelColor(i - 1, 0, (i * 10) % 256, 255 - (i * 10) % 256 );
    strip.setPixelColor(i - 2, 255 - (i * 10) % 256, 0, (i * 10) % 256 );
    strip.show();
    delay(70);

    strip.setPixelColor(i, 0, 0, 0);
    strip.setPixelColor(i - 1, 0, 0, 0);
    strip.setPixelColor(i - 2, 0, 0, 0);
    strip.show();
  }
  delay(70);

  for (int i = 24 ; i >= -2 ; i--)
  {
    strip.setPixelColor(i,  (i * 10) % 256, 255 - (i * 10) % 256 , 0 );
    strip.setPixelColor(i + 1, 0, (i * 10) % 256, 255 - (i * 10) % 256 );
    strip.setPixelColor(i + 2, 255 - (i * 10) % 256, 0, (i * 10) % 256 );
    strip.show();
    delay(70);

    strip.setPixelColor(i, 0, 0, 0);
    strip.setPixelColor(i + 1, 0, 0, 0);
    strip.setPixelColor(i + 2, 0, 0, 0);
    strip.show();
  }

  Wire.begin();
  Clock.halt(false);
  Clock.writeProtect(false);


  delay(500);
}

void loop()
{
  

  bool h12 = false;
  bool pm = false;
 
  String strCurTime = Clock.getTimeStr();
  Serial.println(strCurTime);


  int index =  strCurTime.indexOf(":");
  String strTemp = strCurTime.substring(0, index);
  strCurTime = strCurTime.substring(index + 1, strCurTime.length());
  int h = strTemp.toInt();


  index =  strCurTime.indexOf(":");
  strTemp = strCurTime.substring(0, index);
  strCurTime = strCurTime.substring(index + 1, strCurTime.length());
  int m = strTemp.toInt();


  int s = strCurTime.toInt();



  int hd, md;


  if ( (h == 0 || h == 12) && m > 5)  hd = 13;  
  else                                hd = h;   

  md = m / 5;   


  
  if (old_hd != hd)
  {
    
    for (int i = 0 ; i < 3 ; i++)
    {
      int num = iHour[old_hd][i];
      if (num == -1) continue;

      strip.setPixelColor(num, 0, 0, 0);
      strip.show();
    }

    
    for (int i = 0 ; i < 3 ; i++)
    {
      int num = iHour[hd][i];
      if (num == -1) continue;

      strip.setPixelColor(num, (rand() % 256), 255 - (rand() % 256), abs(128 - (rand() % 256)));
      strip.show();
    }

    old_hd = hd;
  }

  if (old_md != md)
  {
   
    for (int i = 0 ; i < 4 ; i++)
    {
      int num = iMinute[old_md][i];
      if (num == -1) continue;

      strip.setPixelColor(num, 0, 0, 0);
      strip.show();
    }

   
    for (int i = 0 ; i < 4 ; i++)
    {
      int num = iMinute[md][i];
      if (num == -1) continue;

      strip.setPixelColor(num, (rand() % 256), 255 - (rand() % 256), abs(128 - (rand() % 256)));
      strip.show();
    }

    old_md = md;
  }
}
