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
	<!--Creates form for user input-->
	<form method="post" action="directoradded.php"> 

		<fieldset>
			<legend><b>Director Information</b></legend>
			<p>Director First Name <input type="text" name="d_fname" /></p>
			<p>Director Last Name <input type="text" name="d_lname" /></p>
			<p><input type="submit" value="Add Director"/></p>
		</fieldset>
	</form>
</div>
</body>
</html>