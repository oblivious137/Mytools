/*
**1. lock.exe file
**2. lock.exe file aimdir
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sys/stat.h>
#include <bits/basic_string.h>
using namespace std;
const int maxn=1000000;
const char lock[10]=".lock";
char tmp[maxn],name[1000],use[1000];

inline const char* get(const char* x){
	int l=strlen(x);
	strcpy(use,x);
	for (int i=l-1;i>=0;i--) if (use[i]=='.'){
		if (strcmp(use+i,lock)==0){
			use[i]='\0';
			return use;
		}
		else break;
	}
	else if (use[i]=='\\') break;
	sprintf(use+l,"%s",lock);
	return use;
}

inline unsigned long long get_size(const char *fr){
	struct _stati64 info;
	_stati64(fr, &info);
	return info.st_size;
}

char lo[100];
inline void solve(const char *fr,const char *aim){
	clog<<"solve "<<fr<<endl;
	FILE* in=fopen(fr,"rb"),*out=fopen(aim,"wb");
	unsigned long long al=get_size(fr),now=0;  
	int len;
	clog<<"size="<<al<<endl;
	while(len=fread(tmp,1,maxn,in)){
		sprintf(lo,"\r%03lld%%",now*100/al);
		clog<<lo;
		if (len>maxn) break;
		for (int i=0;i<len;i+=3) tmp[i]=~tmp[i];
		fwrite(tmp,1,len,out);
		now+=len;
	}
	fclose(in);
	fclose(out);
	return;
}

inline void pre(char *x){
	int len=strlen(x);
	for (int i=len-1;i>=0;i--) if (x[i]=='\\'){
		int j=0;
		i++;
		for (;i<=len;i++) x[j++]=x[i];
		break;
	}
	return;
}

char qaq[1000],tat[1000];

int main(int argc,char*argv[]){
	if (argc==1)
		while(scanf("%s",name)==1) solve(name,get(name));
	else if (argc==2){
		solve(argv[1],get(argv[1]));
	}
	else if (argc==3){
		strcpy(qaq,argv[1]);
		pre(qaq);
		strcpy(tat,argv[2]);
		strcat(tat,"\\");
		strcat(tat,qaq);
		solve(argv[1],get(tat));
	}
	else cerr<<"Input parameter is wrong...";
	return 0;
}
