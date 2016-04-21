<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Variables</title>
</head>

<body>

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
print_r($response);
?>

<a href="index.php">Regresar</a>&nbsp;&nbsp;<a href="index.php">Regresar</a>
</body>
</html>