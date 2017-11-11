<?php
function  write ($filename,$word,$error_report="似乎有什么不对劲"){
	$filename=$GLOBALS['DataDIR'].$filename;
	$WriteFile=fopen($filename,"w") or die($error_report);
	fwrite($WriteFile,$word);
	fclose($WriteFile);
	#Debug
	if ($GLOBALS['debug']==true){
		file_put_contents("server.log",$_SERVER['REMOTE_ADDR'].":".$_SERVER['REMOTE_PORT']."  ->  ".$_SERVER['SERVER_NAME'].":".$_SERVER['SERVER_PORT']."  ".$_SERVER['REQUEST_METHOD']."  ".microtime(1)."  ".$filename." << '".$word."'\r\n",FILE_APPEND );
	}
}
function  jumpurl ($url){
	if ($GLOBALS['debug']==true){
		file_put_contents("server.log",$_SERVER['REMOTE_ADDR'].":".$_SERVER['REMOTE_PORT']."  ->  ".$_SERVER['SERVER_NAME'].":".$_SERVER['SERVER_PORT']."  ".$_SERVER['REQUEST_METHOD']."  ".microtime(1)."  Redirect >> '".$url."'\r\n",FILE_APPEND );
	}
	header('location:'.$url);
	exit ;
}
function  read ($filename,$error_report="似乎有什么不对劲"){
	$filename=$GLOBALS['DataDIR'].$filename;
	$WriteFile=fopen($filename,"r") or die($error_report);
	$word=fread($WriteFile,filesize($filename));
	fclose($WriteFile);
	#Debug
	if ($GLOBALS['debug']==true){
		file_put_contents("server.log",$_SERVER['REMOTE_ADDR'].":".$_SERVER['REMOTE_PORT']."  ->  ".$_SERVER['SERVER_NAME'].":".$_SERVER['SERVER_PORT']."  ".$_SERVER['REQUEST_METHOD']."  ".microtime(1)."  ".$filename." >> '".$word."'\r\n",FILE_APPEND );
	}
	return $word;
}
if ($_GET["mode"]=="reg"){
	if (file_exists("USERDATA/".$_GET["username"])){
		echo "Error";
	}else {
		write ("USERDATA/".$_GET["username"],md5($_GET["password"]));
	}
	echo "OK";
}
if ($_GET["mode"]=="login"){
	$readpwd=read ("USERDATA/".$_GET["username"]);
	if ($readpwd==md5($_GET["password"])){
		echo "OK";
	}else {
		echo "Error";
	}
}
if (read ("USERDATA/".$_GET["username"])==md5($_GET["password"])){
	$username=$_GET["username"];
	if ($_GET["mode"]=="chat/start"){
		$num=read ("CHATDATA/chat");
		write ("CHATDATA/$username.chatjoinnum",$num);
		echo "OK";
	}
	if ($_GET["mode"]=="chat"){
		set_time_limit(0);
		$i=0;
		$num=read ("CHATDATA/$username.chatjoinnum");
		$allnum=read ("CHATDATA/chat");
		$daa="";
		$a=$num;
		if ($num<$allnum){
			//$a=$a+1;
			$num=$num+1;
			while ($allnum>=$a){
				//echo "$num<br>$allnum<br>$a<br>";
				$omsg=read ("CHATDATA/.".$a);
				$user=read ("CHATDATA/.".$a.".username");
				$daa=$daa.$user.":".$omsg."麤";
				$a++;
			}
			echo $daa;
		}else {
			//	sleep(2);
			echo "无消息";
		}
	}
	if ($_GET["mode"]=="chat/report"){
		$num=read ("CHATDATA/chat");
		$num=$num+1;
		write ("CHATDATA/chat",$num);
		write ("CHATDATA/.".$num,$_GET["t"]);
		write ("CHATDATA/.".$num.".username",$_GET["username"]);
		echo "OK";
		exit ;
	}
	if ($_GET["mode"]=="chat/clear"){
		write ("CHATDATA/chat",0);
		echo "OK";
		exit ;
	}
	if ($_GET["mode"]=="CP"){
		echo "1) BadApple";
	}
	if ($_GET["mode"]=="CPD"){
		if ($_GET["what"]==1){
			jumpurl ("./BadApple");
		}
	}
	if ($_GET["mode"]=="games/wuziqi"){
		$nowwaitingroom=read ("game-wuziqi/game");
		if (file_exists("game-wuziqi/$nowwaitingroom.started")){
			write ("game-wuziqi/game",$nowwaitingroom+1);
			echo "Error Please Rejoin";
		}else {
			if (!file_exists("game-wuziqi/$nowwaitingroom.playerRED")){
				write ("game-wuziqi/$nowwaitingroom.playerRED",$username);
				write ("game-wuziqi/$username.gamingroom",$nowwaitingroom);
				echo "$nowwaitingroom";
			}
			elseif (!file_exists("game-wuziqi/$nowwaitingroom.playerBlue")){
				write ("game-wuziqi/$nowwaitingroom.playerBlue",$username);
				write ("game-wuziqi/$username.gamingroom",$nowwaitingroom);
				write ("game-wuziqi/$nowwaitingroom.started","1");
				mkdir("game-wuziqi/$nowwaitingroom-pan/");
				while ($x<=21){
					while ($y<=21){
						write ("game-wuziqi/$nowwaitingroom-pan/-$x-$y","*");
						$y++;
					}
					$y=-1;
					$x++;
				}
				write ("game-wuziqi/$nowwaitingroom-pan/lastUPDATEx",1);
				write ("game-wuziqi/$nowwaitingroom-pan/lastUPDATEy",1);
				write ("game-wuziqi/$nowwaitingroom-pan/lastqizi","@");
				echo "$nowwaitingroom";
				write ("game-wuziqi/game",$nowwaitingroom+1);
			}
		}
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/pan"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		echo read ("game-wuziqi/$gamingroom-pan/-".$_GET["x"]."-".$_GET["y"]);
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/wait"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		if (file_exists("game-wuziqi/$gamingroom.started")){
			echo "GameStart";
		}else {
			echo "Waiting";
		}
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/report"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		if (read ("game-wuziqi/$gamingroom.playerBlue")==$username){
			$qizi="@";
		}
		elseif (read ("game-wuziqi/$gamingroom.playerRED")==$username){
			$qizi="#";
		}
		write ("game-wuziqi/$gamingroom-pan/-".$_GET["x"]."-".$_GET["y"],$qizi);
		write ("game-wuziqi/$gamingroom-pan/lastUPDATEx",$_GET["x"]);
		write ("game-wuziqi/$gamingroom-pan/lastUPDATEy",$_GET["y"]);
		write ("game-wuziqi/$gamingroom-pan/lastqizi",$qizi);
		echo "OK";
	}
	
	if ($_GET["mode"]=="games/wuziqi/gaming/panupdatex"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		echo read ("game-wuziqi/$gamingroom-pan/lastUPDATEx");
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/panupdatey"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		echo read ("game-wuziqi/$gamingroom-pan/lastUPDATEy");
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/who"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		if (read ("game-wuziqi/$gamingroom.playerBlue")==$username){
			$qizi="@";
		}
		elseif (read ("game-wuziqi/$gamingroom.playerRED")==$username){
			$qizi="#";
		}
		echo $qizi;
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/nowwho"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		if (read ("game-wuziqi/$gamingroom-pan/lastqizi")=="#"){
			$qizi="@";
		}
		elseif (read ("game-wuziqi/$gamingroom-pan/lastqizi")=="@"){
			$qizi="#";
		}
		elseif (read ("game-wuziqi/$gamingroom-pan/lastqizi")=="*")
		{
		    $qizi="*";
		}
		echo $qizi;
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/xiaziok"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		if (read ("game-wuziqi/$gamingroom-pan/lastqizi")=="#"){
			$qizi="@";
		}
		elseif (read ("game-wuziqi/$gamingroom-pan/lastqizi")=="@"){
			$qizi="#";
		}
	}
	if ($_GET["mode"]=="games/wuziqi/gaming/winner"){
		$gamingroom=read ("game-wuziqi/$username.gamingroom");
		if (read ("game-wuziqi/$gamingroom.playerBlue")==$username){
			$qizi="@";
			$duishou="#";
		}
		elseif (read ("game-wuziqi/$gamingroom.playerRED")==$username){
			$qizi="#";
			$duishou="@";
		}
	    write("game-wuziqi/$gamingroom-pan/lastqizi","*");
		write("game-wuziqi/$gamingroom-pan/winner-reporter-$qizi",$_GET["id"]);
		if(read("game-wuziqi/$gamingroom-pan/winner-reporter-$duishou","-1")==$_GET["id"])
		{
		    echo "0";
		}
		else
		{
		    echo "1";
		}
		
	}
}