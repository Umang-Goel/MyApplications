#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
//#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include<sys/stat.h>
#include<dirent.h>
#include<regex>
#include<string>
#include<fcntl.h>
#include<cstdlib>
#include<sys/mman.h>
#include<openssl/md5.h>
#define FileUploadDeny 0
#define FileUploadAllow 1

using namespace std;

typedef struct fileInfo{
	char name[1025];
	off_t size;
	time_t time;
	mode_t mode;
	char filehash[1025];
	int valid;
}fileInfo;

char fname[1024];

int parseInput(char ar[1025],int len);
void listdir(char ar[1025]);
void validateExpr(char ar[1025]);//,regex match);
int isValidTime(time_t t,time_t lo,time_t hi);
void disp(fileInfo f);
char* hashedVal(char name[1024]);
fileInfo fi[1000];
int fi_len = 0;

int calcFileSz(FILE *fp)
{
	int c,fsize=0;
	while ((c = getc(fp)) != EOF) {fsize++;}
	return fsize;
}

int main(int argc, char *argv[])
{
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr; 

	char sendBuff[1025],inp[1025],recvBuff[1025];
	time_t ticks; 

	int val;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000); 

	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

	listen(listenfd, 10); 

	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

	int n;
	while(1)
	{
		bzero(inp,sizeof(inp));
		n = read(connfd,inp,1024);
//		printf("read  %s--\nn = %d\n",inp,n);
		val = parseInput(inp,n);
		//		val =5;
//		cout<<"val  "<<val<<endl;
		if(val == 1)
		{
//			printf("correct\n");
			FILE *fp = fopen(fname , "r");
			if(fp == NULL)
			{
				bzero(sendBuff,sizeof(sendBuff));
				strcpy(sendBuff,"exit");
				write(connfd,sendBuff,sizeof(sendBuff)-1);
				continue;
			}
			else
			{
				bzero(sendBuff,sizeof(sendBuff));
				strcpy(sendBuff,"ok");
				write(connfd,sendBuff,sizeof(sendBuff)-1);
			}
			int totalSz = calcFileSz(fp);
			int noChunks = totalSz / (sizeof(sendBuff)-1);
			int extra = totalSz % (sizeof(sendBuff)-1);
			int tmp1 = noChunks;//htons(noChunks);
			int tmp2 = extra;//htons(extra);
			write(connfd,(char *)&tmp1,sizeof(tmp1));
			write(connfd,(char *)&tmp2,sizeof(tmp2));
			fclose(fp);

			fileInfo info;char dirName[1000];
			strcpy(info.name,fname);info.valid = 1;
			getcwd(dirName,sizeof(dirName));
			struct stat inode;char name[1025];
			sprintf(name,"%s/%s",dirName,fname);
			lstat (name, &inode);
			info.mode = inode.st_mode;
			info.size = inode.st_size;
			info.time = inode.st_mtime;
			strcpy(info.filehash,hashedVal(fname));
			write(connfd,(char*)&info,sizeof(fileInfo));

//			printf("noChunks %d extra %d\n",noChunks,extra);
			fp = fopen(fname , "r");
			//sending File
			while(noChunks)
			{
				bzero(sendBuff,sizeof(sendBuff));
				fread(sendBuff,sizeof(char),sizeof(sendBuff)-1,fp);
				write(connfd, sendBuff, sizeof(sendBuff)-1);
				noChunks --;
			}
			if(extra)
			{
				bzero(sendBuff,sizeof(sendBuff));
				fread(sendBuff,sizeof(char),extra,fp);
				write(connfd, sendBuff, extra);
			}
			fclose(fp);
			sleep(1);
		}
		else if(val == 2)
		{
			listdir(inp);
//			printf("in here\n");
			int x;
			write(connfd,(char*)&fi_len,sizeof(int));
			for(x=0;x<fi_len;x++)
				write(connfd,(char*)&fi[x],sizeof(fileInfo));
		}
		else if(val == 4)
		{
			int x,tmp;
			listdir(inp);
			validateExpr(inp);
			for(x=0;x<fi_len;x++)
			{
				if(fi[x].valid)
					tmp ++;
			}
			write(connfd,(char*)&tmp,sizeof(int));
			for(x=0;x<fi_len;x++)
			{
				if(fi[x].valid)
					write(connfd,(char*)&fi[x],sizeof(fileInfo));
			}
		}
		else if(val == 3)
		{
			int x,tmp=0;
			time_t lo,hi;
			read(connfd,(char*)&lo,sizeof(time_t));
			read(connfd,(char*)&hi,sizeof(time_t));
			listdir(inp);
			for(x=0;x<fi_len;x++)
				fi[x].valid = isValidTime(fi[x].time,lo,hi);
			for(x=0;x<fi_len;x++)
			{
				if(fi[x].valid)
					tmp ++;
			}
			write(connfd,(char*)&tmp,sizeof(int));
			for(x=0;x<fi_len;x++)
			{
				if(fi[x].valid)
					write(connfd,(char*)&fi[x],sizeof(fileInfo));
			}	
		}
		else if(val == 5)	//FileUpload
		{
			int ch;
			int chunks,extra,err_var;
			printf("Request For Upload.....Allow ??\nPress 1 to Allow\nPress 0 to Reject\n");
			scanf("%d",&ch);
			write(connfd,(char*)&ch,sizeof(int));
			if(ch == FileUploadDeny)
				continue;
			bzero(recvBuff,sizeof(recvBuff));
			read(connfd,recvBuff,sizeof(recvBuff)-1);
			if(strcmp(recvBuff,"exit") == 0)
				continue;
			read(connfd,(char*)&chunks,sizeof(int));
			read(connfd,(char*)&extra,sizeof(int));
			//			chunks = ntohs(chunks);
			//			extra = ntohs(extra);
			fileInfo tmp;
			read(connfd,(char*)&tmp,sizeof(fileInfo));
			disp(tmp);

			FILE *fp = fopen(fname,"w");
//			cout << " chunks "<<chunks<< " extra "<<extra<<endl;
			while(chunks--)
			{
				bzero(recvBuff,sizeof(recvBuff));
				read(connfd,recvBuff,sizeof(recvBuff)-1);
				fwrite(recvBuff,sizeof(char),sizeof(recvBuff)-1,fp);
			}
			if(extra)
			{
				bzero(recvBuff,sizeof(recvBuff));
				read(connfd,recvBuff,extra);
				fwrite(recvBuff,sizeof(char),extra,fp);
			}
			fclose(fp);
		}
		if(val == 6)
			break;
		if(val == 7)
		{
			bzero(recvBuff,sizeof(recvBuff));
			read(connfd,recvBuff,sizeof(recvBuff)-1);
			char hash[1025] ,name[1025];
			strcpy(name,recvBuff);
			strcpy(hash,hashedVal(name));
			bzero(sendBuff,sizeof(sendBuff));
			strcpy(sendBuff,hash);
			write(connfd,sendBuff,sizeof(sendBuff));

			char dirName[1000];
			getcwd(dirName,sizeof(dirName));
			struct stat inode;
			bzero(name,sizeof(name));
			sprintf(name,"%s/%s",dirName,fname);
			lstat (name, &inode);
			time_t time = inode.st_mtime;
			bzero(sendBuff,sizeof(sendBuff));
			strcpy(sendBuff,fname);
			write(connfd,sendBuff,sizeof(sendBuff));
			write(connfd,(char*)&time,sizeof(time_t));
		}
		if( val == 8)
		{
			int sz;
			read(connfd,(char*)&sz,sizeof(int));
//			cout<<"sz is "<<sz<<endl;
			while(sz--)
			{
				bzero(recvBuff,sizeof(recvBuff));
				read(connfd,recvBuff,sizeof(recvBuff)-1);
				char hash[1025] ,name[1025];
				strcpy(name,recvBuff);
				strcpy(hash,hashedVal(name));
				bzero(sendBuff,sizeof(sendBuff));
				strcpy(sendBuff,hash);
				write(connfd,sendBuff,sizeof(sendBuff));

				char dirName[1000],name1[1000];
				getcwd(dirName,sizeof(dirName));
				struct stat inode;
				bzero(name1,sizeof(name1));
				sprintf(name1,"%s/%s",dirName,name);
				lstat (name1, &inode);
				time_t time = inode.st_mtime;
				bzero(sendBuff,sizeof(sendBuff));
				strcpy(sendBuff,name);
				write(connfd,sendBuff,sizeof(sendBuff));
				write(connfd,(char*)&time,sizeof(time_t));
			}
		}
		else if (val == -1)
		{
			bzero(sendBuff,sizeof(sendBuff));
			strcpy(sendBuff,"No such Command");
			write(connfd,sendBuff,sizeof(sendBuff)-1);
		}
	}
//	printf("client bye\n");
	close(connfd);
}

int isValidTime(time_t time,time_t low,time_t high)
{
//	printf("time %d low %d high %d\n",time,low,high);
	if(time >=low && time<=high)
		return 1;
	return 0;
}

void validateExpr(char inp[1025])
{
	string tmp=inp;
	string pattern=tmp.substr(15,100);//abs(int(sizeof(msg)-18)));	
	//string pattern="mp3";	
	pattern=pattern.substr(1,pattern.size()-2);
	//	pattern=pattern.substr(1,100);
	regex match(pattern);
	for(int x=0;x<fi_len;x++)
	{		
		//		fi[x].name[strlen(fi[x].name)] = '\0';
		string nm=fi[x].name;
		if (regex_match(nm,match))
		{
			//	cout<<nm<<"\n";
		}
		else
			fi[x].valid = 0;
	}
}

int isvalidTime(char ar[1025],time_t t)
{
	return 1;
}

void disp(fileInfo f)
{
	printf("%s  ",f.name);
	printf("%lld ",f.size);
	//			printf("%node.st_mtime;
	printf( (S_ISDIR(f.mode)) ? "d" : "-");
	printf( (f.mode & S_IRUSR) ? "r" : "-");
	printf( (f.mode & S_IWUSR) ? "w" : "-");
	printf( (f.mode & S_IXUSR) ? "x" : "-");
	printf( (f.mode & S_IRGRP) ? "r" : "-");
	printf( (f.mode & S_IWGRP) ? "w" : "-");
	printf( (f.mode & S_IXGRP) ? "x" : "-");
	printf( (f.mode & S_IROTH) ? "r" : "-");
	printf( (f.mode & S_IWOTH) ? "w" : "-");
	printf( (f.mode & S_IXOTH) ? "x\n" : "-\n");

}

void listdir(char ar[1025])
{
	char dirName[1024];
	getcwd(dirName,sizeof(dirName));
//	printf("current dir %s\n",dirName);
	DIR* dir;
	struct dirent *dirEntry;
	struct stat inode;
	char name[1000];
	dir = opendir(dirName);
	if (dir == 0) 
	{
		printf("Error fetching list\n");
		return;
	}
	fi_len = 0;
	while ((dirEntry=readdir(dir)) != 0) 
	{
		sprintf(name,"%s/%s",dirName,dirEntry->d_name); 
		lstat (name, &inode);
		if(strcmp(dirEntry->d_name,".")==0 || strcmp(dirEntry->d_name,"..")==0)
			continue;
		else
		{
			strcpy(fi[fi_len].name,dirEntry->d_name);
			fi[fi_len].mode = inode.st_mode;
			fi[fi_len].size = inode.st_size;
			fi[fi_len].time = inode.st_mtime;
			fi[fi_len++].valid = 1;
		}
	}
}

unsigned long get_size_by_fd(int fd) {
	struct stat statbuf;
	if(fstat(fd, &statbuf) < 0) exit(-1);
	return statbuf.st_size;
}

char* hashedVal(char fname[1025])
{
	int file_descript;
	unsigned long file_size;
	char* file_buffer;
	unsigned char *result=(unsigned char *)malloc(sizeof(char)*(MD5_DIGEST_LENGTH+1));	
	file_descript = open(fname, O_RDONLY);
	if(file_descript < 0) 
	{
		return "\0";
	}
	file_size = get_size_by_fd(file_descript);
	file_buffer =(char* )mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0);
	MD5((unsigned char*) file_buffer, file_size, result);
	result[MD5_DIGEST_LENGTH]='\0';
	munmap(file_buffer,file_size);
	return (char*)result;
}

int parseInput(char ar[1025],int len)
{
	int x,st;
	bzero(fname,sizeof(fname));
	if(len>0 && ar[0] == 'F' && ar[4]=='D')
	{
		st = 0;
		for(x=13;x<len;x++)
		{
			fname[st++] = ar[x];
		}
		return 1;
	}
	if(len>0 && ar[0] == 'I' && ar[9] == 'L')
	{
		return 2;
	}
	if(len>0 && ar[0] == 'I' && ar[9] == 'S')
	{
		return 3;
	}
	if(len>0 && ar[0] == 'I' && ar[9] == 'R')
	{
		return 4;
	}
	if(len>0 && ar[0] == 'F' && ar[4]=='U')
	{
		st = 0;
		bzero(fname,sizeof(fname));
		for(x=11;x<len;x++)
		{
			fname[st++] = ar[x];
		}
		return 5;
	}
	if(len>0 && ar[0] == 'F' && ar[4]=='H' && ar[9]=='V')
	{
		st=0;
		bzero(fname,sizeof(fname));
		for(x=16;x<len;x++)
		{
			fname[st++]= ar[x];
		}
		return 7;
	}
	if(len>0 && ar[0]== 'F' && ar[4] == 'H' && ar[9] == 'C')
		return 8;
	if(strcmp(ar,"exit") == 0)
		return 6;
	return -1;
}
