#include "libraries.h"
int menu(std::string username="",int menu=0)
{
    if (menu==0)
    {
        //const char*cusername = username.c_str();
        if (username=="")
        {
            std::string in="0";
            while (in!="1"&&in!="2"&&in!="3")
            {
                tools::clear();
                tools::clear();

                std::cout << "Please Set Up A Accounts to continue\n";
                std::cout<<"\033[36m==========================\n\033[1m";
                std::cout<<"1) Login\n"<<"2) Register\n"<<"3) Quit\n";
                std::cin>>in;
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
            std::string in="0";
            tools::clear();
            std::cout<<"\033[1;32mYou are now Online\n";
            std::cout<<"Listening Message\n";
            std::cout<<std::endl<<"\033[0m";
            std::cout<<"\033[1;36m1) Chat\n2) Character Player\n3) Games"<<"\n0) Quit\n\033[0m";
            std::cin>>in;
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
                return 20;
            }
            if (in=="3")
            {
                return 4;
            }

        }
    }
    else if(menu==1)
    {
        std::string in="0";
        tools::clear();
        std::cout<<"Games:\n";
        std::cout<<"\033[1;36m1) 五子棋\n"<<"\n0) Leave\n";
        std::cin>>in;
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
    mkdir(".PokeData",777);
    user::user u;
    int quit=0;
    while (quit!=1)
    {
        tools::clear();
        while(quit==0)
        {
            quit=menu(u.username);
        }
        if (quit==2)
        {
            std::string username;
            std::string password;
            tools::clear();
            std::cout<<"\033[36m--Register--\n\033[0m";
            std::cout<<"Username:";
            std::cin >> username;
            std::cout<<"Password:\033[40;30m";
            std::cin >> password;
            std::cout<<"\033[0m\033[33mLoading\n\033[0m";
            if (u.reg(username,password))
            {
                tools::curl("mode=chat/start&username="+username+"&password="+password,".PokeLiveChatTmpFILE");
                std::cout<<std::endl;
                std::cout<<"You are now Online\n";
                std::cout<<"1) Listening Message\n";
                quit=0;
            }
            else
            {
                std::cout<<"\033[1;31mUser exist \033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                quit=0;
                std::cin>>username;
            }

        }
        if (quit==3)
        {
            std::string username;
            std::string password;
            tools::clear();
            std::cout<<"\033[36m--Login--\n\033[0m";
            std::cout<<"Username:";
            std::cin >> username;
            std::cout<<"Password:\033[40;30m";
            std::cin >> password;
            std::cout<<"\033[0m\033[33mLoading\n\033[0m";
            if (u.login(username,password))
            {
                tools::curl("mode=chat/start&username="+username+"&password="+password+"",".PokeLiveChatTmpFILE");
                std::cout<<std::endl;
                quit=0;
            }
            else
            {
                std::cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                quit=0;
                std::cin>>username;
            }
        }
        if (quit==1)
        {
            tools::clear();
            return 0;
        }
        if (quit==12)
        {
            //tools::tools::curl("mode=chat/clear&username="+u.username+"&password="+u.password+"",".PokeChatClearTmpFile");
            quit=0;
        }
        if (quit==20)
        {
            tools::clear();
            std::cout<<tools::curl("mode=CP&username="+u.username+"&password="+u.password+"",".PokePlayer")<<std::endl;
            std::string in;
            std::cin>>in;
            std::cout<<"\033[33mLoading\n\033[0m";
            std::cout<<"Downloading Data FILE From The Poke Net\n";
            std::string url=tools::curl("mode=CPD&username="+u.username+"&what="+in+"&password="+u.password+"",".PokeDownload");
            std::string bad=tools::curl(url,".PokePlayerDownload",2);
            if (bad==""||bad.length()<200)
            {
                if (bad=="")
                {
                    std::cout<<"File Not Exist\n";
                }
                else
                {
                    std::cout<<"Download Falled";
                }
                std::cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                std::string t;
                std::cin>>t;
                quit=0;
            }
            else
            {
                tools::write(".Poke-Data"+in,bad);
                std::cout<<"3 sec. to Start Playing";
                sleep(3);
                std::string file=".Poke-Data"+in;
                int i,j;
                i=-1;
                j=-1;
                std::ifstream infile;
                infile.open(file.data());
                assert(infile.is_open());
                std::string s;
                while(i<229880)
                {
                    std::thread play(player::player);
                    play.detach();
                    if (tools::read(".PokePlayer")!="Pause")
                    {
                        tools::clear();
                        j=-1;
                        while(j<34)
                        {
                            getline(infile,s,'\n');
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","^",s);
                            s=tools::str_replacve("                                                                                ","+",s);
                            s=tools::str_replacve("                 ","#",s);
                            s=tools::str_replacve("                ","0",s);
                            s=tools::str_replacve("               ","Z",s);
                            s=tools::str_replacve("              ",";",s);
                            s=tools::str_replacve("             ","I",s);
                            s=tools::str_replacve("            ","F",s);
                            s=tools::str_replacve("           ",",",s);
                            s=tools::str_replacve("         ","E",s);
                            s=tools::str_replacve("        ","W",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","-",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","V",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","C",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","X",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","A",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","J",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","D",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","K",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","G",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","L",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","S",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","T",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","R",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","U",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","Y",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","P",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx","O",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxxx","M",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxxx","Q",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxxx","=",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxxx","`",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxxx","\\",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxxx","\"",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxxx","_",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxxx","/",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxxx","}",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxxx","{",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxxx",")",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxxx","(",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxxx","&",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxxx","~",s);
                            s=tools::str_replacve("xxxxxxxxxxxxxx","|",s);
                            s=tools::str_replacve("xxxxxxxxxxxxx",">",s);
                            s=tools::str_replacve("xxxxxxxxxxxx","!",s);
                            s=tools::str_replacve("xxxxxxxxxxx","?",s);
                            s=tools::str_replacve("xxxxxxxxxx","<",s);
                            s=tools::str_replacve("xxxxxxxxx","*",s);
                            s=tools::str_replacve("xxxxxxxx","]",s);
                            s=tools::str_replacve("xxxxxxx","[",s);
                            s=tools::str_replacve("xxxxxx","@",s);
                            s=tools::str_replacve("xxxxx","%",s);
                            s=tools::str_replacve("xxxx",".",s);
                            s=tools::str_replacve("xxx","$",s);
                            i+=1;
                            j+=1;
                            std::cout<<s<<std::endl;
                        }
                        std::cout << "-------------------------------"<<i<<"-------------------------------\n";
                        std::cout << "Powered by Poke\n";
                        usleep(33000);
                    }
                    else
                    {
                        std::cout<<"Paused"<<std::endl;
                        while (tools::read(".PokePlayer")=="Pause") {}
                    }
                }
                tools::clear();
                std::cout<<"Play END"<<std::endl;
                infile.close();
                std::cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                std::string t;
                std::cin>>t;
                quit=0;
            }
        }
        if (quit==31) {
            std::string room=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi",".PokeGamingChannel");
            std::string wait="Waiting";
            tools::clear();
            std::cout<<"Looking for the opponent..\n";
            while(wait=="Waiting")
            {
                wait=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/wait",".PokeGamingChannel");
                sleep(0.25);
            }
            if (wait=="GameStart")
            {
                std::cout<<"Opponent Found\n";
                sleep(1);
                std::cout<<"Starting game\n";
                std::string wuziqipan[50][50];
                std::string report_x;
                std::string report_y;
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
                    std::cout<<std::endl;
                    while(y<=21) {
                        //yt<<y;
                        //yt>>ys;
                        wuziqipan[x][y]="*";
                        std::cout<<std::endl;
                        sleep(0.25);
                        y++;
                    }
                    y=-1;
                    x=x+1;
                }
                int gaming=1;
                int winner=0;
                std::string winners;
                std::string updateqipan;
                std::string gamecofeelback;
                int re=1;
                std::string qizi=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/who&x="+report_x+"&y="+report_y+"",".PokeGamingChannel");
                std::string nowqizi=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/nowwho&x="+report_x+"&y="+report_y+"",".PokeGamingChannel");
                std::string qiziUDx,qiziUDy;
                int UDqiziX,UDqiziY;
                int ry,rx;
                std::string colourful_red="\033[1;31m@\033[0m";
                std::string colourful_blue="\033[1;34m#\033[0m";
                while(gaming==1)
                {
                    std::cout<<std::endl;
                    tools::clear();
                    tools::clear();
                    std::cout<<"\033[1;31mX 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 \033[0m\033[1;34mY\033[0m\n";
                    int showx=1;
                    x=0;
                    y=0;
                    while (x<20)
                    {
                        std::cout<<"\033[0m  ";
                        while(y<20) {
                            if (wuziqipan[x][y]=="@")
                            {
                                std::cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                            }
                            else if(wuziqipan[x][y]=="#")
                            {
                                std::cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                            }
                            else
                            {
                                std::cout<<"\033[1m"<<wuziqipan[x][y]<<"\033[1m  ";
                            }
                            y++;

                        }
                        y=0;
                        x=x+1;
                        std::cout<<"\033[1;34m"<<showx<<"\033[0m\n\033[1m";
                        showx++;
                    }
                    if (nowqizi==qizi)
                    {

                        std::cout<<std::endl<<"\nX:";
                        std::cin>>report_y;
                        std::cout<<"Y:";
                        std::cin>>report_x;
                        rx=atoi(report_x.c_str());
                        ry=atoi(report_y.c_str());
                        rx=rx-1;
                        ry=ry-1;
                        if (rx>=0&&ry>=0&&rx<20&&ry<20&&wuziqipan[rx][ry]=="*")
                        {
                            std::stringstream r;
                            r<<rx;
                            r>>report_x;
                            std::stringstream w;
                            w<<ry;
                            w>>report_y;
                            tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/report&x="+report_x+"&y="+report_y+"",".PokeGamingChannel");
                            re=1;
                        }
                        else
                        {
                            std::cout<<"\n\033[1;31mINPUT ERROR!";
                            re=0;
                            std::cout<<std::endl;
                            sleep(2);
                        }
                    }
                    else if(nowqizi=="*")
                    {
                        std::cout<<"The other side initiates the defeat judgment";
                        std::cout<<"\nChecking";
                        x=1;
                        y=1;
                        while (x<=21&&winner==0)
                        {
                            std::cout<<".";
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
                                    std::stringstream winnerits;
                                    winnerits<<winner;
                                    winnerits>>winners;
                                    gamecofeelback=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/winner&id="+winners+"",".PokeGamingChannel");
                                    gaming=atoi(gamecofeelback.c_str());
                                    wait="END";
                                }
                                else
                                {
                                    gamecofeelback=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/winner&id=0",".PokeGamingChannel");
                                    gaming=atoi(gamecofeelback.c_str());
                                }
                                y++;
                            }
                            std::cout <<"."<<std::endl;
                            y=-1;
                            x=x+1;
                        }

                    }
                    else
                    {
                        std::cout<<"\nWaiting..";
                        std::cout<<std::endl;
                        while(nowqizi!=qizi)
                        {
                            nowqizi=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/nowwho&x="+report_x+"&y="+report_y+"",".PokeGamingChannel");
                            sleep(0.25);
                        }
                        re=1;
                    }
                    if (re==1)
                    {
                        std::cout <<"\033[1;34mRefresh";
                        sleep(1);
                        nowqizi=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/nowwho",".PokeGamingChannel");
                        qiziUDx=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/panupdatex",".PokeGamingChannel");
                        qiziUDy=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/panupdatey",".PokeGamingChannel");
                        std::cout <<".";
                        UDqiziX=atoi(qiziUDx.c_str());
                        UDqiziY=atoi(qiziUDy.c_str());
                        updateqipan=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/pan&x="+qiziUDx+"&y="+qiziUDy+"",".PokeGamingChannel");
                        while(updateqipan=="似乎有什么不对劲")
                        {
                            updateqipan=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/pan&x="+qiziUDx+"&y="+qiziUDy+"",".PokeGamingChannel");
                        }
                        wuziqipan[UDqiziX][UDqiziY]=updateqipan;
                        std::cout <<".";
                        x=1;
                        y=1;






                        while (x<=21&&winner==0)
                        {
                            std::cout<<"+";
                            while(y<=21&&winner==0) {
                                std::cout <<"-";
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

                                    std::stringstream winnerits;
                                    winnerits<<winner;
                                    winnerits>>winners;
                                    std::cout<<"\nFound the winning or losing...\nWaiting\n"<<std::endl;
                                    gamecofeelback="-1";
                                    while(gamecofeelback=="-1")
                                    {
                                        gamecofeelback=tools::curl("username="+u.username+"&password="+u.password+"&mode=games/wuziqi/gaming/winner&id="+winners+"",".PokeGamingChannel");
                                    }
                                    if (gamecofeelback=="0")
                                    {
                                        std::cout<<"The win was admitted"<<std::endl;
                                    }
                                    else
                                    {
                                        std::cout<<"Unrecognized!"<<std::endl;
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
                    tools::clear();
                    std::cout <<"\033[1;31mX 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 \033[0m\033[1;34mY\033[0m\n";
                    int showx=1;
                    x=0;
                    y=0;
                    while (x<20)
                    {
                        std::cout<<"\033[0m  ";
                        while(y<20) {
                            if (wuziqipan[x][y]=="@")
                            {
                                std::cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                            }
                            else if(wuziqipan[x][y]=="#")
                            {
                                std::cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                            }
                            else
                            {
                                std::cout<<"\033[1m"<<wuziqipan[x][y]<<"\033[1m  ";
                            }
                            y++;

                        }
                        y=0;
                        x=x+1;
                        std::cout<<"\033[1;34m"<<showx<<"\033[0m\n\033[1m";
                        showx++;
                    }
                    std::cout<<"\nYou:";
                    if (qizi=="@")
                    {
                        std::cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                    }
                    else if(qizi=="#")
                    {
                        std::cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                    }
                    std::cout<<std::endl<<"You Win";
                    std::cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                    std::string t;
                    std::cin>>t;
                }
                else
                {
                    tools::clear();
                    std::cout <<"\033[1;31mX 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 \033[0m\033[1;34mY\033[0m\n";
                    int showx=1;
                    x=0;
                    y=0;
                    while (x<20)
                    {
                        std::cout<<"\033[0m  ";
                        while(y<20) {
                            if (wuziqipan[x][y]=="@")
                            {
                                std::cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                            }
                            else if(wuziqipan[x][y]=="#")
                            {
                                std::cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                            }
                            else
                            {
                                std::cout<<"\033[1m"<<wuziqipan[x][y]<<"\033[1m  ";
                            }
                            y++;

                        }
                        y=0;
                        x=x+1;
                        std::cout<<"\033[1;34m"<<showx<<"\033[0m\n\033[1m";
                        showx++;
                    }
                    std::cout<<"\nYou:";
                    if (qizi=="@")
                    {
                        std::cout<<"\033[1m"<<colourful_red<<"\033[1m  ";
                    }
                    else if(qizi=="#")
                    {
                        std::cout<<"\033[1m"<<colourful_blue<<"\033[1m  ";
                    }
                    std::cout<<std::endl<<"You Lost";
                    std::cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
                    std::string t;
                    std::cin>>t;
                }
            }
            quit=4;
        }
        if (quit==10)
        {
            //while(quit==10)
            //{
            std::cout<<"\033[33mLoading\n\033[0m";
            tools::clear();
            std::string msg="\033[33mLoading\n\033[0m";
            std::thread chat_sendmessage(chat::sendmsg,u.username,u.password);
            chat_sendmessage.detach();
            while(quit==10)
            {
                if (tools::read(".message_buf")!="#[#(#%$q+u+i+t$%#)#]#")
                {
                    msg=tools::str_replacve("\n","麤",msg);
                    std::cout << msg << std::endl;
                    std::cout << "\n\033[36m==========================\033[0m";
                    std::cout << "\n\033[32mInput /s to send message in buf and /c to chean the buf\033[0m";
                    std::cout << "\n\033[33mInput /q to exit\033[0m\n";
                    std::cout << "\033[1mBuf:"<< tools::read(".message_buf") << std::endl;
                    msg=tools::curl("mode=chat&username="+u.username+"&password="+u.password+"",".PokeLiveChatTmpFILE");
                    sleep(0.33);
                    tools::clear();
                }
                else
                {
                    tools::write(".message_buf","");
                    quit=0;
                }
            }
        }
        if (quit==99)
        {
            std::cout<<"User or Password Changed and Now Your Login is disabled";
            std::cout<<"\033[31m\033[0m\n\033[33mKey Anything to continue(Letter..Number...\n\033[0m";
            quit=0;
            u.username="";
            u.password="";
            std::string t;
            std::cin>>t;
        }
        if (quit==4)
        {
            quit=menu(u.username,1);
        }
    }
}
