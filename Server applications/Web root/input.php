<?php
//ini_set('display_errors', 1);
//ini_set('display_startup_errors', 1);
//error_reporting(E_ALL);

if ($_GET["password"] != "123456") //wrong or no password for auth to send measurements
{
  exit;
}

if ($_GET["station_id"] == "" || $_GET["temperature"] == "" || $_GET["relative_humidity"] == "") //some paramaters are missing
{
  exit;
}

$mysqli = new mysqli("localhost", "root", 'pw', "weatherStation");
if ($mysqli->connect_errno) {
    die("Connection failed: " . $mysqli->connect_error);
}

//https://www.w3schools.com/sql/sql_insert.asp
$sql = "INSERT INTO `weatherStation`.`measurements` (`station_id`, `temperature`, `relative_humidity`) VALUES (?, ?, ?);";
$statement = $mysqli->prepare($sql);
$statement->bind_param('sss', $_GET["station_id"], $_GET["temperature"], $_GET["relative_humidity"]);
$statement->execute();

//Update all humidity
$sql = "SELECT DISTINCT relative_humidity, temperature FROM `weatherStation`.`measurements` WHERE humidity IS NULL;";
$statement = $mysqli->prepare($sql);
$statement->execute();
$no_humidity_result = $statement->get_result();

//Now go through each unique row with a missing humidity
while($no_humidity_row = $no_humidity_result->fetch_assoc()) {
    //Look up the max_humidity for the current temperature in the reference table relative_humidity
    $sql = "SELECT max_humidity FROM `weatherStation`.`relative_humidity` WHERE temperature = ? LIMIT 1;";
    $statement = $mysqli->prepare($sql);
    $statement->bind_param('d', intval($no_humidity_row["temperature"]));
    $statement->execute();
    $relative_humidity_row = $statement->get_result()->fetch_assoc(); //Get the result and fetch it into an associative array in order to read the max_humidity out of it in the next step
    if ($relative_humidity_row["max_humidity"] == NULL) //max_humidity can't be looked up because reference table doesn't have a max_humidity value for the requested temperature
    {
      continue; //try with the next entry with a missing humidity
    }

    $humidity = $relative_humidity_row["max_humidity"] / 100 * $no_humidity_row["relative_humidity"]; //Calculate the humidity by dividing the max_humidity by 100, then multiplying it by the current humidity

    //Update all occurrences of the pair of temperature and relative_humidity values missing a humidity (one update for all of them)
    $sql = "UPDATE measurements SET humidity = ? WHERE relative_humidity = ? AND temperature = ?;";
    $statement = $mysqli->prepare($sql);
    $statement->bind_param('ddd', $humidity, $no_humidity_row["relative_humidity"], $no_humidity_row["temperature"]);
    $statement->execute();
}

//Dump measurements table to file
$filename = 'measurements.csv';
if (filesize($filename) == 0) //if file is empty (creates it if it does not exist)
{
  $sql = "SELECT station_id, time_measured, temperature, humidity, relative_humidity FROM `weatherStation`.`measurements`;"; //query all measurements
  file_put_contents($filename, "station_id".";"."time_measured".";"."temperature".";"."humidity".";"."relative_humidity"."\n"); //write CSV column header names to file
}
else {
  $sql = "SELECT station_id, time_measured, temperature, humidity, relative_humidity FROM `weatherStation`.`measurements` ORDER BY id DESC LIMIT 1;"; //only query the last measurement
  //Notice: Rows deleted from the table won't also be deleted in the file
}

$statement = $mysqli->prepare($sql);
$statement->execute();
$result = $statement->get_result();

//Now go through each measurement and write it into the file
while($row = $result->fetch_assoc()) {
  file_put_contents($filename, $row["station_id"].";".$row["time_measured"].";".$row["temperature"].";".$row["humidity"].";".$row["relative_humidity"]."\n", FILE_APPEND);
}

?>
