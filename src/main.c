#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

#define BBLACK   "\033[1;30m"
#define BRED     "\033[1;31m"
#define BBLUE    "\033[1;34m"
#define BWHITE   "\033[1;37m"
#define WHITE    "\033[0;37m"
#define BLACK    "\033[0;30m"
#define BYELLOW  "\033[1;33m"
#define RESET    "\033[0;m"

struct tux {
	char *col1, *col2, *col3, *col4, *col5, *col6, *col7, *col8;
};

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

void get_pretty_name(char *buf){
  FILE *fp;

  fp = popen("cat /etc/*-release | egrep \"PRETTY_NAME\" | cut -d = -f 2 | tr -d '\"' | tac | tr '\n' ' '", "r");
  if (fp == NULL) {
    fprintf(stderr, "fp == NULL");
    exit(1);
  }

  while (fgets(buf, sizeof(buf), fp) != NULL) {}

  pclose(fp);
}

int main() {
  struct utsname unameData;
  int days, hours, mins;
  struct sysinfo sys_info;
  char *user_buf = malloc(10 * sizeof(char));
  char *pretty_name_buf = malloc(1024);

  sysinfo(&sys_info);
  get_pretty_name(pretty_name_buf);
  if(uname(&unameData)) {
    fprintf(stderr, "uname(&unameData) != 0");
    exit(1);
  }

  user_buf = getlogin();

  hours = sys_info.uptime / 3600;
  mins = (sys_info.uptime / 60) - (hours * 60);

  printf("%s  %s%s%s%s%s%s%s\n", info.col1, BYELLOW, user_buf, BRED, "@", BBLUE, unameData.nodename, BLACK);
  printf("%s  %s%s%s%s\n", info.col2, BYELLOW, "kernel " WHITE, unameData.release, BLACK);
  printf("%s  %s%s%s%s%s\n", info.col3, BYELLOW, " os     ", WHITE, pretty_name_buf, BLACK);
  printf("%s  %s%s%s%luM%s\n", info.col4, BYELLOW, "ram    ", WHITE, (sys_info.totalram / 1024) / 1024, BLACK);
  printf("%s  %s%s%s%d%s%d%s\n", info.col5, BYELLOW, "uptime ", WHITE, hours, "h ", mins, "m");
  printf("%s\n", info.col6);
  printf("%s\n", info.col7);
  printf("%s\n", info.col8);

}
