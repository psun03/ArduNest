<?php
	require_once('nest.class.php');

	// Your Nest username and password.
	$user = "username";
	$pwd = "password";

	$nest = new Nest($user, $pwd);

	if($nest->setTargetTemperature($_GET["SETTEMP"])) { //setTargetTemperature returns 0 or 1 
		echo "{1}";
	}
	else{
		echo "{0}";
}
?>
