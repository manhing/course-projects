<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
//Inserts data into director table	
if(!($stmt = $mysqli->prepare("INSERT INTO director (first_name,last_name) VALUES (?,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("ss",$_POST['d_fname'],$_POST['d_lname']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " movie information to database.";
}
$stmt->close();
?>
	<!--Creates button to go back to adding movie-->
	<form method="post" action="addmovie.php"> 

		<p><input type="submit" value="Go back to Adding movie details"/></p>
	</form>
</div>