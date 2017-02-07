<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
	<body>
    	<h1>Edit Role</h1>

    	<fieldset>
        	<legend>Change Role/Character Name</legend>
        	<table>

            	<tr>
                	<td><b>First Name</b></td>
                	<td><b>Last Name</b></td>
                	<td><b>Other Name</b></td>
            	</tr>
<?php
	if(!($stmt = $mysqli->prepare("SELECT first_name, last_name, other_name FROM role WHERE role_id=?"))){
    	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}

	if(!($stmt->bind_param("s", $_POST['role_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}

	if(!$stmt->execute()){
    	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	if(!$stmt->bind_result($first_name, $last_name, $other_name)){
    	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	while($stmt->fetch()){
 	echo "<tr>\n<td>\n" . $first_name . "\n</td>\n<td>\n" . $last_name . "\n</td>\n<td>\n" . $other_name . "\n</td>\n</tr>\n";
	}

	$stmt->close();
?>
        	</table>

        	<br>

        	<!--form to edit role-->
         	<form action="roleedited.php" method="post">

            	<!--stores the movie_id sent via GET from the previous page-->
            	<input type="hidden" name="role_id" value="<?php echo $_POST['role_id']; ?>" />
            	<input type="hidden" name="movie_id" value="<?php echo $_POST['movie_id']; ?>" />
            	<!--stores the year from user input-->
            	<b>Enter updated role/character name.</b>
            	<br>
            	*Please note: any fields left blank will be overwritten with empty string.
            	<br>

            	First Name: <input type="text" name="role_first_name"/>
            	Last Name: <input type="text" name="role_last_name"/>
            	Other Name: <input type="text" name="role_other_name"/>


            	<input type="submit" value="Update Role" />
        	</form>
    	</fieldset>

        	<!--button that goes back to edit movie details and passes the movie_id back to it-->
        	<form method="post" action="editmovie.php">
            	<input type="hidden" name="movie_id" value="<?php echo $_POST['movie_id']; ?>"/>
            	<input type="submit" value="Cancel"/>
        	</form>

	</body>
</html>
