<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <link rel="stylesheet" href="https://unpkg.com/purecss@1.0.0/build/pure-min.css" integrity="sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w" crossorigin="anonymous">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <title>View Group - Arduino Weather Station</title>
</head>
<body>
  <a href="/" style="text-decoration:none"><h1>Arduino Weather Station</h1></a>
  <h2>View Group</h2>

  <?php
  if (!is_numeric($_GET["id"])) { die(); }
  $mysqli = new mysqli("localhost", "root", 'pw', "weatherStation");
  $sql = "SELECT * FROM groups WHERE id = ".$_GET["id"];
  $statement = $mysqli->prepare($sql);
  $statement->execute();
  $row = $statement->get_result()->fetch_assoc();
  ?>
  <h3>ID: <?php echo $row["id"] ?></h3>
  <h3>Name: <?php echo $row["name"] ?></h3>
  <?php
  $sql = "SELECT COUNT(*) AS members FROM stations WHERE `group` = ".$row["id"];
  $statement = $mysqli->prepare($sql);
  $statement->execute();
  $members_amount_row = $statement->get_result()->fetch_assoc();
  echo "<h3>Member Stations: ".$members_amount_row["members"]."</h3>";
  ?>

  <table class="pure-table">
    <thead>
      <tr>
        <th>ID</th>
        <th>Name</th>
        <th>Location</th>
        <th>Measurements</th>
      </tr>
    </thead>

    <tbody>
      <?php
      $sql = "SELECT * FROM stations WHERE `group` = ".$_GET["id"];
      $statement = $mysqli->prepare($sql);
      $statement->execute();
      $result = $statement->get_result();

      while($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>".$row["id"]."</td>";
        echo "<td><a href=\"/view_station.php?id=".$row["id"]."\">".$row["name"]."</a></td>";
        echo "<td>".$row["location"]."</td>";

        $sql = "SELECT COUNT(*) AS measurements FROM measurements WHERE station_id = ".$row["id"];
        $statement = $mysqli->prepare($sql);
        $statement->execute();
        $measurements_amount_row = $statement->get_result()->fetch_assoc();
        echo "<td>".$measurements_amount_row["measurements"]."</td>";

        echo "</tr>";
      }
      ?>
    </tbody>
  </table>

  <?php
  $sql = "SELECT COUNT(*) AS measurements FROM measurements WHERE station_id = ANY (SELECT id FROM stations	WHERE `group` = ".$_GET["id"].")";
  $statement = $mysqli->prepare($sql);
  $statement->execute();
  $measurements_amount_row = $statement->get_result()->fetch_assoc();
  echo "<h3>Total Measurements: ".$measurements_amount_row["measurements"]."</h3>";
  ?>

  <table class="pure-table">
    <thead>
      <tr>
        <th>ID</th>
        <th>Measuring Station</th>
        <th>Time measured (Unix timestamp)</th>
        <th>Time measured (UTC)</th>
        <th>Temperature</th>
        <th>Humidity</th>
        <th>Relative Humidity</th>
      </tr>
    </thead>

    <tbody>
      <?php
      $sql = "SELECT * FROM measurements WHERE station_id = ANY (SELECT id FROM stations 	WHERE `group` = ".$_GET["id"].")";
      $statement = $mysqli->prepare($sql);
      $statement->execute();
      $result = $statement->get_result();

      while($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>".$row["id"]."</td>";
        echo "<td><a href=\"/view_station.php?id=".$row["station_id"]."\">".$row["station_id"]."</a></td>";
        echo "<td>".$row["time_measured"]."</td>";
        echo "<td>".date('Y-m-d h:m:s', $row["time_measured"])."</td>";
        echo "<td>".$row["temperature"]."</td>";
        echo "<td>".$row["humidity"]."</td>";
        echo "<td>".$row["relative_humidity"]."</td>";
        echo "</tr>";
      }
      ?>
    </tbody>
  </table>

</div>

<style>
.footer {
  position: fixed;
  left: 0;
  bottom: 0;
  width: 100%;
  text-align: right;
}
</style>
<div class="footer">
  <a href="https://www.iconfinder.com/icons/118959/clear_weather_icon">Favicon source</a>
</div>
</body>
</html>
