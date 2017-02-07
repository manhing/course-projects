<?php
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli(/*credentials here*/);
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

$movie_id = $_GET["id"];

?>

<!DOCTYPE html>
<html lang="en">
  <head>
	<meta charset="utf-8">
	<title>Movie Details</title>
  </head>
 
  <body>

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
      	$idNum = $record[0];
      	echo "<b>Title:</b> ".$record[1]."<br>";
      	echo "<b>Year Released:</b> ".$record[2]."<br>";
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
      	$idNum = $record[0];
      	echo "<b>Director:</b> ".$record[1]." ".$record[2];
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

	echo "<br>";
	echo "<b>Genre(s):</b>";
	echo "<br>";


	if ($dbTable->num_rows > 0)
	{
    	while ($record = $dbTable->fetch_row())
    	{
      	$idNum = $record[0];
      	echo $record[1]." <br>";
    	}
	}

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

	echo "<br>";
	echo "<b>Cast</b>";
	echo "<br>";

	if ($dbTable->num_rows > 0)
	{
    	while ($record = $dbTable->fetch_row())
    	{
      	$idNum = $record[0];
      	echo "<b>Role: </b>";
      	echo $record[1]." ".$record[2]." ".$record[3];

      	echo "<b>  Played By: </b>";
      	echo $record[4]." ".$record[5]." ".$record[6]."<br>";
    	}
	}

	?>
	<br>
   <br>

   <a href='database.php'>Go Back Home</a>

  </body>
</html>
