<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

    
	//Updates director information
if(!($stmt = $mysqli->prepare("UPDATE movie SET director_id=? WHERE movie_id =?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}


if(!($stmt->bind_param("ss", $_POST['director_id'], $_POST['movie_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {


	echo "Updated " . $stmt->affected_rows . " director for movie.";
}
$stmt->close();


?>
	<!--Creates button to go back to editing movies-->
	<form method="post" action="editmovie.php">
   	 <input type="hidden" name="movie_id" value="<?php echo $_POST['movie_id']; ?>"/>
    	<input type="submit" value="Make more edits"/>
	</form>
	<!--Creates button to go back to the home page-->
	<form method="post" action="database.php">

    	<input type="submit" value="Go back home"/>
	</form>
</div>
