<?php
session_start();


	if ($_POST['m']!="")
	{
		$macID = $_POST['m'];
		 
		// Set Cookies
		$cookie_name = "bf";
		$_SESSION['bf']=$macID;
		$cookie_value = $macID;
		$expire = time() + (60 * 60 * 24 * 180); // expires in 6 month
		setcookie($cookie_name, $cookie_value, $expire,'','', true, true);
	}
	else
	{
		$macID = "";
	}
 

?>