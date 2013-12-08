#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "pifacecad.h"

/*
    Santa countdown on PiFace PifaceCAD (Control and Display)
    By Gregory Fenton
    http://labby.co.uk
    
    Language: C
    To generate the required libraries, follow the instructions at
    http://piface.github.io/libpifacecad/
    
    Compilation:
        gcc -o santa santa.c -Isrc/ -L. -lpifacecad -L../libmcp23s17/ -lmcp23s17
    Usage:
        ./santa
        While using the software, pressing and holding any button will display
        "Merry Christmas" in over 50 languages (well, 14 characters of it!)
    
    Merry Christmas to you all, and may 2014 be the happiest year ever for you and
    your loved ones.
*/

int main(void)
{
   char * otherlangs[] = 
   {
            "Afrikaans", "Geseende Kersfees",
            "Arabic", "I'd Miilad Said",
            "Argentine","Felices Pasquas",
            "Armenian","Shenoraavor Nor Dari",
            "Basque","Eguberri on",
            "Bohemian","Vesele Vanoce",
            "Breton","Nedeleg laouen",
            "Bulgarian","Tchestita Koleda",
            "Chinese","Saint Dan Fai Lok",
            "Cornish","Nadelik looan na looan blethen noweth",
            "Croatian","Sretan Bozic",
            "Czech","Prejeme Vam",
            "Danish","Glaedelig Jul",
            "Dutch","Vrolijk Kerstfeest",
            "Estonian","Haid joule",
            "Farsi","Cristmas-e-shoma",
            "Filipino","Maligayang Pasko",
            "Finnish","Hyvaa joulua",
            "French","Joyeux Noel",
            "German","Froehliche Weihnachten",
            "Greek","Kala Christouyenna",
            "Hawaiian","Mele Kalikimaka",
            "Hebrew","Mo'adim Lesimkha",
            "Hindi","Shub Naya Baras",
            "Hungarian","Kellemes Karacsonyi unnepeket",
            "Icelandic","Gledileg Jol",
            "Indonesian","Selamat Hari Natal",
            "Iraqi","Idah Saidan",
            "Irish","Nollaig Shona Dhuit",
            "Italian","Buone Feste Natalizie",
            "Japanese"," kurisumasu omedeto",
            "Korean","Sung Tan Chuk Ha",
            "Latvian","Prieci'gus Ziemsve'tkus",
            "Lithuanian","Linksmu Kaledu",
            "Navajo","Merry Keshmish",
            "Norwegian","God Jul",
            "Polish","Wesolych Swiat Bozego Narodzenia",
            "Portuguese","Feliz Natal",
            "Romanian","Craciun fericit",
            "Russian","Pozdrevlyayu s prazdnikom",
            "Serbian","Hristos se rodi",
            "Slovakian","Sretan Bozic",
            "Samoan","La Maunia Le Kilisimasi Ma Le Tausaga Fou",
            "Scots Gaelic","Nollaig chridheil huibh",
            "Serb-Croatian","Sretam Bozic",
            "Slovak","Vesele Vianoce",
            "Spanish","Feliz Navidad",
            "Swedish","God Jul",
            "Tahitian"," Ia orana te Noera",
            "Thai","Sawadee Pee Mai",
            "Turkish","Noeliniz Ve Yeni Yiliniz Kutlu Olsun",
            "Ukrainian","Z Rizdvom Khrystovym",
            "Vietnamese","Chuc Mung Giang Sinh",
            "Welsh","Nadolig Llawen",
            "Yugoslavian","Cestitamo Bozic",
            "111","111" 
   };
   

   uint8_t santa[] = 
   {
      0x1b,0x1d,0x2,0x5,0xa,0xf,0x1f,0x8, //0,0
      0x0,0x18,0x14,0xa,0x16,0x1e,0x1f,0x2, //1,0
      0x1a,0x14,0x15,0x12,0x13,0x12,0x9,0x4, //0,1
      0xb,0x5,0x15,0x9,0x19,0x9,0x12,0x4 //1,1
   };
   uint8_t pifacelogo[] = {
      0b00001, 0b00111, 0b01111, 0b11111, 0b11111, 0b11110, 0b11110, 0b11111,
      0b11100, 0b11110, 0b11111, 0b11111, 0b11111, 0b01111, 0b01110, 0b11110,
      0b11111, 0b11111, 0b01111, 0b01111, 0b00111, 0b00011, 0b00000, 0b00000,
      0b01100, 0b01000, 0b10100, 0b10100, 0b11010, 0b11111, 0b00000, 0b00000 };

   char message[] = " until Santa! ",
        left[]    = "% 3dd,%02dh%02dm%02ds",
        buffer[128];

   time_t now;
   struct tm christmas;
   double seconds;
   int today = 0, triggered = 1, i, count;
   for(i = 0; i < 999; i += 2)
   {
     if(otherlangs[i][0] == '1' && otherlangs[i + 1][0] == '1')
     {
	count = i - 2;
	break;
     }
   }
   pifacecad_open();
   pifacecad_lcd_blink_off();
   pifacecad_lcd_clear();
   pifacecad_lcd_backlight_on();
   pifacecad_lcd_cursor_on();
   pifacecad_lcd_write("PiFaceCAD Xmas\ncountdown");
   sleep(2);
   pifacecad_lcd_clear();
   pifacecad_lcd_write("Gregory Fenton\nlabby.co.uk");
   sleep(2);
   pifacecad_lcd_clear();
   pifacecad_lcd_write("To see Merry\nChristmas in");
   sleep(2);
   pifacecad_lcd_clear();
   pifacecad_lcd_write("Other langs\nhold a button");
   sleep(2);
   pifacecad_lcd_clear();
   pifacecad_lcd_store_custom_bitmap(0, pifacelogo);
   pifacecad_lcd_store_custom_bitmap(1, pifacelogo + 8);
   pifacecad_lcd_store_custom_bitmap(2, pifacelogo + 16);
   pifacecad_lcd_store_custom_bitmap(3, pifacelogo + 24);
   pifacecad_lcd_set_cursor(0, 1);
   pifacecad_lcd_write_custom_bitmap(2);
   pifacecad_lcd_write_custom_bitmap(3);
   pifacecad_lcd_set_cursor(0, 0);
   pifacecad_lcd_write_custom_bitmap(0);
   pifacecad_lcd_write_custom_bitmap(1);
   
   while(1)
   {
      while(pifacecad_read_switches() != 255)
      {
	 i = (rand() % count) & 0xfe;
	 snprintf(buffer, sizeof(buffer), "%14s", otherlangs[i]);
	 pifacecad_lcd_set_cursor(2,0);
	 pifacecad_lcd_write(buffer);
	 snprintf(buffer, sizeof(buffer), "%14s", otherlangs[i + 1]);
	 pifacecad_lcd_set_cursor(2,1);
	 pifacecad_lcd_write(buffer);
	 while(pifacecad_read_switches() != 255)
	   usleep(100 * 1000);
      }
      
      pifacecad_lcd_set_cursor(2, 0);
      time(&now);
      christmas = *localtime(&now);
      if(christmas.tm_mon = 11 && christmas.tm_mday == 25) // Christmas!
	today = 1;
      else
	today = 0;
      christmas.tm_hour = 0;
      christmas.tm_min = 0;
      christmas.tm_sec = 0;
      if(today)
      {
	 triggered = 1;
	 snprintf(buffer, sizeof(buffer), "CHECK THE TREE!");
	 pifacecad_lcd_write(buffer);
	 snprintf(buffer, sizeof(buffer), "SANTA HAS BEEN!");
	 pifacecad_lcd_set_cursor(2, 1);
	 
	 pifacecad_lcd_store_custom_bitmap(0, santa);
	 pifacecad_lcd_store_custom_bitmap(1, santa + 8);
	 pifacecad_lcd_store_custom_bitmap(2, santa + 16);
	 pifacecad_lcd_store_custom_bitmap(3, santa + 24);
      }
      else
      {
	 if(triggered)
	 {
	    triggered = 0;
	    pifacecad_lcd_store_custom_bitmap(0, pifacelogo);
	    pifacecad_lcd_store_custom_bitmap(1, pifacelogo + 8);
	    pifacecad_lcd_store_custom_bitmap(2, pifacelogo + 16);
	    pifacecad_lcd_store_custom_bitmap(3, pifacelogo + 24);

	 }
	 
	 if(christmas.tm_mon == 11 && christmas.tm_mday > 24)
	   christmas.tm_year ++;
	 christmas.tm_mon = 11;
	 christmas.tm_mday = 25;
	 time (&now);
	 seconds = difftime(now, mktime(&christmas));
	 snprintf(buffer, sizeof(buffer), left,
	       -(int)((int)seconds / 86400),
	       -(int)((int)seconds % 86400) / 3600,
	       -(int)((int)seconds % 3600) / 60,
	       -(int)((int)seconds % 60));
	 pifacecad_lcd_set_cursor(2, 1);
	 pifacecad_lcd_write(message);
	 pifacecad_lcd_set_cursor(2,0);

      }
      pifacecad_lcd_write(buffer);
      usleep(250 * 1000);
   }
   pifacecad_close();
   return 1;
}
