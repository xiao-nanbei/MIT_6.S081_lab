#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
  for(int i=0;i<argc;i++){
    if(argv[1][i]>'9'||argv[1][i]<'0'){
      write(1, "error\n", 6);
      exit(-1);
    }
  }
  int times=atoi(argv[1]);
  sleep(times);
  exit(0);
}
