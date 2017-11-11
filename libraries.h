#include <iostream>
#include <sstream>
#include <fstream>

#include <cassert>
#include <cstdio>

#include <string>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>

#include <fcntl.h>

#include <errno.h>
#include <termios.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "httpsocket.h"
using namespace std;
string str_replacve(string dstPattern,string pattern,string str,int count=-1)
{
    string retStr="";
    string::size_type pos;
    int i=0,l_count=0,szStr=str.length();
    if(-1 == count) // replace all
        count = szStr;
    for(i=0; i<szStr; i++)
    {
        if(string::npos == (pos=str.find(pattern,i)))  break;
        if((int)pos < szStr)
        {
            retStr += str.substr(i,pos-i) + dstPattern;
            i=pos+pattern.length()-1;
            if(++l_count >= count)
            {
                i++;
                break;
            }
        }
    }
    retStr += str.substr(i);
    return retStr;
}
void clear(bool hightlight=true)
{
    system("clear");
    if (hightlight==true)
    {
        cout<<"\033[1m";
    }
}
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
extern void clear_screen(int r)
{
    int f=0;
    while (f<r)
    {
        cout <<endl;
        f++;
    }
    //if (m==1)
    //{
    //   cout << "\033[31;1mDon't Input Anything Except Number!!!\033[0m\n";
    //}
}
extern string read(string filename)
{
    const char*f = filename.c_str();
    string data;
    ifstream read;
    read.open(f);
    read >> data;
    read.close();
    return data;
}
extern bool write(string filename,string word)
{
    const char*f = filename.c_str();
    ofstream write;
    write.open(f);
    write << word;
    write.close();
    return  true;
}
extern string curl(string url,string tmp = ".PokeNetTmp")
{
    url="http://v.starfiles.tk:88"+url;
    FILE *fp;
    if(!(fp = fopen(tmp.c_str(),"wb+")))
    {
        printf("can't open local file\n");
        return "Error";
    }
    CHttpSocket *cs = new CHttpSocket();
    cs->Socket();
    cs->Connect("v.starfiles.tk",80);
    long len = 0;
    std::string req = cs->FormatRequestHeader("v.starfiles.tk",url.c_str(),len,NULL,NULL,0,0,0);
    cs->SendRequest(req.c_str(),len);
    int lens;
    std::string head = cs->GetResponseHeader(lens);
    //printf("%s\n",head.c_str());
    int cnt = 0;
    int flag = head.find("Content-Length:",0);
    int endFlag = head.find("\r\n",flag);
    std::string subStr = head.substr(flag,endFlag-flag);
    sscanf(subStr.c_str(),"Content-Length: %d",&lens);
    fseek(fp,0,0);
    while(cnt < lens)
    {
        char buff[1025];
        int tmplen = cs->Receive(buff,1024);
        cnt += tmplen;
        fwrite(buff,1,tmplen,fp);
    }
    fclose(fp);
    //url="wget -o .PokeNetLogs -O "+tmp+" http://v.starfiles.tk:88/"+url;
    //string rm;
    //rm="rm -rf "+tmp;
    //const char*u = url.c_str();
    //system(u);
    string data=read(tmp);
    //system(r);
    return data;
}
class user
{
public:
    //user(string name,string pwd):username(name),password(pwd){}
    string username="";
    string password;
    bool login(string name,string pwd)
    {
        //string realpwd=read("accounts/"+name+"/password");
        string feelback=curl("/project/project.php?mode=login&username="+name+"&password="+pwd+"",".PokeLoginTmpFile");
        if (feelback=="似乎有什么不对劲")
        {
            cout << "\033[31mHave no this User\033[0m";
            return false;
        }
        else
        {
            if (feelback=="OK")
            {
                username=name;
                password=pwd;
                return true;
            }
            else
            {
                cout<< "\033[31mWrong Password\033[0m";
                return false;
            }
        }
    }
    bool reg(string name,string pwd)
    {
        //const char*n = name.c_str();
        //string checkuser=read("accounts/"+name+"/password");
        string feelback=curl("/project/project.php?mode=reg&username="+name+"&password="+pwd+"",".PokeRegTmpFile");
        if (feelback=="OK")
        {
            string f;
            //f="accounts/"+name;
            //const char*fd = f.c_str();
            //mkdir("accounts",755);
            //mkdir(fd,755);
            //system("curl -o .PokeNetTmp ")
            //f=read(".PokeNetTmp");
            //clear();
            //write("accounts/"+name+"/password",pwd);
            username=name;
            password=pwd;
            return true;
        }
        else
        {
            return false;
        }
    }
};
