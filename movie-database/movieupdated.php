<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
//Updates release year of specific movie
if(!($stmt = $mysqli->prepare("UPDATE movie SET release_year =? WHERE title=?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("is",$_POST['released_year'],$_POST['movie_title']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Updated " . $stmt->affected_rows . " movie information to database.";
}
$stmt->close();
?>
	<!--button that goes back to homepage-->
	<form method="post" action="database.php"> 
	<p><input type="submit" value="Go back"/></p>
	</form>
</div>

