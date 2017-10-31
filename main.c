#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

WINDOW* mainw;
WINDOW* header;
WINDOW* footer;
int height,width;

struct send_t{
	char *title;
	char *text;
	char *footer;
};

struct send_t send;
int init();
int acker(int m,int n);
void refreshw(struct send_t* send,int);

int main(){
	if(init())
		return 1;
	send.title="Visual ackermann;  ' '=pause 's'=toggle show";
	send.text=malloc(5000000);
	send.footer=malloc(50);
	for (int loop=0;loop<10;loop++)
		for (int loop0=0;loop0<10;loop0++)
			acker(loop,loop0);
	endwin();
}

int init(){
	initscr();
	getmaxyx(stdscr,height,width);
	curs_set(0);
	header=newwin(1,width,0,0);
	mainw=newwin(height-2,width,1,0);
	footer=newwin(1,width,height-1,0);
	if(mainw==NULL||header==NULL)
		return 1;
	wattron(header,A_REVERSE);
	wattron(footer,A_REVERSE);
	scrollok(mainw,1);
	nodelay(mainw,1);
	keypad(mainw,1);
	noecho();
	return 0;
}

void refreshw(struct send_t* send,int recurtion_level){
	int bw=width;
	getmaxyx(stdscr,height,width);
	if(bw!=width){
		endwin();
		init();
	}
	static int offset=0;
	static int stop=0;
	static int show=1;
	static int frame2=0;
	int ret=wgetch(mainw);
	if(ret==' '||stop==1){
		if(stop)stop=0;
		while(1){
			switch(wgetch(mainw)){
				case KEY_RIGHT:
					stop=1;
					break;
				case ' ':
					stop=2;
					break;
				default:
					usleep(10000);
			}
			if(stop)
				break;
		}
	}else if(ret=='s'){
		show=!show;
	}
	static int before=0;
	if(show){
		if(recurtion_level+strlen(send->text)-offset+1+17*(offset!=0)>(unsigned int)width)
			offset+=width/2-10;
		if(recurtion_level<offset+1)
			offset-=width/2;
		if(offset<0)
			offset=0;
		if(offset)
			wprintw(mainw,"<%04d more lines>",offset);
		for(int loop=0;loop<recurtion_level-1-offset;loop++)
			waddch(mainw,ACS_VLINE);
		if(before<recurtion_level)
			waddch(mainw,ACS_LTEE);
		else
			waddch(mainw,ACS_VLINE);
	}
	before=recurtion_level;
	if(show){
		for(int loop=0;loop<=width;loop++){
			mvwaddch(header,0,loop,' ');
		}
		for(int loop=0;loop<=width;loop++){
			mvwaddch(footer,0,loop,' ');
		}
	}
	if(show||frame2>123){
		frame2=0;
		mvwprintw(header,0,0,"%s",send->title);
		wrefresh(header);
		mvwprintw(footer,0,0,"%s",send->footer);
		wrefresh(footer);
	}else frame2++;
	if(show){
		wprintw(mainw,"%s\n",send->text);
		wrefresh(mainw);
	}
}

int acker(int m,int n){
	static int counter=0;
	static int recurtion_level=0;
	recurtion_level++;
	sprintf(send.text,"acker(%d,%d)",m,n);
	sprintf(send.footer,"ackerman:run %d times, recurtion level %d",counter++,recurtion_level);
	refreshw(&send,recurtion_level);
	if(m==0){
		recurtion_level--;
		return n+1;
	}else if (m>0&&n==0){
		int res=acker(m-1,1);
		recurtion_level--;
		return res;
	}else if(m>0&&n>0){
		int res= acker(m-1,acker(m,n-1));
		recurtion_level--;
		return res;
	}
	recurtion_level--;
}
