<?php
include "include.php";
$get = file_get_contents("http://".$ip."/bomb?params=0");
$response = json_decode($get,true);

if($response['return_value'] == 0){
	echo "<meta http-equiv='refresh' content='0;URL=index.php'>";
	//Grabar en BD fecha de apagado de la bomba si es necesario
    exit;
} else {
	echo "Error";
}
?>