<?php
include "include.php";
error_reporting(E_ALL);

/* Create a TCP/IP socket. */
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
}
$result = socket_connect($socket, $ip, $port);
if ($result === false) {
    echo "socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
}

$in = "ss";

socket_write($socket, $in, strlen($in));

$out = socket_read($socket,2048,PHP_NORMAL_READ);
socket_close($socket);

$response = json_decode($out,true);

$temp = $response['temperatura'];
$hum1 = $response['humedades'][0];
$hum2 = $response['humedades'][1];
$hum3 = $response['humedades'][2];
$mysqli = mysqli_connect("localhost", "root", "1234", "lecturas");
$res = mysqli_query($mysqli, "INSERT INTO sensores (Temp, Hum1, Hum2, Hum3) VALUES ('$temp', '$hum1', '$hum2', '$hum3')") or die("Failed");
echo "<meta http-equiv='refresh' content='0;URL=index.php'>";
?>