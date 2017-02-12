#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wrapper.h"
#include "common.h"

#include <form.h>

#define PLANETS 1000000
#define PLANETIPC "PlanetLab"
int my_pid;
int isRunning;
//mqd_t serverHandle;

void *resever(void)
{
    // This is a threaded function
    while(isRunning){
        
        usleep(60000);
    }

    return NULL;
}

planet_type *createPlanet(FIELD **fiealds){
    planet_type *pl;
    pl = (planet_type *) calloc(1,sizeof(planet_type));
    //pl->name
    //field_buffer( &fiealds[0], 0);
    int counter = 0;
    strcat(pl->name,field_buffer(fiealds[counter],0));
    counter++;
    char *text = field_buffer(fiealds[counter],0);
    int mass =  atoi(text);
    pl->mass = mass;
    counter++;
    pl->life= atoi(field_buffer(fiealds[counter],0));
    counter++;
    pl->sx = atoi(field_buffer(fiealds[counter],0));
    counter++;
    pl->sy = atoi(field_buffer(fiealds[counter],0));
    counter++;
    pl->vx = atoi(field_buffer(fiealds[counter],0));
    counter++;
    pl->vy = atoi(field_buffer(fiealds[counter],0));
    pl->pid = my_pid;
    return pl;
}
void printPlanet(planet_type *pl, const char *message)
{
    int posY = LINES - 10, posX = 10;
    static int rowY = 0;
    char *buffer;
    buffer = (char *) calloc(100,sizeof(char));
    //mvprintw(posY+rowY, posX, pl->name );
    sprintf(buffer, "%s: name: %s\tmass: %f\tpos(%f,%f)", message, pl->name, pl->mass,pl->sx,pl->sy); 
    mvprintw(posY+rowY, posX, buffer);
    rowY++;
}
int  sendPlanet(planet_type *pl)
{
    struct messageBuffer buf;
    buf.mtype = 1;
    buf.planet = *pl;
    int id;
    MQcreate(&id, MQNAME);
    MQwrite(id,&buf);
    //MQclose(id);
    return id;
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

int main( )
{

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
    my_pid = getpid();
    isRunning = 1;
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
    FIELD **fiealds;
    fiealds = (FIELD**) calloc(1, sizeof(FIELD));
    //FIELD *fiealds[nrFealds];
    FORM *form;
    //char *text[nrFealds - 1];
    mvprintw(2,20,"Create planets");
    for (int i = 0; i < nrFealds - 1; ++i) {
        fiealds[i] = (FIELD*) calloc(nrFealds, sizeof(FIELD));
        fiealds[i] = new_field(1,30,posY + i * spaceY, posX ,0,0);
        if (fiealds[i] == NULL ) {
            printf("Fieald is NULL\nExit\n");
            exit(EXIT_FAILURE);
        }
        set_field_fore(fiealds[i], COLOR_PAIR(3));
        set_field_back(fiealds[i], COLOR_PAIR(1));
        set_field_back(fiealds[i], A_UNDERLINE);
        field_opts_off(fiealds[i], O_AUTOSKIP);
        //text[i] = NULL;
        //set_field_userptr(fiealds[i], text[i]);
        //set_field_type(fiealds[i], TYPE_ALNUM,30);
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
    // Create threeed to reead messages form server
    pthread_t resThread;
    pthread_create(
    while (running) {
        ch = getch();
        switch (ch ) {
            case KEY_F(5):
                // Send data and emapyt the fiealds.
                mvprintw(20,10,"Created plannet");
                //text[0] = field_userptr(fiealds[0]);
                //field_buffer(fiealds[0], 30);bbb
                //char *text = field_buffer(fiealds[0] , 0);
                //mvprintw(21,10, text);
                planet_type *pl = createPlanet(fiealds);
                sendPlanet(pl);
                printPlanet(pl, "Created");
                break;
            case 9:     // tab to go to nex line
            case 10:    // Eenter for next line
                form_driver(form, REQ_END_LINE);
                form_driver(form, REQ_NEXT_FIELD);
                break;
            case 353:   //Shift tabb to go back
                form_driver(form, REQ_END_LINE);
                form_driver(form, REQ_PREV_FIELD);
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
                if ((ch >= 45) && (ch <= 122)) {
                    form_driver(form, ch);
                }
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
