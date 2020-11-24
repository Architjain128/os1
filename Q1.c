#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
extern int errno;
typedef long long int ll;
static char bar[] = "==================================================>";
char msg[3100000];
char new_file_path[1000000] ="";
char old_file_path[1000000] ="";


// fuunction to get new_file_path and directory
void new_file_name(char* pa){
    if(pa[0]=='.'){
        // printf("relatibe\n");
        const char * op = strrchr(pa,'/');
        ll len=strlen(pa)-strlen(op);
        strcat(new_file_path,"./Assignment");
        strcat(new_file_path,op);
    }
    else if(pa[0]=='/')
    {
        // printf("exact without ~\n");
        const char * op = strrchr(pa,'/');
        ll len=strlen(pa)-strlen(op);
        strcat(new_file_path,"./Assignment");
        strcat(new_file_path,op);
    }
    else
    {
        // printf("only name ~\n")
        strcpy(old_file_path,"./");
        strcat(old_file_path,pa);
        strcat(new_file_path,"./Assignment/");
        strcat(new_file_path,pa);
    }
    
}

int main(int argc, char** argv) 
{ 
    if(argc == 2){
        // copied input
        strcpy(old_file_path,argv[1]);
        new_file_name(argv[1]);
        
        // // paths
        // sprintf(msg,"\033[0;36m%s -> %s  \033[0;36m\n",old_file_path,new_file_path);
        // write(STDOUT_FILENO,msg,strlen(msg));

        sprintf(msg,"\033[0;36mopening files...\033[0;36m\n");
        write(STDOUT_FILENO,msg,strlen(msg));

        ll oldfd,newfd,oldsz,newsz;
        float percent=0.00;
        ll bari;
        
        // opening input file
        oldfd = open(old_file_path ,O_RDONLY);
        if (oldfd < 0)
        {
            perror("\033[1;31m-->input file\033[1;31m");
            exit(1);
        }

        // checking dir if present or not   
        DIR *mir;
        mir = opendir("Assignment");
        if(mir==0){
            // if not, then creating dir
            ll dir = mkdir("Assignment",0777);
            if(dir < 0)
            {
                perror("\033[1;31m-->making dir\033[1;31m");
                exit(1);
            }
        }

        // opening output file 
        newfd = open(new_file_path ,O_CREAT | O_APPEND | O_WRONLY |O_TRUNC, 0777);
        if (newfd < 0)
        {
            perror("\033[1;31m-->output file\033[1;31m");
            exit(1);
        }

        sprintf(msg,"\033[0;36mAll ready to go...\033[0;36m\n");
        write(STDOUT_FILENO,msg,strlen(msg));

        ll i = lseek(oldfd, 0, SEEK_END);
        ll szbuffer=200000000;
        if(i<2*1e9)
        szbuffer=100000000;

        char *BUFFER = (char *)calloc(szbuffer, sizeof(char));
        
        ll file_size = i;
        ll rmsize=file_size;

        if(file_size==0)
        {
            percent = 100.00;
            bari =49;
            sprintf(msg,"\033[1;31m-->File size is zero\n\033[1;31m");
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"\033[0;33m %2.2f %% task completed  [%s] \033[0;33m\r",percent,&bar[49-bari]);
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        else{
            while(rmsize)
            {
            char temp[1];
                if(rmsize<szbuffer)
                {
                    szbuffer=rmsize;
                }
                lseek(oldfd,rmsize-szbuffer,SEEK_SET);
                oldsz = read(oldfd,BUFFER,szbuffer);
                if(oldsz<0)
                {
                    perror("\033[1;31m-->read\033[1;31m");
                }
                for(ll j=0;j<szbuffer/2;j++)
                {
                    temp[0]=BUFFER[szbuffer-1-j];
                    BUFFER[szbuffer-1-j]=BUFFER[j];
                    BUFFER[j]=temp[0];
                }
                newsz = write(newfd, BUFFER, szbuffer);
                if(newsz<0)
                {
                    perror("\033[1;31m-->write\033[1;31m");
                }
                rmsize-=szbuffer;

                 percent = (float)(i-rmsize)/(float)i*100;
                bari = (ll)(percent-0.1)/2.00;
                sprintf(msg,"\033[0;33m %2.2f %% task completed  [%s] \033[0;33m\r",percent,&bar[49-bari]);
                write(STDOUT_FILENO,msg,strlen(msg));

            }
        }
        sprintf(msg,"\033[0m\n\033[0m");  
        write(STDOUT_FILENO,msg,strlen(msg));

        free(BUFFER);
      
        sprintf(msg,"\033[0;36mclosing all files\033[0;36m\n");
        write(STDOUT_FILENO,msg,strlen(msg));
        // closing files
        if(close(oldfd)<0)
        {
            perror("\033[1;31m-->close input file\033[1;31m");
        }
        if(close(newfd)<0)
        {
            perror("\033[1;31m-->close output file\033[1;31m");
        }
    }
    else
    {
        perror("\033[1;31m-->Not correct input\033[1;31m");
        sprintf(msg,"input should be in form ./a.out <file_path>\n");
        write(STDOUT_FILENO,msg,strlen(msg));
    }
    

    return 0; 
} 