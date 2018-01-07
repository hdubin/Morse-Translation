#include "csapp.h"

int main() 
{
  char *buf, buff[MAXLINE];// *p;
  char arg1[MAXLINE], content[MAXLINE], command[MAXLINE];
  int clientfd, retval;
  char *host, *port;//, *buf2 , *buf[MAXLINE];
  rio_t rio;
  char *newline = "\r\n";
  /* Extract the argument of the phrase */
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    strcpy(arg1, buf);
  }
  
  
  host = "api.funtranslations.com";
  //host = "http://api.funtranslations.com/translate/morse.json";
  port = "80";
  
  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd); //initialize rio library
  //get input from html page--form



  /* Make the response body */
  sprintf(content, "<p> Welcome to the morse translation website: </p>");
  sprintf(content, "%sThanks for visiting!\r\n", content);
  sprintf(content, "%sHere is the argument you typed:%s\n", content, buf);
  /* Generate the HTTP response */
  sprintf(command, "GET /translate/morse.json?%s HTTP/1.1%s", arg1, newline);
  Rio_writen(clientfd, command, strlen(command)); //sends input into the server--api
  sprintf(command, "Host: %s%s%s", host, newline, newline);
  Rio_writen(clientfd, command, strlen(command));
  //fprintf(stderr, "this is the error: ");

  while((retval = Rio_readlineb(&rio, buff, MAXLINE)) > 0){
    fprintf(stderr, "response: %s\n", buff);
    //sprintf(content, "<p> Welcome to the morse translation website: </p>");
    sprintf(content, "%sHere is the argument you typed: %s\n", content, buff);
  }
  

  
  //Rio_readlineb(&rio, buf, MAXLINE);  //READ FROM THE SERVER
  //Fputs(buf, stdout);
  //fprintf(stderr, "this is the second error: ");
  //sprintf(content, "%sthis is the buf%s\n", content,  buf);
  //fprintf(stderr, "This is the content %s", buf);
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
