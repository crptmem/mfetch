#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

#define BBLACK   "\033[1;30m"
#define BGRAY    "\033[1;90m"
#define BRED     "\033[1;31m"
#define BGREEN   "\033[1;32m"
#define BYELLOW  "\033[1;33m"
#define BBLUE    "\033[1;34m"
#define BMAGENTA "\033[1;35m"
#define BCYAN    "\033[1;36m"
#define BWHITE   "\033[1;37m"

#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

#define RESET "\033[0;m"
#define BITAL "\033[1;3m" 

struct tux {
	char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8;
};

struct utsname unameData;

struct tux info = {
	.col1 = "\033[0;30m      ___     ",
	.col2 = "     (\033[0;37m..\033[0;30m \\    ",
	.col3 = "     (\033[0;33m<> \033[0;30m|   ",
	.col4 = "    /\033[0;37m/  \\ \\\033[0;30m\\  ",
	.col5 = "   ( \033[0;37m|  | \033[0;30m/|  ",
	.col6 = "  _/\\ \033[0;37m__)\033[0;30m/\033[0;33m_\033[0;30m) ",
	.col7 = "  \033[0;33m\\/\033[0;30m-____\033[0;33m\\/  ",
	.col8 = "",
};


int main() {

  if(uname(&unameData))
    fprintf(stderr, "uname(&unameData) != 0"); 

  int days, hours, mins;
  struct sysinfo sys_info;
  char *user_buf;
  user_buf = (char*)malloc(10 * sizeof(char));
  user_buf = getlogin();

  char *hostname = (char*)malloc(512);
  gethostname(hostname, 512);

  FILE *fp;
  char path[1035];

  fp = popen("cat /etc/*-release | egrep \"PRETTY_NAME\" | cut -d = -f 2 | tr -d '\"' | tac | tr '\n' ' '", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  while (fgets(path, sizeof(path), fp) != NULL) {}

  pclose(fp);
 
  sysinfo(&sys_info);

  hours = sys_info.uptime / 3600;
  mins = (sys_info.uptime / 60) - (hours * 60);


  printf("%s  %s%s%s%s%s%s%s\n", info.col1, BYELLOW, user_buf, BRED, "@", BBLUE, hostname, BLACK);
  printf("%s  %s%s%s%s\n", info.col2, BYELLOW, "kernel " WHITE, unameData.release, BLACK);
  printf("%s  %s%s%s%s%s\n", info.col3, BYELLOW, " os     ", WHITE, path, BLACK);
  printf("%s  %s%s%s%luM%s\n", info.col4, BYELLOW, "ram    ", WHITE, (sys_info.totalram / 1024) / 1024, BLACK);
  printf("%s  %s%s%s%d%s%d%s\n", info.col5, BYELLOW, "uptime ", WHITE, hours, "h ", mins, "m");
  printf("%s\n", info.col6);
  printf("%s\n", info.col7);
  printf("%s\n", info.col8);

  free(hostname);
}
