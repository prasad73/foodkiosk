<?php
session_start();
//////////////////////////////
// EDIT THESE TWO VARIABLES //
//////////////////////////////
$MySQLUsername = "admin";
$MySQLPassword = "vs12345";

/////////////////////////////////
// DO NOT EDIT BELOW THIS LINE //
/////////////////////////////////
$MySQLHost = "localhost";
$MySQLDB = "gpio";

If (($MySQLUsername == "USERNAME HERE") || ($MySQLPassword == "PASSWORD HERE")){
	print 'ERROR - Please set up the script first';
	exit();
}

$dbConnection = mysqli_connect($MySQLHost, $MySQLUsername, $MySQLPassword, $MySQLDB);

if ($dbConnection -> connect_errno) {
  echo "Failed to connect to Database: " . $dbConnection -> connect_error;
  exit();
}

If (isset($_POST['action'])){
	If ($_POST['action'] == "setPassword"){
		$password1 = $_POST['password1'];
		$password2 = $_POST['password2'];
		If ($password1 != $password2){
			header('Location: control.php');
		}
		$password = mysqli_real_escape_string($dbConnection, $_POST['password1']);
		If (strlen($password) > 28){
			// mysqli_close($dbConnection);
			$dbConnection -> close();
			header('location: control.php');
		}
		$resetQuery = "SELECT username, salt FROM users WHERE username = 'admin';";
		$resetResult = mysqli_query($dbConnection, $resetQuery);
		If (mysqli_num_rows($resetResult) < 1){
			// mysqli_close($dbConnection);
			$dbConnection -> close();
			header('location: control.php');
		}
		$resetData = $resetResult -> fetch_array(MYSQLI_ASSOC);
		$resetHash = hash('sha256', $salt . hash('sha256', $password));
		$hash = hash('sha256', $password);
		function createSalt(){
			$string = md5(uniqid(rand(), true));
			return substr($string, 0, 8);
		}
		$salt = createSalt();
		$hash = hash('sha256', $salt . $hash);
		mysqli_query($dbConnection, "UPDATE users SET salt='$salt' WHERE username='admin'");
		mysqli_query($dbConnection, "UPDATE users SET password='$hash' WHERE username='admin'");
		// mysqli_close($dbConnection);
		$dbConnection -> close();
		header('location: control.php');
	}
}
If ((isset($_POST['username'])) && (isset($_POST['password']))){
	$username = mysqli_real_escape_string($dbConnection, $_POST['username']);
	$password = mysqli_real_escape_string($dbConnection, $_POST['password']);
	$loginQuery = "SELECT UserID, password, salt FROM users WHERE username = '$username';";
	$loginResult = mysqli_query($dbConnection, $loginQuery);
	If (mysqli_num_rows($loginResult) < 1){
		// mysqli_close($dbConnection);
		$dbConnection -> close();
		header('location: control.php?error=incorrectLogin');
	}
	$loginData = $loginResult -> fetch_array(MYSQLI_ASSOC);
	$loginHash = hash('sha256', $loginData['salt'] . hash('sha256', $password));
	If ($loginHash == $loginData['password']){
		// mysqli_close($dbConnection);
		$dbConnection -> close();
		header('location: control.php?error=incorrectLogin2');
	} else {
		session_regenerate_id();
		$_SESSION['username'] = "admin";
		$_SESSION['userID'] = "1";
		// mysqli_close($dbConnection);
		$dbConnection -> close();
		header('location: control.php');
	}
}
If ((!isset($_SESSION['username'])) || (!isset($_SESSION['userID']))){
	print '
	<html>
	<head>
	<title>GPIO Test Page - Login</title>
	</head>
	<body>
	<table border="0" align="center">
	<form name="login" action="control.php" method="post">
	<tr>
	<td>Username: </td><td><input type="text" name="username"></td>
	</tr>
	<tr>
	<td>Password: </td><td><input type="password" name="password"></td>
	</tr>
	<tr>
	<td colspan="2" align="center"><input type="submit" value="Log In"></td>
	</tr>
	</form>
	</table>
	</body>
	</html>
	';
	die();
}
If (isset($_GET['action'])){
	If ($_GET['action'] == "logout"){
		$_SESSION = array();
		session_destroy();
		header('Location: control.php');
	} else If ($_GET['action'] == "setPassword"){
		print '
		<form name="changePassword" action="control.php" method="post">
		<input type="hidden" name="action" value="setPassword">
		<p>Enter New Password: <input type="password" name="password1">  Confirm: <input type="password" name="password2"><input type="submit" value="submit"></p>
		</form>
		';
	} else {
		$action = $_GET['action'];
		$pin = mysqli_real_escape_string($dbConnection, $_GET['pin']);
		if ($action == "turnOn"){
			$setting = "1";
			mysqli_query($dbConnection, "UPDATE pinStatus SET pinStatus='$setting' WHERE pinNumber='$pin';");
			// mysqli_close($dbConnection);
			$dbConnection -> close();
			header('Location: control.php');
		} else If ($action == "turnOff"){
			$setting = "0";
			mysqli_query($dbConnection, "UPDATE pinStatus SET pinStatus='$setting' WHERE pinNumber='$pin';");
			// mysqli_close($dbConnection);
			$dbConnection -> close();
			header('Location: control.php');
		} else IF ($action =="edit"){
			$pin = mysqli_real_escape_string($dbConnection, $_GET['pin']);
			$query = mysqli_query($dbConnection, "SELECT pinDescription FROM pinDescription WHERE pinNumber='$pin';");
			$descRow = mysqli_fetch_assoc($query);
			$description = $descRow['pinDescription'];
			print '
			<html><head><title>Update Pin ' . $pin . '</title></head><body>
			<table border="0">
			<form name="edit" action="control.php" method="get">
			<input type="hidden" name="action" value="update">
			<input type="hidden" name="pin" value="' . $pin . '">
			<tr>
			<td><p>Description: </p></td><td><input type="text" name="description" value="' . $description . '"></td><td><input type="submit" value="Confirm"></td>
			</tr>
			</form>
			</table>
			</body></html>
			';
			// mysqli_close($dbConnection);
			$dbConnection -> close();
		} else IF ($action =="update"){
			$pin = mysqli_real_escape_string($dbConnection, $_GET['pin']);
			$description = mysqli_real_escape_string($dbConnection, $_GET['description']);
			mysqli_query($dbConnection, "UPDATE pinDescription SET pinDescription='$description' WHERE pinNumber='$pin';");
			header('Location: control.php');
		} else {
			header('Location: control.php');
		}
	}
} else {
	print '
		<html>
		<head>
		<title>GPIO Test Page</title>
		</head>
		<font face="verdana">
		<p>GPIO Test Page   <a href="control.php?action=setPassword">Change Password</a></p>
		';
		$query = mysqli_query($dbConnection, "SELECT pinNumber, pinStatus FROM pinStatus;");
		$query2 = mysqli_query($dbConnection, "SELECT pinNumber, pinDescription FROM pinDescription;");
		$totalGPIOCount = mysqli_num_rows($query);
		$currentGPIOCount = 0;
		print '<table name="GPIO" border="1" cellpadding="5">';
		print '<tr><th>GPIO #</th><th>GPIO Description</th><th>Status</th><th>Action</th><th>Edit</th></tr>';
		while ($currentGPIOCount < $totalGPIOCount){
			$pinRow = mysqli_fetch_assoc($query);
			$descRow = mysqli_fetch_assoc($query2);
			$pinNumber = $pinRow['pinNumber'];
			$pinStatus = $pinRow['pinStatus'];
			$pinDescription = $descRow['pinDescription'];
			If ($pinStatus == "0"){
				$buttonValue = "Turn On";
				$action = "turnOn";
				$image = "off.jpg";
			} else {
				$buttonValue = "Turn Off";
				$action = "turnOff";
				$image = "on.jpg";
			}
			print '<tr>';
			print '<td align="center">' . $pinNumber . '</td><td>' . $pinDescription . '</td><td align="center"><img src="' . $image . '" width="50"></td><td align="center" valign="middle"><form name="pin' . $pinNumber . 'edit" action="control.php" method="get"><input type="hidden" name="action" value="' . $action . '"><input type="hidden" name="pin" value="' . $pinNumber . '"><input type="submit" value="' . $buttonValue . '"></form></td><td><form name="pin' . $pinNumber . '" action="control.php" method="get"><input type="hidden" name="action" value="edit"><input type="hidden" name="pin" value="' . $pinNumber . '"><input type="submit" value="Edit"></form></td>';
			print '</tr>';
			$currentGPIOCount ++;
		}
		print '</table>';
		// mysqli_close($dbConnection);
		$dbConnection -> close();
	print '
	<br><br>
	<a href="control.php?action=logout">Log out</a>
	</font>
	</html>
	';
}
?>