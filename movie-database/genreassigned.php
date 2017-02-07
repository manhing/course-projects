<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

    
if(!($stmt = $mysqli->prepare("INSERT INTO movie_genre (movie_id, genre_id) VALUES (?,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("si",$_POST['movie_id'],$_POST['genre_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " genre to movie.";
}
$stmt->close();
?>

	<form method="post" action="editmovie.php">
   	 <input type="hidden" name="movie_id" value="<?php echo $_POST['movie_id']; ?>"/>
    	<input type="submit" value="Make more edits"/>
	</form>

	<form method="post" action="database.php">

    	<input type="submit" value="Go back home"/>
	</form>

