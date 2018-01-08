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
  //host = "http://api.funtranslations.com/translate/morse.json";
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

    //****this is the line that prints everything
    //****when commented, nothing prints out
    
    //Fputs(buff, stdout);
    //fflush(stdout);
  }

  fsetpos(fp, &position);

  //parse through file
  start = regcomp(&regex, "\"contents\": ", 0);
  //start = regcomp(&regex, "{", 0);
  //check if it works. i know this is the wrong regex
  
  //trans = regcomp(&regex, "\"translated\": \"", 0);
  end = regcomp(&regex2, "\"translation\": \"", 0);
  //end = regcomp(&regex2, "}", 0);

  while(fgets(buff, MAXLINE, fp)){
    //fprintf(stderr, "This is buff %s", buff);
    start = regexec(&regex, buff, 0, NULL, 0);
    end = regexec(&regex2, buff, 0, NULL, 0);
    //fprintf(stderr, "this is trans %d", trans);
    //fprintf(stderr, "this is text %d", text);

    if (start==0 && match == 0){
      match=1;
      /****this is the first line we want to be printed 
      fprintf(stdout, "<p> This is the morse translation:  %s </p>",  buff);
      sprintf(content, "%sThis is the translation %s", content, buff);
      Fputs(buff, stdout);
      fflush(stdout);
      */
    }

    else if (end==0 && match == 1){
      break;
      
      /****this is the second line we want to be printed
      fprintf(stdout, "<p> This is text you typed %s </p>\n", buff);
      sprintf(content, "%sThis is the text %s", content, buff);
      Fputs(buff, stdout);
      fflush(stdout);
      */
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
  
  //Rio_readlineb(&rio, buf, MAXLINE);  //READ FROM THE SERVER
  //Fputs(buf, stdout);
  //fprintf(stderr, "this is the second error: ");
  //sprintf(content, "%sthis is the buf%s\n", content,  buf);
  //fprintf(stderr, "This is the content %s", buff);
  //sprintf(content, "%sThis is the content %s", content, buf);
  
  //printf("Connection: close\r\n");
  //printf("Content-length: %d\r\n", (int)strlen(content));
  //printf("Content-type: text/html\r\n\r\n");
  //printf("%s", content);
  //fflush(stdout);
  
  Close(clientfd); //line:netp:echoclient:close
  exit(0);

} 
  
/* $end echoclientmain */



//echo client:
//read from keyboard
//send to server 
//read from server
//send back to client (print on terminal)


/*
    if (argc != 1) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
*/
