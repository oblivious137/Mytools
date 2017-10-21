/*
**1. lockdir.exe dir
**2. lockdir.exe dir aimdir
*/
#include <cstdlib>
#include <direct.h>
#include <string>
#include <cstring>
#include <io.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#include <conio.h>
#include <process.h>
#include <windows.h>
using namespace std;

inline unsigned long long get_size(const char *fr){
	struct _stati64 info;
	_stati64(fr, &info);
	return info.st_size;
}

namespace LOCK{
	const int maxn=1000000;
	const char lock[10]=".lock";
	char tmp[maxn],name[1000],use[1000],lo[100];
	inline string get(string x){
		int t=x.rfind(lock);
		if (t==-1) return x+lock;
		else return x.substr(0,t);
	}
	inline void solve(string &fr,string aim){
		clog<<"solve "<<fr<<endl;
		FILE* in=fopen(fr.c_str(),"rb"),*out=fopen(aim.c_str(),"wb");
		unsigned long long al=get_size(fr.c_str()),now=0;  
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
		clog<<"\r100%"<<endl;
		fclose(in);
		fclose(out);
		return;
	}
	inline string get_name(string &x){return x.substr(x.rfind('\\')+1);}
	char qaq[1000],tat[1000];
	void copy(string a,string b){
		solve(a,b+'\\'+get(get_name(a)));
		return;
	}
}

int work(string pSrc,string pDes)
{
	mkdir(pDes.c_str());
	string srcFileName,desFileName,str = "\\*.*",dir=pSrc+str;
	long hFile;
	_finddata_t fileinfo;
	if ((hFile = _findfirst(dir.c_str(),&fileinfo)) != -1)
	{
		do
		{
			srcFileName=pSrc+'\\'+fileinfo.name;
			desFileName=pDes+'\\'+fileinfo.name;
			if (!(fileinfo.attrib & _A_SUBDIR)) LOCK::copy(srcFileName,pDes);
			else if ( strcmp(fileinfo.name, "." ) != 0 && strcmp(fileinfo.name, ".." ) != 0 )
				work(srcFileName,desFileName);
		}while (_findnext(hFile,&fileinfo) == 0);
		_findclose(hFile);
		return 1;
	}
	return -3;
}

char use[MAX_PATH];
inline string get_name(string &x){
	int f=x.rfind(LOCK::lock);
	if (f==string::npos||(f<x.rfind('\\')&&x.rfind('\\')!=string::npos)){
		return x+LOCK::lock;
	}
	else return x.substr(0,f);
}

int main(int argc, char* argv[])
{
	if (argc==2){
		string a=argv[1];
		work(a,get_name(a));
	}
	else if (argc==3){
		string a=argv[1],b=argv[2];
		work(a,b);
	}
	else if (argc==1){
		string a;
		cout<<"copy from ..."<<endl;
		cin>>a;
		char chpath[MAX_PATH];
		GetModuleFileName(NULL,(LPSTR)chpath,sizeof(chpath));
		work(a,chpath);
	}
	return 0;
}
