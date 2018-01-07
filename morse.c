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
  int trans;
  int text;
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
  //get input from html page--form



  /* Make the response body */
  //sprintf(content, "<p> Welcome to the morse translation website: </p>");
  //sprintf(content, "%sThanks for visiting!\r\n", content);
  sprintf(content, "%sHere is the argument you typed:%s\n", content, buf);
  fprintf(stdout, "here is the argument you typed: %s", buf);
  /* Generate the HTTP response */
  sprintf(command, "GET /translate/morse.json?%s HTTP/1.1%s", arg1, newline);
  Rio_writen(clientfd, command, strlen(command)); //sends input into the server--api
  sprintf(command, "Host: %s%s%s", host, newline, newline);
  Rio_writen(clientfd, command, strlen(command));
  //fprintf(stderr, "this is the error: ");

  //char *stop_string =' ,\n"text"';
  //int stop_string_len = strlen(stop_string);

  while((retval = Rio_readlineb(&rio, buff, MAXLINE)) > 0){
    //fprintf(stderr, "response: %s\n", buff);
    //sprintf(content, "<p> Welcome to the morse translation website: </p>");
    //sprintf(content, "%s<p>Here is the output: %s</p>\n", content, buff);
    //fprintf(stderr, "This is the content %s", buff);
    fprintf(fp, "%s\n", buff);
    fflush(stdout);
    Fputs(buff, stdout);
  }

  fsetpos(fp, &position);

  //parse through file
  trans = regcomp(&regex, "\"translated\": \"", 0);
  text = regcomp(&regex2, "\"text\": \"", 0);

  while(fgets(buff, MAXLINE, fp)){
    //fprintf(stderr, "This is buff %s", buff);
    trans = regexec(&regex, buff, 0, NULL, 0);
    text = regexec(&regex2, buff, 0, NULL, 0);
    //fprintf(stderr, "this is trans %d", trans);
    //fprintf(stderr, "this is text %d", text);

    if (trans==0 && match ==0){
      match=1;
      fprintf(stdout, " this is trans %s",  buff);
      fflush(stdout);
    }

    else if (text==0 && match==1){
      match = 2;
      fprintf(stdout, " this is text %s", buff);
      fflush(stdout);
    }

    else if (match==2){
      fprintf(stdout, "%s\n", buff);
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
