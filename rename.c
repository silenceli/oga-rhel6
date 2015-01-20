#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_REPETE 5

int main(int argc,char *argv[])
{
 struct passwd *srcc_pwd;
 char log_file[1024] = "/var/log/ovirt-guest-agent/ovirt-guest-agent.log";
 char cmd[1024];
 char exec_file[10240] = "/usr/share/ovirt-guest-agent/rename.sh";
 gid_t srcc_gid;
 uid_t srcc_uid;
 int gg,uu;
 int count;
 FILE *fp = NULL;
 int i=0;
 
 if(argc != 2)
 {
	printf("input should have only 1 parameter\n");
	printf("usage: ./rename hostname\n");
	printf("fg:./rename bcec-test\n");
	exit(-1);	
 }

 sprintf(cmd,"sh %s %s",exec_file,argv[1]);
 printf("cmd = %s\n",cmd);
 //open log file
 fp = fopen(log_file,"a+");
 while(fp == NULL && i < MAX_REPETE)
 {	
	sleep(1);
	fp = fopen(log_file,"a+");
	i++;
 }
 if(fp != NULL)
 {
	fprintf(fp,"rename, %s\n",argv[1]);
 }
 
 srcc_pwd=getpwnam("root");
 srcc_gid=srcc_pwd->pw_gid;
 srcc_uid=srcc_pwd->pw_uid;
 gg=setgid(srcc_gid);
 uu=setuid(srcc_uid);
 //run
 gg=system(cmd);
 printf("ret = %d\n",gg);
 if(fp != NULL)
 {
	fprintf(fp,"rename ret = %d\n",gg);
 	fclose(fp);
 }
 return gg;
}
