<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>
<html>
<body>
<div>
	<form method="post" action="genreadded.php">

    	<fieldset>
        	<legend><b>Genre Information</b></legend>
        	<p>Name of Genre: <input type="text" name="type" /></p>

        	<p><input type="submit" value="Add Genre"/></p>
    	</fieldset>
	</form>
</div>
</body>
</html>
