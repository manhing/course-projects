<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
//updates movie title
if(!($stmt = $mysqli->prepare("UPDATE movie SET title=? WHERE movie_id =?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("ss", $_POST['title'], $_POST['movie_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Updated " . $stmt->affected_rows . " movie title.";
}
$stmt->close();


?>
	<!--button that goes back to editing movie-->
	<form method="post" action="editmovie.php">
   	 <input type="hidden" name="movie_id" value="<?php echo $_POST['movie_id']; ?>"/>
    	<input type="submit" value="Make more edits"/>
	</form>
	<!--button that goes back to homepage-->
	<form method="post" action="database.php">

    	<input type="submit" value="Go back home"/>
	</form>
</div>


