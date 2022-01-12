#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
  int p_filedes[2],s_filedes[2];
  pipe(p_filedes);
  pipe(s_filedes);
  char buf[4];
  if(fork()==0){
    read(p_filedes[0],buf,4);
    printf("%d: received %s\n",getpid(),buf);
    write(s_filedes[1],"pong",4);
  }else{
    write(p_filedes[1],"ping",4);
    read(s_filedes[0],buf,4);
    printf("%d: received %s\n",getpid(),buf);
  }
  exit(0);
}
