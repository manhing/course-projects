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
	<!--Creates form for user input-->
	<form method="post" action="moviedeleted.php"> 

		<fieldset>
			<legend><b>Delete by movie title</b></legend>
			<p>Title: <input type="text" name="movie_title" /></p>
		
		</fieldset>
		<p><input type="submit" value="Delete Movie"/></p>
	</form>
</div>

<div>
<!--Creates list of movies and button next to it to let user easily delete movies-->
	<table>
    	<tr>
        	<h1>List of Movies</h1>
    	</tr>
    	<tr>
        	<td><b>Title</b></td>
        	<td><b>Year</b></td>
			<td><b>Director</b></td>
   	 
    	</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT m.title, m.release_year, d.first_name, d.last_name, m.movie_id FROM movie m INNER JOIN director d ON d.director_id=m.director_id ORDER BY m.movie_id"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($title, $release_year, $fname, $lname, $movie_id)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $title . "\n</td>\n<td>\n" . $release_year ."\n</td>\n<td>\n" . $fname ."\n</td>\n<td>\n" . $lname . "\n</td>\n<td>\n";
?>
    	<!--creates a button to delete movie-->
     	<form action="moviedeleted.php" method="post">
        	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />
        	<input type="submit" value="Delete Movie" />
    	</form>
    	</td>
	</tr>

<?php
}

$stmt->close();
?>
	</table>
</div>
  </body>
</html>
