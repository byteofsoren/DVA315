#include <stdio.h>
#include <string.h>
#include "wrapper.h"

#include <form.h>

#define PLANETS 1000000
#define PLANETIPC "PlanetLab"
//mqd_t serverHandle;


void initwindows()
{
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
 
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

    int posY = 5, posX = 18, nrFealds = 8 , spaceY = 2;
    const char *labels[] = {
        "1. Name: ",
        "2. Mass: ",
        "3. Life: ",
        "4. Pos X: ",
        "5. Pos Y: ",
        "6. Speed X: ",
        "7. Speed Y: "};
    //Name = new_field(1,30,posY, posY,0,0);
    FIELD *fiealds[nrFealds];
    FORM *form;
    mvprintw(2,20,"Create planets");
    for (int i = 0; i < nrFealds - 1; ++i) {
        fiealds[i] = new_field(1,30,posY + i * spaceY, posX ,0,0);
        if (fiealds[i] == NULL ) {
            printf("Fieald is NULL\nExit\n");
            exit(EXIT_FAILURE);
        }
        set_field_fore(fiealds[i], COLOR_PAIR(3));
        set_field_back(fiealds[i], COLOR_PAIR(1));
        set_field_back(fiealds[i], A_UNDERLINE);
        field_opts_off(fiealds[i], O_AUTOSKIP);
    }
    fiealds[nrFealds] = NULL;       // Terminating the fealds.
    form = new_form(fiealds);
    post_form(form);
    refresh();
    for (int i = 0; i < nrFealds - 1; ++i) {
        mvprintw(posY + i * spaceY, posX - 15, labels[i]);
    }

    mvprintw(1 , COLS / 2 - 15 ,"Planet Creator");
    mvprintw(LINES - 1, COLS - 15,"Exit with F10");
    mvprintw(LINES - 1, 5 ,"Send planet to server with F5");
    move(0,0);
    // A loop to fill in the form move to diffrent fealds with tabb and shift
    // tabb
    int running = 1;
    int ch = 0;
    while (running) {
        ch = getch();
        switch (ch ) {
            case KEY_F(5):
                // Send data and emapyt the fiealds.
                mvprintw(20,10,"Created plannet");
                break;
            case KEY_DOWN:
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form, REQ_END_LINE);
                break;
            case KEY_UP:
                form_driver(form, REQ_PREV_FIELD);
                form_driver(form, REQ_END_LINE);
                break;
            case KEY_F(10):
                running = 0;
                break;
            case 127:
                //form_driver(form, REQ_CLR_FIELD);
                form_driver(form, REQ_LEFT_CHAR);
                form_driver(form, REQ_DEL_CHAR);
                break;
            default:
                //mvprintw(0,0, (char*)ch);
                form_driver(form, ch);
        }
    }
    // Freeing memmory. =)
    unpost_form(form);
    free_form(form);
    for (int i = 0; i < nrFealds - 1; ++i) {
        free_field(fiealds[i]);
    }
    // Create labbels
    // Print labbles 

    /* Update the stacking order. 2nd panel will be on top */

	/* Show it on the screen */
	doupdate();
	
	//getch();
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
