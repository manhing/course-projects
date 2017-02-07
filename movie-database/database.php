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
	<!--Create buttons for user to add,delete, edit movie information-->
	<form method="post" action="addmovie.php"> 

	<fieldset>
			<legend>Would you like to add, edit, delete a movie?</legend>

		<input type="submit" value="Add Movie"/>
	</form>

	<form method="post" action="choose_movie.php"> 
		<input type="submit" value="Edit Movie"/>
	</form>

	<form method="post" action="deletemovie.php"> 
		<input type="submit" value="Delete Movie"/>
	</form>
	</fieldset>

<div>
	<!--Creates drop down list for genre and directs user to filtered movies-->
	<form method="post" action="filter.php">
		<fieldset>
			<legend>Filter By Genre</legend>
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
				</select>
		</fieldset>
		<input type="submit" value="Run Filter" />
	</form>
</div>
  <head>
	<meta charset="utf-8">
   <title>Movie Database</title>
  </head>

  <body>  
	<h1>Movie Database</h1>

	<br>
	<br>


	<table >
  	<tr>
    	<th>Movie ID</th>
    	<th>Movie Title</th>
    	<th>Year Released</th>
    	<th>Director Name</th>
  	</tr>

	<!--Displays movie information-->
  	<?php

    	//querying done here
    	$filtering = "SELECT m.movie_id, m.title, m.release_year, d.first_name, d.last_name FROM movie m
    	INNER JOIN director d ON d.director_id=m.director_id
    	ORDER BY m.movie_id";

    	//display the results from the query by echoing table data
    	$dbTable = $mysqli->query($filtering);
    	if ($dbTable->num_rows > 0)
    	{
      	while ($record = $dbTable->fetch_row())
      	{
        	$idNum = $record[0];
        	echo "<tr><td>".$record[0].
        	"</td><td><a href='movie_details.php?id=".$record[0]."'>".$record[1]."</a></td>
        	<td>".$record[2]."</td>
        	<td>".$record[3]."</td>
        	<td>".$record[4]."</td>";
      	}
    	}

  	?>


  	</tr>
	</table>
	<br>
	<br>

  </body>
</html>






