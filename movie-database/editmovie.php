<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

$movie_id = $_POST["movie_id"];

?>

<!DOCTYPE html>
<html lang="en">
  <head>
	<meta charset="utf-8">
	<title>Movie Details</title>
  </head>
 
  <body>
	<h1>Edit Current Movie Details</h1>

	<?php
	/******************************************
	*This section displays movie title, year
	*******************************************/
	$display_details = "SELECT m.movie_id, m.title, m.release_year
                    	FROM movie m
                    	WHERE m.movie_id = '".$movie_id."'";

	$dbTable = $mysqli->query($display_details);

	if ($dbTable->num_rows > 0)
	{
    	while ($record = $dbTable->fetch_row())
    	{
?>


    	<!--form to change title-->
     	<form action="movietitleedited.php" method="post">
        	<fieldset>
<?php
            	echo "<b>Title:</b> ".$record[1];
?>

            	<br>
            	<legend>Change Title</legend>
          	<!--stores the movie_id sent via GET from the previous page-->
            	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />


            	Enter Title Here: <input type="text" name="title"/>
            	<input type="submit" value="Update Title" />
        	</fieldset>
    	</form>

    	<br>

    	<!--form to change year released-->
     	<form action="yearedited.php" method="post">
        	<fieldset>

<?php   	 
            	echo "<b>Year Released:</b> ".$record[2];
?>
            	<br>
            	<legend>Change Year Released</legend>

            	<!--stores the movie_id sent via GET from the previous page-->
            	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />

            	<!--stores the year from user input-->
            	Enter Year Released Here: <input type="text" name="release_year"/>
            	<input type="submit" value="Update Year" />
        	</fieldset>
    	</form>

    	<br>

<?php
    	}
	}


	/******************************************
	*This section displays director info
	*******************************************/
	$display_details = "SELECT d.director_id, d.first_name, d.last_name
                    	FROM movie m
                    	INNER JOIN director d ON m.director_id=d.director_id
                    	WHERE m.movie_id = '".$movie_id."'";

	$dbTable = $mysqli->query($display_details);

	if ($dbTable->num_rows > 0)
	{
    	while ($record = $dbTable->fetch_row())
    	{

?>

	<form method="post" action="directorassigned.php">
    	<fieldset>
        	<legend>Change Director</legend>
<?php
        	echo "<b>Director:</b> ".$record[1]." ".$record[2];
?>
        	<br>
        	Select Director:
            	<select name="director_id">

                	<?php
                	if(!($stmt = $mysqli->prepare("SELECT director_id, first_name, last_name FROM director ORDER BY first_name"))){
                    	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
                	}

                	if(!$stmt->execute()){
                    	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
                	}
                	if(!$stmt->bind_result($director_id, $first_name, $last_name)){
                    	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
                	}
                	while($stmt->fetch()){
                 	echo '<option value=" '. $director_id . ' "> ' . $first_name . " " . $last_name . '</option>\n';
                	}
                	$stmt->close();
                	?>

            	</select>
    	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />
    	<input type="submit" value="Update Director" />
    	<br>
    	*Note: If you do not see your desired director listed in the dropdown, please add one by <a href="add_director.php">going here</a>.
    	</fieldset>
	</form>
	<br>

<?php
    	}
	}

	/******************************************
	*This section displays genre
	*******************************************/
	$display_details = "SELECT g.genre_id, g.type
                    	FROM movie m
                    	INNER JOIN movie_genre mg ON mg.movie_id=m.movie_id
                    	INNER JOIN genre g ON g.genre_id=mg.genre_id
                    	WHERE m.movie_id = '".$movie_id."'";

	$dbTable = $mysqli->query($display_details);
?>
	<fieldset>
    	<legend>Add and Remove Genre(s)</legend>
<?php

	echo "<b>Genre(s):</b>";
	echo "<br>";

	echo "<table>";

	if ($dbTable->num_rows > 0)
	{
    	while ($record = $dbTable->fetch_row())
    	{
      	$genre_id = $record[0];

      	echo "<tr>";
      	echo "<td>" . $record[1] . "</td><td>";
?>

       	 
            	<!--creates a button to disassociate genre-->
             	<form action="genreremoved.php" method="post">
                	<input type="hidden" name="genre_id" value="<?php echo $genre_id; ?>" />
                	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />
                	<input type="submit" value="Remove Genre" />
            	</form>

            	</td>
        	</tr>
   	 
<?php
    	}
	}
?>
	</table>

	<!-- begin dropdown for genre -->
	<form method="post" action="genreassigned.php">

        	Select Additional Genre:
            	<select name="genre_id">

                	<?php
                	if(!($stmt = $mysqli->prepare("SELECT genre_id, type FROM genre ORDER BY type"))){
                    	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
                	}

                	if(!$stmt->execute()){
                    	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
                	}
                	if(!$stmt->bind_result($genre_id, $type)){
                    	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
                	}
                	while($stmt->fetch()){
                 	echo '<option value=" '. $genre_id . ' "> ' . $type . '</option>\n';
                	}
                	$stmt->close();
                	?>

            	</select>
    	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />
    	<input type="submit" value="Add Genre to Movie" />

	</form>
	*Note: If you do not see your desired genre listed in the dropdown, please add it by <a href="add_genre.php">going here</a>.
	</fieldset>



	<br>
	<fieldset>
    	<legend>Add/Edit Role(s) and Change the Star Playing the Role(s)</legend>
	<!--begin table for roles and stars-->


	<b>Cast:</b>
    

	<!--form to add new role-->
 	<form action="roleadded.php" method="post">

    	<!--stores the movie_id sent via POST from the previous page-->
    	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />

    	<!--stores the year from user input-->
    	Add New Role Here: <br>

    	First Name: <input type="text" name="role_first_name"/>
    	Last Name: <input type="text" name="role_last_name"/>
    	Other Name: <input type="text" name="role_other_name"/>

    	Select Star:
        	<select name="star_id">

            	<?php
            	if(!($stmt = $mysqli->prepare("SELECT star_id, first_name, middle_name, last_name FROM star ORDER BY first_name"))){
                	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
            	}

            	if(!$stmt->execute()){
                	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
            	}
            	if(!$stmt->bind_result($star_id, $star_first_name, $star_middle_name, $star_last_name)){
                	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
            	}
            	while($stmt->fetch()){
             	echo '<option value=" '. $star_id . ' "> ' . $star_first_name . " " . $star_middle_name . " " . $star_last_name . '</option>\n';
            	}
            	$stmt->close();
            	?>

        	</select>


    	<input type="submit" value="Add New Role" />
	</form>
	*Note: If you do not see your desired star listed in the dropdown, please add a star by <a href="add_star.php">going here</a>.
	<br>
	<br>
	<table>


<?php

	/*****************************************
	*This section displays roles and stars
	*******************************************/
	$display_details = "SELECT r.role_id, r.first_name, r.last_name, r.other_name,
                          	s.first_name, s.last_name, s.middle_name
                    	FROM movie m
                    	INNER JOIN role r ON r.movie_id=m.movie_id
                    	INNER JOIN star s ON r.star_id=s.star_id
                    	WHERE m.movie_id = '".$movie_id."'";

	$dbTable = $mysqli->query($display_details);


	if ($dbTable->num_rows > 0)
	{
    	while ($record = $dbTable->fetch_row())
    	{
      	$role_id = $record[0];
?>

    	<!--creates a button to delete movie-->
    	<tr>
        	<td>
            	<form action="roledeleted.php" method="post">
                	<input type="hidden" name="role_id" value="<?php echo $role_id; ?>" />
                	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />
                	<input type="submit" value="Delete Role" />
            	</form>
        	</td>


        	<td>
            	<form action="editrole.php" method="post">
                	<input type="hidden" name="role_id" value="<?php echo $role_id; ?>" />
                	<input type="hidden" name="movie_id" value="<?php echo $movie_id; ?>" />
                	<input type="submit" value="Edit Role..." />
            	</form>
        	</td>


<?php
      	echo "<td><b>Role: </b>";
      	echo $record[1] . " " . $record[2] . " " . $record[3] . "</td>";

      	echo "<td><b>  Played By: </b>";
      	echo $record[4] . " " . $record[5] . " " . $record[6] . "</td>";
      	echo "</tr>";
    	}
	}

?>

	</table>
	</fieldset>
	<br>
   <br>
   <a href='database.php'>Go Back Home</a>

  </body>
</html>


