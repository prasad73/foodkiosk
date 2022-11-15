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
$MySQLDB = "Vendigo_S1";

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
			header('Location: index.php?error=errorpage');
		}
		$password = mysqli_real_escape_string($dbConnection, $_POST['password1']);
		If (strlen($password) > 28){
			$dbConnection -> close();
			header('location: index.php');
		}
		$resetQuery = "SELECT username, salt FROM users WHERE username = 'admin';";
		$resetResult = mysqli_query($dbConnection, $resetQuery);
		If (mysqli_num_rows($resetResult) < 1){
			$dbConnection -> close();
			// header('location: index.php');
			echo "No user account available, contact admin!!!!!!";
		}
		
		// $UID = mysqli_fetch_assoc($resetResult);
		// $resetData = $resetResult -> fetch_array(MYSQLI_ASSOC);
		// $salt = $UID['salt'];
		// $resetHash = hash('sha256', $reserData['salt'] . hash('sha256', $password));
		// $resetHash = hash('sha256', $salt . hash('sha256', $password)); <<<<<
		$hash = hash('sha256', $password);
		
		function createSalt(){
			$string = md5(uniqid(rand(), true));
			return substr($string, 0, 8);
		}
		$salt = createSalt();
		$hash = hash('sha256', $salt . $hash);
		mysqli_query($dbConnection, "UPDATE users SET salt='$salt' WHERE username='admin'");
		mysqli_query($dbConnection, "UPDATE users SET password='$hash' WHERE username='admin'");
		$dbConnection -> close();
		header('location: index.php');
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
If ((isset($_POST['username'])) && (isset($_POST['password']))){
	$username = mysqli_real_escape_string($dbConnection, $_POST['username']);
	$password = mysqli_real_escape_string($dbConnection, $_POST['password']);
	$loginQuery = "SELECT UserID, password, salt FROM users WHERE username = '$username';";
	$loginResult = mysqli_query($dbConnection, $loginQuery);
	If (mysqli_num_rows($loginResult) < 1){
		$dbConnection -> close();
		header('location: 404.php');
	}
	$UID1 = mysqli_fetch_assoc($loginResult);
	// $loginData = $loginResult -> fetch_array(MYSQLI_ASSOC);
	$salt = $UID1['salt'];
	$pswd = $UID1['password'];
	// $loginHash = hash('sha256', $loginData['salt'] . hash('sha256', $password));
	$hash = hash('sha256', $password);
	$loginHash = hash('sha256', $salt . $hash);
	If ($loginHash != $pswd){
		$dbConnection -> close();
		header('location: 404.php');
	} else {
		session_regenerate_id();
		$_SESSION['username'] = "admin";
		$_SESSION['userID'] = "1";
		$dbConnection -> close();
		header('location: index.php');
	}
}
If ((!isset($_SESSION['username'])) || (!isset($_SESSION['userID']))){
	print '
	<html>
	<head>
	<title>Vendigo Master - Login</title>
	</head>
	<body>
	<table border="0" align="center">
	<form name="login" action="index.php" method="post">
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
		header('Location: index.php');
	} else If ($_GET['action'] == "setPassword"){
		print '
		<form name="changePassword" action="index.php" method="post" align="center">
		<input type="hidden" name="action" value="setPassword">
		<p>Enter New Password: <input type="password" name="password1">  Confirm: <input type="password" name="password2"><input type="submit" value="submit"></p>
		</form>
		';
	} else {
		$action = $_GET['action'];
		$pin = mysqli_real_escape_string($dbConnection, $_GET['pin']);
		if ($action == "turnOff"){
			$setting = "1";
			mysqli_query($dbConnection, "UPDATE BoxStatus SET BoxStatus='$setting' WHERE BoxNumber='$pin';");
			$dbConnection -> close();
			header('Location: index.php');
		} else if ($action == "turnOn"){
			$setting = "0";
			mysqli_query($dbConnection, "UPDATE BoxStatus SET BoxStatus='$setting' WHERE BoxNumber='$pin';");
			$dbConnection -> close();
			header('Location: index.php');
		} else if ($action =="edit"){
			$pin = mysqli_real_escape_string($dbConnection, $_GET['pin']);
			$query = mysqli_query($dbConnection, "SELECT OrderNumber FROM orders WHERE RefID='$pin';");
			$descRow = mysqli_fetch_assoc($query);
			$Order = $descRow['OrderNumber'];
			print '
			<html><head><title>Update Box ' . $pin . '</title></head><body>
			<table border="0" align="center">
			<form name="edit" action="index.php" method="get">
			<input type="hidden" name="action" value="update">
			<input type="hidden" name="pin" value="' . $pin . '">
			<tr>
			<td><p>OrderNumber: </p></td><td><input type="text" name="Order" value="' . $Order . '"></td><td><input type="submit" value="Confirm"></td>
			</tr>
			</form>
			</table>
			</body></html>
			';
			$dbConnection -> close();
		} else IF ($action =="update"){
			$pin = mysqli_real_escape_string($dbConnection, $_GET['pin']);
			$Order = mysqli_real_escape_string($dbConnection, $_GET['Order']);
			mysqli_query($dbConnection, "UPDATE orders SET OrderNumber='$Order' WHERE RefID='$pin';");
			header('Location: index.php');
		} else {
			header('Location: index.php');
		}
	}
} else {
	header("refresh: 3");
	print '
		<html>
		<head>
		<title>Vendigo Master</title>
		<style type="text/css">
		
		table {
		margin: 8px;
		}

		th {
		font-family: Arial, Helvetica, sans-serif;
		font-size: .7em;
		background: #666;
		color: #FFF;
		padding: 2px 6px;
		border-collapse: separate;
		border: 1px solid #000;
		}

		td {
		font-family: Arial, Helvetica, sans-serif;
		font-size: .7em;
		border: 1px solid #DDD;
		}
		</style>
		</head>
		<font-family: Arial, Helvetica, sans-serif;>
		<pre>           Vendigo Access console</pre>
		';
		$query = mysqli_query($dbConnection, "SELECT BoxNumber, BoxStatus FROM BoxStatus;");
		$query2 = mysqli_query($dbConnection, "SELECT BoxNumber, OrderNumber FROM orders;");
		$totalBoxes = mysqli_num_rows($query);
		$currentBox = 0;
		print '<table name="FoodRack" border="1" cellpadding="5" align="center">';
		print '<tr><th>Box #</th><th>Order Number</th><th>Status</th><th>Action</th><th>Edit</th></tr>';
		while ($currentBox < $totalBoxes){
			$BoxRow = mysqli_fetch_assoc($query);
			$OrderRow = mysqli_fetch_assoc($query2);
			$Box = $BoxRow['BoxNumber'];
			$BoxState = $BoxRow['BoxStatus'];
			$Orderno = $OrderRow['OrderNumber'];
			If ($BoxState == "1"){
				$buttonValue = "Open";
				$action = "turnOn";
				$image = "on.jpg";
			} else {
				$buttonValue = "Close";
				$action = "turnOff";
				$image = "off.jpg";
			}
			print '<tr>';
			print '<td align="center">' . $Box . '</td><td align="center">' . $Orderno . '</td><td align="center"><img src="' . $image . '" width="50"></td><td align="center" valign="middle"><form name="pin' . $Box . 'edit" action="index.php" method="get"><input type="hidden" name="action" value="' . $action . '"><input type="hidden" name="pin" value="' . $Box . '"><input type="submit" value="' . $buttonValue . '"></form></td><td><form name="pin' . $Box . '" action="index.php" method="get"><input type="hidden" name="action" value="edit"><input type="hidden" name="pin" value="' . $Box . '"><input type="submit" value="Edit"></form></td>';
			print '</tr>';
			$currentBox ++;
		}
		print '</table>';
		$dbConnection -> close();
	print '
	<br><br>
	<font-family: Arial, Helvetica, sans-serif;>
	<pre>      <a href="index.php?action=setPassword">Change Password</a>           <a href="index.php?action=logout">Log out</a></pre>
	</font>
	</html>
	';
}
?>


