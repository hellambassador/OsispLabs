#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
   pid_t childpid;
   int child[2], parent[2], counter = 1;
   char buffer[256];
   char childMessage[] = "answer";
   char parentMessage[] = "question";
   char exitMessage[] = "quit";
   

   if (pipe(parent) == -1 || pipe(child) == -1) 
   {
     perror("Failed to pipe\n");
     exit(1);
   }

   if ((childpid = fork()) <= -1) 
   {
     perror("Failed to fork\n");
     exit(1);
   }
   
   if (childpid == 0)
   { 
     close(parent[1]);
     close(child[0]);
   }
   else 
   {   
     close(parent[0]);
     close(child[1]); 
   }
   
   while(1)
   {
      if (childpid == 0) 
      {
        if (read(parent[0], &buffer, sizeof(buffer)) <= 0) 
        {
          perror("Child: failed to read from the parent\n");
          exit(1);
        }
        
        if(counter == 5)
        {
        	write(child[1], &exitMessage, sizeof(exitMessage));
        	break;
        }

        if (write(child[1], &childMessage, sizeof(childMessage)) <= 0) 
        {
          perror("Child: failed to write to the parent\n");
          exit(1);
        }
        
        printf("Child%d recieved %s#%d from Parent\n", counter, buffer, counter);
      } else 
      { 
      	printf("Parent sends %s to Child%d\n", parentMessage, counter);
      	
        if (write(parent[1], &parentMessage, sizeof(parentMessage)) <= 0) 
        {
          perror("Parent: failed to write to the child\n");
          exit(1);
        }        
        
        if (read(child[0], &buffer, sizeof(buffer)) <= 0) 
        {
          perror("Parent: failed to read from the child\n");
          exit(1);
        }
        if(strcmp(buffer, exitMessage)==0)
        {
        	printf("Parent recieved %s from Child%d\n", buffer, counter);
        	break;
        }
        
        sleep(1);
        printf("Parent recieved %s from Child%d\n", buffer, counter);
      }
      counter++;
    }
   return 0;
 }
