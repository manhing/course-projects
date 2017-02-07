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
	<form method="post" action="movieadded.php"> 

		<fieldset>
			<legend><b>Movie Information</b></legend>
			<p>Title: <input type="text" name="movie_title" /></p>
			<p>Year Released: <input type="text" name="released_year" /></p>
			<p>Character First Name: <input type="text" name="r_fname" /></p>
			<p>Character Last Name: <input type="text" name="r_lname" /></p>
			<p><legend>Choose Director</legend>
				<select name="director_name">
					<?php
					if(!($stmt = $mysqli->prepare("SELECT director_id, first_name, last_name FROM director ORDER BY first_name"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($id, $fname, $lname)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo '<option value=" '. $id . ' "> ' . $fname ." " . $lname .  '</option>\n';
					}
					$stmt->close();
					?>
				</select></p>
			<p><legend>Choose Actor/Actress</legend>
				<select name="star_name">
					<?php
					if(!($stmt = $mysqli->prepare("SELECT star_id, first_name, middle_name, last_name FROM star ORDER BY first_name"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($id, $fname, $mname, $lname)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo '<option value=" '. $id . ' "> ' . $fname ." " . $mname ." ". $lname .  '</option>\n';
					}
					$stmt->close();
					?>
				</select></p>
			<p><legend>Pick Genre</legend>
				<select name="genre_type">
					<?php
					if(!($stmt = $mysqli->prepare("SELECT genre_id, type FROM genre"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($id, $gname)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo '<option value=" '. $id . ' "> ' . $gname . '</option>\n';
					}
					$stmt->close();
					?>
				</select></p>
				<p><input type="submit" value="Submit Information"/></p>
		</fieldset>

	</form>
</div>
<div>
	<form method="post" action="add_director.php">
	<p> If information is not listed, please add to the list before adding movie.</p>
	<p><input type="submit" value="Add new director"/></p>
	</form>	<form method="post" action="add_star.php">
	<p><input type="submit" value="Add Actor/Actress"/></p>
	</form>
	</form>	<form method="post" action="add_genre.php">
	<p><input type="submit" value="Add Genre"/></p>
	</form>


<form method="post" action="database.php"> 

		<p><input type="submit" value="Go back"/></p>
	</form>
</div>
</body>
</html>
