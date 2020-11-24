# Q1
## Assumptions
### **1. Inputs**
  
  input options available of 3 types with 2 arguments ./a.out followed by file path 

    exact path :       /home/user/Desktop/ ....  {don't use ~}
    relative path :    ./file_name       {in current dir only}
    File name :        file_name         {not as /file_name}

### **2. Within the process**
  - used buffer of size 10^8 bytes(aprox 100Mb) for samll files(less than 2gb) and 2*10^8 bytes(aprox 200Mb) for large files(greater than equal to 2gb) so that large files can be reversed quicker.
  - reversing is done by swaping the 2 letters in buffer to decrease the time for reversing(reading and writing in file not included) to half and uses less memory size than 2 buffers
  - percent change can be shown {filesize/buffersize} times after reversing the string copied in buffer.
### **3. Outputs**
   use colour as distinguishing the output by using ANSI code in sprintf function just to distinguish between the output required
  - **Red** for **perror/error message** 
  - **Yellow** for **progress bar** 
  - **cyan** for **other message**
  - **white** for **required output** 
 
newfile is generated in **Assignment directory** in **same directory of executable**

 ***

# Q2
## Assumptions
### **1. Inputs**
  
  - input options available of 3 types with 4 arguments ./a.out followed by two file path and a directory path. 
  - if any path is wrong or file/directory not exists permissions are printed for others 

  `*same as menitoned in Q1`

    exact path :       /home/user/Desktop/ ....  {don't use ~}
    relative path :    ./file_name       {in current dir only}
    File/Dir name :    file_name         {not as /file_name}

### **2. Within the process**
  - used 2 buffer of size 10^8 bytes(approx 100Mb) each so in total it will require 200Mb space for buffers
  - firstly their sizes are matched if same than checking for all characters else files are not reversed.
  - added progress bar.
### **3. Outputs**

  `*same as menitoned in Q1`

  use colour as distinguishing the output by using ANSI code in sprintf function just to distinguish between the output required
  - **Red** for **perror/error message** 
  - **Yellow** for **progress bar** 
  - **cyan** for **other message** 
  - **white** for **required output** 
  ***
_***for other clarification code is commented**_
