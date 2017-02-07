<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
if(!($stmt = $mysqli->prepare("DELETE FROM director WHERE director_id =?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("s",$_POST['director_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " director information to database.";
}
$stmt->close();
?>
	<!--Creates button to go back to the home page-->
	<form method="post" action="database.php">
	<p><input type="submit" value="Go back"/></p>
	</form>
	<!--Creates button to go back to delete movie-->
	<form method="post" action="deletemovie.php">
	<p><input type="submit" value="Delete More"/></p>
	</form>



