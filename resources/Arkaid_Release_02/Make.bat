G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wa-l -c -o arkaid.o arkaid.c
@CD BungBkg
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wf-bo2 -c -o ..\bungbkg.o bungbkg.c
@CD ..
@CD Splash
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wf-bo3 -c -o ..\Splash.o Splash.c
@CD ..
@CD MainMenu
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wf-bo4 -c -o ..\MainMenu.o MainMenu.c
@CD ..
@CD Story
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wf-bo5 -c -o ..\Story.o Story.c
@CD ..
@CD Record
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wf-bo6 -c -o ..\Record.o Record.c
@CD ..
@CD Music
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wf-bo7 -c -o ..\AxelF.o AxelF.c
@CD ..
@CD Game
G:\SDK\gbz80-gb\2-1-5\bin\lcc -c -o ..\Game.o Game.c
@CD ..
G:\SDK\gbz80-gb\2-1-5\bin\lcc -Wl-yo8 -Wl-yt1 -Wl-yp0x143=0xC0 -Wl-yp0x14A=1 -o arkaid.gb arkaid.o bungbkg.o Splash.o MainMenu.o Story.o Record.o Game.o AxelF.o
