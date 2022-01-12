#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void func(int filedes_f){
  int prime;
  if(read(filedes_f,(char *)&prime,4)!=0){
    printf("prime %d\n",prime);
    int filedes_s[2];
    pipe(filedes_s);
    if(fork()==0){
      close(filedes_s[1]);
      func(filedes_s[0]);
    }
    else{
      int t;
      while(read(filedes_f,(char *)&t,4)!=0){
        if(t%prime!=0){
          write(filedes_s[1],(char *)&t,4);
        }
      }
      close(filedes_s[1]);
      close(filedes_s[0]);
      wait(0);
    }
  }
  else{
    close(filedes_f);
  }
}
int main(int argc, char *argv[]){
  int filedes[2];
  int i;
  pipe(filedes);
  int pid=fork();
  if(pid==0){
    close(filedes[1]);
    func(filedes[0]);
  }else{
    for(i=2;i<36;i++){
      write(filedes[1],(char *)&i,4);
    }
    close(filedes[1]);
    close(filedes[0]);
    wait(0);
  }
    exit(0);
}


