#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include<sys/stat.h>
#include<dirent.h>
#include<regex.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<openssl/md5.h>
#include<time.h>

char choice[1025];
int parseInput(char ar[1025],int len);
char* hashedVal(char name[1025]);
void print_hash(char ar[1025]);
void printTime(time_t time);
time_t convert_tm_to_time_t(int year,int month,int day,int hour,int min);
char fname[1025];

typedef struct fileInfo{
	char name[1025];
	off_t size;
	time_t time;
	mode_t mode;
	char filehash[1025];
	int valid;
}fileInfo;

fileInfo fi,servFiles[1000];
int fi_len,len=0;

int calcFileSz(FILE *fp)
{
	int c,fsize=0;
	while ((c = getc(fp)) != EOF) {fsize++;}
	return fsize;
}


void getInput()
{
	char ch;int x=0;
	scanf("%c",&ch);
	while(ch != '\n' && ch!='\r')
	{
		choice[x++] = ch;
		scanf("%c",&ch);
	}
	choice[x] = '\0';
}

void disp(fileInfo fp);
int main(int argc, char *argv[])
{
	int sockfd = 0, n = 0,val;
	char recvBuff[1025],sendBuff[1025];
	struct sockaddr_in serv_addr; 

/*	if(argc != 2)
	{
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return 1;
	} */

	memset(recvBuff, '0',sizeof(recvBuff));
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Error : Could not create socket \n");
		return 1;
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000); 
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	/*	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
		{
		printf("\n inet_pton error occured\n");
		return 1;
		} */

	if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		return 1;
	} 

	int loop = 0;
	while(1)
	{
		bzero(choice,sizeof(choice));
		getInput();
		val = parseInput(choice,strlen(choice));
//		printf("length is %d sizeof is %d\n",strlen(choice),sizeof(choice));
//		printf("val is %d\n",val);
		write(sockfd,choice,sizeof(choice)-1);
		if(val == 1)
		{
			FILE *fp = fopen(fname,"w");
			int num,extra;
			bzero(recvBuff,sizeof(recvBuff)-1);
			n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
//			printf("Feed back %s",recvBuff);
			if(strcmp(recvBuff,"exit") == 0)
			{
				printf("Error opening File\n");
				fclose(fp);
				continue;
			}
//			printf("Msg  %s\n",recvBuff);
			n = read(sockfd,(char *)&num,sizeof(num));
			n = read(sockfd,(char *)&extra,sizeof(extra));

			read(sockfd,(char*)&servFiles[len],sizeof(fileInfo));

			printf("-------Starting Download-------\n");
			sleep(1);
			disp(servFiles[len++]);
			while(num--)
			{
				bzero(recvBuff,sizeof(recvBuff)-1);
				n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
				fwrite(recvBuff,sizeof(char),sizeof(recvBuff)-1,fp);
				recvBuff[n] = '\0';
				if(n<=0)
					break;
				//printf("%s",recvBuff);
			}
			if(extra)
			{
				bzero(recvBuff,sizeof(recvBuff)-1);
				n = read(sockfd, recvBuff, extra);
				fwrite(recvBuff,sizeof(char),extra,fp);
				if(n<=0)
					break;
				//printf("%s",recvBuff);
			}
			fclose(fp);
			printf("-------Finished Download-------\n");
			if(n < 0)
			{
				printf("\n Read error \n");
			}
		}
		else if (val == 2)
		{
			read(sockfd,(char*)&fi_len,sizeof(fi_len));
			int x;
			for(x=0;x<fi_len;x++)
			{
				read(sockfd,(char*)&fi,sizeof(fileInfo));
				disp(fi);
				printTime(fi.time);
			}
		}
		else if (val == 4)
		{
			read(sockfd,(char*)&fi_len,sizeof(fi_len));
			int x;
			for(x=0;x<fi_len;x++)
			{
				read(sockfd,(char*)&fi,sizeof(fileInfo));
				disp(fi);
				printTime(fi.time);
			}
		}
		else if(val == 3)
		{
			int year1,month1,day1,hour1,min1;
			int year2,month2,day2,hour2,min2;
			printf("Enter Lower year\n");
			scanf("%d",&year1);
			printf("Enter Lower month(in number)\n");
			scanf("%d",&month1);
			printf("Enter lower day(in number)\n");
			scanf("%d",&day1);
			printf("Enter lower hour\n");
			scanf("%d",&hour1);
			printf("Enter lower min\n");
			scanf("%d",&min1);
			printf("Enter higher year\n");
			scanf("%d",&year2);
			printf("Enter higher month(in number)\n");
			scanf("%d",&month2);
			printf("Enter higher day( in number)\n");
			scanf("%d",&day2);
			printf("Enter higher hour\n");
			scanf("%d",&hour2);
			printf("Enter higher min\n");
			scanf("%d",&min2);
			int x;
			time_t lo,hi;
			lo = convert_tm_to_time_t(year1,month1,day1,hour1,min1);
			hi = convert_tm_to_time_t(year2,month2,day2,hour2,min2);
			write(sockfd,(char*)&lo,sizeof(time_t));
			write(sockfd,(char*)&hi,sizeof(time_t));

			read(sockfd,(char*)&fi_len,sizeof(fi_len));
			for(x=0;x<fi_len;x++)
			{
				read(sockfd,(char*)&fi,sizeof(fileInfo));
				disp(fi);
				printTime(fi.time);
			}
		}
		else if(val == 5)
		{
			printf("fname %s--\n",fname);
			int res;
			printf("Waiting for server to Accept request\n");
			read(sockfd,(char*)&res,sizeof(res));
			if(res == 0)
			{
				printf("Request Refused Upload Cancelled\n");
				continue;
			}
			FILE *fp = fopen(fname,"r");
			bzero(sendBuff,sizeof(sendBuff));
			if(fp == NULL)
			{
				strcpy(sendBuff,"exit");
				write(sockfd,sendBuff,sizeof(sendBuff)-1);
				printf("Error opening file\n");
				continue;
			}
			else
			{
				strcpy(sendBuff,"ok");
				write(sockfd,sendBuff,sizeof(sendBuff)-1);
			}
			printf("---------File Upload in progress----------------\n");
			sleep(1);
			int totalSz = calcFileSz(fp);
			int chunks = totalSz / ( sizeof(sendBuff)-1) ;
			int empty = totalSz % ( sizeof(sendBuff)-1);
			int tmp1 = chunks;//htons(chunks);
			int tmp2 = empty;//htons(empty);
			//			tmp2 = 3;
			write(sockfd,(char*)&tmp1,sizeof(int));
			write(sockfd,(char*)&tmp2,sizeof(int));
			fclose(fp);

			fileInfo info;
			strcpy(info.name,fname);info.valid = 1;
			char dirName[1000];
			getcwd(dirName,sizeof(dirName));
			struct stat inode;char name[1025];
			sprintf(name,"%s/%s",dirName,fname);
			lstat (name, &inode);
			info.mode = inode.st_mode;
			info.size = inode.st_size;
			info.time = inode.st_mtime;
			strcpy(info.filehash,hashedVal(fname));
			write(sockfd,(char*)&info,sizeof(fileInfo));


			fp = fopen(fname,"r");
			while(chunks --)
			{
				bzero(sendBuff,sizeof(sendBuff)-1);
				fread(sendBuff,sizeof(char),sizeof(sendBuff)-1,fp);
				write(sockfd,sendBuff,sizeof(sendBuff)-1);
			}
			if(empty)
			{
				bzero(sendBuff,sizeof(sendBuff)-1);
				fread(sendBuff,sizeof(char),empty,fp);
				write(sockfd,sendBuff,empty);
			}
			fclose(fp);
			printf("---------File Uploaded-----------\n");
		}
		else if(val == 6)
			break;
		else if(val == 7)
		{
			time_t tm;char name[1000],val[1025];
			bzero(sendBuff,sizeof(sendBuff));
			strcpy(sendBuff,fname);
			write(sockfd,sendBuff,sizeof(sendBuff)-1);
			bzero(recvBuff,sizeof(recvBuff));
			read(sockfd,recvBuff,sizeof(recvBuff));
			strcpy(val,recvBuff);
			bzero(recvBuff,sizeof(recvBuff));
			read(sockfd,recvBuff,sizeof(recvBuff));
			strcpy(name,recvBuff);
			read(sockfd,(char*)&tm,sizeof(time_t));
			if(strlen(recvBuff))
			{
				printf("%s   ",name);
				print_hash(val);
			}
			else
				printf("Invalid File\n");
		}
		else if(val == 8)
		{
			write(sockfd,(char*)&len,sizeof(int));
			int x;
			time_t tm;char name[1000],val[1025];
			for(x=0;x<len;x++)
			{
				bzero(sendBuff,sizeof(sendBuff));
				strcpy(sendBuff,servFiles[x].name);
				write(sockfd,sendBuff,sizeof(sendBuff)-1);
				bzero(recvBuff,sizeof(recvBuff));
				read(sockfd,recvBuff,sizeof(recvBuff));
				strcpy(val,recvBuff);
				bzero(recvBuff,sizeof(recvBuff));
				read(sockfd,recvBuff,sizeof(recvBuff));
				strcpy(name,recvBuff);
				read(sockfd,(char*)&tm,sizeof(time_t));
				if(strlen(val))
				{
					printf("%s   ",name);
					print_hash(val);
				}
			}
		}
		else if(val == -1)
		{
			read(sockfd,recvBuff,sizeof(recvBuff)-1);
			printf("%s\n",recvBuff);
		}
	}
	close(sockfd);
	return 0;
}

void printTime(time_t time)
{
	struct tm *foo = gmtime(&(time));
	printf("Year: %d ", foo->tm_year+1900);
	printf("Month: %d ", foo->tm_mon+1);
	printf("Day: %d ", foo->tm_mday);
	printf("Hour: %d ", foo->tm_hour);
	printf("Minute: %d \n\n", foo->tm_min);
}

void print_hash(char ar[1025])
{
	int st = 0;
	while(ar[st]!='\0')
		printf("%02x",ar[st++]);
	printf("\n");
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


void disp(fileInfo f)
{
	printf("%s  ",f.name);
	printf("%lld ",f.size);
	//                      printf("%node.st_mtime;
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

time_t convert_tm_to_time_t(int year,int month,int day,int hour,int min)
{
	time_t rawtime;
	time( &rawtime );
	struct tm *foo;
	foo=localtime(&rawtime);
	foo->tm_year=year-1900;
	foo->tm_mon=month-1;
	foo->tm_mday=day;
	foo->tm_hour=hour;
	foo->tm_min=min;
	time_t ans_time=mktime(foo);
	return ans_time;
}

int parseInput(char ar[1025],int len)
{
	int x,st;
//	printf("inp %s--\n",ar);
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
