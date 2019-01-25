<?php
session_start();

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);


if($_SESSION['go']){
	echo "File lister <br>";


	echo "Avialble files <br>";

	echo "<ol>";
  echo "<li><a href='admin.php'>admin.php</a></li>";
    echo "<li><a href='pack-9d392b4893d01af61c5712fdf5aafd8f24d06a10.pack'>pack-9d392b4893d01af61c5712fdf5aafd8f24d06a10.pack</a><br></li>";

  echo "</ol>";

}
else{

	echo "you need to complete the first barrier";

}


?>