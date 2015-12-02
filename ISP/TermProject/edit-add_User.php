<?php
	session_start();
	$add = $_SESSION['add'];
	$edit = $_SESSION['edit'];
	$val = "";
	$usrToEdit = "";
	

	$invalidUserName = false;
	

	#Variables to hold database infro
	$host = "db1.cs.uakron.edu";
	$usr = "ods7";
	$pass = "dai5yi0R";
	$db = "ISP_ods7";
	//$port = "3306";
	
	function validate_input($data){
		$data = trim($data);
		$data = stripslashes($data);
		$data = htmlspecialchars($data);
		return $data;
	}


	if($add)
	{
		$val = "add";
		
		//if the user posts
		if($_SERVER['REQUEST_METHOD'] === 'POST')
		{

			//Get form data
			$usr_id = validate_input($_POST['userid']);
			$fname = validate_input($_POST['fname']);
			$lname = validate_input($_POST['lname']);
			$email = validate_input($_POST['email']);
			$phone = validate_input($_POST['phone']);
			$street = validate_input($_POST['street']);
			$city = validate_input($_POST['city']);
			$state = validate_input($_POST['state']);
			$zip = validate_input($_POST['zip']);
			$sex = validate_input($_POST['sex']);



			#connect to the database
			$connection = mysqli_connect($host, $usr, $pass, $db) or die("Connection failed" . mysqli_connect_error());


			//Check the connection
			if(!$connection)
			{
				die("Connection failed" . mysqli_connect_error());
			}


			//Select the user name to make sure it's unique
			$sql = "SELECT * from users WHERE user_id = '$usr_id'";

			$result = mysqli_query($connection, $sql) or die("Error querying" . mysqli_error($connection));
			//If it's unique then insert the address
			if(mysqli_num_rows($result) == 0)
			{
				$address = "INSERT into address (street, city, state, zip) VALUES ('$street', '$city', '$state', '$zip')";
				if(mysqli_query($connection, $address))
				{
					echo "New record created successfully";
				}
				else
				{
					echo "Error: " . $address . mysqli_error($connection);
				}
				$addressKey = mysqli_insert_id($connection);
				//if the address was inserted ok then insert the user data
				$user = "INSERT into users (user_id, fname, lname, email, phone, sex, address) VALUES ( '$usr_id' , '$fname', '$lname', '$email', '$phone', '$sex', '$addressKey' )";
				if(mysqli_query($connection, $user))
				{
					echo "New record created successfully";
				}
				else
				{
					echo "Error: " . $user . mysqli_error($connection);
				}
			}
			else
			{
				$invalidUserName = true;
				//echo "<p style='color:red'> invalid username </p>";
			}
			mysqli_close($connection);

		}
	}
	elseif ($edit) 
	{
		$val = "edit";
		$usrToEdit = $_SESSION['user_id'];
		
		//connect to the database
		$connection = mysqli_connect($host, $usr, $pass, $db) or die("Connection failed" . mysqli_connect_error());
		//check the connection
		if(!$connection)
		{
			die("Connection failed" . mysqli_connect_error());
		}
		//query the database
		$sql = "SELECT * from users JOIN address ON (users.user_id = '$usrToEdit' AND users.address = address.id )";
		$result = mysqli_query($connection, $sql) or die("Error querying" . mysqli_error($connection));
		$row = mysqli_fetch_assoc($result);
		$address_id = $row['address'];

		//$address = "SELECT * from address WHERE id = " . $row['address'];
		//$addressResult = mysqli_query($connection, $address);
		//$addressRow = mysqli_fetch_assoc($addressResult);

		if($_SERVER['REQUEST_METHOD'] === 'POST')
		{
			$usr_id = validate_input($_POST['userid']);
			$fname = validate_input($_POST['fname']);
			$lname = validate_input($_POST['lname']);
			$email = validate_input($_POST['email']);
			$phone = validate_input($_POST['phone']);
			$street = validate_input($_POST['street']);
			$city = validate_input($_POST['city']);
			$state = validate_input($_POST['state']);
			$zip = validate_input($_POST['zip']);
			$sex = validate_input($_POST['sex']);

			//update address
			$update = "UPDATE address SET street='$street', city='$city', state='$state', zip='$zip' WHERE id='$address_id'";
			if(mysqli_query($connection, $update))
			{
				echo "<p style='color:green;'>record updated successfully</p>";
			}
			else
			{
				echo "<p style='color:red;'>record not updated</p>";
				echo "Error: " . mysqli_error($connection);
			}
			//update users
			$update = "UPDATE users SET fname='$fname', lname='$lname', email='$email', phone='$phone', sex='$sex' WHERE user_id='$usrToEdit' ";
			if(mysqli_query($connection, $update))
			{
				echo "<p style='color:green;'>record updated successfully</p>";
			}
			else
			{
				echo "<p style='color:red;'>record not updated</p>";
				echo "Error: " . mysqli_error($connection);
			}
		}



		
	}
	else
	{
		die("Something went horribly wrong, please reload the page. <br/> If the problem persists contact Owen @ ods7@zips.uakron.edu.");
	}
?>

<html>
	<head>
		<title>
			<?php
				if($add)
				{
					echo "Add New User";
				}
				elseif ($edit) 
				{
					echo "Edit User";
				}
			?>
		</title>
		<meta charset="UTF-8"></meta>
		<!--<link type="text/css" rel="stylesheet" href="stylesheet.css"/> -->
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
		<script type="text/javascript" src="script.js"></script>
	</head>
	<body>
		<div id="nav">
			<a  href="UserListing.php"> User Listing </a>
			
		</div>
		<br/>
		<?php
			if($add)
			{
				echo "<h1>Add User Form</h1>";
			}
			elseif ($edit) {
				echo "<h1>Edit User Form</h1>";
			}
		?>

		<form name="UserData" id="UserData" onsubmit="return validate()" method="POST">
			
			User Name:
			<input type="text" name="userid" id="userid" value="<?php echo $usrToEdit;?>"></input>
			<?php
				if($invalidUserName)
				{
					echo "<span style='color:red'> invalid username: '$usr_id' is already taken </span>";
				}
				else
				{
					$invalidUserName = true;
				}
			?>
			<br/>
			<br/>
			First Name:
			<input type="text" name="fname" id="fname" value="<?php if($edit){ echo $row['fname']; }?>" ></input>
			<br/>
			<br/>
			Last Name:
			<input type="text" name="lname" id="lname" value="<?php if($edit) echo $row['lname']; ?>"></input>
			<br/>
			<br/>
			Email
			<input type="text" name="email" id="email" value="<?php if($edit) echo $row['email']; ?>"></input>
			<br/>
			<br/>
			Phone:
			<input type="text" name="phone" id="phone" value="<?php if($edit) echo $row['phone']; ?>"></input>
			<br/>
			<br/>
			Street:
			<input type="text" name="street" id="street" value="<?php if($edit) echo $row['street']; ?>"></input>
			<br/>
			<br/>
			City:
			<input type="text" name="city" id="city"  value="<?php if($edit) echo $row['city']; ?>"></input>
			<br/>
			<br/>
			State:
			<input type="text" name="state" id="state" value="<?php if($edit) echo $row['state']; ?>"></input>
			<br/>
			<br/>
			Zip:
			<input type="text" name="zip" id="zip"  value="<?php if($edit) echo $row['zip']; ?>"></input>
			<br/>
			<br/>
			Sex:
			Male<input type="radio" name="sex" id="sex_Male" value="male" <?php if(edit) { if($row['sex'] === "male") echo 'checked'; } ?> ></input>
			Female<input type="radio" name="sex" id="sex_Female" value="female" <?php if(edit) { if($row['sex'] === "female") echo 'checked'; } ?> ></input>
			<br/>
			<br/>
			<button type="submit" name="submit" id="submit" value="<?php echo $val; ?>"  METHOD="POST">
				<?php
					if($add)
					{
						echo "Add User";
					}
					elseif($edit)
					{
						echo "Save";
					}
				?>
			</button>
		</form>
	</body>
</html>