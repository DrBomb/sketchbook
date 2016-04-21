<?php
include "include.php";
$get = file_get_contents("http://".$ip."/act");
$response = json_decode($get,true);

if($response['return_value'] == 1){
	echo "<meta http-equiv='refresh' content='0;URL=getSensors.php'>";
	//Grabar en BD fecha de encendido de la bomba si es necesario
    exit;
} else {
	echo "Error";
}