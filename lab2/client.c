#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wrapper.h"
#include "common.h"

#include <form.h>

#define SERVEREXE "./server.out"
#define PLANETS 1000000
#define PLANETIPC "PlanetLab"
//#define DEBUG
int my_pid;
int isRunning;
pthread_mutex_t dismut;

// prototypes
typedef struct bordings{
    WINDOW *win;
    int nrMessages;
    char **messages;
    int x;
    int y;
    int w;
    int h;

}t_board;
//mqd_t serverHandle;

t_board *board_create(int y, int x, int w, int h);
void  board_addPlanet(t_board *board, const char *message, planet_type *pl);
void board_addMessage(t_board *board, const char *message);
void board_update(t_board *board);
//void printPlanet(planet_type *pl, const char *message);
//planet_type *createPlanet(FIELD **fiealds);
planet_type *planet_create_from_fieald(FIELD **fiealds);
int  sendPlanet(planet_type *pl, int command);;

// ipmlementation of the board---

t_board *board_create(int y, int x,int w, int h){
    t_board *board = NULL;
    board = (t_board*) calloc(1,sizeof(t_board));
    board->y = y;
    board->x = x;
    board->w = w;
    board->h = h;
    board->win = newwin(h,w,y,x);
    box(board->win, 0,0);
    mvwprintw(board->win,1,2,"Messages");
    wrefresh(board->win);
    board->nrMessages = 0;
    board->messages = (char**) calloc(1,sizeof(char*));
    return board;
}

void  board_addPlanet(t_board *board, const char *message, planet_type *pl){
    board->nrMessages++;
    char buffer[1000];
    sprintf(buffer, "Message:%s\tName:%s\tLife:%d\n\t-- pos(%.3f, %.3f)\tvel(%.3f, %.3f)", message, pl->name, pl->life, pl->sx, pl->sy, pl->vx, pl->vy);
    int len = strlen(buffer);
    board->messages = (char **) realloc(board->messages, board->nrMessages * sizeof(char*));
    board->messages[board->nrMessages-1] = (char *) calloc(len, sizeof(char));
    strncat(board->messages[board->nrMessages-1], buffer, len);
}

void board_addMessage(t_board *board, const char *message){
    board->nrMessages++;
    char buffer[1000];
    sprintf(buffer, "Message:%s\n", message);
    int len = strlen(buffer);
    board->messages = (char **) realloc(board->messages, board->nrMessages * sizeof(char*));
    board->messages[board->nrMessages - 1] = (char *) calloc( len, sizeof(char));
    strncat(board->messages[board->nrMessages - 1 ], buffer, len);
}

void board_update(t_board *board){
    int row = 0;

    mvwprintw(board->win,1,2,"Messages");
    for (int i = board->nrMessages-1; i >= 0; i--){
        // This for loop shuld be printing stuff backcards.
        // How ewer there is a problem with ofset.
        int rp = board->nrMessages - 1 - i;
        if((rp < 0) || (board->nrMessages - 1 < rp)) exit(EXIT_FAILURE);
        //int onRrow = (row)*2 - board->nrMessages;
        int onRrow =  (board->nrMessages - row * 2) + 3;
        mvwprintw(board->win, onRrow, 3, board->messages[rp]);
        row++;
    }

    box(board->win, 0 ,0);
    wrefresh(board->win);
}

// End of booard
void *resever(void)
{
    // This is a threaded function
    int id;
    int s = MQcreate(&id, MQNAME);
    if (s == 0) {
        printf("Cant create massage queue in thread");
        exit(EXIT_FAILURE);
    }
    struct messageBuffer buffer;
    t_board *servBoard = board_create(4,COLS - 91 ,90,200);
    while(isRunning){
        while(!MQread(id, my_pid,&buffer)){
            board_update(servBoard);
            usleep(60000);
        }
        switch (buffer.command)  {
            case 0:
                // Död planet
                //printPlanet(&buffer.planet, "Planet died");
                board_addPlanet(servBoard, "Planet Diedi:", &buffer.planet);
                break;
            case 1:
                // Connection establiched
                //printPlanet(&buffer.planet, "Conected");
                board_addPlanet(servBoard, "Planet Created:", &buffer.planet);
                break;
        }
        board_update(servBoard);
    }
    
    return NULL;
}

planet_type *planet_create_from_fieald(FIELD **fiealds){
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
    pl->life= atof(field_buffer(fiealds[counter],0));
    counter++;
    pl->sx = atof(field_buffer(fiealds[counter],0));
    counter++;
    pl->sy = atof(field_buffer(fiealds[counter],0));
    counter++;
    pl->vx = atof(field_buffer(fiealds[counter],0));
    counter++;
    pl->vy = atof(field_buffer(fiealds[counter],0));
    pl->pid = my_pid;
    return pl;
}

planet_type *cplanet(const char *name, double mass, double sx, double sy, double vx, double vy, double life){
    planet_type *pl;
    pl = (planet_type *) calloc(1,sizeof(planet_type));
    //pl->name
    //field_buffer( &fiealds[0], 0);
    strncat(pl->name, name, 30);
    pl->mass = mass;
    pl->sx = sx;
    pl->sy = sy;
    pl->vx = vx;
    pl->vy = vy;
    pl->life = life;
    pl->pid = my_pid;
    return pl;
}
//void printPlanet(planet_type *pl, const char *message)
//{
    /*int posY = LINES - 20, posX = 10;
    static int rowY = 0;
    char *buffer;
    buffer = (char *) calloc(100,sizeof(char));
    //mvprintw(posY+rowY, posX, pl->name );
    pthread_mutex_lock(&dismut);
    sprintf(buffer, "%s: name: %s\tmass: %f\tpos(%f,%f)", message, pl->name, pl->mass,pl->sx,pl->sy); 
    pthread_mutex_unlock(&dismut);
    mvprintw(posY+rowY, posX, buffer);
    rowY++;*/

//}
int  sendPlanet(planet_type *pl, int command)
{
    struct messageBuffer buf;
    buf.mtype = 1;
    buf.command = command;
    // Command list
    //  1 create a planet
    //  len the 0 kills the srever
    //  3 pauses the animaitons
    if(pl)
        buf.planet = *pl;
    else{
        planet_type *ptemp;
        ptemp = cplanet("",0,0,0,0,0,0);
        buf.planet = *ptemp;
    }
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
    mvprintw(2,COLS / 2 - 10,"Create planets");
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
    int keyposY = 7; 
    mvprintw(keyposY,50,"F3 - Pause server");
    keyposY++;
    mvprintw(keyposY,50,"F5 - Create Planet");
    //keyposY++;
    //mvprintw(keyposY,50,"F9 - Start server");
    keyposY++;
    mvprintw(keyposY,50,"F10 - EXIT");

    /*mvprintw(1 , COLS / 2 - 15 ,"Planet Creator");
    mvprintw(LINES - 1, COLS - 15,"Exit with F10");
    mvprintw(LINES - 1, 5 ,"Send planet to server with F5");
    move(0,0);*/

    // A loop to fill in the form move to diffrent fealds with tabb and shift
    // tabb
    int running = 1;
    int ch = 0;
    t_board *board;
    board = board_create(LINES - 30,1 , 90, 39  );
    board_addMessage(board, "Start");
#ifdef DEBUG
    planet_type *temp1 = cplanet("Earth", 543,543,5433,43433,543,54);
    planet_type *temp2 = cplanet("moon", 43,53,33,433,3,4);
    planet_type *temp3 = cplanet("astroid", 3,3,3,3,333,334);
    board_addPlanet(board, "created", temp1);
    board_addPlanet(board, "created", temp2);
    board_addPlanet(board, "created", temp3);
#endif
    board_update(board);
    // Create threeed to reead messages form server
    threadCreate(resever, NULL);
    while (running) {
        ch = getch();
        switch (ch ) {
            case 9:     // tab to go to nex line
            case 10:  {  // Eenter for next line
                board_update(board);
                form_driver(form, REQ_END_LINE);
                form_driver(form, REQ_NEXT_FIELD);
                break;
            }
            case 353:{   //Shift tabb to go back
                board_update(board);
                form_driver(form, REQ_END_LINE);
                form_driver(form, REQ_PREV_FIELD);
                break;
            }
            case KEY_F(5):{
                planet_type *planet = planet_create_from_fieald(fiealds);
                //planet_type *planet = cplanet("Earth", 543,543,5433,43433,543,54);
                board_addPlanet(board,"Created:", planet);
                sendPlanet(planet, 1);
                free(planet);
                break;
            }
            case KEY_F(10):{
                running = 0;
                sendPlanet(NULL,-1);
                break;
            }
           /* case KEY_F(9):{
                if(access(SERVEREXE, F_OK)) {
                    system(SERVEREXE);
                    board_addMessage(board, "Started server");
                }else{
                    board_addMessage(board, "Server exe not Found");
                }
                break; 
            }*/
            case KEY_F(3):{
                board_addMessage(board, "Pause server");
                sendPlanet(NULL, 3);
                break;
            }
            case 127:{
                //form_driver(form, REQ_CLR_FIELD);
                form_driver(form, REQ_LEFT_CHAR);
                form_driver(form, REQ_DEL_CHAR);
                board_update(board);
                break;
            }
            default:{
                //mvprintw(0,0, (char*)ch);
                if ((ch >= 45) && (ch <= 122)) {
                    form_driver(form, ch);
                }
            }
        }
        board_update(board);
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
