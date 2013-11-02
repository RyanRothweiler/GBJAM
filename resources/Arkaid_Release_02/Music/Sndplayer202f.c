/*
	
	GB Lemon tracker

	it use the mod2gbl music pack
	
	you can change inside the "void sound ()" part the number of music you want to play
	(don't forget to place the same value in the song_def.c and the exemple.bat) 
	
	code by Lemon on 26 sept 99

	if you use this source (or part) in your code just put me in the credits... ^_^
	lemon@urbanet.ch

*/


#include "..\Music\songs_def.c"		// here you just include the file who will say to the player what he need to play



unsigned int step;
int track;			/* nbr of the track in the song (well not to important, now, maybe later...) */
int timer;

int musicwait;


int voice;
unsigned char fx_value;
unsigned char fx_retrig;

unsigned int snd_swp0 ;
unsigned int snd_lngh0 ;          // to play different instrument on one track !!
unsigned int snd_env0 ;
unsigned int snd_cons0 ;

unsigned int snd_lngh1 ;          // to play different instrument on one track !!
unsigned int snd_env1 ;
unsigned int snd_cons1 ;

unsigned int snd_lngh3 ;          // to play different instrument on one track !!
unsigned int snd_env3 ;
unsigned int snd_poly3 ;
unsigned int snd_cons3 ;
void stopmusic();
void resetmusic();


/************************************************************************/

UWORD frequencies[] = {
  44, 156, 262, 363, 457, 547, 631, 710, 786, 854, 923, 986,
  1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
  1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
  1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
  1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
  1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015
};

/************************************************************************/

void stopmusic()
{
    /* initialise sound output */
  NR52_REG = 0x8FU;
  NR51_REG = 0x00U;
  NR50_REG = 0x77U;

}

/************************************************************************/

void resetmusic()
{
    /* initialise sound output */

  NR52_REG = 0x00U;

  step = 0;
  patern = 0;

  NR52_REG = 0x8FU;
  NR51_REG = 0x00U;
  NR50_REG = 0x77U;

}

/************************************************************************/

void effect_test()
{

   if ( ((data_song_ptr[step*4+voice] >> 4 ) & 0x0007) == 1){
             if (voice == 0){
                                fx_value = ( ((data_song_ptr[step*4+voice]) & 0x000F ) << 4 ) ;
                               }
              if(voice == 1){
                                 fx_value = ( ((data_song_ptr[step*4+voice]) & 0x000F ) << 4 ) ;
                               }
              if(voice == 2){ fx_value = ((data_song_ptr[step*4+voice]) & 0x000F );
                                if (fx_value == 0) { fx_value = 0x00U ; }
                                if (fx_value >= 1 && fx_value <= 5 ) { fx_value = 0x20U ; }
                                if (fx_value >= 6 && fx_value <= 10 ) { fx_value = 0x40U ; }
                                if (fx_value >= 11 && fx_value <= 15 ) { fx_value = 0x60U ; }
                                }

              if(voice == 3){
                                 fx_value = ( ((data_song_ptr[step*4+voice]) & 0x000F ) << 4 ) ;
                                 }
 
    } else if ( ((data_song_ptr[step*4+voice] >> 4 ) & 0x0007) == 7){
             if (voice == 0){
                                
                                }
              if(voice == 1){
                                 
                                 }
              if(voice == 2){  }
              
              if(voice == 3){ fx_retrig = 3; }

   } else   if (((data_song_ptr[step*4+voice] >> 4 ) & 0x0007) == 0){
	      if(voice == 0){
                                fx_value = 0xF7U ;
                                }
              if(voice == 1){
                                 fx_value = 0xF7U ;
                                }
              if(voice == 2){  }
              
              if(voice == 3){
                                 fx_value = 0xF1U ;
                                 }
             }                  
                           

}

/************************************************************************/
void instru_test()
{

     if ( voice == 0 ) {
                            if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 0){     // 
                                                                               snd_swp0 = 0x00U;
                                                                               snd_lngh0 = 0x07U;
                                                                               snd_env0 = fx_value | 0x07U;  
                                                                               snd_cons0 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 1){     // 
                                                                               snd_swp0 = 0x00U;
                                                                               snd_lngh0 = 0x07U;
                                                                               snd_env0 = fx_value | 0x07U;
                                                                               snd_cons0 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 2){     // 
                                                                               snd_swp0 = 0x00U;
                                                                               snd_lngh0 = 0x07U;
                                                                               snd_env0 = fx_value | 0x07U;
                                                                               snd_cons0 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 3){     // 
                                                                               snd_swp0 = 0x00U;
                                                                               snd_lngh0 = 0x07U;
                                                                               snd_env0 = fx_value | 0x07U;
                                                                               snd_cons0 = 0x80U;
                                                                               } 
                           
                          }
                          
     if ( voice == 1 ) {
                            if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 0){     //
                                                                               snd_lngh1 = 0x81U;
                                                                               snd_env1 = fx_value | 0x07U;
                                                                               snd_cons1 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 1){     //
                                                                               snd_lngh1 = 0x81U;
                                                                               snd_env1 = fx_value | 0x07U;
                                                                               snd_cons1 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 2){     //
                                                                               snd_lngh1 = 0x81U;
                                                                               snd_env1 = fx_value | 0x07U;
                                                                               snd_cons1 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 3){     //
                                                                               snd_lngh1 = 0x81U;
                                                                               snd_env1 = fx_value | 0x07U;
                                                                               snd_cons1 = 0x80U;
                                                                               } 
                           
                          }

    if ( voice == 3 ) {
                            if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003) == 0){     // bass drum
                                                                               snd_lngh3 = 0x01U;
                                                                               snd_env3 = fx_value | 0x01U;  //fx_value | 
                                                                               snd_poly3 = 0x55U;
                                                                               snd_cons3 = 0x80U;
                                                                               } else
                           if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003)== 1){     // hi hat
                                                                               snd_lngh3 = 0x01U;
                                                                               snd_env3 = fx_value | 0x01U;
                                                                               snd_poly3 = 0x01U;
                                                                               snd_cons3 = 0x80U;
                                                                               } else
                          if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003)== 2){     // snare
                                                                               snd_lngh3 = 0x01U;
                                                                               snd_env3 = fx_value | 0x01U;
                                                                               snd_poly3 = 0x52U;
                                                                               snd_cons3 = 0x80U;
                                                                               } else
                          if ( ((data_song_ptr[step*4+voice] >> 7 ) & 0x0003)== 3){     // cymbal
                                                                               snd_lngh3 = 0x01U;
                                                                               snd_env3 = fx_value | 0x03U;
                                                                               snd_poly3 = 0x03U;
                                                                               snd_cons3 = 0x80U;
                                                                               } 
                          }

}

/************************************************************************/

void voice0()
{

unsigned char freqLOW;
unsigned char freqHI;
unsigned int gb_freq;

voice = 0;
effect_test();
instru_test();

gb_freq = data_song_ptr[step*4+voice] >> 9 ;

freqLOW = frequencies[gb_freq] & 0x00FF ;
freqHI = (frequencies[gb_freq] & 0x0700) >> 8 ;



    if ((data_song_ptr[step*4+voice]) >> 9 != 0x48 ){
     
    
       NR51_REG = 0xEEU;

       NR10_REG = snd_swp0 ;
       NR11_REG = snd_lngh0 ;
       NR12_REG = snd_env0 ;

       NR13_REG = freqLOW;                       // 8bits of data
       NR14_REG = snd_cons0 | freqHI;            // 3bits of data
       
       NR51_REG = 0xFFU;
         
      }
 
}

/************************************************************************/
 void voice1()
{
unsigned char freqLOW;
unsigned char freqHI;
unsigned int gb_freq;

voice = 1 ;
effect_test();
instru_test();

gb_freq = data_song_ptr[step*4+voice] >> 9 ;

freqLOW = frequencies[gb_freq] & 0x00FF ;
freqHI = (frequencies[gb_freq] & 0x0700) >> 8 ;



    if ((data_song_ptr[step*4+voice]) >> 9 != 0x48 ){
     
    
              NR51_REG = 0xDDU;
              
              NR21_REG = snd_lngh1 ;      //  0x01
              NR22_REG = snd_env1 ;
              NR23_REG = freqLOW ;
              NR24_REG = snd_cons1 | freqHI;

              NR51_REG = 0xFF;
              
            
      }

}

/************************************************************************/
 void voice2()
{
unsigned char freqLOW;
unsigned char freqHI;
unsigned int gb_freq;

voice = 2 ;
effect_test();

gb_freq = data_song_ptr[step*4+voice] >> 9 ;

freqLOW = frequencies[gb_freq] & 0x00FF ;
freqHI = (frequencies[gb_freq] & 0x0700) >> 8 ;



    if ((data_song_ptr[step*4+voice]) >> 9 != 0x48 ){
      
       
              NR51_REG = 0xBBU;
              
              NR30_REG = 0x80U;        //    0x80 = 1.0.0.0-0.0.0.0 output ON
              NR31_REG = 0xFFU;
              NR32_REG = fx_value;
              NR33_REG = freqLOW ;
              NR34_REG = 0x80U | freqHI;
              
              NR51_REG = 0xFF;
              
              
      }
   
}
/************************************************************************/
 void voice3()
{


    voice = 3 ;
    effect_test();
    instru_test();
            
   
        
    if ((data_song_ptr[step*4+voice]) >> 9 != 0x48 ){
      
    
              NR51_REG = 0x77U;
              
              NR41_REG = snd_lngh3;
              NR42_REG = snd_env3;
              NR43_REG = snd_poly3;
              NR44_REG = snd_cons3;
              
              NR51_REG = 0xFF;
              
             
              
              }

}

/************************************************************************/


void music()
{
  voice0();
  voice1();
  voice2();
  voice3();

  ++step;
    if (step == 64){
        step = 0;
        ++patern;
        if (patern >= nbr_patern ){
            patern = 0;
            }
     }

  patern_definition();
}

/************************************************************************/

/* Ed */
void initBkgMusic()
{
   /* bkg music */
	musicClock=0;
	resetmusic();
	patern_definition();
   /* bkg music */
}


/*
I'm sure there is plenty of better way to do this but don't blame me I'm not god ;o)
*/