#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <unistd.h>

#define LINELEN (80)
#define MAX (150)

int lencmp(const char *str1, const char *str2);
int lexcmp(const char *str1, const char *str2);
char *mygets(char *buf, int len);
int mygeti();

int main(int argc, char *argv[])
{
	char *cmpstr[] = {"lexcmp", "lencmp"};
	int veclen = sizeof(cmpstr)/sizeof(char *);
	char str1[LINELEN + 1];
	char str2[LINELEN + 1];
	int index;
	int pipeChild[2];
	int pipeLex[2];
	int pipeLen[2];
	pid_t pidLex = -1, pidLen = -1;
	
	if(pipe(pipeChild) == -1)
	{
		perror("Pipe failure");
		return -2;
	}

	while (1)
	{
		printf("Please enter first string:\n");
		if (mygets(str1, LINELEN) == NULL)
			break;
		printf("Please enter second string:\n");
		if (mygets(str2, LINELEN) == NULL)
			break;
		do {
			printf("Please choose:\n");
			for (int i=0 ; i < veclen ; i++)
				printf("%d - %s\n", i, cmpstr[i]);
			index = mygeti();
		} while ((index < 0) || (index >= veclen));
		
		if(index == 0 && pidLex == -1)
		{
			if(pipe(pipeLex) == -1)
			{
				perror("Pipe failure");
				return -2;
			}
			pidLex = fork();
			if(pidLex == 0)
			{
				dup2(pipeLex[0], 0);
				dup2(pipeChild[1], 1);
				close(pipeLex[1]);
				close(pipeChild[0]);
				
				char* args[] = {"loopcmp", "lexcmp", NULL};
				execvp("./loopcmp", args);
				perror("lexcmp lunch failed");
				return -2;
			}
		}
		
		if(index == 1 && pidLen == -1)
		{
			if(pipe(pipeLen) == -1)
			{
				perror("Pipe failure");
				return -2;
			}
			pidLen = fork();
			if(pidLen == 0)
			{
				dup2(pipeLen[0], 0);
				dup2(pipeChild[1], 1);
				close(pipeLen[1]);
				close(pipeChild[0]);
				
				char* args[] = {"loopcmp", "lencmp", NULL};
				execvp("./loopcmp", args);
				perror("lencmp lunch failed");
				return -2;
			}
		}
		int WFD = (index == 0) ? pipeLex[1] : pipeLen[1];
		write(WFD, str1, strlen(str1));
		write(WFD, "\n", 1);
		write(WFD, str2, strlen(str2));
		write(WFD, "\n", 1); 
		
		char buffer[MAX];
		int num = read(pipeChild[0], buffer, sizeof(buffer) - 1);
		if(num > 0)
		{
			buffer[num] = '\0';
			int res = atoi(buffer);
			printf("%s(%s, %s) == %d\n", cmpstr[index], str1, str2, res);
			fflush(stdout);
		}
		else
		{
			perror("read failed\n");
			return -2;
		}
	}
	if(pidLex > 0)
	{
		waitpid(pidLex, NULL, 0);
		pidLex = -1;
	}
	if(pidLen > 0)
	{
		waitpid(pidLen, NULL, 0);
		pidLen = -1;
	}
	close(pipeChild[0]);
	close(pipeChild[1]);
	return 0;
}



char *mygets(char *buf, int len)
{
	char *retval;

	retval = fgets(buf, len, stdin);
	buf[len] = '\0';
	if (buf[strlen(buf) - 1] == 10) /* trim \r */
		buf[strlen(buf) - 1] = '\0';
	else if (retval) 
		while (getchar() != '\n'); /* get to eol */

	return retval;
}

int mygeti()
{
	int ch;
	int retval=0;

	while(isspace(ch=getchar()));
	while(isdigit(ch))
	{
		retval = retval * 10 + ch - '0';
		ch = getchar();
	}
	while (ch != '\n')
		ch = getchar();
	return retval;
}
