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

$in = "b1";

socket_write($socket, $in, strlen($in));

$out = socket_read($socket,2048,PHP_NORMAL_READ);
socket_close($socket);

	echo "<meta http-equiv='refresh' content='0;URL=index.php'>";
	//Grabar en BD fecha de encendido de la bomba si es necesario

?>