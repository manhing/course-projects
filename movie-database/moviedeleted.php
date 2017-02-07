<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
//deletes movie
if(!($stmt = $mysqli->prepare("DELETE FROM movie WHERE title =?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("s",$_POST['movie_title']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " movie information to database.";
}
$stmt->close();

	
if(!($stmt = $mysqli->prepare("DELETE FROM movie WHERE movie_id =?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['movie_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " movie information to database.";
}
$stmt->close();
?>
	<!--button that goes back to homepage-->
	<form method="post" action="database.php"> 

		<p><input type="submit" value="Go back"/></p>
	</form>
</div>