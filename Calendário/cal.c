/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void* parametro;
char* parametro1;
char* parametro2;
char* aux1;
char* aux2;
char* aux3;
char* aux4;
char* aux5;
char* ano = NULL; //facilitador de leitura de código.
char* mes = NULL; //facilitador de leitura de código.cal.c
char* erro1 = "Parametros ausentes ou incorretos, use mes entre 1 e 12 e ano entre 1 e 9999.\n\n\n";
char* erro2 = "Parametros incorretos\n\n";

/* HTML source for the start of the page we generate.  */

static char* page_start =
  "<html>\n"
  " <body>\n"
  "  <pre>\n";

/* HTML source for the end of the page we generate.  */

static char* page_end =
  "  </pre>\n"
  " </body>\n"
  "</html>\n";

void module_generate (int fd)
{
  pid_t child_pid;
  int rval;

  /* Write the start of the page.  */
  write (fd, page_start, strlen (page_start));
  /* Fork a child process.  */
  child_pid = fork ();
  if (child_pid == 0) {
    /* This is the child process.  */
    /* Set up an argumnet list for the invocation of df.  */
    /* Duplicate stdout and stderr to send data to the client socket.  */
    rval = dup2 (fd, STDOUT_FILENO);
    if (rval == -1)
      system_error ("dup2");
    rval = dup2 (fd, STDERR_FILENO);
    if (rval == -1)
      system_error ("dup2");
    /* Run df to show the free space on mounted file systems.  */
    if (parametro == NULL)
      {
	char* argv[] = { "/usr/bin/cal","-h", NULL };
	execv (argv[0], argv);
      }else {
	      aux1 = strtok(parametro, "&");
	      aux2 = strtok(NULL, "&");
	      aux3 = strtok(aux1,"=");
	      parametro1 = strtok(NULL, "=");
 	      
              if(aux2 != NULL)
	      {
		aux4 = strtok(aux2, "=");
	        parametro2 = strtok(NULL, "=");
	      }
	      //Verifica se os dois parâmetros são nulos
              if(aux1 == NULL && aux2 == NULL)
	      {
		write(fd, erro1,strlen(erro1));
		char* argv[] = { "/usr/bin/cal","-h", NULL };
	        execv (argv[0], argv);
	      }

	      //Verifica se o primeiro parâmetro esta correto sem um segundo parâmetro.
              if(aux1 != NULL && aux2 == NULL)
	      {
		aux5 = strtok(aux1, "=");
		if (aux5==NULL)
		{
		  write(fd, erro2,strlen(erro2));
		  char* argv[] = { "/usr/bin/cal","-h", NULL };
	          execv (argv[0], argv);
		}else{
                    if (!strcmp(aux5, "ano"))
	            {
		       ano = parametro1;
                    }
                    if (!strcmp(aux5, "mes"))
                    {
		       mes = parametro1;
                    }
		    if (mes != NULL && atoi(mes) > 0 && atoi(mes )<= 12){
		        char* argv[] = { "/usr/bin/cal","-m",mes, NULL };
	                execv (argv[0], argv);
		     }
		     if (ano != NULL && atoi(ano) > 0 && atoi(ano) <= 9999){
		        char* argv[] = { "/usr/bin/cal","-y",ano, NULL };
	                execv (argv[0], argv);
                     }else{
			    write(fd, erro1,strlen(erro1));
			    char* argv[] = { "/usr/bin/cal","-h", NULL };
	                    execv (argv[0], argv);
			  }
		 }
	      }
	     //Verifica se o segundo parâmetro esta correto sem um primeiro parâmetro.
	      if(aux1 == NULL && aux2 != NULL)
	      {
		aux5 = strtok(aux2, "=");
                write(fd, aux5,strlen(aux5));
                write(fd, aux2,strlen(aux2));
		if (aux5==NULL)
		{
		  write(fd, erro2,strlen(erro2));
		  char* argv[] = { "/usr/bin/cal","-h", NULL };
	          execv (argv[0], argv);
		}else{
                    if (!strcmp(aux5, "ano"))
	            {
		       ano = parametro2;
                    }
                    if (!strcmp(aux5, "mes"))
                    {
		       mes = parametro2;
                    }
		    if (mes != NULL && atoi(mes) > 0 && atoi(mes )<= 12){
		        char* argv[] = { "/usr/bin/cal","-m",mes, NULL };
	                execv (argv[0], argv);
		     }
		     if (ano != NULL && atoi(ano) > 0 && atoi(ano) <= 9999){
		        char* argv[] = { "/usr/bin/cal","-y",ano, NULL };
	                execv (argv[0], argv);
                     }else{
			    write(fd, erro1,strlen(erro1));
			    char* argv[] = { "/usr/bin/cal","-h", NULL };
	                    execv (argv[0], argv);
			  }
		 }
	      }

              //Comparação do primeiro parâmetro para garantir que mesmo trocando o ano pelo mês, ele funcionará.
	      if (!strcmp(aux3, "ano"))
	      {
		ano = parametro1;
              }
              if (!strcmp(aux3, "mes"))
              {
		mes = parametro1;
              }
	      if (!strcmp(aux4, "ano"))
	      {
		ano = parametro2;
              }
              if (!strcmp(aux4, "mes"))
              {
		mes = parametro2;
              }
	
	      //Caso exista o ano e o mês, ele exibe o calendário com o mês e ano referente.
	      if (ano != NULL  && mes != NULL && atoi(mes) > 0 && atoi(mes)<= 12 && atoi(ano) > 0 && atoi(ano) <= 9999)
	      {
		char* argv[] = { "/usr/bin/cal","-h","-m",mes, ano, NULL };
	        execv (argv[0], argv); 
	      } else 
		   {
		     if (mes != NULL && atoi(mes) > 0 && atoi(mes )<= 12){
		        char* argv[] = { "/usr/bin/cal","-m",mes, NULL };
	                execv (argv[0], argv);
		     }
		     if (ano != NULL && atoi(ano) > 0 && atoi(ano) <= 9999){
		        char* argv[] = { "/usr/bin/cal","-y",ano, NULL };
	                execv (argv[0], argv);
                     }else{
			    write(fd, erro1,strlen(erro1));
			    char* argv[] = { "/usr/bin/cal","-h", NULL };
	                    execv (argv[0], argv);
			  }
			write(fd, erro1,strlen(erro1));
			char* argv[] = { "/usr/bin/cal","-h", NULL };
	                execv (argv[0], argv);
	           }
      }

    /* A call to execv does not return unless an error occurred.  */
    //system_error ("execv");
  }
  else if (child_pid > 0) {
    /* This is the parent process.  Wait for the child process to
       finish.  */
    rval = waitpid (child_pid, NULL, 0);
    if (rval == -1)
      system_error ("waitpid");
  }
  else 
    /* The call to fork failed.  */
    system_error ("fork");
  /* Write the end of the page.  */
  write (fd, page_end, strlen (page_end));
}
