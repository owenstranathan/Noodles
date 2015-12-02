<?php
	session_start();
	#Variables to hold database infro
	$host = "db1.cs.uakron.edu";
	$usr = "ods7";
	$pass = "dai5yi0R";
	$db = "ISP_ods7";
	#connect to the database
	$connection = mysqli_connect($host, $usr, $pass, $db) or die("Connection failed" . mysqli_error($connection));
	if(!$connection)
	{
		echo "Connection failed";
	}
	else
	{
		echo mysqli_error($connection);
		echo "Connected successfully";
	}

	//Query
	$sql = "SELECT * from users JOIN address ON users.address = address.id";

	$result = mysqli_query($connection, $sql);

	if(!$result)
	{
		echo "<p> query failed</p>";
		die(mysqli_error($connection));
	}




	if($_SERVER['REQUEST_METHOD'] === 'POST')
	{
		if (isset($_POST['addUser'])) 
		{
			$_SESSION['edit'] = false;	
			$_SESSION['add'] = true;
			//redirect to add-edit_User, while allowing for POST to finish
			header('Location: edit-add_User.php');
		}
		elseif(isset($_POST['editUser']))
		{
			$_SESSION['add'] = false;
			$_SESSION['edit'] = true;
			$_SESSION['user_id'] = $_POST['editUser'];
			echo $_POST['editUser'];
			//redirect to add-edit_User, while allowing for POST to finish
			header('Location: edit-add_User.php');
		}
		else
		{
			die("Something went horribly wrong, please reload the page. <br/> If the problem persists contact Owen @ ods7@zips.uakron.edu.");
		}
	}
	mysqli_close($connection);
?>
<html>
	<head>
		<title>UserListing</title>
		<link type="text/css" rel="stylesheet" href="stylesheet.css"/>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
		<!--<script type="text/javascript" src="script.js"></script>-->
	</head>
	<body>
		<form method="POST">
			<table id="userTable">
				<tr>
					<th>User Name</th>
					<th>First Name</th>
					<th>Last Name</th>
					<th>Gender</th>
					<th>Email</th>
					<th>Phone</th>
					<th>Street</th>
					<th>City</th>
					<th>State</th>
					<th>Zip Code</th>
				</tr>
				
				<?php
				
					while($row = mysqli_fetch_assoc($result))
					{
						echo 
							"<tr>
								<td>" . $row['user_id'] . "</td> 
								<td>" . $row['fname'] . "</td>
								<td>" . $row['lname'] . "</td>
								<td>" . $row['sex'] . "</td>
								<td>" . $row['email'] . "</td>
								<td>" . $row['phone'] . "</td>
								<td>" . $row['street'] . "</td>
								<td>" . $row['city'] . "</td>
								<td>" . $row['state'] . "</td>
								<td>" . $row['zip'] . "</td>
							 
							
								<td> <button type='submit' name='editUser' id='editUser' value=".$row['user_id'].">Edit User</button> </td>
							
							</tr>";
					}
				?>
			</table>
			
			<button type="submit" name="addUser" id="addUser">Add User</button>
		</form>

	</body>
</html>