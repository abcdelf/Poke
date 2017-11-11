#include "libraries.h"
using namespace std;
int menu(string username="",int menu=0)
{
    if (menu==0)
    {
        //const char*cusername = username.c_str();
        if (username=="")
        {
            string in="0";
            while (in!="1"&&in!="2"&&in!="3")
            {
                clear();
                cout << "Please Set Up A Accounts to continue\n";
                cout<<"\033[36m==========================\n\033[1m";
                cout<<"1) Login\n"<<"2) Register\n"<<"3) Quit\n";
                cin>>in;
            }
            if (in=="3")
            {
                return 1;
            }
            if (in=="2")
            {
                return 2;
            }
            if (in=="1")
            {
                return 3;
            }

        }
        else
        {
            string in="0";
            clear();
            cout<<"\033[1;32mYou are now Online\n";
            cout<<"Listening Message\n";
            cout<<endl<<"\033[0m";
            cout<<"\033[1;36m1) Chat\n2) Chat-Send Message\n3) Character Player\n4) Games"<<"\n0) Quit\n\033[0m";
            cin>>in;
            if (in=="0")
            {
                return 1;
            }
            if (in=="1")
            {
                return 10;
            }
            if (in=="2")
            {
                return 11;
            }
            if (in=="3")
            {
                return 20;
            }
            if (in=="4")
            {
                return 4;
            }
        }
    }
    else if(menu==1)
    {
        string in="0";
        clear();
        cout<<"Games:\n";
        cout<<"\033[1;36m1) 五子棋\n"<<"\n0) Leave\n";
        cin>>in;
        if (in=="0")
        {
            return 0;
        }
        if (in=="1")
        {
            return 31;
        }
    }
    return 0;
}
int main()
{
    user u;
    int quit=0;
    while (quit!=1)
    {
        clear();
        while(quit==0)
        {
            quit=menu(u.username);
        }
        if (quit==2)
        {
            string username;
            string password;
            clear();
            cout<<"\033[36m--Register--\n\033[0m";
            cout<<"Username:";
            cin >> username;
            cout<<"Password:\033[40;30m";
            cin >> password;
            cout<<"\033[0m\033[33mLoading\n\033[0m";
            if (u.reg(username,password))
            {
                curl("'/project/project.php?mode=chat/start&username="+username+"&password="+password+"'",".PokeLiveChatTmpFILE");
                cout<<endl;
                cout<<"You are now Online\n";
                cout<<"1) Listening Message\n";
                quit=0;
            }
            else
            {
                cout<<"\033[1;31mUser exist \033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                quit=0;
                cin>>username;
            }

        }
        if (quit==3)
        {
            string username;
            string password;
            clear();
            cout<<"\033[36m--Login--\n\033[0m";
            cout<<"Username:";
            cin >> username;
            cout<<"Password:\033[40;30m";
            cin >> password;
            cout<<"\033[0m\033[33mLoading\n\033[0m";
            if (u.login(username,password))
            {
                curl("'/project/project.php?mode=chat/start&username="+username+"&password="+password+"'",".PokeLiveChatTmpFILE");
                cout<<endl;
                quit=0;
            }
            else
            {
                cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                quit=0;
                cin>>username;
            }
        }
        if (quit==1)
        {
            clear();
            return 0;
        }
        if (quit==12)
        {
            //curl("'/project/project.php?mode=chat/clear&username="+u.username+"&password="+u.password+"'",".PokeChatClearTmpFile");
            quit=0;
        }
        if (quit==20)
        {
            cout<<curl("'/project/project.php?mode=CP&username="+u.username+"&password="+u.password+"'",".PokePlayer");
            string in;
            cin>>in;
            cout<<"\033[33mLoading\n\033[0m";
            cout<<"Downloading Data FILE From The Poke Net\n";
            string bad=curl("'/project/project.php?mode=CPD&what="+in+"&username="+u.username+"&password="+u.password+"'",".PokePlayerDownload");
            string ur="'/project/project.php?mode=CPD&what="+in+"&username="+u.username+"&password="+u.password+"'";
            if (bad==""||bad.length()<200)
            {
                if (bad=="")
                {
                    cout<<"File Not Exist\n";
                }
                else
                {
                    cout<<"Failed to Download Please Download manual\n";
                    cout<<"Url:"<<ur<<endl;
                    cout<<"Wget:wget -O .Poke-Data"<<in<<" "<<ur;
                }
                cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                string t;
                cin>>t;
                quit=0;
            }
            else
            {
                write(".Poke-Data"+in,bad);
                cout<<"3 sec. to Start Playing";
                sleep(3);
                string file=".Poke-Data"+in;
                int i,j;
                i=-1;
                j=-1;
                ifstream infile;
                infile.open(file.data());
                assert(infile.is_open());
                string s;
                while(i<229880)
                {
                    clear();
                    j=-1;
                    while(j<34)
                    {
                        getline(infile,s,'\n');
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","^",s);
                        s=str_replacve("                                                                                ","+",s);
                        s=str_replacve("                 ","#",s);
                        s=str_replacve("                ","0",s);
                        s=str_replacve("               ","Z",s);
                        s=str_replacve("              ",";",s);
                        s=str_replacve("             ","I",s);
                        s=str_replacve("            ","F",s);
                        s=str_replacve("           ",",",s);
                        s=str_replacve("         ","E",s);
                        s=str_replacve("        ","W",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","-",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","V",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","C",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","X",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","A",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","J",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","D",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","K",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","G",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","L",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","S",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","T",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","R",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","U",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","Y",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","P",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx","O",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxx","M",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxx","Q",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxx","=",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxx","`",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxxx","\\",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxxx","\"",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxxx","_",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxxx","/",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxxx","}",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxxx","{",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxxx",")",s);
                        s=str_replacve("xxxxxxxxxxxxxxxxx","(",s);
                        s=str_replacve("xxxxxxxxxxxxxxxx","&",s);
                        s=str_replacve("xxxxxxxxxxxxxxx","~",s);
                        s=str_replacve("xxxxxxxxxxxxxx","|",s);
                        s=str_replacve("xxxxxxxxxxxxx",">",s);
                        s=str_replacve("xxxxxxxxxxxx","!",s);
                        s=str_replacve("xxxxxxxxxxx","?",s);
                        s=str_replacve("xxxxxxxxxx","<",s);
                        s=str_replacve("xxxxxxxxx","*",s);
                        s=str_replacve("xxxxxxxx","]",s);
                        s=str_replacve("xxxxxxx","[",s);
                        s=str_replacve("xxxxxx","@",s);
                        s=str_replacve("xxxxx","%",s);
                        s=str_replacve("xxxx",".",s);
                        s=str_replacve("xxx","$",s);
                        i+=1;
                        j+=1;
                        cout<<s<<endl;
                    }
                    cout << "-------------------------------"<<i<<"-------------------------------\n";
                    cout << "Powered by Poke\n";
                    usleep(33000);
                }
                clear();
                cout<<"Play END"<<endl;
                infile.close();
                cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                string t;
                cin>>t;
                quit=0;
            }
        }
        if (quit==31) {
            string room=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi'",".PokeGamingChannel");
            string wait="Waiting";
            clear();
            cout<<"Looking for the opponent..\n";
            while(wait=="Waiting")
            {
                wait=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/wait'",".PokeGamingChannel");
                sleep(0.25);
            }
            if (wait=="GameStart")
            {
                cout<<"Opponent Found\n";
                sleep(1);
                cout<<"Starting game\n";
                string wuziqipan[50][50];
                string report_x;
                string report_y;
                int x=0;
                int y=0;
                //stringstream xt;
                //stringstream yt;
                //string xs;
                //string ys;
                while (x<=21)
                {
                    //xt<<x;
                    //xt>>xs;
                    sleep(0.25);
                    cout<<endl;
                    while(y<=21) {
                        //yt<<y;
                        //yt>>ys;
                        wuziqipan[x][y]="*";
                        cout<<endl;
                        sleep(0.25);
                        y++;
                    }
                    y=-1;
                    x=x+1;
                }
                int gaming=1;
                int winner=0;
                string winners;
                string gamecofeelback;
                int re=1;
                string qizi=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/who&x="+report_x+"&y="+report_y+"'",".PokeGamingChannel");
                string nowqizi=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/nowwho&x="+report_x+"&y="+report_y+"'",".PokeGamingChannel");
                string qiziUDx,qiziUDy;
                int UDqiziX,UDqiziY;
                int ry,rx;
                string colourful_red="\033[1;31m@\033[0m";
                string colourful_blue="\033[1;34m#\033[0m";
                while(gaming==1)
                {
                    cout<<endl;
                    clear();
                    clear();
                    cout<<"\033[1;31mX 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 \033[0m\033[1;34mY\033[0m\n";
                    int showx=1;
                    x=0;
                    y=0;
                    while (x<20)
                    {
                        cout<<"\033[0m  ";
                        while(y<20) {
                            if (wuziqipan[x][y]=="@")
                            {
                                cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                            }
                            else if(wuziqipan[x][y]=="#")
                            {
                                cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                            }
                            else
                            {
                                cout<<"\033[1m"<<wuziqipan[x][y]<<"\033[1m  ";
                            }
                            y++;

                        }
                        y=0;
                        x=x+1;
                        cout<<"\033[1;34m"<<showx<<"\033[0m\n\033[1m";
                        showx++;
                    }
                    if (nowqizi==qizi)
                    {
                        cout<<endl<<"\nX:";
                        cin>>report_y;
                        cout<<"Y:";
                        cin>>report_x;
                        rx=atoi(report_x.c_str());
                        ry=atoi(report_y.c_str());
                        rx=rx-1;
                        ry=ry-1;
                        if (rx>=0&&ry>=0&&rx<20&&ry<20&&wuziqipan[rx][ry]=="*")
                        {
                            stringstream r;
                            r<<rx;
                            r>>report_x;
                            stringstream w;
                            w<<ry;
                            w>>report_y;
                            curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/report&x="+report_x+"&y="+report_y+"'",".PokeGamingChannel");
                            re=1;
                        }
                        else
                        {
                            cout<<"\n\033[1;31mINPUT ERROR!";
                            re=0;
                            cout<<endl;
                            sleep(2);
                        }
                    }
                    else if(nowqizi=="*")
                    {
                        cout<<"The other side initiates the defeat judgment";
                        cout<<"\nChecking";
                        x=1;
                        y=1;
                        while (x<=21&&winner==0)
                        {
                            cout<<".";
                            while(y<=21&&winner==0) {
                                //@
                                if (wuziqipan[x][y]=="@"&&wuziqipan[x+1][y]=="@"&&wuziqipan[x+2][y]=="@"&&wuziqipan[x+3][y]=="@"&&wuziqipan[x+4][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x][y]=="@"&&wuziqipan[x-1][y]=="@"&&wuziqipan[x-2][y]=="@"&&wuziqipan[x-3][y]=="@"&&wuziqipan[x-4][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x][y+1]=="@"&&wuziqipan[x][y+2]=="@"&&wuziqipan[x][y+3]=="@"&&wuziqipan[x][y+4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x][y-1]=="@"&&wuziqipan[x][y-2]=="@"&&wuziqipan[x][y-3]=="@"&&wuziqipan[x][y-4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x+1][y+1]=="@"&&wuziqipan[x+2][y+2]=="@"&&wuziqipan[x+3][y+3]=="@"&&wuziqipan[x+4][y+4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x-1][y-1]=="@"&&wuziqipan[x-2][y-2]=="@"&&wuziqipan[x-3][y-3]=="@"&&wuziqipan[x-4][y-4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x-1][y+1]=="@"&&wuziqipan[x-2][y+2]=="@"&&wuziqipan[x-3][y+3]=="@"&&wuziqipan[x-4][y+4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x+1][y-1]=="@"&&wuziqipan[x+2][y-2]=="@"&&wuziqipan[x+3][y-3]=="@"&&wuziqipan[x+4][y-4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                //#
                                if (wuziqipan[x][y]=="#"&&wuziqipan[x+1][y]=="#"&&wuziqipan[x+2][y]=="#"&&wuziqipan[x+3][y]=="#"&&wuziqipan[x+4][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x][y]=="#"&&wuziqipan[x-1][y]=="#"&&wuziqipan[x-2][y]=="#"&&wuziqipan[x-3][y]=="#"&&wuziqipan[x-4][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x][y+1]=="#"&&wuziqipan[x][y+2]=="#"&&wuziqipan[x][y+3]=="#"&&wuziqipan[x][y+4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x][y-1]=="#"&&wuziqipan[x][y-2]=="#"&&wuziqipan[x][y-3]=="#"&&wuziqipan[x][y-4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x+1][y+1]=="#"&&wuziqipan[x+2][y+2]=="#"&&wuziqipan[x+3][y+3]=="#"&&wuziqipan[x+4][y+4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x-1][y-1]=="#"&&wuziqipan[x-2][y-2]=="#"&&wuziqipan[x-3][y-3]=="#"&&wuziqipan[x-4][y-4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x-1][y+1]=="#"&&wuziqipan[x-2][y+2]=="#"&&wuziqipan[x-3][y+3]=="#"&&wuziqipan[x-4][y+4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x+1][y-1]=="#"&&wuziqipan[x+2][y-2]=="#"&&wuziqipan[x+3][y-3]=="#"&&wuziqipan[x+4][y-4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                if (winner!=0)
                                {
                                    stringstream winnerits;
                                    winnerits<<winner;
                                    winnerits>>winners;
                                    gamecofeelback=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/winner&id="+winners+"'",".PokeGamingChannel");
                                    gaming=atoi(gamecofeelback.c_str());
                                    wait="END";
                                }
                                else
                                {
                                    gamecofeelback=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/winner&id=0'",".PokeGamingChannel");
                                    gaming=atoi(gamecofeelback.c_str());
                                }

                                y++;
                            }
                            cout <<"."<<endl;
                            y=-1;
                            x=x+1;
                        }

                    }
                    else
                    {
                        cout<<"\nWaiting..";
                        cout<<endl;
                        while(nowqizi!=qizi)
                        {
                            nowqizi=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/nowwho&x="+report_x+"&y="+report_y+"'",".PokeGamingChannel");
                            sleep(0.25);
                        }
                        re=1;
                    }
                    if (re==1)
                    {
                        cout <<"\033[1;34mRefresh";
                        nowqizi=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/nowwho&x="+report_x+"&y="+report_y+"'",".PokeGamingChannel");
                        qiziUDx=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/panupdatex'",".PokeGamingChannel");
                        qiziUDy=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/panupdatey'",".PokeGamingChannel");
                        cout <<".";
                        UDqiziX=atoi(qiziUDx.c_str());
                        UDqiziY=atoi(qiziUDy.c_str());
                        wuziqipan[UDqiziX][UDqiziY]=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/pan&x="+qiziUDx+"&y="+qiziUDy+"'",".PokeGamingChannel");
                        cout <<".";
                        x=1;
                        y=1;
                        while (x<=21&&winner==0)
                        {
                            cout<<"+";
                            while(y<=21&&winner==0) {
                                cout <<"-";
                                //@
                                if (wuziqipan[x][y]=="@"&&wuziqipan[x+1][y]=="@"&&wuziqipan[x+2][y]=="@"&&wuziqipan[x+3][y]=="@"&&wuziqipan[x+4][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x][y]=="@"&&wuziqipan[x-1][y]=="@"&&wuziqipan[x-2][y]=="@"&&wuziqipan[x-3][y]=="@"&&wuziqipan[x-4][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x][y+1]=="@"&&wuziqipan[x][y+2]=="@"&&wuziqipan[x][y+3]=="@"&&wuziqipan[x][y+4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x][y-1]=="@"&&wuziqipan[x][y-2]=="@"&&wuziqipan[x][y-3]=="@"&&wuziqipan[x][y-4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x+1][y+1]=="@"&&wuziqipan[x+2][y+2]=="@"&&wuziqipan[x+3][y+3]=="@"&&wuziqipan[x+4][y+4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x-1][y-1]=="@"&&wuziqipan[x-2][y-2]=="@"&&wuziqipan[x-3][y-3]=="@"&&wuziqipan[x-4][y-4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x-1][y+1]=="@"&&wuziqipan[x-2][y+2]=="@"&&wuziqipan[x-3][y+3]=="@"&&wuziqipan[x-4][y+4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                else if (wuziqipan[x+1][y-1]=="@"&&wuziqipan[x+2][y-2]=="@"&&wuziqipan[x+3][y-3]=="@"&&wuziqipan[x+4][y-4]=="@"&&wuziqipan[x][y]=="@"){
                                    //gaming=0;
                                    winner=1;
                                }
                                //#
                                if (wuziqipan[x][y]=="#"&&wuziqipan[x+1][y]=="#"&&wuziqipan[x+2][y]=="#"&&wuziqipan[x+3][y]=="#"&&wuziqipan[x+4][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x][y]=="#"&&wuziqipan[x-1][y]=="#"&&wuziqipan[x-2][y]=="#"&&wuziqipan[x-3][y]=="#"&&wuziqipan[x-4][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x][y+1]=="#"&&wuziqipan[x][y+2]=="#"&&wuziqipan[x][y+3]=="#"&&wuziqipan[x][y+4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x][y-1]=="#"&&wuziqipan[x][y-2]=="#"&&wuziqipan[x][y-3]=="#"&&wuziqipan[x][y-4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x+1][y+1]=="#"&&wuziqipan[x+2][y+2]=="#"&&wuziqipan[x+3][y+3]=="#"&&wuziqipan[x+4][y+4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x-1][y-1]=="#"&&wuziqipan[x-2][y-2]=="#"&&wuziqipan[x-3][y-3]=="#"&&wuziqipan[x-4][y-4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x-1][y+1]=="#"&&wuziqipan[x-2][y+2]=="#"&&wuziqipan[x-3][y+3]=="#"&&wuziqipan[x-4][y+4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                else if (wuziqipan[x+1][y-1]=="#"&&wuziqipan[x+2][y-2]=="#"&&wuziqipan[x+3][y-3]=="#"&&wuziqipan[x+4][y-4]=="#"&&wuziqipan[x][y]=="#"){
                                    //gaming=0;
                                    winner=2;
                                }
                                if(winner!=0)
                                {

                                    stringstream winnerits;
                                    winnerits<<winner;
                                    winnerits>>winners;
                                    cout<<"\nFound the winning or losing...\nWaiting\n"<<endl;
                                    gamecofeelback="-1";
                                    while(gamecofeelback=="-1")
                                    {
                                        gamecofeelback=curl("'/project/project.php?username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/winner&id="+winners+"'",".PokeGamingChannel");
                                    }
                                    if (gamecofeelback=="0")
                                    {
                                        cout<<"The win was admitted"<<endl;
                                    }
                                    else
                                    {
                                        cout<<"Unrecognized!"<<endl;
                                    }
                                    gaming=atoi(gamecofeelback.c_str());
                                }
                                y++;
                            }
                            y=-1;
                            x=x+1;
                        }
                    }
                }

                if(winner==1)
                {
                    winners="@";
                }
                else if(winner==2)
                {
                    winners="#";
                }
                if (winners==qizi)
                {
                    clear();
                    cout <<"\033[1;31mX 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 \033[0m\033[1;34mY\033[0m\n";
                    int showx=1;
                    x=0;
                    y=0;
                    while (x<20)
                    {
                        cout<<"\033[0m  ";
                        while(y<20) {
                            if (wuziqipan[x][y]=="@")
                            {
                                cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                            }
                            else if(wuziqipan[x][y]=="#")
                            {
                                cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                            }
                            else
                            {
                                cout<<"\033[1m"<<wuziqipan[x][y]<<"\033[1m  ";
                            }
                            y++;

                        }
                        y=0;
                        x=x+1;
                        cout<<"\033[1;34m"<<showx<<"\033[0m\n\033[1m";
                        showx++;
                    }
                    cout<<"\nYou:";
                    if (qizi=="@")
                    {
                        cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                    }
                    else if(qizi=="#")
                    {
                        cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                    }
                    cout<<endl<<"You Win";
                    cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                    string t;
                    cin>>t;
                }
                else
                {
                    clear();
                    cout <<"\033[1;31mX 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 \033[0m\033[1;34mY\033[0m\n";
                    int showx=1;
                    x=0;
                    y=0;
                    while (x<20)
                    {
                        cout<<"\033[0m  ";
                        while(y<20) {
                            if (wuziqipan[x][y]=="@")
                            {
                                cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                            }
                            else if(wuziqipan[x][y]=="#")
                            {
                                cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                            }
                            else
                            {
                                cout<<"\033[1m"<<wuziqipan[x][y]<<"\033[1m  ";
                            }
                            y++;

                        }
                        y=0;
                        x=x+1;
                        cout<<"\033[1;34m"<<showx<<"\033[0m\n\033[1m";
                        showx++;
                    }
                    cout<<"\nYou:";
                    if (qizi=="@")
                    {
                        cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                    }
                    else if(qizi=="#")
                    {
                        cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                    }
                    cout<<endl<<"You Lost";
                    cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                    string t;
                    cin>>t;
                }
            }
            quit=4;
        }
        if (quit==10)
        {
            //while(quit==10)
            //{
            cout<<"\033[33mLoading\n\033[0m";
            clear();
            string msg="\033[33mLoading\n\033[0m";
            while(quit==10)
            {
                if (msg=="")
                {
                    quit=0;
                }
                else
                {
                    msg=str_replacve("\n","麤",msg);
                    cout << msg<<"\n";
                }
                cout << "\n\033[36m==========================\033[0m\n";
                cout << "If You want to send message,Start a new program And In Logged Menu Choose 2)\n";
                cout << "Press Ctrl+C to exit\n";
                msg=curl("'/project/project.php?mode=chat&username="+u.username+"&password="+u.password+"'",".PokeLiveChatTmpFILE");
                sleep(0.1);
                clear();
            }
        }
        if (quit==11)
        {
            clear();
            string msg;
            while(quit==11)
            {
                cout << "\033[33mChat-Send Message\033[0m";
                cout << endl << "Username:" << u.username <<endl << "Input QuIt to exit\n";
                cout << "\033[36m==========================\n\033[0m";
                cout<<"Please input:";
                cin >> msg;
                if (msg=="QuIt")
                {
                    quit=0;
                }
                else
                {
                    string feelback=curl("'/project/project.php?mode=chat/report&t="+msg+"&username="+u.username+"&password="+u.password+"'",".PokeChatSendMsgTMPFILE");
                    if (feelback=="OK")
                    {
                        clear();
                        cout << "\033[32mMessage Status:Sent\n\n\033[0m";
                    }
                    else
                    {
                        clear();
                        cout << "\n\033[31mError*Message Sending Failure\n\033[0m";
                    }
                }
            }
        }
        if (quit==99)
        {
            cout<<"User or Password Changed and Now Your Login is disabled";
            cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
            quit=0;
            u.username="";
            u.password="";
            string t;
            cin>>t;
        }
        if (quit==4)
        {
            quit=menu(u.username,1);
        }
    }
}
