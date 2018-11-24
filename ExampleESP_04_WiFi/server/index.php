<?php

if(isset($_POST['chat'])){
  // Code to save and send chat
  $chat = fopen("chatdata.txt", "a");
  $data="<b>".$_POST['username'].':</b> '.$_POST['chat']."<br>\n";
  fwrite($chat,$data);
  fclose($chat);
}
  $lines=array();
  $fp = fopen("chatdata.txt", "r");
  while(!feof($fp))
  {
   $line = fgets($fp, 4096);
   array_push($lines, $line);
   if (count($lines) > 16)
       array_shift($lines);
  }
  fclose($fp);
  foreach($lines as $line) {
    print($line);
  }
?>
<form method="post" action="#">
Name: <input name="username" type="text"/><br />
Text: <input name="chat" type="text"/>
<input type="submit">
</form>