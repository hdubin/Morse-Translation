#include "csapp.h"

int main() 
{
  char *buf;// *p;
  char arg1[MAXLINE], content[MAXLINE]; // command[MAXLINE];
  int clientfd;
  char *host, *port;//, *buf2 , *buf[MAXLINE];
  rio_t rio;
  /* Extract the argument of the phrase */
  if ((buf = getenv("QUERY_STRING")) != NULL) {
    strcpy(arg1, buf);
  }
  char *command;
  char buff[MAXLINE];
  
  
  host = "api.funtranslations.com";
  //host = "http://api.funtranslations.com/translate/morse.json";
  port = "80";
  sprintf(command, "GET https://api.funtranslations.com/json?%s\n", arg1);
  
  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd); //initialize rio library
  //get input from html page--form

  Rio_writen(clientfd, command, MAXLINE);
  Rio_readlineb(&rio, buff, MAXLINE);
  sprintf(content, "%sConnected to api: %s", content, buff);
  



  /* Make the response body */
  sprintf(content, "<p> Welcome to the morse translation website: </p>");
  sprintf(content, "%sThanks for visiting!\r\n", content);
  sprintf(content, "%sHere is the argument you typed:%s\n", content, buf);
  /* Generate the HTTP response */
  //  sprintf(command, "GET http://api.funtranslations.com/translate/morse.json%s", arg1);
    // Rio_writen(clientfd, command, strlen(command)); //sends input into the server--api
  // fprintf(stderr, "this is the error: ");
  //Rio_readlineb(&rio, buf, MAXLINE);  //READ FROM THE SERVER
  //sprintf(buf, "this is the buf%s\n", buf);

  
  printf("Connection: close\r\n");
  printf("Content-length: %d\r\n", (int)strlen(content));
  printf("Content-type: text/html\r\n\r\n");
  printf("%s", content);
  fflush(stdout);
  
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
