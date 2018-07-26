#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <curses.h>
#include <stdlib.h>

#define MAX_NAME_LEN 45
#define KEY_ENTER 10

//screen window subwindow
//stdscr curscr

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}


int main(int argc, char const *argv[])
{
    WINDOW *wnd;
    WINDOW *subwnd;
    int fd, ch;
	int tryfd;
    char file_name[MAX_NAME_LEN + 1];
	char file_buf[3005];
	char insert_buf[3000];

    initscr();
    raw();
    keypad(stdscr, TRUE);
    signal(SIGWINCH, sig_winch);
    cbreak();
    refresh();
    curs_set(TRUE);
    
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLUE);
  	
    if(argc>1){
		fd = open(argv[1],O_RDWR);
		if(fd == -1) perror("descriptor");
		if(!read(fd, file_buf, 1500)) perror("read");
		delwin(wnd);
		clear();
		wnd = newwin(80, 80, 1, 1);
		printw("%s\n", file_buf);
		refresh();
   	}
  	else{
   		wnd = newwin(5, 35, 10, 15);
    	wbkgd(wnd, COLOR_PAIR(1));
    	box(wnd, '|', '-');
    	mvwprintw(wnd, 0, 2, "[F1]-open|[F2]-save|[F3]-close");
    	mvwprintw(wnd, 2, 2, "Please, enter the name of file:");
    	wrefresh(wnd);
    	mvwgetnstr(wnd, 3, 5, file_name, MAX_NAME_LEN);
   		wmove(wnd, 3, 5 + sizeof(file_name));
   		curs_set(FALSE);
  	}

   	while(ch = getch()){
   		if(ch == KEY_F(1)){
    	//f1 open file
			fd = open(file_name,O_RDWR);
			if(fd == -1) perror("descriptor");
			if(!read(fd, file_buf, 1500)) perror("read");
			delwin(wnd);
			clear();
			wnd = newwin(80, 80, 1, 1);
			printw("%s\n", file_buf);
			refresh();
			break;
    }
   } 	
   	curs_set(TRUE);
    move(0, 0);
	//getnstr(insert_buf, 3000);

	while(ch = getch()){
	//f2 edit
		if(ch == KEY_ENTER){
			int x,y;
			getyx(stdscr,y,x);
			move(y+1,0);
		}	
		if(ch == KEY_F(2)){
	    	scr_dump("try.txt");
    		tryfd = open("try.txt", O_RDWR); //change to file_name
    		lseek(tryfd, 92,SEEK_SET);
    		read(tryfd, file_buf, 3000);
    		pwrite(fd, file_buf, 3000, 0);
		}
	//f3 close
		else if(ch == KEY_F(3)){
			endwin();
    		exit(EXIT_SUCCESS);
			return 0;
		}
	}
}