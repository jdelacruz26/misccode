<?php
// Cargamos el archivo file.xml. El mismo debe estar en el seridor localhost
$xml=simplexml_load_file("file.xml") or die("Error: Cannot create object");

$con = mysql_connect("localhost","root",""); //nos conectamos con el servidor
mysql_select_db("new_xml_extract",$con) or die(mysql_error()); // seleccionamos la base de datos que hemos creado previamente

foreach ($xml -> item as $row) {
	$title = $row -> title; //cambiar por los campos deseados
	$destination = $row -> destination; //cambiar por los campos deseados
	$price = $row -> price; //cambiar por los campos deseados
	
// performance sql query
$sql = "INSERT INTO `test_xml` (`title`, `destination`, `price`)" 
	. "VALUES ('$title', '$destination', '$price')";

$result = mysql_query($sql);

if (!$result) {
	echo 'MYSQL ERROR :(';
	} else {
		echo ' SUCCES :)';
		}
}
?>