//Enable unshare() feature.
#define _GNU_SOURCE
//Include heads.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/stat.h>
#include <linux/sched.h>
#include <linux/limits.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//need to be linked with `-lcap`.
#include <sys/capability.h>
//For debugging,set it to `./a.out`.
//I will find a better way to get root permissions or use shell to implement. 
#define BINARY_PATH "./a.out"
//Only for centering output.
void show_n_char(int num){
  char *space=" ";
  int count;
  for (count = 1; count <= num; count++){
    putchar(space[0]);
  }
}
//Greeting information.
//As an easter agg.
void greeting(){
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  short row=size.ws_col;
  row-=44;
  row/=2;
  show_n_char(row);
  printf("%s\n","\033[30m               ▅▅▀▀▀▀▀▀▀▀▀▀▀▀▅");
  show_n_char(row);
  printf("%s\n","          ▅▅▀▀▀               ▀▀▅▅");
  show_n_char(row);
  printf("%s\n","     ▅▅▅▀▀            ▅           ▀▅");
  show_n_char(row);
  printf("%s\n","      ▅▀      ▅▀█▅▅▀▀▅▀▅        ▅▅  ▀▅");
  show_n_char(row);
  printf("%s\n","     ▅▀   █▅▀▀  ▀     ▀ ▀▀▅▅    █ ▀▀▅ █");
  show_n_char(row);
  printf("%s\n","    ▅▀   ▅▀  ▅▀      ▀▅    ▀▅   █▅███▀█");
  show_n_char(row);
  printf("%s\n","  ▅▅█▀▅ █ ▅▅▀          ▀▀   █   ████   █");
  show_n_char(row);
  printf("%s\n","      █ █ ▅▅▅▅▅        ▅▅▅▅▅ █  ▀█▀    █");
  show_n_char(row);
  printf("%s\n","      █ █▀ ▅▅▅ ▀      ▀ ▅▅▅ ▀█   █     █");
  show_n_char(row);
  printf("%s\n","      █ █ █\033[40;31m█▀█\033[0m\033[30m█        █\033[40;31m█▀█\033[0m\033[30m█ █   █     █");
  show_n_char(row);
  printf("%s\n","     █  █ █\033[31m███\033[30m█        █\033[31m███\033[30m█ █   █     ▀▅");
  show_n_char(row);
  printf("%s\n","    ▅▀  █  ▀▀▀          ▀▀▀  █   █      █");
  show_n_char(row);
  printf("%s\n","  ▅▀▅▀ █                     █   █      █");
  show_n_char(row);
  printf("%s\n"," █   █ ▀▅ ▅▀▅   ▅▀▅   ▅▅     █   █      ▀▅");
  show_n_char(row);
  printf("%s\n","▅█▅▅██▅ ▅██  ▀███ ▅████ ▀▅█▀▅▀   █       ▀▅");
  show_n_char(row);
  printf("%s\n","███████ ▀██████████████████▀▀             █");
  show_n_char(row);
  printf("%s\n"," █    ▀▅  ██▀ ▀██▀▀██▀▀██▀█     █▀         █");
  show_n_char(row);
  printf("%s\n"," ▀▅     ▀▀█              ▅▀     █          █");
  show_n_char(row);
  printf("%s\n","   ▀▅    █               █     ██        ▅▀");
  show_n_char(row);
  printf("%s\n","     ▀▅▅▅▀                ▀▀▀▀▀ █        █");
  show_n_char(row);
  printf("%s\n","        ▀                       ▀        ▀");
  show_n_char(row);
  printf("%s\n","           「Keep moe,keep cool」");
}
//Run unshare container.
void unshare_container(char *CONTAINER_DIR){
  //chroot into container.
  chroot(CONTAINER_DIR);
  chdir("/");
  printf("\033[1;38;2;166;227;161mRun unshare container.\033[0m\n");
  //umount /proc for two times because in my device,it has been mounted twice.
  umount("/proc");
  umount("/proc");
  //mount proc,sys and dev.
  mount("proc","/proc","proc",MS_NOSUID|MS_NOEXEC|MS_NODEV,NULL);
  //For /sys,we make it read-only.
  mount("sysfs","/sys","sysfs",MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_RDONLY,NULL);
  mount("tmpfs","/dev","tmpfs",MS_NOSUID,"size=65536k,mode=755");
  //Continue mounting some other directories in /dev.
  mkdir("/dev/pts", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("devpts","/dev/pts","devpts",0,"gid=4,mode=620");
  mkdir("/dev/shm", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("tmpfs","/dev/shm","tmpfs",MS_NOSUID|MS_NOEXEC|MS_NODEV,"mode=1777");
  mkdir("/dev/mqune", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("mqune","/dev/mqune","mqune",0,NULL);
  //Protect some system runtime directories.
  mount("/proc/bus","/proc/bus","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/fs","/proc/fs","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/irq","/proc/irq","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/sys","/proc/sys","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/asound","/proc/asound","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/proc/scsi","/proc/scsi","proc",MS_BIND|MS_RDONLY,NULL);
  mount("/sys/firmware","/sys/firmware","sysfs",MS_BIND|MS_RDONLY,NULL);
  //For making dev nodes
  int dev;
  //Create system runtime nodes in /dev and then fix permissions.
  dev=makedev(1,3);
  mknod("/dev/null",S_IFCHR,dev);
  chmod("/dev/null", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(5,1);
  mknod("/dev/console", S_IFCHR, dev);
  chown("/dev/console", 0, 5);
  chmod("/dev/console", S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH);
  dev=makedev(1,5);
  mknod("/dev/zero",S_IFCHR,dev);
  chmod("/dev/zero", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(5,2);
  mknod("/dev/ptmx",S_IFCHR,dev);
  chown("/dev/ptmx", 0, 5);
  chmod("/dev/ptmx", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(5,0);
  mknod("/dev/tty",S_IFCHR,dev);
  chown("/dev/tty", 0, 5);
  chmod("/dev/tty", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  dev=makedev(1,8);
  mknod("/dev/random",S_IFCHR,dev);
  chmod("/dev/random", S_IRUSR|S_IRGRP|S_IROTH);
  dev=makedev(1,9);
  mknod("/dev/urandom",S_IFCHR,dev);
  chmod("/dev/urandom", S_IRUSR|S_IRGRP|S_IROTH);
  mkdir("/dev/net", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  dev=makedev(10,200);
  mknod("/dev/net/tun",S_IFCHR,dev);
  //Create some system runtime link files in /dev.
  symlink("/proc/self/fd", "/dev/fd");
  symlink("/proc/self/fd/0", "/dev/stdin");
  symlink("/proc/self/fd/1", "/dev/stdout");
  symlink("/proc/self/fd/2", "/dev/stderr");
  symlink("/dev/null", "/dev/tty0");
  //Lower permissions.

  //TODO:drop more capabilities.
  cap_drop_bound(CAP_SYS_ADMIN);
  //Login to container.
  //Use exec() family function because system() is unavailable now.
  char *login[]={"/bin/su","-",NULL};
  execv(login[0],login);
}
//main() starts here.
//Need to be moved to other function for other functions.
int main(int argc,char **argv){
  if (argc==1){
    printf("Chroot directory not set");
    exit(0);
  }
  //Unset $LD_PRELOAD to run binaries in container.
  unsetenv("LD_PRELOAD");
  //Check if we are running with root permissions.
  if (getuid()!=0){
    //exec() is more powerful than system(),isn't that?
    char *privilege[]={"sudo",BINARY_PATH,argv[1],NULL};
    execvp(privilege[0],privilege);
    //We should exit here to avoid running the following part without root permissions.
    exit(0);
  }
  //Try to create namespaces with unshare().
  if(unshare(CLONE_NEWNS) == -1){
    printf("Seems that mount namespace is not supported on this device\n");
  }
  if(unshare(CLONE_NEWUTS) == -1){
    printf("Seems that uts namespace is not supported on this device\n");
  }
  if(unshare(CLONE_NEWIPC) == -1){
    printf("Seems that ipc namespace is not supported on this device\n");
  }
  if(unshare(CLONE_NEWPID) == -1){
    printf("Seems that pid namespace is not supported in this host\n");
  }
  //Fork itself into namespace.
  //This can fix 'can't fork: out of memory` issue.
  int pid=fork();
  //Run container in the forked process.
  if (pid==0) {
    greeting();
    unshare_container(argv[1]);
  }
  //Fix `can't access tty` issue.
  waitpid(pid, NULL, 0);
  return 0;
}
