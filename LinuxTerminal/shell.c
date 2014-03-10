#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/utsname.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/prctl.h>

struct utsname sys_info;
char g_pwd[50],p_pwd[50],inp[500];
char user_name[50];
char *args[500];
int background,sig_fl;
int terminal_id;

typedef struct list
{
	int id;
	char ar[50];
	struct list *next;
}queue;
queue *head;

void initialise_shell()
{

	terminal_id=STDERR_FILENO;
	int  shell_is_interactive=isatty(terminal_id);
	int shell_pgid;
	if(shell_is_interactive)
	{
		while(tcgetpgrp(terminal_id)!=(shell_pgid=getpgrp()))
			kill(- shell_pgid, SIGTTIN);

		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU,SIG_IGN);
		//signal (SIGCHLD, SIG_IGN);

		shell_pgid=getpid();
		if (setpgid(shell_pgid,shell_pgid) < 0)
		{
			perror("Couldn't put the shell in its own process group");
			exit(1);
		}

		tcsetpgrp(terminal_id,shell_pgid);
	}
}

void prompt()
{
	char host_name[100];
	getlogin_r(user_name,sizeof(user_name));
	gethostname(host_name,sizeof(host_name));
	uname(&sys_info);
	//	user_name=getenv("USER");
	if(strcmp(g_pwd,p_pwd)==0)	//check if pwd==home then show '~'
		fprintf(stderr,"<%s@%s:~>",user_name,host_name);
	else
		fprintf(stderr,"<%s@%s:%s>",user_name,host_name,p_pwd);
}

void push(int proc_id)		//push a running process in queue
{
	queue *tmp=head;
	//	printf("in push inp is %s\n",inp);
	if(head==NULL)
	{
		head=(queue *)malloc(sizeof(queue));
		head->id=proc_id;
		strcpy(head->ar,inp);
		//		printf("head->ar is %s",head->ar);
		head->next=NULL;
		return;
	}
	while(tmp->next!=NULL)
		tmp=tmp->next;
	tmp->next=(queue *)malloc(sizeof(queue));
	tmp->next->id=proc_id;
	strcpy(tmp->next->ar,inp);
	tmp->next->next=NULL;
}

char * delete(int proc_id)	//removing a process from process queue
{
	char name[100];
	if(head==NULL)
		return "\0";
	if(proc_id==head->id)
	{
		strcpy(name,head->ar);
		queue *tmp=head;
		head=head->next;
		free(tmp);
		return name;
	}
	queue *tmp=head;
	int ct=1;
	while(tmp->next!=NULL)  
	{
		if(tmp->next->id==proc_id)
		{
			queue *a=tmp->next;
			strcpy(name,a->ar);
			tmp->next=tmp->next->next;
			free(a);
			return name;
		}
		tmp=tmp->next;
		ct++;
	}
	return "\0";
}

void jobs()	//displays all background
{
	queue *tmp=head;
	int ct=1;
	while(tmp!=NULL)
	{
		printf("[%d] %s [%d]\n",ct++,tmp->ar,tmp->id);
		tmp=tmp->next;
	}
}

void make_argument()	//splits the input with space as delimitor
{
	int ct=0,x;
	const char s[2]=" ";
	args[ct]=strtok(inp,s);
	while(args[ct]!=NULL)
	{
		args[++ct]=strtok(NULL,s);
	}
	background=0;
	if(strcmp(args[ct-1],"&")==0)	//if '&' at the end of input then set background flag as 1
	{
		background=1;
		args[ct-1]=NULL;
	}
	return ;
}

int get_pid(int pno)	//gets pid from queue's index no.
{
	int ct=1;
	queue *tmp=head;
	while(tmp!=NULL && ct!=atoi(args[1]))
	{
		tmp=tmp->next;
		ct++;
	}
	if(tmp==NULL)	//if no such index then return -1
		return -1;
	else
		return tmp->id;
}

void kjob()
{
	if(args[1]==NULL || args[2]==NULL)	//check if proper no of arguments are given
		printf("More arguments required\n");
	else
	{
		int p_id=get_pid(atoi(args[1]));
		if(p_id==-1)	//if no such process exist in process queue then print message
			printf("No such process\n");
		else	//else operate
			kill(p_id,atoi(args[2]));
	}
}

void make_process()
{
	int x,ct;
	pid_t pid;
	pid=fork();
	if(pid<0)	//if fork not succesful
	{
		perror("Error");
		return;
	}
	else if(pid==0)
	{
		prctl(PR_SET_PDEATHSIG, SIGHUP);	//kill all child process when quit
		setpgid(getpid(),getpid());	//changing group id of every child process
		if(background==0)	//if child is a foreground process then give it the terminal
			tcsetpgrp(terminal_id,getpid());		
		//making signals default for the child
		signal(SIGINT, SIG_DFL);	
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGSTOP,SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);

		if((execvp(args[0],args))<0)
		{
			perror("ERROR");	//if not able to exec 
			_exit(-1);
		}
		_exit(0);
	}
	else
	{
		push(pid);	//push the new process into process queue
		if(background==0)
		{
			tcsetpgrp(terminal_id,pid);		//if child is foreground process give it terminal
			//written again to handle race condition
			waitpid(pid,&x,WUNTRACED);	//wait until stopped or exited
			if(WIFSTOPPED(x));	//if stopped do nothing
			else
			{
				delete(pid);	//if exited then remove from running queue
			}
			tcsetpgrp(terminal_id,getpid());	//again give back terminal to main process
		}
	}
}



void pinfo(int proc_id)
{
	int p_id;
	unsigned long int mem;
	//	long long int mem;
	char tmp1[300],tmp2[300],exe[300],path[300],status,*ref;
	FILE *fp1;
	if(args[1]==NULL)	//check if no argument then give info about parent process
	{
		sprintf(tmp1,"/proc/%d/stat",proc_id);	//stat used to get info about pid,status and memory
		sprintf(tmp2,"/proc/%d/exe",proc_id);	// for path of executable
	}
	else	//if argument there then info about mentioned process
	{
		sprintf(tmp1,"/proc/%d/stat",get_pid(atoi(args[1])));
		sprintf(tmp2,"/proc/%d/exe",get_pid(atoi(args[1])));
	}
	fp1=fopen(tmp1,"r");
	if(fp1==NULL)
	{
		fprintf(stderr,"Error executing command\n");
		return;
	}
	fscanf(fp1,"%d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %*d %*d %*d %*d %*d %*d %*u %lu %*d %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*d %*d %*u %*u %*u %*u %*d",&p_id,&status,&mem);
	int len=readlink(tmp2,exe,sizeof(exe));
	exe[len]='\0';
	if(strstr(exe,g_pwd)!=NULL)	//processing relative path of the executable
	{
		strcpy(path,"~");
		ref=&exe[0];
		ref+=strlen(g_pwd);
		strcat(path,ref);
	}
	else
		strcpy(path,exe);
	fprintf(stderr,"pid -- %d\nProcess Status -- %c\nmemory -- %lu\nExecutable Path -- %s\n",p_id,status,mem,path);
}

void sig_handler(int signo)
{
	if (signo == SIGKILL)
		;
	else if (signo == SIGINT)
		;
	else if(signo==SIGCHLD)
	{
		int status;
		int p_id=waitpid(-1,&status,WNOHANG);	//check for all child processes
		if(p_id!=-1 && p_id!=0)		//show message only when child is exited
		{
			char *name;
			fprintf(stderr,"\nProcess %s with pid %d ",delete(p_id),p_id);	
			if(WIFEXITED(status))	//if exited then show exited normally
			{
				fprintf(stderr,"exited normally\n");
			}
			if(WIFSIGNALED(status))		//else show it was killed
			{
				fprintf(stderr,"was killed\n");
			}
			prompt();	//display prompt
		}
	}
}

void check_signal()	//checks all signals for main program
{
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGUSR1\n");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGSTOP\n");
	if (signal(SIGCHLD, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGCHLD\n");
}

void over_kill()	//kills all running processes in queue
{
	while(head!=NULL)
	{
		kill(head->id,SIGKILL);
	}
}

void clear_all()	//clears input and arguments
{
	int x=0;
	while(args[x]!=NULL)	//clearing arguments by making it null
		args[x++]=NULL;
	inp[0]='\0';	//clears input
}

void fg()	//toggle process from background to foreground
{
	if(args[1]==NULL)	//check if proper no of arguments are given or not
	{
		fprintf(stderr,"More arguments required\n");
		return;
	}
	int p_id=get_pid(atoi(args[1]));	//get pid from index no.
	int x;
	if(p_id==-1)
	{
		fprintf(stderr,"No such background process no\n");
		return;
	}
	kill(p_id,SIGCONT);	
	tcsetpgrp(terminal_id,p_id);		//gives terminal back to the child process to make it foreground
	waitpid(p_id,&x,WUNTRACED);	//wait until stopped or exited
	if(WIFSTOPPED(x));
	else
	{
		delete(p_id);	//if exited delete from running process's queue
	}
	tcsetpgrp(terminal_id,getpid());	//again give back control to main process

}

void cd()
{
	char path[40],*ref,tmp[60];
	path[0]='\0';
	if(args[1]!=NULL)
	{
		strcpy(tmp,args[1]);
		if(args[1][0]=='~')
		{
			strcpy(tmp,g_pwd);
			strcat(tmp,args[1]+1);
		}
		realpath(tmp,path);
	}
	else	//change PWD to HOME if no path given
	{
		strcpy(p_pwd,g_pwd);
		chdir(g_pwd);
		return;
	}
	int fl=chdir(path);
	if(fl==-1)	//print Error message if no such path exist
	{
//		prompt();
		printf("No such Directory \"%s\"\n",path);
	}
	else	//for changing pwd accordingly
	{
		ref=strstr(path,g_pwd);
		if(ref==NULL)			//if the absolute path doesnt contain HOME path then completly change 
			strcpy(p_pwd,path);
		else if(strcmp(path,g_pwd)==0)
			strcpy(p_pwd,g_pwd);
		else		//else concatenate the rest of the path to '~'
		{
			strcpy(p_pwd,"~");
			ref=&path[0];
			ref+=strlen(g_pwd);
			strcat(p_pwd,ref);
		}
	}
}
int main()	//main process
{
	int fl,pos;
	char ch;
	getcwd(g_pwd,sizeof(g_pwd));	//store HOME path in g_pwd
	getcwd(p_pwd,sizeof(p_pwd));	//stores PWD path in p_pwd
	terminal_id=getpid();	//get pid of the main process
	initialise_shell();
	while(1)
	{
		check_signal();		//check for signal
		prompt();
		scanf("%[^\n]s",inp);
		scanf("%c",&ch);
		while(inp[0]=='\0')	//scan input until it is '\n'
		{
			prompt();
			scanf("%[^\n]s",inp);
			scanf("%c",&ch);
		}
		background=0;	//initialize background variable
		make_argument();	//split input to create arguments
		if(strcmp(args[0],"quit")==0)
			break;
		if(strstr(args[0],"cd")!=NULL)
			cd();
		else if(strcmp(args[0],"jobs")==0)
			jobs();
		else if(strstr(args[0],"pinfo")!=NULL)
			pinfo(getpid());
		else if(strstr(args[0],"kjob")!=NULL)
			kjob();
		else if(strcmp(args[0],"overkill")==0)
			over_kill();
		else if(strcmp(args[0],"fg")==0)
			fg();
		else
			make_process();
		clear_all();
	}
	return 0;
}
