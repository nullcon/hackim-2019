<?php
session_start();

	if ($_POST['username']!="" && $_POST['password']!=""){

		if($_POST['username']=="admin" && $_POST['password']=="admin"){


			if( $_COOKIE['bf']=="2656613544186699742"){

				if($_SESSION['bf']==$_COOKIE['bf']){

					echo "Wolla Wolla, you just passed the first barrier. /fea24a3a981cb8aa898dfbf30ccb4196/ ";
					$_SESSION['bf']=$_COOKIE['bf'];
					$_SESSION['go']="1";
			

				}

				else {
					echo "You cannot be here without tracking the user. Try harder";
				}

			}

			else{
				echo "Credentials are correct but you didnt login from admin browser. check the cookies";

			}


		}

		else {
			echo "Try harder";
		}

	}





?>