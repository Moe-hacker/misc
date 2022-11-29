#define _GNU_SOURCE
#include <linux/stat.h>
#include <linux/sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#define CHROOT_DIR "/data/alpine"
#define BINARY_PATH "./a.out"
void show_n_char(int num){
  char *space=" ";
  int count;
  for (count = 1; count <= num; count++){
    putchar(space[0]);
  }
}
void greeting(){
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  short row=size.ws_col;
  row-=44;
  row/=2;
  show_n_char(row);
  printf("%s\n","\033[30m               ▅▅▀▀▀▀▀▀▀▀▀▀▀▀▅          ");
  show_n_char(row);
  printf("%s\n","          ▅▅▀▀▀               ▀▀▅▅      ");
  show_n_char(row);
  printf("%s\n","     ▅▅▅▀▀            ▅           ▀▅    ");
  show_n_char(row);
  printf("%s\n","      ▅▀      ▅▀█▅▅▀▀▅▀▅        ▅▅  ▀▅  ");
  show_n_char(row);
  printf("%s\n","     ▅▀   █▅▀▀  ▀     ▀ ▀▀▅▅    █ ▀▀▅ █ ");
  show_n_char(row);
  printf("%s\n","    ▅▀   ▅▀  ▅▀      ▀▅    ▀▅   █▅███▀█ ");
  show_n_char(row);
  printf("%s\n","  ▅▅█▀▅ █ ▅▅▀          ▀▀   █   ████   █");
  show_n_char(row);
  printf("%s\n","      █ █ ▅▅▅▅▅        ▅▅▅▅▅ █  ▀█▀    █");
  show_n_char(row);
  printf("%s\n","      █ █▀ ▅▅▅ ▀      ▀ ▅▅▅ ▀█   █     █");
  show_n_char(row);
  printf("%s\n","      █ █ █\033[40;31m█▀█\033[0m\033[30m█        █\033[40;31m█▀█\033[0m\033[30m█ █   █     █   ");
  show_n_char(row);
  printf("%s\n","     █  █ █\033[31m███\033[30m█        █\033[31m███\033[30m█ █   █     ▀▅   ");
  show_n_char(row);
  printf("%s\n","    ▅▀  █  ▀▀▀          ▀▀▀  █   █      █   ");
  show_n_char(row);
  printf("%s\n","  ▅▀▅▀ █                     █   █      █   ");
  show_n_char(row);
  printf("%s\n"," █   █ ▀▅ ▅▀▅   ▅▀▅   ▅▅     █   █      ▀▅  ");
  show_n_char(row);
  printf("%s\n","▅█▅▅██▅ ▅██  ▀███ ▅████ ▀▅█▀▅▀   █       ▀▅ ");
  show_n_char(row);
  printf("%s\n","███████ ▀██████████████████▀▀             █ ");
  show_n_char(row);
  printf("%s\n"," █    ▀▅  ██▀ ▀██▀▀██▀▀██▀█     █▀         █");
  show_n_char(row);
  printf("%s\n"," ▀▅     ▀▀█              ▅▀     █          █");
  show_n_char(row);
  printf("%s\n","   ▀▅    █               █     ██        ▅▀ ");
  show_n_char(row);
  printf("%s\n","     ▀▅▅▅▀                ▀▀▀▀▀ █        █  ");
  show_n_char(row);
  printf("%s\n","        ▀                       ▀        ▀  ");
  show_n_char(row);
  printf("%s\n","           「Keep moe,keep cool」           ");
}
void unshare_container(){
  chroot(CHROOT_DIR);
  chdir("/");
  printf("\033[1;38;2;166;227;161mRun unshare container.\033[0m\n");
  umount("/proc");
  umount("/proc");
  mount("proc","/proc","proc",MS_NOSUID|MS_NOEXEC|MS_NODEV,NULL);
  mount("sysfs","/sys","sysfs",MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_RDONLY,NULL);
  mount("tmpfs","/dev","tmpfs",MS_NOSUID,"size=65536k,mode=755");
  int dev;
  dev=makedev(1,3);
  mknod("/dev/null",S_IFCHR,dev);
  dev=makedev(5,1);
  mknod("/dev/console", S_IFCHR, dev);
  dev=makedev(1,5);
  mknod("/dev/zero",S_IFCHR,dev);
  dev=makedev(5,2);
  mknod("/dev/ptmx",S_IFCHR,dev);
  dev=makedev(5,0);
  mknod("/dev/tty",S_IFCHR,dev);
  dev=makedev(1,8);
  mknod("/dev/random",S_IFCHR,dev);
  dev=makedev(1,9);
  mknod("/dev/urandom",S_IFCHR,dev);
  mkdir("/dev/net", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  dev=makedev(10,200);
  mknod("/dev/net/tun",S_IFCHR,dev);
  symlink("/proc/self/fd", "/dev/fd");
  symlink("/proc/self/fd/0", "/dev/stdin");
  symlink("/proc/self/fd/1", "/dev/stdout");
  symlink("/proc/self/fd/2", "/dev/stderr");
  symlink("/dev/null", "/dev/tty0");
  mkdir("/dev/pts", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("devpts","/dev/pts","devpts",0,"gid=4,mode=620");
  mkdir("/dev/shm", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("tmpfs","/dev/shm","tmpfs",MS_NOSUID|MS_NOEXEC|MS_NODEV,"mode=1777");
  mkdir("/dev/mqune", S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH|S_IRGRP|S_IWGRP);
  mount("mqune","/dev/mqune","mqune",0,NULL);
  chown("/dev/console", 0, 5);
  chown("/dev/ptmx", 0, 5);
  chown("/dev/tty", 0, 5);
  chmod("/dev/console", S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH);
  chmod("/dev/null", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  chmod("/dev/zero", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  chmod("/dev/ptmx", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  chmod("/dev/tty", S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  chmod("/dev/random", S_IRUSR|S_IRGRP|S_IROTH);
  chmod("/dev/urandom", S_IRUSR|S_IRGRP|S_IROTH);
  char *login[]={"/bin/su","-","root",NULL};
  execv(login[0],login);
}
int main(){
  unsetenv("LD_PRELOAD");
  if (getuid()!=0){
    char *privilege[]={"/bin/su","-c",BINARY_PATH,NULL};
    execv(privilege[0],privilege);
    exit(0);
  }
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
  int pid=fork();
  if (pid==0) {
    greeting();
    unshare_container();
  }
  waitpid(pid, NULL, 0);
  return 0;
}
