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
char new_file_path[1000000] ="";
char old_file_path[1000000] ="";
char directory[1000000] ="";
char msg[1000000] ;
char *output4[]= {"Yes","No"};
ll arrary[3][9];
ll check[3]={1,1,1};

void init()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            arrary[i][j]=-1;
        }   
    }
}

// function to 
void prop(struct stat stats,int a){
    if(stats.st_mode & S_IRUSR){
        arrary[a][0]=1;
    }
    else{
        arrary[a][0]=0;
    }
    if(stats.st_mode & S_IWUSR){
        arrary[a][1]=1;
    }
    else{
        arrary[a][1]=0;
    }
    if(stats.st_mode & S_IXUSR){
        arrary[a][2]=1;
    }
    else{
        arrary[a][2]=0;
    }
    if(stats.st_mode & S_IRGRP){
        arrary[a][3]=1;
    }
    else{
        arrary[a][3]=0;
    }
    if(stats.st_mode & S_IWGRP){
        arrary[a][4]=1;
    }
    else{
        arrary[a][4]=0;
    }
    if(stats.st_mode & S_IXGRP){
        arrary[a][5]=1;
    }
    else{
        arrary[a][5]=0;
    }
    if(stats.st_mode & S_IROTH){
        arrary[a][6]=1;
    }
    else{
        arrary[a][6]=0;
    }
    if(stats.st_mode & S_IWOTH){
        arrary[a][7]=1;
    }
    else{
        arrary[a][7]=0;
    }
    if(stats.st_mode & S_IXOTH){
        arrary[a][8]=1;
    }
    else{
        arrary[a][8]=0;
    }
    
    
}

int main(int argc, char** argv) 
{ 
    if(argc == 4){
        init();
        // copied input in a variable
        strcpy(new_file_path,argv[1]);
        strcpy(old_file_path,argv[2]);
        strcpy(directory,argv[3]);
       
        sprintf(msg,"\033[0;36mopening files...\033[0;36m\n");
        write(STDOUT_FILENO,msg,strlen(msg));

        ll oldfd,newfd,oldsz,newsz;
        ll flag=1;
        float percent;
        ll bari;
      
        // opening oldfile 
        oldfd = open(old_file_path ,O_RDONLY);
        if (oldfd < 0)
        {
            perror("\033[1;31m-->opening old file\033[1;31m");
            check[1]=0;
        }

        // checking dir if present or not   
        DIR *mir;
        mir = opendir(directory);
        if(mir==0){
            perror("\033[1;31m-->checking for directory\033[1;31m");
            check[2]=0;
        }
          
        // opening newfile
        newfd = open(new_file_path ,O_RDONLY);
        if (newfd < 0)
        {
            perror("\033[1;31m-->opening new file\033[1;31m");
            check[0]=0;
        }

        sprintf(msg,"\033[0;36mAll ready to go...\033[0;36m\n");
        write(STDOUT_FILENO,msg,strlen(msg));


        ll szbuffer = 100000000;
        char *BUFFER = (char *)calloc(szbuffer, sizeof(char));
        char *DUFFER = (char *)calloc(szbuffer, sizeof(char));
        
        ll old_file_size = lseek(oldfd, 0, SEEK_END);
        ll new_file_size = lseek(newfd, 0, SEEK_END);
       
        // checking the file sizes 
        if(old_file_size != new_file_size)
        {
            perror("\033[1;31m-->file size not matched\033[1;31m");
            flag = 0;
        }
        else if(old_file_size==0)
        {
            percent = 100.00;
            bari =49;
            sprintf(msg,"\033[1;31m-->File size is zero\n\033[1;31m");
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"\033[0;33m %2.2f %% task completed  [%s] \033[0;33m\r",percent,&bar[49-bari]);
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        else{
        }
        ll rmsize=old_file_size;
        ll pip=0;
        ll i=old_file_size;
        if(flag == 1)
        {
            while(rmsize)
            {
                if(rmsize<szbuffer)
                {
                    szbuffer=rmsize;
                }
                
                lseek(oldfd, rmsize-szbuffer, SEEK_SET);
                lseek(newfd, pip, SEEK_SET);

                oldsz = read(oldfd,BUFFER,szbuffer);
                if(oldsz<0)
                {
                    perror("\033[1;31m-->reading from oldfile\033[1;31m");
                }
                newsz = read(newfd,DUFFER,szbuffer);
                if(oldsz<0)
                {
                    perror("\033[1;31m-->reading from newfile\033[1;31m");
                }
                for(ll z=0;z<szbuffer;z++)
                {
                    if(DUFFER[z]!=BUFFER[szbuffer-1-z])
                    {
                        flag=0;
                        break;
                    } 
                }
                if(flag==0)
                {
                    sprintf(msg,"\033[0;33m file is not reversed [%s]\033[0;33m\r",&bar[0]);
                    write(STDOUT_FILENO,msg,strlen(msg));
                    break;
                }
                rmsize-=szbuffer;
                pip+=szbuffer;
                percent = (float)(i-rmsize)/(float)i*100;
                bari = (ll)(percent-0.1)/2.00;
                sprintf(msg,"\033[0;33m %2.2f %% task completed  [%s] \033[0;33m\r",percent,&bar[49-bari]);
                write(STDOUT_FILENO,msg,strlen(msg));
            }
        }
        

        free(BUFFER);
        free(DUFFER);

        // checking permissions
        struct stat stats;
        if(check[0]==1)
        {
            if(stat(new_file_path, &stats)==0)
            {
                prop(stats,0);
            } 
            else
            {
                perror("\033[1;31m-->newfile properties\033[1;31m");
            }
        }
        if (check[1]==1)
        {
            if(stat(old_file_path, &stats)==0)
            {
                prop(stats,1);
            } 
            else
            {
                perror("\033[1;31m-->oldfile properties\033[1;31m");
            }
        }
        if(check[2]==1)
        {
            if(stat(directory, &stats)==0)
            {
                prop(stats,2);
            } 
            else
            {
                perror("\033[1;31m-->directory properties\033[1;31m");
            }
        }
       
        // printind output
        sprintf(msg,"\033[0m\n\n\033[0m");  
        write(STDOUT_FILENO,msg,strlen(msg));
        sprintf(msg,"Directory is created: %s\n\n",output4[1-check[2]]);
        write(STDOUT_FILENO,msg,strlen(msg));
        sprintf(msg,"Whether file contents are reversed in newfile: %s\n\n",output4[1-flag]);
        write(STDOUT_FILENO,msg,strlen(msg));
        if(check[0]==1){
            sprintf(msg,"User has read permissions on newfile : %s\n",output4[1-arrary[0][0]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"User has write permissions on newfile : %s\n",output4[1-arrary[0][1]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"User has execute permissions on newfile : %s\n",output4[1-arrary[0][2]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has read permissions on newfile : %s\n",output4[1-arrary[0][3]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has write permissions on newfile : %s\n",output4[1-arrary[0][4]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has execute permissions on newfile : %s\n",output4[1-arrary[0][5]]);
            write(STDOUT_FILENO,msg,strlen(msg)); 
            sprintf(msg,"Others has read permissions on newfile : %s\n",output4[1-arrary[0][6]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Others has write permissions on newfile : %s\n",output4[1-arrary[0][7]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Others has execute permissions on newfile : %s\n\n",output4[1-arrary[0][8]]);
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        else{
            sprintf(msg,"Can't find out permissions of newfile\n");
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        if(check[1]==1){
            sprintf(msg,"User has read permissions on oldfile : %s\n",output4[1-arrary[1][0]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"User has write permissions on oldfile : %s\n",output4[1-arrary[1][1]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"User has execute permissions on oldfile : %s\n",output4[1-arrary[1][2]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has read permissions on oldfile : %s\n",output4[1-arrary[1][3]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has write permissions on oldfile : %s\n",output4[1-arrary[1][4]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has execute permissions on oldfile : %s\n",output4[1-arrary[1][5]]);
            write(STDOUT_FILENO,msg,strlen(msg)); 
            sprintf(msg,"Others has read permissions on oldfile : %s\n",output4[1-arrary[1][6]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Others has write permissions on oldfile : %s\n",output4[1-arrary[1][7]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Others has execute permissions on oldfile : %s\n\n",output4[1-arrary[1][8]]);
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        else{
            sprintf(msg,"Can't find out permissions of oldfile\n");
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        if(check[2]==1){
            sprintf(msg,"User has read permissions on directory : %s\n",output4[1-arrary[2][0]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"User has write permissions on directory : %s\n",output4[1-arrary[2][1]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"User has execute permissions on directory : %s\n",output4[1-arrary[2][2]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has read permissions on directory : %s\n",output4[1-arrary[2][3]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has write permissions on directory : %s\n",output4[1-arrary[2][4]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Group has execute permissions on directory : %s\n",output4[1-arrary[2][5]]);
            write(STDOUT_FILENO,msg,strlen(msg)); 
            sprintf(msg,"Others has read permissions on directory : %s\n",output4[1-arrary[2][6]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Others has write permissions on directory : %s\n",output4[1-arrary[2][7]]);
            write(STDOUT_FILENO,msg,strlen(msg));
            sprintf(msg,"Others has execute permissions on directory : %s\n\n",output4[1-arrary[2][8]]);
            write(STDOUT_FILENO,msg,strlen(msg));
        }
        else{
            sprintf(msg,"Can't find out permissions of directory\n");
            write(STDOUT_FILENO,msg,strlen(msg));
        }

        sprintf(msg,"\033[0;36mclosing all files\033[0;36m\n");
        write(STDOUT_FILENO,msg,strlen(msg));
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
        perror("\033[1;31m--> Not correct input format\033[1;31m");
        sprintf(msg,"input should be in form ./a.out <new_file_path> <old_file_path> <directory_path>\n");
        write(STDOUT_FILENO,msg,strlen(msg));
    }
    
    return 0; 
} 