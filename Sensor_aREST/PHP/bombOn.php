<?php
include "include.php";
$get = file_get_contents("http://".$ip."/bomb?params=1");
$response = json_decode($get,true);

if($response['return_value'] == 1){
	echo "<meta http-equiv='refresh' content='0;URL=index.php'>";
	//Grabar en BD fecha de encendido de la bomba si es necesario
    exit;
} else {
	echo "Error";
}
?>