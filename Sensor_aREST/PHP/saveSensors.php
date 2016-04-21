<?php
include "include.php";
$get = url_get_contents("http://".$ip);
$response = json_decode($get,true);
$temp = $response['variables']['temp'];
$hum1 = $response['variables']['hum0'];
$hum2 = $response['variables']['hum1'];
$hum3 = $response['variables']['hum2'];
$mysqli = mysqli_connect("localhost", "root", "1234", "lecturas");
$res = mysqli_query($mysqli, "INSERT INTO sensores (Temp, Hum1, Hum2, Hum3) VALUES ('$temp', '$hum1', '$hum2', '$hum3')") or die("Failed");
echo "<meta http-equiv='refresh' content='0;URL=index.php'>";
?>