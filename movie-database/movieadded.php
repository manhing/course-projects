<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
if(!($stmt = $mysqli->prepare("INSERT INTO movie (director_id, title, release_year) VALUES 
((SELECT director_id FROM director d WHERE d.director_id=?), ?,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("iss",$_POST['director_name'],$_POST['movie_title'],$_POST['released_year']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " movie information to movie table.";
}
$stmt->close();

if(!($stmt = $mysqli->prepare("INSERT INTO movie_genre (movie_id, genre_id) VALUES
((SELECT movie_id FROM movie m WHERE m.title=?),(SELECT genre_id FROM genre g WHERE g.genre_id=?))"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("si",$_POST['movie_title'],$_POST['genre_type']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " movie information to movie_genre.";
}
$stmt->close();
if(!($stmt = $mysqli->prepare("INSERT INTO role (first_name, last_name, movie_id, star_id) VALUES
(?, ?, (SELECT movie_id FROM movie WHERE title=?), (SELECT star_id FROM star s WHERE s.star_id=?))"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("sssi",$_POST['r_fname'],$_POST['r_lname'],$_POST['movie_title'],$_POST['star_name']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " movie information to role.";
}
$stmt->close();
?>

<form method="post" action="database.php"> 

		<p><input type="submit" value="Go back"/></p>
	</form>
</div>

