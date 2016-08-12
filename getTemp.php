<?php
	require_once('nest.class.php');

	$user = "username";
	$pwd = "password";
	// Your Nest username and password.
	
	$nest = new Nest($user, $pwd);
	$curTemp = $infos->current_state->temperature;
	$tarTemp = $infos->target->temperature;
	echo "{" . $curTemp . "|" . $tarTemp . "}"; 
?>
