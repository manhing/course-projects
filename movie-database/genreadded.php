<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
    
if(!($stmt = $mysqli->prepare("INSERT INTO genre (type) VALUES (?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("s",$_POST['type']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " genre to database.";
}
$stmt->close();
?>
	<form method="post" action="addmovie.php">

    	<p><input type="submit" value="Go back to Adding movie details"/></p>
	</form>
</div>
