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
	<form method="post" action="staradded.php"> 

		<fieldset>
			<legend><b>Actor/Actress Information</b></legend>
			<p>First Name <input type="text" name="s_fname" /></p>
			<p>Middle Name <input type="text" name="s_mname" /></p>
			<p>Last Name <input type="text" name="s_lname" /></p>
			<p><input type="submit" value="Add Actor/Actress"/></p>
		</fieldset>
	</form>
</div>
</body>
</html>