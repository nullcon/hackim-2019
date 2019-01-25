<?php
session_start();


if($_SESSION['go']){

$sp_php=explode('/', $_SERVER['PHP_SELF']);
$langfilename=$sp_php[count($sp_php)-1];

$pageListArray = array('index.php' => "1");

if($pageListArray [$langfilename]!=1){
		echo "not_authorized";
	    Header("Location: index.php?not_authorized");
	
	}

else{
	echo "hackim19{JS_GIT_PHP_HeR0_a1m40d}";
}
}

else{

	echo "you need to complete the first barrier";

}


?>
