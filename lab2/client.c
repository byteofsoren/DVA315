#include <stdio.h>
#include <string.h>
#include "wrapper.h"

#include <form.h>

#define PLANETS 1000000
#define PLANETIPC "PlanetLab"
//mqd_t serverHandle;


void initwindows()
{

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);


}
/*
int connectToServer(char * name)
{
	int errorCode = 0;
	Create a socket to handle communication with client
	errorCode = MQconnect (&serverHandle, name);
	return errorCode;
}
*/

int main()
{
    initwindows();
    int posY = 4, posX = 18, nrFealds = 8;
    const char *labels[] = {
        "Name: ",
        "Mass: ",
        "Life: ",
        "Pos X: ",
        "Pos Y: ",
        "Speed X: ",
        "Speed Y: "};
    //Name = new_field(1,30,posY, posY,0,0);
    FIELD *fiealds[nrFealds];
    FORM *form;
    for (int i = 0; i < nrFealds - 1; ++i) {
        fiealds[i] = new_field(1,30,posY + i + 1, posX,0,0);
        set_field_back(fiealds[i], A_UNDERLINE);
        mvprintw(posY + 1 + i, posX - 10,labels[i]);
    }
    fiealds[nrFealds] = NULL;       // Terminating the fealds.
    form = new_form(fiealds);
    post_form(form);
    refresh();
    // Create labbels
    // Print labbles 

    /* Update the stacking order. 2nd panel will be on top */

	/* Show it on the screen */
	doupdate();
	
	getch();
	endwin();
	//Instead of using a returnhandle, we instead use a global mailslot handle (serverHandle)
	//I think this is more convenient, however, would you could alter the method so that it
	//returns a handle
//    int ec = 0;
/*	if ((ec = connectToServer(PLANETIPC))==0)
	{
		printf("Failed to connect to server!");
	}
	while(1)
	{
		//Obviously, since you have already made mailslot read compatible with the
		//Planet struct, you should send a planet to the server

		//Instructions as following:
		//Initialize a planet struct
		//Send the planet struct to the server using MQwrite(&serverHandle)
		//if write is success, then you are very well on your way to a planet system 
	}
	if ((ec = MQclose(&serverHandle, PLANETIPC))==0)
	{
		printf("Failed to close server, watch out for memory leaks");
	}*/
	return 0;
}
