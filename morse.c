#include "csapp.h"
#include <regex.h>

int main() 
{
  char *buf, buff[MAXLINE];// *p;
  char arg1[MAXLINE], content[MAXLINE], command[MAXLINE];
  int clientfd, retval;
  char *host, *port;//, *buf2 , *buf[MAXLINE];
  rio_t rio;
  char *newline = "\r\n";
  FILE *fp;
  fpos_t position;
  regex_t regex;
  regex_t regex2;
  int start;
  int end;
  int match = 0;

  //open file
  fp = fopen("file.txt", "w+");

  //get position at beginnning of file
  fgetpos(fp, &position);
  
  /* Extract the argument of the phrase */
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    strcpy(arg1, buf);
  }
  
  host = "api.funtranslations.com";
  port = "80";
  
  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd); //initialize rio library
  
  /* Make the response body */

  /* Generate the HTTP response */
  sprintf(command, "GET /translate/morse.json?%s HTTP/1.1%s", arg1, newline);
  Rio_writen(clientfd, command, strlen(command)); //sends input into the server--api
  sprintf(command, "Host: %s%s%s", host, newline, newline);
  Rio_writen(clientfd, command, strlen(command));

  while((retval = Rio_readlineb(&rio, buff, MAXLINE)) > 0){

    fprintf(fp, "%s\n", buff);
    fflush(fp);

    //****this is the line that prints everything but when commented, nothing prints out 
    //Fputs(buff, stdout);
    //fflush(stdout);
  }

  fsetpos(fp, &position);

  //parse through file
  start = regcomp(&regex, "\"contents\": ", 0);
  //start = regcomp(&regex, "{", 0);
 
  end = regcomp(&regex2, "\"translation\": \"", 0);
  //end = regcomp(&regex2, "}", 0);

  while(fgets(buff, MAXLINE, fp)){
    start = regexec(&regex, buff, 0, NULL, 0);
    end = regexec(&regex2, buff, 0, NULL, 0);
    
    if (start==0 && match == 0){
      match=1;
    }

    else if (end==0 && match == 1){
      break;
    }

    else if (match == 1){
      fprintf(stdout, "%s\n", buff);
      //sprintf(content, "%sThis is what we want printed %s", content, buff);
      //Fputs(buff, stdout);
      fflush(stdout);
    }
    else {
      //fprintf(stdout, "This is everything else fprintf: %s\n", buff);
      //sprintf(content, "%sThis is everything else sprintf:  %s", content, buff);
      //Fputs(buff, stdout);
      fflush(stdout);

    }
  }
  fclose(fp);
  
 
  Close(clientfd); //line:netp:echoclient:close
  exit(0);

} 
