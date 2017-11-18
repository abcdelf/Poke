#include <iostream>
#include <sstream>
#include <fstream>

#include <thread>

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
#include <time.h>

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

namespace tools {
std::string str_replacve(std::string dstPattern,std::string pattern,std::string str,int count=-1)
{
    std::string retStr="";
    std::string::size_type pos;
    int i=0,l_count=0,szStr=str.length();
    if(-1 == count) // replace all
        count = szStr;
    for(i=0; i<szStr; i++)
    {
        if(std::string::npos == (pos=str.find(pattern,i)))  break;
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
        std::cout<<"\033[1m";
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
        std::cout <<std::endl;
        f++;
    }
    //if (m==1)
    //{
    //   std::cout << "\033[31;1mDon't Input Anything Except Number!!!\033[0m\n";
    //}
}
extern std::string read(std::string filename)
{
    const char*f = filename.c_str();
    std::string data;
    std::ifstream read;
    read.open(f);
    std::stringstream buffer;
    buffer << read.rdbuf();
    std::string contents(buffer.str());
    return contents;
}
extern bool write(std::string filename,std::string word,int mode=1)
{
    const char*f = filename.c_str();
    std::ofstream write;
    if (mode==1)
    {
        write.open(f);
    }
    else if (mode==2)
    {
        write.open(f,std::ios::app);
    }
    write << word;
    write.close();
    return  true;
}

extern std::string curl(std::string url,std::string tmp = ".PokeNetTmp",int mode=1)
{
    std::srand((unsigned)time( NULL ) );
    int randnum=rand();
    std::stringstream ss;
    ss<<randnum;
    std::string rands;
    ss>>rands;
    tmp=rands+tmp;
    tmp=".PokeData/"+tmp;
    if (mode==1)
    {
        url="http://v.starfiles.tk:88/project/project.php?"+url;
    }
    else if (mode==2)
    {
        url="http://v.starfiles.tk:88/"+url;
    }
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
    std::sscanf(subStr.c_str(),"Content-Length: %d",&lens);
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
    //std::string rm;
    //rm="rm -rf "+tmp;
    //const char*u = url.c_str();
    //system(u);
    std::string data=tools::read(tmp);
    //system(r);
    return data;
}
}
namespace player {
extern int player(){
    std::string co;
    for (;;)
    {
        co="";
        std::cin>>co;
        if (co=="p")
        {
            tools::write(".PokePlayer","Pause");
        }
        else if (co=="n")
        {
            tools::write(".PokePlayer","");
        }
    }
    exit(0);
}
}
namespace game_wuziqi {
//extern int input(std::string username,std::string password) {

//}
}
namespace chat {
int sendmsg(std::string username,std::string password) {
    // std::string msg="";
    std::string msg;
    for(;;)
    {
        msg="";
        std::cin>>msg;
        if (msg=="/s") {
            tools::curl("mode=chat/report&t="+tools::read(".message_buf")+"&username="+username+"&password="+password+"",".PokeChatSendMsgTMPFILE");
            tools::write(".message_buf","");
        }
        else if (msg=="/c")
        {
            tools::write(".message_buf","");
        }
        else if (msg=="/q")
        {
            tools::write(".message_buf","#[#(#%$q+u+i+t$%#)#]#");
            return 0;
        }
        else
        {
            tools::write(".message_buf",msg,2);
        }
    }
}
}
namespace user {
void keep_heartbeat(std::string username,std::string password) {
    for(;;)
    {
        tools::curl("mode=heartbeat&username="+username+"&password="+password+"",".PokeRegTmpFile");
        sleep(10);
    }
    return;
}
class user
{
public:
    //user(std::string name,std::string pwd):username(name),password(pwd){}
    std::string username="";
    std::string password;
    bool login(std::string name,std::string pwd)
    {
        //std::string realpwd=tools::read("accounts/"+name+"/password");
        std::string feelback=tools::curl("mode=login&username="+name+"&password="+pwd+"",".PokeLoginTmpFile");
        if (feelback=="似乎有什么不对劲")
        {
            std::cout << "\033[31mHave no this User\033[0m";
            return false;
        }
        else
        {
            if (feelback=="OK")
            {
                username=name;
                password=pwd;
                std::thread heartbeat(keep_heartbeat,this->username,this->password);
                heartbeat.detach();
                return true;
            }
            else
            {
                std::cout<< "\033[31mWrong Password\033[0m";
                return false;
            }
        }
    }
    bool reg(std::string name,std::string pwd)
    {
        //const char*n = name.c_str();
        //std::string checkuser=read("accounts/"+name+"/password");
        std::string feelback=tools::curl("mode=reg&username="+name+"&password="+pwd+"",".PokeRegTmpFile");
        if (feelback=="OK")
        {
            std::string f;
            //f="accounts/"+name;
            //const char*fd = f.c_str();
            //mkdir("accounts",755);
            //mkdir(fd,755);
            //system("tools::curl -o .PokeNetTmp ")
            //f=read(".PokeNetTmp");
            //clear();
            //tools::write("accounts/"+name+"/password",pwd);
            username=name;
            password=pwd;
            std::thread heartbeat(keep_heartbeat,this->username,this->password);
            heartbeat.detach();
            return true;
        }
        else
        {
            return false;
        }
    }

};
}

