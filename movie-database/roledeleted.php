<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

 //Deletes data from role   
if(!($stmt = $mysqli->prepare("DELETE FROM role WHERE role_id =?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("s",$_POST['role_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " role from database.";
}
$stmt->close();
?>

    <!--button that goes back to edit movie details and passes the movie_id back to it-->
	<form method="post" action="editmovie.php">
   	 <input type="hidden" name="movie_id" value="<?php echo $_POST['movie_id']; ?>"/>
    	<input type="submit" value="Make more edits"/>
	</form>

    <!--button that goes back to homepage-->
	<form method="post" action="database.php">

    	<input type="submit" value="Go back home"/>
	</form>
