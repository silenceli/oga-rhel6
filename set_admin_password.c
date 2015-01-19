#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_REPETE 5

int main(int argc,char *argv[])
{
 struct passwd *srcc_pwd;
 //char *proc_name = "sh /usr/share/ovirt-guest-agent/myfile.sh";
 char log_file[1024] = "/var/log/ovirt-guest-agent/ovirt-guest-agent.log";
 char cmd[1024];
 char password_file[1024] = "/usr/share/ovirt-guest-agent/password.txt";
 gid_t srcc_gid;
 uid_t srcc_uid;
 int gg,uu;
 int count;
 FILE *fp_password = NULL;
 FILE *fp = NULL;
 int i=0;
/*
 for(count=0;count<argc;count++)
	printf("%d,%s\n",count,argv[count]);
*/
 if(argc != 2)
 {
	printf("input should have only 1 parameter\n");
	printf("usage: ./set_admin_password admin_pass\n");
	printf("fg:./set_admin_password 123456\n");
	exit(-1);	
 }
 //create password file
 fp_password = fopen(password_file,"w+");
 fprintf(fp_password,"root:%s",argv[1]);
 fclose(fp_password);
 //create cmd
 sprintf(cmd,"chpasswd < %s",password_file);
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
	fprintf(fp,"set_admin_password, cmd = %s\n",cmd);
 	fprintf(fp,"password = %s\n",argv[1]);
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
	fprintf(fp,"set_admin_password ret = %d\n",gg);
 	fclose(fp);
 }
 //remove password file
 remove(password_file);
 return gg;
}
