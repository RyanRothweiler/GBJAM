/*
	File for the music definitions to use with the Lemon Player

	created with mod2gbl 0.6

	Whoops, in fact you will need to create this file with the part of the song data
	created with mod2gbl.
	Just follow this exemple

	on 26 sept 99

	lemon@urbanet.ch

*/


int patern ;
int song_nbr ;

extern UWORD data_song_axelf0[];
extern UWORD data_song_axelf1[];
extern UWORD data_song_axelf2[];
extern UWORD data_song_axelf3[];
extern UWORD data_song_axelf4[];
extern UWORD data_song_axelf5[];
extern UWORD data_song_axelf6[];
extern UWORD data_song_axelf7[];
extern UWORD data_song_axelf8[];
extern UWORD data_song_axelf9[];

extern UWORD data_song_axelf10[];
extern UWORD data_song_axelf11[];
extern UWORD data_song_axelf12[];
extern UWORD data_song_axelf13[];
extern UWORD data_song_axelf14[];
extern UWORD data_song_axelf15[];
extern UWORD data_song_axelf16[];
extern UWORD data_song_axelf17[];
extern UWORD data_song_axelf18[];
extern UWORD data_song_axelf19[];

extern UWORD data_song_axelf20[];
extern UWORD data_song_axelf21[];
extern UWORD data_song_axelf22[];
extern UWORD data_song_axelf23[];
extern UWORD data_song_axelf24[];
extern UWORD data_song_axelf25[];
extern UWORD data_song_axelf26[];
extern UWORD data_song_axelf27[];
extern UWORD data_song_axelf28[];
extern UWORD data_song_axelf29[];




char songname[]="axelf";
int nbr_patern = 30 ;
UWORD *data_song_ptr;

void patern_definition()
{
         if(patern == 0){ data_song_ptr = data_song_axelf0 ; }
         if(patern == 1){ data_song_ptr = data_song_axelf1 ; }
         if(patern == 2){ data_song_ptr = data_song_axelf2 ; }
         if(patern == 3){ data_song_ptr = data_song_axelf3 ; }
         if(patern == 4){ data_song_ptr = data_song_axelf4 ; }
         if(patern == 5){ data_song_ptr = data_song_axelf5 ; }
         if(patern == 6){ data_song_ptr = data_song_axelf6 ; }
         if(patern == 7){ data_song_ptr = data_song_axelf7 ; }
         if(patern == 8){ data_song_ptr = data_song_axelf8 ; }
         if(patern == 9){ data_song_ptr = data_song_axelf9 ; }
         if(patern == 10){ data_song_ptr = data_song_axelf10 ; }
         if(patern == 11){ data_song_ptr = data_song_axelf11 ; }
         if(patern == 12){ data_song_ptr = data_song_axelf12 ; }
         if(patern == 13){ data_song_ptr = data_song_axelf13 ; }
         if(patern == 14){ data_song_ptr = data_song_axelf14 ; }
         if(patern == 15){ data_song_ptr = data_song_axelf15 ; }
         if(patern == 16){ data_song_ptr = data_song_axelf16 ; }
         if(patern == 17){ data_song_ptr = data_song_axelf17 ; }
         if(patern == 18){ data_song_ptr = data_song_axelf18 ; }
         if(patern == 19){ data_song_ptr = data_song_axelf19 ; }
         if(patern == 20){ data_song_ptr = data_song_axelf20 ; }
         if(patern == 21){ data_song_ptr = data_song_axelf21 ; }
         if(patern == 22){ data_song_ptr = data_song_axelf22 ; }
         if(patern == 23){ data_song_ptr = data_song_axelf23 ; }
         if(patern == 24){ data_song_ptr = data_song_axelf24 ; }
         if(patern == 25){ data_song_ptr = data_song_axelf25 ; }
         if(patern == 26){ data_song_ptr = data_song_axelf26 ; }
         if(patern == 27){ data_song_ptr = data_song_axelf27 ; }
         if(patern == 28){ data_song_ptr = data_song_axelf28 ; }
         if(patern == 29){ data_song_ptr = data_song_axelf29 ; }
}




