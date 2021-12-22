#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

int main()
{
   int fd[10][2];
   
   for(int i = 0; i < 10; i++)
   {
      if(pipe(fd[i]) < 0)
      {
        return 1;
      }
   }

   int pid1 = fork();
   if(pid1 < 0)
   {
      return 1;
   }
   
   if(pid1 == 0)
   {
        char buffer[256];
        char message[] = "process1!\n";
      
   	close(fd[0][0]);
   	close(fd[1][1]);
   	close(fd[2][0]);
   	close(fd[3][1]);
   	close(fd[2][1]);
   	close(fd[3][0]);
   	close(fd[6][0]);
   	close(fd[7][1]);
   	close(fd[6][1]);
   	close(fd[7][0]);
   	close(fd[8][0]);
   	close(fd[9][1]);
   	close(fd[4][1]);
   	close(fd[5][0]);
   	close(fd[4][0]);
   	close(fd[5][1]);
   	
   	sleep(6);
   	
   	if(read(fd[1][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process1 gets %s from Process4\n", buffer);
   	
   	if(write(fd[8][1], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	if(read(fd[9][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process1 gets %s from Process2\n", buffer);
   	
   	if(write(fd[0][1], &message, sizeof(message)) < 0)
   	{
   		return 1;
   	}
   	
   	close(fd[1][0]);
   	close(fd[8][1]);
   	close(fd[9][0]);
   	close(fd[0][1]);   
	return 0;	
   }
   
   int pid2 = fork();
   if(pid2 < 0)
   {
      return 1;
   }
   
   if(pid2 == 0)
   {
        char buffer[256];
        char message[] = "Process2!\n";
      
   	close(fd[0][0]);
   	close(fd[1][1]);
   	close(fd[2][0]);
   	close(fd[3][1]);
   	close(fd[2][1]);
   	close(fd[3][0]);
   	close(fd[6][0]);
   	close(fd[7][1]);
   	close(fd[0][1]);
   	close(fd[1][0]);
   	close(fd[8][1]);
   	close(fd[9][0]);
   	close(fd[4][1]);
   	close(fd[5][0]);
   	close(fd[4][0]);
   	close(fd[5][1]);
   	
   	sleep(4);
   	
   	if(read(fd[8][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process2 gets %s from Process1\n", buffer);
   	
   	if(write(fd[6][1], &message, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	if(read(fd[7][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process2 gets %s from Process3\n", buffer);
   	
   	if(write(fd[9][1], &message, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	close(fd[8][0]);
   	close(fd[9][1]);
   	close(fd[7][0]);
   	close(fd[6][1]);   	
   	return 0;
   }

   
   int pid3 = fork();
   if(pid3 < 0)
   {
      return 1;
   }
   
   if(pid3 == 0)
   {
        char buffer[256];
        char message[] = "process3!\n";
      
   	close(fd[0][0]);
   	close(fd[1][1]);
   	close(fd[2][0]);
   	close(fd[3][1]);
   	close(fd[6][1]);
   	close(fd[7][0]);
   	close(fd[8][0]);
   	close(fd[9][1]);
   	close(fd[0][1]);
   	close(fd[1][0]);
   	close(fd[8][1]);
   	close(fd[9][0]);
   	close(fd[4][1]);
   	close(fd[5][0]);
   	close(fd[4][0]);
   	close(fd[5][1]);
   	
   	//sleep(2);
   	
   	if(read(fd[6][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process3 gets %s from Process2\n", buffer);
   	
   	if(write(fd[2][1], &message, sizeof(message)) < 0)
   	{
   		return 1;
   	}
   	
   	if(read(fd[3][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process3 gets %s from Process4\n", buffer);
   	
   	if(write(fd[7][1], &message, sizeof(message)) < 0)
   	{
   		return 1;
   	}
   	
   	close(fd[6][0]);
   	close(fd[7][1]);
   	close(fd[2][1]);
   	close(fd[3][0]);   	
   	return 0;
   }
   
   int pid4 = fork();
   if(pid4 < 0)
   {
      return 1;
   }
   
   if(pid4 == 0)
   {
        char buffer[] = "Process4!!";
      
   	close(fd[3][0]);
   	close(fd[2][1]);
   	close(fd[6][0]);
   	close(fd[7][1]);
   	close(fd[6][1]);
   	close(fd[7][0]);
   	close(fd[8][0]);
   	close(fd[9][1]);
   	close(fd[0][1]);
   	close(fd[1][0]);
   	close(fd[8][1]);
   	close(fd[9][0]);
   	close(fd[4][1]);
   	close(fd[5][0]);
   	close(fd[4][0]);
   	close(fd[5][1]);
   	
   	if(read(fd[2][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process4 gets %s from Process3\n", buffer);
   	
   	if(write(fd[1][1], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	if(read(fd[0][0], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	printf("Process4 gets %s from Process1\n", buffer);
   	
   	if(write(fd[3][1], &buffer, sizeof(buffer)) < 0)
   	{
   		return 1;
   	}
   	
   	close(fd[2][0]);
   	close(fd[3][1]);
   	close(fd[1][1]);
   	close(fd[0][0]);   	
   	return 0;
   }

   
   waitpid(pid1, NULL, 0);
   waitpid(pid2, NULL, 0);
   waitpid(pid3, NULL, 0);
   
   return 0;
 }
