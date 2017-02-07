<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<body>
<div>
	<table>
		<tr>
			<h1>Filtered Movies</h1>
		</tr>
		<tr>
			<td><b>Title</b></td>
			<td><b>Year</b></td>
			<td><b>Director</b></td>
			<td><b>Name</b></td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT movie.title, movie.release_year, director.first_name, director.last_name FROM genre 
INNER JOIN movie_genre ON movie_genre.genre_id=genre.genre_id
 INNER JOIN movie ON movie_genre.movie_id=movie.movie_id 
INNER JOIN director ON director.director_id=movie.director_id WHERE genre.genre_id=?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("i",$_POST['genre_type']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($title, $released_year, $d_fname, $d_lname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $title . "\n</td>\n<td>\n" . $released_year . "\n</td>\n<td>\n" . $d_fname . "\n</td>\n<td>\n" . $d_lname ."\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>

</body>
</html>